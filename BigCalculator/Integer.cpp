#include "Integer.h"
vector<string>Integer::numIntList;
vector<string>Integer::nameIntList;
Integer::Integer(string a) :number(a)//�~��//�S���R�W��Int(�i�H������ȥ��ܼ�
{
	long long int space = a.find(" ");//�p�G�r�꦳�Ů�N��a�O�⦡�A�n�p��A�x�s
	if (space != a.npos)
	{
		vector<string> formula;//�x�s�⦡��
		stringstream ss(a);
		string tempss = "";
		while (getline(ss, tempss, ' '))//��ѿ�J�r��
			formula.push_back(tempss);
		ss.str("");
		ss.clear();
		bool Valid = checkValid(formula, a);//�ˬd&�ץ�&���Nformula�x�s���Ʀror�ܼơA���H�W��J�P�ɿ�Xĵ��
		if (Valid == false)//��J�Ʀr�˴����ųW�w
		{
			num = "0";
			name = "";
		}
		else//�⦡�p��
		{	
			Compute(formula);
			string errorMessage = formula[0];
			if (!isdigit(errorMessage[0]))//�Ĥ@��s���O���~�T��
			{
				cout << errorMessage << endl;
				num = "0";
				name = "";
			}
			else//�p�⵲�G�x�s
			{
				Integer temp(formula[0]);//�⵪�װ��r��B�z
				num = temp.num;
				name = "";
			}
		}
	}
	else//��@�Ʀr���έp��
	{
		string tempPN = "";
		if (a[0] == '-')//����t���M�Ʀr����
		{
			tempPN = "-";
			a = a.substr(1, a.length() - 1);
		}
		while (a[0] == '0' && a.length() > 1)//�h�e�m0
			a = a.substr(1, a.length() - 1);
		tempPN += a;
		long long int ait = tempPN.find(".");
		if (ait != tempPN.npos)//�h�p���I
			tempPN = tempPN.substr(0, ait);
		num = tempPN;
		name = "";
	}
}

Integer::Integer(string a, string setN) :number(a)//���R�W��"�s"Int
{
	long long int space = a.find(" ");//�p�G�r�꦳�Ů�N��a�O�⦡�A�n�p��A�x�s
	if (space != a.npos)
	{
		vector<string> formula;//�x�s�⦡��
		stringstream ss(a);
		string tempss = "";
		while (getline(ss, tempss, ' '))//��ѿ�J�r��
			formula.push_back(tempss);
		ss.str("");
		ss.clear();
		bool Valid = checkValid(formula, a);//�ˬd&�ץ�&���Nformula�x�s���Ʀror�ܼơA���H�W��J�P�ɿ�Xĵ��
		if (Valid == false)//��J�Ʀr�˴����ųW�w
		{
			num = "0";
			name = "";
		}
		else//�⦡�p��
		{
			Compute(formula);
			string errorMessage = formula[0];
			if (!isdigit(errorMessage[0]))//�Ĥ@��s���O���~�T��
			{
				cout << errorMessage << endl;
				num = "0";
				name = "";
			}
			else//�p�⵲�G�x�s
			{
				Integer temp(formula[0]);//�⵪�װ��r��B�z
				num = temp.num;
				name = setN;
				numIntList.push_back(num);
				nameIntList.push_back(name);
			}
		}
	}
	else
	{
		string tempPN = "";
		if (a[0] == '-')//����t���M�Ʀr����
		{
			tempPN = "-";
			a = a.substr(1, a.length() - 1);
		}
		while (a[0] == '0' && a.length() > 1)//�h�e�m0
			a = a.substr(1, a.length() - 1);
		tempPN += a;
		long long int ait = tempPN.find(".");
		if (ait != tempPN.npos)//�h�p���I
			tempPN = tempPN.substr(0, ait);
		num = tempPN;
		name = setN;
		numIntList.push_back(num);
		nameIntList.push_back(name);
	}
}
Integer Integer::operator =(string a)//a�O�Ʀr(��¥Ψӭק�this���ƭ�
{
	int pos = searchIntName(this->name);//�P�B�ק�static����
	Integer temp(a);//����Ʀr���B�z(�h�e�m0&�p���I
	this->numInt = temp.numInt;
	numIntList[pos] = this->numInt;
	return *this;
}

Integer Integer::operator =(const Integer& var)//var�O�ܼ�(this���ƭȩM�W�r����
{
	int pos = searchIntName(this->name);//�P�B�ק�static����
	nameIntList[pos] = var.name;
	numIntList[pos] = var.numInt;
	this->numInt = var.numInt;
	this->name = var.name;
	return *this;
}

ostream& operator<<(ostream& strm, const Integer& c)
{
	strm << c.numInt;
	return strm;
}

istream& operator>>(istream& strm, Integer& c)
{
	string temp;
	strm >> temp;//��Jtemp�s�JInt
	c = temp;//Integer assign=
	return strm;
}

int Integer::searchIntName(string a)//��W�r�s���s�b�A�s�b�^�ǲĴX�ӡA���s�b�^��-1
{
	for (int i = 0; i < nameIntList.size(); i++)
	{
		if (a == nameIntList[i])
			return i;
	}
	return -1;//�S���
}

string Integer::searchIntValue(int pos)//�^�ǦW�r���ȡApos=-1�^��WRONG_NAME
{
	if (pos == -1)
		return "WRONG_NAME";
	return numIntList[pos];
}

void Integer::setValue(string value, int pos)
{
	numIntList[pos] = value;
}