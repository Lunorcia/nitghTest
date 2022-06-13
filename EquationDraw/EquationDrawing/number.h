#ifndef NUMBER_H
#define NUMBER_H
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>
using namespace std;
bool checkValid(vector<string>& formula, string originInput);
bool checkBracketAmount(const string& line);
//bool checkOperator(string line);
bool checkDPs(const string& num);
bool negativeRoot(const string& num);
void mergePN(string& num);
//bool convertPower(vector<string>& formula);
void Compute(vector<string>& formula);
class number
{
public:
    number(string a)
    {
        num = a;
    };
    string operator +(number K);
    string operator -(number K);
    string operator *(number K);
    string operator /(number K);
    string operator ^(number K);
    string computeSin();
    string computeCos();
    string computeTan();
    bool operator ==(number K);
    string num;
private:
};
#endif // NUMBER_H
