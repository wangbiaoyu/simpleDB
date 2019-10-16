/***
 *
 *2019-9-19 wby
 *
 ***/
#include "version_edit.h"

namespace kvDB
{
	void VersionEdit::Clear(){
		log_number_ = 0;
		next_log_number_ = 2;
	}
	
	void VersionEdit::SetLogNumber(SequenceNumber num){
		log_number_ = num;
	}
	
	void VersionEdit::SetNextLogNumber(SequenceNumber num){
		next_log_number_ = num;
	}

	void VersionEdit::EncodeTo(string& dst){
			
	}

	void VersionEdit::Decode(const std::string& ver){
		
	}

}
