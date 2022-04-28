#include "number.h"
bool intIsBiggerOrEqual(string a, string b)
{
    //去除前置0
    while (b[0] == '0' && b.length() > 1 )
    {
        b = b.substr(1, b.length() - 1);
    }
    while (a[0] == '0' && a.length() > 1 )
    {
        a = a.substr(1, a.length() - 1);
    }

    if (a.length() > b.length())
        return true;
    if (a.length() < b.length())
        return false;
    //位數相同時
    for (int i = 0; i < a.length(); i++)
    {
        if (a[i] > b[i])
            return true;
        if (a[i] < b[i])
            return false;
    }
    //比較結果相同
    return true;
}

bool checkForDivide(string a, string b)
{
    //(a.num.length()>=b.num.length() && a.num!="0")
    //a的長度大於1但數字=0回傳true
    //a長度=b長度時，a>b回傳true，a<b回傳false

    //a的長度大於1但數字=0回傳true
    if(a.length()>1)
    {
        bool allZeroTF = true;
        for(int i =0; allZeroTF && i < a.length(); i++)
        {
            if(a[i]!='0')
                allZeroTF = false;
        }
        if(allZeroTF)
            return true;
    }

    // a長度=b長度時，a>b回傳true
    if (a.length() == b.length())
    {
        for(int i = 0; i < a.length(); i++)
        {
            if (a[i] > b[i])
            {
                return true;
            }
            else if (a[i] < b[i])
                return false;
        }
    }
    return false;
}

string number::subForDivide(number a, number b)//給除法用的簡化版減法
{
    //a.b為兩正整數相減，a>=b，ans>=0
    if (a.num == b.num)
        return "0";

    string ans = "";
    int* numA, * numB, * numAns;//計算用陣列
    string revA(a.num.rbegin(), a.num.rend()), revB(b.num.rbegin(), b.num.rend());//字串反轉
     //整數位補前置0
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
    for (int i = len - 1; i >= 0; i--)
        ans += to_string(numAns[i]);

    delete[]numA;
    delete[]numB;
    delete[]numAns;
    return ans;
}

