#pragma once

class UndoLog{

public:

    UndoLog(std::string dir);
    void append(string operation);
    void fsync();
    
private:

    VS records_;
    string dir;

}
