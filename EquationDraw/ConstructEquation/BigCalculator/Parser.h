#pragma once
#include "number.h"

bool isDigit(string s);
bool isInConstructVariable(vector<string> cv, string v);
int existAxisXOrY(vector<string> variableNameList, vector<vector<string>> constructVariable);

class Parser{
public:
	Parser();
	vector<string> equationPart;//等式陣列
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
	
	void getAxisVector();
private:
};
