#include "number.h"

void fact(unsigned long long int ansArr[], unsigned long long numA)//�����έp��
{
    if (numA == 0) return;
    unsigned long long int c = 0;//�i��
    for (int i = 40000 - 1; i >= 0; --i)//maxLen = 40000(�̧C��=40000-1)
    {
        ansArr[i] = ansArr[i] * numA + c;
        c = ansArr[i] / 10;
        ansArr[i] %= 10;
    }
    fact(ansArr, numA - 1);
}
string number::factorial()
{
	//�i�p��e�������b(�p�Ƥ���ⶥ��)
	// 
	//���t�����ޱ��A�p�⧹�A�[�^�h ex:-12! = -(12!)
	bool PN = true;//���G��(T)�t(F)
	if (num[0] == '-')
	{
		PN = false;
		num = num.substr(1, num.length() - 1);//�h�t��
	}
	//�����L���t��
    string ans="";
    if (PN == false)
        ans += "-";
    if (num == "0")
    {
        ans += '1';
        return ans;
    }
    int maxLen = 40000;//�̪���ơA�i�վ�
    unsigned long long int* ansArr = new unsigned long long int[maxLen];
    memset(ansArr, 0, maxLen * sizeof(unsigned long long int));//��l�ư}�C��0
    ansArr[maxLen - 1] = 1;
    unsigned long long int numA = 0;/////////////��J�j�Ƥ���W�Lunsigned LL
    for (int i = 0; i < num.length(); i++)//�r����Ʀr
        numA = numA * 10 + (num[i] - 48);
    cout <<"A=" << numA << endl;
    fact(ansArr, numA);//�p��
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