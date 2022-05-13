#include "board.h"
#include "qmessagebox.h"

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
    //上米字線
    painter.drawLine(QPoint(BOUNDARY+3*GRID_WIDTH,BOUNDARY),QPoint(BOUNDARY+5*GRID_WIDTH,BOUNDARY+2*GRID_WIDTH));//左上右下
    painter.drawLine(QPoint(BOUNDARY+3*GRID_WIDTH,BOUNDARY+2*GRID_WIDTH),QPoint(BOUNDARY+5*GRID_WIDTH,BOUNDARY));//左下右上
    //下米字線
    painter.drawLine(QPoint(BOUNDARY+3*GRID_WIDTH,BOUNDARY+7*GRID_WIDTH),QPoint(BOUNDARY+5*GRID_WIDTH,BOUNDARY+9*GRID_WIDTH));//左上右下
    painter.drawLine(QPoint(BOUNDARY+3*GRID_WIDTH,BOUNDARY+9*GRID_WIDTH),QPoint(BOUNDARY+5*GRID_WIDTH,BOUNDARY+7*GRID_WIDTH));//左下右上

    //畫棋子
    /*for(int i=0;i<BoardChessState.size();i++)
        drawChess(painter,BoardChessState[0]);*/
    Chess C(1,3,0);
    Chess *c=&C;
    drawChess(painter,c);

}
QPoint Board::location(int row, int column)//棋盤座標轉介面座標
{
    QPoint QLocation;
    QLocation.rx()=BOUNDARY+column*GRID_WIDTH;
    QLocation.ry()=BOUNDARY+row*GRID_WIDTH;
    return QLocation;
}
QPoint Board::location(const Chess& ch)//棋子的棋盤座標轉介面座標
{
    QPoint QLocation;
    QLocation.rx()=BOUNDARY+ch.position.first*GRID_WIDTH;
    QLocation.ry()=BOUNDARY+ch.position.second*GRID_WIDTH;
    return QLocation;

}
void Board::drawChess(QPainter& painter, const Chess* c)//畫棋子
{
    QPoint p=location(*c);//棋子中心位置
    QRect rec(p.x()-CHESSSIZE*1.5,p.y()-CHESSSIZE*1.5,GRID_WIDTH,GRID_WIDTH);//畫字的格子
    painter.setBrush(QBrush(QColor(255,255,240)));//棋底顏色
    painter.drawEllipse(p, CHESSSIZE, CHESSSIZE);//畫圓
    QFont f;
    f.setFamily("SimSun");//字體
    f.setPointSize(CHESSSIZE-5);//文字大小
    painter.setFont(f);
    if(c->colorRB==0)//紅字
    {
        painter.setPen(QColor(255,0,0));
        switch(c->chessType)
        {
            case  Chess::Type::GENERAL:
                painter.drawText(rec,"帥",QTextOption(Qt::AlignCenter));//在rec方框置中位置印字
                break;
            case  Chess::Type::MANDARIN:
                painter.drawText(rec,"仕",QTextOption(Qt::AlignCenter));//在rec方框置中位置印字
                break;
            case  Chess::Type::ELEPHANT:
                painter.drawText(rec,"相",QTextOption(Qt::AlignCenter));//在rec方框置中位置印字
                break;
            case  Chess::Type::ROOK:
                painter.drawText(rec,"俥",QTextOption(Qt::AlignCenter));//在rec方框置中位置印字
                break;
            case  Chess::Type::HORSE:
                painter.drawText(rec,"傌",QTextOption(Qt::AlignCenter));//在rec方框置中位置印字
                break;
            case  Chess::Type::CANNON:
                painter.drawText(rec,"炮",QTextOption(Qt::AlignCenter));//在rec方框置中位置印字
                break;
            case  Chess::Type::SOLDIER:
                painter.drawText(rec,"兵",QTextOption(Qt::AlignCenter));//在rec方框置中位置印字
                break;
            default:
                painter.drawText(rec,"R",QTextOption(Qt::AlignCenter));
                break;
        }
    }
    else//黑字
    {
        painter.setPen(QColor(0,0,0));
        switch(c->chessType)
        {
            case  Chess::Type::GENERAL:
                painter.drawText(rec,"將",QTextOption(Qt::AlignCenter));//在rec方框置中位置印字
                break;
            case  Chess::Type::MANDARIN:
                painter.drawText(rec,"士",QTextOption(Qt::AlignCenter));//在rec方框置中位置印字
                break;
            case  Chess::Type::ELEPHANT:
                painter.drawText(rec,"象",QTextOption(Qt::AlignCenter));//在rec方框置中位置印字
                break;
            case  Chess::Type::ROOK:
                painter.drawText(rec,"車",QTextOption(Qt::AlignCenter));//在rec方框置中位置印字
                break;
            case  Chess::Type::HORSE:
                painter.drawText(rec,"馬",QTextOption(Qt::AlignCenter));//在rec方框置中位置印字
                break;
            case  Chess::Type::CANNON:
                painter.drawText(rec,"砲",QTextOption(Qt::AlignCenter));//在rec方框置中位置印字
                break;
            case  Chess::Type::SOLDIER:
                painter.drawText(rec,"卒",QTextOption(Qt::AlignCenter));//在rec方框置中位置印字
                break;
            default:
                painter.drawText(rec,"B",QTextOption(Qt::AlignCenter));
                break;
        }
    }
}

