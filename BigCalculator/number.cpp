#include "number.h"
//////////////////////////
//////////////////////////字串串接要用 += 或 .append(str) 

void addzero(string &n)//小數補0
{
	unsigned long long int it = n.find(".");
	if (it != n.npos)
	{
		unsigned long long int need = 100 - (n.length() - it - 1);
		for (int i = 0; i < need; i++)
			n += "0";
	}
}
string number::operator +(number K)
{
	//判斷a.b是否是正數
	number a(num), b(K.num);
	if (a.num[0] == '-')//a負b負 or a負b正
	{
		a.num = a.num.substr(1, a.num.length() - 1);//去負號
		    
		return b - a;
	}
	if (b.num[0] == '-')//a+b-
	{
		b.num = b.num.substr(1, b.num.length() - 1);//去負號
		
		
		return a - b;
	}
	//判斷a.b是小數或整數相加
	unsigned long long int ait = a.num.find(".");
	unsigned long long int bit = b.num.find(".");
	bool checkDec = false;
	if (ait != a.num.npos)//a是小數
	{
		checkDec = true;
		if (bit == b.num.npos)//b不是小數，補小數點和零
		{
			b.num += ".";
			for (int i = 1; i < a.num.length() - ait; i++)
				b.num += "0";
		}
		//b是小數
	}
	else if (bit != b.num.npos)//b是小數
	{
		checkDec = true;
		if (ait == a.num.npos)//a不是小數，補小數點和零
		{
			a.num += ".";
			for (int i = 1; i < b.num.length() - bit; i++)
				a.num += "0";
		}
		//a是小數
	}

	string ans = "";
	int* numA, * numB, * numAns;//計算用陣列
	unsigned long long int len;
	if (checkDec == true)//小數相加
	{	//確認小數位數
		ait = a.num.find(".");
		bit = b.num.find(".");
		if (a.num.length() - ait > b.num.length() - bit)//a小數位數比b多，b補0
		{
			unsigned long long int zero = (a.num.length() - ait) - (b.num.length() - bit);
			for (int i = 0; i < zero; i++)
				b.num += "0";
		}
		else if (a.num.length() - ait < b.num.length() - bit)//a小數位數比b少，a補0
		{
			unsigned long long int zero = (b.num.length() - bit) - (a.num.length() - ait);
			for (int i = 0; i < zero; i++)
				a.num += "0";
		}

		string revA(a.num.rbegin(), a.num.rend()), revB(b.num.rbegin(), b.num.rend());//字串反轉
		 //整數位補前置0
		if (revA.length() > revB.length())
		{
			int L = revA.length() - revB.length();
			for (int i = 0; i < L; i++)
				revB += "0";
		}
		else if (revA.length() < revB.length())
		{
			int L = revB.length() - revA.length();
			for (int i = 0; i < L; i++)
				revA += "0";
		}

		len = revA.length();
		numA = new int[len];
		numB = new int[len];
		numAns = new int[len + 1];
		ait = revA.find(".");
		for (int i = 0; i < ait; i++)//字串轉數字(小數部分)
		{
			numA[i] = revA[i] - 48;
			numB[i] = revB[i] - 48;
		}
		numA[ait] = 0;//小數點位置
		numB[ait] = 0;
		for (int i = ait + 1; i < len; i++)//字串轉數字(整數部分)
		{
			numA[i] = revA[i] - 48;
			numB[i] = revB[i] - 48;
		}

		for (int i = 0; i < len + 1; i++)//答案陣列歸零
			numAns[i] = 0;
		//計算過程
		int c = 0;
		for (int i = 0; i < ait; i++)//小數部分計算
		{
			numAns[i] = numA[i] + numB[i] + c;
			if (numAns[i] > 9)//進位
			{
				numAns[i] -= 10;
				c = 1;
			}
			else
				c = 0;
		}
		for (int i = ait + 1; i < len; i++)//整數部分計算
		{
			numAns[i] = numA[i] + numB[i] + c;
			if (numAns[i] > 9)//進位
			{
				numAns[i] -= 10;
				c = 1;
			}
			else
				c = 0;
		}
		numAns[len] = c;//最高位
		if (numAns[len] == 0)//加法結果位數沒有超過a.b
			len--;
		//結果轉換回字串
		for (int i = len; i > ait; i--)
			ans += to_string(numAns[i]);
		ans += ".";
		for (int i = ait - 1; i >= 0; i--)
			ans += to_string(numAns[i]);
		addzero(ans);//小數補0
	}
	else//整數相加
	{
		string revA(a.num.rbegin(), a.num.rend()), revB(b.num.rbegin(), b.num.rend());//字串反轉
		 //整數位補前置0
		if (revA.length() > revB.length())
		{
			int L = revA.length() - revB.length();
			for (int i = 0; i < L; i++)
			{
				revB += "0";
			}
				
		}
		else if (revA.length() < revB.length())
		{
			int L = revB.length() - revA.length();
			for (int i = 0; i < L; i++)
			{
				revA += "0";
			}
		}

		len = revA.length();
		numA = new int[len];
		numB = new int[len];
		numAns = new int[len + 1];
		for (int i = 0; i < len; i++)//字串轉數字
		{
			numA[i] = revA[i] - 48;
			numB[i] = revB[i] - 48;
		}
		for (int i = 0; i < len + 1; i++)//答案陣列歸零
			numAns[i] = 0;
		//計算過程
		int c = 0;
		for (int i = 0; i < len; i++)
		{
			numAns[i] = numA[i] + numB[i] + c;
			if (numAns[i] > 9)//進位
			{
				numAns[i] -= 10;
				c = 1;
			}
			else
				c = 0;
		}
		numAns[len] = c;//最高位
		if (numAns[len] == 0)//加法結果位數沒有超過a.b
			len--;
		//結果轉換回字串
		for (int i = len; i >= 0; i--)
			ans += to_string(numAns[i]);
	}
	delete[]numA;
	delete[]numB;
	delete[]numAns;
	return ans;
};

