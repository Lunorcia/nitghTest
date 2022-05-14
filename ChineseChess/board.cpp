#include "board.h"

Board::Board(QWidget *parent)
    : QWidget{parent}
{
    reset();
    setMinimumSize(QSize(800,800));//故定視窗大小(最大最小值)
    setMaximumSize(QSize(800,800));
}
void Board::reset()
{
    current_player=0;//預設起始紅0
    endOrNot=false;
    cancelChoose();//選棋重置
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
        BoardChessState.push_back(new Chariot(0,i,9));//紅俥x=i(0.8),y=9
        BoardChessState.push_back(new Chariot(1,i,0));//黑車x=i(0.8),y=0
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
        BoardChessState.push_back(new Advisor(0,i,9));//紅仕x=i(3.5),y=9
        BoardChessState.push_back(new Advisor(1,i,0));//黑士x=i(3.5),y=0
    }
    //帥將
    BoardChessState.push_back(new General(0,4,9));//紅帥x=4,y=9
    BoardChessState.push_back(new General(1,4,0));//黑將x=4,y=0
    QMessageBox msgBox;
    msgBox.setText(QString::number(BoardChessState.size()));
    msgBox.exec();
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
    int i=0;
    for(;i<BoardChessState.size();i++)
    {

        drawChess(painter,BoardChessState[i]);
    }

    /*Chess C(1,3,0);
    Chess *c=&C;
    drawChess(painter,c);*/

}

