#include "number.h"
//////////////////////////
//////////////////////////�r��걵�n�� += �� .append(str) 

void addzero(string &n)//�p�Ƹ�0
{
	unsigned long long int it = n.find(".");
	if (it != n.npos)
	{
		long long int need = 100 - (n.length() - it - 1);
		for (int i = 0; i < need; i++)
			n += "0";
	}
}
bool isSquareRoot(number K)/*��O�O�_��0.5����ƭ�*/
{ 
	string tmp = K * number("2"); /*�NK���H2�A�i��K�O���O0.5����ƭ��A�u�n���G���O��ơA�^��false*/
	int decimalPoint = -1;
	for (int i = 0; i < tmp.length(); i++) 
	{
		if (tmp[i] == '.') 
		{
			decimalPoint = i;
		}
	}
	if (decimalPoint == -1) 
	{
		return true;
	}
	else if (decimalPoint != -1)
	{
		for (int i = decimalPoint + 1; i < tmp.length(); i++) 
		{
			if (tmp[i] != '0')
			{
				return false;
			}
		}
		return true;
	}
}
string number::operator +(number K)
{
	//�P�_a.b�O�_�O����
	number a(num), b(K.num);
	if (a.num[0] == '-')//a�tb�t or a�tb��
	{
		a.num = a.num.substr(1, a.num.length() - 1);//�h�t��
		    
		return b - a;
	}
	if (b.num[0] == '-')//a+b-
	{
		b.num = b.num.substr(1, b.num.length() - 1);//�h�t��
		
		
		return a - b;
	}
	//�P�_a.b�O�p�Ʃξ�Ƭۥ[
	unsigned long long int ait = a.num.find(".");
	unsigned long long int bit = b.num.find(".");
	bool checkDec = false;
	if (ait != a.num.npos)//a�O�p��
	{
		checkDec = true;
		if (bit == b.num.npos)//b���O�p�ơA�ɤp���I�M�s
		{
			b.num += ".";
			for (int i = 1; i < a.num.length() - ait; i++)
				b.num += "0";
		}
		//b�O�p��
	}
	else if (bit != b.num.npos)//b�O�p��
	{
		checkDec = true;
		if (ait == a.num.npos)//a���O�p�ơA�ɤp���I�M�s
		{
			a.num += ".";
			for (int i = 1; i < b.num.length() - bit; i++)
				a.num += "0";
		}
		//a�O�p��
	}

	string ans = "";
	int* numA, * numB, * numAns;//�p��ΰ}�C
	unsigned long long int len;
	if (checkDec == true)//�p�Ƭۥ[
	{	//�T�{�p�Ʀ��
		ait = a.num.find(".");
		bit = b.num.find(".");
		if (a.num.length() - ait > b.num.length() - bit)//a�p�Ʀ�Ƥ�b�h�Ab��0
		{
			unsigned long long int zero = (a.num.length() - ait) - (b.num.length() - bit);
			for (int i = 0; i < zero; i++)
				b.num += "0";
		}
		else if (a.num.length() - ait < b.num.length() - bit)//a�p�Ʀ�Ƥ�b�֡Aa��0
		{
			unsigned long long int zero = (b.num.length() - bit) - (a.num.length() - ait);
			for (int i = 0; i < zero; i++)
				a.num += "0";
		}

		string revA(a.num.rbegin(), a.num.rend()), revB(b.num.rbegin(), b.num.rend());//�r�����
		 //��Ʀ�ɫe�m0
		if (revA.length() > revB.length())
		{
			int L = revA.length() - revB.length();
			for (int i = 0; i < L; i++)
				revB += "0";
		}
		else if (revA.length() < revB.length())
		{
			int L = revB.length() - revA.length();
			for (int i = 0; i < L; i++)
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
		string revA(a.num.rbegin(), a.num.rend()), revB(b.num.rbegin(), b.num.rend());//�r�����
		 //��Ʀ�ɫe�m0
		if (revA.length() > revB.length())
		{
			int L = revA.length() - revB.length();
			for (int i = 0; i < L; i++)
			{
				revB += "0";
			}
				
		}
		else if (revA.length() < revB.length())
		{
			int L = revB.length() - revA.length();
			for (int i = 0; i < L; i++)
			{
				revA += "0";
			}
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
};

string number::operator -(number K)
{
	number a(num), b(K.num);
//�P�_a.b�O�_�O����
	if (b.num[0] == '-')//a-(-5)=a+5
	{
		b.num = b.num.substr(1, b.num.length() - 1);//�h�t��
		//number tmp1(num),tmp2(b.num);
		return a + b;
	}
	if (a.num[0] == '-')//a�tb�� (-5)-b=-(5+b)
	{
		a.num = a.num.substr(1, a.num.length() - 1);//�h�t��
		//number tmp1(num),tmp2(b.num);
		string temp = a + b;
		string ans = "-";
		ans.append(temp);
		return ans;
	}
	//a.b���⥿�Ƭ۴�
	//�P�_a.b�O�p�Ʃξ��
	unsigned long long int ait = a.num.find(".");
	unsigned long long int bit = b.num.find(".");
	bool checkDec = false;
	if (ait != a.num.npos)//a�O�p��
	{
		checkDec = true;
		if (bit == b.num.npos)//b���O�p�ơA�ɤp���I�M�s
		{
			b.num += ".";
			for (int i = 1; i < a.num.length() - ait; i++)
				b.num += "0";
		}
		//b�O�p��
	}
	else if (bit != b.num.npos)//b�O�p��
	{
		checkDec = true;
		if (ait == a.num.npos)//a���O�p�ơA�ɤp���I�M�s
		{
			a.num += ".";
			for (int i = 1; i < b.num.length() - bit; i++)
				a.num += "0";
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
		ait = a.num.find(".");
		bit = b.num.find(".");
		if (a.num.length() - ait > b.num.length() - bit)//a�p�Ʀ�Ƥ�b�h�Ab��0
		{
			unsigned long long int zero = (a.num.length() - ait) - (b.num.length() - bit);
			for (int i = 0; i < zero; i++)
				b.num += "0";
		}
		else if (a.num.length() - ait < b.num.length() - bit)//a�p�Ʀ�Ƥ�b�֡Aa��0
		{
			unsigned long long int zero = (b.num.length() - bit) - (a.num.length() - ait);
			for (int i = 0; i < zero; i++)
				a.num += "0";
		}
		
		//���a,b�j�p
		if (ait < bit)//a����Ʀ�Ƥ�b�p�A��k���G���t
		{
			PN = false;
			string temp = a.num;//3-5�洫-(5-3)
			a.num = b.num;
			b.num = temp;
			unsigned long long int t = ait;
			ait = bit;
			bit = t;
		}
		else if (ait == bit)//��Ʀ�ƬۦP�A�v�Ƥ��
		{
			bool tempCheck = false;//������
			for (int i = 0; i < ait; i++)
			{
				if (a.num[i] > b.num[i])
				{
					tempCheck = true;
					break;
				}
				if (a.num[i] < b.num[i])
				{
					PN = false;
					string temp = a.num;//3-5�洫-(5-3)
					a.num = b.num;
					b.num = temp;
					unsigned long long int t = ait;
					ait = bit;
					bit = t;
				}
			}
			if (PN == true && tempCheck==false)//��ƨS����X�j�p�A����p��
			{
				for (int i = ait + 1; i < a.num.length(); i++)
				{
					if (a.num[i] > b.num[i])
					{
						tempCheck = true;
						break;
					}
					if (a.num[i] < b.num[i])
					{
						tempCheck = true;
						PN = false;
						string temp = a.num;//3-5�洫-(5-3)
						a.num = b.num;
						b.num = temp;
						unsigned long long int t = ait;
						ait = bit;
						bit = t;
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

		string revA(a.num.rbegin(), a.num.rend()), revB(b.num.rbegin(), b.num.rend());//�r�����
		 //��Ʀ�ɫe�m0
		if (revA.length() > revB.length())
		{
			int L = revA.length() - revB.length();
			for (int i = 0; i < L; i++)
				revB += "0";
		}
		else if (revA.length() < revB.length())
		{
			int L = revB.length() - revA.length();
			for (int i = 0; i < L; i++)
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
	else//��Ƭ۴�
	{
		//���a,b�j�p
		if (a.num.length() < b.num.length())//a����Ƥ�b�p�A��k���G���t
		{
			PN = false;
			string temp = a.num;//3-5�洫-(5-3)
			a.num = b.num;
			b.num = temp;
		}
		else if (a.num.length() == b.num.length())//��ƬۦP�A�v�Ƥ��
		{
			bool tempCheck = false;//������
			for (int i = 0; i < a.num.length(); i++)
			{
				if (a.num[i] > b.num[i])
				{
					tempCheck = true;
					break;
				}
				if (a.num[i] < b.num[i])
				{
					PN = false;
					string temp = a.num;//3-5�洫-(5-3)
					a.num = b.num;
					b.num = temp;
					break;
				}
			}
			if (PN == true && tempCheck == false)//�S����X�j�p�Aa=b
				return "0";
		}
		string revA(a.num.rbegin(), a.num.rend()), revB(b.num.rbegin(), b.num.rend());//�r�����
		 //��Ʀ�ɫe�m0
		if (revA.length() > revB.length())
		{
			int L = revA.length() - revB.length();
			for (int i = 0; i < L; i++)
				revB += "0";
		}
		else if (revA.length() < revB.length())
		{
			int L = revB.length() - revA.length();
			for (int i = 0; i < L; i++)
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

string number::operator *(number K)
{
	number a(num), b(K.num);
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
	//����a.b�L���t��
	//�P�_a.b�O�p�Ʃξ�Ƭۭ��A�O�p�ƴN��p���I�h���A�����p�Ʀ��
	unsigned long long int ait = a.num.find(".");
	unsigned long long int bit = b.num.find(".");
	unsigned long long int countDec = 0;
	bool checkDec = false;
	if (ait != a.num.npos)//a�O�p��
	{
		checkDec = true;
		countDec = countDec + a.num.length() - ait -1;
		string temp = a.num.substr(ait + 1, a.num.length() - ait - 1);//�p�Ƴ���
		a.num = a.num.substr(0, ait);//��Ƴ���
		a.num.append(temp);
	}
	if (bit != b.num.npos)//b�O�p��
	{
		checkDec = true;
		countDec = countDec + b.num.length() - bit - 1;
		string temp = b.num.substr(bit + 1, b.num.length() - bit - 1);//�p�Ƴ���
		b.num = b.num.substr(0, bit);//��Ƴ���
		b.num.append(temp);
	}

	string ans = "";
	int* numA, * numB, * numAns;//�p��ΰ}�C
	string revA(a.num.rbegin(), a.num.rend()), revB(b.num.rbegin(), b.num.rend());//�r�����
	unsigned long long int len = revA.length() + revB.length();
	numA = new int[revA.length()];
	numB = new int[revB.length()];
	numAns = new int[len];
	for (int i = 0; i < revA.length(); i++)//�r����Ʀr
		numA[i] = revA[i] - 48;

	for (int i = 0; i < revB.length(); i++)//�r����Ʀr
		numB[i] = revB[i] - 48;

	for (int i = 0; i < len; i++)//���װ}�C�k�s
		numAns[i] = 0;

	//�p��L�{
	int c = 0;
	for (int i = 0; i < revA.length(); i++)
	{
		for (int j = 0; j < revB.length(); j++)
		{
			numAns[i + j] += numA[i] * numB[j];
			if (numAns[i + j] > 9)
			{
				numAns[i + j + 1] += numAns[i + j] / 10;
				numAns[i + j] %= 10;
			}
		}
	}

	//���G�ഫ�^�r��
	while (len > 1 && numAns[len - 1] == 0)//��̰��줣��0���ƥB�O�d��Ƴ̤֤@���(120*5=0600)
		len--;

	if (checkDec == true)//���G�O�p�ơA�p���I�ɦ^
	{
		for (int i = 0; i <countDec; i++)//�p��
			ans += to_string(numAns[i]);
		ans += ".";
		for (int i = countDec; i <len; i++)//���
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
		for (int i = len - 1; i >= 0; i--)
			ans += to_string(numAns[i]);
	}
	delete[]numA;
	delete[]numB;
	delete[]numAns;
	return ans;
}

string number::operator ^(number K) {
	number a(num), b(K.num);
	unsigned long long int ait = a.num.find(".");
	unsigned long long int bit = b.num.find(".");
	bool a_sign = true;/*true��ܥ���*/
	bool b_sign = true;/*true��ܥ���*/
	bool decimalDigitsAllZero = true;
	bool b_dp_change = false;

	if (a.num[0] == '-') {/*a���t�A�h�ھ�b���Ӧ�ƪ��_���P�_���G�����t*/
		if (bit != b.num.npos) { /*�p�Gb"��"�p���I�A��p���I�e�@��Ʀr*/
			switch (b.num[bit - 1]) {
			case '1': case '3': case '5': case '7': case '9':
				a_sign = false;
				break;
			}
		}
		else if (bit == b.num.npos) { /*�p�Gb"�S��"�p���I�A��̫�@��Ʀr*/
			switch (b.num[b.num.length() - 1]) {
			case '1': case '3': case '5': case '7': case '9':
				a_sign = false;
				break;
			}
		}
		a.num.erase(0, 1);/*�w�T�{�����G�����t�ȡA�Na���t���h��*/
		ait = a.num.find(".");/*���s��p���I��m*/
	}
	
	if (b.num[0] == '-') {/*�p�Gb���t�ơA����n���˼ƹB��*/
		b_sign = false;
	}

	if (bit != b.num.npos && isSquareRoot(b) == true) { /*�p�Gb���p�ƥBb��0.5����ƭ�*/
		for (int i = bit + 1; i < b.num.length(); i++) {
			if (b.num[i] != '0') {
				decimalDigitsAllZero = false;/*decimalDigitsAllZero�Gb���p���I�Ҭ�0�O��true�A�Ϥ���false*/
				break;
			}
		}
		if (decimalDigitsAllZero == true) {/*�p�Gb���p���I��Ҭ�0�A�Nb���p���I�Τp�Ʀ�h���C*/
			b.num.erase(b.num.begin() + bit, b.num.end());
			bit = b.num.find(".");/*bit���s��p���I�A���G����npos*/
			b_dp_change = true;/*�O��b���p�Ʀ�O�Q���ܹL��*/
		}
	}
	else if (isSquareRoot(b) == false) { /*�p�Gb����0.5����ƭ��A�Nb���p���I�Τp�Ʀ�h���C*/
		b.num.erase(b.num.begin() + bit, b.num.end());
		bit = b.num.find(".");/*bit���s��p���I�A���G����npos*/
		b_dp_change = true;/*�O��b���p�Ʀ�O�Q���ܹL��*/
	}

	if (ait == a.num.npos && bit == b.num.npos) { /*����a�M����b�Ҭ���ơA�i�����B��*/
		if (b_sign == false) /*�p�Gb���t�ơA�R�h�t��(�o�q�i��Τ@)*/
			b.num.erase(0, 1);
		if (a.num == "0") {/*�p�Ga�����0�Ab�����*/
			number ans("0");
			if (b.num == "0")/*a�� 0 �M -0 ���赲�G�� 1*/
				ans.num = "1";
			if (b.num != "0" && b_sign == false)/*���Fa��-0����A���L����b���t�ɡA�^�ǪŭȡA�N��L�k�p��*/
				return "";
			if (b_dp_change == true) {/*�N��b�쥻���p��*/
				ans.num.insert(ans.num.end(), 1, '.');
				ans.num.insert(ans.num.end(), 100, '0');
			}
			return ans.num;
		}
		number count("0");
		number ans("1");
		while (count - b != "0") {
			ans.num = ans * a;
			count.num = count + number("1");
		}
		if (b_dp_change == true) {
			ans.num.insert(ans.num.end(), 1, '.');
			ans.num.insert(ans.num.end(), 100, '0');
		}
		if (b_sign == false)
			ans.num = number("1") / ans;
		if (a_sign == false && ans.num != "0")
			ans.num.insert(0, 1, '-');
		return ans.num;
	}
	else if (ait != a.num.npos && bit == b.num.npos) { /*����a���p�ơA����b����ơA���G�����p��*/
		for (int i = a.num.length() - 1; i > ait; i--) {/*�qa�����}�l�A�R���p�Ƴ����L�N�q��0*/
			if (a.num[i] == '0')
				a.num.erase(i, 1);
			else
				break;
		}
		unsigned long long int aDecDigits = a.num.length() - 1 - ait;/*����a�p���I�᪺���*/
		a.num.erase(ait, 1);/*���R���p���I*/
		int deleteZero = 0;
		for (int i = 0; i < a.num.length(); i++) {/*�qa�Y���}�l�A�R���e�褣�v�T�p�⪺0*/
			if (a.num[i] == '0')
				deleteZero++;
			else
				break;
		}
		a.num.erase(0, deleteZero);
		unsigned long long int ansDecDigits = 0;/*�������G���p���I�᪺���*/
		if (b_sign == false) /*�p�Gb���t�ơA�R�h�t��*/
			b.num.erase(0, 1);

		if (a.num == "0") { /*�p�G��z�᪺a�����0*/
			number ans("0");
			if (b.num == "0")/*a�� 0 �M -0 ���赲�G�� 1*/
				ans.num = "1";
			if (b.num != "0" && b_sign == false)/*���Fa��-0����A���L����b���t�ɡA�^�ǪŭȡA�N��L�k�p��*/
				return "";
			ans.num.insert(ans.num.end(), 1, '.');
			ans.num.insert(ans.num.end(), 100, '0');
			return ans.num;
		}

		number count("0");
		number ans("1");
		while (count - b != "0") {
			ans.num = ans * a;
			count.num = count + number("1");
			ansDecDigits += aDecDigits;/*�C���@���A���G���p���I���ƼW�[*/
		}
		if (ansDecDigits > ans.num.length()) /*�٭�e��R����0*/
			ans.num.insert(0, ansDecDigits - ans.num.length() + 1, '0');
		ans.num.insert(ans.num.end() - ansDecDigits, 1, '.'); /*�٭�p���I��m*/
		if (ans.num.find(".") == 0)
			ans.num.insert(0, 1, '0');
		if (ansDecDigits > 100)
			ans.num.erase(ans.num.begin() + ans.num.find(".") + 101, ans.num.end());
		else if (ansDecDigits < 100)
			ans.num.insert(ans.num.end(), 100 - ansDecDigits, '0');
		if (b_sign == false) {
			ans.num = number("1") / ans;
			if (ans.num.length() - 1 - ans.num.find(".") > 100)
				ans.num.erase(ans.num.begin() + ans.num.find(".") + 101, ans.num.end());
		}
		if (a_sign == false) {
			bool allZero = false;
			if (ans.num[0] == '0') {
				allZero = true;
				for (int i = 2; i < ans.num.length(); i++) {
					if (ans.num[i] != '0') {
						allZero = false;
						break;
					}
				}
			}
			if (allZero == false)
				ans.num.insert(0, 1, '-');
		}
		return ans.num;
	}
	else if (isSquareRoot(b) == true) { /*�p�Gb��0.5��ƭ����p��(�p�Gb���p�Ƴ�������0�A�h�w�g��z�����b)�Aa�i�ର��Ƥ]�i�ର�p��*/
		if (a.num[0] == '0') {
			number ans("0");
			bool aAllZero = true;/*�P�_a�O�_����0*/
			if (ait != a.num.npos) {/*�p�Ga���p��*/
				for (int i = 2; i < a.num.length(); i++) {
					if (a.num[i] != '0') {
						aAllZero = false;
						break;
					}
				}
			}
			if (aAllZero == true) {/*�p�Ga��0��0.0...0*/
				if (b_sign == false) {/*�p�G����b���t�A�^�ǪŭȡA��ܵL�k�p��*/
					return "";
				}
				ans.num.insert(ans.num.end(), 1, '.');
				ans.num.insert(ans.num.end(), 100, '0');
				return ans.num;
			}
		}

		if (b_sign == false) { /*�p�Gb���t�ơA�R�h�t��*/
			b.num.erase(0, 1);
			bit = b.num.find(".");
		}
		vector<int> tmp; /*�H�p���I�����ߡA�C��ӼƦr���@��*/
		unsigned long long int resultit;  /*�����p�⵲�G(result)���p���I��m*/
		number _a(a.num);
		if (ait == a.num.npos) { /*���*/
			if (_a.num.length() % 2 != 0) {/*�_�ơA�b�Ĥ@�Ӧ�m��0�A�����ܦ�����*/
				_a.num.insert(0, 1, '0');
			}
			for (int i = 0; i < _a.num.length(); i = i + 2) {
				string n;
				n.push_back(_a.num[i]);
				n.push_back(_a.num[i + 1]);
				tmp.push_back(stoi(n));
			}
			resultit = tmp.size();
			for (int i = 0; i < 100; i++) { /*�}�ڸ��i�঳�p�ơA���w�d100��p��*/
				tmp.push_back(0);
			}
		}
		else { /*�p��*/
			if (ait % 2 != 0) { /*�p���I�H�e���Ʀr���׬��_�ơA�b�Ĥ@�Ӧ�m��0�A�����ܦ�����*/
				_a.num.insert(0, 1, '0');
				ait++;
			}
			for (int i = 0; i < ait; i = i + 2) {  /*��Ʀ���@��*/
				string n;
				n.push_back(_a.num[i]);
				n.push_back(_a.num[i + 1]);
				tmp.push_back(stoi(n));
			}
			resultit = tmp.size();
			int decimal_len = _a.num.length() - 1 - ait; /*decimal_len�G�p���I�H��Ʀr������*/
			for (int i = 0; i < 200 - decimal_len; i++) { /*�p�Gdecimal_len���_�ơA�h��0��p���I���200��*/
				_a.num.push_back('0');
			}
			for (int i = ait + 1; i < _a.num.length(); i = i + 2) { /*�p�Ʀ�ǭǤ@�աA���Ϋ�|�x�s��100��*/
				string n;
				n.push_back(_a.num[i]);
				n.push_back(_a.num[i + 1]);
				tmp.push_back(stoi(n));
			}
		}

		int guess = 0;
		while (guess * guess <= tmp[0]) /*�Ĥ@�ӼƦr�}�ڸ�*/
			guess++;
		guess--;
		number result(to_string(guess));/*result�G�����}�ڸ��᪺�p�⵲�G*/
		int t = (tmp[0] - guess * guess) * 100 + tmp[1]; /*t�G�Ĥ@�ռ�(tmp[0])�Mguess*guess���t�A���H100�A�A�[�U�@��tmp[1]*/
		number t_num(to_string(t)); /*t�নnumber���O*/
		number g("0");
		while (number(t_num - number(number(number(result * number("20")) + g) * g)).num[0] != '-') { /*��̱���t_num���Ʀr�A���G�O��g*/
			g.num = g + number("1");
		}
		g.num = g - number("1");
		for (int i = 2; i < tmp.size(); i++) { /*��̱���t_num���Ʀr�A���G�O��g�A�÷s�W��result*/
			t_num.num = number(number(t_num - number(number(number(result * number("20")) + g) * g)) * number("100")) + number(to_string(tmp[i])); /*�s��t_num�P�W�@��result�����A���p��*/
			result.num.push_back(g.num[0]); /*�����s�W�����G*/
			g.num = "0";
			while (number(t_num - number(number(number(result * number("20")) + g) * g)).num[0] != '-') {
				g.num = g + number("1");
			}
			g.num = g - number("1");
		}

		unsigned long long int aDecDigits = 0;
		ait = a.num.find(".");
		if (ait != a.num.npos) { /*�p�Ga���p��*/
			for (int i = a.num.length() - 1; i > ait; i--) {/*�qa�����}�l�A�R���p�Ƴ����L�N�q��0*/
				if (a.num[i] == '0')
					a.num.erase(i, 1);
				else
					break;
			}
			aDecDigits = a.num.length() - 1 - ait;/*����a�p���I�᪺���*/
			a.num.erase(ait, 1);/*���R���p���I*/
			int deleteZero = 0;
			for (int i = 0; i < a.num.length(); i++) {/*�qa�Y���}�l�A�R���e�褣�v�T�p�⪺0*/
				if (a.num[i] == '0')
					deleteZero++;
				else
					break;
			}
			a.num.erase(0, deleteZero);
		}
		unsigned long long int ansDecDigits = 0;/*�������G���p���I�᪺���*/
		b.num.erase(bit);/*�R�hb���p�Ƴ���(.5)*/
		number ans("1");
		number count("0");
		while (count - b != "0") {
			ans.num = ans * a;
			count.num = count + number("1");
			ansDecDigits += aDecDigits;/*�C���@���A���G���p���I���ƼW�[*/
		}
		ans.num = result * ans;
		ansDecDigits += result.num.length() - resultit;
		if (ansDecDigits > ans.num.length())/*�٭�e��R����0*/
			ans.num.insert(0, ansDecDigits - ans.num.length() + 1, '0');
		ans.num.insert(ans.num.end() - ansDecDigits, 1, '.'); /*�٭�p���I��m*/
		if (ans.num.find(".") == 0)
			ans.num.insert(0, 1, '0');
		if (ansDecDigits > 100) /*�p���I��Y�W�L100��A�h�R���W�L������*/
			ans.num.erase(ans.num.begin() + ans.num.find(".") + 101, ans.num.end());
		if (b_sign == false) {
			ans.num = number("1") / ans;
			if (ans.num.length() - 1 - ans.num.find(".") > 100)
				ans.num.erase(ans.num.begin() + ans.num.find(".") + 101, ans.num.end());
		}
		if (a_sign == false) {
			bool allZero = false;
			if (ans.num[0] == '0') {
				allZero = true;
				for (int i = 2; i < ans.num.length(); i++) {
					if (ans.num[i] != '0') {
						allZero = false;
						break;
					}
				}
			}
			if (allZero == false)
				ans.num.insert(0, 1, '-');
		}
		return ans.num;
	}
}


/*string operator +(string a, string b)
{
	//�P�_a.b�O�_�O����
	if (a[0] == '-')//a�tb�t or a�tb��
	{
		a = a.substr(1, a.length() - 1);//�h�t��
		number temp(a, b);
		return temp.numb - temp.numa;
	}
	if (b[0] == '-')//a+b-
	{
		b = b.substr(1, b.length() - 1);//�h�t��
		number temp(a, b);
		return temp.numa - temp.numb;
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
}*/
/*string operator -(string a, string b)
{
	//�P�_a.b�O�_�O����
	if (b[0] == '-')//a-(-5)=a+5
	{
		b = b.substr(1, b.length() - 1);//�h�t��
		number tmp(a, b);
		return tmp.numa + tmp.numb;
	}
	if (a[0] == '-')//a�tb�� (-5)-b=-(5+b)
	{
		a = a.substr(1, a.length() - 1);//�h�t��
		number tmp(a, b);
		string temp = tmp.numa + tmp.numb;
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
}*/
/*string operator *(string a, string b)
{
	bool PN = true;//���G��(T)�t(F)
	//�P�_a.b���t��
	if (a[0] == '-' && b[0] == '-')//a.b�t�A���G����
	{
		a = a.substr(1, a.length() - 1);//�h�t��
		b = b.substr(1, b.length() - 1);//�h�t��
	}
	else if (a[0] == '-')//a-b+
	{
		PN = false;
		a = a.substr(1, a.length() - 1);//�h�t��
	}
	else if (b[0] == '-')//a+b-
	{
		PN = false;
		b = b.substr(1, b.length() - 1);//�h�t��
	}
	//����a.b�L���t��
	//�P�_a.b�O�p�Ʃξ�Ƭۭ��A�O�p�ƴN��p���I�h���A�����p�Ʀ��
	unsigned long long int ait = a.find(".");
	unsigned long long int bit = b.find(".");
	unsigned long long int countDec = 0;
	bool checkDec = false;
	if (ait != a.npos)//a�O�p��
	{
		checkDec = true;
		countDec = countDec + a.length() - ait - 1;
		string temp = a.substr(ait+1,a.length()-ait-1);//�p�Ƴ���
		a = a.substr(0, ait);//��Ƴ���
		a.append(temp);
	}
	if (bit != b.npos)//b�O�p��
	{
		checkDec = true;
		countDec = countDec + b.length() - bit - 1;
		string temp = b.substr(bit + 1, b.length() - bit - 1);//�p�Ƴ���
		b = b.substr(0, bit);//��Ƴ���
		b.append(temp);
	}

	string ans = "";
	int* numA, * numB, * numAns;//�p��ΰ}�C
	string revA(a.rbegin(), a.rend()), revB(b.rbegin(), b.rend());//�r�����
	unsigned long long int len = revA.length() + revB.length();
	numA = new int[revA.length()];
	numB = new int[revB.length()];
	numAns = new int[len];
	for (int i = 0; i < revA.length(); i++)//�r����Ʀr
		numA[i] = revA[i] - 48;

	for (int i = 0; i < revB.length(); i++)//�r����Ʀr
		numB[i] = revB[i] - 48;

	for (int i = 0; i < len; i++)//���װ}�C�k�s
		numAns[i] = 0;

	//�p��L�{
	int c = 0;
	for (int i = 0; i < revA.length(); i++)
	{
		for (int j = 0; j < revB.length(); j++)
		{
			int temp = numA[i] * numB[j];
			numAns[i + j] += temp % 10;
			numAns[i + j + 1] += temp / 10;
		}
	}
	//���G�ഫ�^�r��
	while (len > 1 && numAns[len - 1] == 0)//��̰��줣��0���ƥB�O�d��Ƴ̤֤@���(120*5=0600)
		len--;

	if (PN == false)//���G�O�t�ơA�t���[�^
		ans = "-";
	if (checkDec == true)//���G�O�p�ơA�p���I�ɦ^
	{
		for (int i = len - 1; i > len-countDec; i--)//���
			ans += to_string(numAns[i]);
		ans += ".";
		for (int i = len - countDec; i >= 0; i--)//�p��
			ans += to_string(numAns[i]);
		addzero(ans);
	}
	else//���G�O��ơA�����ഫ�r��
	{
		for (int i = len - 1; i >= 0; i--)
			ans += to_string(numAns[i]);
	}
	delete[]numA;
	delete[]numB;
	delete[]numAns;
	return ans;
}*/
/*string operator /(string a, string b)
{
	return "0";
}
string Exponential(string a, string b)//����
{
	return "0";
}
string Factorial(string a, string b)//����
{
	return "0";
}*/