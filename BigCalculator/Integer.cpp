#include "Integer.h"
vector<string>Integer::numIntList;
vector<string>Integer::nameIntList;
Integer::Integer(string a) :number(a)//繼承//沒有命名的Int(可以直接當暫用變數
{
	long long int space = a.find(" ");//如果字串有空格代表a是算式，要計算再儲存
	if (space != a.npos)
	{
		vector<string> formula;//儲存算式用
		stringstream ss(a);
		string tempss = "";
		while (getline(ss, tempss, ' '))//拆解輸入字串
			formula.push_back(tempss);
		ss.str("");
		ss.clear();
		bool Valid = checkValid(formula, a);//檢查&修正&取代formula儲存的數字or變數，有違規輸入同時輸出警示
		if (Valid == false)//輸入數字檢測不符規定
		{
			num = "0";
			name = "";
		}
		else//算式計算
		{	
			Compute(formula);
			string errorMessage = formula[0];
			if (!isdigit(errorMessage[0]))//第一格存的是錯誤訊息
			{
				cout << errorMessage << endl;
				num = "0";
				name = "";
			}
			else//計算結果儲存
			{
				Integer temp(formula[0]);//把答案做字串處理
				num = temp.num;
				name = "";
			}
		}
	}
	else//單一數字不用計算
	{
		string tempPN = "";
		if (a[0] == '-')//先把負號和數字分離
		{
			tempPN = "-";
			a = a.substr(1, a.length() - 1);
		}
		while (a[0] == '0' && a.length() > 1)//去前置0
			a = a.substr(1, a.length() - 1);
		tempPN += a;
		long long int ait = tempPN.find(".");
		if (ait != tempPN.npos)//去小數點
			tempPN = tempPN.substr(0, ait);
		num = tempPN;
		name = "";
	}
}

Integer::Integer(string a, string setN) :number(a)//有命名的"新"Int
{
	long long int space = a.find(" ");//如果字串有空格代表a是算式，要計算再儲存
	if (space != a.npos)
	{
		vector<string> formula;//儲存算式用
		stringstream ss(a);
		string tempss = "";
		while (getline(ss, tempss, ' '))//拆解輸入字串
			formula.push_back(tempss);
		ss.str("");
		ss.clear();
		bool Valid = checkValid(formula, a);//檢查&修正&取代formula儲存的數字or變數，有違規輸入同時輸出警示
		if (Valid == false)//輸入數字檢測不符規定
		{
			num = "0";
			name = "";
		}
		else//算式計算
		{
			Compute(formula);
			string errorMessage = formula[0];
			if (!isdigit(errorMessage[0]))//第一格存的是錯誤訊息
			{
				cout << errorMessage << endl;
				num = "0";
				name = "";
			}
			else//計算結果儲存
			{
				Integer temp(formula[0]);//把答案做字串處理
				num = temp.num;
				name = setN;
				numIntList.push_back(num);
				nameIntList.push_back(name);
			}
		}
	}
	else
	{
		string tempPN = "";
		if (a[0] == '-')//先把負號和數字分離
		{
			tempPN = "-";
			a = a.substr(1, a.length() - 1);
		}
		while (a[0] == '0' && a.length() > 1)//去前置0
			a = a.substr(1, a.length() - 1);
		tempPN += a;
		long long int ait = tempPN.find(".");
		if (ait != tempPN.npos)//去小數點
			tempPN = tempPN.substr(0, ait);
		num = tempPN;
		name = setN;
		numIntList.push_back(num);
		nameIntList.push_back(name);
	}
}
Integer Integer::operator =(string a)//a是數字(單純用來修改this的數值
{
	int pos = searchIntName(this->name);//同步修改static的值
	Integer temp(a);//先把數字做處理(去前置0&小數點
	this->numInt = temp.numInt;
	numIntList[pos] = this->numInt;
	return *this;
}

Integer Integer::operator =(const Integer& var)//var是變數(this的數值和名字都改
{
	int pos = searchIntName(this->name);//同步修改static的值
	nameIntList[pos] = var.name;
	numIntList[pos] = var.numInt;
	this->numInt = var.numInt;
	this->name = var.name;
	return *this;
}

ostream& operator<<(ostream& strm, const Integer& c)
{
	strm << c.numInt;
	return strm;
}

istream& operator>>(istream& strm, Integer& c)
{
	string temp;
	strm >> temp;//輸入temp存入Int
	c = temp;//Integer assign=
	return strm;
}

int Integer::searchIntName(string a)//找名字存不存在，存在回傳第幾個，不存在回傳-1
{
	for (int i = 0; i < nameIntList.size(); i++)
	{
		if (a == nameIntList[i])
			return i;
	}
	return -1;//沒找到
}

string Integer::searchIntValue(int pos)//回傳名字的值，pos=-1回傳WRONG_NAME
{
	if (pos == -1)
		return "WRONG_NAME";
	return numIntList[pos];
}

void Integer::setValue(string value, int pos)
{
	numIntList[pos] = value;
}