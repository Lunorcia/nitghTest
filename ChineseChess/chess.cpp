#include "board.h"
bool chessIsSameColor(const pair<int, int> &pos, const vector<Chess*>& BoardChessState, const int color) {
    for (int i = 0; i < BoardChessState.size(); i++) {
        if ((pos.first == BoardChessState[i]->position.first) && (pos.second == BoardChessState[i]->position.second) && !(BoardChessState[i]->isDead())) {
            if (BoardChessState[i]->colorRB == color) {
                return true;
            }
        }
    }
    return false;
}

bool existChess(const pair<int, int> &pos, const vector<Chess*>& BoardChessState){
    for(int i=0;i<BoardChessState.size();i++)
    {
        if(pos.first==BoardChessState[i]->position.first && pos.second==BoardChessState[i]->position.second && !(BoardChessState[i]->isDead()))
            return true;
    }
    return false;
}

Chess::Chess()
{
    colorRB=0;
    position.first=-1;
    position.second=-1;
    dead=false;
    chessType=NONE;
}
Chess::Chess(int color,int x,int y)
{
    colorRB=color;
    position.first=x;
    position.second=y;
    dead=false;
    chessType=NONE;
}

bool Chess::isDead()
{
    return dead;
}

General::General(int color,int x,int y):Chess(color,x,y)
{
    chessType=GENERAL;
}

Advisor::Advisor(int color,int x,int y):Chess(color,x,y)
{
    chessType=ADVISOR;
}

Elephant::Elephant(int color,int x,int y):Chess(color,x,y)
{
    chessType=ELEPHANT;
}

Chariot::Chariot(int color,int x,int y):Chess(color,x,y)
{
    chessType=CHARIOT;
}

Horse::Horse(int color,int x,int y):Chess(color,x,y)
{
    chessType=HORSE;
}

Cannon::Cannon(int color,int x,int y):Chess(color,x,y)
{
    chessType=CANNON;
}

Soldier::Soldier(int color,int x,int y):Chess(color,x,y)
{
    chessType=SOLDIER;
    crossRiver=false;
}
vector<pair<int, int>> Chess::canMovePos(const vector<Chess*> &BoardChessState) const//預設移動(無用)
{
    vector<pair<int, int>> t;
    t.clear();
    pair<int, int> p={-1,-1};
    t.push_back(p);
    return t;
}
vector<pair<int, int>> General::canMovePos(const vector<Chess*> &BoardChessState) const{//帥和將 移動方案
    vector<pair<int, int>> nextPos;
    pair<int, int> p(position.first+1, position.second);
    if (colorRB == 0 && p.first >= 3 && p.first <= 5 && p.second >= 7 && p.second <= 9){//帥
        if (existChess(p, BoardChessState) == false)
            nextPos.push_back(p);
        else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false)
            nextPos.push_back(p);
    }
    else if (colorRB == 1 && p.first >= 3 && p.first <= 5 && p.second >= 0 && p.second <= 2){//將
        if (existChess(p, BoardChessState) == false)
            nextPos.push_back(p);
        else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false)
            nextPos.push_back(p);
    }
    p.first = position.first-1;
    p.second = position.second;
    if (colorRB == 0 && p.first >= 3 && p.first <= 5 && p.second >= 7 && p.second <= 9){//帥
        if (existChess(p, BoardChessState) == false)
            nextPos.push_back(p);
        else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false)
            nextPos.push_back(p);
    }
    else if (colorRB == 1 && p.first >= 3 && p.first <= 5 && p.second >= 0 && p.second <= 2){//將
        if (existChess(p, BoardChessState) == false)
            nextPos.push_back(p);
        else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false)
            nextPos.push_back(p);
    }
    p.first = position.first;
    p.second = position.second+1;
    if (colorRB == 0 && p.first >= 3 && p.first <= 5 && p.second >= 7 && p.second <= 9){//帥
        if (existChess(p, BoardChessState) == false)
            nextPos.push_back(p);
        else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false)
            nextPos.push_back(p);
    }
    else if (colorRB == 1 && p.first >= 3 && p.first <= 5 && p.second >= 0 && p.second <= 2){//將
        if (existChess(p, BoardChessState) == false)
            nextPos.push_back(p);
        else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false)
            nextPos.push_back(p);
    }
    p.first = position.first;
    p.second = position.second-1;
    if (colorRB == 0 && p.first >= 3 && p.first <= 5 && p.second >= 7 && p.second <= 9){//帥
        if (existChess(p, BoardChessState) == false)
            nextPos.push_back(p);
        else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false)
            nextPos.push_back(p);
    }
    else if (colorRB == 1 && p.first >= 3 && p.first <= 5 && p.second >= 0 && p.second <= 2){//將
        if (existChess(p, BoardChessState) == false)
            nextPos.push_back(p);
        else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false)
            nextPos.push_back(p);
    }
    return nextPos;
}

