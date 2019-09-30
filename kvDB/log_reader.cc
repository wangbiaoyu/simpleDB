/***
 *
 *2019-9-27 wby
 *
 ***/

#include <stdio.h>
#include "log_reader.h"
#include "slice.h"

namespace kvDB
{
	LogRdeader::LogReader(file* file,bool crc,uint64_t initial_offest)
	:	file_(file)
	,	crc_(crc)
	,	initial_offest_(initial_offest)
	, 	last_offest_(0)
	,	end_offest_(0)
	{
									
	}

	bool LogReader::NextBlock(Slice* save){
		if(last_offest_ > initial_offest_){
			
			return false;	
		}
		save->clear();
		while(true){
			//uint64_t physic
			std::string record;
			ReadType type = ReadPhyscalRecod(record);
			switch(type){
				case ReadType::kZeroType:
				break;
				case ReadType::kFullType:
					return true;
				case ReadType::kFirstType:
				break;
				case ReadType::kMiddleType:
				break;
				case ReadType::kLastType:
				break;
			}
		}	
	}

	ReadType LogReader::ReadPhyscalRecord(std::string& record){
		Status s;
		while(true){
					
			s = file_->Read(buffer_,kBlockSize);
			end_offest_ += buffer_.size();
			if(!s.ok()) { }
			else if(buffer_.size() < kBlockSize){
				return kLastType;
			}else{
						
			}	
							 	
		}
	}
}
