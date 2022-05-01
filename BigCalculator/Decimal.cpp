#include "Decimal.h"
Decimal::Decimal(string a) :number(a)//繼承//沒有命名的Decimal(可以直接用
{
	long long int space = a.find(" ");//如果字串有空格代表a是算式
	if (space != a.npos) /*a為算式，需要計算*/
	{
		////////////////////////////////
		//a=number計算(a);
		////////////////////////////////
		vector<string> formula;//儲存算式用
		stringstream ss(a);
		string tempss = "";
		while (getline(ss, tempss, ' '))//拆解輸入字串，儲存進formula
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
			if (!isdigit(errorMessage[0])) //如果Compute後結果並非數字，第一格存的是錯誤訊息
			{
				cout << errorMessage << endl;
				num = "0";
				name = "";
			}
			else //儲存計算結果
			{
				//如果結果為整數，轉成小數//
				long long int dpit = formula[0].find(".");/*尋找計算結果的小數點*/
				if (dpit == formula[0].npos) { /*如果計算結果為整數，補小數點和小數點後100位*/
					formula[0].insert(formula[0].end(), 0, '.');
					formula[0].insert(formula[0].end(), 100, '0');
				}
				else {/*如果結果為小數，回傳結果應該會到小數點後100位，就不需要這一段else*/
					formula[0].insert(formula[0].end(), 100-(formula[0].length()-1-dpit), '0');
				}
				Decimal temp(formula[0]);//把答案做字串處理
				num = temp.num;
				name = "";
			}
		}
	}
	else { //單一數字不用計算
		string tempPN = "";
		if (a[0] == '-') //先把負號和數字分離
		{
			tempPN = "-"; /*儲存負號至tempPN*/
			a = a.substr(1, a.length() - 1);/*去除負號，也可以用erase?*/
		}
		long long int ait = a.find("."); /*尋找a的小數點位置*/
		if (ait == a.npos) { /*如果計算結果為整數，補小數點和小數點後100位*/
			a.insert(a.end(), 0, '.');
			a.insert(a.end(), 100, '0');
			ait = a.find("."); /*重新尋找a的小數點位置*/
		}
		else { /*如果結果為小數，用0補滿小數點後100位*/
			a.insert(a.end(), 100 - (a.length() - 1 - ait), '0');
		}
		while (a[0] == '0' && ait > 1) /*dpit相當於整數位數，當dpit大於1時，檢查是否有多餘的0*/
			a = a.substr(1, a.length() - 1); /*去除多餘的0*/
		tempPN += a; /*a整理完後儲存進tempPN*/
		num = tempPN;
		name = "";
	}
}

Decimal::Decimal(string a, string setN) :number(a)//有命名的Decimal
{
	long long int space = a.find(" ");//如果字串有空格代表a是算式
	if (space != a.npos) /*a為算式，需要計算*/
	{
		////////////////////////////////
		//a=number計算(a);
		////////////////////////////////
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
				//如果結果為整數，轉成小數//
				long long int dpit = formula[0].find(".");/*尋找計算結果的小數點*/
				if (dpit == formula[0].npos) { /*如果計算結果為整數，補小數點和小數點後100位*/
					formula[0].insert(formula[0].end(), 0, '.');
					formula[0].insert(formula[0].end(), 100, '0');
				}
				else {/*如果結果為小數，回傳結果應該會到小數點後100位，就不需要這一段else*/
					formula[0].insert(formula[0].end(), 100 - (formula[0].length() - 1 - dpit), '0');
				}
				Decimal temp(formula[0]);//把答案做字串處理
				num = temp.num;
				name = setN;
				numDecList.push_back(num);
				nameDecList.push_back(name);
			}
		}
	}
	else //單一數字不用計算
	{
		string tempPN = "";
		if (a[0] == '-')//先把負號和數字分離
		{
			tempPN = "-"; /*儲存負號至tempPN*/
			a = a.substr(1, a.length() - 1); /*去除負號*/
		}
		long long int ait = a.find("."); /*尋找a的小數點位置*/
		if (ait == a.npos) { /*如果計算結果為整數，補小數點和小數點後100位*/
			a.insert(a.end(), 0, '.');
			a.insert(a.end(), 100, '0');
			ait = a.find("."); /*重新尋找a的小數點位置*/
		}
		else { /*如果結果為小數，用0補滿小數點後100位*/
			a.insert(a.end(), 100 - (a.length() - 1 - ait), '0');
		}
		while (a[0] == '0' && ait > 1) /*dpit相當於整數位數，當dpit大於1時，檢查是否有多餘的0*/
			a = a.substr(1, a.length() - 1); /*去除多餘的0*/
		num = tempPN;
		name = setN;
		numDecList.push_back(num);
		nameDecList.push_back(name);
	}
}
Decimal Decimal::operator =(string a)/////////////a是數字，不能傳其他變數名字進來(單純用來修改this的值
{
	if (this->name != "") {/*如果this有名字*/
		int pos = searchDecName(this->name);/*查找nameDecList內是否有this的名字，同步修改static的值*/
		Decimal temp(a); /*先把數字做處理(去前置0)，令a符合Decimal格式*/
		this->numDec = temp.numDec;/*指派temp的數字(a)給this，也就是修改this的數值*/
		numDecList[pos] = this->numDec;/*如果this的名字存在，修改pos位置的數值*/
	}
	return *this;
}

Decimal Decimal::operator =(const Decimal& var)//var是變數(this的數值和名字都改
{
	if (this->name != "") { /*如果this有名字*/
		int pos = searchDecName(this->name);/*查找nameDecList內是否有this的名字，同步修改static的值*/
		nameDecList[pos] = var.name;/*修改pos位置的名字*/
		numDecList[pos] = var.numDec;/*修改pos位置的數值*/
		this->numDec = var.numDec;/*修改this的名字*/
		this->name = var.name;/*修改this的數值*/
	}
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

void Decimal::setValue(string value, int pos)
{
	numDecList[pos] = value;
}