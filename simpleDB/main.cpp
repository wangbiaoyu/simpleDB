#include <stdio.h>
#include "Lex_ana.h"
#include <iostream>
#include <memory.h>
using namespace std;

int main(int argc,char* argv[])
{
    printf("welcome to the DB world\n");
    char cmd[81];
    printf("simpleDB: ");
    while(cin.getline(cmd,81)){
	//if(strcmp(cmd,"q") == 0) break;
	Lex_ana* ana =	new Lex_ana(cmd);
	ana->getOpCode();
	memset(cmd,0,81);
	printf("simpleDB: ");
    }   
    return 0;
}
