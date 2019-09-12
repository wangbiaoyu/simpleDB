/***
 *
 *2019-9-4 wby
 *
 ***/

#pragma once

#include <pthread.h>
#include <functional>
#include <string>
#include <assert.h>
#include <vector>
#include <queue>

#include "mutex.h"

using namespace std;
namespace common
{
	typedef std::function<void* (void *)> Func;
	typedef std::function<void ()> Func1;
	typedef std::function<void ()> Task;
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
	
	public:
		ThreadPool(int32_t size) 
		: size_(size)
		, mutex_()
		, cond_(&mutex_)
		, running_(true)
		{
			thread_pool_.reserve(size_);
			assert(size_ > 0);
			for(int32_t i =0;i < size_;i++){
				pthread_t tid;
				alert_info("thread init",pthread_create(&tid,NULL,ThreadWrapper,this));
				thread_pool_.push_back(tid);
			}
		}
	
		void addTask(Task task){
			MutexLock lock(&mutex_);
			if(!running_) return;
			task_.push(task);
			cond_.BroadCast();
		}

		~ThreadPool(){
			running_ = false;
			for(int i=0;i < thread_pool_.size();i++){
				alert_info("thread_pool join",pthread_join(thread_pool_[i],NULL));
			}
			thread_pool_.clear();
			task_ = queue<Task>();
		}
		
	private:
		static void* ThreadWrapper(void* arg){
			reinterpret_cast<ThreadPool*>(arg)->ThreadProc();
			return NULL;
		}

		void ThreadProc(){
			while(running_){
				while(task_.empty()){
					cond_.Wait();
				}
				if(running_ == false){
					break;
				}
				if(!task_.empty()){
					Task tmp = task_.front();
					tmp();
					task_.pop();
				}
			}
		}
		
	private:
		bool running_;
		int32_t size_;
		vector<pthread_t> thread_pool_;
		queue<Task> task_;
		Mutex mutex_;
		Condition cond_;
	};
}
