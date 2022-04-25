//divide
/*unsigned long long int ansLen = 1;//ans整數位數長度
while (intIsBiggerOrEqual(a.num, b.num))//被除數大於等於除數
{
    a.num = subForDivide(a, b);//除法用的簡化版減法
    //AnsInt答案儲存
    numAnsInt[0]++;
    if (numAnsInt[0]>9)//ans進位
    {
        for (int i = 0; i < ansLen; i++)
        {
            if (numAnsInt[i] > 9)
            {
                if (numAnsInt[ansLen] == 0 && i + 1 == ansLen)
                    ansLen++;
                numAnsInt[i] -= 10;
                numAnsInt[i + 1]++;
            }
            else //後面不會再進位
                break;
        }
    }
}
//numAnsInt儲存進ans
for (int i = ansLen - 1; i >= 0; i--)
{
    ans += to_string(numAnsInt[i]);
}*/