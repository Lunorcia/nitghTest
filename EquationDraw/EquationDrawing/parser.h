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
    QVector<double> x,y; //存計算的座標點數值
    static vector<pair<string,vector<string>>> variableList;//first:設定的變數名稱 second:等號左邊的建構變數
    int textLineNumber; //parser對應第幾個textLine輸入(1~10)
    bool needDraw; //預設false,有x或y設true
    static vector<string> variableFormulaList;//設定變數的算式(等號右邊)
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
    bool checkLoopDefinedVariable(vector<int> relatedTextLineNumber); //變數是否循環定義 檢查相關變數設定 不用全部檢查
    void setEquationPart(string input); //儲存等式
    void computeAllEquation();
    double compute(vector<string> formula);
    int existAxisXOrY();
};

#endif // PARSER_H

bool checkBracket(const string& line); //檢查左右括號
bool checkOperator(const string& line); //檢查運算子
bool checkDPs(const string& num);
void mergePN(string& num);
bool checkValid(vector<string>& formula);
bool isInConstructVariable(vector<string> cv, string v);
bool isDigit(string s);
bool isDigitWithPN(string s);
double stringToDouble(string s);
string doubleToString(double d);

