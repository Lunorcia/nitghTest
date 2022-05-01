#pragma once
#include "number.h"
class Decimal :public number
{
public:
	Decimal(string a);//繼承
	Decimal(string a, string setN);
	static int searchDecName(string a);//找名字存不存在，存在回傳第幾個，不存在回傳-1
	static string searchDecValue(int pos);//回傳名字的值，pos=-1回傳WRONG_NAME
	static void setValue(string value, int pos);

	Decimal operator =(string a);//a是數字(單純用來修改this的數值
	Decimal operator =(const Decimal& var);//var是變數(this的數值和名字都改

	friend ostream& operator<<(ostream& strm, const Decimal& c);
	friend istream& operator>>(istream& strm, Decimal& c);
private:
	string numDec;
	string name;
	static vector<string>numDecList;
	static vector<string>nameDecList;
};
