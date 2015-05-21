#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <hiredis.h>

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

static void decode(const char *str, int len);

int main() {
    redisContext *c;
    string host = "127.0.0.1";
    int port = 6379;

    c = redisConnect(host.c_str(), port);
    if (c == NULL || c->err) {
        if (c) {
            cout << "Connection error: " << c->errstr << endl;;
            redisFree(c);
        } else {
            cout << "Connection error: can't allocate redis context" << endl;
        }
        exit(1);
    }

    string key;
    while(cin >> key) {
        redisReply *reply = (redisReply *)redisCommand(c, "GET %s", key.c_str()); 
        decode(reply->str, reply->len);
    }

    return 0;
}

static void decode(const char *str, int str_len) {
    size_t len = 0;
    size_t num_of_fields = str[len]; ++len;
    
    ostringstream oss;
    for(size_t i = 0; i < num_of_fields - 1; ++i) {
        size_t num_of_items = str[len]; ++len; 

        if(num_of_items == 0) {
            if(i != 0) 
                oss << "\t";

            oss << 0;
            continue;
        }

        for(size_t j = 0; j < num_of_items; ++j) {
            int n = *((int *)(str + len)); len += 4;

            int n1 = (n >> 16) & 0xFFFF;
            int n2 = (n >> 8) & 0xFF;
            int n3 = (n & 0xFF);

            float weight = n2 + n3 * 0.01;

            if(j != 0) 
                oss << ",";
            
            oss << n1 << ":" << weight;
        }

        if(i != 0) 
            oss << "\t";
    }

    /* group */
    int n = str[len];
    oss << "\t" << n;

    assert(str_len = len + 1);

    cout << oss.str() << endl;
}
