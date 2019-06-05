#include "HashIndex.h"
#include <assert.h>
#include <stdio.h>

string HashIndex::dbDir = "/home/llfi/simpleDB/DB/dbDir/";
string HashIndex::undoDir = "/home/llfi/simpleDB/DB/undoDir/";
string HashIndex::redoDir = "/home/llfi/simpleDB/DB/redoDir/";

HashIndex::HashIndex()
    :table_(""),
    next(NULL)
{ }

HashIndex::HashIndex(string table)
    :table_(table),
    next(NULL)
{ }

//insert a record
void HashIndex::setMVS(string key,vector<string> value,HashIndex* node){
    node->records_.insert({key,value});
}

//get cur table node
static MVS getRecords(HashIndex* node){
    assert(node != NULL);
    return node->records_;
}

void HashIndex::printNodeData(HashIndex* node){
    assert(node!=NULL);
    MVS mvs = node->records_;
    MVS::iterator b = mvs.begin();   
    for(;b != mvs.end();++b){
	VS vs = b->second;
	printf("%s\n",vs[0].c_str());
    }
}
