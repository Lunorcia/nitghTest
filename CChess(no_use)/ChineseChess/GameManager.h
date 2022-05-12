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
	vector<Chess> on_board;//還在盤面上的棋子有哪些
	int current_player;//輪到紅/黑玩家//預設起始紅
	Board board;//控制盤面狀況
	Viewer viewer;//盤面顯示更新
	
	void newGame();//建立新局
	//if(board.isEnd())
	//else{change current_player}
	bool askNewGame();//棋局結束後是否開新局
	void changePlayer();



	//判斷點擊位置
	//POINT pt;
	//BOOL bReturn = GetCursorPos(&pt); //獲取滑鼠指標位置到pt
	// if (bReturn != 0) //如果函式執行成功
	//cout << "Cursor postition is: " << pt.x << "," << pt.y << endl; //顯示pt中的資料
	//else //如果函式沒有執行成功 //cout << "Error!" << endl; //報錯
	// 
	//點擊位置上有沒有棋子>沒有，繼續讀取>有，判斷棋子顏色是不是攻方
	//不是攻方，繼續等待判斷點擊位置>是攻方，選定為要移動的棋
	//判斷下一個點擊位置
	//下一個點擊位置是棋子是攻方的棋，轉換要移動的棋，等待下一次點擊>不是攻方的棋，判斷移動座標是否有效>有效移動吃子，無效繼續等待下一次點擊
	//下一個點擊位置是空的>判斷移動座標是否有效>有效移動，無效繼續等待下一次點擊
};

