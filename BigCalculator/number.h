#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>
using namespace std;
class number
{
public:
	number(string a)//設置同時去除前置0
	{ 
		string tempPN = "";
		if (a[0] == '-')//先把負號和數字分離
		{
			tempPN = "-";
			a = a.substr(1, a.length() - 1);
		}
		while (a[0] == '0' && a.length() > 1)
			a = a.substr(1, a.length() - 1);
		tempPN += a;
		num = tempPN;
	};
	string operator +(number K);
	string operator -(number K);
	string operator *(number K);
	string operator /(number K);
	string operator ^(number K);
	string factorial();
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
bool checkForDivide(string a, string b);
bool isSquareRoot(number K);
void fact(unsigned long long int ansArr[], unsigned long long numA);//階乘用計算