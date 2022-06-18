//#include "parser.h"
#include "viewer.h"
//viewer裡有parser.h了
//static
vector<pair<string,vector<string>>> Parser::variableList(11); //最多10個([1]~[10],[0]no use)
vector<string> Parser::variableFormulaList(11); //設定變數的等式

Parser::Parser(){
    //x.fill(0.0,8000);//填入8000個0
    //y.fill(0.0,8000);//填入8000個0
    needDraw=false;
}

Parser::Parser(int num){
    //x.fill(0.0,8000);//填入8000個0
    //y.fill(0.0,8000);//填入8000個0
    textLineNumber=num;
    needDraw=false;
}

void Parser::process(){//暫定總處理函式
    //清除上一次設置的變數和方程式
    variableList[textLineNumber].first = "";//vector型態用空值清除上一次的設置會報錯,改用clear()會清空元素,但保留內存空間
    variableFormulaList[textLineNumber] = "";//vector型態用空值清除上一次的設置會報錯,改用clear()會清空元素,但保留內存空間
//    variableList[textLineNumber].second.clear();
    //進入算式處理
    setEquationPart(Viewer::equationInput[textLineNumber].toStdString());
    if (variableList[textLineNumber].first == "y" || variableList[textLineNumber].first == "x")
        computeAllEquation();
}


int Parser::searchVariableName(string a) {
    for (int i = 0; i < variableList.size(); i++) {
        if (variableList[i].first == a)
            return i;
    }
    return -1;
}

bool Parser::checkDefinedVariable() {
    for (int i = 0; i < variableList[textLineNumber].second.size(); i++) {
        if (variableList[textLineNumber].second[i] == "x" || variableList[textLineNumber].second[i] == "y")
            continue;
        int pos = searchVariableName(variableList[textLineNumber].second[i]);
        if (pos > textLineNumber && pos == -1)
            return false;
    }
    return true;
}

bool Parser::checkLoopDefinedVariable(vector<int> relatedTextLineNumber) {
    for (int i = 0; i < relatedTextLineNumber.size(); i++) {
        if (variableList[relatedTextLineNumber[i]].first == "x" || variableList[relatedTextLineNumber[i]].first == "y")
            continue;
        for (int j = i + 1; j < relatedTextLineNumber.size(); j++) {
            if (isInConstructVariable(variableList[relatedTextLineNumber[i]].second, variableList[relatedTextLineNumber[j]].first) == true && isInConstructVariable(variableList[relatedTextLineNumber[j]].second, variableList[relatedTextLineNumber[i]].first) == true)
                return false;
        }
    }
    return true;
}

