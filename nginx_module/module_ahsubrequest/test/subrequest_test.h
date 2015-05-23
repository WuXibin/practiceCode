#ifndef __SUBREQUEST_TEST_H__
#define __SUBREQUEST_TEST_H__

#include "../../module_ngx_common/plugin.h"

class CPluginTest: public plugin::CPlugin {
    public:
        int Init(const std::string& so_conf);     
        int Handle(plugin::CRequest& request);
        int SubreqHandle(plugin::CRequest& request);  

    private:
        std::string so_conf;
};

#endif
