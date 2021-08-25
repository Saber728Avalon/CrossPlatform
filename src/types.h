 /**
 * @file		types.h
 * @brief		主要作用是为了软件夸平台的通用性
 * @author		duanqiang
 * @date		2020/08/19
 * @version 	1.0.0.1
 * @copyright	Copyright (C) 2009 duanqiang <email@2891018428@qq.com>
 */


/**********************************************************************平台宏 开始**************************************************************/
#if defined( _WIN32) ||  defined( _WIN64)
//define something for Windows (32-bit and 64-bit, this part is common)
	#define DUAN_DLL_EXPORT _declspec(dllexport)
	#define DUAN_DLL_IMPORT _declspec(dllimport)
#elif defined(__APPLE__)
    #define DUAN_DLL_EXPORT __attribute__((visibility("default")))
    #if TARGET_IPHONE_SIMULATOR
	// iOS Simulator
	#elif TARGET_OS_IPHONE
	// iOS device
	#elif TARGET_OS_MAC
	// Other kinds of Mac OS
	#else
	// Unsupported platform
	#endif
#elif defined(__linux__)
// linux
	#define DUAN_DLL_EXPORT __attribute__((visibility("default")))
#elif defined(__unix__) // all unices not caught above
// Unix
#elif defined(__posix)
// POSIX
#elif defined(__ANDROID__)
//android
#elif defined(_AIX)
//aix
#endif

/**********************************************************************平台宏 结束**************************************************************/


/******************************************声明为C函数 开始************************************/
#ifdef __cplusplus
	#define DUAN_EXTERN_C extern "C"
	#define EXTERN_C_BEGIN DUAN_EXTERN_C {
	#define EXTERN_C_END	}
#else
	#define DUAN_EXTERN_C extern
	#define EXTERN_C_BEGIN 
	#define EXTERN_C_END	
#endif // _cplusplus

/******************************************声明为C函数 结束************************************/

/*****************************************C++命名空间 开始**************************************/
#define NAME_SPACE_BEGIN(xxx) namespace xxx {
#define NAME_SPACE_END	}

#define DUAN_NAME_SPACE_BEGIN NAME_SPACE_BEGIN(duan)
#define DUAN_NAME_SPACE_END NAME_SPACE_END
/*****************************************C++命名空间 开始**************************************/

/***********************************************************函数调用方式 开始*******************************************************************/
//调用者释放堆栈

#ifdef __linux__
	#define DUAN_CDECL __attribute__((__cdecl__))

	//被调用者自己释放堆栈

	#define DUAN_STDCALL __attribute__((__stdcall__))

	//寄存器传值
	#define DUAN_FASTCALL  __attribute__((__fastcall__))
#else
	#define DUAN_CDECL __cdecl

	//被调用者自己释放堆栈

	#define DUAN_STDCALL __stdcall

	//寄存器传值
	#define DUAN_FASTCALL __fastcall
#endif

/***********************************************************函数调用方式 结束*******************************************************************/


/***********************************************************VS版本宏 开始*******************************************************************/
#if _MSC_VER <= 1310 //VS2003
#elif _MSC_VER <= 1400 //VS2005
#elif _MSC_VER <= 1500 //VS2008
#elif _MSC_VER <= 1600 //VS2010
#elif _MSC_VER <= 1700 //VS2012
#elif _MSC_VER <= 1800 //VS2003
#elif _MSC_VER <= 1900 //VS2015
#elif _MSC_VER <= 1910 //VS2017
#elif _MSC_VER <= 1928 //VS2019
#else
#endif

/***********************************************************VS版本宏 结束*******************************************************************************/


/***********************************************************GCC版本宏 开始*******************************************************************/
#if __GNUC__ <= 1 //GCC1
	#if __GNUC_MINOR__ <= 1  //GCC1.1
	#elif __GNUC_MINOR__ <= 2//GCC1.2
	#endif
#elif __GNUC__ <= 2 //GCC2
#elif __GNUC__ <= 3 //GCC3
#elif __GNUC__ <= 4 //GCC4
#elif __GNUC__ <= 5 //GCC5
#elif __GNUC__ <= 6 //GCC6
#elif __GNUC__ <= 7 //GCC7
#elif __GNUC__ <= 8 //GCC8
#elif __GNUC__ <= 9 //GCC9
#else
#endif

/***********************************************************GCC版本宏 结束*******************************************************************************/


/***********************************************************VC++ dll 中使用开始*******************************************************************************/

/***********************************************************VC++ dll 中使用结束*******************************************************************************/