#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <hiredis.h>

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>

#include <boost/algorithm/string.hpp>

#include "zstring.h"
#include "userinfo.pb.h"

using namespace std;
using namespace AdServerCommon;

static void redis_hashtable(redisContext *c, const string& log_file);
static void redis_raw_string(redisContext*c, const string& log_file);
static void redis_zlib_string(redisContext*c, const string& log_file);
static void redis_encode_string(redisContext*c, const string& log_file);
static void redis_protobuf_string(redisContext *c, const string &log_file);

static void usage(int argc, char **argv);

int main(int argc, char **argv) {
    string host = "127.0.0.1";
    int port = 6379;
    int type = 0;
    string file;

    int opt;
    while((opt = getopt(argc, argv, "h:p:t:")) != -1) {
        switch(opt) {
            case 'h':
                host = string(optarg); 
                break;
            case 'p':
                port = atoi(optarg);
                break;
            case 't':
                type = atoi(optarg);
                break;
            default: /* '?' */
                usage(argc, argv); 
                exit(1);
        }
    }

    if(type < 1 || type > 5) {
        usage(argc, argv); 
        exit(1);
    }

    if(optind >= argc) {
        usage(argc, argv); 
        exit(1);
    }

    file = string(argv[optind]); 

    redisContext *c = redisConnect(host.c_str(), port);
    if (c == NULL || c->err) {
        if (c) {
            cout << "Connection error: " << c->errstr << endl;;
            redisFree(c);
        } else {
            cout << "Connection error: can't allocate redis context" << endl;
        }
        exit(1);
    }

    switch(type) {
        case 1:
            redis_hashtable(c, file);
            break;
        case 2:
            redis_raw_string(c, file);
            break;
        case 3:
            redis_zlib_string(c, file);
            break;
        case 4:
            redis_encode_string(c, file); 
            break;
        case 5:
            redis_protobuf_string(c, file); 
    }

    return 0;
}

static void redis_raw_string(redisContext *c, const string& log_file) {
    ifstream fs(log_file.c_str(), ios_base::in);
    if(!fs) {
        cerr << "Can't open " << log_file << endl;
        return;
    }

    string line;
    int count = 0;
    while(getline(fs, line)) {
        vector<string> fields;
        boost::split(fields, line, boost::is_any_of("\t"));
        assert(fields.size() == 10);

        string command = "SET " + fields[0];
        for(size_t i = 2; i < 10; ++i) {
            if(i == 2) {
                command += " " + fields[i];
                continue;
            }
            command += "\t" + fields[i]; 
        }
        
        freeReplyObject(redisCommand(c, command.c_str()));

        if(++count % 100 == 0) {
            cout << "insert " << count << endl;
        }        
    }
}

static void redis_zlib_string(redisContext *c, const string& log_file) {
    ifstream fs(log_file.c_str(), ios_base::in);
    if(!fs) {
        cerr << "Can't open " << log_file << endl;
        return;
    }

    char **argv = new char*[3];
    size_t *argvlen = new size_t[3];

    argv[0] = new char[3];              //command
    memcpy(argv[0], "SET", 3);
    argvlen[0] = 3;
    
    argv[1] = new char[64];             //key
    argv[2] = new char[10240];           //value

    string line;
    int count = 0;
    while(getline(fs, line)) {
        vector<string> fields;
        boost::split(fields, line, boost::is_any_of("\t"));
        assert(fields.size() == 10);

        string value;
        for(size_t i = 2; i < 10; ++i) {
            if(i == 2) {
                value += fields[i];
                continue;
            }
            value += "\t" + fields[i]; 
        }       

        string cstr = compress_string(value);
        //std::cerr << "Inflated data: "
        //          << val.size() << " -> " << cstr.size() << endl;

        memcpy(argv[1], fields[0].c_str(), fields[0].size());
        argvlen[1] = fields[0].size();

        memcpy(argv[2], cstr.c_str(), cstr.size());
        argvlen[2] = cstr.size();

        freeReplyObject(redisCommandArgv(c, 3, const_cast<const char **>(argv), argvlen));

        if(++count % 100 == 0) {
            cout << "insert " << count << endl;
        }
    }
}

