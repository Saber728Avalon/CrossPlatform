project ( CrossPlatform 
		LANGUAGES C CXX )
cmake_minimum_required ( VERSION 2.8 )


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

#configure_file(
#	"${PROJECT_SOURCE_DIR}/PassageWay.cpp.in"
#	"${PROJECT_SOURCE_DIR}/PassageWay.cpp"
#)

set(LIST_MY_LIB_FILE LoadLibStatic)
if(MSVC)
else()
endif()

set(LIST_SYSTEM_LIB_FILE  "")
if(MSVC)
else()
	set(LIST_SYSTEM_LIB_FILE  ${LIST_SYSTEM_LIB_FILE} dl)
endif()

set(LoadLibrary_HDRS
	LoadLib.h
	types.h
	FileUtils.h
	LoadLib.h
	StringOper.h
	types.h
	DebugOut.h
	CommFunction.h
	DuanThread.h
	EncodeChange.h
	Singleton.h
	NumberOper.h
)

# 添加文件
set(LoadLibrary_SRC 
	FileUtils.cpp
	LoadLib.cpp
	StringOper.cpp
	DebugOut.cpp
	Uc2ToUtf8.cpp
	Utf8ToUc2.cpp
	TransFormCodeFormat.cpp
	NumberOper.cpp
)

#编译lib
add_library(CrossPlatformStatic STATIC ${LoadLibrary_SRC} ${LoadLibrary_HDRS})
