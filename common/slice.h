/***
 *
 *2019-9-11 wby
 *
 ***/

#pragma once

#include <string>
#include <string.h>

using namespace std;
namespace common
{
	class Slice{
	
	public:
		Slice() : data_(NULL),size_(0) { }

		Slice(std::string& src) : data_(src.data()),size_(src.size()) {}

		Slice(const char* src) : data_(src),size_(strlen(src)) {}
	
		Slice(const char* src,size_t n) : data_(src),size_(n) {}

		bool empty() { return size_ == 0; }
		
		size_t size() { return size_; }
	
		void clear() { 
			data_ = "";
			size_ = 0;
		}

		char operator[](size_t n){
			assert(n < )
		}  

		
	private:
		const char* data_;
		size_t size_;
	};

}
