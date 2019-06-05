#include "UndoLog.h"
#include "Mutex.h"
#include "Condition.h"

#include <stdio.h>
#include <unistd.h>

/***
    info  :
    prams : operation records
    return:
***/
UndoLog::UndoLog(string dir)
    :dir_(dir),
    mutex_(),
    cond_(mutex_)
{
    
}

/***
    info  : append before operation info from disk inorder
    prams : op(like insert into 
    return:
***/
void UndoLog::appendToUndoLog(MVS op){
    //Mutex lock
    string path  = dir_ + filename;
    ofstream file = fopen(path.c_str(),ios::out|ios::app);
    save(node);
}

void UndoLog::recovery(){
    HashIndex* head = file->getAllDiskTable(dir),node;
    if(head == NULL) return;
    node = head;
    while(node != NULL){
	file->save(node,true);
	node = node->next;
    }
}
