/***
 *
 *2019-9-27 wby
 *
 ***/
#include <string>
#include "version_set.h"
#include "log_reader.h"

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
		File* file;
		Slice* save;
		s = env_->NewSequenceFile(file);
		LogReader reader(file,true,0);
		while(reader.NextBlock(save)){
			//aynalsis v_set;		
		}
	}
}
