#pragma once
#include <iostream>
#include <vector>
using namespace std;
class Chess
{
public:
	Chess();
	virtual void Move();
	int RB;//��0��1
	pair<int, int> position;//first=row,second=column
};

class General:public Chess//�N/��
{
public:
	General();
	virtual void Move();//�E�c��
};

class Mandarin :public Chess//�h
{
public:
	Mandarin();
	virtual void Move();//�E�c��׽u
};

class Elephant :public Chess//�H
{
public:
	Elephant();
	virtual void Move();//�Цr�ר����A�Цr���ߦ��Ѥ��ਫ
};

class Rook :public Chess//��
{
public:
	Rook();
	virtual void Move();//����N��
};

class Horse :public Chess//��
{
public:
	Horse();
	virtual void Move();//��r���k(�e�i�@�B+�ר��@�B)�A�e�i��V���Ѥ��ਫ
};

class Cannon :public Chess//��
{
public:
	Cannon();
	virtual void Move();//����N���A�Y�l�n�j�@��
};

class Soldier :public Chess//�L/��
{
public:
	Soldier();
	bool crossRiver;//false���L true�w�L
	virtual void Move();//�����@�B�A�L�e�i���k�A����h��
};