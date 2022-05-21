#ifndef CHESS_H
#define CHESS_H
#include <iostream>
#include <vector>


using namespace std;

class Chess
{
public:
    Chess();
    Chess(int color,int x,int y);
    enum Type{NONE,GENERAL,ADVISOR,ELEPHANT,CHARIOT,HORSE,CANNON,SOLDIER};
    bool isDead();
    virtual vector<pair<int, int>> canMovePos(const vector<Chess*> &BoardChessState) const;//儲存可移動的位置，需要參考當前棋盤資訊
    int colorRB;//紅0黑1
    int chessType;//棋種Base預設NONE
    bool dead;//預設false
    pair<int, int> position;//first=x,second=y

};

class General:public Chess//將/帥
{
public:
    General(int color,int x,int y);
    vector<pair<int, int>> canMovePos(const vector<Chess*> &BoardChessState) const;//九宮格
};

class Advisor :public Chess//士
{
public:
    Advisor(int color,int x,int y);
    vector<pair<int, int>> canMovePos(const vector<Chess*> &BoardChessState) const;//九宮格斜線
};

class Elephant :public Chess//象
{
public:
    Elephant(int color,int x,int y);
    vector<pair<int, int>> canMovePos(const vector<Chess*> &BoardChessState) const;//田字斜走兩格，田字中心有棋不能走
};

class Chariot :public Chess//車
{
public:
    Chariot(int color,int x,int y);
    vector<pair<int, int>> canMovePos(const vector<Chess*> &BoardChessState) const;//橫直任意走
};

class Horse :public Chess//馬
{
public:
    Horse(int color,int x,int y);
    vector<pair<int, int>> canMovePos(const vector<Chess*> &BoardChessState) const;//日字走法(前進一步+斜走一步)，前進方向有棋不能走
};

class Cannon :public Chess//砲
{
public:
    Cannon(int color,int x,int y);
    vector<pair<int, int>> canMovePos(const vector<Chess*> &BoardChessState) const;//橫直任意走，吃子要隔一棋
};

class Soldier :public Chess//兵/卒
{
public:
    Soldier(int color,int x,int y);
    bool crossRiver;//false未過 true已過
    vector<pair<int, int>> canMovePos(const vector<Chess*> &BoardChessState) const;//直走一步，過河可左右，不能退後
};
#endif // CHESS_H