void Parser::setEquationPart(string input) {
    input.erase(remove(input.begin(), input.end(), ' '), input.end());
    vector<string> formula;
    string s;
    for (int i = 0; i < input.size(); i++){
        s += input[i];
        if (s == "=" || s == "(" || s == ")" || s == "+" || s == "-" || s == "*" || s == "/" || s == "^" || s == "sin(" || s == "cos(" || s == "tan("){
            formula.push_back(s);
            s.clear();
        }
        else if (((input[i + 1] < '0' || input[i + 1] > '9') && input[i + 1] != '.') && isDigit(s) == true){

            formula.push_back(s);
            s.clear();
        }
        else if(s == "x"|| s == "y") {
            formula.push_back(s);
            s.clear();
        }
        else if ((s == "sin" || s == "cos" || s == "tan") && input[i + 1] == '('){
            continue;
        }
        else if (input[i + 1] == '=' || input[i + 1] == '(' || input[i + 1] == ')' || input[i + 1] == '+' || input[i + 1] == '-' || input[i + 1] == '*' || input[i + 1] == '/' || input[i + 1] == '^'){
            formula.push_back(s);
            s.clear();
        }

        if(i == input.size() - 1){
            formula.push_back(s);
            s.clear();
        }
    }
    for (int i = 0; i < formula.size(); i++){
        if (formula[i] == "")
            formula.erase(formula.begin() + i);
    }

    string variableName;
    if (formula.size() > 2 && formula[1] == "="){
        variableName = formula[0];
        variableList[textLineNumber].first=variableName;
        formula.erase(formula.begin(), formula.begin() + 2);
        input.erase(0, variableName.size()+1);
    }
    else{
        return;
    }

    for (int i = formula.size()-1; i > 0; i--){
        if (isDigitWithPN(formula[i]) == true){
            if (formula[i-1] == "+" || formula[i-1] == "-") {
                if (i-1 == 0){
                    formula[i-1].append(formula[i]);
                    formula.erase(formula.begin() + i);
                    mergePN(formula[i-1]);
                    break;
                }
                else{
                    if (formula[i-2] == "(" || formula[i-2] == "+" || formula[i-2] == "-" || formula[i-2] == "sin(" || formula[i-2] == "cos(" || formula[i-2] == "tan("){
                        //(formula[i-2][formula[i-2].size()-1] >= '0' && formula[i-2][formula[i-2].size()-1] <= '9') ||
                        //formual[i]的前一個字元是+或- 前前一個字元是=(+-*/^ sin( cos( tan( 或是剛好i-2為第一個字元 "右括號不算"
                        formula[i-1].append(formula[i]);
                        formula.erase(formula.begin() + i);
                        mergePN(formula[i-1]);
                    }
                }
            }
        }
    }
    string temp;//存取校正正負號的input
    for (int i = 0; i < formula.size(); i++){
        temp.append(formula[i]);
    }
    input = temp;

    if (checkBracket(input) == false)
        input = "error";
    if (checkOperator(input) == false)
        input = "error";
    bool valid = checkValid(formula);
    if (valid == false)
        input = "error";

    if (input == "error"){
        variableList[textLineNumber].second.push_back("error");
    }
    else{
        vector<string> cv;
        for (int i = 0; i < formula.size(); i++){
            if (formula[i] != "(" && formula[i] != ")" && formula[i] != "+" && formula[i] != "-" && formula[i] != "*" && formula[i] != "/" && formula[i] != "^" && formula[i] != "sin(" && formula[i] != "cos(" && formula[i] != "tan(" && isDigit(formula[i]) == false)
                cv.push_back(formula[i]);
        }
        variableList[textLineNumber].second = cv;
        if (checkDefinedVariable() == false){
            variableList[textLineNumber].second.clear();
            variableList[textLineNumber].second.push_back("error");
            input = "error";
        }
    }
    variableFormulaList[textLineNumber] = input;
}