string number::operator -(number K)
{
	number a(num), b(K.num);
//判斷a.b是否是正數
	if (b.num[0] == '-')//a-(-5)=a+5
	{
		b.num = b.num.substr(1, b.num.length() - 1);//去負號
		//number tmp1(num),tmp2(b.num);
		return a + b;
	}
	if (a.num[0] == '-')//a負b正 (-5)-b=-(5+b)
	{
		a.num = a.num.substr(1, a.num.length() - 1);//去負號
		//number tmp1(num),tmp2(b.num);
		string temp = a + b;
		string ans = "-";
		ans.append(temp);
		return ans;
	}
	//a.b為兩正數相減
	//判斷a.b是小數或整數
	unsigned long long int ait = a.num.find(".");
	unsigned long long int bit = b.num.find(".");
	bool checkDec = false;
	if (ait != a.num.npos)//a是小數
	{
		checkDec = true;
		if (bit == b.num.npos)//b不是小數，補小數點和零
		{
			b.num += ".";
			for (int i = 1; i < a.num.length() - ait; i++)
				b.num += "0";
		}
		//b是小數
	}
	else if (bit != b.num.npos)//b是小數
	{
		checkDec = true;
		if (ait == a.num.npos)//a不是小數，補小數點和零
		{
			a.num += ".";
			for (int i = 1; i < b.num.length() - bit; i++)
				a.num += "0";
		}
		//a是小數
	}

	string ans = "";
	int* numA, * numB, * numAns;//計算用陣列
	unsigned long long int len;
	bool PN = true;//結果正(t)負(f)
	if (checkDec == true)//小數相減
	{
		//小數位數先補0
		ait = a.num.find(".");
		bit = b.num.find(".");
		if (a.num.length() - ait > b.num.length() - bit)//a小數位數比b多，b補0
		{
			unsigned long long int zero = (a.num.length() - ait) - (b.num.length() - bit);
			for (int i = 0; i < zero; i++)
				b.num += "0";
		}
		else if (a.num.length() - ait < b.num.length() - bit)//a小數位數比b少，a補0
		{
			unsigned long long int zero = (b.num.length() - bit) - (a.num.length() - ait);
			for (int i = 0; i < zero; i++)
				a.num += "0";
		}
		
		//比較a,b大小
		if (ait < bit)//a的整數位數比b小，減法結果為負
		{
			PN = false;
			string temp = a.num;//3-5交換-(5-3)
			a.num = b.num;
			b.num = temp;
			unsigned long long int t = ait;
			ait = bit;
			bit = t;
		}
		else if (ait == bit)//整數位數相同，逐數比較
		{
			bool tempCheck = false;//比較整數
			for (int i = 0; i < ait; i++)
			{
				if (a.num[i] > b.num[i])
				{
					tempCheck = true;
					break;
				}
				if (a.num[i] < b.num[i])
				{
					PN = false;
					string temp = a.num;//3-5交換-(5-3)
					a.num = b.num;
					b.num = temp;
					unsigned long long int t = ait;
					ait = bit;
					bit = t;
				}
			}
			if (PN == true && tempCheck==false)//整數沒比較出大小，比較小數
			{
				for (int i = ait + 1; i < a.num.length(); i++)
				{
					if (a.num[i] > b.num[i])
					{
						tempCheck = true;
						break;
					}
					if (a.num[i] < b.num[i])
					{
						tempCheck = true;
						PN = false;
						string temp = a.num;//3-5交換-(5-3)
						a.num = b.num;
						b.num = temp;
						unsigned long long int t = ait;
						ait = bit;
						bit = t;
					}
				}
				if (tempCheck == false)//沒比較出大小，a=b
				{
					ans = "0.0";
					addzero(ans);
					return ans;
				}
			}
		}

		string revA(a.num.rbegin(), a.num.rend()), revB(b.num.rbegin(), b.num.rend());//字串反轉
		 //整數位補前置0
		if (revA.length() > revB.length())
		{
			int L = revA.length() - revB.length();
			for (int i = 0; i < L; i++)
				revB += "0";
		}
		else if (revA.length() < revB.length())
		{
			int L = revB.length() - revA.length();
			for (int i = 0; i < L; i++)
				revA += "0";
		}

		len = revA.length();
		numA = new int[len];
		numB = new int[len];
		numAns = new int[len];
		ait = revA.find(".");
		for (int i = 0; i < ait; i++)//字串轉數字(小數部分)
		{
			numA[i] = revA[i] - 48;
			numB[i] = revB[i] - 48;
		}
		numA[ait] = 0;//小數點位置
		numB[ait] = 0;
		for (int i = ait + 1; i < len; i++)//字串轉數字(整數部分)
		{
			numA[i] = revA[i] - 48;
			numB[i] = revB[i] - 48;
		}

		for (int i = 0; i < len; i++)//答案陣列歸零
			numAns[i] = 0;
		//計算過程
		int c = 0;
		for (int i = 0; i < ait; i++)//小數部分計算
		{
			numAns[i] = numA[i] - numB[i] - c;
			if (numAns[i] < 0)//借位
			{
				numAns[i] += 10;
				c = 1;
			}
			else
				c = 0;
		}
		for (int i = ait + 1; i < len; i++)//整數部分計算
		{
			numAns[i] = numA[i] - numB[i] - c;
			if (numAns[i] < 0)//借位
			{
				numAns[i] += 10;
				c = 1;
			}
			else
				c = 0;
		}
		while(len - 2 != ait && numAns[len - 1] == 0)//找最高位不為0的數且保留整數最少一位數(134.1-134=000.1)
			len--;
		//結果轉換回字串
		if (PN == false)//結果是負數，負號加回
			ans = "-";
		for (int i = len - 1; i > ait; i--)
			ans += to_string(numAns[i]);
		ans += ".";
		for (int i = ait - 1; i >= 0; i--)
			ans += to_string(numAns[i]);
		addzero(ans);
	}
	else//整數相減
	{
		//比較a,b大小
		if (a.num.length() < b.num.length())//a的位數比b小，減法結果為負
		{
			PN = false;
			string temp = a.num;//3-5交換-(5-3)
			a.num = b.num;
			b.num = temp;
		}
		else if (a.num.length() == b.num.length())//位數相同，逐數比較
		{
			bool tempCheck = false;//比較整數
			for (int i = 0; i < a.num.length(); i++)
			{
				if (a.num[i] > b.num[i])
				{
					tempCheck = true;
					break;
				}
				if (a.num[i] < b.num[i])
				{
					PN = false;
					string temp = a.num;//3-5交換-(5-3)
					a.num = b.num;
					b.num = temp;
					break;
				}
			}
			if (PN == true && tempCheck == false)//沒比較出大小，a=b
				return "0";
		}
		string revA(a.num.rbegin(), a.num.rend()), revB(b.num.rbegin(), b.num.rend());//字串反轉
		 //整數位補前置0
		if (revA.length() > revB.length())
		{
			int L = revA.length() - revB.length();
			for (int i = 0; i < L; i++)
				revB += "0";
		}
		else if (revA.length() < revB.length())
		{
			int L = revB.length() - revA.length();
			for (int i = 0; i < L; i++)
				revA += "0";
		}

		len = revA.length();
		numA = new int[len];
		numB = new int[len];
		numAns = new int[len];
		for (int i = 0; i < len; i++)//字串轉數字
		{
			numA[i] = revA[i] - 48;
			numB[i] = revB[i] - 48;
		}
		for (int i = 0; i < len; i++)//答案陣列歸零
			numAns[i] = 0;
		//計算過程
		int c = 0;
		for (int i = 0; i < len; i++)
		{
			numAns[i] = numA[i] - numB[i] - c;
			if (numAns[i] < 0)//進位
			{
				numAns[i] += 10;
				c = 1;
			}
			else
				c = 0;
		}
		while (len > 1 && numAns[len - 1] == 0)//找最高位不為0的數且保留整數最少一位數(134-133=001)
			len--;
		//結果轉換回字串
		if (PN == false)//結果是負數，負號加回
			ans = "-";
		for (int i = len - 1; i >= 0; i--)
			ans += to_string(numAns[i]);
	}
	delete[]numA;
	delete[]numB;
	delete[]numAns;
	return ans;
}

