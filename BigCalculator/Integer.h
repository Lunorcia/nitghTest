#pragma once
#include "number.h"
class Integer:public number
{
public:
	Integer(string a);//繼承
	Integer(string a,string setN);
	static int searchIntName(string a);//找名字存不存在，存在回傳第幾個，不存在回傳-1
	static string searchIntValue(int pos);//回傳名字的值，pos=-1回傳WRONG_NAME
	static void setValue(string value, int pos);

	Integer operator =(string a);//a是數字(單純用來修改this的數值
	Integer operator =(const Integer& var);//var是變數(this的數值和名字都改

	friend ostream& operator<<(ostream& strm, const Integer& c);
	friend istream& operator>>(istream& strm, Integer& c);
private:
	string numInt;
	string name;
	static vector<string>numIntList;
	static vector<string>nameIntList;
};
vector<string>Integer::numIntList;
vector<string>Integer::nameIntList;