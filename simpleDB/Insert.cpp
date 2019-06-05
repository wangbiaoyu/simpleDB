#include "Insert.h"
#include "File.h"
#include "UndoLog.h"
#include "RedoLog.h"

#include <string.h>
#include <stdio.h>

//class Table;
//insert into user.db values (1,wwwangby,18)

typedef map<string,vector<string> > MVS;
typedef map<string,map<string,vector<string> > > DB;

string path_db = string("/home/llfi/simpleDB/DB/dbDir/");
string path_undo = "/home/llfi/simpleDB/DB/undoDir/";
string path_redo = "/home/llfi/simpleDB/DB/redoDir/";

Insert::Insert(const vector<string>& tokens,Table* table_)
    :tokens(tokens),
    table_(table_)
{
    appendToCache();  
}



/***
    info  : append data to undo log and redo log before flush to disk;
    param :
    return:
***/
void Insert::appendToCache()
{
    HashIndex* table = table_->getTable(tokens[2]);
    HashIndex* disk_node;
    UndoLog* undo = new UndoLog(path_undo,HashIndex::dbDir);
    RedoLog* redo = new RedoLog(path_redo,HashIndex::dbDir);
    bool flag = false;
    VS vs(1,tokens[4]);
    if(table != NULL){
	flag = true;
	table->setMVS(tokens[4],vs,table);
	undo->appendToUndoLog(table);
	redo->appendToRedoLog(table);
    }
    if(flag == false){
	File* file = new File(table,path_undo);
	disk_node = file->getDiskTable(tokens[2]);
	if(disk_node != NULL){
	    disk_node->setMVS(tokens[4],vs,disk_node);
	    undo->appendToUndoLog(disk_node);
	    redo->appendToRedoLog(disk_node);
	}
    }
    if(table == NULL && disk_node == NULL){
	printf("table %s not exist!!!\n",tokens[2].c_str());
    }
}
