    #include "gamemanager.h"
#include "ui_gamemanager.h"
int GameManager::current_player=0;
QString GameManager::fileN=0;
bool GameManager::endOrNot=false;
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

void GameManager::resetOn_Board()
{
    for(int i=0;i<board.BoardChessState.size();i++)
    {
        on_board.push_back(board.BoardChessState[i]);
    }
}

void GameManager::viewMenu()//主畫面
{
    GameManager *w=new GameManager(this);
    viewer.viewMenu();
    this->show();
    qDebug() <<this;
    qDebug() <<w;
}

void GameManager::newGame()//建立新局
{
    on_board.clear();
    current_player=0;
    endOrNot=false;
    fileN="";
    board.reset();
    resetOn_Board();
    createNewFile();
    viewer.viewBoard(board);
    while(!endOrNot)
    {
        //遊戲進行中
        QTime t;
        t.start();
        while(t.elapsed()<1000)
        {
            QCoreApplication::processEvents();
        }
    }
    if(askNewGame())
    {
        newGame();
    }
    else
        viewMenu();
}

void GameManager::createNewFile()//建立新遊戲txt檔
{
    QString str("log_");
    qsrand(time(NULL));
    for(int i=0;i<10;i++)
    {
        int r=qrand()%10;
        str += QString::number(r);
    }
    str+=".txt";
    QFile file(str);
    QFileInfo fileinfo(file);
    qDebug() <<fileinfo.filePath();

    if(!file.open(QIODevice::ReadWrite| QIODevice::Text))
    {
        qDebug() << "Cannot open file for reading:" << qPrintable(file.errorString());
        return;
    }
    fileN=str;
}

void GameManager::loadGame()//讀txt檔
{
    QString fileName=QFileDialog::getOpenFileName(NULL,QObject::tr("Text file"),qApp->applicationDirPath(),QObject::tr("Files (*.txt)"));
    fileN=fileName;
    QFile file(fileName);
    //qDebug()<<fileN;
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "Cannot open file for reading:" << qPrintable(file.errorString());
        return;
    }
    this->hide();//讀檔成功收起面板
    QTextStream input(&file);
    while(!input.atEnd())
    {
        QString moveCmd=input.readLine();
        //qDebug()<<moveCmd;
        board.stringControl(moveCmd);
        if(endOrNot==true)//棋局已經有勝負
            break;

    }
    viewer.viewBoard(board);
    file.close();
    while(!endOrNot)
    {   //遊戲進行中
        QTime t;
        t.start();
        while(t.elapsed()<1000)
        {
            QCoreApplication::processEvents();
        }

    }
    if(askNewGame())
    {
        board.reset();
        newGame();
    }
    else
    {
        viewer.closeBoard(board);
        viewMenu();
    }


}

bool GameManager::askNewGame()//棋局結束後是否開新局
{
    //viewer.closeBoard(board);
    return viewer.askNewGame();
    /*if(viewer.askNewGame())
    {
        viewer.closeBoard(board);
        newGame();
    }
    else
    {
        viewer.closeBoard(board);
        viewMenu();
    }*/
}

void GameManager::changePlayer()
{

    current_player=(current_player+1) % 2;
}

void GameManager::on_StartGameButton_clicked()
{
    this->hide();
    newGame();
}

void GameManager::on_LoadGameButton_clicked()
{

    loadGame();

}

void GameManager::on_LeaveGameButton_clicked()
{
    this->close();
}
