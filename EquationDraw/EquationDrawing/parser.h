#ifndef PARSER_H
#define PARSER_H
#pragma execution_character_set("utf-8")
#include <iostream>
#include <cmath>
#include <QObject>
#include <vector>
#include <string>
#include "number.h"

using namespace std;
class Parser
{
public:
    Parser();
    Parser(int num);
    vector<string> equationPart;//拆解後的字串
    QVector<double> x,y;//存計算的座標點數值
    static vector<pair<string,vector<string>>> variableList;
        //static 儲存變數(變數,拆解後的字串)
        //一個textline對應一個變數,最多10個([1]~[10],[0]no use)
        //沒設定變數的話要把那一格變回空的""(不要erase,對應順序會亂
    void process();//暫定總處理函式

    //拆字串
    //檢查輸入合法
    //是不是設定變數
    //一個變數只能定義一次(避免循環定義)
    //有錯誤
    //變數有套用x以外的變數就先替換(ex: a=5+x; b=a+3>>b=5+x+3)
    //equation有y出現的時候再計算
    int textLineNumber;//parser對應第幾個textLine輸入(1~10)
    bool needDraw;//預設false,有y設true

    vector<string> variableNameList;//�ܼƦW�ٰ}�C
    vector<string> variableFormulaList;//�]�w�ܼƪ�����
    vector<vector<string>> constructVariable;
    int searchVariableName(string a);//���ܼƦs���s�b�A�s�b�^�ǲĴX�ӡA���s�b�^��-1
    bool checkDefinedVariable(vector<string> cv); //�ܼƬO�_���w�q
    bool checkLoopDefinedVariable(); //�ܼƬO�_�`���w�q
    void setEquationPart(string input);//�x�s����
    void computeAllEquation();
    double compute(vector<string> formula);
    void getAxisVector();

};

#endif // PARSER_H
bool isDigit(string s);
double stringToDouble(string s);
string doubleToString(double d);
bool checkBracket(const string& line); //�ˬd���k�A��
bool checkOperator(const string& line); //�ˬd�B���l
bool checkDPs(const string& num);
bool negativeRoot(const string& num);
void mergePN(string& num);
bool checkValid(vector<string>& formula);
bool isInConstructVariable(vector<string> cv, string v);
int existAxisXOrY(vector<string> variableNameList, vector<vector<string>> constructVariable);
