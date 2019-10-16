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
		VersionSetBuilder build(this);
		s = env_->NewSequenceFile(file,manifest);
		LogReader reader(file,true,0);
		while(reader.NextBlock(save)){
			VersionEdit edit;
			s = edit.Decode(save);	
			if(!s.ok()) {}
			else{
				build.apply(edit);
			}								
		}
	}

class VersionSetBuilder{
	//字典升序
	public:
		VersionSetBuilder(VersionSet* v_set) ： v_set_(v_set)
		{
			
		}

		void apply(VersionEdit edit){
			
		}

	private:
		VersionSet v_set_；
	
}

}
