#include <stdio.h>
#include <string>
#include <vector>

#include "Lex_ana.h"
#include "Table.h"
#include "Insert.h"
#include "Select.h"
#include "State_code.h"

void once_init();
void initInstance();
static pthread_once_t once_control_ = PTHREAD_ONCE_INIT;
static Table* table_;
string Lex_ana::dir = "/home/llfi/simpleDB/DB/dbDir/";
Lex_ana::Lex_ana(const char* cmd)
{
    cur_cmd = cmd;
    his_cmd.push_back(cmd);
}

vector<string > Lex_ana::split(const char* cmd){
    if(cmd == NULL) return vector<string>();
    string temp;
    vector<string> tokens;
    for(int i = 0;cmd[i] != '\0';++i){
	if(cmd[i] == ' '){
	    tokens.push_back(temp);
	    temp.clear();
	}else
	    temp.push_back(cmd[i]);
    }
    //printf("%s\n",temp.c_str());
    if(!temp.empty()) tokens.push_back(temp);
    return tokens;
}

void Lex_ana::getOpCode()
{
    initInstance();    
    if(cur_cmd == NULL)
    {
	printf("error CMD!!!\n");
	return;
    }
    vector<string> tokens = split(cur_cmd); 
    switch(anaOpition(tokens[0])){
	case 0: printf("cmd EOBRROR!!!");break;
	case 1: table_->creatTable(tokens);break;
	case 2: cmdHelp();break;
	case 3: cmdHistoryOp();break;
	case 4: cmdTableInfo();break;
	case 10: new Insert(tokens,table_);break;
	case 11: new Select(table_,tokens);break;
	case 100:delete table_;exit(0);
	default:printf("error");break;
    }
}

void Lex_ana::cmdHelp(){
    printf("/************CMD FORMAT BEG************/\n");
    printf("select * from user\n");
    printf("creat table user (name,age)\n");
    printf("insert into user values (www,18)\n");
    printf("table info --- show table records\n");
    printf("history info --- show history operations\n");
    printf("help --- you know\n");
    printf("q --- you know\n");
    printf("/************CMD FORMATE END************/\n");
}

void Lex_ana::cmdHistoryOp(){
    if(his_cmd.empty())
	printf("history cmd empty!!!\n");
    for(int i = 0;i < his_cmd.size();++i)
	printf("%s\n",his_cmd[i]);
}

void Lex_ana::cmdTableInfo(){
    //if()
}

void initInstance(){
    pthread_once(&once_control_,&once_init);  
}

void once_init(){
    table_ = new Table(Lex_ana::dir);
}
