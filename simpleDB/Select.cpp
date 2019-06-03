#include "Select.h"
#include <map>
#include <stdio.h>
#include "HashIndex.h"
#include "File.h"

using namespace std;

typedef vector<string> VS;
typedef map<string,VS > MVS;
typedef map<string,MVS> MMVS;



Select::Select(Table* table,const vector<string>& tokens){
    tokens_ = tokens;
    //todo select op;
    int op = 0;
    switch(op){
	default:selectAll(table,tokens[3]);break;
    }
}

/***
    info  : select records of a table
    table : the program of Table instance 
    return: 
***/
void Select::selectAll(Table* table,string tab){
    HashIndex* mem_node = table->getTable(tab);
    printf("/******** TABLE %s ********/\n",tab.c_str());
    if(mem_node != NULL){
	mem_node->printNodeData(mem_node);
    }
    File* file = new File(mem_node);
    HashIndex* disk_node = file->getDiskTable(tab);
    if(disk_node != NULL){
	disk_node->printNodeData(disk_node);
    }
    if(mem_node == NULL && disk_node == NULL){
	printf("\n****** NONE ******\n");
    }
    printf("/******** TABLE %s ********/\n",tab.c_str());
} 
