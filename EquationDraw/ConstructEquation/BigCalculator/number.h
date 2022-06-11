#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>
using namespace std;
bool checkValid(vector<string>& formula, string originInput);
bool checkBracket(const string& line); //浪琩オ珹腹
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
bool isAllZero(string a); //常0->T Τ獶0->F “猔種 礚跌计翴
bool isDec(string a); //琌计T ぃ琌计or计翴0->F
bool isDecStrict(string a); //琌计T ぃ琌计->F
bool isDot5(string a); //^ノ 絋粄琌秨腹 X.5
