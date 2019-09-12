/***
 *
 *2019-9-11 wby
 *
 ***/

#pragma once

#include <>

namespace kvDB
{
	class DB{
		
	public:

		DB();

		virtual Status Open(Option op,string& db_name,DB** ptr);

		virtual Status Get(ReadOption read_op,string& key,string* value);

		virtual Status Put(WriteOption write_op,string& key,string& value);

		virtual Status Delete(WriteOption );	

		virtual ~DB();

	private:

	};
}
