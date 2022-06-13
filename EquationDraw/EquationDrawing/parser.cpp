//#include "parser.h"
#include "viewer.h" //viewer裡有parser.h了
//static
vector<pair<string,vector<string>>> Parser::variableList(11);//最多10個([1]~[10],[0]no use)
vector<string> Parser::variableNameList(11);//變數名稱陣列
vector<string> Parser::variableFormulaList(11);//設定變數的等式

Parser::Parser()
{
    x.fill(0.0,8000);//填入8000個0
    y.fill(0.0,8000);//填入8000個0
    equationPart.clear();
    needDraw=false;
}

Parser::Parser(int num)
{
    x.fill(0.0,8000);//填入8000個0
    y.fill(0.0,8000);//填入8000個0
    equationPart.clear();
    textLineNumber=num;
    needDraw=false;
}

void Parser::process()//暫定總處理函式
{
    //清除上一次設置的變數和方程式
    variableNameList[textLineNumber]="";
    variableFormulaList[textLineNumber]="";
    /*進入算式處理
     * setEquationPart(Viewer::equationInput[textLineNumber].toStdString());*/
    return;
}


int Parser::searchVariableName(string a) {
    for (int i = 0; i < variableNameList.size(); i++) {
        if (variableNameList[i] == a)
            return i;
    }
    return -1;
}

bool checkBracket(const string& line)//檢查左右括弧是否合法
{
    int countP = 0, countN = 0;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == '(')
            countP++;
        else if (line[i] == ')')
            countN++;
        if (countN > countP) { //檢查左右括弧順序是否相反
            return false;
        }
    }
    if (countP != countN) //檢查左右括弧數量是否一樣
        return false;
    return true;
}

bool checkOperator(const string& line)//連續運算符 +*-/^單獨空格的才算(依空格拆解字串，字串長度為1的才是運算符)
{
    string previous = "", now = "";//紀錄前一個，以及當前的字
        stringstream ss(line);
        while (getline(ss, now, ' ')) //空格拆解字串
        {
            if (now == "+" || now == "-" || now == "*" || now == "/" || now == "^" || now == "=")
            {
                if (previous == "+" || previous == "-" || previous == "*" || previous == "/" || previous == "^" || previous == "=" || previous == "(")
                    return false;
            }
            //if (previous == "sin" || previous == "cos" || previous == "tan") { //sin、cos、tan和左括號""有""間隔，確認附帶左括號!
            //	if (now != "(")
            //		return false;
            //}
            if (now == ")") { //括號內是空的
                if (previous == "(" || previous == "sin(" || previous == "cos(" || previous == "tan(") //sin、cos、tan和括號""沒有""間隔
                    return false;
            }
            previous = now;
        }
        return true;
}

bool checkDPs(const string& num)//多重小數點
{
    int it = num.find('.');
    if (it != num.npos)//有小數點
    {
        it = num.find('.', it + 1);//找有沒有第二個小數點
        if (it != num.npos)
            return false;
    }
    //如果找不到or只找到一個小數點 回傳true
    return true;
}

bool negativeRoot(const string& num)//負數不能開根號
{
    if (num[0] == '-')
        return false;
    return true;
}

void mergePN(string& num)
{
    int P = 0, N = 0, c = 0;
    while (num[c] == '+' || num[c] == '-')
    {
        if (num[c] == '+')
            P++;
        if (num[c] == '-')
            N--;
        c++;
    }
    if (P + N < 0 && abs(P + N) % 2 == 1)//正負合併結果是負
    {
        num = "-" + num.substr(c, num.length() - c);//只留負號
        if (num[1] == '.')//例如-.2
            num = "-0" + num.substr(1, num.length() - 1);//補前置0>>-0.2
    }
    else//結果是正，把正負號全拿掉
    {
        num = num.substr(c, num.length() - c);
        if (num[0] == '.')//例如 .52
            num = "0" + num;//補前置0>>0.52
    }
}

