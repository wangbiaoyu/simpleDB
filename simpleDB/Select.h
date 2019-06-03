#pragma once

#include "Table.h"
#include <vector>
#include <string>
using namespace std;

//class Table;
//select * from user.db where id = 1010

class Select{

public:
    Select(Table* table,const vector<string>& tokens);
    void selectAll(Table* table,string tab);
private:
    vector<string> tokens_;   
    Table* table_;
};