string number::operator /(number K) {
    number a(num), b(K.num);
    /*if (b.num == "0") {          //除以0
        return "You cannot divide by 0!";
    }*/

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

    string ansforDOne = "";      //除以1時用的答案字串
    if (PN == false)              //負數則+負號
        ansforDOne += '-';

    unsigned long long int ait = a.num.find(".");
    unsigned long long int bit = b.num.find(".");
    if (b.num == "1")
    {          //除以1
        ansforDOne += a.num;
        if (ait != a.num.npos)//a是小數
        {
            addzero(ansforDOne);
        }
        return ansforDOne;
    }
    else if (b.num[0] == '1' && b.num[1] == '.')//b=1且b是小數
    {
        bool allZeroTF = 1;
        for (int i = bit + 1; i < b.num.length(); i++)////檢測b的小數點後是否皆為0
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
            if (ait == a.num.npos)//a不是小數
                ansforDOne += ".";
            addzero(ansforDOne);
            return ansforDOne;
        }
    }

    //取完a.b無正負號
    //判斷a.b是小數或整數相除，是小數就把小數點去除，紀錄小數位數
    ait = a.num.find(".");
    bit = b.num.find(".");
    unsigned long long int countDec = 0;
    bool checkDecA = false;
    bool checkDecB = false;
    string decA = "0";//A的小數部分

    if (bit != b.num.npos)//b是小數，調整成整數並修改a (1.555 / 0.05 = 155.5 / 5)
    {
        checkDecB = true;
        string temp = b.num.substr(bit + 1, b.num.length() - bit - 1);//小數部分
        countDec = temp.length();
        b.num = b.num.substr(0, bit);//整數部分
        b.num.append(temp);//去除小數點的b
        while (b.num[0] == '0'&&b.num.length()>1)//去除b的前置0 (005>>5)
            b.num = b.num.substr(1, b.num.length() - 1);

        if (ait != a.num.npos)//a是小數
        {
            checkDecA = true;
            addzero(a.num);//先補0避免countDec調整超過原始長度
            string temp = a.num.substr(0, ait);//整數部分
            string temp2 = a.num.substr(ait + 1, countDec);//要移動的小數位
            a.num = a.num.substr(ait + 1 + countDec, a.num.length() - (temp.length() + temp2.length() + 1));//a剩餘的小數位
            temp += temp2;//移動完的整數部分
            temp += ".";
            temp += a.num;//移動完的小數部分
            a.num = temp;
            addzero(a.num);
            ait = a.num.find(".");//重新記錄a小數點位置
        }
        else//a是整數，補0
        {
            for (int i = 0; i < countDec; i++)
                a.num += '0';
            a.num += ".0";
            addzero(a.num);
            ait = a.num.find(".");//重新記錄a小數點位置
            checkDecA = true;
        }
    }
    if (b.num == "1")
    {          //除以1
        ansforDOne += a.num;
        addzero(ansforDOne);
        return ansforDOne;
    }
    if (ait != a.num.npos)//a是小數，整數和小數拆開
    {
        checkDecA = true;
        addzero(a.num);
        decA = a.num.substr(ait + 1, a.num.length() - ait - 1);//a小數部分
        a.num = a.num.substr(0, ait);//a整數部分
    }

    string ans = "", ansDec = "";

    //計算過程
    
    //如果a(被除數)<b(除數)且a b皆為整數，則直接回傳0
    if ((ait == a.num.npos) && (bit == b.num.npos) && !(intIsBiggerOrEqual(a.num, b.num)))
        return "0";

    unsigned long long int remainLen = 0;
    while (intIsBiggerOrEqual(a.num, b.num) || checkForDivide(a.num, b.num))//直式除法，取a前位數和b做減法 
    {
        int n = 0;//一次取n位數
        string partA = "", remainA = "";
        while (intIsBiggerOrEqual(b.num, partA) && b.num != partA && n < a.num.length())//b比partA大就再取一位數(&&排除b=a時多取一位)，當partA足夠被減時結束迴圈
        {
            n++;
            partA = a.num.substr(0, n);
        }
        if(partA==a.num)//a取到結尾時
        {
            remainA = "";
            bool allZeroTF = true;
            for (int i = 0; i < partA.length(); i++)
            {
                if (partA[i] != '0')
                {
                    allZeroTF = false;
                    break;
                }
            }
            if (allZeroTF)
            {
                for (int i = 0; i < partA.length(); i++)
                    ans += '0';
                break;
            }
        }
        else
            remainA = a.num.substr(n, a.num.length() - n);
        
        //取n位-前一次迴圈餘數位數 -1(除法一次可下放一位)=多借，商要補0
        for (int i = 0; i < n - remainLen - 1; i++)
            ans += '0';
        //減法算商
        unsigned long long int quotient = 0;
        while (intIsBiggerOrEqual(partA, b.num))
        {
            number tempA(partA);
            partA = subForDivide(tempA, b);
            quotient++;
        }
        //餘數位數
        if (partA == "0")
            remainLen = 0;
        else
        {
            while (partA[0] == '0' && partA.length() > 1)//去餘數多餘的0
                partA = partA.substr(1, partA.length() - 1);
            remainLen = partA.length();
        }
        //商存入ans，修改a.num除完的數
        ans += to_string(quotient);
        a.num = partA + remainA;
        if (a.num[0] == '0' && a.num.length() > 1)//partA被整除的話去開頭0
            a.num = a.num.substr(1, a.num.length() - 1);
    }
    while (ans[0] == '0' && ans.length() > 1)//去ans開頭0(第一次迴圈商補0產生的)
        ans = ans.substr(1, ans.length() - 1);

        
    //--------------------------------------------------------------------------------------------------------------//
    //以下小數計算    
    if (checkDecA == true || checkDecB == true)//需要計算小數
    {
        if (ans == "")
            ans += "0";
        ans += ".";
        
        while (a.num[0] == '0' && a.num.length() > 1)//去a.num開頭0
            a.num = a.num.substr(1, a.num.length() - 1);
        //cout << "before add zero,ans= " << ans << endl;
        //cout << "before add zero,a.num(dec)= " << a.num << endl;

        if (a.num != "0")//a有餘數
        {
            unsigned long long int reLen = a.num.length();//餘數長度
            a.num += decA;//餘數和小數串接
            //小數商補前置0
            if (!intIsBiggerOrEqual(a.num.substr(0, b.num.length()), b.num))//被除數(b位數)小於除數
            {   //ex:(3.56/38=0.09，補1個0) (450.123/46123=0.0097，補2個0)
                for (int i = 0; i < b.num.length() - reLen; i++)
                    ansDec += "0";
            }
            else//被除數(b位數)大於等於除數
            {   //ex: 450.123/45012=0.010，補1個0(5-3-1)
                for (int i = 0; i < b.num.length() - reLen - 1; i++)
                    ansDec += "0";
            }
        }
        else//a無餘數
        {
            a.num = decA;//a的小數部分
           //小數商補前置0
            if (!intIsBiggerOrEqual(a.num.substr(0, b.num.length()), b.num))//被除數(b位數)小於除數
            {   //ex: 0.345/35=0.009，補2個0
                for (int i = 0; i < b.num.length(); i++)
                    ansDec += "0";
            }
            else//被除數(b位數)大於等於除數
            {   //ex: ex: 0.345/34=0.01，補1個0
                for (int i = 0; i < b.num.length() - 1; i++)
                    ansDec += "0";
            }
        }
        //while (a.num[0] == '0' && a.num.length() > 1)//去除前置0 (00123>>123)
            //a.num = a.num.substr(1, a.num.length() - 1);


        remainLen = 0;         
        string tempAnsDec="";///////////////////////////答案計算完再跟ansDec合併 不然去前置0會錯
        bool firstLoop = true;
        int redundantZero=0;//第一次while迴圈會在商多補0，用來記錄需要去掉幾個0
        while (intIsBiggerOrEqual(a.num, b.num) || checkForDivide(a.num, b.num))//直式除法，取a前位數和b做減法 
        {
            int n = 0;//一次取n位數
            string partA = "", remainA = "";
            while (intIsBiggerOrEqual(b.num, partA) && b.num != partA && n < a.num.length())//b比partA大就再取一位數(&&排除b=a時多取一位)，當partA足夠被減時結束迴圈
            {
                n++;
                partA = a.num.substr(0, n);
            }
            if (partA == a.num)//a取到結尾時
            {
                remainA = "";
                bool allZeroTF = true;
                for (int i = 0; i < partA.length(); i++)
                {
                    if (partA[i] != '0')
                    {
                        allZeroTF = false;
                        break;
                    }
                }
                if (allZeroTF)
                {
                    for (int i = 0; i < partA.length(); i++)
                        tempAnsDec += '0';
                    break;
                }
            }
            else
                remainA = a.num.substr(n, a.num.length() - n);
            
            if (firstLoop == true)//第一個while會在下一個for迴圈(商補0)補上不需要的0，紀錄完在離開迴圈後刪除多餘的0
            {
                redundantZero = n - remainLen;
                for (int i = 0; i < partA.length(); i++)//(0.0001/10 >> 0001/10 >> 前面000不能記錄到多餘0)
                {
                    if (partA[i] == '0')
                        redundantZero--;
                    else
                        break;
                }
                firstLoop = false;
            }
            //取n位-前一次迴圈餘數位數 -1(除法一次可下放一位)=多借，商要補0
            for (int i = 0; i < n - remainLen - 1; i++)
                tempAnsDec += '0';
            //減法算商
            unsigned long long int quotient = 0;
            while (intIsBiggerOrEqual(partA, b.num))
            {
                number tempA(partA);
                partA = subForDivide(tempA, b);
                quotient++;
            }
            //餘數位數

            if (partA == "0")
                remainLen = 0;
            else
            {
                while (partA[0] == '0' && partA.length() > 1)//去餘數多餘的0
                    partA = partA.substr(1, partA.length() - 1);
                remainLen = partA.length();
            }

            //商存入ans，修改a.num除完的數
            tempAnsDec += to_string(quotient);
            a.num = partA + remainA;
            if (a.num[0] == '0' && a.num.length() > 1)//partA被整除的話去開頭0
                a.num = a.num.substr(1, a.num.length() - 1);
        }

        for (int i = 0; i < redundantZero && tempAnsDec[0] == '0'; i++)//去tempAnsDec開頭0(第一次迴圈商補0產生的)
            tempAnsDec = tempAnsDec.substr(1, tempAnsDec.length() - 1);

        ansDec += tempAnsDec;//前置0和計算結果合併
       
        ans += ansDec;
    }
    if (PN == false)
    {
        string temp = "-";
        temp += ans;
        ans = temp;
    }
    return ans;
}