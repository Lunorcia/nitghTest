#include "parser.h"
//static
vector<pair<string,vector<string>>> Parser::variableList(11);//最多10個([1]~[10],[0]no use)


Parser::Parser()
{
    x.fill(0.0,8000);//填入8000個0
    y.fill(0.0,8000);//填入8000個0
    needDraw=false;
}
void Parser::process()//暫定總處理函式
{
    return;
}

