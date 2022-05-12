#pragma once
#include <iostream>
#include <vector>
#include "Chess.h"
#include "Viewer.h"
#include "Board.h"
using namespace std;
class GameManager
{
	GameManager();
	~GameManager();
	vector<Chess> on_board;//�٦b�L���W���Ѥl������
	int current_player;//�����/�ª��a//�w�]�_�l��
	Board board;//����L�����p
	Viewer viewer;//�L����ܧ�s
	
	void newGame();//�إ߷s��
	//if(board.isEnd())
	//else{change current_player}
	bool askNewGame();//�ѧ�������O�_�}�s��
	void changePlayer();



	//�P�_�I����m
	//POINT pt;
	//BOOL bReturn = GetCursorPos(&pt); //����ƹ����Ц�m��pt
	// if (bReturn != 0) //�p�G�禡���榨�\
	//cout << "Cursor postition is: " << pt.x << "," << pt.y << endl; //���pt�������
	//else //�p�G�禡�S�����榨�\ //cout << "Error!" << endl; //����
	// 
	//�I����m�W���S���Ѥl>�S���A�~��Ū��>���A�P�_�Ѥl�C��O���O���
	//���O���A�~�򵥫ݧP�_�I����m>�O���A��w���n���ʪ���
	//�P�_�U�@���I����m
	//�U�@���I����m�O�Ѥl�O��誺�ѡA�ഫ�n���ʪ��ѡA���ݤU�@���I��>���O��誺�ѡA�P�_���ʮy�ЬO�_����>���Ĳ��ʦY�l�A�L���~�򵥫ݤU�@���I��
	//�U�@���I����m�O�Ū�>�P�_���ʮy�ЬO�_����>���Ĳ��ʡA�L���~�򵥫ݤU�@���I��
};

