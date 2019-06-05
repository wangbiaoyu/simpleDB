#include "Table.h"
#include <stdio.h>
#include <iostream>
#include "File.h"
#include "HashIndex.h"

using namespace std;

//creat table user.db (id,name,age)

Table::Table(string dir)
    :dbDir(dir)
{

}

void Table::creatTable(const vector<string>& tokens){
    //printf("tokens size %d\n",tokens.size());
    HashIndex* head = getTable(tokens[2]);
    File* file = new File(head,HashIndex::dbDir);
    HashIndex* disk = file->getDiskTable(tokens[2]);
    if(head == NULL && disk == NULL){
	head = new HashIndex(tokens[2]);
	VS vs(1,tokens[3]);
	head->records_[tokens[3]] = vs;
	if(db_ != NULL)
	    head->next = db_;
	db_ = head;
	printf("creat table %s\n",tokens[2].c_str());
    }else{
	printf("table exist!!!\n");
    }
}

HashIndex* Table::getDB(){
    return db_;
}

HashIndex* Table::getDiskDB(){
    return diskDB_;
}

/***  check memory(db_ exist this table node
      table  : check table name
      return : node or NULL;
***/
HashIndex* Table::getTable(string table){
    if(db_ == NULL) return NULL;
    HashIndex* head = db_; 
    while(head != NULL){
	if(head->table_ == table)
	    return head;
	head = head->next;
    }
    return NULL;
}

/***
    info  : write to disk
    prams :
    return: to fix(better solution
***/

Table::~Table(){
    //printf("~Table()\n");
    if(db_ != NULL){
	File* file = new File(db_,dbDir);
	while(db_ != NULL){
	    file->writeToDisk(db_,false);
	    db_ = db_->next;
	}
    }   
}
