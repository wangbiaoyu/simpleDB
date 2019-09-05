/***
 *
 *2019-9-3 wby
 *
 ***/

#pragma once

#include <sys/time.h>
#include <string.h>
#include <string>
#include <iostream>

using namespace std;
namespace common
{
	extern string convertTimeString(){
		struct timeval tv;
		gettimeofday(&tv,NULL);
		const time_t seconds = tv.tv_sec;
		struct tm tmp;
		localtime_r(&seconds,&tmp);
		std::string year = std::to_string(tmp.tm_year+1900);
		std::string month = to_string(tmp.tm_mon+1);
		std::string day = to_string(tmp.tm_mday);
		std::string hour = to_string(tmp.tm_hour);
		std::string min = to_string(tmp.tm_min);
		std::string sec = to_string(tmp.tm_sec);
		return year+"-"+month+"-"+day+"."+hour+":"+min+":"+sec;
	}

	extern int32_t time_len(){
		return static_cast<int32_t>(convertTimeString().length());
	}
}
