#include "number.h"

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
    //---------------------------------------------------------------

    if (b.num == "10") {      // 埃10

    }



    //Чa.b礚タ璽腹
    //耞a.b琌计┪俱计埃琌计碞р计翴埃魁计计
    unsigned long long int ait = a.num.find(".");
    unsigned long long int bit = b.num.find(".");
    unsigned long long int countDec = 0;
    bool checkDecA = false;
    bool checkDecB = false;
    string decA;//A计

   // bool mk = 0;//夹癘'.'竚⊿ 1 0ゼ
   // int pointWhere;  //'.'竚


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
            string temp = a.num.substr(0, ait);//俱计场だ
            string temp2 = a.num.substr(ait + 1, countDec);//璶簿笆计
            a.num = a.num.substr(ait + 1 + countDec, a.num.length() - (temp.length() + temp2.length() + 1));//a逞緇计
            temp += temp2;//簿笆Ч俱计场だ
            temp += ".";
            temp += a.num;//簿笆Ч计场だ
            a.num = temp;
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
       // countDec = a.num.length() - ait - 1;     ///////////////>>>>>>>计计
        decA = a.num.substr(ait + 1, a.num.length() - ait - 1);//////////////////a计场だ
        a.num = a.num.substr(0, ait);//a俱计场だ
       // a.num.append(temp);//埃计翴a
    }

    string ans = "";
    int* numAnsInt, * numAnsDec;//璸衡ノ皚
    //string revA(a.num.rbegin(), a.num.rend()), revB(b.num.rbegin(), b.num.rend());//﹃は锣
    unsigned long long int lena = a.num.length();
    unsigned long long int lenb = b.num.length(); //埃计碭计
    if (checkDecA == true)//a琌计
    {
        numIntA = new int[a.num.length()];
        numDecA = new int[decA.length()];
        for (int i = 0; i < decA.length(); i++)//计氮皚耴箂
            numAnsDec[i] = 0;
        
    }   
    else//a琌俱计
    {
        numIntA = new int[a.num.length()];
        numDecA = new int[1];
    }
    numB = new int[b.num.length()];
    numAnsInt = new int[a.num.length()];
    numAnsDec = new int[100];

   /* for (int i = 0; i < a.num.length(); i++)//a俱计﹃锣计
        numIntA[i] = a.num[i] - 48;
    for (int i = 0; i < decA.length(); i++)//a计﹃锣计
        numDecA[i] = decA[i] - 48;
    for (int i = 0; i < b.num.length(); i++)//b﹃锣计
        numB[i] = b.num[i] - 48;*/
    for (int i = 0; i < a.num.length(); i++)//俱计氮皚耴箂
        numAnsInt[i] = 0;

    //璸衡筁祘

    while (a.num >= b.num)//计﹃ゑ耕糶
    {
        string sub = a - b;
        a.num = sub;
        //AnsInt氮纗
    }








    //4.20------------------------------------

    //挡狦锣传﹃
    while (lena > 1 && numAns[lena - 1] == 0)//т程蔼ぃ0计玂痙俱计程ぶ计(120*5=0600)
        len--;

    if (checkDec == true)//挡狦琌计计翴干
    {
        for (int i = 0; i < countDec; i++)//计
            ans += to_string(numAns[i]);
        ans += ".";
        for (int i = countDec; i < lena; i++)//俱计
            ans += to_string(numAns[i]);
        if (ans[ans.length() - 1] == '.')//俱计场だ0
            ans += "0";
        if (PN == false)//挡狦琌璽计璽腹
            ans += "-";
        reverse(ans.begin(), ans.end());
        addzero(ans);
    }
    else//挡狦琌俱计钡锣传﹃
    {
        if (PN == false)//挡狦琌璽计璽腹
            ans = "-";
        for (int i = lena - 1; i >= 0; i--)
            ans += to_string(numAns[i]);
    }
    delete[]numA;
    delete[]numB;
    delete[]numAns;
    return ans;
}