/***
 *
 * 2019-9-2 wby
 *
 ***/

#pragma once

#include <stdio.h> 
#include <string.h>
#include <string>
#include <stdarg.h>

namespace common
{
	enum LogLevel{
		INFO=0,
		WARNING=1,
		DEBUG=2
	};
	extern void Logger(int level,const char* fmt, ...);
	//extern void setLevel();
	extern void setFileSize();
	extern void Logv(int level,va_list vl);

	class LogStream{
		void operator<<(int num);
		void operator<<(double num);
	};
}


#define LOG(level,fmt, args...) ::common::Logger(level,"[%s:%d]%s",__FILE__,__LINE__ ,fmt,##args)
