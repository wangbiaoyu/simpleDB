/***
 *
 *2019-9-15 wby
 *
 ***/

#pragma once

namespace kvDB
{
	class Env{
	
	public:
		Env();
		~Env();
		void CreateDir(const string& dbname);
		void CreateFile(const string& file);
		void DeleteFile(const string& file);
	private:
		
	};
}
