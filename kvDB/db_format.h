/***
 *
 *2019-10-17 wby
 *
 ***/ 

#pragma once
#include "slice.h"
#include <string>

namespace kvDB
{

namespace db{

	struct ValueType{
		kTypeDeletion = 0X0;
		kTypeVale = 0X1;
	};

	class InternalKey{
	
	private:
		std::string user_key;
		SequenceNumber seq;
		ValueType type;
	
	public:
						
		
	};
	
	struct FileMetaData{
		int refs;
		int allow_seeks;
		uint64_t file_size;
		uint64_t number;
		InternalKey smallest;
		InternalKey bigest;
	};

}

class InternalKeyCompator ： public Compator{
	
public:
	virtual bool Compare()

}

namespace config{
	static int kLevelNums = 7;
	//static int kFile
}

}
