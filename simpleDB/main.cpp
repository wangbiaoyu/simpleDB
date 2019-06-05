#include <stdio.h>
#include "Lex_ana.h"
#include <iostream>
#include <memory.h>
using namespace std;

string db_dir = "/home/llfi/simpleDB/DB/dbDir/";
string undo_dir = "/home/llfi/simpleDB/DB/undoDir/";
string redo_dir = "/home/llfi/simpleDB/DB/redoDir/";

int main(int argc,char* argv[])
{
    printf("welcome to the DB world\n");
    char cmd[81];
    //todo check undo log and redo log dir
    UndoLog* undo = new UndoLog(undo_dir,db_dir);
    RedoLog* redo = new RedoLog(redo_dir,db_dir);
    redo->recovery();
    undo->recovery();
    
    printf("simpleDB:> ");
    while(cin.getline(cmd,81)){
	//if(strcmp(cmd,"q") == 0) break;
	Lex_ana* ana =	new Lex_ana(cmd);
	ana->getOpCode();
	memset(cmd,0,81);
	printf("simpleDB:> ");
    }   
    return 0;
}
