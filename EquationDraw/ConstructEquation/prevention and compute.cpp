#include "number.h"

bool checkValid(vector<string>& formula,string originInput)//�ˬd&�ץ�&���Nformula�x�s���Ʀror�ܼơA���H�W��J�P�ɿ�Xĵ��
{
	if (!checkBracket(originInput))//�ˬd�A����
	{
		cout << "�A�����X�k" << endl;
		return false;//Ū�U�@�ӿ�J�⦡
	}
	if (!checkOperator(originInput))//�ˬd�s��B��l
	{
		cout << "�B��l���X�k" << endl;
		return false;//Ū�U�@�ӿ�J�⦡
	}
	for (int i = 0; i < formula.size(); i++)
	{
		//�����e�m0���B�z�g��class number��construct�̤F�A��r��s���Ʀr�ɦ۰ʰ�
		string temp = formula[i];
		if (temp == "(" || temp == ")" || temp == "+" || temp == "-" || temp == "*" || temp == "/" || temp == "^" || temp == "sin" || temp == "cos" || temp == "tan" || temp == "sin(" || temp == "cos(" || temp == "tan(")//�@��B��l���γB�z
			continue;
		mergePN(temp);//���t����X(�p�G���p���I�S���e�m0�]�|�ɤW)
		if (!checkDPs(temp))//�Ʀr���ƼƭӤp���I
		{
			cout << "�p���I��J���~" << endl;
			return false;
		}
		formula[i] = temp;//�˴����T�A�⥿�t����X�����ȵ��G�s�^formula
	}
	return true;//��J�Ʀr�˴��Ť��ųW�w
}

bool checkBracket(const string& line)//�ˬd���k�A���O�_�X�k
{
	int countP = 0, countN = 0;
	for (int i = 0; i < line.length(); i++){
		if (line[i] == '(')
			countP++;
		else if (line[i] == ')')
			countN++;
		if (countN > countP) { //�ˬd���k�A�����ǬO�_�ۤ�
			return false;
		}
	}
	if (countP != countN) //�ˬd���k�A���ƶq�O�_�@��
		return false;
	return true;
}

bool checkOperator(const string& line)//�s��B��� +*-/^��W�Ů檺�~��(�̪Ů��Ѧr��A�r����׬�1���~�O�B���)
{
	string previous = "", now = "";//�����e�@�ӡA�H�η�e���r
	stringstream ss(line);
	while (getline(ss, now, ' ')) //�Ů��Ѧr��
	{
		if (now == "+" || now == "-" || now == "*" || now == "/" || now == "^" || now == "=")
		{
			if (previous == "+" || previous == "-" || previous == "*" || previous == "/" || previous == "^" || previous == "=" || previous == "(" )
				return false;
		}
		if (previous == "sin" || previous == "cos" || previous == "tan") { //sin�Bcos�Btan�M���A��""��""���j�A�T�{���a���A��!
			if (now != "(")
				return false;
		}
		if (now == ")") { //�A�����O�Ū�
			if (previous == "(" || previous == "sin(" || previous == "cos(" || previous == "tan(") //sin�Bcos�Btan�M�A��""�S��""���j
				return false;
		}
		previous = now;
	}
	return true;
}

bool checkDPs(const string& num)//�h���p���I
{
	int it = num.find('.');
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
	while (num[c] == '+' || num[c] == '-')
	{
		if (num[c] == '+')
			P++;
		if (num[c] == '-')
			N--;
		c++;
	}
	if (P + N < 0 && abs(P + N) % 2 == 1)//���t�X�ֵ��G�O�t
	{
		num = "-" + num.substr(c, num.length() - c);//�u�d�t��
		if (num[1] == '.')//�Ҧp-.2
			num = "-0" + num.substr(1, num.length() - 1);//�ɫe�m0>>-0.2
	}
	else//���G�O���A�⥿�t��������
	{
		num = num.substr(c, num.length() - c);
		if (num[0] == '.')//�Ҧp .52
			num = "0" + num;//�ɫe�m0>>0.52
	}
}

