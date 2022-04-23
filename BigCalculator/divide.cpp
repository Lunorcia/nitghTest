#include "number.h"
bool intIsBiggerOrEqual(string a, string b)
{
    if (a.length() > b.length())
        return true;
    if (a.length() < b.length())
        return false;
    //计
    for (int i = 0; i < a.length(); i++)
    {
        if (a[i] > b[i])
            return true;
        if (a[i] < b[i])
            return false;
    }
    //ゑ耕挡狦
    return true;
}

string number::subForDivide(number a, number b)//倒埃猭ノ虏て搭猭
{
	//a.bㄢタ俱计搭a>=bans>=0
    if (a.num == b.num)
        return "0";

	string ans = "";
	int* numA, * numB, * numAns;//璸衡ノ皚
    string revA(a.num.rbegin(), a.num.rend()), revB(b.num.rbegin(), b.num.rend());//﹃は锣
     //俱计干玡竚0
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
    for (int i = len - 1; i >= 0; i--)
        ans += to_string(numAns[i]);

	delete[]numA;
	delete[]numB;
	delete[]numAns;
	return ans;
}

string number::operator /(number K) {
    number a(num), b(K.num);
    /*if (b.num == "0") {          //埃0
        return "You cannot divide by 0!";
    }*/

    bool PN = true;//挡狦タ(T)璽(F)
    //耞a.bタ璽腹
    if (a.num[0] == '-' && b.num[0] == '-')//a.b璽挡狦タ
    {
        a.num = a.num.substr(1, a.num.length() - 1);//璽腹
        b.num = b.num.substr(1, b.num.length() - 1);//璽腹
    }
    else if (a.num[0] == '-')//a-b+
    {
        PN = false;
        a.num = a.num.substr(1, a.num.length() - 1);//璽腹
    }
    else if (b.num[0] == '-')//a+b-
    {
        PN = false;
        b.num = b.num.substr(1, b.num.length() - 1);//璽腹
    }

    string ansforDOne = "";      //埃1ノ氮﹃
    if (PN == false)              //璽计玥+璽腹
        ansforDOne += '-';

    unsigned long long int ait = a.num.find(".");
    unsigned long long int bit = b.num.find(".");
    if (b.num == "1")
    {          //埃1
        ansforDOne += a.num;
        if (ait != a.num.npos)//a琌计
        {
            addzero(ansforDOne += a.num);
        }
        return ansforDOne;
    }
    else if (b.num[0] == '1' && b.num[1] == '.')//b=1b琌计
    {
        bool allZeroTF = 1;
        for (int i = bit + 1; bit < b.num.length(); i++)////浪代b计翴琌0
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
            if (ait == a.num.npos)//aぃ琌计
                ansforDOne += ".";
            addzero(ansforDOne);
            return ansforDOne;
        }
    }

    //Чa.b礚タ璽腹
    //耞a.b琌计┪俱计埃琌计碞р计翴埃魁计计
    ait = a.num.find(".");
    bit = b.num.find(".");
    unsigned long long int countDec = 0;
    bool checkDecA = false;
    bool checkDecB = false;
    string decA = "0";//A计场だ

    if (bit != b.num.npos)//b琌计秸俱Θ俱计эa (1.555 / 0.05 = 155.5 / 5)
    {
        checkDecB = true;

        string temp = b.num.substr(bit + 1, b.num.length() - bit - 1);//计场だ
        countDec = temp.length();
        b.num = b.num.substr(0, bit);//俱计场だ
        b.num.append(temp);//埃计翴b
        while (b.num[0] == '0')//埃b玡竚0 (005>>5)
            b.num = b.num.substr(1, b.num.length() - 1);

        if (ait != a.num.npos)//a琌计
        {
            addzero(a.num);//干0磷countDec秸俱禬筁﹍
            string temp = a.num.substr(0, ait);//俱计场だ
            string temp2 = a.num.substr(ait + 1, countDec);//璶簿笆计
            a.num = a.num.substr(ait + 1 + countDec, a.num.length() - (temp.length() + temp2.length() + 1));//a逞緇计
            temp += temp2;//簿笆Ч俱计场だ
            temp += ".";
            temp += a.num;//簿笆Ч计场だ
            a.num = temp;
            addzero(a.num);
            ait = a.num.find(".");//穝癘魁a计翴竚
        }
        else//a琌俱计干0
        {
            for (int i = 0; i < countDec; i++)
                a.num += '0';
        }
    }
    if (ait != a.num.npos)//a琌计俱计㎝计╊秨
    {
        checkDecA = true;
        decA = a.num.substr(ait + 1, a.num.length() - ait - 1);//a计场だ
        a.num = a.num.substr(0, ait);//a俱计场だ
    }

    string ans = "", ansDec = "";
    int* numAnsInt, * numAnsDec;//璸衡ノ皚
    //string revA(a.num.rbegin(), a.num.rend()), revB(b.num.rbegin(), b.num.rend());//﹃は锣
    unsigned long long int lena = a.num.length();
    unsigned long long int lenb = b.num.length(); //埃计碭计

    numAnsInt = new int[a.num.length()];
    numAnsDec = new int[100];

    for (int i = 0; i < a.num.length(); i++)//俱计氮皚耴箂
        numAnsInt[i] = 0;
    for (int i = 0; i < 100; i++)//计氮皚耴箂
        numAnsDec[i] = 0;

    //璸衡筁祘
    unsigned long long int ansLen = 1;//ans俱计计
    while (intIsBiggerOrEqual(a.num, b.num))//砆埃计单埃计
    {
        a.num = subForDivide(a, b);//埃猭ノ虏て搭猭
        //AnsInt氮纗
        numAnsInt[0]++;
        if (numAnsInt[0]>9)//ans秈
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
                else //ぃ穦秈
                    break;
            }
        }
    }
    //numAnsInt纗秈ans
    for (int i = ansLen - 1; i >= 0; i--)
    {
        ans += to_string(numAnsInt[i]);
    }
    if (checkDecA == true || checkDecB == true)//惠璶璸衡计
    {
        ans += ".";
        if (a.num != "0")//aΤ緇计
        {
            unsigned long long int remainLen = a.num.length();//緇计
            a.num += decA;//緇计㎝计﹃钡
            //计坝干玡竚0
            if (!intIsBiggerOrEqual(a.num.substr(0, b.num.length()), b.num))//砆埃计(b计)埃计
            {   //ex:(3.56/38=0.09干10) (450.123/46123=0.0097干20)
                for (int i = 0; i < b.num.length() - remainLen; i++)
                    ansDec += "0";
            }
            else//砆埃计(b计)单埃计
            {   //ex: 450.123/45012=0.010干10(5-3-1)
                for (int i = 0; i < b.num.length() - remainLen - 1; i++)
                    ansDec += "0";
            }
        }
        else//a礚緇计
        {
            a.num = decA;//a计场だ
           //计坝干玡竚0
            if (!intIsBiggerOrEqual(a.num.substr(0, b.num.length()), b.num))//砆埃计(b计)埃计
            {   //ex: 0.345/35=0.009干20
                for (int i = 0; i < b.num.length(); i++)
                    ansDec += "0";
            }
            else//砆埃计(b计)单埃计
            {   //ex: ex: 0.345/34=0.01干10
                for (int i = 0; i < b.num.length() - 1; i++)
                    ansDec += "0";
            }
        }
        while(a.num[0]=='0'&&a.num.length()>1)//埃玡竚0 (00123>>123)
            a.num = a.num.substr(1, a.num.length() - 1);

        unsigned long long int ansDecLen = 1;//ans计计
        while (intIsBiggerOrEqual(a.num, b.num))//砆埃计单埃计
        {
            a.num = subForDivide(a, b);//埃猭ノ虏て搭猭
            //numAnsDec氮纗
            numAnsDec[0]++;
            if (numAnsDec[0] > 9)//ans秈
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
                    else //ぃ穦秈
                        break;
                }
            }
        }
        //numAnsDec纗秈ansDec(100)
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