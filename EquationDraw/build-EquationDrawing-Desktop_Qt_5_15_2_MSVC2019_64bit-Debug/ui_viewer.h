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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_Viewer
{
public:
    QWidget *centralwidget;
    QCustomPlot *customPlot;
    QWidget *equationWidget;
    QPushButton *addEquationButton;
    QLineEdit *Equation1;
    QLineEdit *Equation2;
    QLineEdit *lineEdit_3;
    QLineEdit *Equation3;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_6;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Viewer)
    {
        if (Viewer->objectName().isEmpty())
            Viewer->setObjectName(QString::fromUtf8("Viewer"));
        Viewer->resize(1065, 637);
        centralwidget = new QWidget(Viewer);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        customPlot = new QCustomPlot(centralwidget);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));
        customPlot->setGeometry(QRect(29, 29, 571, 551));
        equationWidget = new QWidget(centralwidget);
        equationWidget->setObjectName(QString::fromUtf8("equationWidget"));
        equationWidget->setGeometry(QRect(630, 400, 341, 181));
        addEquationButton = new QPushButton(centralwidget);
        addEquationButton->setObjectName(QString::fromUtf8("addEquationButton"));
        addEquationButton->setGeometry(QRect(630, 30, 93, 29));
        Equation1 = new QLineEdit(centralwidget);
        Equation1->setObjectName(QString::fromUtf8("Equation1"));
        Equation1->setGeometry(QRect(630, 80, 280, 25));
        Equation2 = new QLineEdit(centralwidget);
        Equation2->setObjectName(QString::fromUtf8("Equation2"));
        Equation2->setGeometry(QRect(630, 110, 280, 25));
        lineEdit_3 = new QLineEdit(centralwidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(630, 170, 280, 25));
        Equation3 = new QLineEdit(centralwidget);
        Equation3->setObjectName(QString::fromUtf8("Equation3"));
        Equation3->setGeometry(QRect(630, 140, 280, 25));
        lineEdit_5 = new QLineEdit(centralwidget);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(630, 230, 280, 25));
        lineEdit_6 = new QLineEdit(centralwidget);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        lineEdit_6->setGeometry(QRect(630, 200, 280, 25));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(910, 80, 49, 25));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(910, 110, 49, 25));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(910, 170, 49, 25));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(910, 140, 49, 25));
        Viewer->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Viewer);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1065, 26));
        Viewer->setMenuBar(menubar);
        statusbar = new QStatusBar(Viewer);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Viewer->setStatusBar(statusbar);

        retranslateUi(Viewer);

        QMetaObject::connectSlotsByName(Viewer);
    } // setupUi

    void retranslateUi(QMainWindow *Viewer)
    {
        Viewer->setWindowTitle(QCoreApplication::translate("Viewer", "Viewer", nullptr));
        addEquationButton->setText(QCoreApplication::translate("Viewer", "Add", nullptr));
        pushButton->setText(QCoreApplication::translate("Viewer", "D", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Viewer", "D", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Viewer", "D", nullptr));
        pushButton_4->setText(QCoreApplication::translate("Viewer", "D", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Viewer: public Ui_Viewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWER_H