void compute(vector<string>& formula)
{
	vector<int>foundOP;
	while (formula.size() > 1 || (formula.size() == 3 && formula[1] == "/"))
	{
		int found1 = -1; //��̫᪺���A����m
		int found2 = -1; //��Ĥ@�ӥk�A������m
		for (int i = 0; i < formula.size(); i++)
		{
			if (formula[i] == "(")
				found1 = i;
		}
		for (int i = found1 + 1; i < formula.size(); i++)
		{
			if (formula[i] == ")")
			{
				found2 = i;
				break;
			}
		}

		if (found1 != -1 && found2 != -1 && found1 < found2) //��o��A������
		{
			if (found1 + 1 == found2)
			{
				formula[0] = "err";
				cout << "()���L�Ʀr\n";
				return;
			}
		}
		else//�S���A��
		{
			found1 = -1;
			found2 = formula.size();
		}

		//for (int i = found1 + 1; i < found2; i++) //�B�zsin cos tan
		//{
		//	string b;
		//	if (formula[i] == "sin") {
		//		number a(formula[i+1]);
		//		b = a.computeSin();
		//	}
		//	else if (formula[i] == "cos") {
		//		number a(formula[i+1]);
		//		b = a.computeCos();
		//	}
		//	if (formula[i] == "tan") {
		//		number a(formula[i+1]);
		//		b = a.computeTan();
		//	}
		//	formula[i] = b;
		//	formula.erase(formula.begin() + i, formula.begin() + i + 1);
		//	found2--;
		//}

		for (int i = found2 - 1; i > found1; i--)//�B�z����
		{
			if (formula[i] == "^" && i != found1 + 1)
			{
				string temp = formula[i - 1];
				if (temp[0] == '-' && isDot5(formula[i + 1]))//�p�G�O�t�ƶ}�ڸ�
				{
					formula[0] = "err";
					cout << "�t�Ƥ���}�ڸ�\n";
					return;
				}
				else if (isAllZero(temp))//���Ƭ�0
				{
					formula.erase(formula.begin() + i, formula.begin() + i + 2);
					found2 -= 2;
					i--;
				}
				else
				{
					formula[i - 1] = number(formula[i - 1]) ^ number(formula[i + 1]);
					formula.erase(formula.begin() + i, formula.begin() + i + 2);
					found2 -= 2;
					i--;
				}
			}
		}

		for (int i = found1 + 1; i < found2; i++) //�B�z����
		{
			if (formula[i] == "/" || formula[i] == "*")
			{
				if (formula[i] == "/")
				{
					if (isAllZero(formula[i + 1]))
					{
						formula[0] = "���Ƥ��ର 0";
						return;
					}
					else
					{
						formula[i - 1] = number(formula[i - 1]) / number(formula[i + 1]);
						formula.erase(formula.begin() + i, formula.begin() + i + 2);
						found2 -= 2;
						i -= 2;
					}
				}
				else if (formula[i] == "*")
				{
					formula[i - 1] = number(formula[i - 1]) * number(formula[i + 1]);
					formula.erase(formula.begin() + i, (formula.begin() + i + 2));
					found2 -= 2;
					i--;
				}
			}
		}
		for (int i = found1 + 1; i < found2; i++) //�B�z�[��
		{
			if (formula[i] == "+" || formula[i] == "-")
			{
				if (i == found1 + 1 && formula[i] == "+") // (+ 123) = 123 ; (+ -123) = -123
				{
					formula[found1 + 1] = formula[1];
				}
				else if (i == found1 + 1 && formula[i] == "-")
				{
					number zero("0");
					number b(formula[i + 1]);
					formula[found1 + 1] = zero - b;
				}
				else if (formula[i] == "+") //(1 + 2) = 3
				{
					number a(formula[found1 + 1]);
					number b(formula[i + 1]);
					formula[found1 + 1] = a + b;
				}
				else if (formula[i] == "-")
				{
					number a(formula[found1 + 1]);
					number b(formula[i + 1]);
					formula[found1 + 1] = a - b;
				}
				i++;
			}
		}

		if (found1 == -1)//�S�A�����B��
		{
			formula.erase(formula.begin() + 1, formula.end());
		}
		else
		{
			formula[found1] = formula[found1 + 1];
			formula.erase(formula.begin() + found1 + 1, formula.begin() + found2 + 1);
		}
	}
}

