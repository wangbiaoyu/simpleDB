#pragma once 

#include <dirent.h>
#include "HashIndex.h"

class File{

public:

    File(HashIndex* head,string dir);
    void flush();
    void readn(string );
    bool tableExist(string table);
    HashIndex* getDiskTable(string table);
    HashIndex* getAllDiskTable();
    void writeToDisk(HashIndex* node,bool );
       
private:

    void save(HashIndex* ,bool );
    void load(HashIndex* ,string ,bool );

private:

    HashIndex* head_;
    string path1;

};

//string path1 = "home/llfi/simpleDB/DB/";
