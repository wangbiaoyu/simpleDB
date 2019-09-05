/***
 *
 *2019-9-4 wby
 *
 ***/

#pragma once

#include <pthread.h>
#include <functional>
#include <string>

namespace common
{
	typedef std::function<void* (void *)> Func;
	typedef std::function<void ()> Func1;
	typedef void *(Fun) (void *);
	class Thread{

	public:
		Thread(){  memset(&tid_,0,sizeof(tid_));}
		
		void Start(Fun func,void* arg){
			alert_info("start thread",pthread_create(&tid_,NULL,func,arg));
		}

		void Start(Func1 fun){
			func_ = fun;
			alert_info("start thread",pthread_create(&tid_,NULL,funcWrapper,this));
		} 
	
		void Join(){
			alert_info("thread join",pthread_join(tid_,NULL));
		}

		~Thread()=default;

	private:
		Thread(const Thread&);
		void operator=(const Thread&);
		static void* funcWrapper(void* arg){
			reinterpret_cast<Thread*>(arg)->func_();
			return NULL;
		}

	private:
		pthread_t tid_;
		Func1 func_;		
	};

	class ThreadPool{
		
	};
}
