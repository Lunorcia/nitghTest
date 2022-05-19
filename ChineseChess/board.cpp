#include "gamemanager.h"

Board::Board(QWidget *parent)
    : QWidget{parent}
{
    reset();
    setMinimumSize(QSize(800,800));//故定視窗大小(最大最小值)
    setMaximumSize(QSize(800,800));
}
void Board::reset()
{
    count=0;
    GameManager::endOrNot=false;
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
        BoardChessState.push_back(new Cannon(0,i,7));//紅炮x=i(1.7),y=7
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
    /*QMessageBox msgBox;
    msgBox.setText(QString::number(BoardChessState.size()));
    msgBox.exec();*/
}

void Board::stringControl(QString moveCmd)//讀檔移動
{
    QStringList list=moveCmd.split(" ");//字串用空白切割

    //Player: 1, Action: Soldier (4, 6) -> (4, 5)
    //[0]"Player:"
    //[1]"1,">>助教題目預設紅1黑2>>程式寫的用紅0黑1
    //[2]"Action:"
    //[3]"Soldier"
    //[4]"(4,"
    //[5]"6)"
    //[6]"->"
    //[7]"(4,"
    //[8]"5)"
    if(list[1].mid(0,1) != QString::number(GameManager::current_player + 1))//移動不是攻方
    {
        QMessageBox msgBox;
        msgBox.setText("移動棋子非攻方");
        msgBox.exec();
        return;
    }
    list[1]=list[1].mid(0,1);//去逗號
    int player=-1, tempType=0, nowX=-1, nowY=-1, nextX=-1, nextY=-1;
    //棋種轉換
    if(list[3]=="Soldier")
    {
        tempType=Chess::Type::SOLDIER;
    }
    else if(list[3]=="Cannon")
    {
        tempType=Chess::Type::CANNON;
    }
    else if(list[3]=="Chariot")
    {
        tempType=Chess::Type::CHARIOT;
    }
    else if(list[3]=="Horse")
    {
        tempType=Chess::Type::HORSE;
    }
    else if(list[3]=="Elephant")
    {
        tempType=Chess::Type::ELEPHANT;
    }
    else if(list[3]=="Advisor")
    {
        tempType=Chess::Type::ADVISOR;
    }
    else if(list[3]=="General")
    {
        tempType=Chess::Type::GENERAL;
    }
    else//棋種輸入錯誤
    {
        QMessageBox msgBox;
        msgBox.setText("棋種輸入錯誤");
        msgBox.exec();
        return;
    }

    //玩家和座標轉數字
    if(list[4].length()>3 || list[5].length()>2 || list[7].length()>3 || list[8].length()>2)//輸入座標格式錯誤
    {
        QMessageBox msgBox;
        msgBox.setText(list[0]+list[1]+" 輸入座標不合法/格式錯誤");
        msgBox.exec();
        return;
    }
    player=list[1].toInt() - 1;
    nowX=list[4].mid(1,1).toInt();
    nowY=list[5].mid(0,1).toInt();
    nextX=list[7].mid(1,1).toInt();
    nextY=list[8].mid(0,1).toInt();
    if(nowX<0||nowX>=COLUMN||nowY<0||nowY>=ROW || nextX<0||nextX>=COLUMN||nextY<0||nextY>=ROW)//輸入座標超出棋盤範圍
    {
        QMessageBox msgBox;
        msgBox.setText(list[0]+list[1]+" 輸入座標不合法");
        msgBox.exec();
        return;
    }
    int i=0;
    for(;i<BoardChessState.size();i++)  //找在點上且活著的攻方棋子
    {
        if(player==BoardChessState[i]->colorRB &&
           nowX==BoardChessState[i]->position.first &&
           nowY==BoardChessState[i]->position.second &&
                !(BoardChessState[i]->isDead()))
            break;
    }
    if(i>=BoardChessState.size())//沒找到對應的棋子
    {
        QMessageBox msgBox;
        msgBox.setText(list[0]+list[1]+"找不到棋子"+list[3]);
        msgBox.exec();
        return;
    }
    chooseMovePiece(pair<int,int>{nowX,nowY});//選棋
    if(selectOrNot)//選棋成功
    {
        if(!existChess(pair<int,int>{nextX,nextY}))//點擊位置沒有棋子
        {
            if(checkValidMove(*MovingChess, pair<int,int>{nextX,nextY}))//有效move,無效取消選擇
            {
                stringMove(pair<int,int>{nextX,nextY});//讀檔用移棋子(移動不寫檔)
            }
            else
                cancelChoose();
        }
        else//點擊位置有棋子
        {
            stringChooseMovePosition(pair<int,int>{nextX,nextY},moveCmd);
        }
    }
}