pair<int,int> Board::isClickChess(int row, int column,QPoint p)//判斷有沒有點到交叉格(可能有棋子的位置)
{
    for(row=0;row<10;row++)
    {
        for(column=0;column<9;column++)
        {
            QPoint temp=location(row,column);//把棋盤座標轉成介面座標
            //點擊位置在棋子半徑以內才算點到棋
            //distance=點擊位置到棋子中心的距離
            int distance=(p.x()-temp.x())*(p.x()-temp.x())+(p.y()-temp.y())*(p.y()-temp.y());
            if(distance<=CHESSSIZE*CHESSSIZE)
            {
                //有效點擊,回傳棋盤座標
                pair<int,int> pos={column,row};
                return  pos;
            }
        }
    }
    //點擊位置不在棋格有效範圍
    pair<int,int> pos={-1,-1};
    return  pos;
}
void Board::mouseReleaseEvent(QMouseEvent* ev)//滑鼠左鍵點擊
{
    if(endOrNot==true)//棋局已結束
        return;
    else if(ev->button()!=Qt::LeftButton)//左鍵以外的滑鼠點擊
        return;
    //彈出視窗顯示點擊座標
    /*QMessageBox msgBox;
    QPoint t=ev->pos();
    QString s=QString::number(t.x())+" "+QString::number(t.y());
     msgBox.setText(s);
     msgBox.exec();*/

    click(ev->pos());//進入判定滑鼠點擊

}
void Board::click(QPoint p)//有滑鼠點擊事件發生
{
    pair<int,int> pos=isClickChess(0,0,p);//點擊位置是否有效
    if(pos.first<0||pos.second<0)//無效點擊
        return;
    QMessageBox msgBox;
    msgBox.setText("valid");
    msgBox.exec();
    if(selectOrNot==false)//如果還沒點棋子
    {
        //existChess有沒有棋子
        //choosePiece>>判斷點選棋子是不是攻方(是反方就不動作)
        //有成功選到棋>>selectOrNot=true
    }
    else//已經選擇要移動的棋子selectOrNot==true
    {
        //確認點選位置是>同色棋子/不同色棋子/空位置
        //同色棋子isSameColor return true>>改變選擇要移動的棋子
        //空位置existChess return false>>checkValidMove>>有效move,無效取消選擇(回復未選棋狀態)
        //不同色棋子isSameColor return false>>checkValidMove>>有效killChess,然後move,無效取消選擇(回復未選棋狀態)
    }


}


