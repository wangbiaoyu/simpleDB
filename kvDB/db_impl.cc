/***
 *
 *2019-9-10 wby
 *
 ***/

#pragma once

#include "db.h"
#include "db_impl.h"
#include "status.h"

namespace kvDB
{
	
	DBImpl::DBImpl(Option op,const string& dbname)
	:	op_(op)
	,	dbname_(dbname)
	,	mem_(new memTable())
	, 	imm_(NULL)
    ,   
	{
					
	}

	Status DBImpl::Recover(VertionEdit edit){
		Status s;
		s = env_.CreatDir(dbname_);
        if(!s.ok()){
			::common::LOG(::common::ERROR,"create dir error");
		}
	    if(env_)	
	}

	Status DB::Open(Option op,const string& dbname,DB** ptr){
		ptr = NULL:
		DBImpl* impl = new DBImpl(op,dbname);
		VersionEdit edit;
		Status s = impl->Recover(edit);	
        if(!s.ok()){
            LOG(::common::BUG,"recover error!");
        }

	}	
    
    
}
