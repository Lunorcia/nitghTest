#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>
using namespace std;

class Parser{
public:
	Parser();
	~Parser();
	vector<double> x;
	vector<double> y;
	vector<string> variableNameList;//變數名稱陣列
	vector<string> variableFormulaList;//設定變數的等式
	vector<vector<string>> constructVariable;
	int searchVariableName(string a);//找變數存不存在，存在回傳第幾個，不存在回傳-1
	bool checkDefinedVariable(vector<string> cv); //變數是否未定義
	bool checkLoopDefinedVariable(); //變數是否循環定義
	void setEquationPart(string input);//儲存等式
	void computeAllEquation();
	double compute(vector<string> formula);
	void getAxisVector();
private:
};

bool isDigit(string s);
double stringToDouble(string s);
string doubleToString(double d);
bool checkBracket(const string& line); //檢查左右括號
bool checkOperator(const string& line); //檢查運算子
bool checkDPs(const string& num);
bool negativeRoot(const string& num);
void mergePN(string& num);
bool checkValid(vector<string>& formula);
bool isInConstructVariable(vector<string> cv, string v);
int existAxisXOrY(vector<string> variableNameList, vector<vector<string>> constructVariable);
