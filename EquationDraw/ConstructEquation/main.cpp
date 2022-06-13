#include "Parser.h"

int main()
{
	vector<Parser> parser;
	string input;
	Parser p;
	while (getline(cin, input))
	{
		if (input == "OK") {
			//for (int i = 0; i < p.variableFormulaList.size(); i++) {
			//	cout << p.variableNameList[i] << endl;
			//	/*cout << p.variableFormulaList[i] << endl;*/
			//}
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