#include "number.h"

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
        for (int i = bit+1; bit < b.num.length(); i++)////�˴�b���p���I��O�_�Ҭ�0
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
    //---------------------------------------------------------------

    if (b.num == "10") {      // ���H10
 
    }



    //����a.b�L���t��
    //�P�_a.b�O�p�Ʃξ�Ƭ۰��A�O�p�ƴN��p���I�h���A�����p�Ʀ��
    unsigned long long int ait = a.num.find(".");
    unsigned long long int bit = b.num.find(".");
    unsigned long long int countDec = 0;
    bool checkDecA = false;
    bool checkDecB = false;

    bool mk = 0;//�аO'.'����m�F�S 1�w 0��
    int pointWhere;  //'.'����m


    if (bit != b.num.npos)//b�O�p�ơA�վ㦨��ƨíק�a (1.555 / 0.05 = 155.5 / 5)
    {
        checkDecB = true;
        
        string temp = b.num.substr(bit + 1, b.num.length() - bit - 1);//�p�Ƴ���
        countDec = temp.length();   
        b.num = b.num.substr(0, bit);//��Ƴ���
        b.num.append(temp);//�h���p���I��b
        while(b.num[0]=='0')//�h��b���e�m0 (005>>5)
            b.num = b.num.substr(1, b.num.length() - 1);

        if(ait != a.num.npos)//a�O�p��
        {
            string temp = a.num.substr(0, ait);//��Ƴ���
            string temp2 = a.num.substr(ait + 1, countDec);//�n���ʪ��p�Ʀ�
            a.num = a.num.substr(ait + 1 + countDec, a.num.length() - (temp.length() + temp2.length() + 1));//a�Ѿl���p�Ʀ�
            temp += temp2;//���ʧ�����Ƴ���
            temp += ".";
            temp += a.num;//���ʧ����p�Ƴ���
            a.num = temp;
            ait = a.num.find(".");//���s�O��a�p���I��m
        }
        else//a�O��ơA��0
        {
            for (int i = 0; i < countDec; i++)
                a.num += '0';
        }
    }
    if (ait != a.num.npos)//a�O�p��
    {
        checkDecA = true;
        countDec = a.num.length() - ait - 1;     ///////////////>>>>>>>�p�Ʀ�ƪ���
        string temp = a.num.substr(ait + 1, a.num.length() - ait - 1);//�p�Ƴ���
        a.num = a.num.substr(0, ait);//��Ƴ���
        a.num.append(temp);//�h���p���I��a
    }
    if (checkDecA == false)
    {
        pointWhere = a.num.length();          ///////////////////////>>>>>>>>>>�ण�ઽ����countDec���?
        mk = 1;
    }


    string ans = "";
    int* numA, * numB, * numAns;//�p��ΰ}�C
    //string revA(a.num.rbegin(), a.num.rend()), revB(b.num.rbegin(), b.num.rend());//�r�����
    unsigned long long int lena = a.num.length();
    unsigned long long int lenb = b.num.length(); //���ƪ����ס]�X��ơ^
    if(checkDecA==true)//a�O�p��
        numA = new int[a.num.length()+(100 - ait)];       ////>>>>>>>>>>>>>>a�O��ƪ��ܤ����ait(�t)
    else//a�O���
        numA = new int[a.num.length() + 100];
    numB = new int[b.num.length()];
    numAns = new int[lena+100];
    for (int i = 0; i < a.num.length(); i++)//�r����Ʀr
        numA[i] = a.num[i] - 48;
    for (int i = a.num.length(); i < a.num.length()+100 - ait; i++) //�Q���Ƹ�0�]���p���I�᪺�Ʀr�Q��)
        numA[i] = 0;

    for (int i = 0; i < b.num.length(); i++)//�r����Ʀr
        numB[i] = b.num[i] - 48;

    for (int i = 0; i < lena+100; i++)//���װ}�C�k�s
        numAns[i] = 0;

    //�p��L�{
    int c = 0;   //c=�ɦ�
    int MSD = 0;
    int j;


    for (MSD; MSD < lena - lenb; MSD++)
    {
        for (int i = MSD,int iB=0; i < lenb; i++,iB++)//�q�̰���ơ]���^���Ʀr�}�l�T�{
        {
            if (numA[i] > numB[iB])               //�p�G�̰����>���ƪ��̰���ƫh�@�w�i�H��
            {
                for (int k = lenb, j = lenb + MSD; k >= 0; j--, k--)//�q�̧C��ơ]�k�^�}�l��
                {
                    numAns[i] += 1;//i �n��
                    numA[j] = numA[j] - numB[k] - c;
                    c = 0;
                    if (numA[j] < 0)//����ܭt�Ʈɭɦ�V�e�@��ɦ�
                    {
                        numA[j] += 10;
                        c = 1;
                    }
                }
                if (mk == 0 && j == ait)//�p��
                {
                    pointWhere = j;
                    mk = 1;
                }
                i = MSD-1;                        //��A�^��̥��� ���s�ˬd//////////////////////////////////�j��i�|�A�[�@�A�U�@�Ӱj��O�qi=MSD+1�}�l�P�_�A���O�̥����H
                iB = -1;
            }
            else if (numA[i] == numB[iB])
                continue;
            else
                break;
        }
    }
    //4.20------------------------------------

    //���G�ഫ�^�r��
    while (lena > 1 && numAns[lena - 1] == 0)//��̰��줣��0���ƥB�O�d��Ƴ̤֤@���(120*5=0600)
        len--;

    if (checkDec == true)//���G�O�p�ơA�p���I�ɦ^
    {
        for (int i = 0; i < countDec; i++)//�p��
            ans += to_string(numAns[i]);
        ans += ".";
        for (int i = countDec; i < lena; i++)//���
            ans += to_string(numAns[i]);
        if (ans[ans.length() - 1] == '.')//��Ƴ�����0
            ans += "0";
        if (PN == false)//���G�O�t�ơA�t���[�^
            ans += "-";
        reverse(ans.begin(), ans.end());
        addzero(ans);
    }
    else//���G�O��ơA�����ഫ�r��
    {
        if (PN == false)//���G�O�t�ơA�t���[�^
            ans = "-";
        for (int i = lena - 1; i >= 0; i--)
            ans += to_string(numAns[i]);
    }
    delete[]numA;
    delete[]numB;
    delete[]numAns;
    return ans;
}