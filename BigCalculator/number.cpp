#include "number.h"
//////////////////////////
//////////////////////////�r��걵�n�� += �� .append(str) 
void addzero(string &num)//�p�Ƹ�0
{
	unsigned long long int it = num.find(".");
	unsigned long long int need = 100-(num.length() - it - 1);
	for (int i = 0; i < need; i++)
		num += "0";
}
string operator +(string a, string b)
{
	//�P�_a.b�O�_�O����
	if (a[0] == '-')//a�tb�t or a�tb��
	{
		a = a.substr(1, a.length() - 1);//�h�t��
		return b - a;
	}
	if (b[0] == '-')//a+b-
	{
		b = b.substr(1, b.length() - 1);//�h�t��
		return a - b;
	}
	//�P�_a.b�O�p�Ʃξ�Ƭۥ[
	unsigned long long int ait = a.find(".");
	unsigned long long int bit = b.find(".");
	bool checkDec = false;
	if (ait != a.npos)//a�O�p��
	{
		checkDec = true;
		if (bit == b.npos)//b���O�p�ơA�ɤp���I�M�s
		{
			b += ".";
			for (int i = 1; i < a.length() - ait; i++)
				b += "0";
		}
		//b�O�p��
	}
	else if (bit != b.npos)//b�O�p��
	{
		checkDec = true;
		if (ait == a.npos)//a���O�p�ơA�ɤp���I�M�s
		{
			a += ".";
			for (int i = 1; i < b.length() - bit; i++)
				a += "0";
		}
		//a�O�p��
	}

	string ans="";
	int* numA, * numB, * numAns;//�p��ΰ}�C
	unsigned long long int len;
	if (checkDec == true)//�p�Ƭۥ[
	{	//�T�{�p�Ʀ��
		ait = a.find(".");
		bit = b.find(".");
		if (a.length() - ait > b.length() - bit)//a�p�Ʀ�Ƥ�b�h�Ab��0
		{
			unsigned long long int zero = (a.length() - ait) - (b.length() - bit);
			for (int i = 0; i < zero; i++)
				b += "0";
		}
		else if (a.length() - ait < b.length() - bit)//a�p�Ʀ�Ƥ�b�֡Aa��0
		{
			unsigned long long int zero = (b.length() - bit) - (a.length() - ait);
			for (int i = 0; i < zero; i++)
				a += "0";
		}

		string revA(a.rbegin(), a.rend()),revB(b.rbegin(), b.rend());//�r�����
		 //��Ʀ�ɫe�m0
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
		for (int i = 0; i < ait; i++)//�r����Ʀr(�p�Ƴ���)
		{
			numA[i] = revA[i] - 48;
			numB[i] = revB[i] - 48;
		}
		numA[ait] = 0;//�p���I��m
		numB[ait] = 0;
		for (int i = ait + 1; i < len; i++)//�r����Ʀr(��Ƴ���)
		{
			numA[i] = revA[i] - 48;
			numB[i] = revB[i] - 48;
		}
			
		for (int i = 0; i < len + 1; i++)//���װ}�C�k�s
			numAns[i] = 0;
		//�p��L�{
		int c = 0;
		for (int i = 0; i < ait; i++)//�p�Ƴ����p��
		{
			numAns[i] = numA[i] + numB[i] + c;
			if (numAns[i] > 9)//�i��
			{
				numAns[i] -= 10;
				c = 1;
			}
			else
				c = 0;
		}
		for (int i = ait + 1; i < len; i++)//��Ƴ����p��
		{
			numAns[i] = numA[i] + numB[i] + c;
			if (numAns[i] > 9)//�i��
			{
				numAns[i] -= 10;
				c = 1;
			}
			else
				c = 0;
		}
		numAns[len] = c;//�̰���
		if (numAns[len] == 0)//�[�k���G��ƨS���W�La.b
			len--;
		//���G�ഫ�^�r��
		for (int i = len; i > ait; i--)
			ans += to_string(numAns[i]);
		ans += ".";
		for (int i = ait - 1; i >= 0; i--)
			ans += to_string(numAns[i]);
		addzero(ans);//�p�Ƹ�0
	}
	else//��Ƭۥ[
	{
		string revA(a.rbegin(), a.rend()), revB(b.rbegin(), b.rend());//�r�����
		 //��Ʀ�ɫe�m0
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
		for (int i = 0; i < len; i++)//�r����Ʀr
		{
			numA[i] = revA[i] - 48;
			numB[i] = revB[i] - 48;
		}
		for (int i = 0; i < len + 1; i++)//���װ}�C�k�s
			numAns[i] = 0;
		//�p��L�{
		int c = 0;
		for (int i = 0; i < len; i++)
		{
			numAns[i] = numA[i] + numB[i] + c;
			if (numAns[i] > 9)//�i��
			{
				numAns[i] -= 10;
				c = 1;
			}
			else
				c = 0;
		}
		numAns[len] = c;//�̰���
		if (numAns[len] == 0)//�[�k���G��ƨS���W�La.b
			len--;
		//���G�ഫ�^�r��
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
	//�P�_a.b�O�_�O����
	if (b[0] == '-')//a-(-5)=a+5
	{
		b = b.substr(1, b.length() - 1);//�h�t��
		return a + b;
	}
	if (a[0] == '-')//a�tb�� (-5)-b=-(5+b)
	{
		a = a.substr(1, a.length() - 1);//�h�t��
		string temp = a + b;
		string ans = "-";
		ans.append(temp);
		return ans;
	}
	//a.b���⥿�Ƭ۴�
	//�P�_a.b�O�p�Ʃξ��
	unsigned long long int ait = a.find(".");
	unsigned long long int bit = b.find(".");
	bool checkDec = false;
	if (ait != a.npos)//a�O�p��
	{
		checkDec = true;
		if (bit == b.npos)//b���O�p�ơA�ɤp���I�M�s
		{
			b += ".";
			for (int i = 1; i < a.length() - ait; i++)
				b += "0";
		}
		//b�O�p��
	}
	else if (bit != b.npos)//b�O�p��
	{
		checkDec = true;
		if (ait == a.npos)//a���O�p�ơA�ɤp���I�M�s
		{
			a += ".";
			for (int i = 1; i < b.length() - bit; i++)
				a += "0";
		}
		//a�O�p��
	}

	string ans = "";
	int* numA, * numB, * numAns;//�p��ΰ}�C
	unsigned long long int len;
	bool PN = true;//���G��(t)�t(f)
	if (checkDec == true)//�p�Ƭ۴�
	{
		//�p�Ʀ�ƥ���0
		ait = a.find(".");
		bit = b.find(".");
		if (a.length() - ait > b.length() - bit)//a�p�Ʀ�Ƥ�b�h�Ab��0
		{
			unsigned long long int zero = (a.length() - ait) - (b.length() - bit);
			for (int i = 0; i < zero; i++)
				b += "0";
		}
		else if (a.length() - ait < b.length() - bit)//a�p�Ʀ�Ƥ�b�֡Aa��0
		{
			unsigned long long int zero = (b.length() - bit) - (a.length() - ait);
			for (int i = 0; i < zero; i++)
				a += "0";
		}
		
		//���a,b�j�p
		if (ait < bit)//a����Ʀ�Ƥ�b�p�A��k���G���t
		{
			PN = false;
			string temp = a;//3-5�洫-(5-3)
			a = b;
			b = temp;
			unsigned long long int t = ait;
			ait = bit;
			bit = t;
		}
		else if (ait == bit)//��Ʀ�ƬۦP�A�v�Ƥ��
		{
			bool tempCheck = false;//������
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
					string temp = a;//3-5�洫-(5-3)
					a = b;
					b = temp;
					unsigned long long int t = ait;
					ait = bit;
					bit = t;
					break;
				}
			}
			if (PN == true && tempCheck==false)//��ƨS����X�j�p�A����p��
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
						string temp = a;//3-5�洫-(5-3)
						a = b;
						b = temp;
						unsigned long long int t = ait;
						ait = bit;
						bit = t;
						break;
					}
				}
				if (tempCheck == false)//�S����X�j�p�Aa=b
				{
					ans = "0.0";
					addzero(ans);
					return ans;
				}
			}
		}

		string revA(a.rbegin(), a.rend()), revB(b.rbegin(), b.rend());//�r�����
		 //��Ʀ�ɫe�m0
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
		for (int i = 0; i < ait; i++)//�r����Ʀr(�p�Ƴ���)
		{
			numA[i] = revA[i] - 48;
			numB[i] = revB[i] - 48;
		}
		numA[ait] = 0;//�p���I��m
		numB[ait] = 0;
		for (int i = ait + 1; i < len; i++)//�r����Ʀr(��Ƴ���)
		{
			numA[i] = revA[i] - 48;
			numB[i] = revB[i] - 48;
		}

		for (int i = 0; i < len; i++)//���װ}�C�k�s
			numAns[i] = 0;
		//�p��L�{
		int c = 0;
		for (int i = 0; i < ait; i++)//�p�Ƴ����p��
		{
			numAns[i] = numA[i] - numB[i] - c;
			if (numAns[i] < 0)//�ɦ�
			{
				numAns[i] += 10;
				c = 1;
			}
			else
				c = 0;
		}
		for (int i = ait + 1; i < len; i++)//��Ƴ����p��
		{
			numAns[i] = numA[i] - numB[i] - c;
			if (numAns[i] < 0)//�ɦ�
			{
				numAns[i] += 10;
				c = 1;
			}
			else
				c = 0;
		}
		while(len - 2 != ait && numAns[len - 1] == 0)//��̰��줣��0���ƥB�O�d��Ƴ̤֤@���(134.1-134=000.1)
			len--;
		//���G�ഫ�^�r��
		if (PN == false)//���G�O�t�ơA�t���[�^
			ans = "-";
		for (int i = len - 1; i > ait; i--)
			ans += to_string(numAns[i]);
		ans += ".";
		for (int i = ait - 1; i >= 0; i--)
			ans += to_string(numAns[i]);
		addzero(ans);
	}
	else//��Ƭۥ[
	{
		//���a,b�j�p
		if (a.length() < b.length())//a����Ƥ�b�p�A��k���G���t
		{
			PN = false;
			string temp = a;//3-5�洫-(5-3)
			a = b;
			b = temp;
		}
		else if (a.length() == b.length())//��ƬۦP�A�v�Ƥ��
		{
			bool tempCheck = false;//������
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
					string temp = a;//3-5�洫-(5-3)
					a = b;
					b = temp;
					break;
				}
			}
			if (PN == true && tempCheck == false)//�S����X�j�p�Aa=b
				return "0";
		}
		string revA(a.rbegin(), a.rend()), revB(b.rbegin(), b.rend());//�r�����
		 //��Ʀ�ɫe�m0
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
		if (PN == false)//���G�O�t�ơA�t���[�^
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

}
string operator /(string a, string b)
{

}
string Exponential(string a, string b)//����
{

}
string Factorial(string a, string b)//����
{

}