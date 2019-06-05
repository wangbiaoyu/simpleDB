#pragma once

#include "HashIndex.h"

class RedoLog{
    
public:
    
    RedoLog(string redo,string db);
    void appendToRedoLog(HashIndex* node);
    void recovery();

private:
    
    string redoDir;
    string dbDir;

};
