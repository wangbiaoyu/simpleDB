#include "RedoLog.h"

RedoLog::RedoLog(string redo,string db) 
   :redoDir(redo),
    dbDir(db)
{
    
}   

void RedoLog::appendToRedoLog(HashIndex* node){
    //Mutex Lock
    file->save(node);
}

/***
    info  : recover redo log file to a buf
    prams : file directory
    return:
***/
void RedoLog::recover(string dir){
    HashIndex* head = file->getAllDiskTable(dir),node;
    node = head;
    if(head == NULL) return ;
    while(node != NULL){
	File::save(node,true);
	node = node->next;
    }  
}

