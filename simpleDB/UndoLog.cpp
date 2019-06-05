#include "UndoLog.h"
#include "File.h"
//#include "/base/Mutex.h"
//#include "/base/Condition.h"

#include <stdio.h>
#include <unistd.h>

/***
    info  :
    prams : operation records
    return:
***/
UndoLog::UndoLog(string undo,string db)
    :undoDir(undo),
    dbDir(db)
    //mutex_(),
    //cond_(mutex_)
{
    
}

/***
    info  : append before operation info from disk inorder
    prams : op(like insert into 
    return:
***/
void UndoLog::appendToUndoLog(HashIndex* node){
    //Mutex lock
    File* file = new File(node,HashIndex::undoDir);
    HashIndex* node_to_redo = file->getDiskTable(node->table_);
    File* file1 = new File(node_to_redo,HashIndex::undoDir);
    file1->writeToDisk(node,true);
}

void UndoLog::recovery(){
    HashIndex* node = NULL;
    File* file = new File(node,HashIndex::undoDir);
    HashIndex* head = file->getAllDiskTable();
    if(head == NULL) return;
    File* file1 = new File(head,HashIndex::dbDir);
    node = head;
    while(node != NULL){
	file1->writeToDisk(node,true);
	node = node->next;
    }
}
