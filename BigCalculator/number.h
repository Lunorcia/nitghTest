#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;
class number
{
public:
	number(string a, string b) { numa = a; numb = b; };
	friend string operator +(string a, string b);
	friend string operator -(string a, string b);
	friend string operator *(string a, string b);
	friend string operator /(string a, string b);
	friend string Exponential(string a, string b);//指數
	friend string Factorial(string a, string b);//階乘
private:
	string numa;
	string numb;
};
void addzero(string &num);//小數補0