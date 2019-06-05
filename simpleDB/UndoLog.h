#pragma once

#include "HashIndex.h"

class UndoLog{

public:

    UndoLog(std::string undo,string db);
    void appendToUndoLog(HashIndex* node);
    void recovery();
    void fsync();
    
private:

    VS records_;
    string undoDir;
    string dbDir;

};
