#include "number.h"
//////////////////////////
//////////////////////////﹃﹃钡璶ノ += ┪ .append(str) 
string operator +(string a, string b);
string operator -(string a, string b);
void addzero(string &num)//计干0
{
	unsigned long long int it = num.find(".");
	unsigned long long int need = 100-(num.length() - it - 1);
	for (int i = 0; i < need; i++)
		num += "0";
}
string operator +(string a, string b)
{
	//耞a.b琌琌タ计
	if (a[0] == '-')//a璽b璽 or a璽bタ
	{
		a = a.substr(1, a.length() - 1);//璽腹
		number temp(a, b);
		return temp.numb - temp.numa;
	}
	if (b[0] == '-')//a+b-
	{
		b = b.substr(1, b.length() - 1);//璽腹
		number temp(a, b);
		return temp.numa - temp.numb;
	}
	//耞a.b琌计┪俱计
	unsigned long long int ait = a.find(".");
	unsigned long long int bit = b.find(".");
	bool checkDec = false;
	if (ait != a.npos)//a琌计
	{
		checkDec = true;
		if (bit == b.npos)//bぃ琌计干计翴㎝箂
		{
			b += ".";
			for (int i = 1; i < a.length() - ait; i++)
				b += "0";
		}
		//b琌计
	}
	else if (bit != b.npos)//b琌计
	{
		checkDec = true;
		if (ait == a.npos)//aぃ琌计干计翴㎝箂
		{
			a += ".";
			for (int i = 1; i < b.length() - bit; i++)
				a += "0";
		}
		//a琌计
	}

	string ans="";
	int* numA, * numB, * numAns;//璸衡ノ皚
	unsigned long long int len;
	if (checkDec == true)//计
	{	//絋粄计计
		ait = a.find(".");
		bit = b.find(".");
		if (a.length() - ait > b.length() - bit)//a计计ゑbb干0
		{
			unsigned long long int zero = (a.length() - ait) - (b.length() - bit);
			for (int i = 0; i < zero; i++)
				b += "0";
		}
		else if (a.length() - ait < b.length() - bit)//a计计ゑbぶa干0
		{
			unsigned long long int zero = (b.length() - bit) - (a.length() - ait);
			for (int i = 0; i < zero; i++)
				a += "0";
		}

		string revA(a.rbegin(), a.rend()),revB(b.rbegin(), b.rend());//﹃は锣
		 //俱计干玡竚0
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
		for (int i = 0; i < ait; i++)//﹃锣计(计场だ)
		{
			numA[i] = revA[i] - 48;
			numB[i] = revB[i] - 48;
		}
		numA[ait] = 0;//计翴竚
		numB[ait] = 0;
		for (int i = ait + 1; i < len; i++)//﹃锣计(俱计场だ)
		{
			numA[i] = revA[i] - 48;
			numB[i] = revB[i] - 48;
		}
			
		for (int i = 0; i < len + 1; i++)//氮皚耴箂
			numAns[i] = 0;
		//璸衡筁祘
		int c = 0;
		for (int i = 0; i < ait; i++)//计场だ璸衡
		{
			numAns[i] = numA[i] + numB[i] + c;
			if (numAns[i] > 9)//秈
			{
				numAns[i] -= 10;
				c = 1;
			}
			else
				c = 0;
		}
		for (int i = ait + 1; i < len; i++)//俱计场だ璸衡
		{
			numAns[i] = numA[i] + numB[i] + c;
			if (numAns[i] > 9)//秈
			{
				numAns[i] -= 10;
				c = 1;
			}
			else
				c = 0;
		}
		numAns[len] = c;//程蔼
		if (numAns[len] == 0)//猭挡狦计⊿Τ禬筁a.b
			len--;
		//挡狦锣传﹃
		for (int i = len; i > ait; i--)
			ans += to_string(numAns[i]);
		ans += ".";
		for (int i = ait - 1; i >= 0; i--)
			ans += to_string(numAns[i]);
		addzero(ans);//计干0
	}
	else//俱计
	{
		string revA(a.rbegin(), a.rend()), revB(b.rbegin(), b.rend());//﹃は锣
		 //俱计干玡竚0
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
		for (int i = 0; i < len; i++)//﹃锣计
		{
			numA[i] = revA[i] - 48;
			numB[i] = revB[i] - 48;
		}
		for (int i = 0; i < len + 1; i++)//氮皚耴箂
			numAns[i] = 0;
		//璸衡筁祘
		int c = 0;
		for (int i = 0; i < len; i++)
		{
			numAns[i] = numA[i] + numB[i] + c;
			if (numAns[i] > 9)//秈
			{
				numAns[i] -= 10;
				c = 1;
			}
			else
				c = 0;
		}
		numAns[len] = c;//程蔼
		if (numAns[len] == 0)//猭挡狦计⊿Τ禬筁a.b
			len--;
		//挡狦锣传﹃
		for (int i = len; i >= 0; i--)
			ans += to_string(numAns[i]);
	}
	delete[]numA;
	delete[]numB;
	delete[]numAns;
	return ans;
}
string operator -(string a, string b)
{
	//耞a.b琌琌タ计
	if (b[0] == '-')//a-(-5)=a+5
	{
		b = b.substr(1, b.length() - 1);//璽腹
		number tmp(a, b);
		return tmp.numa + tmp.numb;
	}
	if (a[0] == '-')//a璽bタ (-5)-b=-(5+b)
	{
		a = a.substr(1, a.length() - 1);//璽腹
		number tmp(a, b);
		string temp = tmp.numa + tmp.numb;
		string ans = "-";
		ans.append(temp);
		return ans;
	}
	//a.bㄢタ计搭
	//耞a.b琌计┪俱计
	unsigned long long int ait = a.find(".");
	unsigned long long int bit = b.find(".");
	bool checkDec = false;
	if (ait != a.npos)//a琌计
	{
		checkDec = true;
		if (bit == b.npos)//bぃ琌计干计翴㎝箂
		{
			b += ".";
			for (int i = 1; i < a.length() - ait; i++)
				b += "0";
		}
		//b琌计
	}
	else if (bit != b.npos)//b琌计
	{
		checkDec = true;
		if (ait == a.npos)//aぃ琌计干计翴㎝箂
		{
			a += ".";
			for (int i = 1; i < b.length() - bit; i++)
				a += "0";
		}
		//a琌计
	}

	string ans = "";
	int* numA, * numB, * numAns;//璸衡ノ皚
	unsigned long long int len;
	bool PN = true;//挡狦タ(t)璽(f)
	if (checkDec == true)//计搭
	{
		//计计干0
		ait = a.find(".");
		bit = b.find(".");
		if (a.length() - ait > b.length() - bit)//a计计ゑbb干0
		{
			unsigned long long int zero = (a.length() - ait) - (b.length() - bit);
			for (int i = 0; i < zero; i++)
				b += "0";
		}
		else if (a.length() - ait < b.length() - bit)//a计计ゑbぶa干0
		{
			unsigned long long int zero = (b.length() - bit) - (a.length() - ait);
			for (int i = 0; i < zero; i++)
				a += "0";
		}
		
		//ゑ耕a,b
		if (ait < bit)//a俱计计ゑb搭猭挡狦璽
		{
			PN = false;
			string temp = a;//3-5ユ传-(5-3)
			a = b;
			b = temp;
			unsigned long long int t = ait;
			ait = bit;
			bit = t;
		}
		else if (ait == bit)//俱计计硋计ゑ耕
		{
			bool tempCheck = false;//ゑ耕俱计
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
					string temp = a;//3-5ユ传-(5-3)
					a = b;
					b = temp;
					unsigned long long int t = ait;
					ait = bit;
					bit = t;
					break;
				}
			}
			if (PN == true && tempCheck==false)//俱计⊿ゑ耕ゑ耕计
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
						string temp = a;//3-5ユ传-(5-3)
						a = b;
						b = temp;
						unsigned long long int t = ait;
						ait = bit;
						bit = t;
						break;
					}
				}
				if (tempCheck == false)//⊿ゑ耕a=b
				{
					ans = "0.0";
					addzero(ans);
					return ans;
				}
			}
		}

		string revA(a.rbegin(), a.rend()), revB(b.rbegin(), b.rend());//﹃は锣
		 //俱计干玡竚0
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
		for (int i = 0; i < ait; i++)//﹃锣计(计场だ)
		{
			numA[i] = revA[i] - 48;
			numB[i] = revB[i] - 48;
		}
		numA[ait] = 0;//计翴竚
		numB[ait] = 0;
		for (int i = ait + 1; i < len; i++)//﹃锣计(俱计场だ)
		{
			numA[i] = revA[i] - 48;
			numB[i] = revB[i] - 48;
		}

		for (int i = 0; i < len; i++)//氮皚耴箂
			numAns[i] = 0;
		//璸衡筁祘
		int c = 0;
		for (int i = 0; i < ait; i++)//计场だ璸衡
		{
			numAns[i] = numA[i] - numB[i] - c;
			if (numAns[i] < 0)//
			{
				numAns[i] += 10;
				c = 1;
			}
			else
				c = 0;
		}
		for (int i = ait + 1; i < len; i++)//俱计场だ璸衡
		{
			numAns[i] = numA[i] - numB[i] - c;
			if (numAns[i] < 0)//
			{
				numAns[i] += 10;
				c = 1;
			}
			else
				c = 0;
		}
		while(len - 2 != ait && numAns[len - 1] == 0)//т程蔼ぃ0计玂痙俱计程ぶ计(134.1-134=000.1)
			len--;
		//挡狦锣传﹃
		if (PN == false)//挡狦琌璽计璽腹
			ans = "-";
		for (int i = len - 1; i > ait; i--)
			ans += to_string(numAns[i]);
		ans += ".";
		for (int i = ait - 1; i >= 0; i--)
			ans += to_string(numAns[i]);
		addzero(ans);
	}
	else//俱计
	{
		//ゑ耕a,b
		if (a.length() < b.length())//a计ゑb搭猭挡狦璽
		{
			PN = false;
			string temp = a;//3-5ユ传-(5-3)
			a = b;
			b = temp;
		}
		else if (a.length() == b.length())//计硋计ゑ耕
		{
			bool tempCheck = false;//ゑ耕俱计
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
					string temp = a;//3-5ユ传-(5-3)
					a = b;
					b = temp;
					break;
				}
			}
			if (PN == true && tempCheck == false)//⊿ゑ耕a=b
				return "0";
		}
		string revA(a.rbegin(), a.rend()), revB(b.rbegin(), b.rend());//﹃は锣
		 //俱计干玡竚0
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
		for (int i = 0; i < len; i++)//﹃锣计
		{
			numA[i] = revA[i] - 48;
			numB[i] = revB[i] - 48;
		}
		for (int i = 0; i < len; i++)//氮皚耴箂
			numAns[i] = 0;
		//璸衡筁祘
		int c = 0;
		for (int i = 0; i < len; i++)
		{
			numAns[i] = numA[i] - numB[i] - c;
			if (numAns[i] < 0)//秈
			{
				numAns[i] += 10;
				c = 1;
			}
			else
				c = 0;
		}
		while (len > 1 && numAns[len - 1] == 0)//т程蔼ぃ0计玂痙俱计程ぶ计(134-133=001)
			len--;
		//挡狦锣传﹃
		if (PN == false)//挡狦琌璽计璽腹
			ans = "-";
		for (int i = len - 1; i >= 0; i--)
			ans += to_string(numAns[i]);
	}
	delete[]numA;
	delete[]numB;
	delete[]numAns;
	return ans;
}
string operator *(string a, string b)
{
	bool PN = true;//挡狦タ(T)璽(F)
	//耞a.bタ璽腹
	if (a[0] == '-' && b[0] == '-')//a.b璽挡狦タ
	{
		a = a.substr(1, a.length() - 1);//璽腹
		b = b.substr(1, b.length() - 1);//璽腹
	}
	else if (a[0] == '-')//a-b+
	{
		PN = false;
		a = a.substr(1, a.length() - 1);//璽腹
	}
	else if (b[0] == '-')//a+b-
	{
		PN = false;
		b = b.substr(1, b.length() - 1);//璽腹
	}
	//Чa.b礚タ璽腹
	//耞a.b琌计┪俱计琌计碞р计翴埃魁计计
	unsigned long long int ait = a.find(".");
	unsigned long long int bit = b.find(".");
	unsigned long long int countDec = 0;
	bool checkDec = false;
	if (ait != a.npos)//a琌计
	{
		checkDec = true;
		countDec = countDec + a.length() - ait - 1;
		string temp = a.substr(ait+1,a.length()-ait-1);//计场だ
		a = a.substr(0, ait);//俱计场だ
		a.append(temp);
	}
	if (bit != b.npos)//b琌计
	{
		checkDec = true;
		countDec = countDec + b.length() - bit - 1;
		string temp = b.substr(bit + 1, b.length() - bit - 1);//计场だ
		b = b.substr(0, bit);//俱计场だ
		b.append(temp);
	}

	string ans = "";
	int* numA, * numB, * numAns;//璸衡ノ皚
	string revA(a.rbegin(), a.rend()), revB(b.rbegin(), b.rend());//﹃は锣
	unsigned long long int len = revA.length() + revB.length();
	numA = new int[revA.length()];
	numB = new int[revB.length()];
	numAns = new int[len];
	for (int i = 0; i < revA.length(); i++)//﹃锣计
		numA[i] = revA[i] - 48;

	for (int i = 0; i < revB.length(); i++)//﹃锣计
		numB[i] = revB[i] - 48;

	for (int i = 0; i < len; i++)//氮皚耴箂
		numAns[i] = 0;

	//璸衡筁祘
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
	//挡狦锣传﹃
	while (len > 1 && numAns[len - 1] == 0)//т程蔼ぃ0计玂痙俱计程ぶ计(120*5=0600)
		len--;

	if (PN == false)//挡狦琌璽计璽腹
		ans = "-";
	if (checkDec == true)//挡狦琌计计翴干
	{
		for (int i = len - 1; i > len-countDec; i--)//俱计
			ans += to_string(numAns[i]);
		ans += ".";
		for (int i = len - countDec; i >= 0; i--)//计
			ans += to_string(numAns[i]);
		addzero(ans);
	}
	else//挡狦琌俱计钡锣传﹃
	{
		for (int i = len - 1; i >= 0; i--)
			ans += to_string(numAns[i]);
	}
	delete[]numA;
	delete[]numB;
	delete[]numAns;
	return ans;
}
string operator /(string a, string b)
{
	return "0";
}
string Exponential(string a, string b)//计
{
	return "0";
}
string Factorial(string a, string b)//顶
{
	return "0";
}