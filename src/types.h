 /**
 * @file		types.h
 * @brief		��Ҫ������Ϊ�������ƽ̨��ͨ����
 * @author		duanqiang
 * @date		2020/08/19
 * @version 	1.0.0.1
 * @copyright	Copyright (C) 2009 duanqiang <email@2891018428@qq.com>
 */


/**********************************************************************ƽ̨�� ��ʼ**************************************************************/
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

/**********************************************************************ƽ̨�� ����**************************************************************/


/******************************************����ΪC���� ��ʼ************************************/
#ifdef __cplusplus
	#define DUAN_EXTERN_C extern "C"
	#define EXTERN_C_BEGIN DUAN_EXTERN_C {
	#define EXTERN_C_END	}
#else
	#define DUAN_EXTERN_C extern
	#define EXTERN_C_BEGIN 
	#define EXTERN_C_END	
#endif // _cplusplus

/******************************************����ΪC���� ����************************************/

/*****************************************C++�����ռ� ��ʼ**************************************/
#define NAME_SPACE_BEGIN(xxx) namespace xxx {
#define NAME_SPACE_END	}

#define DUAN_NAME_SPACE_BEGIN NAME_SPACE_BEGIN(duan)
#define DUAN_NAME_SPACE_END NAME_SPACE_END
/*****************************************C++�����ռ� ��ʼ**************************************/

/***********************************************************�������÷�ʽ ��ʼ*******************************************************************/
//�������ͷŶ�ջ

#ifdef __linux__
	#define DUAN_CDECL __attribute__((__cdecl__))

	//���������Լ��ͷŶ�ջ

	#define DUAN_STDCALL __attribute__((__stdcall__))

	//�Ĵ�����ֵ
	#define DUAN_FASTCALL  __attribute__((__fastcall__))
#else
	#define DUAN_CDECL __cdecl

	//���������Լ��ͷŶ�ջ

	#define DUAN_STDCALL __stdcall

	//�Ĵ�����ֵ
	#define DUAN_FASTCALL __fastcall
#endif

/***********************************************************�������÷�ʽ ����*******************************************************************/


/***********************************************************VS�汾�� ��ʼ*******************************************************************/
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

/***********************************************************VS�汾�� ����*******************************************************************************/


/***********************************************************GCC�汾�� ��ʼ*******************************************************************/
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

/***********************************************************GCC�汾�� ����*******************************************************************************/


/***********************************************************VC++ dll ��ʹ�ÿ�ʼ*******************************************************************************/

/***********************************************************VC++ dll ��ʹ�ý���*******************************************************************************/