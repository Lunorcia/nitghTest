#include "number.h"
bool intIsBiggerOrEqual(string a, string b)
{
    if (a.length() > b.length())
        return true;
    if (a.length() < b.length())
        return false;
    //��ƬۦP��
    for (int i = 0; i < a.length(); i++)
    {
        if (a[i] > b[i])
            return true;
        if (a[i] < b[i])
            return false;
    }
    //������G�ۦP
    return true;
}

string number::subForDivide(number a, number b)//�����k�Ϊ�²�ƪ���k
{
	//a.b���⥿��Ƭ۴�Aa>=b�Aans>=0
    if (a.num == b.num)
        return "0";

	string ans = "";
	int* numA, * numB, * numAns;//�p��ΰ}�C
    string revA(a.num.rbegin(), a.num.rend()), revB(b.num.rbegin(), b.num.rend());//�r�����
     //��Ʀ�ɫe�m0
    if (revA.length() > revB.length())
    {
        int L = revA.length() - revB.length();
        for (int i = 0; i < L; i++)
            revB += "0";
    }

    unsigned long long int len = revA.length();
    numA = new int[len];
    numB = new int[len];
    numAns = new int[len];
    for (int i = 0; i < len; i++)//�r����Ʀr
    {
        numA[i] = revA[i] - 48;
        numB[i] = revB[i] - 48;
    }
    for (int i = 0; i < len; i++)//���װ}�C�k�s
        numAns[i] = 0;
    //�p��L�{
    int c = 0;
    for (int i = 0; i < len; i++)
    {
        numAns[i] = numA[i] - numB[i] - c;
        if (numAns[i] < 0)//�i��
        {
            numAns[i] += 10;
            c = 1;
        }
        else
            c = 0;
    }
    while (len > 1 && numAns[len - 1] == 0)//��̰��줣��0���ƥB�O�d��Ƴ̤֤@���(134-133=001)
        len--;
    //���G�ഫ�^�r��
    for (int i = len - 1; i >= 0; i--)
        ans += to_string(numAns[i]);

	delete[]numA;
	delete[]numB;
	delete[]numAns;
	return ans;
}

