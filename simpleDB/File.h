#pragma once 

#include <dirent.h>
#include "HashIndex.h"

class File{

public:
    File(HashIndex* head);
    void flush();
    void readn(string );
    bool tableExist(string table);
    HashIndex* getDiskTable(string table);
    void writeToDisk(HashIndex* node);
       
private:
    void save(HashIndex* );
    void load(HashIndex* ,string );

private:
    HashIndex* head_;

};

//string path1 = "home/llfi/simpleDB/DB/";
