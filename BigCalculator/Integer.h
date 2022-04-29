#pragma once
#include "number.h"
class Integer:public number
{
public:
	Integer(string a);//�~��
	Integer(string a,string setN);
	static int searchIntName(string a);//��W�r�s���s�b�A�s�b�^�ǲĴX�ӡA���s�b�^��-1
	static string searchIntValue(int pos);//�^�ǦW�r���ȡApos=-1�^��WRONG_NAME
	static void setValue(string value, int pos);

	Integer operator =(string a);//a�O�Ʀr(��¥Ψӭק�this���ƭ�
	Integer operator =(const Integer& var);//var�O�ܼ�(this���ƭȩM�W�r����

	friend ostream& operator<<(ostream& strm, const Integer& c);
	friend istream& operator>>(istream& strm, Integer& c);
private:
	string numInt;
	string name;
	static vector<string>numIntList;
	static vector<string>nameIntList;
};
vector<string>Integer::numIntList;
vector<string>Integer::nameIntList;