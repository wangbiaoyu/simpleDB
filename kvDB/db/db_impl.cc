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
	:	env_(op.env)
	,	dbname_(dbname)
	,	mem_(new MemTable())
	, 	imm_(NULL)   
	{
		v_set_ = new VersionSet(dbname_,env_,table_,icmp);					
	}

	Status DBImpl::Recover(VertionEdit edit){
		Status s;
		s = env_->CreateDir(dbname_);
        if(!s.ok()){
			::common::LOG(::common::ERROR,"create dir error");
		}
	    if(!env_->FileExist(CurrentFile(dbname_))){
			if(option.create_if_missing){
				s = NewDB();
			}else{
				
			}
		}else{
        	if(option.error_if_exist){
				
			}    
	    }		
		s = version_->Recover();
		if(s.ok()){
			SequenceNumber max_sequence = 0;
			const uint64_t min_log = versions_->LogNumber();
			const uint64_t prev_log = versions_->PrevLogNumber();
			std::vector<std::string> filenames;
			s = env_->GetChildren(dbname_,&filenames);
			if(!s.ok()){
				return s;
			}
			std::set<uint64_t> expected;
			versions_->AddLiveFiles(&expected);
			uint64_t number;
			FileType type;
			std::vector<uint64_t> logs;
			for(size_t i = 0; i < filenames.size();i++){
				if(ParseFileName(filenames[i],&number,&type)){
					expected.erase(number);
				}
				if(type == kLogFile && ((number >= min_log) || (number == prev_log))){
					logs.push_back(number);
				}
			}
			if(!expected.empty()){

			}
			std::sort(logs.begin(),logs.end());
		}
	}

	Status DBImpl::NewDB(){
		VersionEdit new_edit;
		new_edit.SetLogNumber(0);
		new_edit.SetNextLogNumber(2);
		
		std::string manifest = DescriptorFileName(dbname_,1);
		WritableFile* file;
		Status s = env_->NewWritableFile(manifest,&file);
		if(!s.ok()){
			return s;
		}	
		LogWriter log(file);
		std::string record;
		new_edit.Encode(record);
		s = log.AppendLog(record);
		if(s.ok()){
			file->Close();
		}
		delete file;
		if(s.ok()){
			s = SetCurrentFile(env,dbname_,1);
		}else{
			env_->DeleteFile(manifest);
		}
		return s;
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
