/***
 *
 * 2019-9-2
 *
 ***/
#pragma once

#include <pthread.h>
#include <string.h>
#include <stdio.h>

namespace common
{

static void alert_info(const char* info,int sig){
	if(sig != 0){	
		printf("error %s\n",info);		
	}
}
class Mutex{
public:
	Mutex() { memset(&mutex,0,sizeof(mutex)); }
	void Init() {common::alert_info("mutex init",pthread_mutex_init(&mutex,NULL));}
	void Lock() {common::alert_info("mutex lock",pthread_mutex_lock(&mutex));}
	void UnLock() {common::alert_info("mutex unlock",pthread_mutex_unlock(&mutex));}
	pthread_mutex_t* get() { return &mutex; }
private:
	Mutex(const Mutex&);
	void operator=(const Mutex&);
	pthread_mutex_t mutex;    	
};

class MutexLock{
	public:
		MutexLock(Mutex* mu) : mu_(mu)
		{
			mu_->Init();
			mu_->Lock();
		}

		void UnLock(){
			mu_->UnLock();
		}

	private:
		MutexLock(const MutexLock&);
		void operator=(const MutexLock&);
		Mutex* mu_;
};

class Condition{
	public:
		explicit Condition(Mutex* mu) : mu_(mu) { 
			common::alert_info("cond init",pthread_cond_init(&cond_,NULL)); }
		
		~Condition() { common::alert_info("cond destroy",pthread_cond_destroy(&cond_)); }		

		void Wait() { common::alert_info("cond wait",pthread_cond_wait(&cond_,mu_->get())); }

		void NotifyOne() { common::alert_info("cond notifyOne",pthread_cond_signal(&cond_)); }

		void BroadCast() { common::alert_info("cond broadcast",pthread_cond_broadcast(&cond_)); }

	private:
		Condition(const Condition&);
		void operator=(const Condition&);
		pthread_cond_t cond_;
		Mutex* mu_;
};

}
