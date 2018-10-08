#ifndef __CPPM_CONFIG_CMAKE_H__
#define __CPPM_CONFIG_CMAKE_H__

#include "config/base_config.h"
#include <vector>

namespace cppm
{
    class Cmake : public base_config
    {
    public:
        void parse(table_ptr table);
    public:
        std::string name;
        std::string version;
        std::string option;
    };
}


#endif
