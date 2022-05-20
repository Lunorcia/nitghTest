/********************************************************************************
** Form generated from reading UI file 'gamemanager.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEMANAGER_H
#define UI_GAMEMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameManager
{
public:
    QWidget *centralwidget;
    QPushButton *StartGameButton;
    QPushButton *LoadGameButton;
    QPushButton *LeaveGameButton;
    QLabel *label;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *GameManager)
    {
        if (GameManager->objectName().isEmpty())
            GameManager->setObjectName(QString::fromUtf8("GameManager"));
        GameManager->resize(800, 800);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\273\237\346\255\243\351\273\221\351\253\224"));
        font.setPointSize(10);
        GameManager->setFont(font);
        centralwidget = new QWidget(GameManager);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        StartGameButton = new QPushButton(centralwidget);
        StartGameButton->setObjectName(QString::fromUtf8("StartGameButton"));
        StartGameButton->setGeometry(QRect(270, 220, 211, 71));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\273\237\346\255\243\351\273\221\351\253\224"));
        font1.setPointSize(16);
        StartGameButton->setFont(font1);
        LoadGameButton = new QPushButton(centralwidget);
        LoadGameButton->setObjectName(QString::fromUtf8("LoadGameButton"));
        LoadGameButton->setGeometry(QRect(270, 320, 211, 71));
        LoadGameButton->setFont(font1);
        LeaveGameButton = new QPushButton(centralwidget);
        LeaveGameButton->setObjectName(QString::fromUtf8("LeaveGameButton"));
        LeaveGameButton->setGeometry(QRect(270, 420, 211, 71));
        LeaveGameButton->setFont(font1);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(240, 100, 271, 91));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\346\250\231\346\245\267\351\253\224"));
        font2.setPointSize(28);
        label->setFont(font2);
        label->setAlignment(Qt::AlignCenter);
        GameManager->setCentralWidget(centralwidget);
        menubar = new QMenuBar(GameManager);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 29));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\346\250\231\346\245\267\351\253\224"));
        menu->setFont(font3);
        GameManager->setMenuBar(menubar);
        statusbar = new QStatusBar(GameManager);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        GameManager->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());

        retranslateUi(GameManager);

        QMetaObject::connectSlotsByName(GameManager);
    } // setupUi

    void retranslateUi(QMainWindow *GameManager)
    {
        GameManager->setWindowTitle(QCoreApplication::translate("GameManager", "MainWindow", nullptr));
        StartGameButton->setText(QCoreApplication::translate("GameManager", "\351\226\213\345\247\213\351\201\212\346\210\262", nullptr));
        LoadGameButton->setText(QCoreApplication::translate("GameManager", "\350\256\200\345\217\226\346\252\224\346\241\210", nullptr));
        LeaveGameButton->setText(QCoreApplication::translate("GameManager", "\351\233\242\351\226\213\351\201\212\346\210\262", nullptr));
        label->setText(QCoreApplication::translate("GameManager", "\344\270\255\345\234\213\350\261\241\346\243\213", nullptr));
        menu->setTitle(QCoreApplication::translate("GameManager", "\344\270\255\345\234\213\350\261\241\346\243\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameManager: public Ui_GameManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEMANAGER_H
