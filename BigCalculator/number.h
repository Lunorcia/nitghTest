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
	string subForDivide(number a, number b);//�����k�Ϊ�²�ƪ���k
	//friend string operator +(string a, string b);
	//friend string operator -(string a, string b);
	//friend string operator *(string a, string b);
	//friend string operator /(string a, string b);
	//friend string Exponential(string a, string b);//����
	//friend string Factorial(string a, string b);//����
	string num;
private:

};
void addzero(string &n);//�p�Ƹ�0
bool intIsBiggerOrEqual(string a, string b);