void Parser::computeAllEquation() {
    vector<int> relatedTextLineNumber;
    for (int i = 0; i <= textLineNumber; i++) {
        if (i == textLineNumber) {
            if (variableFormulaList[i] == "error")
                return;
            relatedTextLineNumber.push_back(i);
        }
        else {
            if (variableList[i].first != "x" && variableList[i].first != "y" ) {
                if (variableList[i].second.size() == 0 || isInConstructVariable(variableList[textLineNumber].second, variableList[i].first) == true) {
                    if (variableFormulaList[i] == "error")
                        return;
                    int e = false;
                    for (int j = 0; j < relatedTextLineNumber.size(); j++) {
                        if (variableList[i].first == variableList[relatedTextLineNumber[j]].first) {
                            e = true;
                            relatedTextLineNumber[j] = i;
                            break;
                        }
                    }
                    if (e == false)
                        relatedTextLineNumber.push_back(i);
                }
            }
        }
    }
    if (checkLoopDefinedVariable(relatedTextLineNumber) == false)
        return;

    vector<vector<string>> allFormula;
    vector<string> formula;
    string s;
    for (int r = 0; r < relatedTextLineNumber.size(); r++) {
        for (int i = 0; i < variableFormulaList[relatedTextLineNumber[r]].size(); i++) {
            s += variableFormulaList[relatedTextLineNumber[r]][i];
            if (s == "=" || s == "(" || s == ")" || s == "+" || s == "-" || s == "*" || s == "/" || s == "^" || s == "sin(" || s == "cos(" || s == "tan(") {
                formula.push_back(s);
                s.clear();
            }
            else if (s == "x" && variableList[relatedTextLineNumber[r]].first == "y") {
                formula.push_back(s);
                s.clear();
            }
            else if (s == "y" && variableList[relatedTextLineNumber[r]].first == "x") {
                formula.push_back(s);
                s.clear();
            }
            else if (((variableFormulaList[relatedTextLineNumber[r]][i + 1] < '0' || variableFormulaList[relatedTextLineNumber[r]][i + 1] > '9') && variableFormulaList[relatedTextLineNumber[r]][i + 1] != '.') && isDigit(s) == true) {
                formula.push_back(s);
                s.clear();
            }
            else if ((s == "sin" || s == "cos" || s == "tan") && variableFormulaList[relatedTextLineNumber[r]][i + 1] == '(') {
                continue;
            }
            else if (variableFormulaList[relatedTextLineNumber[r]][i + 1] == '=' || variableFormulaList[relatedTextLineNumber[r]][i + 1] == '(' || variableFormulaList[relatedTextLineNumber[r]][i + 1] == ')' || variableFormulaList[relatedTextLineNumber[r]][i + 1] == '+' || variableFormulaList[relatedTextLineNumber[r]][i + 1] == '-' || variableFormulaList[relatedTextLineNumber[r]][i + 1] == '*' || variableFormulaList[relatedTextLineNumber[r]][i + 1] == '/' || variableFormulaList[relatedTextLineNumber[r]][i + 1] == '^') {
                formula.push_back(s);
                s.clear();
            }
            if (i == variableFormulaList[relatedTextLineNumber[r]].size() - 1) {
                formula.push_back(s);
                s.clear();
            }
        }
        for (int i = 0; i < formula.size(); i++) {
            if (formula[i] == "")
                formula.erase(formula.begin() + i);
        }
        allFormula.push_back(formula);
        formula.clear();
    }

    for (int i = 0; i < relatedTextLineNumber.size(); i++) {
        for (int j = i + 1; j < relatedTextLineNumber.size(); j++) {
            if (isInConstructVariable(variableList[relatedTextLineNumber[j]].second, variableList[relatedTextLineNumber[i]].first) == true) {
                for (int w = 0; w < allFormula[j].size(); w++) {
                    if (variableList[relatedTextLineNumber[i]].first == allFormula[j][w]) {
                        allFormula[j][w] = "(";
                        allFormula[j].insert(allFormula[j].begin() + w + 1, ")");
                        allFormula[j].insert(allFormula[j].begin() + w + 1 , allFormula[i].begin(), allFormula[i].end());
                    }
                }
            }
        }
    }

    int exist = existAxisXOrY();
    if (exist == -1)
        return;

    needDraw = true;
    double d = -9999;
    while(d <= 10000) {
        vector<string> replaceFormula = allFormula[allFormula.size() - 1];
        if (exist == 0 && variableList[textLineNumber].first == "x") {
            y.push_back(d);
            x.push_back(compute(replaceFormula));
        }
        else if (exist == 1 && variableList[textLineNumber].first == "y") {
            x.push_back(d);
            y.push_back(compute(replaceFormula));
        }
        else if (exist == 2) {
            if (variableList[textLineNumber].first == "y") {
                x.push_back(d);
                for (int i = 0; i < replaceFormula.size(); i++) {
                    if (replaceFormula[i] == "x") {
                        string sd;
                        stringstream ssd;
                        ssd << d;
                        ssd >> sd;
                        replaceFormula[i].replace(replaceFormula[i].find("x"), 1, sd);
                    }
                }
                y.push_back(compute(replaceFormula));
            }
            else if (variableList[textLineNumber].first == "x"){
                y.push_back(d);
                for (int i = 0; i < replaceFormula.size(); i++){
                    if (replaceFormula[i] == "y") {
                        string sd;
                        stringstream ssd;
                        ssd << d;
                        ssd >> sd;
                        replaceFormula[i].replace(replaceFormula[i].find("y"), 1, sd);
                    }
                }
                x.push_back(compute(replaceFormula));
            }
        }
        d+=0.1;
    }

}

