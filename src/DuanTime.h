#pragma  once
 /**
 * @file		DuanTime.h
 * @brief		封装C++ 时间类
 * @author		duanqiang
 * @date		2020/12/16
 * @version 	1.0.0.1
 * @copyright	Copyright (C) 2009 duanqiang <email@2891018428@qq.com>
 */

#include <sys/timeb.h>
#include <time.h>
#include <stdint.h>








/**
	* @brief     得到从1970-1-1 00:00:00到现在的秒数
	* @note      
	* @returns   time_t
	* @code      
	* @endcode    
	* @since     2020/12/16
*/
static time_t DQGetCurSec()
{
	return time(NULL);
}



/**
	* @brief     得到系统当前的时间戳
	* @note      
	* @returns   uint64_t
	* @code      
	* @endcode    
	* @since     2021/01/13
*/
static uint64_t DQTimeStamp()
{
	struct timeb rawTime;
	ftime(&rawTime);
	uint64_t u64Timestamp = rawTime.time * 1000 + rawTime.millitm;
	return u64Timestamp;
}