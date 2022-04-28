#include "number.h"
bool checkBracketAmount(const string& line);
bool checkOperator(string line);
bool checkDPs(const string& num);
bool negativeRoot(const string& num);
void mergePN(string& num);
bool convertPower(vector<string>& formula);
void checkValidCompute(vector<string> formula);
int main()
{	//����\���٨S��>>Power(2,3)>>��J��ꤣ�n�Ů�A�i�p��Ψ禡�ন
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
		//���P�_���S������rSet
		
		vector<string> formula;//�x�s�⦡��
		stringstream ss(input);
		string tempss="";
		while (getline(ss, tempss, ' '))//��ѿ�J�r��
			formula.push_back(tempss);
		ss.str("");
		ss.clear();

		//�p�Gvector size=1�A�N��M��ÿ�X�ܼ�
		//�p�G�ĤG�Ӧr��O�����A�̫ᵲ�G�u�nassign�A���ο�X

		if (!checkBracketAmount(input))//�ˬd�A����
		{
			cout << "�A��������" << endl;
			continue;//Ū�U�@�ӿ�J�⦡
		}
		if (!checkOperator(input))//�ˬd�s��B��l
		{
			cout << "���i�s���J(��.�t��.����)�H�~���B��l+-*/^" << endl;
			continue;//Ū�U�@�ӿ�J�⦡
		}
		/////////////////////////////Power�ഫ��|�ݭn���ƥ��ˬd�������A����W�ߦ��@�Ө禡
		bool checkValid = true;
		for (int i = 0; i < formula.size(); i++)
		{
			//Integer&Decimal�ܼƷӼ˶ǤJ
			//�����e�m0���B�z�g��class number��construct�̡A��r��s���Ʀr�ɦ۰ʰ�
			
			string temp = formula[i];
			if (temp == "(" || temp == ")" || temp == "+" || temp == "-" || temp == "*" || temp == "/" || temp == "!" || temp == "^" || temp.substr(0, 5) == "Power")//�@��B��l���γB�z
				continue;
			mergePN(temp);//���t����X(�p�G���p���I�S���e�m0�]�|�ɤW)
			if (temp == "WRONG_NAME")
			{
				cout << "�䤣���ܼ�" << endl;
				checkValid = false;
				break;
			}
			if (!checkDPs(temp))//�Ʀr���ƼƭӤp���I
			{
				cout << "�p���I��J���~" << endl;
				break;
			}

			formula[i] = temp;//�˴����T�A�⥿�t����X��& Int or Dec���ȵ��G�s�^���N
		}
		
		if (checkValid == false)//��J�Ʀr�˴����ųW�w
			continue;//Ū�U�@�ӿ�J�⦡
		checkValid = convertPower(formula);//�ഫPower(a,b)>>a^b
		if (!checkValid)
		{
			cout << "Power��J���~" << endl;
			continue;//Ū�U�@�ӿ�J�⦡
		}

	}

	//���b�Ψ禡�O����A�����ǤJ�r���˴�
	//Power(5, 2)
	//��ѼƦr�e���b:�A���ơA�s��B���+-*/^
	//��ѫ��W�Ʀr�@�ߥ��i���t����X,ex: +-+5 >> -5�A�M��i�p���I�ƶq�T�{(���ެO���O�p��)
	//�p���u����:����>����
	//�p��e(���u�Хܿ�J�⦡���Ů�):	��������O�t��,ex:-5_!
	//									���Ƥ���O0,ex: 5_/_0	
	//									�t�Ƥ���}�ڸ�,ex: -2.5_^_0.5
	//									���ƭp��e>>�ڸ�0=0
}