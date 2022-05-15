#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <QApplication>
#include <QDebug>
#include "viewer.h"
#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QTime>
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
    static QString fileN;//檔案名
    Board board;//控制盤面狀況
    Viewer viewer;//盤面顯示更新
    void resetOn_Board();
    void viewMenu();//主畫面
    void newGame();//建立新局
    void createNewFile();//建立新遊戲txt檔
    void loadGame();//讀txt檔
    //if(board.isEnd())
    //else{change current_player}
    //bool isEnd(){return endOrNot;};//其中一方的將軍死亡.遊戲是否結束
    bool askNewGame();//棋局結束後是否開新局
    static void changePlayer();
    static bool endOrNot;//預設false

private slots:
    void on_StartGameButton_clicked();

    void on_LeaveGameButton_clicked();

    void on_LoadGameButton_clicked();

private:
    Ui::GameManager *ui;
};

#endif // GAMEMANAGER_H
