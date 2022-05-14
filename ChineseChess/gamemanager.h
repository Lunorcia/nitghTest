#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "viewer.h"
#include <QMainWindow>

namespace Ui {
class GameManager;
}

class GameManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameManager(QWidget *parent = nullptr);
    ~GameManager();
    vector<Chess*> on_board;//還在盤面上的棋子有哪些
    static int current_player;//輪到紅0/黑1玩家//預設起始紅
    Board board;//控制盤面狀況
    Viewer viewer;//盤面顯示更新

    void viewMenu();//主畫面
    void newGame();//建立新局
    //if(board.isEnd())
    //else{change current_player}
    bool askNewGame();//棋局結束後是否開新局
    static void changePlayer();

private slots:
    void on_StartGameButton_clicked();

    void on_LeaveGameButton_clicked();

private:
    Ui::GameManager *ui;
};

#endif // GAMEMANAGER_H