vector<pair<int, int>> Advisor::canMovePos(const vector<Chess*> &BoardChessState) const{//士 移動方案
    vector<pair<int, int>> nextPos;
    pair<int, int> p;
    if (colorRB == 0){//紅士
        if ((position.first == 3 || position.first == 5) && (position.second == 7 || position.second == 9)){
            p.first = 4;
            p.second = 8;
            if (existChess(p, BoardChessState) == false)
                nextPos.push_back(p);
            else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false)
                nextPos.push_back(p);
        }
        else if (position.first == 4 && position.second == 8){
            p.first = 3;
            p.second = 7;
            if (existChess(p, BoardChessState) == false)
                nextPos.push_back(p);
            else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false)
                nextPos.push_back(p);

            p.first = 5;
            p.second = 7;
            if (existChess(p, BoardChessState) == false)
                nextPos.push_back(p);
            else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false)
                nextPos.push_back(p);

            p.first = 3;
            p.second = 9;
            if (existChess(p, BoardChessState) == false)
                nextPos.push_back(p);
            else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false)
                nextPos.push_back(p);

            p.first = 5;
            p.second = 9;
            if (existChess(p, BoardChessState) == false)
                nextPos.push_back(p);
            else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false)
                nextPos.push_back(p);
        }
    }
    else if (colorRB == 1){//黑士
        if ((position.first == 3 || position.first == 5) && (position.second == 0 || position.second == 2)){
            p.first = 4;
            p.second = 1;
            if (existChess(p, BoardChessState) == false)
                nextPos.push_back(p);
            else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false)
                nextPos.push_back(p);
        }
        else if (position.first == 4 && position.second == 1){
            p.first = 3;
            p.second = 0;
            if (existChess(p, BoardChessState) == false)
                nextPos.push_back(p);
            else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false)
                nextPos.push_back(p);

            p.first = 5;
            p.second = 0;
            if (existChess(p, BoardChessState) == false)
                nextPos.push_back(p);
            else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false)
                nextPos.push_back(p);

            p.first = 3;
            p.second = 2;
            if (existChess(p, BoardChessState) == false)
                nextPos.push_back(p);
            else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false)
                nextPos.push_back(p);

            p.first = 5;
            p.second = 2;
            if (existChess(p, BoardChessState) == false)
                nextPos.push_back(p);
            else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false)
                nextPos.push_back(p);
        }
    }
    return nextPos;
}

vector<pair<int, int>> Elephant::canMovePos(const vector<Chess*> &BoardChessState) const{//象 移動方案
    vector<pair<int, int>> nextPos;
    pair<int, int> p(position.first-2, position.second-2);
    pair<int, int> testp(position.first-1, position.second-1);
    if (existChess(testp, BoardChessState) == false){
        if (p.first >= 0 && p.first <= 8 && p.second >= 0 && p.second <= 9){
            if (existChess(p, BoardChessState) == false)
                nextPos.push_back(p);
            else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false )
                nextPos.push_back(p);
        }
    }
    p.first = position.first+2;
    p.second = position.second-2;
    testp.first = position.first+1;
    testp.second = position.second-1;
    if (existChess(testp, BoardChessState) == false){
        if (p.first >= 0 && p.first <= 8 && p.second >= 0 && p.second <= 9){
            if (existChess(p, BoardChessState) == false)
                nextPos.push_back(p);
            else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false )
                nextPos.push_back(p);
        }
    }
    p.first = position.first-2;
    p.second = position.second+2;
    testp.first = position.first-1;
    testp.second = position.second+1;
    if (existChess(testp, BoardChessState) == false){
        if (p.first >= 0 && p.first <= 8 && p.second >= 0 && p.second <= 9){
            if (existChess(p, BoardChessState) == false)
                nextPos.push_back(p);
            else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false )
                nextPos.push_back(p);
        }
    }
    p.first = position.first+2;
    p.second = position.second+2;
    testp.first = position.first+1;
    testp.second = position.second+1;
    if (existChess(testp, BoardChessState) == false){
        if (p.first >= 0 && p.first <= 8 && p.second >= 0 && p.second <= 9){
            if (existChess(p, BoardChessState) == false)
                nextPos.push_back(p);
            else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false )
                nextPos.push_back(p);
        }
    }
    return nextPos;
}

