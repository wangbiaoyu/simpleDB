/***
 *
 *2019-9-2 wby
 *
 ***/
#include "log.h"
#include "mutex.h"
#include "util.h"
#include "thread.h"

#include <stdarg.h>
#include <assert.h>
#include <queue>
#include <stdio.h>

using namespace std;
namespace common
{
	int default_log_size_ = 8 * 2^10 * 2^10;
	FILE* log_file_;
	
	void getNewLog(){
		string file_path;
		string pre = ::common::convertTimeString();
		string fix = ".log.txt";
		file_path = pre + fix;
		log_file_ = fopen(file_path.c_str(),"a+");
		assert(log_file_);
	}

	typedef queue<char*> Queue;
	class AsyncLog
	{
		public:
			AsyncLog() 
			: mu_(),
			  cond_(&mu_),
			  left_(0),
			  writen_(0),
			  running(true),
			  frontBuffer_(),
			  bgBuffer_()
			{ 
				thread_.Start(std::bind(&AsyncLog::AsyncWrite,this)); 
			}

			~AsyncLog(){
				running = false;
				thread_.Join();
			}

			bool AppendLog(char* buf,int32_t len){
				assert(buf != NULL);
				char* bf = (char *)malloc(len * sizeof(char));
				strncpy(bf,buf,len);
				frontBuffer_.push(bf);
				cond_.NotifyOne();	
			}
			
			void AsyncWrite(){ 
				while(running){
					while(!bgBuffer_.empty()){
						if(log_file_ == NULL || writen_ >= default_log_size_){
							getNewLog();
							writen_ = 0;
						}
						char* log = bgBuffer_.front();
						writen_ += fprintf(log_file_,"%s",log);
						fprintf(log_file_,"%s","\n");
						bgBuffer_.pop();
						delete[] log;
					}
					//assert(!frontBuffer.empty());
					MutexLock lock(&mu_);
					if(!frontBuffer_.empty()){
						frontBuffer_.swap(bgBuffer_);
						continue;
					}
					if(writen_) fflush(log_file_);
					cond_.Wait();
					writen_ = 0;
				}
			} 	

		private:
			bool running;
			Mutex mu_;
			Thread thread_;
			Condition cond_;
			int32_t left_;
			int32_t writen_;
			Queue frontBuffer_;
			Queue bgBuffer_;
	};

	AsyncLog asyncLog_;

	void Logv(int level,const char* fmt,va_list ap){
		char l_buffer[8];
		memset(l_buffer,0,8);
		switch(level){
			case ::common::INFO:strcpy(l_buffer,"INFO");break;
			case ::common::WARNING:strcpy(l_buffer,"WARNING");break;
			case ::common::DEBUG:strcpy(l_buffer,"BUG");break;
			//default: assert()
		}
		int size = 0;
		char* p;
		char buffer[350];
		char *limit;
		for(int iter= 0;iter < 2;iter++){
			char* base;
			if(iter == 0){
				size = sizeof(buffer);
				p = buffer;
			}else{
				size = 30000;
				p = new char[size];
			}
			limit = p + size;
				base = p;
				strcpy(p,l_buffer);
				p += strlen(l_buffer);
				*p++ = '|';
				strcpy(p,::common::convertTimeString().c_str());		
				int32_t time_len = ::common::time_len();
				p += time_len;
			*p++ = '|';
			if(p < limit){
				va_list part;
				va_copy(part,ap);
				p += vsnprintf(p,limit-p,fmt,part);
				va_end(part);
			}
			if(p >= limit){
				if(iter == 0) {continue; }
				else p = limit -1;
			}	
			assert(p <= limit);
			//std::cout << "p:" << p << endl;
			asyncLog_.AppendLog(base,p-base);
			if(base != buffer){
				delete[] base;
			}
			break;		
		}
	}
	
	void Logger(int level,const char* fmt, ...){
		va_list ap;
		va_start(ap,fmt);
		Logv(level,fmt,ap);
		va_end(ap);
	}

}
