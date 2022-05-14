#include "chess.h"

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
}