void Board::drawChess(QPainter& painter, const Chess* c)//畫棋子
{

    if(c->dead==true)//棋子已死不用畫
        return;
    QPoint p=location(*c);//棋子中心位置
    QRect rec(p.x()-CHESSSIZE*1.5,p.y()-CHESSSIZE*1.5,GRID_WIDTH,GRID_WIDTH);//畫字的格子
    painter.setPen(QColor(0,0,0));
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
            case  Chess::Type::ADVISOR:
                painter.drawText(rec,"仕",QTextOption(Qt::AlignCenter));//在rec方框置中位置印字
                break;
            case  Chess::Type::ELEPHANT:
                painter.drawText(rec,"相",QTextOption(Qt::AlignCenter));//在rec方框置中位置印字
                break;
            case  Chess::Type::CHARIOT:
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
            case  Chess::Type::ADVISOR:
                painter.drawText(rec,"士",QTextOption(Qt::AlignCenter));//在rec方框置中位置印字
                break;
            case  Chess::Type::ELEPHANT:
                painter.drawText(rec,"象",QTextOption(Qt::AlignCenter));//在rec方框置中位置印字
                break;
            case  Chess::Type::CHARIOT:
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
    if(MovingChess==c)//要移動的棋子
    {
        QRect rs(p.x()-CHESSSIZE,p.y()-CHESSSIZE,CHESSSIZE*2,CHESSSIZE*2);//畫字的格子
        QPen p;
        p.setWidth(3);
        p.setColor(QColor(50,50,250));
        painter.setBrush(Qt::NoBrush);//方框設成中空
        painter.setPen(p);
        painter.drawRect(rs);//畫選擇棋的方框
    }
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

void Board::mouseReleaseEvent(QMouseEvent* ev)//滑鼠左鍵點擊
{
    if(endOrNot==true)//棋局已結束
        return;
    else if(ev->button()!=Qt::LeftButton)//左鍵以外的滑鼠點擊
        return;
    click(ev->pos());//進入判定滑鼠點擊
}

void Board::click(QPoint p)//有滑鼠點擊事件發生
{
    pair<int,int> pos=isClickChess(0,0,p);//點擊位置是否有效
    if(pos.first<0||pos.second<0)//無效點擊
        return;
    /*QMessageBox msgBox;
    msgBox.setText("valid x,y="+QString::number(pos.first)+" "+QString::number(pos.second));
    msgBox.exec();*/
    if(selectOrNot==false)//還沒點棋子
    {
        if(existChess(pos))//點擊位置有棋子
            chooseMovePiece(pos);//判斷棋子是不是攻方+選棋(是守方就不動作)
    }
    else//已經選擇要移動的棋子(selectOrNot==true)
    {
        if(!existChess(pos))//點擊位置沒有棋子
        {
            if(checkValidMove(*MovingChess, pos))//有效move,無效取消選擇
                move(pos,pos);
        }
        else//點擊位置有棋子
            chooseMovePosition(pos);
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

bool Board::existChess(pair<int,int> pos)//點擊位置有沒有棋子
{
    for(int i=0;i<BoardChessState.size();i++)
    {   //位置相符且棋子沒死
        if(pos.first==BoardChessState[i]->position.first && pos.second==BoardChessState[i]->position.second && !(BoardChessState[i]->isDead()))
            return true;//點擊位置有棋子
    }
    return false;//點擊位置沒有棋子
}

void Board::chooseMovePiece(pair<int,int> pos)//選擇要移動的棋子(pos必定有棋)
{
    int i=0;
    for(;i<BoardChessState.size();i++)
    {   //位置相符且棋子沒死
        if(pos.first==BoardChessState[i]->position.first && pos.second==BoardChessState[i]->position.second && !(BoardChessState[i]->isDead()))
            break;//點擊位置有棋子
    }
    if(i!=BoardChessState.size())
    {
        if(isSameColor(*BoardChessState[i]))//點的棋子是攻方
        {
            selectOrNot=true;
            MovingChess=BoardChessState[i];
        }
        else//點的棋子是守方
            cancelChoose();
    }
    else
        cancelChoose();
    update();//顯示出點擊的棋子
}

void Board::chooseMovePosition(pair<int,int> pos)//選擇棋子要移動的位置(pos必定有棋)
{
    int i=0;
    for(;i<BoardChessState.size();i++)
    {   //位置相符且棋子沒死
        if(pos.first==BoardChessState[i]->position.first && pos.second==BoardChessState[i]->position.second && !(BoardChessState[i]->isDead()))
            break;//點擊位置有棋子
    }
    if(i!=BoardChessState.size())
    {
        if(isSameColor(*BoardChessState[i]))//點的棋子是攻方
            chooseMovePiece(pos);//改變要移動的棋子

        else//點的棋子是守方
        {
            if(checkValidMove(*MovingChess, pos))//有效移動
            {
                killChess(pos);//吃子
                move(BoardChessState[i]->position, pos);//移動棋子
            }
            else//無效移動,取消選擇
                cancelChoose();
        }
    }
}

bool Board::isSameColor(const Chess& ch)
{
    if(ch.colorRB==current_player)
        return true;
    return false;
}

bool Board::checkValidMove(const Chess & ch, pair<int,int> nextPos)//選取的位置能不能移動
{
    return true;
}

void Board::cancelChoose()
{
    selectOrNot=false;
    MovingChess=NULL;
    update();//盤面刷新
}

void Board::killChess(pair<int,int> pos)//吃子
{
    int i=0;
    for(;i<BoardChessState.size();i++)
    {   //位置相符且棋子沒死
        if(pos.first==BoardChessState[i]->position.first && pos.second==BoardChessState[i]->position.second && !(BoardChessState[i]->isDead()))
            break;//點擊位置有棋子
    }
    if(i!=BoardChessState.size())
    {
        BoardChessState[i]->dead=true;
        BoardChessState[i]->position.first= -1;
        BoardChessState[i]->position.second= -1;
    }
}

void Board::move(pair<int,int> nowPos, pair<int,int> nextPos)//移動
{
    writeRecord(nowPos,nextPos);
    MovingChess->position.first=nextPos.first;
    MovingChess->position.second=nextPos.second;
    isCheckmate();
    cancelChoose();
    changePlayer();

}

bool Board::isCheckmate()//是否將軍
{
    return false;
}

void Board::writeRecord(pair<int,int> nowPos, pair<int,int> nextPos)//寫檔
{
    //遊戲誰贏也要寫
}
void Board::changePlayer()
{
    current_player=(current_player+1) % 2;
}
