#include "RedoLog.h"
#include "File.h"

RedoLog::RedoLog(string redo,string db) 
   :redoDir(redo),
    dbDir(db)
{
    
}   

/***
    info  : flush to disk row nom
    prams :
    return:
***/
void RedoLog::appendToRedoLog(HashIndex* node){
    //Mutex Lock
    //File* file = new File(node,redoDir);
    //HashIndex* node_to_redo = file->getDiskTable(node->table_);
    File* file1 = new File(node,HashIndex::redoDir);
    file1->writeToDisk(node,true);
}

/***
    info  : recover redo log file to a buf
    prams : file directory
    return:
***/
void RedoLog::recovery(){
    HashIndex* head = NULL,*node;
    File* file = new File(head,HashIndex::redoDir);
    head = file->getAllDiskTable();
    node = head;
    if(head == NULL) return ;
    File* file1 = new File(node,HashIndex::dbDir);
    while(node != NULL){
	file1->writeToDisk(node,true);
	node = node->next;
    }  
}
