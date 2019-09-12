/***
 *
 *2019-9-4 wby
 *
 ***/

#include <iostream>
//#ifndef
	#include "../log.h"
//#define

#include <stdio.h>
#include "../mutex.h"
//#include "../util.h"
#include "../thread.h"

#include <memory>
using namespace std;
using namespace common;
void* test1(void* arg)
{
	char str[2000];
	memset(str,0,sizeof(str));
	for(int i= 0;i < sizeof(str);++i){
		str[i]= '0';
	}
	//cout << str << endl;
	LOG(::common::INFO,str);
	cout << "the end" << endl;
	//delete str;
}


void  Test_thread(){
	//test1(NULL);
	//test1(NULL);
	::common::Thread t[5];
	//::common::Thread t2;
	//::common::Thread t3;
	for(int i = 0;i < 5;i++){
		t[i].Start(&test1,NULL);
		//t2.Start(&test1,NULL);
		//t3.Start(&test1,NULL);
		t[i].Join();
		//t2.Join();
		//t3.Join();
	}
}

void Test_threadPool(){
	int32_t size = 2;
	shared_ptr<ThreadPool> pool =make_shared<ThreadPool>(size);
	pool->addTask(&Test_thread);
	//delete pool;
}

void test2(){
	string* str1 = new string("qwer");
	string* str2 = new string("1234");
	uint32_t a1 = static_cast<uint32_t>((*str1)[2]);
	uint32_t a2 = static_cast<uint32_t>((*str2)[2]);
	cout << "a1" << a1 << endl << "a2" << a2 << endl;
	printf("int--a1 %d,a2 %d\n",a1,a2);
	printf("s-- a1 %s,a2 %s\n",&a1,&a2);
}

int main(){
	//Test_threadPool();
	//Test_thread();
	test2();
	return 0;
}
