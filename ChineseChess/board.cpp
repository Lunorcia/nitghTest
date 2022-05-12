#include "board.h"
#
Board::Board(QWidget *parent)
    : QWidget{parent}
{
    //reset();
    setMinimumSize(QSize(800,800));//故定視窗大小(最大最小值)
    setMaximumSize(QSize(800,800));
}
void Board::reset()
{
    endOrNot=false;
    BoardChessState.clear();
    //座標column=x,row=y
    //pair<> first=x,second=y
    //紅棋0黑棋1
    for(int i=0;i<5;i++)//兵卒
    {
        BoardChessState.push_back(new Soldier(0,i*2,6));//兵x=i*2(02468),y=6
        BoardChessState.push_back(new Soldier(1,i*2,3));//卒x=i*2(02468),y=3
    }
    for(int i=1;i<=7;i+=6)//炮砲
    {
        BoardChessState.push_back(new Cannon(0,i,5));//紅炮x=i(1.7),y=5
        BoardChessState.push_back(new Cannon(1,i,2));//黑砲x=i(1.7),y=2
    }
    for(int i=0;i<=8;i+=8)//俥車
    {
        BoardChessState.push_back(new Rook(0,i,9));//紅俥x=i(0.8),y=9
        BoardChessState.push_back(new Rook(1,i,0));//黑車x=i(0.8),y=0
    }
    for(int i=1;i<=7;i+=6)//人馬 馬
    {
        BoardChessState.push_back(new Horse(0,i,9));//紅馬x=i(1.7),y=9
        BoardChessState.push_back(new Horse(1,i,0));//黑馬x=i(1.7),y=0
    }
    for(int i=2;i<=6;i+=4)//相象
    {
        BoardChessState.push_back(new Elephant(0,i,9));//紅相x=i(2.6),y=9
        BoardChessState.push_back(new Elephant(1,i,0));//黑象x=i(2.6),y=0
    }
    for(int i=3;i<=5;i+=2)//仕士
    {
        BoardChessState.push_back(new Mandarin(0,i,9));//紅仕x=i(3.5),y=9
        BoardChessState.push_back(new Mandarin(1,i,0));//黑士x=i(3.5),y=0
    }
    //帥將
    BoardChessState.push_back(new General(0,4,9));//紅帥x=4,y=9
    BoardChessState.push_back(new General(1,4,0));//黑將x=4,y=0
}

void Board::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    //CHESSSIZE 30//棋子半徑
    //BOUNDARY 70//介面邊界和棋盤邊緣距離
    //GRID_WIDTH 60//格子的間隔寬度
    //ROW 10//10行橫線
    //COLUMN 9//9行直線
    for(int i=0;i<ROW;i++)//10橫線
    {
        painter.drawLine(QPoint(BOUNDARY,BOUNDARY+i*GRID_WIDTH),QPoint(BOUNDARY+8*GRID_WIDTH,BOUNDARY+i*GRID_WIDTH));
    }
    for(int i=0;i<COLUMN;i++)//9直線
    {
        if(i==0||i==8)//邊界兩條
            painter.drawLine(QPoint(BOUNDARY+i*GRID_WIDTH,BOUNDARY),QPoint(BOUNDARY+i*GRID_WIDTH,BOUNDARY+9*GRID_WIDTH));
        else//線被河拆上下兩半
        {
             painter.drawLine(QPoint(BOUNDARY+i*GRID_WIDTH,BOUNDARY),QPoint(BOUNDARY+i*GRID_WIDTH,BOUNDARY+4*GRID_WIDTH));
             painter.drawLine(QPoint(BOUNDARY+i*GRID_WIDTH,BOUNDARY+5*GRID_WIDTH),QPoint(BOUNDARY+i*GRID_WIDTH,BOUNDARY+9*GRID_WIDTH));
        }
    }
}
