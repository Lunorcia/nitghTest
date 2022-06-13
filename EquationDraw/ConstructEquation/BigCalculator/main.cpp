#include "Parser.h"
#include "number.h"

int main()
{
	Parser p;
	string input;
	while (getline(cin, input))
	{
		/*number a(inputA);*/
		/*cout << a.computeSin() << endl;
		cout << a.computeCos() << endl;
		cout << a.computeTan() << endl;*/
		/*cout << a + b << endl;
		cout << a - b << endl;
		cout << a * b << endl;
		string exp = a ^ b;
		cout << exp << endl;
		cout << a / b << endl;*/
		if (input == "OK") {
			for (int i = 0; i < p.variableFormulaList.size(); i++) {
				cout << p.variableNameList[i] << endl;
				cout << p.variableFormulaList[i] << endl;
			}
			p.computeAllEquation();
			p.getAxisVector();
		}
		else{
			p.setEquationPart(input);
		}
	}
}