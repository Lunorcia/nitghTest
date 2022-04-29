#include "number.h"
#include "Integer.h"
#include "Decimal.h"

int main()
{
	string str1("a"), str2;
	while (cin >> str1 && str1 != "-1")
	{
		cin >> str2;
		number num1(str1), num2(str2);
		//cout  << num1 / num2 << " a" << endl;//<< num1 + num2 << endl << num1 - num2 << endl
		string ans = num1 ^ num2;
		cout << "exp = " << ans << endl;//<< num1 + num2 << endl << num1 - num2 << endl
		//ans = num1.factorial();
		//cout << "fact = " << ans << endl;
	}
	string input;
	while (getline(cin, input))
	{
		
		vector<string> formula;//儲存算式用
		stringstream ss(input);
		string tempss="";
		while (getline(ss, tempss, ' '))//拆解輸入字串
			formula.push_back(tempss);
		ss.str("");
		ss.clear();
		//先判斷有沒有關鍵字Set
		//如果Set變數有計算(A=3+5-0.8)下面過程先算完，最後叫class Int/Dec(值，名)(儲存變數要先確定名字有沒有存在，已存在就修改值，沒有就存新的)
		///////////////////class寫好的話要改成Integer temp(算式or單一值,名); cout<<temp;	值的計算在呼叫Integer時呼叫函式(下面這些步驟寫成global function)
		bool setInt = false, setDec = false;
		string variableName = "";
		if (formula[0] == "Set" && formula.size()>4)
		{
			if (formula[1] == "Integer" && formula[3] == "=")
			{
				setInt = true;
				variableName = formula[2];
				formula.erase(formula.begin(), formula.begin() + 4);//去Set//去Integer//去變數//去等號
			}
			else if (formula[1] == "Decimal" && formula[3] == "=")
			{
				setDec = true;
				variableName = formula[2];
				formula.erase(formula.begin(), formula.begin() + 4);//去Set//去Decimal//去變數//去等號
			}
			else
			{
				cout << "輸入格式錯誤" << endl;
				continue;//讀下一個輸入算式
			}
		}
		if (formula[1] == "=")		//如果第二個字串是等號，最後結果只要assign，不用輸出
		{
			string var = formula[0];
			int pos = Integer::searchIntName(formula[0]);
			if (pos != -1)//名字在Integer
			{
				setInt = true;
				variableName = formula[0];
				formula.erase(formula.begin(), formula.begin() + 2);//去變數//去等號
			}
			else if (Decimal::searchDecName(formula[0]) != -1)//名字在Decimal
			{
				setDec = true;
				variableName = formula[0];
				formula.erase(formula.begin(), formula.begin() + 2);//去變數//去等號
			}
			else
			{
				cout << "找不到變數" << endl;
				continue;//讀下一個輸入算式
			}
		}

		//assign前置結束，檢查算式
		bool Valid = checkValid(formula,input);//檢查&修正&取代formula儲存的數字or變數，有違規輸入同時輸出警示
		if (Valid == false)//輸入數字檢測不符規定
			continue;//讀下一個輸入算式

		////////////////算式計算/////////////////
		Compute(formula);
		string errorMessage = formula[0];
		if (!isdigit(errorMessage[0]))//第一格存的是錯誤訊息
		{
			cout << errorMessage << endl;
			continue; //讀下一個輸入算式
		}
		
		if (setInt == true)//結果assign就好不用輸出
		{	//找變數存不存在
			int pos = Integer::searchIntName(variableName);
			if (pos != -1)//存在改值
				Integer::setValue(formula[0], pos);

			else//不存在，存新值
				Integer temp(formula[0], variableName);//存入static list
		}
		else if (setDec == true)
		{	//找變數存不存在
			int pos = Decimal::searchDecName(variableName);
			if (pos != -1)//存在改值
				Decimal::setValue(formula[0], pos);

			else//不存在，存新值
				Decimal temp(formula[0], variableName);//存入static list
		}
		else//結果要輸出
		{
			cout << formula[0];
		}
	}

}