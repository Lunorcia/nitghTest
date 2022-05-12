#ifndef CHESS_H
#define CHESS_H
#include <iostream>
#include <vector>
using namespace std;

class Chess
{
public:
    Chess();
    bool isDead();
    virtual void canMovePos(){};
    int colorRB;//紅0黑1
    bool dead;//預設false
    pair<int, int> position;//first=row,second=column
};

class General:public Chess//將/帥
{
public:
    General();
    virtual void canMovePos(){};//九宮格
};

class Mandarin :public Chess//士
{
public:
    Mandarin();
    virtual void canMovePos(){};//九宮格斜線
};

class Elephant :public Chess//象
{
public:
    Elephant();
    virtual void canMovePos(){};//田字斜走兩格，田字中心有棋不能走
};

class Rook :public Chess//車
{
public:
    Rook();
    virtual void canMovePos(){};//橫直任意走
};

class Horse :public Chess//馬
{
public:
    Horse();
    virtual void canMovePos(){};//日字走法(前進一步+斜走一步)，前進方向有棋不能走
};

class Cannon :public Chess//砲
{
public:
    Cannon();
    virtual void canMovePos(){};//橫直任意走，吃子要隔一棋
};

class Soldier :public Chess//兵/卒
{
public:
    Soldier();
    bool crossRiver;//false未過 true已過
    virtual void canMovePos(){};//直走一步，過河可左右，不能退後
};
#endif // CHESS_H
