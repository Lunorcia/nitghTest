#include "Parser.h"
#include "number.h"

int main()
{
	vector<Parser> parser;
	string input;
	Parser p;
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
			parser.push_back(p);
			p.~Parser();
		}
		else{
			p.setEquationPart(input);
		}

	}
}