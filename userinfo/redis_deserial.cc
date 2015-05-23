#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <hiredis.h>

#include <string>
#include <iostream>

#include "userinfo.pb.h"

using namespace std;
using namespace AdServerCommon;

static void deserialize(const char *str, int len);

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
        deserialize(reply->str, reply->len);
    }

    return 0;
}

static void deserialize(const char *str, int len) {
    USER_INFO_S user_info;

    user_info.ParseFromArray(str, len);

    cout << user_info.DebugString() << endl; 
}
