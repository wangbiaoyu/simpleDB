/***
 *
 *2019-9-27 wby
 *
 ***/

#pragma once

#include <string>

#include "slice.h"
#include "version_set.h"

namespace kvDB
{
	enum ReadType{
		kZeroType = 0,
		kFullType= 1,
		kFirstType=2,
		kMiddleType=3,
		kLastType,
	};

	class LogReader
	{
		
	public:
		LogReader(VersionSet* v_set,Version* v);
		bool NextRecord(Slice* );
		ReadType ReadPhyscalRecord(std::string& record);
	private:
		VersionSet* v_set_;	
	};

}
