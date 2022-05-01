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
	while (num[c] == '+' || num[c] == '-')
	{
		if (num[c] == '+')
			P++;
		if (num[c] == '-')
			N--;
		c++;
	}

	//�J�줣�O�Ʀr(Integer&Decimal���W��)�n���j�M(���Ѧ�class�\���٨S�g)�A�S�j�M��^��"WRONG_NAME"

	if (P + N < 0 && abs(P + N) % 2 == 1)//���t�X�ֵ��G�O�t
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

long long int findFra(unsigned long long int n, vector<long long int>foundOP) {
	int lastOne = 0;
	for (int i = 0; i < foundOP.size(); i++)
	{
		if (n == foundOP[i])
			lastOne = i;
	}
	return lastOne;
}
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

	vector<number>denominator, numerator;
	vector<long long int>foundOP;
	bool Fraction = false;

	while (formula.size() > 1 || (formula.size() == 3 && formula[1] == "/"))
	{
		long long int found1 = -1; //��̫᪺���A����m
		long long int found2 = -1; //��Ĥ@�ӥk�A������m
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

		for (int i = found1 + 1; i < found2; i++)//�B�z����
		{
			if (formula[i] == "!" && i != found1 + 1)
			{
				if (formula[i - 1][0] == '-')
				{
					formula[0] = "err";
					cout << "�t�Ƥ���ⶥ��\n";
					return;
				}
				else if (!isDec(formula[i - 1]))
				{
					string a = number(formula[i-1]).factorial();
					formula[i - 1] = a;
					formula.erase(formula.begin() + i, formula.begin() + i+1);
					found2 -= 1;
					i--;
					
				}
				else
				{
					formula[0] = "err";
					cout << "�p�Ƥ���ⶥ��\n";
					return;
				}
			}
		}
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
						if (!isDec(formula[i + 1]) && !isDec(formula[i - 1]))
						{
							formula[i - 1] = number(formula[i - 1]) / number(formula[i + 1]);
							formula.erase(formula.begin() + i, formula.begin() + i+2);
							found2 -= 2;
						}
						else if (!Fraction)
						{
							denominator.push_back(number(formula[i + 1])); //�]�w����
							numerator.push_back(number(formula[i - 1]));  //�]�w���l
							foundOP.push_back(i - 1);
							formula.erase(formula.begin() + i, formula.begin() + i + 2);
							found2 -= 2;
							formula[i - 1] = "Fraction";
							Fraction = true;
						}
						else // a/b
						{
							if (formula[i + 1] == "Fraction" && formula[i - 1] != "Fraction")// a���O���� b�O���� 
							{
								long long int foundDen = findFra(i + 1, foundOP);
								number temp(denominator[foundDen].num);
								number a(formula[i - 1]);
								denominator[foundDen].num = numerator[foundDen].num;
								numerator[foundDen].num = temp * a;
								foundOP[foundDen] = i - 1;
								formula.erase(formula.begin() + i, formula.begin() + i + 2);
								found2 -= 2;
								formula[i - 1] = "Fraction";
							}
							else if (formula[i + 1] != "Fraction" && formula[i - 1] == "Fraction") //a�O���� b���O����
							{
								long long int foundNum = findFra(i - 1, foundOP);
								number a(formula[i + 1]);
								denominator[foundNum].num = denominator[foundNum] * a;
								foundOP[foundNum] = i - 1;
								formula.erase(formula.begin() + i, formula.begin() + i + 2);
								found2 -= 2;
								formula[i - 1] = "Fraction";
							}
							else if (formula[i + 1] == "Fraction" && formula[i - 1] == "Fraction") //a b���O����
							{
								long long int foundNum = findFra(i - 1, foundOP); //a
								long long int foundDen = findFra(i + 1, foundOP); //b

								numerator[foundNum].num = numerator[foundNum] * denominator[foundDen];//a�����l=a�����l*b������
								denominator[foundNum].num = denominator[foundNum] * numerator[foundDen];//a������=a������*b�����l

								foundOP[foundNum] = i - 1;
								foundOP.erase(foundOP.begin() + foundDen); //�R��b����m����
								numerator.erase(numerator.begin() + foundDen); //�R��b�����l
								denominator.erase(denominator.begin() + foundDen);//�R��b������

								formula.erase(formula.begin() + i, formula.begin() + i + 2);
								found2 -= 2;
								formula[i - 1] = "Fraction";
							}
							else //a b �����O����
							{
								denominator.push_back(number(formula[i + 1])); //�]�w����
								numerator.push_back(number(formula[i - 1]));  //�]�w���l
								foundOP.push_back(i - 1);
								formula.erase(formula.begin() + i, (formula.begin() + i + 2));
								found2 -= 2;
								formula[i - 1] = "Fraction";
							}
						}
						i-=2;
					}
				}
				else if (formula[i] == "*")
				{
					if (formula[i + 1] == "Fraction" && formula[i - 1] != "Fraction")// a���O���� b�O���� 
					{
						long long int foundDen = findFra(i + 1, foundOP);
						number a(formula[i - 1]);
						numerator[foundDen].num = numerator[foundDen] * a;
						foundOP[foundDen] = i - 1;
						formula.erase(formula.begin() + i, formula.begin() + i + 2);
						found2 -= 2;
						formula[i - 1] = "Fraction";
					}
					else if (formula[i + 1] != "Fraction" && formula[i - 1] == "Fraction") //a�O���� b���O����
					{
						long long int foundNum = findFra(i - 1, foundOP);
						number a(formula[i + 1]);
						numerator[foundNum].num = numerator[foundNum] * a;
						foundOP[foundNum] = i - 1;
						formula.erase(formula.begin() + i, formula.begin() + i + 2);
						found2 -= 2;
						formula[i - 1] = "Fraction";
					}
					else if (formula[i + 1] == "Fraction" && formula[i - 1] == "Fraction") //a b���O����
					{
						long long int foundNum = findFra(i - 1, foundOP); //a
						long long int foundDen = findFra(i + 1, foundOP); //b

						numerator[foundNum].num = numerator[foundNum] * numerator[foundDen];//a�����l=a�����l*b�����l
						denominator[foundNum].num = denominator[foundNum] * denominator[foundDen];//a������=a������*b������

						foundOP[foundNum] = i - 1;
						foundOP.erase(foundOP.begin() + foundDen); //�R��b����m����
						numerator.erase(numerator.begin() + foundDen); //�R��b�����l
						denominator.erase(denominator.begin() + foundDen);//�R��b������

						formula.erase(formula.begin() + i, formula.begin() + i + 2);
						found2 -= 2;
						formula[i - 1] = "Fraction";
					}
					else //a b �����O����
					{
						formula[i - 1] = number(formula[i - 1]) * number(formula[i + 1]);
						formula.erase(formula.begin() + i, (formula.begin() + i + 2));
						found2 -= 2;
					}
					i--;
				}
			}
		}
		for (int i = found1 + 1; i < found2; i++) //�B�z�[��
		{
			if (formula[i] == "+" || formula[i] == "-")
			{
				if (!Fraction)//���q()���L����
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
				else //���q()��������
				{
					if (i == found1 + 1 && formula[i] == "+" && formula[i + 1] == "Fraction")//(+ 1/3)= 1/3
					{
						long long int foundFra = findFra(i + 1, foundOP);
						foundOP[foundFra] = found1 + 1;
						formula[found1 + 1] = "Fraction";
					}
					else if (i == found1 + 1 && formula[i] == "-" && formula[i + 1] == "Fraction")//(- -1/3)= +1/3
					{
						long long int foundFra = findFra(i + 1, foundOP);
						number zero("0");
						numerator[foundFra].num = zero - numerator[foundFra];
						denominator[foundFra].num = zero - denominator[foundFra];
						foundOP[foundFra] = found1 + 1;
						formula[found1 + 1] = "Fraction";
					}
					else if (formula[i] == "+" && formula[i + 1] == "Fraction" && formula[found1 + 1] != "Fraction") // (1 + 1/3) = (1*3+1)/3
					{
						long long int foundFra = findFra(i + 1, foundOP);
						number a(formula[found1 + 1]);
						numerator[foundFra].num = numerator[foundFra] + a * denominator[foundFra];
						foundOP[foundFra] = found1 + 1;
						formula[found1 + 1] = "Fraction";
					}
					else if (formula[i] == "+" && formula[i + 1] != "Fraction" && formula[found1 + 1] == "Fraction") // (1/3 + 1) = (1+1*3)/3
					{
						long long int foundFra = findFra(found1 + 1, foundOP);
						number a(formula[i + 1]);
						numerator[foundFra].num = numerator[foundFra] + number(a * denominator[foundFra]);
					}
					else if (formula[i] == "+" && formula[i + 1] == "Fraction" && formula[found1 + 1] == "Fraction") // (1/3 + 1/3) = (2/3)
					{
						long long int founda = findFra(found1 + 1, foundOP);
						long long int foundb = findFra(i + 1, foundOP);
						if (denominator[founda] == denominator[foundb])//�����ۦP->���ݳq�� ���l�ۥ[�ᵲ�G�x�s��a��
						{
							numerator[founda] = numerator[founda] + numerator[foundb];
							cout << numerator[founda].num << endl;
						}
						else//�������P->�q��
						{
							numerator[founda] = number(numerator[founda] * denominator[foundb]) + number(numerator[foundb] * denominator[founda]);
							denominator[founda] = denominator[founda] * denominator[foundb];
							cout << numerator[founda].num << endl;
						}
					}

					else if (formula[i] == "-" && formula[i + 1] == "Fraction" && formula[found1 + 1] != "Fraction") // (1 - 1/3) = (1*3-1)/3
					{
						long long int foundFra = findFra(i + 1, foundOP);
						number a(formula[found1 + 1]);
						numerator[foundFra].num = number(a * denominator[foundFra]) - numerator[foundFra];
						foundOP[foundFra] = found1 + 1;
						formula[found1 + 1] = "Fraction";
					}
					else if (formula[i] == "-" && formula[i + 1] != "Fraction" && formula[found1 + 1] == "Fraction") // (1/3 - 1) = (1-1*3)/3
					{
						long long int foundFra = findFra(found1 + 1, foundOP);
						number a(formula[i + 1]);
						numerator[foundFra].num = numerator[foundFra] - number(a * denominator[foundFra]);
					}
					else if (formula[i] == "-" && formula[i + 1] == "Fraction" && formula[found1 + 1] == "Fraction") // (1/3 - 1/3) = (0)
					{
						long long int founda = findFra(found1 + 1, foundOP);
						long long int foundb = findFra(i + 1, foundOP);
						if (denominator[founda] == denominator[foundb])//�����ۦP->���ݳq�� ���l�ۥ[�ᵲ�G�x�s��a��
						{
							numerator[founda] = numerator[founda] - numerator[foundb];
						}
						else//�������P->�q��
						{
							numerator[founda] = number(numerator[founda] * denominator[foundb]) - number(numerator[foundb] * denominator[founda]);
							denominator[founda] = denominator[founda] * denominator[foundb];
						}
					}
				}

			}
		}

		if (found1 == -1)//�S�A�����B��
		{
			if (!Fraction)//�p�G�S����
				formula.erase(formula.begin() + 1, formula.end());
			else
			{
				long long int foundFra = findFra(found1 + 1, foundOP);
				formula[0] = numerator[foundFra] / denominator[foundFra];
				formula.erase(formula.begin() + 1, formula.end());
				numerator.erase(numerator.begin(), numerator.end());
				denominator.erase(denominator.begin(), denominator.end());
				foundOP.erase(foundOP.begin(), foundOP.end());
			}
		}
		else
		{
			if (!Fraction)//�p�G�S����
			{
				formula[found1] = formula[found1 + 1];
				formula.erase(formula.begin() + found1 + 1, formula.begin() + found2+1);
			}
			else //������
			{
				long long int foundFra = findFra(found1 + 1, foundOP);
				formula[found1] = numerator[foundFra].num;
				formula[found1 + 1] = "/";
				formula[found1 + 2] = denominator[foundFra].num;
				formula.erase(formula.begin() + found1 + 3, formula.begin() + found2+1);
				numerator.erase(numerator.begin(), numerator.end());
				denominator.erase(denominator.begin(), denominator.end());
				foundOP.erase(foundOP.begin(), foundOP.end());
			}
		}
	}
}

