#ifndef PARSER_H
#define PARSER_H
#pragma execution_character_set("utf-8")
#include <iostream>
#include <cmath>
#include <QObject>
#include <vector>
#include <string>
#include <sstream>

using namespace std;
class Parser
{
public:
    Parser();
    Parser(int num); //存取textLineNumber
//    vector<string> equationPart; //拆解後的字串(等號右邊)
    QVector<double> x,y; //存計算的座標點數值
    static vector<pair<string,vector<string>>> variableList;
    int textLineNumber; //parser對應第幾個textLine輸入(1~10)
    bool needDraw; //預設false,有y設true

    //static vector<string> variableNameList;//變數名稱陣列
    static vector<string> variableFormulaList;//設定變數的等式
    //static vector<vector<string>> constructVariableList;//建構變數的所有變數
//    static 儲存變數(變數,拆解後的字串)
//    一個textline對應一個變數,最多10個([1]~[10],[0]no use)
//    沒設定變數的話要把那一格變回空的""(不要erase,對應順序會亂
//    拆字串
//    檢查輸入合法
//    是不是設定變數
//    一個變數只能定義一次(避免循環定義)
//    有錯誤
//    變數有套用x以外的變數就先替換(ex: a=5+x; b=a+3>>b=5+x+3)
//    equation有y出現的時候再計算
    void process(); //暫定總處理函式
    int searchVariableName(string a); //找變數存不存在，存在回傳第幾個，不存在回傳-1
    bool checkDefinedVariable(); //變數是否未定義
    bool checkLoopDefinedVariable(); //變數是否循環定義
    void setEquationPart(string input); //儲存等式
    void computeAllEquation();
    double compute(vector<string> formula);
    int existAxisXOrY();
//    void getAxisVector();

};

#endif // PARSER_H

bool checkBracket(const string& line); //檢查左右括號
bool checkOperator(const string& line); //檢查運算子
bool checkDPs(const string& num);
bool negativeRoot(const string& num);
void mergePN(string& num);
bool checkValid(vector<string>& formula);
bool isInConstructVariable(vector<string> cv, string v);
bool isDigit(string s);
bool isDigitWithPN(string s);
double stringToDouble(string s);
string doubleToString(double d);
