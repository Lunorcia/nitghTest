#include "number.h"

void fact(unsigned long long int ansArr[], unsigned long long numA)//階乘用計算
{
    if (numA == 0) return;
    unsigned long long int c = 0;//進位
    for (int i = 40000 - 1; i >= 0; --i)//maxLen = 40000(最低位=40000-1)
    {
        ansArr[i] = ansArr[i] * numA + c;
        c = ansArr[i] / 10;
        ansArr[i] %= 10;
    }
    fact(ansArr, numA - 1);
}
string number::factorial()
{
	//進計算前先做防呆(小數不能算階乘)
	// 
	//有負號先拔掉，計算完再加回去 ex:-12! = -(12!)
	bool PN = true;//結果正(T)負(F)
	if (num[0] == '-')
	{
		PN = false;
		num = num.substr(1, num.length() - 1);//去負號
	}
	//取完無正負號
    string ans="";
    if (PN == false)
        ans += "-";
    if (num == "0")
    {
        ans += '1';
        return ans;
    }
    int maxLen = 40000;//最長位數，可調整
    unsigned long long int* ansArr = new unsigned long long int[maxLen];
    memset(ansArr, 0, maxLen * sizeof(unsigned long long int));//初始化陣列為0
    ansArr[maxLen - 1] = 1;
    unsigned long long int numA = 0;/////////////輸入大數不能超過unsigned LL
    for (int i = 0; i < num.length(); i++)//字串轉數字
        numA = numA * 10 + (num[i] - 48);
    cout <<"A=" << numA << endl;
    fact(ansArr, numA);//計算
    int checkMSB = 0;
    for (int i = 0; i < maxLen; i++) {
        if (checkMSB==0 && ansArr[i] > 0)
            checkMSB = 1;
        if (checkMSB)
            ans += to_string(ansArr[i]);
    }

    delete[]ansArr;
    return ans;
	
}