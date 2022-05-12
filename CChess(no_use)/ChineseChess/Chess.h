#pragma once
#include <iostream>
#include <vector>
using namespace std;
class Chess
{
public:
	Chess();
	bool isDead();
	virtual void canMovePos();
	int colorRB;//��0��1
	bool dead;//�w�]false
	pair<int, int> position;//first=row,second=column
};

class General:public Chess//�N/��
{
public:
	General();
	virtual void canMovePos();//�E�c��
};

class Mandarin :public Chess//�h
{
public:
	Mandarin();
	virtual void canMovePos();//�E�c��׽u
};

class Elephant :public Chess//�H
{
public:
	Elephant();
	virtual void canMovePos();//�Цr�ר����A�Цr���ߦ��Ѥ��ਫ
};

class Rook :public Chess//��
{
public:
	Rook();
	virtual void canMovePos();//����N��
};

class Horse :public Chess//��
{
public:
	Horse();
	virtual void canMovePos();//��r���k(�e�i�@�B+�ר��@�B)�A�e�i��V���Ѥ��ਫ
};

class Cannon :public Chess//��
{
public:
	Cannon();
	virtual void canMovePos();//����N���A�Y�l�n�j�@��
};

class Soldier :public Chess//�L/��
{
public:
	Soldier();
	bool crossRiver;//false���L true�w�L
	virtual void canMovePos();//�����@�B�A�L�e�i���k�A����h��
};