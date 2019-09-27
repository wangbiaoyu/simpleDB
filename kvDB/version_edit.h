/***
 *
 *2019-9-18 wby
 *
 ***/
#pragma once
#include "dbformat.h"

namespace kvDB
{
	
	class VersionEdit{
		
	public:

		VersionEdit() { Clear(); }
		void Clear();
		void SetLogNumber(SequenceNumber num);
		void SetNextLogNumber(SequenceNumber num);
		
		void EncodeTo(const string& dst);
	private:
		bool has_log_number;
		bool has_next_log_number;
		SequenceNumber log_number_;
		SequenceNumber next_log_number_;
	};

}
