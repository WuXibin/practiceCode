#include "upstream_plugin.h"
#include <iostream>

CAhUPPlugin::CAhUPPlugin():m_request(NULL)
{}

int CAhUPPlugin::SetRequest(CRequest * request)
{
    if (m_request) {
        delete m_request;
        m_request = NULL;
    }

    m_request = request;
}

CRequest * CAhUPPlugin::getRequest()
{
    return m_request;
}

CAhUPPlugin::~CAhUPPlugin()
{
    if (m_request) {
        delete m_request;
        m_request = NULL;
    }
}

int CAhTestUP::CreateRequest(STR_MAP & in, STR_MAP & out)
{
    STR_MAP::iterator iter;
    for (iter = in.begin(); iter != in.end(); ++iter) {
        cout << iter->first << ": "
            << iter->second << endl;
    }

    out["body"] = "upstream plugin body.";
}

int CAhTestUP::ProcessBody(STR_MAP &in, STR_MAP & out)
{

}

CAhUPPlugin * create_upstream_plugin() 
{
    return new CAhTestUP;
}
