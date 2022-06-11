#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>
using namespace std;
bool checkValid(vector<string>& formula, string originInput);
bool checkBracket(const string& line); //�ˬd���k�A��
bool checkOperator(const string& line);
bool checkDPs(const string& num);
bool negativeRoot(const string& num);
void mergePN(string& num);
void compute(vector<string> &formula);
class number
{
public:
	number(string a)
	{ 
		num = a;
	};
	string operator +(number K);
	string operator -(number K);
	string operator *(number K);
	string operator /(number K);
	string operator ^(number K);
	string computeSin();
	string computeCos();
	string computeTan();
	bool operator ==(number K); 
	string num;
private:
};
bool isAllZero(string a); //��0->T ���D0->F �]���`�N �L���p���I�^
bool isDec(string a); //�O�p��T ���O�p��or�p���I��Ҭ�0->F
bool isDecStrict(string a); //�O�p��T ���O�p��->F
bool isDot5(string a); //^�� �T�{�O�_�t�}�ڸ� X.5
