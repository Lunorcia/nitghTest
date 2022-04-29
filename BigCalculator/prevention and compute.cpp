#include "number.h"
#include "Integer.h"
#include "Decimal.h"
bool checkValid(vector<string>& formula,string originInput)//檢查&修正&取代formula儲存的數字or變數，有違規輸入同時輸出警示
{
	if (!checkBracketAmount(originInput))//檢查括號數
	{
		cout << "括號不完全" << endl;
		return false;//讀下一個輸入算式
	}
	if (!checkOperator(originInput))//檢查連續運算子
	{
		cout << "不可連續輸入(正.負號.階乘.括號)以外的運算子+-*/^=" << endl;
		return false;//讀下一個輸入算式
	}
	bool Valid = true;
	for (int i = 0; i < formula.size(); i++)
	{
		//Integer&Decimal變數照樣傳入
		//移除前置0的處理寫到class number的construct裡了，把字串存成數字時自動做
		string temp = formula[i];
		if (temp == "(" || temp == ")" || temp == "+" || temp == "-" || temp == "*" || temp == "/" || temp == "!" || temp == "^" || temp.substr(0, 5) == "Power")//一般運算子不用處理
			continue;
		mergePN(temp);//正負號整合(如果有小數點沒有前置0也會補上)
		if (temp == "WRONG_NAME")
		{
			cout << "找不到變數" << endl;
			Valid = false;
			break;
		}
		if (!checkDPs(temp))//數字有複數個小數點
		{
			cout << "小數點輸入錯誤" << endl;
			break;
		}
		formula[i] = temp;//檢測正確，把正負號整合完& Int or Dec的值結果存回
	}
	return Valid;//輸入數字檢測符不符規定
}
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
		if (now == "+" || now == "-" || now == "*" || now == "/" || now == "^" || now == "=")
		{
			if (previous == "+" || previous == "-" || previous == "*" || previous == "/" || previous == "^" || now == "=")
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
			int pos=Integer::searchIntName(var);
			if (pos >= 0)//名字在Integer
				var = Integer::searchIntValue(pos);
			else//名字在Decimal
			{
				pos = Decimal::searchDecName(var);
				var = Decimal::searchDecValue(pos);//有找到就回傳值，沒找到就直接回傳WRONG_NAME
			}
			
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
			string var = num;
			int pos = Integer::searchIntName(var);
			if (pos >= 0)//名字在Integer
				var = Integer::searchIntValue(pos);
			else//名字在Decimal
			{
				pos = Decimal::searchDecName(var);
				var = Decimal::searchDecValue(pos);//有找到就回傳值，沒找到就直接回傳WRONG_NAME
			}

			num = var;//有找到結果是數值，沒有就是WRONG_NAME
		}
	}


}
/*bool convertPower(vector<string>& formula)//Power(2,3)拆成3個字串>>"2">>"^">>"3"，第一個取代temp在vector的位置，後面兩個用插入接著(拆出來的兩個數字要先跑一次前面的檢測
{
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
}*/
void Compute(vector<string>& formula)
{
	/////////////計算方法/////////////////
	// 如果計算中途有無效運算(底下條件其一)
	// 把錯誤訊息存在formula[0]，結束計算，不用回傳值(錯誤訊息回傳:階乘不能是負數、除數不能是0、負數不能開根號、...)
	// 最後留下formula[0](答案)
	// 
	// (v)拆解數字前防呆:括號數，連續運算符+-*/^
	// (v)拆解後單獨數字一律先進正負號整合,ex: +-+5 >> -5，然後進小數點數量確認(不管是不是小數)
	// 計算優先度:階乘>指數(優先度由右到左)> * > / > + > - 
	// 兩數計算前檢查(底線標示輸入算式的空格):
	// 階乘不能是負數,ex:-5_!
	// 除數不能是0,ex: 5_/_0	
	// 負數不能開根號,ex: -2.5_^_0.5
	// 指數計算前>>根號0=0
}