static void redis_hashtable(redisContext *c, const string& log_file) {
    ifstream fs(log_file.c_str(), ios_base::in);
    if(!fs) {
        cerr << "Can't open " << log_file << endl;
        return;
    }

    string line;
    int count = 0;
    while(getline(fs, line)) {
        vector<string> fields;
        boost::split(fields, line, boost::is_any_of("\t"));
        assert(fields.size() == 10);
        
        string command = "HMSET";
        command += " " + fields[0];
        command += " spec " + (fields[2].empty() ? "\"\"" : fields[2]);
        command += " series " + (fields[3].empty() ? "\"\"" : fields[3]);
        command += " brand " + (fields[4].empty() ? "\"\"" : fields[4]);
        command += " level " + (fields[5].empty() ? "\"\"" : fields[5]);
        command += " price " + (fields[6].empty() ? "\"\"" : fields[6]);
        command += " sect " + (fields[7].empty() ? "\"\"" : fields[7]);
        command += " place " + (fields[8].empty() ? "\"\"" : fields[8]);
        command += " group " + (fields[9].empty() ? "\"\"" : fields[9]);

        freeReplyObject(redisCommand(c, command.c_str()));

        if(++count % 100 == 0) {
            cout << "insert " << count << endl;
        }
    }
}

static void redis_encode_string(redisContext *c, const string& log_file) {
    ifstream fs(log_file.c_str(), ios_base::in);
    if(!fs) {
        cerr << "Can't open " << log_file << endl;
        return;
    }

    assert(sizeof(int) == 4);

    char **argv = new char*[3];
    size_t *argvlen = new size_t[3];

    argv[0] = new char[3];              //command
    memcpy(argv[0], "SET", 3);
    argvlen[0] = 3;
    
    argv[1] = new char[64];             //key
    argv[2] = new char[4096];           //value

    string line;
    int count = 0;

    while(getline(fs, line)) {
        vector<string> fields;
        boost::split(fields, line, boost::is_any_of("\t"));
        assert(fields.size() == 10);

        memcpy(argv[1], fields[0].c_str(), fields[0].size());
        argvlen[1] = fields[0].size();
        
        char *buf = argv[2];
        size_t len = 0;

        /* field number */
        buf[len] = 8; ++len;                   

        for(size_t i = 2; i < 9; ++i) {
            vector<string> items;
            boost::split(items, fields[i], boost::is_any_of(","));           
            
            /* nil field */
            if(items.size() == 1 && items[0] == "0") {
                buf[len] = 0; ++len;                        
                continue;
            }
            
            /* field items number */
            buf[len] = items.size(); ++len;                 

            for(size_t j = 0; j < items.size(); ++j) {
                int n = 0, n1, n2, n3;
                sscanf(items[j].c_str(), "%d:%d.%d", &n1, &n2, &n3); 
                n |= ((n1 & 0xFFFF) << 16);
                n |= ((n2 & 0xFF) << 8);
                n |= (n3 & 0xFF);

                /* encode every item into a 4 bytes integer value */
                *((int *)(buf + len)) = n; len += 4;        
            }
        }

        /* group */
        int n;
        sscanf(fields[9].c_str(), "%d", &n);
        buf[len] = n & 0xFF; ++len;

        argvlen[2] = len;

        freeReplyObject(redisCommandArgv(c, 3, const_cast<const char **>(argv), argvlen));

        if(++count % 100 == 0) {
            cout << "insert " << count << endl;
        }
    }
}

