#include "number.h"

bool checkValid(vector<string>& formula,string originInput)//檢查&修正&取代formula儲存的數字or變數，有違規輸入同時輸出警示
{
	if (!checkBracket(originInput))//檢查括號數
	{
		cout << "括號不合法" << endl;
		return false;//讀下一個輸入算式
	}
	if (!checkOperator(originInput))//檢查連續運算子
	{
		cout << "運算子不合法" << endl;
		return false;//讀下一個輸入算式
	}
	for (int i = 0; i < formula.size(); i++)
	{
		//移除前置0的處理寫到class number的construct裡了，把字串存成數字時自動做
		string temp = formula[i];
		if (temp == "(" || temp == ")" || temp == "+" || temp == "-" || temp == "*" || temp == "/" || temp == "^" || temp == "sin" || temp == "cos" || temp == "tan" || temp == "sin(" || temp == "cos(" || temp == "tan(")//一般運算子不用處理
			continue;
		mergePN(temp);//正負號整合(如果有小數點沒有前置0也會補上)
		if (!checkDPs(temp))//數字有複數個小數點
		{
			cout << "小數點輸入錯誤" << endl;
			return false;
		}
		formula[i] = temp;//檢測正確，把正負號整合完的值結果存回formula
	}
	return true;//輸入數字檢測符不符規定
}

bool checkBracket(const string& line)//檢查左右括弧是否合法
{
	int countP = 0, countN = 0;
	for (int i = 0; i < line.length(); i++){
		if (line[i] == '(')
			countP++;
		else if (line[i] == ')')
			countN++;
		if (countN > countP) { //檢查左右括弧順序是否相反
			return false;
		}
	}
	if (countP != countN) //檢查左右括弧數量是否一樣
		return false;
	return true;
}

bool checkOperator(const string& line)//連續運算符 +*-/^單獨空格的才算(依空格拆解字串，字串長度為1的才是運算符)
{
	string previous = "", now = "";//紀錄前一個，以及當前的字
	stringstream ss(line);
	while (getline(ss, now, ' ')) //空格拆解字串
	{
		if (now == "+" || now == "-" || now == "*" || now == "/" || now == "^" || now == "=")
		{
			if (previous == "+" || previous == "-" || previous == "*" || previous == "/" || previous == "^" || previous == "=" || previous == "(" )
				return false;
		}
		if (previous == "sin" || previous == "cos" || previous == "tan") { //sin、cos、tan和左括號""有""間隔，確認附帶左括號!
			if (now != "(")
				return false;
		}
		if (now == ")") { //括號內是空的
			if (previous == "(" || previous == "sin(" || previous == "cos(" || previous == "tan(") //sin、cos、tan和括號""沒有""間隔
				return false;
		}
		previous = now;
	}
	return true;
}

bool checkDPs(const string& num)//多重小數點
{
	int it = num.find('.');
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
	while (num[c] == '+' || num[c] == '-')
	{
		if (num[c] == '+')
			P++;
		if (num[c] == '-')
			N--;
		c++;
	}
	if (P + N < 0 && abs(P + N) % 2 == 1)//正負合併結果是負
	{
		num = "-" + num.substr(c, num.length() - c);//只留負號
		if (num[1] == '.')//例如-.2
			num = "-0" + num.substr(1, num.length() - 1);//補前置0>>-0.2
	}
	else//結果是正，把正負號全拿掉
	{
		num = num.substr(c, num.length() - c);
		if (num[0] == '.')//例如 .52
			num = "0" + num;//補前置0>>0.52
	}
}