double Parser::compute(vector<string> formula) {
    double ans = 0;

//    for (int i = 0; i < formula.size(); i++) {
//         if (isDigit(formula[i]) == true && formula[i - 1] == "(" && formula[i + 1] == ")") {
//             formula.erase(formula.begin() + i - 1);
//             formula.erase(formula.begin() + i);
//             i--;
//         }
//     }

    if (formula.size() == 1){
        ans = stringToDouble(formula[0]);
        return ans;
    }
    while (formula.size() > 1 || (formula.size() == 3 && formula[1] == "/")){
        int found1 = -1;
        int found2 = -1;
        string leftBracket = "";
        for (int i = 0; i < formula.size(); i++){
            if (formula[i] == "(" || formula[i] == "sin(" || formula[i] == "cos(" || formula[i] == "tan(") {
                found1 = i;
                leftBracket = formula[i];
            }
        }
        for (int i = found1 + 1; i < formula.size(); i++){
            if (formula[i] == ")"){
                found2 = i;
                break;
            }
        }

        if (found1 != -1 && found2 != -1 && found1 < found2){
            if (found1 + 1 == found2)
                return NAN;
        }
        else {
            found1 = -1;
            found2 = formula.size();
        }
        for (int i = found2 - 1; i > found1; i--){
            if (formula[i] == "^" && i != found1 + 1){
                double temp = stringToDouble(formula[i - 1]);
                if (stringToDouble(formula[i + 1]) < 0)
                    return NAN;
                else {
                    temp = pow(temp, stringToDouble(formula[i + 1]));
                    formula[i - 1] = doubleToString(temp);
                    formula.erase(formula.begin() + i, formula.begin() + i + 2);
                    found2 -= 2;
                    i--;
                }
            }
        }

        for (int i = found1 + 1; i < found2; i++){
            if (formula[i] == "/"){
                if (stringToDouble(formula[i + 1]) == 0){
                    return NAN;
                }
                else {
                    double temp = stringToDouble(formula[i - 1]) / stringToDouble(formula[i + 1]);
                    formula[i - 1] = doubleToString(temp);
                    formula.erase(formula.begin() + i, formula.begin() + i + 2);
                    found2 -= 2;
                    i -= 2;
                }
            }
            else if (formula[i] == "*") {
                double temp = stringToDouble(formula[i - 1]) * stringToDouble(formula[i + 1]);
                formula[i - 1] = doubleToString(temp);
                formula.erase(formula.begin() + i, formula.begin() + i + 2);
                found2 -= 2;
                i--;
            }
        }

        for (int i = found1 + 1; i < found2; i++){
            if (i == found1 + 1 && formula[i] == "+"){
                formula[i] = formula[1];
                i++;
            }
            else if (i == found1 + 1 && formula[i] == "-"){
                formula[i] = doubleToString(0 - stringToDouble(formula[i + 1]));
                i++;
            }
            if (formula[i] == "+"){
                formula[found1+1] = doubleToString(stringToDouble(formula[found1+1]) + stringToDouble(formula[i + 1]));
                i++;
            }
            else if (formula[i] == "-"){
                formula[found1+1] = doubleToString(stringToDouble(formula[found1+1]) - stringToDouble(formula[i + 1]));
                i++;
            }
        }

        if (found1 == -1){
            formula.erase(formula.begin() + 1, formula.end());
            if (leftBracket == "sin(")
                formula[0] = doubleToString(sin(stringToDouble(formula[0])));
            else if (leftBracket == "cos(")
                formula[0] = doubleToString(cos(stringToDouble(formula[0])));
            else if (leftBracket == "tan(")
                formula[0] = doubleToString(tan(stringToDouble(formula[0])));
            ans = stringToDouble(formula[0]);
            return ans;
        }
        else{
            formula[found1] = formula[found1 + 1];
            formula.erase(formula.begin() + found1 + 1, formula.begin() + found2 + 1);
            if (leftBracket == "sin(")
                formula[found1] = doubleToString(sin(stringToDouble(formula[found1])));
            else if (leftBracket == "cos(")
                formula[found1] = doubleToString(cos(stringToDouble(formula[found1])));
            else if (leftBracket == "tan(")
                formula[found1] = doubleToString(tan(stringToDouble(formula[found1])));
            if(formula.size()==1){
                ans = stringToDouble(formula[0]);
                return ans;
            }
        }
    }
    return ans;
}

int Parser::existAxisXOrY(){
    bool haveX = false;
    bool haveY = false;
    if (variableList[textLineNumber].first == "x")
        haveX = true;
    if (variableList[textLineNumber].first == "y")
        haveY = true;
    for (int i = 0; i <= textLineNumber; i++) {
        for (int j = 0; j < variableList[i].second.size(); j++) {
            if (variableList[i].second[j] == "x")
                haveX = true;
            if (variableList[i].second[j] == "y")
                haveY = true;
        }
    }

    if (haveX == true && haveY == true)
        return 2;
    else if (haveX == true && haveY == false)
        return 0;
    else if (haveX == false && haveY == true)
        return 1;
    else if (haveX == false && haveY == false)
        return -1;
    return -1;
}

