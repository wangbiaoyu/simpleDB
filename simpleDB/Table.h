#pragma once
#include <stdio.h>
#include <vector>
#include <string>
#include <map>
#include "HashIndex.h"

using namespace std;
//creat table

typedef vector<string> VS;
typedef map<string,VS > MVS;
typedef map<string,MVS> DB;

//static DB db_;


class Table{

public:

    void creatTable(const vector<string>& tokens);
    HashIndex* getDB();   
    HashIndex* getTable(string );
    HashIndex* getDiskDB();
    friend class Insert;
    //friend class Select;
    ~Table();
    Table(string dir);

private:
    
    HashIndex* db_; 
    HashIndex* diskDB_; 
    string dbDir;
};
