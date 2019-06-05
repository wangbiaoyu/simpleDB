#pragma once

#include "UndoLog.h"
#include "RedoLog.h"

#include <vector>
#include <string>
using namespace std;
//lexcial analysis
class Lex_ana{

public:
    Lex_ana(const char* cmd);
    char* getOp();
    void cmdHelp();
    void cmdHistoryOp();
    void cmdTableInfo();
    void getOpCode();

private:
    vector<string > split(const char* cmd);
    vector<const char *> his_cmd;
    const char* cur_cmd;
    int op;
public:
    static string dir;// = "/home/llfi/simpleDB/DB/dbDir/";
};
