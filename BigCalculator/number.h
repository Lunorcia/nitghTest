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
	number(string a)//�]�m�P�ɥh���e�m0
	{ 
		string tempPN = "";
		if (a[0] == '-')//����t���M�Ʀr����
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
bool checkForDivide(string a, string b);
bool isSquareRoot(number K);
void fact(unsigned long long int ansArr[], unsigned long long numA);//�����έp��