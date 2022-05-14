/********************************************************************************
** Form generated from reading UI file 'viewer.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWER_H
#define UI_VIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Viewer
{
public:
    QPushButton *StartGameButton;
    QPushButton *LoadGameButton;
    QPushButton *LeaveButton;

    void setupUi(QWidget *Viewer)
    {
        if (Viewer->objectName().isEmpty())
            Viewer->setObjectName(QString::fromUtf8("Viewer"));
        Viewer->resize(800, 600);
        Viewer->setMaximumSize(QSize(800, 600));
        StartGameButton = new QPushButton(Viewer);
        StartGameButton->setObjectName(QString::fromUtf8("StartGameButton"));
        StartGameButton->setGeometry(QRect(280, 290, 201, 61));
        QFont font;
        font.setPointSize(16);
        StartGameButton->setFont(font);
        LoadGameButton = new QPushButton(Viewer);
        LoadGameButton->setObjectName(QString::fromUtf8("LoadGameButton"));
        LoadGameButton->setGeometry(QRect(280, 370, 201, 61));
        LoadGameButton->setFont(font);
        LeaveButton = new QPushButton(Viewer);
        LeaveButton->setObjectName(QString::fromUtf8("LeaveButton"));
        LeaveButton->setGeometry(QRect(280, 450, 201, 61));
        LeaveButton->setFont(font);

        retranslateUi(Viewer);

        QMetaObject::connectSlotsByName(Viewer);
    } // setupUi

    void retranslateUi(QWidget *Viewer)
    {
        Viewer->setWindowTitle(QCoreApplication::translate("Viewer", "Form", nullptr));
        StartGameButton->setText(QCoreApplication::translate("Viewer", "\351\226\213\345\247\213\351\201\212\346\210\262", nullptr));
        LoadGameButton->setText(QCoreApplication::translate("Viewer", "\350\256\200\345\217\226\351\201\212\346\210\262", nullptr));
        LeaveButton->setText(QCoreApplication::translate("Viewer", "\351\233\242\351\226\213\351\201\212\346\210\262", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Viewer: public Ui_Viewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWER_H
