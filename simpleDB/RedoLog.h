#pragma once

#include "HashIndex.h"

class RedoLog{
    
public:
    
    RedoLog();
    void appendToRedoLog(HashIndex* node);
    void recover();

private:
    
    string redoDir_;
    string dbDir_;

};
