#include "number.h"
#include "Integer.h"
#include "Decimal.h"

int main()
{
	string str1("a"), str2;
	while (cin >> str1 && str1 != "-1")
	{
		cin >> str2;
		number num1(str1), num2(str2);
		//cout  << num1 / num2 << " a" << endl;//<< num1 + num2 << endl << num1 - num2 << endl
		string ans = num1 ^ num2;
		cout << "exp = " << ans << endl;//<< num1 + num2 << endl << num1 - num2 << endl
		//ans = num1.factorial();
		//cout << "fact = " << ans << endl;
	}
	string input;
	while (getline(cin, input))
	{
		
		vector<string> formula;//�x�s�⦡��
		stringstream ss(input);
		string tempss="";
		while (getline(ss, tempss, ' '))//��ѿ�J�r��
			formula.push_back(tempss);
		ss.str("");
		ss.clear();
		//���P�_���S������rSet
		//�p�GSet�ܼƦ��p��(A=3+5-0.8)�U���L�{���⧹�A�̫�sclass Int/Dec(�ȡA�W)(�x�s�ܼƭn���T�w�W�r���S���s�b�A�w�s�b�N�ק�ȡA�S���N�s�s��)
		///////////////////class�g�n���ܭn�令Integer temp(�⦡or��@��,�W); cout<<temp;	�Ȫ��p��b�I�sInteger�ɩI�s�禡(�U���o�ǨB�J�g��global function)
		bool setInt = false, setDec = false;
		string variableName = "";
		if (formula[0] == "Set" && formula.size()>4)
		{
			if (formula[1] == "Integer" && formula[3] == "=")
			{
				setInt = true;
				variableName = formula[2];
				formula.erase(formula.begin(), formula.begin() + 4);//�hSet//�hInteger//�h�ܼ�//�h����
			}
			else if (formula[1] == "Decimal" && formula[3] == "=")
			{
				setDec = true;
				variableName = formula[2];
				formula.erase(formula.begin(), formula.begin() + 4);//�hSet//�hDecimal//�h�ܼ�//�h����
			}
			else
			{
				cout << "��J�榡���~" << endl;
				continue;//Ū�U�@�ӿ�J�⦡
			}
		}
		if (formula[1] == "=")		//�p�G�ĤG�Ӧr��O�����A�̫ᵲ�G�u�nassign�A���ο�X
		{
			string var = formula[0];
			int pos = Integer::searchIntName(formula[0]);
			if (pos != -1)//�W�r�bInteger
			{
				setInt = true;
				variableName = formula[0];
				formula.erase(formula.begin(), formula.begin() + 2);//�h�ܼ�//�h����
			}
			else if (Decimal::searchDecName(formula[0]) != -1)//�W�r�bDecimal
			{
				setDec = true;
				variableName = formula[0];
				formula.erase(formula.begin(), formula.begin() + 2);//�h�ܼ�//�h����
			}
			else
			{
				cout << "�䤣���ܼ�" << endl;
				continue;//Ū�U�@�ӿ�J�⦡
			}
		}

		//assign�e�m�����A�ˬd�⦡
		bool Valid = checkValid(formula,input);//�ˬd&�ץ�&���Nformula�x�s���Ʀror�ܼơA���H�W��J�P�ɿ�Xĵ��
		if (Valid == false)//��J�Ʀr�˴����ųW�w
			continue;//Ū�U�@�ӿ�J�⦡

		////////////////�⦡�p��/////////////////
		Compute(formula);
		string errorMessage = formula[0];
		if (!isdigit(errorMessage[0]))//�Ĥ@��s���O���~�T��
		{
			cout << errorMessage << endl;
			continue; //Ū�U�@�ӿ�J�⦡
		}
		
		if (setInt == true)//���Gassign�N�n���ο�X
		{	//���ܼƦs���s�b
			int pos = Integer::searchIntName(variableName);
			if (pos != -1)//�s�b���
				Integer::setValue(formula[0], pos);

			else//���s�b�A�s�s��
				Integer temp(formula[0], variableName);//�s�Jstatic list
		}
		else if (setDec == true)
		{	//���ܼƦs���s�b
			int pos = Decimal::searchDecName(variableName);
			if (pos != -1)//�s�b���
				Decimal::setValue(formula[0], pos);

			else//���s�b�A�s�s��
				Decimal temp(formula[0], variableName);//�s�Jstatic list
		}
		else//���G�n��X
		{
			cout << formula[0];
		}
	}

}