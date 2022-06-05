#include "number.h"

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
