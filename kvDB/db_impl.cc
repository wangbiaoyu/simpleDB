/***
 *
 *2019-9-10 wby
 *
 ***/

#pragma once

#include "db.h"
#include "db_impl.h"

namespace kvDB
{
	
	DBImpl::DBImpl(Option op,const string& dbname)
	:	op_(op)
	,	dbname_(dbname)
	,	mem_(new memTable())
	, 	imm_(NULL)
	{
					
	}

	Status DBImpl::Recover(VertionEdit){
		Status s;
		if(env_->CreatDir(dbname_) == false){
			::common::LOG(::common::ERROR,"create dir error");
		}
		
	}

	Status DB::Open(Option op,const string& dbname,DB** ptr){
		ptr = NULL:
		DBImpl* impl = new DBImpl(op,dbname);
		VersionEdit edit;
		Status s = impl->Recover(edit);	
	}	

}
