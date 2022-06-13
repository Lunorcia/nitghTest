#pragma once
#include "number.h"

bool isDigit(string s);
bool isInConstructVariable(vector<string> cv, string v);
int existAxisXOrY(vector<string> variableNameList, vector<vector<string>> constructVariable);

class Parser{
public:
	Parser();
	vector<string> equationPart;//�����}�C
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
	
	void getAxisVector();
private:
};
