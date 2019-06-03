#include "File.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include "HashIndex.h"

string path1 = "/home/llfi/simpleDB/DB/";

File::File(HashIndex* node){
    head_ = node;    
}


/***
    info  : save a table node to file
    prams : a node express a table
    return:
***/
void File::save(HashIndex* node){
    string table = path1 + node->table_;
    std::ofstream fd(table.c_str(),ios::app);
    boost::archive::text_oarchive oa(fd);
    oa << *node;
    fd.close();
}

/***
    info  : load a file table to node
    prams : table , load(to save
    return:
***/
void File::load(HashIndex* load,string table){
    string table1 = path1 + table;
    printf("%s\n",table1.c_str());
    std::ifstream fd(table1.c_str());
    boost::archive::text_iarchive ia(fd);
    ia >> *load; 
    fd.close();
}


/***
    info  : path exist the file 
    prams : 
    return: true(exist false(no
***/
bool File::tableExist(string table){
    struct dirent *ptr;
    DIR* dir;
    dir = opendir(path1.c_str());
    while((ptr = readdir(dir)) != NULL){
	//skip '.' | '..' 
	if(ptr->d_name[0] == '.') continue;
	if(ptr->d_name == table)
	    return true;
    }
    return false;
}
	    

/***
    info  : get a node from disk DB
    prams : table name
    return: node or NULL;
***/
HashIndex* File::getDiskTable(string table){ 
    if(table.empty()) return NULL;
    if(tableExist(table) == false) return NULL;
    HashIndex* node = new HashIndex();
    load(node,table);
    return node;
}


/***
    info  : write/append a node to disk
    prams : a node(table
    return:
***/
void File::writeToDisk(HashIndex* node){
    save(node);
}