bool checkValid(vector<string>& formula)//檢查&修正&取代formula儲存的數字or變數，有違規輸入同時輸出警示
{
    for (int i = 0; i < formula.size(); i++)
    {
        //移除前置0的處理寫到class number的construct裡了，把字串存成數字時自動做
        string temp = formula[i];
        if (temp == "(" || temp == ")" || temp == "+" || temp == "-" || temp == "*" || temp == "/" || temp == "^" || temp == "sin(" || temp == "cos(" || temp == "tan(")//一般運算子不用處理
            continue;
        mergePN(temp);//正負號整合(如果有小數點沒有前置0也會補上)
        if (!checkDPs(temp))//數字有複數個小數點
        {
            //cout << "小數點輸入錯誤" << endl;
            return false;
        }
        formula[i] = temp;//檢測正確，把正負號整合完的值結果存回formula
    }
    return true;//輸入數字檢測符不符規定
}

bool isInConstructVariable(vector<string> cv, string v) {
    for (int i = 0; i < cv.size(); i++) {
        if (cv[i] == v)
            return true;
    }
    return false;
}

int existAxisXOrY(vector<string> variableNameList, vector<vector<string>> constructVariable)//都不存在：-1, 存在x：0, 存在y：1, 兩者都存在：2
{
    bool haveX = false;
    bool haveY = false;
    for (int i = 0; i < variableNameList.size(); i++) {
        if (variableNameList[i] == "x") {
            haveX = true;
        }
        if (variableNameList[i] == "y") {
            haveY = true;
        }
    }
    for (int i = 0; i < constructVariable.size(); i++) {
        for (int j = 0; j < constructVariable[i].size(); j++) {
            if (constructVariable[i][j] == "x") {
                haveX = true;
            }
            if (constructVariable[i][j] == "y") {
                haveY = true;
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
    input.erase(remove(input.begin(), input.end(), ' '), input.end());
    vector<string> formula;
    string s = "";
    for (int i = 0; i < input.size(); i++)
    {
        s += input[i];
        if (s == "=" || s == "(" || s == ")" || s == "+" || s == "-" || s == "*" || s == "/" || s == "^" || s == "sin(" || s == "cos(" || s == "tan(")
        {
            formula.push_back(s);
            s.clear();
        }
        else if (((input[i + 1] < '0' || input[i + 1] > '9') && input[i + 1] != '.') && isDigit(s) == true)
        {//數字
            formula.push_back(s);
            s.clear();
        }
        else if ((s == "sin" || s == "cos" || s == "tan") && input[i + 1] == '(')
        {
            continue;
        }
        else if (input[i + 1] == '=' || input[i + 1] == '(' || input[i + 1] == ')' || input[i + 1] == '+' || input[i + 1] == '-' || input[i + 1] == '*' || input[i + 1] == '/' || input[i + 1] == '^')
        { //變數
            formula.push_back(s);
            s.clear();
        }
        if (i == input.size() - 1)
        {
            formula.push_back(s);
            s.clear();
        }
    }
    formula.erase(formula.begin() + formula.size()-1);/*刪除getline造成的多餘空格(endl)*/
    /*for (int i = 0; i < formula.size(); i++) {
        cout << formula[i] << endl;
    }*/

    string variableName;
    if (formula.size() > 2 && formula[1] == "=") //如果第二個字串是等號
    {
        variableName = formula[0];
        variableNameList.push_back(variableName); //儲存變數
        formula.erase(formula.begin(), formula.begin() + 2); //刪除變數和去等號
        input.erase(0, variableName.size()+1);//刪除assign的變數名稱和等號;
    }
    if (checkBracket(input) == false)//檢查括號數
    {
        input = "error";
        //cout << "括號不合法" << endl;
    }
    if (checkOperator(input) == false)//檢查連續運算子
    {
        input = "error";
        //cout << "運算子不合法" << endl;
    }
    bool valid = checkValid(formula); //檢查&修正&取代formula儲存的數字or變數，有違規輸入同時輸出警示
    if (valid == false) //輸入數字檢測不符規定
        input = "error";
    else
    {
        vector<string> cv;//儲存構成新變數的變數們
        for (int i = 0; i < formula.size(); i++)
        {
            if (formula[i] != "(" && formula[i] != ")" && formula[i] != "+" && formula[i] != "-" && formula[i] != "*" && formula[i] != "/" && formula[i] != "^" && formula[i] != "sin(" && formula[i] != "cos(" && formula[i] != "tan(" && isDigit(formula[i]) == false)
            {
                cv.push_back(formula[i]);
            }
        }
        constructVariable.push_back(cv);
        if (checkDefinedVariable(cv) == false)
        { //存在未定義變數
            input = "error";
            //cout << "存在未定義變數" << endl;
        }
    }
    variableFormulaList.push_back(input); //儲存算式
    return;
}

void Parser::computeAllEquation() {
    for (int i = 0; i < variableNameList.size(); i++) {
        if (checkBracket(variableNameList[i]) == false && checkOperator(variableNameList[i]) == false) {
            //cout << "變數名稱錯誤" << endl;
            return;
        }
    }
    for (int i = 0; i < variableFormulaList.size(); i++) {
        if (variableFormulaList[i] == "error") {
            //cout << "存在錯誤，不可運算" << endl;
            return;
        }
    }
    if (checkLoopDefinedVariable() == false) {
        //cout << "循環定義變數，不可運算" << endl;
        return;
    }
    int exist = existAxisXOrY(variableNameList, constructVariable);
    if (exist == -1) {
        //cout << "x和y不存在，無法繪圖" << endl;
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
        string s;
        for (int i = 0; i < variableFormulaList[0].size(); i++) {
            s += variableFormulaList[0][i];
            if (s == "=" || s == "(" || s == ")" || s == "+" || s == "-" || s == "*" || s == "/" || s == "^" || s == "sin(" || s == "cos(" || s == "tan(") {
                formula.push_back(s);
                s.clear();
            }
            else if (((variableFormulaList[0][i+1] < '0' || variableFormulaList[0][i + 1] > '9') && variableFormulaList[0][i + 1] != '.') && isDigit(s) == true) {//數字
                formula.push_back(s);
                s.clear();
            }
            else if ((s == "sin" || s == "cos" || s == "tan") && variableFormulaList[0][i + 1] == '(') {
                continue;
            }
            else if (variableFormulaList[0][i + 1] == '=' || variableFormulaList[0][i + 1] == '(' || variableFormulaList[0][i + 1] == ')' || variableFormulaList[0][i + 1] == '+' || variableFormulaList[0][i + 1] == '-' || variableFormulaList[0][i + 1] == '*' || variableFormulaList[0][i + 1] == '/' || variableFormulaList[0][i + 1] == '^') { //變數
                formula.push_back(s);
                s.clear();
            }
            if (i == variableFormulaList[0].size() - 1) {
                formula.push_back(s);
                s.clear();
            }
        }

        if (exist == 0 && variableNameList[0] == "x") {
            y.push_back(d);
            x.push_back(compute(formula));
        }
        else if (exist == 1 && variableNameList[0] == "y") {
            x.push_back(d);
            y.push_back(compute(formula));
        }
        else if (exist == 2) {
            if (variableNameList[0] == "y") {
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
                y.push_back(compute(formula));
            }
            else if (variableNameList[0] == "x") {
                y.push_back(d);
                for (int i = 0; i < formula.size(); i++) {
                    if (formula[i] == "y") {
                        string sd;
                        stringstream ssd;
                        ssd << d;
                        ssd >> sd;
                        formula[i].replace(formula[i].find("y"), 1, sd);
                    }
                }
                x.push_back(compute(formula));
            }
        }
    }

}

double Parser::compute(vector<string> formula) {
    double ans = 0;

    while (formula.size() > 1 || (formula.size() == 3 && formula[1] == "/"))
    {
        //for (int i = 0; i < formula.size(); i++) { //去除沒有意義的括號
        //	if (isDigit(formula[i]) == true && formula[i - 1] == "(" && formula[i + 1] == ")") {
        //		formula[i - 1].replace(formula[i - 1].find("("), 1, formula[i]);
        //		formula.erase(formula.begin() + i);
        //		formula.erase(formula.begin() + i + 1);
        //		i--;
        //	}
        //}
        int found1 = -1; //找最後的左括弧位置
        int found2 = -1; //找第一個右括弧的位置
        string leftBracket;
        for (int i = 0; i < formula.size(); i++)
        {
            if (formula[i] == "(" || formula[i] == "sin(" || formula[i] == "cos(" || formula[i] == "tan(") {
                found1 = i;
                leftBracket = formula[i];
            }
        }
        for (int i = found1 + 1; i < formula.size(); i++)
        {
            if (formula[i] == ")")
            {
                found2 = i;
                break;
            }
        }

        if (found1 != -1 && found2 != -1 && found1 < found2) //找得到括弧的話
        {
            if (found1 + 1 == found2)
            {
                cout << "括號內無數字\n";
                return NAN;
            }
        }
        else//沒找到括弧
        {
            found1 = -1;
            found2 = formula.size();
        }

        for (int i = found2 - 1; i > found1; i--)//處理指數
        {
            if (formula[i] == "^" && i != found1 + 1)
            {
                double temp = stringToDouble(formula[i - 1]);
                if (temp < 0)//如果是負數開根號
                {
                    cout << "負數不能開根號\n";
                    return NAN;
                }
                else {
                    temp = pow(temp, stringToDouble(formula[i + 1]));
                    formula[i - 1] = doubleToString(temp);
                    formula.erase(formula.begin() + i, formula.begin() + i + 2);
                    found2 -= 2;
                    i--;
                }
            }
        }

        for (int i = found1 + 1; i < found2; i++) //處理乘除
        {
            if (formula[i] == "/")
            {
                if (stringToDouble(formula[i + 1]) == 0) {
                    //cout << "除數不能為 0\n";
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

        for (int i = found1 + 1; i < found2; i++) //處理加減
        {
            if (i == found1 + 1 && formula[i] == "+") // (+ 123) = 123 ; (+ -123) = -123
            {
                formula[i] = formula[1];
                i++;
            }
            else if (i == found1 + 1 && formula[i] == "-")
            {
                formula[i] = doubleToString(0 - stringToDouble(formula[i + 1]));
                i++;
            }
            if (formula[i] == "+") //(1 + 2) = 3
            {
                formula[found1+1] = doubleToString(stringToDouble(formula[found1+1]) + stringToDouble(formula[i + 1]));
                i++;
            }
            else if (formula[i] == "-")
            {
                formula[found1+1] = doubleToString(stringToDouble(formula[found1+1]) - stringToDouble(formula[i + 1]));
                i++;
            }
        }

        if (found1 == -1)//沒括弧的運算
        {
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
        else
        {
            formula[found1] = formula[found1 + 1];
            formula.erase(formula.begin() + found1 + 1, formula.begin() + found2 + 1);
            if (leftBracket == "sin(")
                formula[found1] = doubleToString(sin(stringToDouble(formula[found1])));
            else if (leftBracket == "cos(")
                formula[found1] = doubleToString(cos(stringToDouble(formula[found1])));
            else if (leftBracket == "tan(")
                formula[found1] = doubleToString(tan(stringToDouble(formula[found1])));
        }
    }
}


void Parser::getAxisVector() {
    for (int i = 0; i < x.size(); i++) {
        cout << x[i] << " " << y[i] << endl;
    }
}

bool isDigit(string s) {
    for (int i = 0; i < s.size(); i++) {
        if ((s[i] > '9' || s[i] < '0') && s[i] != '.')
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

