#include "Decimal.h"
Decimal::Decimal(string a) :number(a)//�~��//�S���R�W��Decimal(�i�H������
{
	long long int space = a.find(" ");//�p�G�r�꦳�Ů�N��a�O�⦡
	if (space != a.npos)
	{
		////////////////////////////////
		//a=number�p��(a);
		////////////////////////////////
	}
	string tempPN = "";
	if (a[0] == '-')//����t���M�Ʀr����
	{
		tempPN = "-";
		a = a.substr(1, a.length() - 1);
	}
	while (a[0] == '0' && a.length() > 1)
		a = a.substr(1, a.length() - 1);
	tempPN += a;

	num = tempPN;
	name = "";
}

Decimal::Decimal(string a, string setN) :number(a)//���R�W��Decimal
{
	long long int space = a.find(" ");//�p�G�r�꦳�Ů�N��a�O�⦡
	if (space != a.npos)
	{
		////////////////////////////////
		//a=number�p��(a);
		////////////////////////////////
	}
	string tempPN = "";
	if (a[0] == '-')//����t���M�Ʀr����
	{
		tempPN = "-";
		a = a.substr(1, a.length() - 1);
	}
	while (a[0] == '0' && a.length() > 1)
		a = a.substr(1, a.length() - 1);
	tempPN += a;

	num = tempPN;
	name = setN;
	numDecList.push_back(num);
	nameDecList.push_back(name);
}
Decimal Decimal::operator =(string a)/////////////a�O�Ʀr�A����Ǩ�L�ܼƦW�r�i��(��¥Ψӭק�this����
{
	int pos = searchDecName(this->name);//�P�B�ק�static����
	Decimal temp(a);//����Ʀr���B�z(�h�e�m0
	this->numDec = temp.numDec;
	numDecList[pos] = this->numDec;
	return *this;
}

ostream& operator<<(ostream& strm, const Decimal& c)
{
	strm << c.numDec;
	return strm;
}

istream& operator>>(istream& strm, Decimal& c)
{
	string temp;//////////////��Jtemp�O�Ʀr
	strm >> temp;//��Jtemp�s�JDec
	c = temp;//assign=
	return strm;
}

int Decimal::searchDecName(string a)//��W�r�s���s�b�A�s�b�^�ǲĴX�ӡA���s�b�^��-1
{
	for (int i = 0; i < nameDecList.size(); i++)
	{
		if (a == nameDecList[i])
			return i;
	}
	return -1;//�S���
}

string Decimal::searchDecValue(int pos)//�^�ǦW�r���ȡApos=-1�^��WRONG_NAME
{
	if (pos == -1)
		return "WRONG_NAME";
	return numDecList[pos];
}