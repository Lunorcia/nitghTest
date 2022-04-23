#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;
class number
{
public:
	number(string a) { num = a; };
	string operator +(number K);
	string operator -(number K);
	string operator *(number K);
	string operator /(number K);
	string subForDivide(number a, number b);//給除法用的簡化版減法
	//friend string operator +(string a, string b);
	//friend string operator -(string a, string b);
	//friend string operator *(string a, string b);
	//friend string operator /(string a, string b);
	//friend string Exponential(string a, string b);//指數
	//friend string Factorial(string a, string b);//階乘
	string num;
private:

};
void addzero(string &n);//小數補0
bool intIsBiggerOrEqual(string a, string b);