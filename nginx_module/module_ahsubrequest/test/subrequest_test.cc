#include <stdio.h>
#include <iostream>
#include "subrequest_test.h"

using namespace std;
using namespace plugin;

int CPluginTest::Init(const string& so_conf) {
    cout << so_conf << endl;

    return PLUGIN_OK;
}


int CPluginTest::Handle(CRequest& request) {
    cout << "~~~start time: " << request.start_time.tv_sec 
        << "." << request.start_time.tv_usec << endl;

    cout << "~~~param: " << endl;
    map<string, string>::iterator mbeg = request.param.begin();
    map<string, string>::iterator mend = request.param.end();
    for(; mbeg != mend; ++mbeg){
        cout << mbeg->first << "=" << mbeg->second << endl;
    }

    cout << "~~~host: " << request.headers_in.host << endl;
    cout << "~~~user_agent: " << request.headers_in.user_agent<< endl;
    cout << "~~~referer: " << request.headers_in.referer<< endl;
    cout << "~~~x_real_ip: " << request.headers_in.x_real_ip<< endl;

    cout << "~~~x_forwarded_for: " << endl;;
    for(size_t i = 0; i < request.headers_in.x_forwarded_for.size(); ++i) {
        cout << request.headers_in.x_forwarded_for[i] << endl;
    }

    cout << "~~~cookies: " << endl;;
    mbeg = request.headers_in.cookies.begin();
    mend = request.headers_in.cookies.end();
    for(; mbeg != mend; ++mbeg){
        cout << mbeg->first << "=" << mbeg->second << endl;
    }

    cout << "~~~request body: " << request.request_body << endl;
    /*
    size_t n = request.headers_in.cookies.size();
    for(size_t i = 0; i < n; ++i) {
        cout << request.headers_in.cookies[i] << endl;
    }
    */

    list<pair<string, string> >::iterator beg = request.headers_in.headers.begin();
    list<pair<string, string> >::iterator end = request.headers_in.headers.end();
    cout << "~~~headers in" << endl;
    for(; beg != end; ++beg) {
        cout << beg->first << " : " << beg->second << endl; 
    }

    request.subrequest.push_back(CSubrequest("/test1", "psids=9&pageid=1415962581311_8620"));        
    request.subrequest.push_back(CSubrequest("/test2", "psids=1234&pageid=1415962581311_8620"));        
    request.subrequest.push_back(CSubrequest("/test3", "areaid=21233"));        

    return PLUGIN_AGAIN;
}

int CPluginTest::SubreqHandle(CRequest& request) {
    for(size_t i = 0; i < request.subrequest.size(); ++i) {
        CSubrequest &sr = request.subrequest[i];
        cout << "subrequest: " << sr.uri << "?" << sr.args << endl;
        cout << "response: " << sr.response << endl;
        cout << "status: " << sr.status << endl;
        cout << "spend time: " << sr.sec << "." << sr.usec << endl;

        request.response_body.append(sr.response);
    }    

    request.headers_out.status = 302;
    //request.headers_out.status_line = "Nice to see you";
    request.headers_out.location = "http://www.baidu.com";
    request.headers_out.content_type= "text/plain";
    request.headers_out.charset= "utf-8";
    request.headers_out.headers.push_back(make_pair("Set-Cookie", "Hello=World"));
    //request.headers_out.headers.push_back(make_pair("Location", "http://www.baidu.com"));

    return PLUGIN_OK;
}

extern "C" {
    CPlugin* create_instance() {
        return new CPluginTest();
    }
}