vector<pair<int, int>> Chariot::canMovePos(const vector<Chess*> &BoardChessState) const{//車 移動方案
    vector<pair<int, int>> nextPos;
    pair<int, int> p;
    for (int x = position.first+1; x <= 8; x++) {
        p.first = x;
        p.second = position.second;
        if (existChess(p, BoardChessState) == false)
            nextPos.push_back(p);
        else{
            if (chessIsSameColor(p, BoardChessState, this->colorRB) == false){//陣營不同 可吃子
                nextPos.push_back(p);
                break;
            }
            else
                break;
        }
    }
    for (int x = position.first-1; x >= 0; x--) {
        p.first = x;
        p.second = position.second;
        if (existChess(p, BoardChessState) == false)
            nextPos.push_back(p);
        else{
            if (chessIsSameColor(p, BoardChessState, this->colorRB) == false){//陣營不同 可吃子
                nextPos.push_back(p);
                break;
            }
            else
                break;
        }
    }
    for (int y = position.second+1; y <= 9; y++) {
        p.first = position.first;
        p.second = y;
        if (existChess(p, BoardChessState) == false)
            nextPos.push_back(p);
        else{
            if (chessIsSameColor(p, BoardChessState, this->colorRB) == false){//陣營不同 可吃子
                nextPos.push_back(p);
                break;
            }
            else
                break;
        }
    }
    for (int y = position.second-1; y >= 0; y--) {
        p.first = position.first;
        p.second = y;
        if (existChess(p, BoardChessState) == false)
            nextPos.push_back(p);
        else{
            if (chessIsSameColor(p, BoardChessState, this->colorRB) == false){//陣營不同 可吃子
                nextPos.push_back(p);
                break;
            }
            else
                break;
        }
    }
    return nextPos;
};

vector<pair<int, int>> Horse::canMovePos(const vector<Chess*> &BoardChessState) const{//馬 移動方案
    vector<pair<int, int>> nextPos;
    pair<int, int> p(position.first-2, position.second-1);
    pair<int, int> testp(position.first-1, position.second);
    if (existChess(testp, BoardChessState) == false){
        if (p.first >= 0 && p.first <= 8 && p.second >= 0 && p.second <= 9){
            if (existChess(p, BoardChessState) == false)
                nextPos.push_back(p);
            else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false )
                nextPos.push_back(p);
        }
        p.second = position.second+1;
        if (p.first >= 0 && p.first <= 8 && p.second >= 0 && p.second <= 9){
            if (existChess(p, BoardChessState) == false)
                nextPos.push_back(p);
            else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false )
                nextPos.push_back(p);
        }
    }
    p.first = position.first+2;
    p.second = position.second-1;
    testp.first = position.first+1;
    testp.second = position.second;
    if (existChess(testp, BoardChessState) == false){
        if (p.first >= 0 && p.first <= 8 && p.second >= 0 && p.second <= 9){
            if (existChess(p, BoardChessState) == false)
                nextPos.push_back(p);
            else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false )
                nextPos.push_back(p);
        }
        p.second = position.second+1;
        if (p.first >= 0 && p.first <= 8 && p.second >= 0 && p.second <= 9){
            if (existChess(p, BoardChessState) == false)
                nextPos.push_back(p);
            else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false )
                nextPos.push_back(p);
        }
    }
    p.first = position.first-1;
    p.second = position.second-2;
    testp.first = position.first;
    testp.second = position.second-1;
    if (existChess(testp, BoardChessState) == false){
        if (p.first >= 0 && p.first <= 8 && p.second >= 0 && p.second <= 9){
            if (existChess(p, BoardChessState) == false)
                nextPos.push_back(p);
            else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false )
                nextPos.push_back(p);
        }
        p.first = position.first+1;
        if (p.first >= 0 && p.first <= 8 && p.second >= 0 && p.second <= 9){
            if (existChess(p, BoardChessState) == false)
                nextPos.push_back(p);
            else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false )
                nextPos.push_back(p);
        }
    }
    p.first = position.first-1;
    p.second = position.second+2;
    testp.first = position.first;
    testp.second = position.second+1;
    if (existChess(testp, BoardChessState) == false){
        if (p.first >= 0 && p.first <= 8 && p.second >= 0 && p.second <= 9){
            if (existChess(p, BoardChessState) == false)
                nextPos.push_back(p);
            else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false )
                nextPos.push_back(p);
        }
        p.first = position.first+1;
        if (p.first >= 0 && p.first <= 8 && p.second >= 0 && p.second <= 9){
            if (existChess(p, BoardChessState) == false)
                nextPos.push_back(p);
            else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false )
                nextPos.push_back(p);
        }
    }
    return nextPos;
}