string number::operator *(number K)
{
	number a(num), b(K.num);
	bool PN = true;//結果正(T)負(F)
	//判斷a.b正負號
	if (a.num[0] == '-' && b.num[0] == '-')//a.b負，結果為正
	{
		a.num = a.num.substr(1, a.num.length() - 1);//去負號
		b.num = b.num.substr(1, b.num.length() - 1);//去負號
	}
	else if (a.num[0] == '-')//a-b+
	{
		PN = false;
		a.num = a.num.substr(1, a.num.length() - 1);//去負號
	}
	else if (b.num[0] == '-')//a+b-
	{
		PN = false;
		b.num = b.num.substr(1, b.num.length() - 1);//去負號
	}
	//取完a.b無正負號
	//判斷a.b是小數或整數相乘，是小數就把小數點去除，紀錄小數位數
	unsigned long long int ait = a.num.find(".");
	unsigned long long int bit = b.num.find(".");
	unsigned long long int countDec = 0;
	bool checkDec = false;
	if (ait != a.num.npos)//a是小數
	{
		checkDec = true;
		countDec = countDec + a.num.length() - ait -1;
		string temp = a.num.substr(ait + 1, a.num.length() - ait - 1);//小數部分
		a.num = a.num.substr(0, ait);//整數部分
		a.num.append(temp);
	}
	if (bit != b.num.npos)//b是小數
	{
		checkDec = true;
		countDec = countDec + b.num.length() - bit - 1;
		string temp = b.num.substr(bit + 1, b.num.length() - bit - 1);//小數部分
		b.num = b.num.substr(0, bit);//整數部分
		b.num.append(temp);
	}

	string ans = "";
	int* numA, * numB, * numAns;//計算用陣列
	string revA(a.num.rbegin(), a.num.rend()), revB(b.num.rbegin(), b.num.rend());//字串反轉
	unsigned long long int len = revA.length() + revB.length();
	numA = new int[revA.length()];
	numB = new int[revB.length()];
	numAns = new int[len];
	for (int i = 0; i < revA.length(); i++)//字串轉數字
		numA[i] = revA[i] - 48;

	for (int i = 0; i < revB.length(); i++)//字串轉數字
		numB[i] = revB[i] - 48;

	for (int i = 0; i < len; i++)//答案陣列歸零
		numAns[i] = 0;

	//計算過程
	int c = 0;
	for (int i = 0; i < revA.length(); i++)
	{
		for (int j = 0; j < revB.length(); j++)
		{
			numAns[i + j] += numA[i] * numB[j];
			if (numAns[i + j] > 9)
			{
				numAns[i + j + 1] += numAns[i + j] / 10;
				numAns[i + j] %= 10;
			}
		}
	}

	//結果轉換回字串
	while (len > 1 && numAns[len - 1] == 0)//找最高位不為0的數且保留整數最少一位數(120*5=0600)
		len--;

	if (checkDec == true)//結果是小數，小數點補回
	{
		for (int i = 0; i <countDec; i++)//小數
			ans += to_string(numAns[i]);
		ans += ".";
		for (int i = countDec; i <len; i++)//整數
			ans += to_string(numAns[i]);
		if (ans[ans.length() - 1] == '.')//整數部分為0
			ans += "0";
		if (PN == false)//結果是負數，負號加回
			ans += "-";
		reverse(ans.begin(), ans.end());
		addzero(ans);
	}
	else//結果是整數，直接轉換字串
	{
		if (PN == false)//結果是負數，負號加回
			ans = "-";
		for (int i = len - 1; i >= 0; i--)
			ans += to_string(numAns[i]);
	}
	delete[]numA;
	delete[]numB;
	delete[]numAns;
	return ans;
}



