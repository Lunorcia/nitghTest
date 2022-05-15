#include "gamemanager.h"
//#include "board.h"

#include "mainwindow.h"

//#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*  中文文字翻譯  */
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "ChineseChess_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    /*  中文文字翻譯  */

    GameManager w;
     w.viewMenu();
    /*while(1)
    {
        while(!w.isEnd())
        {
            //遊戲進行
        }
        if(w.askNewGame())
        {
            w.newGame();
        }

    }*/




    return a.exec();
}
