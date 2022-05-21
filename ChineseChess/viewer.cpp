#include "viewer.h"
#include "gamemanager.h"

Viewer::Viewer()
{

}

Viewer::~Viewer()
{

}

void Viewer::viewMenu()
{
}

void Viewer::viewBoard(Board &board)
{
    board.show();
}

void Viewer::showWhoWin()
{
    QMessageBox msgBox;
    if(GameManager::winPlayer==0)
        msgBox.setText("紅方勝利");
    else
        msgBox.setText("黑方勝利");
    msgBox.exec();
}

void Viewer::closeBoard(Board &board)
{
    board.close();
}

bool Viewer::askNewGame()
{
    QMessageBox::StandardButtons ask;
    ask=QMessageBox::information(NULL,"勝負已分","是否開始新局?",QMessageBox::Yes|QMessageBox::No);
    if(ask==QMessageBox::Yes)
        return true;
    else
        return false;
}
