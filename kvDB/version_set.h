/***
 *
 *2019-9-27 wby
 *
 ***/

#pragma once

#include <status.h>

namespace kvDB
{
	class VersionSet
	{
	
	public:
		VersionSet(const std::string& dbname, Env* env,TableCache* table);
		Status Recover();
		Status AppendVersion(Version* version);
		
			
	private:
		const std::string& dbname_;
		Env* env_;
		TableCache* table_;
	
	};

	class Version{
	
	public:
		Version(VersionSet* ver_set);

	private:
		Version* pre_;
		Version* next_;
	};
}	
