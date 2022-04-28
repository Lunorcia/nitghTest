#include "number.h"
bool checkBracketAmount(const string& line)//左右括弧數量不一樣
{
	int countP = 0, countN = 0;
	for (int i = 0; i < line.length(); i++)
	{
		if (line[i] == '(')
			countP++;
		else if (line[i] == ')')
			countN++;
	}
	if (countP != countN)
		return false;
	return true;

}
bool checkOperator(string line)//連續運算符 +*-/^(階乘可以連續(3_!_!=720))單獨空格的才算(依空格拆解字串，字串長度為1的才是運算符)
{
	vector<string> numAndOpe;
	string previous = "", now = "";
	stringstream ss(line);
	while (getline(ss, now, ' '))//空格拆解字串
	{
		if (now == "+" || now == "-" || now == "*" || now == "/" || now == "^")
		{
			if (previous == "+" || previous == "-" || previous == "*" || previous == "/" || previous == "^")
				return false;
		}
		previous = now;
	}
	return true;

}
bool checkDPs(const string& num)//多重小數點
{
	long long int it = num.find('.');
	if (it != num.npos)//有小數點
	{
		it = num.find('.',it+1);//找有沒有第二個小數點
		if (it != num.npos)
			return false;
	}
	//如果找不到or只找到一個小數點 回傳true
	return true;
}
bool negativeRoot(const string& num)//負數不能開根號
{
	if (num[0] == '-')
		return false;
	return true;
}
void mergePN(string& num)
{
	int P = 0, N = 0, c = 0;
	while (num[c] == '+' || num[c] == '+')
	{
		if (num[c] == '+')
			P++;
		if (num[c] == '-')
			N--;
		c++;
	}

	//遇到不是數字(Integer&Decimal的名稱)要先搜尋(註解行class功能還沒寫)，沒搜尋到回傳"WRONG_NAME"

	if (P + N < 0)//正負合併結果是負
	{
		num = "-" + num.substr(c, num.length() - c);
		if (num[1] == '.')//例如-.2
			num = "-0" + num.substr(1, num.length() - 1);//補前置0>>-0.2
		if (!isdigit(num[1]))//負號後第一個字元不是數字>>輸入是變數
		{
			string var = num.substr(1, num.length() - 1);

			//var=呼叫class.func(var)，回傳變數值;沒搜尋到回傳"WRONG_NAME"

			if (var == "WRONG_NAME")//沒找到變數
			{
				num = var;
				return;
			}
			else
			{
				num = "-" + var;
			}
		}
	}
	else//結果是正，把正負號全拿掉
	{
		num = num.substr(c, num.length() - c);
		if (num[0] == '.')//例如 .52
			num = "0" + num;//補前置0>>0.52
		if (!isdigit(num[0]))//第一個字元不是數字>>輸入是變數
		{
			//num=呼叫class.func(num)，回傳變數值;沒搜尋到回傳"WRONG_NAME"

			/*if (num == "WRONG_NAME")//沒找到變數
				return;*/

		}
	}


}
bool convertPower(vector<string>& formula)//Power(2,3)拆成3個字串>>"2">>"^">>"3"，第一個取代temp在vector的位置，後面兩個用插入接著(拆出來的兩個數字要先跑一次前面的檢測
{/////////////////連續power沒做
	for (int i = 0; i < formula.size(); i++)
	{
		string temp = formula[i];
		if (temp.substr(0, 5) == "Power")
		{
			long long int commaF = temp.find(',');
			long long int commaB = temp.rfind(',');
			if (commaF != commaB)//有複數個逗號
				return false;
			long long int braL = temp.find('(');
			long long int braR = temp.rfind(')');
			if (braL != temp[5] || braR != temp[temp.length() - 1])//左右括號位置不對
				return false;
			string numA(temp.begin() + 6, temp.end());//複製左括號後的字串(第6個字元開始)
			commaF = numA.find(',');
			numA = numA.substr(0, commaF);//底數
			string numB(temp.begin() + 7 + numA.length(), temp.end());
			numB = numB.substr(0, numB.length() - 1);//指數(去右括號)
			formula[i] = numA;
			if (i == formula.size() - 1)//最尾端插入用end()(i+1會超出vector size)
			{
				formula.insert(formula.end() , "^");
				i++;
				formula.insert(formula.end(), numB);
				i++;
			}
			else
			{
				formula.insert(formula.begin() + i + 1, "^");//插入在i+1前面(=numA後)
				i++;
				formula.insert(formula.begin() + i + 1, numB);
				i++;
			}
		}
	}
	return true;
}
void checkValidCompute(vector<string> formula)
{
	
//Power(5, 2)
//拆解數字前防呆:括號數，連續運算符+-*/^
//拆解後單獨數字一律先進正負號整合,ex: +-+5 >> -5，然後進小數點數量確認(不管是不是小數)
//計算優先度:階乘>指數
//計算前(底線標示輸入算式的空格):	階乘不能是負數,ex:-5_!
//									除數不能是0,ex: 5_/_0	
//									負數不能開根號,ex: -2.5_^_0.5
//根號0=0
}