void compute(vector<string>& formula)
{
	vector<int>foundOP;
	while (formula.size() > 1 || (formula.size() == 3 && formula[1] == "/"))
	{
		int found1 = -1; //找最後的左括弧位置
		int found2 = -1; //找第一個右括弧的位置
		for (int i = 0; i < formula.size(); i++)
		{
			if (formula[i] == "(")
				found1 = i;
		}
		for (int i = found1 + 1; i < formula.size(); i++)
		{
			if (formula[i] == ")")
			{
				found2 = i;
				break;
			}
		}

		if (found1 != -1 && found2 != -1 && found1 < found2) //找得到括弧的話
		{
			if (found1 + 1 == found2)
			{
				formula[0] = "err";
				cout << "()內無數字\n";
				return;
			}
		}
		else//沒找到括弧
		{
			found1 = -1;
			found2 = formula.size();
		}

		//for (int i = found1 + 1; i < found2; i++) //處理sin cos tan
		//{
		//	string b;
		//	if (formula[i] == "sin") {
		//		number a(formula[i+1]);
		//		b = a.computeSin();
		//	}
		//	else if (formula[i] == "cos") {
		//		number a(formula[i+1]);
		//		b = a.computeCos();
		//	}
		//	if (formula[i] == "tan") {
		//		number a(formula[i+1]);
		//		b = a.computeTan();
		//	}
		//	formula[i] = b;
		//	formula.erase(formula.begin() + i, formula.begin() + i + 1);
		//	found2--;
		//}

		for (int i = found2 - 1; i > found1; i--)//處理指數
		{
			if (formula[i] == "^" && i != found1 + 1)
			{
				string temp = formula[i - 1];
				if (temp[0] == '-' && isDot5(formula[i + 1]))//如果是負數開根號
				{
					formula[0] = "err";
					cout << "負數不能開根號\n";
					return;
				}
				else if (isAllZero(temp))//底數為0
				{
					formula.erase(formula.begin() + i, formula.begin() + i + 2);
					found2 -= 2;
					i--;
				}
				else
				{
					formula[i - 1] = number(formula[i - 1]) ^ number(formula[i + 1]);
					formula.erase(formula.begin() + i, formula.begin() + i + 2);
					found2 -= 2;
					i--;
				}
			}
		}

		for (int i = found1 + 1; i < found2; i++) //處理乘除
		{
			if (formula[i] == "/" || formula[i] == "*")
			{
				if (formula[i] == "/")
				{
					if (isAllZero(formula[i + 1]))
					{
						formula[0] = "除數不能為 0";
						return;
					}
					else
					{
						formula[i - 1] = number(formula[i - 1]) / number(formula[i + 1]);
						formula.erase(formula.begin() + i, formula.begin() + i + 2);
						found2 -= 2;
						i -= 2;
					}
				}
				else if (formula[i] == "*")
				{
					formula[i - 1] = number(formula[i - 1]) * number(formula[i + 1]);
					formula.erase(formula.begin() + i, (formula.begin() + i + 2));
					found2 -= 2;
					i--;
				}
			}
		}
		for (int i = found1 + 1; i < found2; i++) //處理加減
		{
			if (formula[i] == "+" || formula[i] == "-")
			{
				if (i == found1 + 1 && formula[i] == "+") // (+ 123) = 123 ; (+ -123) = -123
				{
					formula[found1 + 1] = formula[1];
				}
				else if (i == found1 + 1 && formula[i] == "-")
				{
					number zero("0");
					number b(formula[i + 1]);
					formula[found1 + 1] = zero - b;
				}
				else if (formula[i] == "+") //(1 + 2) = 3
				{
					number a(formula[found1 + 1]);
					number b(formula[i + 1]);
					formula[found1 + 1] = a + b;
				}
				else if (formula[i] == "-")
				{
					number a(formula[found1 + 1]);
					number b(formula[i + 1]);
					formula[found1 + 1] = a - b;
				}
				i++;
			}
		}

		if (found1 == -1)//沒括弧的運算
		{
			formula.erase(formula.begin() + 1, formula.end());
		}
		else
		{
			formula[found1] = formula[found1 + 1];
			formula.erase(formula.begin() + found1 + 1, formula.begin() + found2 + 1);
		}
	}
}

