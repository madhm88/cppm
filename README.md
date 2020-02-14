
[Cppm](https://injae.github.io/cppm/) ***(BETA)*** 
========
|Linux|Windows|MacOS|
|:----|:------|:----|
![Linux](https://github.com/injae/cppm/workflows/Linux/badge.svg) | ![Windows](https://github.com/injae/cppm/workflows/Windows/badge.svg) | ![MacOS](https://github.com/injae/cppm/workflows/MacOS/badge.svg) |

![](cppm_demo.gif)
> Cppm is a cross platform C++ project manager like Rust's Cargo.   
> Cmake is as difficult to use as package manager in other languages.   
> So, like other package managers, to manage the C++ project,   
> we created the cppm.toml file so that we could create the Cmake project.   
> Cppm is made up of C++ and CMake only.   
> So with a Cmake and a C++ Compiler, you can build it anywhere on the platform that Cmake supports.  
> The goal of this project is to make the C++ project as comfortable as Rust's Cargo.  
> Not many libraries are supported by the cppkg yet.   
> So cppm made the package of the [Hunter Package Manager](https://github.com/ruslo/hunter) available.   
> If there is a library you want to add, please issue a pull request to the [Cppkg repository](https://github.com/injae/cppkg)  

## Installation
### Ubuntu
```
sudo apt-get install build-essential
git clone https://github.com/INJAE/cppm.git
cd cppm
cmake -Bbuild
cd build
cmake --build . 
./cppm build install
# Adding to cppm path
export PATH="$HOME/.cppm/local/bin:$PATH"
```
### Windows
```
# need visual studio 
git clone https://github.com/INJAE/cppm.git
cd cppm
cmake -Bbuild --Release
cd build
cmake --build . --config Release
cd Release
./cppm build install
# Add System Path \.cppm\local\bin
```

## Features
- [x] cmake dependencies auto installer (cppkg)
- [x] generate build command (cppm build {options})
- [x] Cppkg package search (cppm search)
- [x] cmake project initialize (cppm init {options} {name})
- [x] regist cppkg package in local repository (cppm add cppkg {name})
- [x] cppkg repository update (cppm update)
- [x] hunter package dependency available 
- [x] sub project option
- [ ] unit test option

## Document
### [GitBook](https://cppm.gitbook.io/project/)
### Beta: [GitBook](https://injae.github.io/cppm/)