vector<pair<int, int>> Cannon::canMovePos(const vector<Chess*> &BoardChessState) const{//炮 移動方案
    vector<pair<int, int>> nextPos;
    pair<int, int> p;
    int fort = 0;//砲台:炮遇到的第一個棋子,讓炮與可吃子的敵方另一個棋子相隔
    for (int x = position.first+1; x <= 8; x++) {
        p.first = x;
        p.second = position.second;
        if (existChess(p, BoardChessState) == false){
            if (fort == 0)
                nextPos.push_back(p);
        }
        else{
            if (fort == 0){
                fort++;
            }
            else if (fort == 1){
                if (chessIsSameColor(p, BoardChessState, this->colorRB) == false){//陣營不同 可吃子
                    nextPos.push_back(p);
                    break;
                }
                else
                    break;
            }
        }
    }
    fort = 0;
    for (int x = position.first-1; x >= 0; x--) {
        p.first = x;
        p.second = position.second;
        if (existChess(p, BoardChessState) == false){
            if (fort == 0)
                nextPos.push_back(p);
        }
        else{
            if (fort == 0){
                fort++;
            }
            else if (fort == 1){
                if (chessIsSameColor(p, BoardChessState, this->colorRB) == false){//陣營不同 可吃子
                    nextPos.push_back(p);
                    break;
                }
                else
                    break;
            }
        }
    }
    fort = 0;
    for (int y = position.second+1; y <= 9; y++) {
        p.first = position.first;
        p.second = y;
        if (existChess(p, BoardChessState) == false){
            if (fort == 0)
                nextPos.push_back(p);
        }
        else{
            if (fort == 0){
                fort++;
            }
            else if (fort == 1){
                if (chessIsSameColor(p, BoardChessState, this->colorRB) == false){//陣營不同 可吃子
                    nextPos.push_back(p);
                    break;
                }
                else
                    break;
            }
        }
    }
    fort = 0;
    for (int y = position.second-1; y >= 0; y--) {
        p.first = position.first;
        p.second = y;
        if (existChess(p, BoardChessState) == false){
            if (fort == 0)
                nextPos.push_back(p);
        }
        else{
            if (fort == 0){
                fort++;
            }
            else if (fort == 1){
                if (chessIsSameColor(p, BoardChessState, this->colorRB) == false){//陣營不同 可吃子
                    nextPos.push_back(p);
                    break;
                }
                else
                    break;
            }
        }
    }
    return nextPos;
};

vector<pair<int, int>> Soldier::canMovePos(const vector<Chess*> &BoardChessState) const{ //兵卒 移動方案
    vector<pair<int, int>> nextPos;
    pair<int, int> p;
    if(crossRiver==false){
        if(colorRB==0){//兵
            p.first = position.first;
            p.second = position.second-1;
        }
        else if(colorRB==1){//卒
            p.first = position.first;
            p.second = position.second+1;
        }
        if (p.first >= 0 && p.first <= 8 && p.second >= 0 && p.second <= 9) {
            if (existChess(p, BoardChessState) == false)
                nextPos.push_back(p);
            else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false) {
                nextPos.push_back(p);
            }
        }
    }
    else if (crossRiver==true){
        if(colorRB==0){//兵
            p.first = position.first;
            p.second = position.second-1;
            if (p.first >= 0 && p.first <= 8 && p.second >= 0 && p.second <= 9) {
                if (existChess(p, BoardChessState) == false)
                    nextPos.push_back(p);
                else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false) {
                    nextPos.push_back(p);
                }
            }
            p.first = position.first-1;
            p.second = position.second;
            if (p.first >= 0 && p.first <= 8 && p.second >= 0 && p.second <= 9) {
                if (existChess(p, BoardChessState) == false)
                    nextPos.push_back(p);
                else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false) {
                    nextPos.push_back(p);
                }
            }
            p.first = position.first+1;
            p.second = position.second;
            if (p.first >= 0 && p.first <= 8 && p.second >= 0 && p.second <= 9) {
                if (existChess(p, BoardChessState) == false)
                    nextPos.push_back(p);
                else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false) {
                    nextPos.push_back(p);
                }
            }
        }
        if (colorRB == 1) {//卒
            p.first = position.first;
            p.second = position.second+1;
            if (p.first >= 0 && p.first <= 8 && p.second >= 0 && p.second <= 9) {
                if (existChess(p, BoardChessState) == false)
                    nextPos.push_back(p);
                else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false) {
                    nextPos.push_back(p);
                }
            }
            p.first = position.first - 1;
            p.second = position.second;
            if (p.first >= 0 && p.first <= 8 && p.second >= 0 && p.second <= 9) {
                if (existChess(p, BoardChessState) == false)
                    nextPos.push_back(p);
                else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false) {
                    nextPos.push_back(p);
                }
            }
            p.first = position.first + 1;
            p.second = position.second;
            if (p.first >= 0 && p.first <= 8 && p.second >= 0 && p.second <= 9) {
                if (existChess(p, BoardChessState) == false)
                    nextPos.push_back(p);
                else if (existChess(p, BoardChessState) == true && chessIsSameColor(p, BoardChessState, this->colorRB) == false) {
                    nextPos.push_back(p);
                }
            }
        }
    }
    return nextPos;
};
