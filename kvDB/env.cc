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

