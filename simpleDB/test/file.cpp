#include <stdio.h>
#include <iostream>
#include "../HashIndex.h"
#include "../File.h"
using namespace std;

//class HashIndex;
HashIndex* creatDB(int num){
    HashIndex* head;
    while(num--){
	string str = std::to_string(num);
	HashIndex* hi =new HashIndex(str);
	VS vs(1,str);
	hi->records_[str] = vs;
	if(!head) head = hi;
	else{
	    hi->next = head;
	    head = hi;
	}
    }
    return head;
}
int main(int argc,char* argv[]){
    HashIndex* head = creatDB(5);
    File file = File(head);
    file.readn("1");
    file.readn("2");
    return 0;
}
