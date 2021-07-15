#pragma once

#include <stdio.h>
#include "types.h"

#define USE_DLFCN 1

#ifdef _WIN32
//define something for Windows (32-bit and 64-bit, this part is common)
	#include <Windows.h>  
	#define LOAD_LIB_HANDLE HMODULE
#elif __APPLE__
    EXTERN_C_BEGIN
    #include <dlfcn.h>
    EXTERN_C_END
    #define LOAD_LIB_HANDLE  void* 
    #ifdef TARGET_IPHONE_SIMULATOR
    // iOS Simulator
    #elif TARGET_OS_IPHONE
    // iOS device
    #elif TARGET_OS_MAC
    // Other kinds of Mac OS
    #define LOAD_LIB_HANDLE HANDLE
    #else
    // Unsupported platform
    #endif
#elif __linux__
	EXTERN_C_BEGIN
		#include <dlfcn.h>
	EXTERN_C_END
	#define LOAD_LIB_HANDLE  void*
#elif __unix // all unices not caught above
// Unix
#elif __posix
// POSIX
#endif

EXTERN_C_BEGIN


enum LOAD_FLAGS
{
	// unix
	PR_LD_LAZY= 0x01,
	PR_LD_NOW = 0x02,
	PR_LD_GLOBAL = 0x04,
	PR_LD_LOCAL = 0x08,

	//windows
	CHARACTER_ASCII = 0x10,
	CHARACTER_UNICODE = 0x20,


	LOAD_FLAGS_COUNT
};

/**
	* @brief     加载lib
	* @note      
	* @returns   DUAN_DLL_EXPORT LOAD_LIB_HANDLE
	* @param[in] const char * pszPath
	* @param[in] LOAD_FLAGS encoding
	* @code      
	* @endcode    
	* @since     2020/09/21
*/
DUAN_DLL_EXPORT LOAD_LIB_HANDLE  PW_LoadLib(const char *pszPath, LOAD_FLAGS encoding);


/**
	* @brief     卸载lib
	* @note      
	* @returns   DUAN_DLL_EXPORT unsigned int
	* @param[in] LOAD_LIB_HANDLE lib
	* @code      
	* @endcode    
	* @since     2020/09/21
*/
DUAN_DLL_EXPORT unsigned int  PW_UnloadLib(LOAD_LIB_HANDLE lib);


/**
	* @brief     根据函数名，导出lib的函数
	* @note      
	* @returns   DUAN_DLL_EXPORT void*
	* @param[in] LOAD_LIB_HANDLE lib
	* @param[in] const char * name
	* @code      
	* @endcode    
	* @since     2020/09/21
*/
DUAN_DLL_EXPORT void*  PW_FindSymbolInLib(LOAD_LIB_HANDLE lib, const char *name);

EXTERN_C_END