#pragma once
#include <iostream>
#include <vector>
using namespace std;
#define CHESSSIZE 20//�Ѥl�b�|
#define BOUNDARY 60//������ɩM�ѽL��t�Z��
#define GRID_WIDTH 50//��l�����j�e��

#define ROW 10//10���u
#define COLUMN 9//9�檽�u
class Board
{
public:
	void reset();//���m�Ҧ��Ѥl���A&endOrNot
	void createChess();//�غc�Ѥl
	void choosePiece(int row, int column);//��ܭn���ʪ��X�l
	//void existChess();���ʦ�m�W���S���Ѥl
	void getCanMove();//���o�ثe�Ѥl�i�H���ʪ���m

	bool isEnd() { return endOrNot; };//�C���O�_����
	bool checkValidMove(int nowPos, int nextPos);//�������m�ण�ಾ��
	void killChess();//�Y�l�M�Ჾ��(move)
	void move(int nowPos,int nextPos);//����
	bool isCheckmate();//�O�_�N�x

	QPoint location(int row, int column);//�ѽL�y���श���y��
	QPoint location(const Chess& ch);//�Ѥl���ѽL�y���श���y��
	QPoint getRealLocation(QPoint pt);//���ƹ����o�y���ഫPainter�y��
	virtual void paintEvent(QPaintEvent*);//�e�ѽL
	void drawChess(QPainter& painter, int id);//�e�Ѥl

	virtual void clickChess(int row, int column);
	virtual void mousePressEvent(QMouseEvent*);//�ƹ������I��

	bool endOrNot;//�w�]false

private:
	vector<vector<Chess*>> BoardChessState;//�L�������Ѥl����m
};

