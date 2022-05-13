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
    void choosePiece(int row, int column);//選擇要移動的旗子
    bool existChess();//移動位置上有沒有棋子
    bool isSameColor();
    void getCanMove();//取得目前棋子可以移動的位置

    bool isEnd() { return endOrNot; };//遊戲是否結束
    bool checkValidMove(int nowPos, int nextPos);//選取的位置能不能移動
    void killChess();//吃子然後移動(move)
    void move(int nowPos,int nextPos);//移動
    bool isCheckmate();//是否將軍

    QPoint location(int row, int column);//棋盤座標轉介面座標
    QPoint location(const Chess& ch);//棋子的棋盤座標轉介面座標
    //QPoint getRealLocation(QPoint pt);//讓滑鼠取得座標轉換Painter座標

    virtual void paintEvent(QPaintEvent*);//畫棋盤
    void drawChess(QPainter& painter, const Chess* c);//畫棋子


    virtual void mouseReleaseEvent(QMouseEvent* ev);//滑鼠左鍵點擊
    void click(QPoint p);//有滑鼠點擊事件發生
    pair<int,int> isClickChess(int row, int column,QPoint p);//判斷有沒有點到交叉格(可能有棋子的位置)
    bool endOrNot;//預設false

private:
    vector<Chess*> BoardChessState;//盤面全部棋子的位置
    bool selectOrNot;//是否選取要移動的棋子,預設false

signals:

};

#endif // BOARD_H
