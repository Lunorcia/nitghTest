#include "number.h"

//bool isDigit(string s) {
//	for (int i = 0; i < s.size(); i++) {
//		if (s[i] > '9' || s[i] < '0' || s[i] != '.')
//			return false;
//	}
//	return true;
//}

string number::operator +(number K)
{
	number a(num), b(K.num);
	stringstream ss_a, ss_b;
	ostringstream ss_ans;
	double db_a, db_b, db_ans;
	ss_a << a.num;
	ss_a >> db_a;
	ss_b << b.num;
	ss_b >> db_b;

	db_ans = db_a + db_b;
	ss_ans << db_ans;
	string ans = ss_ans.str();
	return ans;
};

string number::operator -(number K)
{
	number a(num), b(K.num);
	stringstream ss_a, ss_b;
	ostringstream ss_ans;
	double db_a, db_b, db_ans;
	ss_a << a.num;
	ss_a >> db_a;
	ss_b << b.num;
	ss_b >> db_b;

	db_ans = db_a - db_b;
	ss_ans << db_ans;
	string ans = ss_ans.str();
	return ans;
}

string number::operator *(number K)
{
	number a(num), b(K.num);
	stringstream ss_a, ss_b;
	ostringstream ss_ans;
	double db_a, db_b, db_ans;
	ss_a << a.num;
	ss_a >> db_a;
	ss_b << b.num;
	ss_b >> db_b;

	db_ans = db_a * db_b;
	ss_ans << db_ans;
	string ans = ss_ans.str();
	return ans;
}

string number::operator /(number K)
{
	number a(num), b(K.num);
	stringstream ss_a, ss_b;
	ostringstream ss_ans;
	double db_a, db_b, db_ans;
	ss_a << a.num;
	ss_a >> db_a;
	ss_b << b.num;
	ss_b >> db_b;

	db_ans = db_a / db_b;
	if (db_b == 0) {
		string ans = "error";
		return ans;
	}
	ss_ans << db_ans;
	string ans = ss_ans.str();
	return ans;
}

string number::operator ^(number K)
{
	number a(num), b(K.num);
	stringstream ss_a, ss_b;
	ostringstream ss_ans;
	double db_a, db_b, db_ans;
	ss_a << a.num;
	ss_a >> db_a;
	ss_b << b.num;
	ss_b >> db_b;

	db_ans = pow(db_a, db_b);
	ss_ans << db_ans;
	string ans = ss_ans.str();
	return ans;
}

string number::computeSin()
{
	number a(num);
	stringstream ss_a;
	ostringstream ss_ans;
	double db_a, db_ans;
	ss_a << a.num;
	ss_a >> db_a;
	
	db_ans = sin(db_a);
	ss_ans << db_ans;
	string ans = ss_ans.str();
	return ans;
}

string number::computeCos()
{
	number a(num);
	stringstream ss_a;
	ostringstream ss_ans;
	double db_a, db_ans;
	ss_a << a.num;
	ss_a >> db_a;

	db_ans = cos(db_a);
	ss_ans << db_ans;
	string ans = ss_ans.str();
	return ans;
}

string number::computeTan()
{
	number a(num);
	stringstream ss_a;
	ostringstream ss_ans;
	double db_a, db_ans;
	ss_a << a.num;
	ss_a >> db_a;

	db_ans = tan(db_a);
	ss_ans << db_ans;
	string ans = ss_ans.str();
	return ans;
}

bool number::operator ==(number K)
{
	if (num == K.num)
		return true;
	else
		return false;
}

bool isAllZero(string a)//常0->T Τ獶0->F  “猔種 礚跌计翴
{
	for (unsigned long long i = 0; i < a.length(); i++)
	{
		if (a[i] != '0' && a[i] != '.')
			return false;
	}
	return true;
}
bool isDec(string a) //琌计T ぃ琌计or计翴0->F
{
	for (long long i = 0; i < a.length(); i++)
	{
		if (a[i] == '.')
		{
			if (isAllZero(a.substr(i + 1, a.length() - i)))
				return false;
			else
				return true;
		}
	}
	return false;
}

bool isDecStrict(string a) //琌计T ぃ琌计->F
{
	for (long long i = 0; i < a.length(); i++)
	{
		if (a[i] == '.')
		{
			return true;
		}
	}
	return false;
}

bool isDot5(string a) //^ノ 絋粄琌秨腹 X.5
{
	long long int i;
	for (i = 0; i < a.length(); i++)
	{
		if (a[i] == '.')
			break;
	}
	if (a[i + 1] == '5')
		return true;
	else
		return false;
}