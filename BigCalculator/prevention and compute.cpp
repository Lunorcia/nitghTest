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
	while (num[c] == '+' || num[c] == '-')
	{
		if (num[c] == '+')
			P++;
		if (num[c] == '-')
			N--;
		c++;
	}

	//遇到不是數字(Integer&Decimal的名稱)要先搜尋(註解行class功能還沒寫)，沒搜尋到回傳"WRONG_NAME"

	if (P + N < 0 && abs(P + N) % 2 == 1)//正負合併結果是負
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

long long int findFra(unsigned long long int n, vector<long long int>foundOP) {
	int lastOne = 0;
	for (int i = 0; i < foundOP.size(); i++)
	{
		if (n == foundOP[i])
			lastOne = i;
	}
	return lastOne;
}
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

	vector<number>denominator, numerator;
	vector<long long int>foundOP;
	bool Fraction = false;

	while (formula.size() > 1 || (formula.size() == 3 && formula[1] == "/"))
	{
		long long int found1 = -1; //找最後的左括弧位置
		long long int found2 = -1; //找第一個右括弧的位置
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

		for (int i = found1 + 1; i < found2; i++)//處理階乘
		{
			if (formula[i] == "!" && i != found1 + 1)
			{
				if (formula[i - 1][0] == '-')
				{
					formula[0] = "err";
					cout << "負數不能算階乘\n";
					return;
				}
				else if (!isDec(formula[i - 1]))
				{
					string a = number(formula[i-1]).factorial();
					formula[i - 1] = a;
					formula.erase(formula.begin() + i, formula.begin() + i+1);
					found2 -= 1;
					i--;
					
				}
				else
				{
					formula[0] = "err";
					cout << "小數不能算階乘\n";
					return;
				}
			}
		}
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
						if (!isDec(formula[i + 1]) && !isDec(formula[i - 1]))
						{
							formula[i - 1] = number(formula[i - 1]) / number(formula[i + 1]);
							formula.erase(formula.begin() + i, formula.begin() + i+2);
							found2 -= 2;
						}
						else if (!Fraction)
						{
							denominator.push_back(number(formula[i + 1])); //設定分母
							numerator.push_back(number(formula[i - 1]));  //設定分子
							foundOP.push_back(i - 1);
							formula.erase(formula.begin() + i, formula.begin() + i + 2);
							found2 -= 2;
							formula[i - 1] = "Fraction";
							Fraction = true;
						}
						else // a/b
						{
							if (formula[i + 1] == "Fraction" && formula[i - 1] != "Fraction")// a不是分數 b是分數 
							{
								long long int foundDen = findFra(i + 1, foundOP);
								number temp(denominator[foundDen].num);
								number a(formula[i - 1]);
								denominator[foundDen].num = numerator[foundDen].num;
								numerator[foundDen].num = temp * a;
								foundOP[foundDen] = i - 1;
								formula.erase(formula.begin() + i, formula.begin() + i + 2);
								found2 -= 2;
								formula[i - 1] = "Fraction";
							}
							else if (formula[i + 1] != "Fraction" && formula[i - 1] == "Fraction") //a是分數 b不是分數
							{
								long long int foundNum = findFra(i - 1, foundOP);
								number a(formula[i + 1]);
								denominator[foundNum].num = denominator[foundNum] * a;
								foundOP[foundNum] = i - 1;
								formula.erase(formula.begin() + i, formula.begin() + i + 2);
								found2 -= 2;
								formula[i - 1] = "Fraction";
							}
							else if (formula[i + 1] == "Fraction" && formula[i - 1] == "Fraction") //a b都是分數
							{
								long long int foundNum = findFra(i - 1, foundOP); //a
								long long int foundDen = findFra(i + 1, foundOP); //b

								numerator[foundNum].num = numerator[foundNum] * denominator[foundDen];//a的分子=a的分子*b的分母
								denominator[foundNum].num = denominator[foundNum] * numerator[foundDen];//a的分母=a的分母*b的分子

								foundOP[foundNum] = i - 1;
								foundOP.erase(foundOP.begin() + foundDen); //刪除b的位置紀錄
								numerator.erase(numerator.begin() + foundDen); //刪除b的分子
								denominator.erase(denominator.begin() + foundDen);//刪除b的分母

								formula.erase(formula.begin() + i, formula.begin() + i + 2);
								found2 -= 2;
								formula[i - 1] = "Fraction";
							}
							else //a b 都不是分數
							{
								denominator.push_back(number(formula[i + 1])); //設定分母
								numerator.push_back(number(formula[i - 1]));  //設定分子
								foundOP.push_back(i - 1);
								formula.erase(formula.begin() + i, (formula.begin() + i + 2));
								found2 -= 2;
								formula[i - 1] = "Fraction";
							}
						}
						i-=2;
					}
				}
				else if (formula[i] == "*")
				{
					if (formula[i + 1] == "Fraction" && formula[i - 1] != "Fraction")// a不是分數 b是分數 
					{
						long long int foundDen = findFra(i + 1, foundOP);
						number a(formula[i - 1]);
						numerator[foundDen].num = numerator[foundDen] * a;
						foundOP[foundDen] = i - 1;
						formula.erase(formula.begin() + i, formula.begin() + i + 2);
						found2 -= 2;
						formula[i - 1] = "Fraction";
					}
					else if (formula[i + 1] != "Fraction" && formula[i - 1] == "Fraction") //a是分數 b不是分數
					{
						long long int foundNum = findFra(i - 1, foundOP);
						number a(formula[i + 1]);
						numerator[foundNum].num = numerator[foundNum] * a;
						foundOP[foundNum] = i - 1;
						formula.erase(formula.begin() + i, formula.begin() + i + 2);
						found2 -= 2;
						formula[i - 1] = "Fraction";
					}
					else if (formula[i + 1] == "Fraction" && formula[i - 1] == "Fraction") //a b都是分數
					{
						long long int foundNum = findFra(i - 1, foundOP); //a
						long long int foundDen = findFra(i + 1, foundOP); //b

						numerator[foundNum].num = numerator[foundNum] * numerator[foundDen];//a的分子=a的分子*b的分子
						denominator[foundNum].num = denominator[foundNum] * denominator[foundDen];//a的分母=a的分母*b的分母

						foundOP[foundNum] = i - 1;
						foundOP.erase(foundOP.begin() + foundDen); //刪除b的位置紀錄
						numerator.erase(numerator.begin() + foundDen); //刪除b的分子
						denominator.erase(denominator.begin() + foundDen);//刪除b的分母

						formula.erase(formula.begin() + i, formula.begin() + i + 2);
						found2 -= 2;
						formula[i - 1] = "Fraction";
					}
					else //a b 都不是分數
					{
						formula[i - 1] = number(formula[i - 1]) * number(formula[i + 1]);
						formula.erase(formula.begin() + i, (formula.begin() + i + 2));
						found2 -= 2;
					}
					i--;
				}
			}
		}
		for (int i = found1 + 1; i < found2; i++) //處理加減
		{
			if (formula[i] == "+" || formula[i] == "-")
			{
				if (!Fraction)//此段()內無分數
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
				else //此段()內有分數
				{
					if (i == found1 + 1 && formula[i] == "+" && formula[i + 1] == "Fraction")//(+ 1/3)= 1/3
					{
						long long int foundFra = findFra(i + 1, foundOP);
						foundOP[foundFra] = found1 + 1;
						formula[found1 + 1] = "Fraction";
					}
					else if (i == found1 + 1 && formula[i] == "-" && formula[i + 1] == "Fraction")//(- -1/3)= +1/3
					{
						long long int foundFra = findFra(i + 1, foundOP);
						number zero("0");
						numerator[foundFra].num = zero - numerator[foundFra];
						denominator[foundFra].num = zero - denominator[foundFra];
						foundOP[foundFra] = found1 + 1;
						formula[found1 + 1] = "Fraction";
					}
					else if (formula[i] == "+" && formula[i + 1] == "Fraction" && formula[found1 + 1] != "Fraction") // (1 + 1/3) = (1*3+1)/3
					{
						long long int foundFra = findFra(i + 1, foundOP);
						number a(formula[found1 + 1]);
						numerator[foundFra].num = numerator[foundFra] + a * denominator[foundFra];
						foundOP[foundFra] = found1 + 1;
						formula[found1 + 1] = "Fraction";
					}
					else if (formula[i] == "+" && formula[i + 1] != "Fraction" && formula[found1 + 1] == "Fraction") // (1/3 + 1) = (1+1*3)/3
					{
						long long int foundFra = findFra(found1 + 1, foundOP);
						number a(formula[i + 1]);
						numerator[foundFra].num = numerator[foundFra] + number(a * denominator[foundFra]);
					}
					else if (formula[i] == "+" && formula[i + 1] == "Fraction" && formula[found1 + 1] == "Fraction") // (1/3 + 1/3) = (2/3)
					{
						long long int founda = findFra(found1 + 1, foundOP);
						long long int foundb = findFra(i + 1, foundOP);
						if (denominator[founda] == denominator[foundb])//分母相同->不需通分 分子相加後結果儲存到a裡
						{
							numerator[founda] = numerator[founda] + numerator[foundb];
							cout << numerator[founda].num << endl;
						}
						else//分母不同->通分
						{
							numerator[founda] = number(numerator[founda] * denominator[foundb]) + number(numerator[foundb] * denominator[founda]);
							denominator[founda] = denominator[founda] * denominator[foundb];
							cout << numerator[founda].num << endl;
						}
					}

					else if (formula[i] == "-" && formula[i + 1] == "Fraction" && formula[found1 + 1] != "Fraction") // (1 - 1/3) = (1*3-1)/3
					{
						long long int foundFra = findFra(i + 1, foundOP);
						number a(formula[found1 + 1]);
						numerator[foundFra].num = number(a * denominator[foundFra]) - numerator[foundFra];
						foundOP[foundFra] = found1 + 1;
						formula[found1 + 1] = "Fraction";
					}
					else if (formula[i] == "-" && formula[i + 1] != "Fraction" && formula[found1 + 1] == "Fraction") // (1/3 - 1) = (1-1*3)/3
					{
						long long int foundFra = findFra(found1 + 1, foundOP);
						number a(formula[i + 1]);
						numerator[foundFra].num = numerator[foundFra] - number(a * denominator[foundFra]);
					}
					else if (formula[i] == "-" && formula[i + 1] == "Fraction" && formula[found1 + 1] == "Fraction") // (1/3 - 1/3) = (0)
					{
						long long int founda = findFra(found1 + 1, foundOP);
						long long int foundb = findFra(i + 1, foundOP);
						if (denominator[founda] == denominator[foundb])//分母相同->不需通分 分子相加後結果儲存到a裡
						{
							numerator[founda] = numerator[founda] - numerator[foundb];
						}
						else//分母不同->通分
						{
							numerator[founda] = number(numerator[founda] * denominator[foundb]) - number(numerator[foundb] * denominator[founda]);
							denominator[founda] = denominator[founda] * denominator[foundb];
						}
					}
				}

			}
		}

		if (found1 == -1)//沒括弧的運算
		{
			if (!Fraction)//如果沒分數
				formula.erase(formula.begin() + 1, formula.end());
			else
			{
				long long int foundFra = findFra(found1 + 1, foundOP);
				formula[0] = numerator[foundFra] / denominator[foundFra];
				formula.erase(formula.begin() + 1, formula.end());
				numerator.erase(numerator.begin(), numerator.end());
				denominator.erase(denominator.begin(), denominator.end());
				foundOP.erase(foundOP.begin(), foundOP.end());
			}
		}
		else
		{
			if (!Fraction)//如果沒分數
			{
				formula[found1] = formula[found1 + 1];
				formula.erase(formula.begin() + found1 + 1, formula.begin() + found2+1);
			}
			else //有分數
			{
				long long int foundFra = findFra(found1 + 1, foundOP);
				formula[found1] = numerator[foundFra].num;
				formula[found1 + 1] = "/";
				formula[found1 + 2] = denominator[foundFra].num;
				formula.erase(formula.begin() + found1 + 3, formula.begin() + found2+1);
				numerator.erase(numerator.begin(), numerator.end());
				denominator.erase(denominator.begin(), denominator.end());
				foundOP.erase(foundOP.begin(), foundOP.end());
			}
		}
	}
}