string number::operator /(number K) {
    number a(num), b(K.num);
    /*if (b.num == "0") {          //���H0
        return "You cannot divide by 0!";
    }*/

    bool PN = true;//���G��(T)�t(F)
    //�P�_a.b���t��
    if (a.num[0] == '-' && b.num[0] == '-')//a.b�t�A���G����
    {
        a.num = a.num.substr(1, a.num.length() - 1);//�h�t��
        b.num = b.num.substr(1, b.num.length() - 1);//�h�t��
    }
    else if (a.num[0] == '-')//a-b+
    {
        PN = false;
        a.num = a.num.substr(1, a.num.length() - 1);//�h�t��
    }
    else if (b.num[0] == '-')//a+b-
    {
        PN = false;
        b.num = b.num.substr(1, b.num.length() - 1);//�h�t��
    }

    string ansforDOne = "";      //���H1�ɥΪ����צr��
    if (PN == false)              //�t�ƫh+�t��
        ansforDOne += '-';

    unsigned long long int ait = a.num.find(".");
    unsigned long long int bit = b.num.find(".");
    if (b.num == "1")
    {          //���H1
        ansforDOne += a.num;
        if (ait != a.num.npos)//a�O�p��
        {
            addzero(ansforDOne += a.num);
        }
        return ansforDOne;
    }
    else if (b.num[0] == '1' && b.num[1] == '.')//b=1�Bb�O�p��
    {
        bool allZeroTF = 1;
        for (int i = bit + 1; bit < b.num.length(); i++)////�˴�b���p���I��O�_�Ҭ�0
        {
            if (b.num[i] != '0')
            {
                allZeroTF = 0;
                break;
            }
        }
        if (allZeroTF == 1)
        {
            ansforDOne += a.num;
            if (ait == a.num.npos)//a���O�p��
                ansforDOne += ".";
            addzero(ansforDOne);
            return ansforDOne;
        }
    }

    //����a.b�L���t��
    //�P�_a.b�O�p�Ʃξ�Ƭ۰��A�O�p�ƴN��p���I�h���A�����p�Ʀ��
    ait = a.num.find(".");
    bit = b.num.find(".");
    unsigned long long int countDec = 0;
    bool checkDecA = false;
    bool checkDecB = false;
    string decA = "0";//A���p�Ƴ���

    if (bit != b.num.npos)//b�O�p�ơA�վ㦨��ƨíק�a (1.555 / 0.05 = 155.5 / 5)
    {
        checkDecB = true;

        string temp = b.num.substr(bit + 1, b.num.length() - bit - 1);//�p�Ƴ���
        countDec = temp.length();
        b.num = b.num.substr(0, bit);//��Ƴ���
        b.num.append(temp);//�h���p���I��b
        while (b.num[0] == '0')//�h��b���e�m0 (005>>5)
            b.num = b.num.substr(1, b.num.length() - 1);

        if (ait != a.num.npos)//a�O�p��
        {
            addzero(a.num);//����0�קKcountDec�վ�W�L��l����
            string temp = a.num.substr(0, ait);//��Ƴ���
            string temp2 = a.num.substr(ait + 1, countDec);//�n���ʪ��p�Ʀ�
            a.num = a.num.substr(ait + 1 + countDec, a.num.length() - (temp.length() + temp2.length() + 1));//a�Ѿl���p�Ʀ�
            temp += temp2;//���ʧ�����Ƴ���
            temp += ".";
            temp += a.num;//���ʧ����p�Ƴ���
            a.num = temp;
            addzero(a.num);
            ait = a.num.find(".");//���s�O��a�p���I��m
        }
        else//a�O��ơA��0
        {
            for (int i = 0; i < countDec; i++)
                a.num += '0';
        }
    }
    if (ait != a.num.npos)//a�O�p�ơA��ƩM�p�Ʃ�}
    {
        checkDecA = true;
        decA = a.num.substr(ait + 1, a.num.length() - ait - 1);//a�p�Ƴ���
        a.num = a.num.substr(0, ait);//a��Ƴ���
    }

    string ans = "", ansDec = "";
    int* numAnsInt, * numAnsDec;//�p��ΰ}�C
    //string revA(a.num.rbegin(), a.num.rend()), revB(b.num.rbegin(), b.num.rend());//�r�����
    unsigned long long int lena = a.num.length();
    unsigned long long int lenb = b.num.length(); //���ƪ����ס]�X��ơ^

    numAnsInt = new int[a.num.length()];
    numAnsDec = new int[100];

    for (int i = 0; i < a.num.length(); i++)//��Ƶ��װ}�C�k�s
        numAnsInt[i] = 0;
    for (int i = 0; i < 100; i++)//�p�Ƶ��װ}�C�k�s
        numAnsDec[i] = 0;

    //�p��L�{
    unsigned long long int ansLen = 1;//ans��Ʀ�ƪ���
    while (intIsBiggerOrEqual(a.num, b.num))//�Q���Ƥj�󵥩󰣼�
    {
        a.num = subForDivide(a, b);//���k�Ϊ�²�ƪ���k
        //AnsInt�����x�s
        numAnsInt[0]++;
        if (numAnsInt[0]>9)//ans�i��
        {
            for (int i = 0; i < ansLen; i++)
            {
                if (numAnsInt[i] > 9)
                {
                    if (numAnsInt[i + 1] == 0)
                        ansLen++;
                    numAnsInt[i] -= 10;
                    numAnsInt[i + 1]++;
                }
                else //�᭱���|�A�i��
                    break;
            }
        }
    }
    //numAnsInt�x�s�ians
    for (int i = ansLen - 1; i >= 0; i--)
    {
        ans += to_string(numAnsInt[i]);
    }
    if (checkDecA == true || checkDecB == true)//�ݭn�p��p��
    {
        ans += ".";
        if (a.num != "0")//a���l��
        {
            unsigned long long int remainLen = a.num.length();//�l�ƪ���
            a.num += decA;//�l�ƩM�p�Ʀ걵
            //�p�ưӸɫe�m0
            if (!intIsBiggerOrEqual(a.num.substr(0, b.num.length()), b.num))//�Q����(b���)�p�󰣼�
            {   //ex:(3.56/38=0.09�A��1��0) (450.123/46123=0.0097�A��2��0)
                for (int i = 0; i < b.num.length() - remainLen; i++)
                    ansDec += "0";
            }
            else//�Q����(b���)�j�󵥩󰣼�
            {   //ex: 450.123/45012=0.010�A��1��0(5-3-1)
                for (int i = 0; i < b.num.length() - remainLen - 1; i++)
                    ansDec += "0";
            }
        }
        else//a�L�l��
        {
            a.num = decA;//a���p�Ƴ���
           //�p�ưӸɫe�m0
            if (!intIsBiggerOrEqual(a.num.substr(0, b.num.length()), b.num))//�Q����(b���)�p�󰣼�
            {   //ex: 0.345/35=0.009�A��2��0
                for (int i = 0; i < b.num.length(); i++)
                    ansDec += "0";
            }
            else//�Q����(b���)�j�󵥩󰣼�
            {   //ex: ex: 0.345/34=0.01�A��1��0
                for (int i = 0; i < b.num.length() - 1; i++)
                    ansDec += "0";
            }
        }
        while(a.num[0]=='0'&&a.num.length()>1)//�h���e�m0 (00123>>123)
            a.num = a.num.substr(1, a.num.length() - 1);

        unsigned long long int ansDecLen = 1;//ans�p�Ʀ�ƪ���
        while (intIsBiggerOrEqual(a.num, b.num))//�Q���Ƥj�󵥩󰣼�
        {
            a.num = subForDivide(a, b);//���k�Ϊ�²�ƪ���k
            //numAnsDec�����x�s
            numAnsDec[0]++;
            if (numAnsDec[0] > 9)//ans�i��
            {
                
                for (int i = 0; i < ansDecLen; i++)
                {
                    if (numAnsDec[i] > 9)
                    {
                        if(numAnsDec[i + 1]==0)
                            ansDecLen++;
                        numAnsDec[i] -= 10;
                        numAnsDec[i + 1]++;
                    }
                    else //�᭱���|�A�i��
                        break;
                }
            }
        }
        //numAnsDec�x�s�iansDec(�u�s100��)
        for (int i = ansDecLen - 1; i >= 0 && ansDec.length() < 100; i--)
        {
            ansDec += to_string(numAnsDec[i]);
        }
        ans += ansDec;
    }
    if (PN == false)
    {
        string temp = "-";
        temp += ans;
        ans = temp;
    }

    delete[]numAnsInt;
    delete[]numAnsDec;
    return ans;
}