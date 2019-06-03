#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../HashIndex.h"
#include <string.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
//#include <boost/archive/text_oarchive.hpp>

using namespace std;

std::stringstream ss;

void save(string table){
    std::ofstream fd(table.c_str(),ios::app);
    boost::archive::text_oarchive oa(fd);
    string ta = "text2";
    HashIndex hs = HashIndex(table);
    VS vs(1,table);
    hs.records_[table] = vs;
    oa << hs;
    fd.close();
    //rewind(fd);
    //fwrite(&oa,sizeof(oa),1,fd);
}


void load(string table){
    std::ifstream fd(table.c_str());
    fd.seekg(0,ios::end);
    int num = fd.tellg()-1;
    fd.seekg(0,ios::beg);
    HashIndex* head;
    while(fd.good()){
	boost::archive::text_iarchive ia(fd);
	HashIndex* hs = new HashIndex();
	    (ia >> *hs);
	if(head == NULL){
	    head = hs;
	}else{
	    hs->next = head;
	    head = hs;
	}
	if(fd.tellg() == num) break;
	printf("%d\n",hs->records_.size());
    }
    fd.close();
    //rewind(fd);
    //fread(&ia,sizeof(hs),1,fd);
    //printf("table is %s\n",hs.table_.c_str());
}
int main(int argc,char* argv[]){
    string a="/home/llfi/simpleDB/f.txt";
    string fi = "user";
    //FILE* fd = fopen(a.c_str(),"a+");
    //if(fd == NULL) exit(1);
    //save(a);
    load(a);
    //fclose(fd);
    return 0;
}
