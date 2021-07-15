project ( CrossPlatform 
		LANGUAGES C CXX )
cmake_minimum_required ( VERSION 2.8 )

include_directories(../src)


#生成调试用exe
OPTION(BUILD_TEST_EXECUTABLES "build exe" ON)

#lib后缀
set(MY_LIB_SUFFIX .lib)
if(MSVC)
	set(MY_LIB_SUFFIX .lib)
else()
	set(MY_LIB_SUFFIX .a)
endif()

set(MY_LIB_PREFFIX )
if(MSVC)
	set(MY_LIB_PREFFIX lib)
else()
	set(MY_LIB_PREFFIX  )
endif()

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
    add_definitions(-D_CRT_NONSTDC_NO_DEPRECATE)
endif()

IF(CMAKE_COMPILER_IS_GNUCXX)
	add_compile_options(-std=c++11)
	add_compile_options(-fPIC)
	add_compile_options(-fPIE)
	message(STATUS "option:-std=c++11")
ENDIF()

#设置lib的查找路径
IF(CMAKE_BUILD_TYPE MATCHES "Release")
	LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/bin/Release)
ELSE()
	LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/bin/Debug)
ENDIF() 


set(LIST_MY_LIB_FILE CrossPlatformStatic)
if(MSVC)
else()
endif()

set(LIST_SYSTEM_LIB_FILE  "")
if(MSVC)
elseif(XCODE)
	set(LIST_SYSTEM_LIB_FILE  ${LIST_SYSTEM_LIB_FILE} dl pthread)
else()
	set(LIST_SYSTEM_LIB_FILE  ${LIST_SYSTEM_LIB_FILE} dl pthread uuid)
endif()


#调试用exe
if(BUILD_TEST_EXECUTABLES)
	add_executable(TestLoadLib TestLoadLib.cpp)
	foreach(mylib ${LIST_MY_LIB_FILE})
		target_link_libraries(TestLoadLib ${mylib}${MY_LIB_SUFFIX})
	endforeach()
	foreach(systemlib ${LIST_SYSTEM_LIB_FILE})
		target_link_libraries(TestLoadLib ${systemlib})
	endforeach()
	add_library(TestLib SHARED TestLib.cpp)
endif()