/***
 *
 *2019-9-27 wby
 *
 ***/

#pragma once

#include "version_set.h"

namespace kvDB
{
	class LogReader
	{
		
	public:
		LogReader(VersionSet* v_set,Version* v);
		Status NextRecord();

	private:
		VersionSet* v_set_;	
	};

}
