/***
 *
 *2019-9-18 wby
 *
 ***/

#include "env.h"
#include "status.h"
namespace kvDB
{
	//errno linux error string
	Env::Env() {};

	Status Env::CreateDir(const string& dbname){
		Status res;
		if(mkdir(dbname.c_str(),0755) != 0){
			res = IOError(dbname,errno);
		}
		return res;
	}

	Status Env::DeleteFile(const string& file){
		Status res;
		if(unlink(file.c_str()) != 0){
			res = IOError(file,errno);
		}	
		return res;
	}
	
	Status Env::GetManifestFileName(const string& dbname,string& manifest){
		Status s;
		file* fp = fopen(CurrentFile(),"r");
		if(!fp) { s = IOError("",errno); }
		const char buf[81];
		if(fgets(buf,fp) == NULL） { s = IOError("",errno); }
		std::string tmp(buf,strlen(fp));
		manifest = tmp;
		return s; 
	}

	Status Env::FileExist(const std::string& filename){
		Status s;
		if(access(filename.c_str(),F_OK) != 0){
			s = IOError("Invalid filename %s",errno);
		}
		return s;
	}
	
	Status Env::NewSequenceFile(SequenceFile* file,std::string filename){
		
	}

}
