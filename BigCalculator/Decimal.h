#pragma once
#include "number.h"
class Decimal :public number
{
public:
	Decimal(string a);//�~��
	Decimal(string a, string setN);
	static int searchDecName(string a);//��W�r�s���s�b�A�s�b�^�ǲĴX�ӡA���s�b�^��-1
	static string searchDecValue(int pos);//�^�ǦW�r���ȡApos=-1�^��WRONG_NAME
	static void setValue(string value, int pos);

	Decimal operator =(string a);//a�O�Ʀr(��¥Ψӭק�this���ƭ�
	Decimal operator =(const Decimal& var);//var�O�ܼ�(this���ƭȩM�W�r����

	friend ostream& operator<<(ostream& strm, const Decimal& c);
	friend istream& operator>>(istream& strm, Decimal& c);
private:
	string numDec;
	string name;
	static vector<string>numDecList;
	static vector<string>nameDecList;
};
