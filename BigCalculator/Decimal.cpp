#include "Decimal.h"
Decimal::Decimal(string a) :number(a)//繼承//沒有命名的Decimal(可以直接用
{
	long long int space = a.find(" ");//如果字串有空格代表a是算式
	if (space != a.npos)
	{
		////////////////////////////////
		//a=number計算(a);
		////////////////////////////////
	}
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
	name = "";
}

Decimal::Decimal(string a, string setN) :number(a)//有命名的Decimal
{
	long long int space = a.find(" ");//如果字串有空格代表a是算式
	if (space != a.npos)
	{
		////////////////////////////////
		//a=number計算(a);
		////////////////////////////////
	}
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
	name = setN;
	numDecList.push_back(num);
	nameDecList.push_back(name);
}
Decimal Decimal::operator =(string a)/////////////a是數字，不能傳其他變數名字進來(單純用來修改this的值
{
	int pos = searchDecName(this->name);//同步修改static的值
	Decimal temp(a);//先把數字做處理(去前置0
	this->numDec = temp.numDec;
	numDecList[pos] = this->numDec;
	return *this;
}

ostream& operator<<(ostream& strm, const Decimal& c)
{
	strm << c.numDec;
	return strm;
}

istream& operator>>(istream& strm, Decimal& c)
{
	string temp;//////////////輸入temp是數字
	strm >> temp;//輸入temp存入Dec
	c = temp;//assign=
	return strm;
}

int Decimal::searchDecName(string a)//找名字存不存在，存在回傳第幾個，不存在回傳-1
{
	for (int i = 0; i < nameDecList.size(); i++)
	{
		if (a == nameDecList[i])
			return i;
	}
	return -1;//沒找到
}

string Decimal::searchDecValue(int pos)//回傳名字的值，pos=-1回傳WRONG_NAME
{
	if (pos == -1)
		return "WRONG_NAME";
	return numDecList[pos];
}