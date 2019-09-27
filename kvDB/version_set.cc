/***
 *
 *2019-9-27 wby
 *
 ***/

#include "version_set.h"

namespace kvDB
{

	VersionSet::VersionSet(const std::string& dbname,Env* env,TableCache* table)
	:	dbname_(dbname)
	,	env_(env)
	,	table_(table)
	{
		
	}

	Status VersionSet::Recover(){
		Status s;
		std::string manifest;
		s = env_->GetManifestFileName(dbname_,manifest);
		if(!s.ok()) { }
		s = env_->
	}
}
