//divide
/*unsigned long long int ansLen = 1;//ans��Ʀ�ƪ���
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
                if (numAnsInt[ansLen] == 0 && i + 1 == ansLen)
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
}*/