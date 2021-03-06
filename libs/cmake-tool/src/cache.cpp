#include "cmake-tool/cache.h"
#include <regex>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

namespace cmake
{
   Cache::Cache(std::string path) {
       path += "/CMakeCache.txt";
       if(!fs::exists(path)) { exist_file_=false; return; } 
       auto ss = std::stringstream{util::read_file_all(path)};
       std::string to;
       std::regex filter("^(?!#)(.*):(.*)=(.*)$");
       std::smatch what;
       while (std::getline(ss, to, '\n')) {
           if(std::regex_match(to, what, filter)) {
             variables.insert(std::make_pair(what[1], std::make_pair(what[2], what[3])));}
       }
   }
   
   bool Cache::exist(const std::string& name, const std::string& value) {
       if(auto data = variables.find(name); data != variables.end()) {
           if(data->second.second == value) return true;
           return false;
       }
       else {
           return false;
       }
   }
   
   Cmake Cmake::generator(const std::string& generator) {
       auto hook = [generator](auto& cache, auto& cmake_option){
           if(!cache->exist("CMAKE_GENERATOR", generator)) {
               if(!cmake_option) cmake_option = "";
               *cmake_option += "-G {} "_format(generator);
           }
       };
       after_hooks.push(hook);
       return *this;
   }
   
   Cmake Cmake::define(const std::string name, const std::string value, const std::string option_type) {
       auto hook = [name, value, option_type](auto& cache, auto& cmake_option){
           if(!cache->exist(name, value)) {
               if(!cmake_option) cmake_option = "";
               *cmake_option += "-{}{}={} "_format(option_type, name, value);
           }
       };
       after_hooks.push(hook);
       return *this;
   }
   
   Cmake Cmake::set(const std::string name, const std::string value, const std::string option_type) {
       if(!cache->exist(name, value)) {
           if(!cmake_option) cmake_option = "";
           *cmake_option += "-{}{}={} "_format(option_type, name, value);
       }
       return *this;
   }
   
   Cmake Cmake::generator_options(const std::string& option) {
       if(!generator_option) generator_option = "";
       *generator_option += option;
       return *this;
   }
   
   Cmake Cmake::set_target(const std::string& target) {
       target_ = target;
       return *this;
   }
   
   Cmake Cmake::build(const std::string& root, const std::string& build_path) {
       cache = Cache("{}/{}"_format(root, build_path));
       define("CMAKE_BUILD_TYPE", build_type);
       while(!after_hooks.empty()) { after_hooks.front()(cache, cmake_option); after_hooks.pop(); }
       if(prefix != "") set("CMAKE_INSTALL_PREFIX", prefix);
   
       auto script = "cd {}/{} && "_format(root, build_path);
       script += (no_cache || cmake_option || !cache->exist_file())  ? "cmake {}.. && "_format(*cmake_option) : "";
   
       auto target_script = target_ ? "--target {} "_format(*target_) : "";
       script += "cmake --build . {}--config {} -- {}"_format(target_script, build_type, *generator_option);
   
       auto is_sudo = (!(strcmp(util::system::what(), "windows")) || sudo) ? "sudo" : "";
       script += install ? " && {} cmake --install ."_format(is_sudo) : "";
       if(detail) fmt::print(script + "\n");
       system(script.c_str());
       return *this;
   }
}
