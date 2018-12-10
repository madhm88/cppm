#ifndef __CPPM_OPTION_ADD_H__
#define __CPPM_OPTION_ADD_H__

#include "option/base_option.h"
#include "config/config.h"
#include <cpptoml.h>
#include <memory>

namespace cppm::option
{
    class Add : public base_option
    {
    public:
        Add(Config& config);
    private:
        void toolchain();
        void dependencies(Config config);
    };
}



#endif