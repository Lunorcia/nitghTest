#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "chess.h"
#include "viewer.h"
#include "board.h"
using namespace std;

class GameManager
{
public:
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
};

#endif // GAMEMANAGER_H
