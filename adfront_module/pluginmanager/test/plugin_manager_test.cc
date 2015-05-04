#include "../iplugin.h"
#include "../plugin_config.h"
#include "../plugin_manager.h"

using namespace std;
using namespace sharelib;

int main() {
    PluginManager  plugin_manager;

    plugin_manager.Init("plugin_manager.conf"); 

    IPlugin *plugin = plugin_manager.GetPlugin("deliver");
    
    IPluginCtx *ctx = new IPluginCtx(); 

    plugin->Handle(ctx);

    return 0;
}
