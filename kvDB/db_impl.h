/***
 *
 *2019-9-11 wby
 *
 ***/

#pragma once

#include "db.h"
#include "../common/status.h"

namespace kvDB
{
	class DBImpl : public DB{
	
	public:
		BImpl();

		//virtual Status Open(Option op,const string& dbname,DB** ptr);

		virtual Status Get(ReadOptions readOp,const Slice& key,const Slice& value);

		virtual Status Put(WriteOptions writeOp,const Slice& key,const Slice& value);

	private:
		Status NewDB();

	private:
		Env* env_;
		const std::string dbname_;		
		MemTable* mem_;
		MemTable* imm_;
		InternalKeyCompator* icmp_;
		VersionSet* v_set_;
	};
}
