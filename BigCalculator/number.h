#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;
class number
{
public:
	friend string operator +(string a, string b);
	friend string operator -(string a, string b);
	friend string operator *(string a, string b);
	friend string operator /(string a, string b);
	friend string Exponential(string a, string b);//����
	friend string Factorial(string a, string b);//����
};
void addzero(string &num);//�p�Ƹ�0