void Board::stringChooseMovePosition(pair<int,int> pos, QString moveCmd)//選擇棋子要移動的位置(pos必定有棋)(移動不寫檔)
{
    int i=0;
    for(;i<BoardChessState.size();i++)
    {   //位置相符且棋子沒死
        if(pos.first==BoardChessState[i]->position.first && pos.second==BoardChessState[i]->position.second && !(BoardChessState[i]->isDead()))
            break;//點擊位置有棋子
    }
    if(i!=BoardChessState.size())
    {
        if(isSameColor(*BoardChessState[i]))//要移動的位置是攻方棋
        {
            cancelChoose();
            QMessageBox msgBox;
            msgBox.setText("移動位置已有同陣營棋子存在/移動位置無效");
            msgBox.exec();
            return;
        }
        else//點的棋子是守方
        {
            if(checkValidMove(*MovingChess, pos))//有效移動
            {
                killChess(pos);//吃子
                stringMove(pos);//讀檔用移棋子(移動不寫檔)
            }
            else//無效移動
            {
                cancelChoose();
                QMessageBox msgBox;
                msgBox.setText("移動位置無效");
                msgBox.exec();
                return;
            }
        }
    }
}

void Board::stringMove(pair<int,int> nextPos)//讀檔用移棋子(移動不寫檔)
{
    MovingChess->position.first=nextPos.first;
    MovingChess->position.second=nextPos.second;
    isCheckmate(*MovingChess, nextPos);
    cancelChoose();
    GameManager::changePlayer();
}

void Board::drawCanMovePos(QPainter & painter, const Chess* c){
    if (c->dead==true)
        return;
    if (MovingChess==c){
        vector<pair<int, int>> nextPos= c->canMovePos(BoardChessState);
        for (int i = 0; i < nextPos.size(); i++){
            QPoint pos = location(nextPos[i].second, nextPos[i].first);
//            QRect rec(pos.x()-CHESSSIZE*1.5,pos.y()-CHESSSIZE*1.5,CHESSSIZE,CHESSSIZE);
            painter.setPen(Qt::blue);
            painter.drawRect(pos.x()-CHESSSIZE*1.5,pos.y()-CHESSSIZE*1.5,CHESSSIZE,CHESSSIZE);
        }
    }
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
        drawCanMovePos(painter,BoardChessState[i]);
    }
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
    if(GameManager::endOrNot==true)//棋局已結束
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
                move(pos);
            else
                cancelChoose();
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
                move(pos);//移動棋子
                isCheckmate(*MovingChess, pos);
            }
            else//無效移動,取消選擇
                cancelChoose();
        }
    }
}

bool Board::isSameColor(const Chess& ch)
{
    if(ch.colorRB==GameManager::current_player)
        return true;
    return false;
}

