#include "option/init.h"
#include "option/cppkg.h"
#include "cppm/util/filesystem.h"
#include "cppm/core/config.hpp"
#include "cppm/core/cppm_tool.hpp"
#include "cppm/util/string.hpp"
#include <iostream>
#include <cstdlib>

using namespace fmt::literals;
using namespace cppm::util::str;

namespace cppm::option
{
    Init::Init() {
        app_.add_option("bin")
            .abbr("b")
            .desc("initialize new c++ binary project")
            .call_back([&](nlpo::arg::One arg){ make_bin(arg); }, "{binary name}");
        app_.add_option("lib")
            .abbr("l")
            .desc("initialize new c++ library project")
            .call_back([&](nlpo::arg::One arg){ make_lib(arg); }, "{library name}");
    }

    void Init::make_bin(const std::string& name) {
        auto gen = make_project(name);
        gen += "[[bin]]\n"
            +  "   name = {}\n"_format(quot(name))
            +  "   source = [{}]\n"_format("src/.*"_quot)
            ;

        auto project = core::Path::make((fs::current_path()/name).string());
        std::fstream file; 
        file.open(project.root/"cppm.toml", std::ios::out);
        file << gen;
        file.close();

        file.open(project.source/"main.cpp", std::ios::out);
        file << "#include <iostream>\nint main(int argc, char* argv[]) {\n    std::cout<<\"hello world\"<<std::endl;\n    return 0; \n}";
        file.close();
    } 

    void Init::make_lib(const std::string& name) {
        auto gen = make_project(name);
        gen += "[lib]\n"
            +  "   name = {}\n"_format(quot(name))
            +  "   type = {}\n"_format("shared"_quot)
            +  "   source = [{}]\n"_format("src/.*"_quot)
            ;

        auto project = core::Path::make((fs::current_path()/name).string());
        std::fstream file; 
        file.open(project.root/"cppm.toml", std::ios::out);
        file << gen;
        file.close();

        fs::create_directory(project.include/name);
    }

    std::string Init::make_project(const std::string& name, bool dupl_check) {
        if(dupl_check && fs::exists(name)) { std::cerr << "this name is exist" << std::endl; exit(1);}
        fs::create_directory(name);
        auto project = core::Path::make((fs::current_path()/name).string());
        fs::create_directory(project.build);
        fs::create_directory(project.cmake);
        fs::create_directory(project.include);
        fs::create_directory(project.source);
        fs::create_directory(project.thirdparty);
        fs::create_directory(project.cmake);
        fs::create_directory(project.cmake/"Modules");
        make_gitignore(project);

        auto cppm_path = core::cppm_root();
        util::over_write_copy_file("{0}cmake/cppm_loader.cmake"_format(core::cppm_root())
                                    ,"{0}/cppm_loader.cmake"_format(project.cmake));

        return "[package]\n"
             + "   name = {}\n"_format(quot(name))
             + "   version = {}\n"_format("0.0.1"_quot)
             + "   description = {}\n"_format(""_quot)
             + "\n"
             ;
    }

    void Init::make_gitignore(core::Path& project) {
        std::fstream file; 
        file.open(project.root/".gitignore", std::ios::out);
        file << "build/\n.ccls-cache\ncompile_commands.json\n"_format();
        file.close();
    }
}
