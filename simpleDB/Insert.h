#pragma once
#include <map>
#include <vector>
#include <string>
#include "Table.h"
using namespace std;

class Insert{

public:

    Insert(const vector<string>& tokens,Table* table_);
    void appendToCache();
    
private:
 
    Table* table_;
    vector<string> tokens;     
};
