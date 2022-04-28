#include "number.h"
bool checkBracketAmount(const string& line)//���k�A���ƶq���@��
{
	int countP = 0, countN = 0;
	for (int i = 0; i < line.length(); i++)
	{
		if (line[i] == '(')
			countP++;
		else if (line[i] == ')')
			countN++;
	}
	if (countP != countN)
		return false;
	return true;

}
bool checkOperator(string line)//�s��B��� +*-/^(�����i�H�s��(3_!_!=720))��W�Ů檺�~��(�̪Ů��Ѧr��A�r����׬�1���~�O�B���)
{
	vector<string> numAndOpe;
	string previous = "", now = "";
	stringstream ss(line);
	while (getline(ss, now, ' '))//�Ů��Ѧr��
	{
		if (now == "+" || now == "-" || now == "*" || now == "/" || now == "^")
		{
			if (previous == "+" || previous == "-" || previous == "*" || previous == "/" || previous == "^")
				return false;
		}
		previous = now;
	}
	return true;

}
bool checkDPs(const string& num)//�h���p���I
{
	long long int it = num.find('.');
	if (it != num.npos)//���p���I
	{
		it = num.find('.',it+1);//�䦳�S���ĤG�Ӥp���I
		if (it != num.npos)
			return false;
	}
	//�p�G�䤣��or�u���@�Ӥp���I �^��true
	return true;
}
bool negativeRoot(const string& num)//�t�Ƥ���}�ڸ�
{
	if (num[0] == '-')
		return false;
	return true;
}
void mergePN(string& num)
{
	int P = 0, N = 0, c = 0;
	while (num[c] == '+' || num[c] == '+')
	{
		if (num[c] == '+')
			P++;
		if (num[c] == '-')
			N--;
		c++;
	}

	//�J�줣�O�Ʀr(Integer&Decimal���W��)�n���j�M(���Ѧ�class�\���٨S�g)�A�S�j�M��^��"WRONG_NAME"

	if (P + N < 0)//���t�X�ֵ��G�O�t
	{
		num = "-" + num.substr(c, num.length() - c);
		if (num[1] == '.')//�Ҧp-.2
			num = "-0" + num.substr(1, num.length() - 1);//�ɫe�m0>>-0.2
		if (!isdigit(num[1]))//�t����Ĥ@�Ӧr�����O�Ʀr>>��J�O�ܼ�
		{
			string var = num.substr(1, num.length() - 1);

			//var=�I�sclass.func(var)�A�^���ܼƭ�;�S�j�M��^��"WRONG_NAME"

			if (var == "WRONG_NAME")//�S����ܼ�
			{
				num = var;
				return;
			}
			else
			{
				num = "-" + var;
			}
		}
	}
	else//���G�O���A�⥿�t��������
	{
		num = num.substr(c, num.length() - c);
		if (num[0] == '.')//�Ҧp .52
			num = "0" + num;//�ɫe�m0>>0.52
		if (!isdigit(num[0]))//�Ĥ@�Ӧr�����O�Ʀr>>��J�O�ܼ�
		{
			//num=�I�sclass.func(num)�A�^���ܼƭ�;�S�j�M��^��"WRONG_NAME"

			/*if (num == "WRONG_NAME")//�S����ܼ�
				return;*/

		}
	}


}
bool convertPower(vector<string>& formula)//Power(2,3)�3�Ӧr��>>"2">>"^">>"3"�A�Ĥ@�Ө��Ntemp�bvector����m�A�᭱��ӥδ��J����(��X�Ӫ���ӼƦr�n���]�@���e�����˴�
{/////////////////�s��power�S��
	for (int i = 0; i < formula.size(); i++)
	{
		string temp = formula[i];
		if (temp.substr(0, 5) == "Power")
		{
			long long int commaF = temp.find(',');
			long long int commaB = temp.rfind(',');
			if (commaF != commaB)//���Ƽƭӳr��
				return false;
			long long int braL = temp.find('(');
			long long int braR = temp.rfind(')');
			if (braL != temp[5] || braR != temp[temp.length() - 1])//���k�A����m����
				return false;
			string numA(temp.begin() + 6, temp.end());//�ƻs���A���᪺�r��(��6�Ӧr���}�l)
			commaF = numA.find(',');
			numA = numA.substr(0, commaF);//����
			string numB(temp.begin() + 7 + numA.length(), temp.end());
			numB = numB.substr(0, numB.length() - 1);//����(�h�k�A��)
			formula[i] = numA;
			if (i == formula.size() - 1)//�̧��ݴ��J��end()(i+1�|�W�Xvector size)
			{
				formula.insert(formula.end() , "^");
				i++;
				formula.insert(formula.end(), numB);
				i++;
			}
			else
			{
				formula.insert(formula.begin() + i + 1, "^");//���J�bi+1�e��(=numA��)
				i++;
				formula.insert(formula.begin() + i + 1, numB);
				i++;
			}
		}
	}
	return true;
}
void checkValidCompute(vector<string> formula)
{
	
//Power(5, 2)
//��ѼƦr�e���b:�A���ơA�s��B���+-*/^
//��ѫ��W�Ʀr�@�ߥ��i���t����X,ex: +-+5 >> -5�A�M��i�p���I�ƶq�T�{(���ެO���O�p��)
//�p���u����:����>����
//�p��e(���u�Хܿ�J�⦡���Ů�):	��������O�t��,ex:-5_!
//									���Ƥ���O0,ex: 5_/_0	
//									�t�Ƥ���}�ڸ�,ex: -2.5_^_0.5
//�ڸ�0=0
}