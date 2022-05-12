#pragma once
#include <iostream>
#include <vector>
using namespace std;
#define CHESSSIZE 20//棋子半徑
#define BOUNDARY 60//介面邊界和棋盤邊緣距離
#define GRID_WIDTH 50//格子的間隔寬度

#define ROW 10//10行橫線
#define COLUMN 9//9行直線
class Board
{
public:
	void reset();//重置所有棋子狀態&endOrNot
	void createChess();//建構棋子
	void choosePiece(int row, int column);//選擇要移動的旗子
	//void existChess();移動位置上有沒有棋子
	void getCanMove();//取得目前棋子可以移動的位置

	bool isEnd() { return endOrNot; };//遊戲是否結束
	bool checkValidMove(int nowPos, int nextPos);//選取的位置能不能移動
	void killChess();//吃子然後移動(move)
	void move(int nowPos,int nextPos);//移動
	bool isCheckmate();//是否將軍

	QPoint location(int row, int column);//棋盤座標轉介面座標
	QPoint location(const Chess& ch);//棋子的棋盤座標轉介面座標
	QPoint getRealLocation(QPoint pt);//讓滑鼠取得座標轉換Painter座標
	virtual void paintEvent(QPaintEvent*);//畫棋盤
	void drawChess(QPainter& painter, int id);//畫棋子

	virtual void clickChess(int row, int column);
	virtual void mousePressEvent(QMouseEvent*);//滑鼠左鍵點擊

	bool endOrNot;//預設false

private:
	vector<vector<Chess*>> BoardChessState;//盤面全部棋子的位置
};

