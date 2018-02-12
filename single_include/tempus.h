#ifndef TEMPUS_H_
#define TEMPUS_H_

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define WINDOWS_PLATFORM 1
#include <Windows.h>
#include <process.h>
#else
#define UNIX_PLATFORM 1
#define _GNU_SOURCE
#include <errno.h> // To access  program_invocation_name
#include <stdlib.h>
#include <unistd.h>
#endif

#ifndef TEMPUS_PREFIX
#define TEMPUS_PREFIX tempus
#endif

#define STRINGIFY(args) #args


#include <string>
#include <process.h>
#include <ctime>
#include <algorithm>

namespace tempus {


namespace  {
#ifdef WINDOWS_PLATFORM
         const char* Separator = "\\";
#else
         const char* Separator = "/";
#endif

    // internal helpers to deal with path
    template<class T>
    T base_name(T const & path, T const & delims = "/\\")
    {
      return path.substr(path.find_last_of(delims) + 1);
    }

    template<class T>
    T remove_extension(T const & filename)
    {
      typename T::size_type const p(filename.find_last_of('.'));
      return p > 0 && p != T::npos ? filename.substr(0, p) : filename;
    }

    inline std::string getBaseName(std::string const & path)
    {
        return remove_extension<std::string>( base_name<std::string>( path ));
    }


    inline std::string encodedTime()
    {
        std::time_t now = std::time(nullptr);
        char buffer[1024];
        int size = std::snprintf(buffer, 1024, "%llx", now );

        return std::string(buffer, size);
    }



}

extern std::string AppDirectory;

inline std::string getAppDirectory()
{
    if (AppDirectory.length() > 0 )
        return AppDirectory;

    // Define varibale used in all platform
    int pid = 0;
    std::string base_name, full_name;

    // Retreive temp path
#ifdef WINDOWS_PLATFORM

    // Get the temp root folder
    TCHAR tmp_path[MAX_PATH ];
    DWORD path_size = GetTempPathA(MAX_PATH , tmp_path);

    if (path_size == 0 || path_size > MAX_PATH ) {
        return std::string();
    }

    TCHAR app_name[MAX_PATH];
    GetModuleFileNameA(NULL, app_name, MAX_PATH );

    pid = _getpid();
    base_name = getBaseName(app_name);

#else



#endif

    // Generate temp directory
    char folder_name[1024];
    std::snprintf( folder_name, 1024, "%s%i%s", base_name.c_str(), pid, encodedTime().c_str());


    // Create directory
#ifdef WINDOWS_PLATFORM
    full_name = std::string(tmp_path) + std::string(folder_name);
    CreateDirectoryA(full_name.c_str(), NULL);
    AppDirectory = full_name;
#else



#endif

    return AppDirectory;
}

inline std::string tmpFilename(std::string const& name = "")
{
    std::string filename = name;
    if (name.length() == 0)
        filename = encodedTime();

    return getAppDirectory() + Separator + filename;
}

inline std::string tmpDir(std::string const& name = "")
{
    std::string filename = name;
    if (name.empty())
        filename = name;

    filename = getAppDirectory() + Separator + filename;

#ifdef WINDOWS_PLATFORM
    CreateDirectoryA(filename.c_str(), NULL);
#else

#endif

    return filename;
}


#ifdef TEMPUS_IMPL
std::string AppDirectory = "";
#endif


}
#endif
