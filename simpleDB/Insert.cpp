#include "Insert.h"
#include <stdio.h>
#include "File.h"
//class Table;
//insert into user.db values (1,wwwangby,18)
typedef map<string,vector<string> > MVS;
typedef map<string,map<string,vector<string> > > DB;
Insert::Insert(const vector<string>& tokens,Table* table_){
    /*DB cur = table_->getDB(); 
    DB::iterator temp = cur.find(tokens[2]);
    if(temp != cur.end()){
	vector<string> t(1,tokens[4]);
	MVS mvs;
	mvs[tokens[4]] = t;
	cur[tokens[2]] = mvs; 
	printf("insert success!!!table %s size is %d\n",tokens[2].c_str(),temp->second.size());
    }else{
	printf("insert failure!!!\n");
    }*/
    HashIndex* table = table_->getTable(tokens[2]);
    HashIndex* disk_node;
    bool flag = false;
    VS vs(1,tokens[4]);
    if(table != NULL){
	flag = true;
	table->setMVS(tokens[4],vs,table);
    }
    if(flag == false){
	File* file = new File(table);
	disk_node = file->getDiskTable(tokens[2]);
	if(disk_node != NULL){
	    disk_node->setMVS(tokens[4],vs,disk_node);
	}
    }
    if(table == NULL && disk_node == NULL){
	printf("table %s not exist!!!\n",tokens[2].c_str());
    }
}
