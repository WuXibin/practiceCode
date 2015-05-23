#include <stdio.h>
#include "plugin.h"

using namespace plugin;
using std::string;

class CTestUp : public plugin::CPlugin
{
public:
    CTestUp();
    int Init(const std::string & conf);

    int CreateRequest(plugin::CRequest & request);

    int ProcessBody(plugin::CRequest & request);

private:
};

extern "C" {
    CPlugin * create_instance()
    {
        return new CTestUp;
    }
}

CTestUp::CTestUp()
{
}

int CTestUp::Init(const std::string & conf)
{
    printf("CTestUp Init conf_path: %s\n", conf.c_str());
    return PLUGIN_OK;
}

int CTestUp::CreateRequest(CRequest & request)
{
    printf("CTesetUp::CreateRequest:\n\
            headers_in->\n\
            \t\thost: %s\n\
            \t\tuser_agent: %s\n\
            \t\treferer: %s\n\
            \t\tx_real_ip: %s\n  \
            request_body->\n%s\n",
            request.headers_in.host.c_str(),
            request.headers_in.user_agent.c_str(),
            request.headers_in.referer.c_str(),
            request.headers_in.x_real_ip.c_str(),
            request.request_body.c_str());     

    request.response_body = "this body come from CTestUp, need send to adserver.";
    return PLUGIN_OK;
}

int CTestUp::ProcessBody(CRequest & request)
{
    printf("response come from adserver: %s\n",
                request.response_body.c_str());
    return PLUGIN_OK;
}
