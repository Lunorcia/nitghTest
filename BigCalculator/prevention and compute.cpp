#include "number.h"
#include "Integer.h"
#include "Decimal.h"
bool checkValid(vector<string>& formula,string originInput)//�ˬd&�ץ�&���Nformula�x�s���Ʀror�ܼơA���H�W��J�P�ɿ�Xĵ��
{
	if (!checkBracketAmount(originInput))//�ˬd�A����
	{
		cout << "�A��������" << endl;
		return false;//Ū�U�@�ӿ�J�⦡
	}
	if (!checkOperator(originInput))//�ˬd�s��B��l
	{
		cout << "���i�s���J(��.�t��.����.�A��)�H�~���B��l+-*/^=" << endl;
		return false;//Ū�U�@�ӿ�J�⦡
	}
	bool Valid = true;
	for (int i = 0; i < formula.size(); i++)
	{
		//Integer&Decimal�ܼƷӼ˶ǤJ
		//�����e�m0���B�z�g��class number��construct�̤F�A��r��s���Ʀr�ɦ۰ʰ�
		string temp = formula[i];
		if (temp == "(" || temp == ")" || temp == "+" || temp == "-" || temp == "*" || temp == "/" || temp == "!" || temp == "^" || temp.substr(0, 5) == "Power")//�@��B��l���γB�z
			continue;
		mergePN(temp);//���t����X(�p�G���p���I�S���e�m0�]�|�ɤW)
		if (temp == "WRONG_NAME")
		{
			cout << "�䤣���ܼ�" << endl;
			Valid = false;
			break;
		}
		if (!checkDPs(temp))//�Ʀr���ƼƭӤp���I
		{
			cout << "�p���I��J���~" << endl;
			break;
		}
		formula[i] = temp;//�˴����T�A�⥿�t����X��& Int or Dec���ȵ��G�s�^
	}
	return Valid;//��J�Ʀr�˴��Ť��ųW�w
}
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
		if (now == "+" || now == "-" || now == "*" || now == "/" || now == "^" || now == "=")
		{
			if (previous == "+" || previous == "-" || previous == "*" || previous == "/" || previous == "^" || now == "=")
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
			int pos=Integer::searchIntName(var);
			if (pos >= 0)//�W�r�bInteger
				var = Integer::searchIntValue(pos);
			else//�W�r�bDecimal
			{
				pos = Decimal::searchDecName(var);
				var = Decimal::searchDecValue(pos);//�����N�^�ǭȡA�S���N�����^��WRONG_NAME
			}
			
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
			string var = num;
			int pos = Integer::searchIntName(var);
			if (pos >= 0)//�W�r�bInteger
				var = Integer::searchIntValue(pos);
			else//�W�r�bDecimal
			{
				pos = Decimal::searchDecName(var);
				var = Decimal::searchDecValue(pos);//�����N�^�ǭȡA�S���N�����^��WRONG_NAME
			}

			num = var;//����쵲�G�O�ƭȡA�S���N�OWRONG_NAME
		}
	}


}
/*bool convertPower(vector<string>& formula)//Power(2,3)�3�Ӧr��>>"2">>"^">>"3"�A�Ĥ@�Ө��Ntemp�bvector����m�A�᭱��ӥδ��J����(��X�Ӫ���ӼƦr�n���]�@���e�����˴�
{
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
}*/
void Compute(vector<string>& formula)
{
	/////////////�p���k/////////////////
	// �p�G�p�⤤�~���L�ĹB��(���U�����@)
	// ����~�T���s�bformula[0]�A�����p��A���Φ^�ǭ�(���~�T���^��:��������O�t�ơB���Ƥ���O0�B�t�Ƥ���}�ڸ��B...)
	// �̫�d�Uformula[0](����)
	// 
	// (v)��ѼƦr�e���b:�A���ơA�s��B���+-*/^
	// (v)��ѫ��W�Ʀr�@�ߥ��i���t����X,ex: +-+5 >> -5�A�M��i�p���I�ƶq�T�{(���ެO���O�p��)
	// �p���u����:����>����(�u���ץѥk�쥪)> * > / > + > - 
	// ��ƭp��e�ˬd(���u�Хܿ�J�⦡���Ů�):
	// ��������O�t��,ex:-5_!
	// ���Ƥ���O0,ex: 5_/_0	
	// �t�Ƥ���}�ڸ�,ex: -2.5_^_0.5
	// ���ƭp��e>>�ڸ�0=0
}