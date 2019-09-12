/***
 *
 *2019-9-11 wby
 *
 ***/

#pragma once

#include <common/slice.h>

namespace common
{
	class State{
	
	public:
		State() { state_ = NULL; }
		
		~State()=default;

		static Status OK() { return Status(); }

		static Status IOError(const Slice& msg,const Slice& msg2 = Slice()){
			return Status(eIOError,msg,msg2);
		}

		static Status NotFound(const Slice& msg,const Slice& msg2 = Slice()){
			return Status(eNotFound,msg,msg2);
		}
		
		static Status InvalidArgument(const Slice& msg,const Slice& msg2 = Slice()){
			return Status(eInvalidArgument,msg,msg2);
		}

		Status(const Code& code,const Slice& msg,const Slice& msg2){
			assert(code != eOK);
			
		}

		bool ok() { return (state_ == NULL); }
	
		bool ioError() {return (code() == IOError); }

	private:
		char* state_;
		enum Code {
			eOK = 0,
			eIOError = 1,
			eNotFound = 2,
			eInvalidArgument = 3
		};

		Code code(){
			return 
		}

	};

}
