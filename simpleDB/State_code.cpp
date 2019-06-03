#include "State_code.h"

int anaOpition(string opt){
    if(opt == "help") return helpCmd();
    if(opt == "creat") return createTableCmd();
    if(opt == "history info") return historyOpCmd();
    if(opt == "insert") return insertCmd();
    if(opt == "table info") return tableInfoCmd();
    if(opt == "select") return selectCmd();
    if(opt == "q") return 100;
    return errorCmd();   
}

int errorCmd()
{
    return 0;
}

int createTableCmd()
{
    return 1;
}
int insertCmd()
{
    return 10;
}

int selectCmd()
{
    return 11;
}

int helpCmd()
{
    return 2;
}

int historyOpCmd()
{
    return 3;
}

int tableInfoCmd()
{
    return 4;
}