static void redis_protobuf_string(redisContext *c, const string &log_file) {
    ifstream fs(log_file.c_str(), ios_base::in);
    if(!fs) {
        cerr << "Can't open " << log_file << endl;
        return;
    }

    char **argv = new char*[3];
    size_t *argvlen = new size_t[3];

    argv[0] = new char[3];              //command
    memcpy(argv[0], "SET", 3);
    argvlen[0] = 3;
    
    argv[1] = new char[64];             //key
    argv[2] = new char[10240];           //value

    string line;
    int count = 0;
    while(getline(fs, line)) {
        vector<string> fields;
        boost::split(fields, line, boost::is_any_of("\t"));
        assert(fields.size() == 10);

        memcpy(argv[1], fields[0].c_str(), fields[0].size());
        argvlen[1] = fields[0].size();

        USER_INFO_S user_info;

        // brand
        vector<string> items;
        boost::split(items, fields[2], boost::is_any_of(","));           

        for(size_t i = 0; i < items.size(); ++i) {
            int n; float f;
            if(sscanf(items[i].c_str(), "%d:%f", &n, &f) != 2) break;

            USER_INFO_S::USER_TAG_S *user_tag = user_info.add_m_user_auto_brand(); 
            user_tag->set_tag(n);
            user_tag->set_score(f);
        }
        
        // serie
        items.clear();
        boost::split(items, fields[3], boost::is_any_of(","));           
        for(size_t i = 0; i < items.size(); ++i) {
            int n; float f;
            if(sscanf(items[i].c_str(), "%d:%f", &n, &f) != 2) break;

            USER_INFO_S::USER_TAG_S *user_tag = user_info.add_m_user_auto_serie(); 
            user_tag->set_tag(n);
            user_tag->set_score(f);
        }

        // level
        items.clear();
        boost::split(items, fields[4], boost::is_any_of(","));           

        for(size_t i = 0; i < items.size(); ++i) {
            int n; float f;
            if(sscanf(items[i].c_str(), "%d:%f", &n, &f) != 2) break;

            USER_INFO_S::USER_TAG_S *user_tag = user_info.add_m_user_auto_level(); 
            user_tag->set_tag(n);
            user_tag->set_score(f);
        }
        
        // price
        items.clear();
        boost::split(items, fields[5], boost::is_any_of(","));           
        for(size_t i = 0; i < items.size(); ++i) {
            int n; float f;
            if(sscanf(items[i].c_str(), "%d:%f", &n, &f) != 2) break;

            USER_INFO_S::USER_TAG_S *user_tag = user_info.add_m_user_auto_price(); 
            user_tag->set_tag(n);
            user_tag->set_score(f);
        }
        
        // spec
        items.clear();
        boost::split(items, fields[6], boost::is_any_of(","));           

        for(size_t i = 0; i < items.size(); ++i) {
            int n; float f;
            if(sscanf(items[i].c_str(), "%d:%f", &n, &f) != 2) break;

            USER_INFO_S::USER_TAG_S *user_tag = user_info.add_m_user_auto_spec(); 
            user_tag->set_tag(n);
            user_tag->set_score(f);
        }
        
        // sect
        items.clear();
        boost::split(items, fields[7], boost::is_any_of(","));           
        for(size_t i = 0; i < items.size(); ++i) {
            int n; float f;
            if(sscanf(items[i].c_str(), "%d:%f", &n, &f) != 2) break;

            USER_INFO_S::USER_TAG_S *user_tag = user_info.add_m_user_auto_sect(); 
            user_tag->set_tag(n);
            user_tag->set_score(f);
        }
        
        // place
        items.clear();
        boost::split(items, fields[8], boost::is_any_of(","));           
        for(size_t i = 0; i < items.size(); ++i) {
            int n; float f;
            if(sscanf(items[i].c_str(), "%d:%f", &n, &f) != 2) break;

            USER_INFO_S::USER_TAG_S *user_tag = user_info.add_m_user_auto_place(); 
            user_tag->set_tag(n);
            user_tag->set_score(f);
        }

        // group
        int group;
        sscanf(fields[9].c_str(), "%d", &group);
        user_info.set_m_user_group(group);

        string user_str;
        user_info.SerializeToString(&user_str);
        memcpy(argv[2], user_str.c_str(), user_str.size());
        argvlen[2] = user_str.size();
        
        freeReplyObject(redisCommandArgv(c, 3, const_cast<const char **>(argv), argvlen));

        if(++count % 1000 == 0) {
            cout << "insert " << count << endl;
        }
    }
}

static void usage(int argc, char **argv) {
    printf("Usage: %s [-h host] [-p port] -t type file\n"
           "\t-h <hostname>   Server hostname (default: 127.0.0.1).\n"
           "\t-p <port>       Server port (default: 6379).\n"
           "\t-t <type>       Memory storage type: 1-hashtable, 2-raw string, "
           "3-zlib string, 4-encode string, 5-protobuf encoding\n"
           "\t<file>          userinfo file\n", argv[0]);
}