/*string operator +(string a, string b)
{
	//判斷a.b是否是正數
	if (a[0] == '-')//a負b負 or a負b正
	{
		a = a.substr(1, a.length() - 1);//去負號
		number temp(a, b);
		return temp.numb - temp.numa;
	}
	if (b[0] == '-')//a+b-
	{
		b = b.substr(1, b.length() - 1);//去負號
		number temp(a, b);
		return temp.numa - temp.numb;
	}
	//判斷a.b是小數或整數相加
	unsigned long long int ait = a.find(".");
	unsigned long long int bit = b.find(".");
	bool checkDec = false;
	if (ait != a.npos)//a是小數
	{
		checkDec = true;
		if (bit == b.npos)//b不是小數，補小數點和零
		{
			b += ".";
			for (int i = 1; i < a.length() - ait; i++)
				b += "0";
		}
		//b是小數
	}
	else if (bit != b.npos)//b是小數
	{
		checkDec = true;
		if (ait == a.npos)//a不是小數，補小數點和零
		{
			a += ".";
			for (int i = 1; i < b.length() - bit; i++)
				a += "0";
		}
		//a是小數
	}

	string ans="";
	int* numA, * numB, * numAns;//計算用陣列
	unsigned long long int len;
	if (checkDec == true)//小數相加
	{	//確認小數位數
		ait = a.find(".");
		bit = b.find(".");
		if (a.length() - ait > b.length() - bit)//a小數位數比b多，b補0
		{
			unsigned long long int zero = (a.length() - ait) - (b.length() - bit);
			for (int i = 0; i < zero; i++)
				b += "0";
		}
		else if (a.length() - ait < b.length() - bit)//a小數位數比b少，a補0
		{
			unsigned long long int zero = (b.length() - bit) - (a.length() - ait);
			for (int i = 0; i < zero; i++)
				a += "0";
		}

		string revA(a.rbegin(), a.rend()),revB(b.rbegin(), b.rend());//字串反轉
		 //整數位補前置0
		if (revA.length() > revB.length())
		{
			for (int i = 0; i < revA.length() - revB.length(); i++)
				revB += "0";
		}
		else if (revA.length() < revB.length())
		{
			for (int i = 0; i < revB.length() - revA.length(); i++)
				revA += "0";
		}

		len = revA.length();
		numA = new int[len];
		numB = new int[len];
		numAns = new int[len + 1];
		ait = revA.find(".");
		for (int i = 0; i < ait; i++)//字串轉數字(小數部分)
		{
			numA[i] = revA[i] - 48;
			numB[i] = revB[i] - 48;
		}
		numA[ait] = 0;//小數點位置
		numB[ait] = 0;
		for (int i = ait + 1; i < len; i++)//字串轉數字(整數部分)
		{
			numA[i] = revA[i] - 48;
			numB[i] = revB[i] - 48;
		}
			
		for (int i = 0; i < len + 1; i++)//答案陣列歸零
			numAns[i] = 0;
		//計算過程
		int c = 0;
		for (int i = 0; i < ait; i++)//小數部分計算
		{
			numAns[i] = numA[i] + numB[i] + c;
			if (numAns[i] > 9)//進位
			{
				numAns[i] -= 10;
				c = 1;
			}
			else
				c = 0;
		}
		for (int i = ait + 1; i < len; i++)//整數部分計算
		{
			numAns[i] = numA[i] + numB[i] + c;
			if (numAns[i] > 9)//進位
			{
				numAns[i] -= 10;
				c = 1;
			}
			else
				c = 0;
		}
		numAns[len] = c;//最高位
		if (numAns[len] == 0)//加法結果位數沒有超過a.b
			len--;
		//結果轉換回字串
		for (int i = len; i > ait; i--)
			ans += to_string(numAns[i]);
		ans += ".";
		for (int i = ait - 1; i >= 0; i--)
			ans += to_string(numAns[i]);
		addzero(ans);//小數補0
	}
	else//整數相加
	{
		string revA(a.rbegin(), a.rend()), revB(b.rbegin(), b.rend());//字串反轉
		 //整數位補前置0
		if (revA.length() > revB.length())
		{
			for (int i = 0; i < revA.length() - revB.length(); i++)
				revB += "0";
		}
		else if (revA.length() < revB.length())
		{
			for (int i = 0; i < revB.length() - revA.length(); i++)
				revA += "0";
		}

		len = revA.length();
		numA = new int[len];
		numB = new int[len];
		numAns = new int[len + 1];
		for (int i = 0; i < len; i++)//字串轉數字
		{
			numA[i] = revA[i] - 48;
			numB[i] = revB[i] - 48;
		}
		for (int i = 0; i < len + 1; i++)//答案陣列歸零
			numAns[i] = 0;
		//計算過程
		int c = 0;
		for (int i = 0; i < len; i++)
		{
			numAns[i] = numA[i] + numB[i] + c;
			if (numAns[i] > 9)//進位
			{
				numAns[i] -= 10;
				c = 1;
			}
			else
				c = 0;
		}
		numAns[len] = c;//最高位
		if (numAns[len] == 0)//加法結果位數沒有超過a.b
			len--;
		//結果轉換回字串
		for (int i = len; i >= 0; i--)
			ans += to_string(numAns[i]);
	}
	delete[]numA;
	delete[]numB;
	delete[]numAns;
	return ans;
}*/
/*string operator -(string a, string b)
{
	//判斷a.b是否是正數
	if (b[0] == '-')//a-(-5)=a+5
	{
		b = b.substr(1, b.length() - 1);//去負號
		number tmp(a, b);
		return tmp.numa + tmp.numb;
	}
	if (a[0] == '-')//a負b正 (-5)-b=-(5+b)
	{
		a = a.substr(1, a.length() - 1);//去負號
		number tmp(a, b);
		string temp = tmp.numa + tmp.numb;
		string ans = "-";
		ans.append(temp);
		return ans;
	}
	//a.b為兩正數相減
	//判斷a.b是小數或整數
	unsigned long long int ait = a.find(".");
	unsigned long long int bit = b.find(".");
	bool checkDec = false;
	if (ait != a.npos)//a是小數
	{
		checkDec = true;
		if (bit == b.npos)//b不是小數，補小數點和零
		{
			b += ".";
			for (int i = 1; i < a.length() - ait; i++)
				b += "0";
		}
		//b是小數
	}
	else if (bit != b.npos)//b是小數
	{
		checkDec = true;
		if (ait == a.npos)//a不是小數，補小數點和零
		{
			a += ".";
			for (int i = 1; i < b.length() - bit; i++)
				a += "0";
		}
		//a是小數
	}

	string ans = "";
	int* numA, * numB, * numAns;//計算用陣列
	unsigned long long int len;
	bool PN = true;//結果正(t)負(f)
	if (checkDec == true)//小數相減
	{
		//小數位數先補0
		ait = a.find(".");
		bit = b.find(".");
		if (a.length() - ait > b.length() - bit)//a小數位數比b多，b補0
		{
			unsigned long long int zero = (a.length() - ait) - (b.length() - bit);
			for (int i = 0; i < zero; i++)
				b += "0";
		}
		else if (a.length() - ait < b.length() - bit)//a小數位數比b少，a補0
		{
			unsigned long long int zero = (b.length() - bit) - (a.length() - ait);
			for (int i = 0; i < zero; i++)
				a += "0";
		}
		
		//比較a,b大小
		if (ait < bit)//a的整數位數比b小，減法結果為負
		{
			PN = false;
			string temp = a;//3-5交換-(5-3)
			a = b;
			b = temp;
			unsigned long long int t = ait;
			ait = bit;
			bit = t;
		}
		else if (ait == bit)//整數位數相同，逐數比較
		{
			bool tempCheck = false;//比較整數
			for (int i = 0; i < ait; i++)
			{
				if (a[i] > b[i])
				{
					tempCheck = true;
					break;
				}
				if (a[i] < b[i])
				{
					PN = false;
					string temp = a;//3-5交換-(5-3)
					a = b;
					b = temp;
					unsigned long long int t = ait;
					ait = bit;
					bit = t;
					break;
				}
			}
			if (PN == true && tempCheck==false)//整數沒比較出大小，比較小數
			{
				for (int i = ait + 1; i < a.length(); i++)
				{
					if (a[i] > b[i])
					{
						tempCheck = true;
						break;
					}
					if (a[i] < b[i])
					{
						tempCheck = true;
						PN = false;
						string temp = a;//3-5交換-(5-3)
						a = b;
						b = temp;
						unsigned long long int t = ait;
						ait = bit;
						bit = t;
						break;
					}
				}
				if (tempCheck == false)//沒比較出大小，a=b
				{
					ans = "0.0";
					addzero(ans);
					return ans;
				}
			}
		}

		string revA(a.rbegin(), a.rend()), revB(b.rbegin(), b.rend());//字串反轉
		 //整數位補前置0
		if (revA.length() > revB.length())
		{
			for (int i = 0; i < revA.length() - revB.length(); i++)
				revB += "0";
		}
		else if (revA.length() < revB.length())
		{
			for (int i = 0; i < revB.length() - revA.length(); i++)
				revA += "0";
		}

		len = revA.length();
		numA = new int[len];
		numB = new int[len];
		numAns = new int[len];
		ait = revA.find(".");
		for (int i = 0; i < ait; i++)//字串轉數字(小數部分)
		{
			numA[i] = revA[i] - 48;
			numB[i] = revB[i] - 48;
		}
		numA[ait] = 0;//小數點位置
		numB[ait] = 0;
		for (int i = ait + 1; i < len; i++)//字串轉數字(整數部分)
		{
			numA[i] = revA[i] - 48;
			numB[i] = revB[i] - 48;
		}

		for (int i = 0; i < len; i++)//答案陣列歸零
			numAns[i] = 0;
		//計算過程
		int c = 0;
		for (int i = 0; i < ait; i++)//小數部分計算
		{
			numAns[i] = numA[i] - numB[i] - c;
			if (numAns[i] < 0)//借位
			{
				numAns[i] += 10;
				c = 1;
			}
			else
				c = 0;
		}
		for (int i = ait + 1; i < len; i++)//整數部分計算
		{
			numAns[i] = numA[i] - numB[i] - c;
			if (numAns[i] < 0)//借位
			{
				numAns[i] += 10;
				c = 1;
			}
			else
				c = 0;
		}
		while(len - 2 != ait && numAns[len - 1] == 0)//找最高位不為0的數且保留整數最少一位數(134.1-134=000.1)
			len--;
		//結果轉換回字串
		if (PN == false)//結果是負數，負號加回
			ans = "-";
		for (int i = len - 1; i > ait; i--)
			ans += to_string(numAns[i]);
		ans += ".";
		for (int i = ait - 1; i >= 0; i--)
			ans += to_string(numAns[i]);
		addzero(ans);
	}
	else//整數相加
	{
		//比較a,b大小
		if (a.length() < b.length())//a的位數比b小，減法結果為負
		{
			PN = false;
			string temp = a;//3-5交換-(5-3)
			a = b;
			b = temp;
		}
		else if (a.length() == b.length())//位數相同，逐數比較
		{
			bool tempCheck = false;//比較整數
			for (int i = 0; i < a.length(); i++)
			{
				if (a[i] > b[i])
				{
					tempCheck = true;
					break;
				}
				if (a[i] < b[i])
				{
					PN = false;
					string temp = a;//3-5交換-(5-3)
					a = b;
					b = temp;
					break;
				}
			}
			if (PN == true && tempCheck == false)//沒比較出大小，a=b
				return "0";
		}
		string revA(a.rbegin(), a.rend()), revB(b.rbegin(), b.rend());//字串反轉
		 //整數位補前置0
		if (revA.length() > revB.length())
		{
			for (int i = 0; i < revA.length() - revB.length(); i++)
				revB += "0";
		}
		else if (revA.length() < revB.length())
		{
			for (int i = 0; i < revB.length() - revA.length(); i++)
				revA += "0";
		}

		len = revA.length();
		numA = new int[len];
		numB = new int[len];
		numAns = new int[len];
		for (int i = 0; i < len; i++)//字串轉數字
		{
			numA[i] = revA[i] - 48;
			numB[i] = revB[i] - 48;
		}
		for (int i = 0; i < len; i++)//答案陣列歸零
			numAns[i] = 0;
		//計算過程
		int c = 0;
		for (int i = 0; i < len; i++)
		{
			numAns[i] = numA[i] - numB[i] - c;
			if (numAns[i] < 0)//進位
			{
				numAns[i] += 10;
				c = 1;
			}
			else
				c = 0;
		}
		while (len > 1 && numAns[len - 1] == 0)//找最高位不為0的數且保留整數最少一位數(134-133=001)
			len--;
		//結果轉換回字串
		if (PN == false)//結果是負數，負號加回
			ans = "-";
		for (int i = len - 1; i >= 0; i--)
			ans += to_string(numAns[i]);
	}
	delete[]numA;
	delete[]numB;
	delete[]numAns;
	return ans;
}*/
/*string operator *(string a, string b)
{
	bool PN = true;//結果正(T)負(F)
	//判斷a.b正負號
	if (a[0] == '-' && b[0] == '-')//a.b負，結果為正
	{
		a = a.substr(1, a.length() - 1);//去負號
		b = b.substr(1, b.length() - 1);//去負號
	}
	else if (a[0] == '-')//a-b+
	{
		PN = false;
		a = a.substr(1, a.length() - 1);//去負號
	}
	else if (b[0] == '-')//a+b-
	{
		PN = false;
		b = b.substr(1, b.length() - 1);//去負號
	}
	//取完a.b無正負號
	//判斷a.b是小數或整數相乘，是小數就把小數點去除，紀錄小數位數
	unsigned long long int ait = a.find(".");
	unsigned long long int bit = b.find(".");
	unsigned long long int countDec = 0;
	bool checkDec = false;
	if (ait != a.npos)//a是小數
	{
		checkDec = true;
		countDec = countDec + a.length() - ait - 1;
		string temp = a.substr(ait+1,a.length()-ait-1);//小數部分
		a = a.substr(0, ait);//整數部分
		a.append(temp);
	}
	if (bit != b.npos)//b是小數
	{
		checkDec = true;
		countDec = countDec + b.length() - bit - 1;
		string temp = b.substr(bit + 1, b.length() - bit - 1);//小數部分
		b = b.substr(0, bit);//整數部分
		b.append(temp);
	}

	string ans = "";
	int* numA, * numB, * numAns;//計算用陣列
	string revA(a.rbegin(), a.rend()), revB(b.rbegin(), b.rend());//字串反轉
	unsigned long long int len = revA.length() + revB.length();
	numA = new int[revA.length()];
	numB = new int[revB.length()];
	numAns = new int[len];
	for (int i = 0; i < revA.length(); i++)//字串轉數字
		numA[i] = revA[i] - 48;

	for (int i = 0; i < revB.length(); i++)//字串轉數字
		numB[i] = revB[i] - 48;

	for (int i = 0; i < len; i++)//答案陣列歸零
		numAns[i] = 0;

	//計算過程
	int c = 0;
	for (int i = 0; i < revA.length(); i++)
	{
		for (int j = 0; j < revB.length(); j++)
		{
			int temp = numA[i] * numB[j];
			numAns[i + j] += temp % 10;
			numAns[i + j + 1] += temp / 10;
		}
	}
	//結果轉換回字串
	while (len > 1 && numAns[len - 1] == 0)//找最高位不為0的數且保留整數最少一位數(120*5=0600)
		len--;

	if (PN == false)//結果是負數，負號加回
		ans = "-";
	if (checkDec == true)//結果是小數，小數點補回
	{
		for (int i = len - 1; i > len-countDec; i--)//整數
			ans += to_string(numAns[i]);
		ans += ".";
		for (int i = len - countDec; i >= 0; i--)//小數
			ans += to_string(numAns[i]);
		addzero(ans);
	}
	else//結果是整數，直接轉換字串
	{
		for (int i = len - 1; i >= 0; i--)
			ans += to_string(numAns[i]);
	}
	delete[]numA;
	delete[]numB;
	delete[]numAns;
	return ans;
}*/
/*string operator /(string a, string b)
{
	return "0";
}
string Exponential(string a, string b)//指數
{
	return "0";
}
string Factorial(string a, string b)//階乘
{
	return "0";
}*/