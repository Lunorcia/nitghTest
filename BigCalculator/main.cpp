#include "number.h"
bool checkBracketAmount(const string& line);
bool checkOperator(string line);
bool checkDPs(const string& num);
bool negativeRoot(const string& num);
void mergePN(string& num);
bool convertPower(vector<string>& formula);
void checkValidCompute(vector<string> formula);
int main()
{	//次方功能還沒做>>Power(2,3)>>輸入整串不要空格，進計算用函式轉成
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
		//先判斷有沒有關鍵字Set
		
		vector<string> formula;//儲存算式用
		stringstream ss(input);
		string tempss="";
		while (getline(ss, tempss, ' '))//拆解輸入字串
			formula.push_back(tempss);
		ss.str("");
		ss.clear();

		//如果vector size=1，代表尋找並輸出變數
		//如果第二個字串是等號，最後結果只要assign，不用輸出

		if (!checkBracketAmount(input))//檢查括號數
		{
			cout << "括號不完全" << endl;
			continue;//讀下一個輸入算式
		}
		if (!checkOperator(input))//檢查連續運算子
		{
			cout << "不可連續輸入(正.負號.階乘)以外的運算子+-*/^" << endl;
			continue;//讀下一個輸入算式
		}
		/////////////////////////////Power轉換後會需要重複用檢查的部分，之後獨立成一個函式
		bool checkValid = true;
		for (int i = 0; i < formula.size(); i++)
		{
			//Integer&Decimal變數照樣傳入
			//移除前置0的處理寫到class number的construct裡，把字串存成數字時自動做
			
			string temp = formula[i];
			if (temp == "(" || temp == ")" || temp == "+" || temp == "-" || temp == "*" || temp == "/" || temp == "!" || temp == "^" || temp.substr(0, 5) == "Power")//一般運算子不用處理
				continue;
			mergePN(temp);//正負號整合(如果有小數點沒有前置0也會補上)
			if (temp == "WRONG_NAME")
			{
				cout << "找不到變數" << endl;
				checkValid = false;
				break;
			}
			if (!checkDPs(temp))//數字有複數個小數點
			{
				cout << "小數點輸入錯誤" << endl;
				break;
			}

			formula[i] = temp;//檢測正確，把正負號整合完& Int or Dec的值結果存回取代
		}
		
		if (checkValid == false)//輸入數字檢測不符規定
			continue;//讀下一個輸入算式
		checkValid = convertPower(formula);//轉換Power(a,b)>>a^b
		if (!checkValid)
		{
			cout << "Power輸入錯誤" << endl;
			continue;//讀下一個輸入算式
		}

	}

	//防呆用函式是全域，直接傳入字串檢測
	//Power(5, 2)
	//拆解數字前防呆:括號數，連續運算符+-*/^
	//拆解後單獨數字一律先進正負號整合,ex: +-+5 >> -5，然後進小數點數量確認(不管是不是小數)
	//計算優先度:階乘>指數
	//計算前(底線標示輸入算式的空格):	階乘不能是負數,ex:-5_!
	//									除數不能是0,ex: 5_/_0	
	//									負數不能開根號,ex: -2.5_^_0.5
	//									指數計算前>>根號0=0
}