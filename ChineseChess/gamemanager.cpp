#include "gamemanager.h"
#include "ui_gamemanager.h"
int GameManager::current_player=0;
GameManager::GameManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameManager)
{
    ui->setupUi(this);
    on_board.clear();
}

GameManager::~GameManager()
{
    delete ui;
}

void GameManager::viewMenu()//主畫面
{
    viewer.viewMenu();
    this->show();
}

void GameManager::newGame()//建立新局
{
    viewer.viewBoard(board);
}

bool GameManager::askNewGame()//棋局結束後是否開新局
{
    return true;
}

void GameManager::changePlayer()
{
    current_player=(current_player+1) % 2;
}

void GameManager::on_StartGameButton_clicked()
{
    this->close();
    viewer.viewBoard(board);
}


void GameManager::on_LeaveGameButton_clicked()
{
    this->close();
}