bool checkBracket(const string& line){
    if (line == "error")
            return false;
    int countP = 0;
    int countN = 0;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == '(')
            countP++;
        else if (line[i] == ')')
            countN++;
        if (countN > countP)
            return false;
    }
    if (countP != countN)
        return false;
    return true;
}


bool checkOperator(const string& line){
    if (line == "error")
        return false;

    vector<string> formula;
    string s = "";
    for (int i = 0; i < line.size(); i++){
        s += line[i];
        if (s == "=" || s == "(" || s == ")" || s == "+" || s == "-" || s == "*" || s == "/" || s == "^" || s == "sin(" || s == "cos(" || s == "tan("){
            formula.push_back(s);
            s.clear();
        }
        else if (((line[i + 1] < '0' || line[i + 1] > '9') && line[i + 1] != '.') && isDigit(s) == true){
            formula.push_back(s);
            s.clear();
        }
        else if ((s == "sin" || s == "cos" || s == "tan") && line[i + 1] == '('){
            continue;
        }
        else if (line[i + 1] == '=' || line[i + 1] == '(' || line[i + 1] == ')' || line[i + 1] == '+' || line[i + 1] == '-' || line[i + 1] == '*' || line[i + 1] == '/' || line[i + 1] == '^'){
            formula.push_back(s);
            s.clear();
        }
        if (i == line.size() - 1){
            formula.push_back(s);
            s.clear();
        }
    }
    for (int i = 0; i < formula.size(); i++) {
        if (formula[i] == "")
        formula.erase(formula.begin() + i);
    }

    string previous = "";
    string now = "";
    for(int i = 0; i < formula.size(); i++){
        now = formula[i];
        if (now == "+" || now == "-"){
            if (previous == "*" || previous == "/" || previous == "^" || previous == "="){
                return false;
            }
        }
        else if (now == "*" || now == "/" || now == "^" || now == "="){
            if (previous == "+" || previous == "-" || previous == "*" || previous == "/" || previous == "^" || previous == "=" || previous == "(" || previous == "sin(" || previous == "cos(" || previous == "tan("){
                return false;
            }
        }
        if (now == ")") {
            if (previous == "(" || previous == "sin(" || previous == "cos(" || previous == "tan(")
                return false;
        }
        previous = now;
    }
    return true;
}

bool checkDPs(const string& num){
    int it = num.find('.');
    if (it != num.npos){
        it = num.find('.', it + 1);
        if (it != num.npos)
            return false;
    }
    return true;
}

void mergePN(string& num){
    int N = 0, c = 0;
    for (int i = 0;i < num.size(); i++){
        if (num[i] == '-')
            N++;
        if (num[i] != '+' && num[i] != '-')
            break;
        c++;
    }
    num.erase(0,c);
    if (N % 2 == 1){
        num.insert(0,1,'-');
    }
}

bool checkValid(vector<string>& formula){
    for (int i = 0; i < formula.size(); i++){
        string temp = formula[i];
        if (temp == "(" || temp == ")" || temp == "+" || temp == "-" || temp == "*" || temp == "/" || temp == "^" || temp == "sin(" || temp == "cos(" || temp == "tan(")
            continue;
        if (!checkDPs(temp))
            return false;
        formula[i] = temp;
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

bool isDigit(string s){
    for (int i = 0; i < s.length(); i++) {
        if ((s[i] > '9'|| s[i] < '0') && (s[i] != '.'))
            return false;
    }
    return true;
}

bool isDigitWithPN(string s){
    for (int i = 0; i < s.length(); i++){
        if ((s[i] > '9'|| s[i] < '0') && (s[i] != '.') && (s[i] != '+') && (s[i] != '-'))
            return false;
    }
    return true;
}

double stringToDouble(string s) {
    stringstream ss;
    double d;
    ss << s;
    ss >> d;
    return d;
}

string doubleToString(double d) {
    stringstream ss;
    string s;
    ss << d;
    ss >> s;
    return s;
}

