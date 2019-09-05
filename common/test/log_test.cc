/***
 *
 *2019-9-4 wby
 *
 ***/

#include <iostream>
//#ifndef
	#include "../log.h"
//#define

#include "../mutex.h"
//#include "../util.h"
#include "../thread.h"

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


int main(){
	//test1(NULL);
	//test1(NULL);
	::common::Thread t[10];
	//::common::Thread t2;
	//::common::Thread t3;
	for(int i = 0;i < 10;i++){
		t[i].Start(&test1,NULL);
		//t2.Start(&test1,NULL);
		//t3.Start(&test1,NULL);
		t[i].Join();
		//t2.Join();
		//t3.Join();
	}
	return 0;
}
