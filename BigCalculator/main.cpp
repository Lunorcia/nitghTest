#include "number.h"
int main()
{
	string str1("a"), str2;
	while (cin >> str1 && str1 != "-1")
	{
		cin >> str2;
		number num1(str1), num2(str2);
		cout  << num1 / num2 << endl;//<< num1 + num2 << endl << num1 - num2 << endl
	}
	
}