#ifndef UTILCONFIG_H
#define UTILCONFIG_H

#include<map>
#include<string>

namespace UtilConfig {
    std::map<std::string, std::string> * loadConfig();
    std::string getConfValueByKey(std::string key);
}
#endif // UTILCONFIG_H
