#ifndef BOARD_H
#define BOARD_H
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include "chess.h"

#define CHESSSIZE 20//棋子半徑
#define BOUNDARY 70//介面邊界和棋盤邊緣距離
#define GRID_WIDTH 60//格子的間隔寬度

#define ROW 10//10行橫線
#define COLUMN 9//9行直線
class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = nullptr);
    void reset();//重置所有棋子狀態&endOrNot
    //void createChess();//建構棋子>>寫在reset

    void getCanMove();//取得目前棋子可以移動的位置

    bool isEnd() { return endOrNot; };//遊戲是否結束

    virtual void paintEvent(QPaintEvent*);//畫棋盤
    void drawChess(QPainter& painter, const Chess* c);//畫棋子

    QPoint location(int row, int column);//棋盤座標轉介面座標
    QPoint location(const Chess& ch);//棋子的棋盤座標轉介面座標

    virtual void mouseReleaseEvent(QMouseEvent* ev);//滑鼠左鍵點擊
    void click(QPoint p);//有滑鼠點擊事件發生
    pair<int,int> isClickChess(int row, int column,QPoint p);//判斷有沒有點到交叉格(可能有棋子的位置)
    bool existChess(pair<int,int> pos);//點擊位置有沒有棋子
    void chooseMovePiece(pair<int,int> pos);//選擇要移動的棋子
    void chooseMovePosition(pair<int,int> pos);//選擇棋子要移動的位置
    bool isSameColor(const Chess& ch);//點選的棋子和目前攻方是否同色
    bool checkValidMove(const Chess & ch, pair<int,int> nextPos);//選取的位置能不能移動
    void cancelChoose();
    void killChess(pair<int,int> pos);//吃子
    void move(pair<int,int> nowPos, pair<int,int> nextPos);//移動
    bool isCheckmate();//是否將軍
    void writeRecord(pair<int,int> nowPos, pair<int,int> nextPos);//寫檔
    bool endOrNot;//預設false
private:
    vector<Chess*> BoardChessState;//盤面全部棋子的位置
    bool selectOrNot;//是否選取要移動的棋子,預設false
    Chess *MovingChess;//預設空Chess

signals:

};

#endif // BOARD_H
