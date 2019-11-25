#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>

#ifdef __MINGW32__
#include <windows.h>
#include <cstdlib>
#include <wchar.h>
#else
#include <dlfcn.h>
#endif

int main(int argc, char **argv) {

    #ifdef __MINGW32__
    std::vector<HINSTANCE> libhandle;
    std::string path = "plugins";
    #else
    std::vector<void*> libhandle;
    std::string path = "./plugins";
    #endif
    
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        
        #ifdef __MINGW32__
        auto libpath_p = entry.path();
        const wchar_t* libpath_wchar = libpath_p.c_str();
        char* libpath = new char[wcslen(libpath_wchar) + 1];

        std::wcstombs(libpath, libpath_wchar, wcslen(libpath_wchar) + 1);

        std::cout << "Loading plugin: " << libpath << std::endl;
        //printf("%s\n", librarypath);
        
        libhandle.push_back(LoadLibrary(libpath));
        
        delete[] libpath_wchar;
        delete[] libpath;
        #else

        const char* libpath = entry.path().c_str();
        std::cout << "Loading plugin: " << libpath << std::endl;

        libhandle.push_back(dlopen(entry.path().c_str(), RTLD_LAZY));
        #endif

        if (!libhandle.back()) {
            printf("ERROR: Could not open library.\n");
            return 1;
        }

        void (*initFunc) ();
        #ifdef __MINGW32__
        initFunc = (void(*)()) GetProcAddress(libhandle.back(), "init");
        #else
        initFunc = (void(*)()) dlsym(libhandle.back(), "init");
        #endif
        
        if(initFunc == NULL) {
            printf("ERROR: Could not read functions from library.\n");
            return 1;
        }

        initFunc();
        
        #ifdef __MINGW32__
        FreeLibrary(libhandle.back());
        #else
        dlclose(libhandle.back());
        #endif
    }
}
