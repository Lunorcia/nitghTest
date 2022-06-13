#include "Parser.h"

bool isDigit(string s) {
	for (int i = 0; i < s.size(); i++) {
		if ((s[i] > '9' || s[i] < '0') && s[i] != '.')
			return false;
	}
	return true;
}

bool isInConstructVariable(vector<string> cv, string v) {
	for (int i = 0; i < cv.size(); i++) {
		if (cv[i] == v)
			return true;
	}
	return false;
}

int existAxisXOrY(vector<string> variableNameList, vector<vector<string>> constructVariable) {//都不存在：-1, 存在x：0, 存在y：1, 兩者都存在：2
	bool haveX = false;
	bool haveY = false;
	for (int i = 0; i < variableNameList.size(); i++) {
		if (variableNameList[i] == "x") {
			haveX = true;
			continue;
		}
		else if (variableNameList[i] == "y") {
			haveY = true;
			continue;
		}
		for (int j = 0; j < constructVariable[i].size(); j++) {
			if (constructVariable[i][j] == "x") {
				haveX = true;
				continue;
			}
			else if (constructVariable[i][j] == "y") {
				haveY = true;
				continue;
			}
		}
	}

	if (haveX == true && haveY == true) {
		return 2;
	}
	else if (haveX == true && haveY == false) {
		return 0;
	}
	else if (haveX == false && haveY == true) {
		return 1;
	}
	else if (haveX == false && haveY == false) {
		return -1;
	}
}

Parser::Parser() {

}

int Parser::searchVariableName(string a) {
	for (int i = 0; i < variableNameList.size(); i++) {
		if (variableNameList[i] == a)
			return i;
	}
	return -1;
}

bool Parser::checkDefinedVariable(vector<string> cv) { //算式中除了x和y，存在未定義變數
	for (int i = 0; i < cv.size(); i++) {
		int pos = searchVariableName(cv[i]);
		if (pos == -1 && cv[i] != "x" && cv[i] != "y") {
			return false;
		}
	}
	return true;
}

bool Parser::checkLoopDefinedVariable() { //循環定義變數
	for (int i = 0; i < variableNameList.size(); i++) {
		for (int j = i + 1; j < variableNameList.size(); j++) {
			if (isInConstructVariable(constructVariable[i], variableNameList[j]) == true && isInConstructVariable(constructVariable[j], variableNameList[i]) == true)
				return false;
		}
	}
	return true;
}

void Parser::setEquationPart(string input) { //儲存等式
	equationPart.push_back(input);//儲存原始等式
	vector<string> formula;
	stringstream ss(input);
	string tempss = "";
	while (getline(ss, tempss, ' '))//拆解輸入字串
		formula.push_back(tempss);
	string variableName;
	if (formula.size() > 2 && formula[1] == "=") //如果第二個字串是等號
	{
		variableName = formula[0];
		variableNameList.push_back(variableName); //儲存變數
		formula.erase(formula.begin(), formula.begin() + 2); //刪除變數和去等號
		input = input.substr(variableName.length() + 3, input.length() - 3 - variableName.length()); //原始字串要跟著修改(checkValid用)
	}

	bool valid = checkValid(formula, input); //檢查&修正&取代formula儲存的數字or變數，有違規輸入同時輸出警示
	if (valid == false) //輸入數字檢測不符規定
		input = "error";
	else {
		vector<string> bv;//儲存構成新變數的變數們
		for (int i = 0; i < formula.size(); i++) {
			if (formula[i] != "(" && formula[i] != ")" && formula[i] != "+" && formula[i] != "-" && formula[i] != "*" && formula[i] != "/" && formula[i] != "^" &&
				formula[i] != "sin" && formula[i] != "cos" && formula[i] != "tan" && formula[i] != "sin(" && formula[i] != "cos(" && formula[i] != "tan(") {
				if (isDigit(formula[i]) == false)
					bv.push_back(formula[i]);
			}
		}
		constructVariable.push_back(bv);
		if (checkDefinedVariable(bv) == false) //存在未定義變數
			input = "error";
	}
	variableFormulaList.push_back(input); //儲存算式
	return;
}

void Parser::computeAllEquation() {
	for (int i = 0; i < variableNameList.size(); i++) {
		if (checkBracket(variableNameList[i]) == false && checkOperator(variableNameList[i]) == false) {
			cout << "變數名稱錯誤" << endl;
			return;
		}
	}
	for (int i = 0; i < variableFormulaList.size(); i++) {
		if (variableFormulaList[i] == "error") {
			cout << "存在錯誤，不可運算" << endl;
			return;
		}
	}
	if (checkLoopDefinedVariable() == false) {
		cout << "循環定義變數，不可運算" << endl;
		return;
	}
	/*cout << "成功" << endl;*/
	//vector<string> vnl, vfl;
	//vector<vector<string>> cv;
	//for (int i = 0; i < variableNameList.size(); i++) {
	//	int pos = searchVariableName(variableNameList[i]);
	//	if (pos == -1) {
	//		vnl.push_back(variableNameList[i]);
	//		vfl.push_back(variableFormulaList[i]);
	//	}
	//	else {
	//		vnl[pos].clear();
	//		vfl[pos].clear();
	//		vnl.push_back(variableNameList[i]);
	//		vfl.push_back(variableFormulaList[i]);
	//		////
	//	}
	//}
	//variableNameList = vnl;
	//variableFormulaList = vfl;
	

	for (double d = 0; d < 20; d += 1) {
		vector<string> formula;
		string tempFormula = variableFormulaList[0];
		stringstream ss(tempFormula);
		string tempss = "";
		while (getline(ss, tempss, ' '))//拆解輸入字串
			formula.push_back(tempss);
		x.push_back(d);
		for (int i = 0; i < formula.size(); i++) {
			if (formula[i] == "x") {
				string sd;
				stringstream ssd;
				ssd << d;
				ssd >> sd;
				formula[i].replace(formula[i].find("x"), 1, sd);
			}
		}
		compute(formula);
		string sans = formula[0];
		double ans;
		stringstream ssans;
		ssans << sans;
		ssans >> ans;
		y.push_back(ans);
	}
}

void Parser::getAxisVector() {
	for (int i = 0; i < x.size(); i++) {
		cout << x[i] << " " << y[i] << endl;
	}
}