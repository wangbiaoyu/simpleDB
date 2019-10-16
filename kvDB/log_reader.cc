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
	LogReader::LogReader(file* file,bool crc,uint64_t initial_offest)
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
					if()
					save->assign(record.data(),record.size());
					last_offest_ += record.length();
				break;
				case ReadType::kMiddleType:
					save->append(record.data(),record.size());
					last_offest_ += record.length();
				break;
				case ReadType::kLastType:
					save->append(record.data(),record.size());
					last_offest_ += record.length();
				break;
				case kEof:
					buffer_.clear();
					return false;
				case kBadType:
					buffer_.clear();
					return false;
			}
		}
		return false;	
	}

	//顺序读文件
	ReadType LogReader::ReadPhyscalRecord(std::string& record){
		Status s;
		while(true){
			if(buffer_.size() < kHeaderSize){
				if(!eof_){
					s = file_->Read(buffer_,kBlockSize);
					end_offest_ += buffer_.size();
					if(!s.ok()) { }//recover version_set error}
					else if(buffer_.size() < kBlockSize){
						eof_ = true;
						return kEof;
					}
					continue;
				}else{
					buffer_.clear();
					return kEof;
				}	
			}
			//prase the block finaly

		}
	}
}