bool Board::checkValidMove(const Chess & ch, pair<int,int> nextPos)//選取的位置能不能移動
{
    if(ch.position.first == nextPos.first && ch.position.second == nextPos.second)//兩點相同(未移動)
        return false;

    if(ch.chessType == 1) //GENERAL
    {
        int fieldY;
        if(ch.colorRB==0)//紅棋(下方)
        {
            pair<int, int> black(ch.position.first,0);
            if(numOfChessesBetweenChesses(black,nextPos,1)==0)//如果目標點跟對面最底部之間沒有任何棋子
            {
                int i=0;
                for(;i<BoardChessState.size();i++)
                {   //位置相符且棋子沒死
                    if(black.first==BoardChessState[i]->position.first && black.second==BoardChessState[i]->position.second && !(BoardChessState[i]->isDead()))
                        break;//點擊位置有棋子
                }
                if(BoardChessState[i]->chessType==1)//如果會將帥對臉
                    return false;
            }
            fieldY = 9;
        }
        else            //黑棋(上方)
        {
            pair<int, int> red(ch.position.first,9);
            if(numOfChessesBetweenChesses(red,nextPos,1)==0)//如果目標點跟對面最底部之間沒有任何棋子
            {
                int i=0;
                for(;i<BoardChessState.size();i++)
                {   //位置相符且棋子沒死
                    if(red.first==BoardChessState[i]->position.first && red.second==BoardChessState[i]->position.second && !(BoardChessState[i]->isDead()))
                        break;//點擊位置有棋子
                }
                if(BoardChessState[i]->chessType==1)//如果會將帥對臉
                    return false;
            }
            fieldY = 2;
        }

        if((nextPos.first==3||nextPos.first==4||nextPos.first==5)&&(nextPos.second==fieldY||nextPos.second==fieldY-1||nextPos.second==fieldY-2))//如果目標點在九宮格內
        {
            if((ch.position.second == nextPos.second && ch.position.first+1 == nextPos.first)||(ch.position.second == nextPos.second && ch.position.first-1 == nextPos.first)||(ch.position.second+1 == nextPos.second && ch.position.first == nextPos.first)||(ch.position.second-1 == nextPos.second && ch.position.first == nextPos.first))
            {   //如果移動是一橫格or一直格
                return true;//移動合法
            }
        }
        return false;
    }
    else if (ch.chessType == 2) //ADVISOR
    {
        int fieldY;
        if(ch.colorRB==0)//紅棋(下方)
            fieldY = 9;
        else            //黑棋(上方)
            fieldY = 2;

        if((nextPos.first==3||nextPos.first==4||nextPos.first==5)&&(nextPos.second==fieldY||nextPos.second==fieldY-1||nextPos.second==fieldY-2))//如果目標點在九宮格內
        {
            if((ch.position.second+1 == nextPos.second && ch.position.first+1 == nextPos.first)||(ch.position.second-1 == nextPos.second && ch.position.first-1 == nextPos.first)||(ch.position.second+1 == nextPos.second && ch.position.first-1 == nextPos.first)||(ch.position.second-1 == nextPos.second && ch.position.first+1 == nextPos.first))
            {   //如果移動是斜著走一格
                return true;//移動合法
            }
        }
        return false;
    }
    else if (ch.chessType == 3) //ELEPHANT
    {
        if((ch.position.second+2 == nextPos.second && ch.position.first+2 == nextPos.first)||(ch.position.second-2 == nextPos.second && ch.position.first-2 == nextPos.first)||(ch.position.second+2 == nextPos.second && ch.position.first-2 == nextPos.first)||(ch.position.second-2 == nextPos.second && ch.position.first+2 == nextPos.first))
        {   //如果移動是斜著走兩格
            pair<int, int> center((ch.position.first+nextPos.first)/2,(ch.position.second+nextPos.second)/2);
            if(!existChess(center))//如果沒有塞象眼
            {
                if((ch.colorRB==0&&nextPos.second>4)||(ch.colorRB==1&&nextPos.second<5))
                    return true;//移動合法
            }

        }
        return false;
    }
    else if (ch.chessType == 4) //CHARIOT
    {
        if(ch.position.first == nextPos.first)//兩點在同一條Y軸上
        {
            if(numOfChessesBetweenChesses(ch.position,nextPos,1)==0)//車在Y軸上移動並且中間沒有其他棋子
            {
                return true;//移動合法
            }
            else
            {
                return false;//移動不合法
            }

        }
        else if(ch.position.second == nextPos.second)//兩點在同一條X軸上
        {
            if(numOfChessesBetweenChesses(ch.position,nextPos,0)==0)//車在X軸上移動並且中間沒有其他棋子
            {
                return true;//移動合法
            }
            else
            {
                return false;//移動不合法
            }
        }
        return false;//移動不合法
    }
    else if (ch.chessType == 5) //HORSE
    {
        if((ch.position.second+2 == nextPos.second && ch.position.first+1 == nextPos.first)||(ch.position.second-2 == nextPos.second && ch.position.first-1 == nextPos.first)||(ch.position.second+2 == nextPos.second && ch.position.first-1 == nextPos.first)||(ch.position.second-2 == nextPos.second && ch.position.first+1 == nextPos.first)||(ch.position.second+1 == nextPos.second && ch.position.first+2 == nextPos.first)||(ch.position.second-1 == nextPos.second && ch.position.first-2 == nextPos.first)||(ch.position.second+1 == nextPos.second && ch.position.first-2 == nextPos.first)||(ch.position.second-1 == nextPos.second && ch.position.first+2 == nextPos.first))
        {   //如果移動是一步一尖
            pair<int, int> center(ch.position.first,ch.position.second);
            if((ch.position.first+nextPos.first)%2==0)
                center.first = (ch.position.first+nextPos.first)/2;
            else
                center.second = (ch.position.second+nextPos.second)/2;
            if(!existChess(center))//如果沒有蹩馬腿
            {
                    return true;//移動合法
            }

        }
        return false;
    }
    else if (ch.chessType == 6) //CANNON
    {
        if(ch.position.first == nextPos.first)//兩點在同一條Y軸上
        {
            if(existChess(nextPos))//目標點有棋子
            {
                if(numOfChessesBetweenChesses(ch.position,nextPos,1)==1)//中間是否只有一顆任一方棋子
                {
                    return true;//移動合法
                }
                else
                {
                    return false;//移動不合法
                }
            }
            else//目標點沒有棋子
            {
                if(numOfChessesBetweenChesses(ch.position,nextPos,1)==0)//砲在Y軸上移動並且中間沒有其他棋子
                {
                    return true;//移動合法
                }
                else
                {
                    return false;//移動不合法
                }
            }
        }
        else if(ch.position.second == nextPos.second)//兩點在同一條X軸上
        {

            if(existChess(nextPos))//目標點有棋子
            {
                if(numOfChessesBetweenChesses(ch.position,nextPos,0)==1)//中間是否只有一顆任一方棋子
                {
                    return true;//移動合法
                }
                else
                {
                    return false;//移動不合法
                }
            }
            else//目標點沒有棋子
            {
                if(numOfChessesBetweenChesses(ch.position,nextPos,0)==0)//砲在X軸上移動並且中間沒有其他棋子
                {
                    return true;//移動合法
                }
                else
                {
                    return false;//移動不合法
                }
            }
        }
        return false;//移動不合法
    }
    else if (ch.chessType == 7) //SOLDIER
    {
        if(ch.colorRB==0)//紅棋(下方)
        {
            if(ch.position.second-1 == nextPos.second && ch.position.first == nextPos.first)//士兵為往前一格
            {
                return true;//移動合法
            }
            if(ch.position.second<5)//士兵過河
            {
                if((ch.position.second == nextPos.second && ch.position.first+1 == nextPos.first)||(ch.position.second == nextPos.second && ch.position.first-1 == nextPos.first))//士兵為往左或往右一格
                {
                    return true;//移動合法
                }
            }
            return false;//移動不合法
        }
        else //黑棋(上方)
        {
            if(ch.position.second+1 == nextPos.second && ch.position.first == nextPos.first)//士兵為往前一格
            {
                return true;//移動合法
            }
            if(ch.position.second>4)//士兵過河
            {
                if((ch.position.second == nextPos.second && ch.position.first+1 == nextPos.first)||(ch.position.second == nextPos.second && ch.position.first-1 == nextPos.first))//士兵為往左或往右一格
                {
                    return true;//移動合法
                }
            }
            return false;//移動不合法
        }

    }

    return false;
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

void Board::move(pair<int,int> nextPos)//移動
{
    writeRecord(MovingChess->position,nextPos);
    MovingChess->position.first=nextPos.first;
    MovingChess->position.second=nextPos.second;
    isCheckmate(*MovingChess, nextPos);
    cancelChoose();
    GameManager::changePlayer();
    count++;
    if(count==50)
    {
        count=0;
        GameManager::endOrNot=true;

    }

}

void Board::isCheckmate(const Chess & ch, pair<int,int> pos)//是否將軍
{

    int i=0;
    /*for(;i<BoardChessState.size();i++)
    {
        if(BoardChessState[i]->chessType==1&&BoardChessState[i]->colorRB!=ch.colorRB)
            break;
    }*/
    if(BoardChessState[i]->chessType==1)//如果被吃的是將帥
    { /*GameManager::endOrNot==true;*/
        if (ch.chessType == 4) //CHARIOT
        {
            if(pos.first == BoardChessState[i]->position.first)//兩點在同一條Y軸上
            {
                if(numOfChessesBetweenChesses(pos,BoardChessState[i]->position,1)==0)//車在Y軸上移動並且中間沒有其他棋子
                {
                    GameManager::endOrNot=true;
                }

            }
            else if(pos.second == BoardChessState[i]->position.second)//兩點在同一條X軸上
            {
                if(numOfChessesBetweenChesses(pos,BoardChessState[i]->position,0)==0)//車在X軸上移動並且中間沒有其他棋子
                {
                    GameManager::endOrNot=true;
                }
            }
        }
        else if (ch.chessType == 5) //HORSE
        {
            if((pos.second+2 == BoardChessState[i]->position.second && pos.first+1 == BoardChessState[i]->position.first)||(pos.second-2 == BoardChessState[i]->position.second && pos.first-1 == BoardChessState[i]->position.first)||(pos.second+2 == BoardChessState[i]->position.second && pos.first-1 == BoardChessState[i]->position.first)||(pos.second-2 == BoardChessState[i]->position.second && pos.first+1 == BoardChessState[i]->position.first)||(pos.second+1 == BoardChessState[i]->position.second && pos.first+2 == BoardChessState[i]->position.first)||(pos.second-1 == BoardChessState[i]->position.second && pos.first-2 == BoardChessState[i]->position.first)||(pos.second+1 == BoardChessState[i]->position.second && pos.first-2 == BoardChessState[i]->position.first)||(pos.second-1 == BoardChessState[i]->position.second && pos.first+2 == BoardChessState[i]->position.first))
            {   //如果移動是一步一尖
                pair<int, int> center(pos.first,pos.second);
                if((pos.first+BoardChessState[i]->position.first)%2==0)
                    center.first = (pos.first+BoardChessState[i]->position.first)/2;
                else
                    center.second = (pos.second+BoardChessState[i]->position.second)/2;
                if(!existChess(center))//如果沒有蹩馬腿
                {
                        GameManager::endOrNot=true;
                }
            }
        }
        else if (ch.chessType == 6) //CANNON
        {
            if(pos.first == BoardChessState[i]->position.first)//兩點在同一條Y軸上
            {
                if(numOfChessesBetweenChesses(pos,BoardChessState[i]->position,1)==1)//中間是否只有一顆任一方棋子
                {
                    GameManager::endOrNot=true;
                }

            }
            else if(pos.second == BoardChessState[i]->position.second)//兩點在同一條X軸上
            {
                if(numOfChessesBetweenChesses(pos,BoardChessState[i]->position,0)==1)//中間是否只有一顆任一方棋子
                {
                    GameManager::endOrNot=true;
                }
            }
        }
        else if (ch.chessType == 7) //SOLDIER
        {
            if(ch.colorRB==0)//紅棋(下方)
            {
                if(pos.second-1 == BoardChessState[i]->position.second && pos.first == BoardChessState[i]->position.first)//士兵為往前一格
                {
                    GameManager::endOrNot=true;
                }
                if(pos.second<5)//士兵過河
                {
                    if((pos.second == BoardChessState[i]->position.second && pos.first+1 == BoardChessState[i]->position.first)||(pos.second == BoardChessState[i]->position.second && pos.first-1 == BoardChessState[i]->position.first))//士兵為往左或往右一格
                    {
                        GameManager::endOrNot=true;
                    }
                }
            }
            else //黑棋(上方)
            {
                if(pos.second+1 == BoardChessState[i]->position.second &&pos.first == BoardChessState[i]->position.first)//士兵為往前一格
                {
                    GameManager::endOrNot=true;
                }
                if(pos.second>4)//士兵過河
                {
                    if((pos.second == BoardChessState[i]->position.second && pos.first+1 == BoardChessState[i]->position.first)||(pos.second == BoardChessState[i]->position.second && pos.first-1 == BoardChessState[i]->position.first))//士兵為往左或往右一格
                    {
                        GameManager::endOrNot=true;
                    }
                }
            }
        }
    }
}

void Board::writeRecord(pair<int,int> nowPos, pair<int,int> nextPos)//寫檔
{
    QFile file(GameManager::fileN);
    if (!file.open(QIODevice::Append | QIODevice::Text))
    {
        qDebug() << "Cannot open file for writing:" << qPrintable(file.errorString());
        return;
    }
    QTextStream output(&file);
    QString str("Player: ");
    str+=QString::number(GameManager::current_player + 1);
    str+=", Action: ";
    switch(MovingChess->chessType)
    {
    case  Chess::Type::GENERAL:
        str+="General ";
        break;
    case  Chess::Type::ADVISOR:
        str+="Advisor ";
        break;
    case  Chess::Type::ELEPHANT:
        str+="Elephant ";
        break;
    case  Chess::Type::CHARIOT:
        str+="Chariot ";
        break;
    case  Chess::Type::HORSE:
        str+="Horse ";
        break;
    case  Chess::Type::CANNON:
        str+="Cannon ";
        break;
    case  Chess::Type::SOLDIER:
        str+="Soldier ";
        break;
    default:
        break;
    }
    //(6, 3) -> (6, 4)
    str+="("+QString::number(nowPos.first)+", "+QString::number(nowPos.second)
            +") -> ("+QString::number(nextPos.first)+", "+QString::number(nextPos.second)+")";
    output<< str << "\n";
    file.close();

    //遊戲誰贏也要寫
}

int Board::numOfChessesBetweenChesses(pair<int,int> nowPos,pair<int,int> nextPos,int XorY)  //回傳兩顆棋子之間有多少棋子 X = 0 Y = 1(???????????????
{
    int num=0,bigNum,smallNum;
    pair<int, int> checkedPos(nowPos.first, nowPos.second);
    if(XorY==0)//檢查兩棋之間的X軸
    {
        if(nowPos.first>nextPos.first)
        {
            bigNum = nowPos.first;
            smallNum = nextPos.first+1;
        }
        else
        {
            bigNum = nextPos.first;
            smallNum = nowPos.first+1;
        }
        for(int i = smallNum;i<bigNum;i++)
        {
            checkedPos.first = i;
            if(existChess(checkedPos))
                num++;
        }
    }
    else//檢查兩棋之間的Y軸
    {
        if(nowPos.second>nextPos.second)
        {
            bigNum = nowPos.second;
            smallNum = nextPos.second+1;
        }
        else
        {
            bigNum = nextPos.second;
            smallNum = nowPos.second+1;
        }
        for(int i = smallNum;i<bigNum;i++)
        {
            checkedPos.second = i;
            if(existChess(checkedPos))
                num++;
        }
    }
    return num;
}
