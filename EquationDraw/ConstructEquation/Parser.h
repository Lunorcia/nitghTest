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
private:
};

bool isDigit(string s);
double stringToDouble(string s);
string doubleToString(double d);
bool checkBracket(const string& line); //�ˬd���k�A��
bool checkOperator(const string& line); //�ˬd�B��l
bool checkDPs(const string& num);
bool negativeRoot(const string& num);
void mergePN(string& num);
bool checkValid(vector<string>& formula);
bool isInConstructVariable(vector<string> cv, string v);
int existAxisXOrY(vector<string> variableNameList, vector<vector<string>> constructVariable);
