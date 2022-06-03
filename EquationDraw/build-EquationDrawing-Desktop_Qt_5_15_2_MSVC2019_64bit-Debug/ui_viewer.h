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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
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
    QLabel *label;
    QPushButton *addEquationButton;
    QLineEdit *Equation1;
    QLineEdit *Equation2;
    QLineEdit *Equation4;
    QLineEdit *Equation3;
    QLineEdit *Equation6;
    QLineEdit *Equation5;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QLineEdit *Equation7;
    QPushButton *pushButton_8;
    QLineEdit *Equation8;
    QLineEdit *Equation9;
    QLineEdit *Equation10;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QCheckBox *checkBox_1;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_6;
    QCheckBox *checkBox_7;
    QCheckBox *checkBox_8;
    QCheckBox *checkBox_9;
    QCheckBox *checkBox_10;
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
        label = new QLabel(equationWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 10, 251, 21));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        addEquationButton = new QPushButton(centralwidget);
        addEquationButton->setObjectName(QString::fromUtf8("addEquationButton"));
        addEquationButton->setGeometry(QRect(630, 30, 93, 29));
        Equation1 = new QLineEdit(centralwidget);
        Equation1->setObjectName(QString::fromUtf8("Equation1"));
        Equation1->setGeometry(QRect(630, 80, 280, 25));
        Equation2 = new QLineEdit(centralwidget);
        Equation2->setObjectName(QString::fromUtf8("Equation2"));
        Equation2->setGeometry(QRect(630, 110, 280, 25));
        Equation4 = new QLineEdit(centralwidget);
        Equation4->setObjectName(QString::fromUtf8("Equation4"));
        Equation4->setGeometry(QRect(630, 170, 280, 25));
        Equation3 = new QLineEdit(centralwidget);
        Equation3->setObjectName(QString::fromUtf8("Equation3"));
        Equation3->setGeometry(QRect(630, 140, 280, 25));
        Equation6 = new QLineEdit(centralwidget);
        Equation6->setObjectName(QString::fromUtf8("Equation6"));
        Equation6->setGeometry(QRect(630, 230, 280, 25));
        Equation5 = new QLineEdit(centralwidget);
        Equation5->setObjectName(QString::fromUtf8("Equation5"));
        Equation5->setGeometry(QRect(630, 200, 280, 25));
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
        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(910, 320, 49, 25));
        pushButton_6 = new QPushButton(centralwidget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(910, 350, 49, 25));
        pushButton_7 = new QPushButton(centralwidget);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(910, 290, 49, 25));
        Equation7 = new QLineEdit(centralwidget);
        Equation7->setObjectName(QString::fromUtf8("Equation7"));
        Equation7->setGeometry(QRect(630, 260, 280, 25));
        pushButton_8 = new QPushButton(centralwidget);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(910, 260, 49, 25));
        Equation8 = new QLineEdit(centralwidget);
        Equation8->setObjectName(QString::fromUtf8("Equation8"));
        Equation8->setGeometry(QRect(630, 290, 280, 25));
        Equation9 = new QLineEdit(centralwidget);
        Equation9->setObjectName(QString::fromUtf8("Equation9"));
        Equation9->setGeometry(QRect(630, 320, 280, 25));
        Equation10 = new QLineEdit(centralwidget);
        Equation10->setObjectName(QString::fromUtf8("Equation10"));
        Equation10->setGeometry(QRect(630, 350, 280, 25));
        pushButton_9 = new QPushButton(centralwidget);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(910, 230, 49, 25));
        pushButton_10 = new QPushButton(centralwidget);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setGeometry(QRect(910, 200, 49, 25));
        checkBox_1 = new QCheckBox(centralwidget);
        checkBox_1->setObjectName(QString::fromUtf8("checkBox_1"));
        checkBox_1->setGeometry(QRect(890, 80, 16, 24));
        checkBox_2 = new QCheckBox(centralwidget);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setGeometry(QRect(890, 110, 16, 24));
        checkBox_3 = new QCheckBox(centralwidget);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setGeometry(QRect(890, 140, 16, 24));
        checkBox_4 = new QCheckBox(centralwidget);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        checkBox_4->setGeometry(QRect(890, 170, 16, 24));
        checkBox_5 = new QCheckBox(centralwidget);
        checkBox_5->setObjectName(QString::fromUtf8("checkBox_5"));
        checkBox_5->setGeometry(QRect(890, 200, 16, 24));
        checkBox_6 = new QCheckBox(centralwidget);
        checkBox_6->setObjectName(QString::fromUtf8("checkBox_6"));
        checkBox_6->setGeometry(QRect(890, 230, 16, 24));
        checkBox_7 = new QCheckBox(centralwidget);
        checkBox_7->setObjectName(QString::fromUtf8("checkBox_7"));
        checkBox_7->setGeometry(QRect(890, 260, 16, 24));
        checkBox_8 = new QCheckBox(centralwidget);
        checkBox_8->setObjectName(QString::fromUtf8("checkBox_8"));
        checkBox_8->setGeometry(QRect(890, 290, 16, 24));
        checkBox_9 = new QCheckBox(centralwidget);
        checkBox_9->setObjectName(QString::fromUtf8("checkBox_9"));
        checkBox_9->setGeometry(QRect(890, 320, 16, 24));
        checkBox_10 = new QCheckBox(centralwidget);
        checkBox_10->setObjectName(QString::fromUtf8("checkBox_10"));
        checkBox_10->setGeometry(QRect(890, 350, 16, 24));
        Viewer->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Viewer);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1065, 26));
        Viewer->setMenuBar(menubar);
        statusbar = new QStatusBar(Viewer);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Viewer->setStatusBar(statusbar);
        QWidget::setTabOrder(addEquationButton, Equation1);
        QWidget::setTabOrder(Equation1, Equation2);
        QWidget::setTabOrder(Equation2, Equation4);
        QWidget::setTabOrder(Equation4, Equation3);
        QWidget::setTabOrder(Equation3, Equation6);
        QWidget::setTabOrder(Equation6, Equation5);
        QWidget::setTabOrder(Equation5, pushButton);
        QWidget::setTabOrder(pushButton, pushButton_2);
        QWidget::setTabOrder(pushButton_2, pushButton_3);
        QWidget::setTabOrder(pushButton_3, pushButton_4);
        QWidget::setTabOrder(pushButton_4, pushButton_5);
        QWidget::setTabOrder(pushButton_5, pushButton_6);
        QWidget::setTabOrder(pushButton_6, pushButton_7);
        QWidget::setTabOrder(pushButton_7, Equation7);
        QWidget::setTabOrder(Equation7, pushButton_8);
        QWidget::setTabOrder(pushButton_8, Equation8);
        QWidget::setTabOrder(Equation8, Equation9);
        QWidget::setTabOrder(Equation9, Equation10);
        QWidget::setTabOrder(Equation10, pushButton_9);
        QWidget::setTabOrder(pushButton_9, pushButton_10);
        QWidget::setTabOrder(pushButton_10, checkBox_1);
        QWidget::setTabOrder(checkBox_1, checkBox_2);
        QWidget::setTabOrder(checkBox_2, checkBox_3);
        QWidget::setTabOrder(checkBox_3, checkBox_4);
        QWidget::setTabOrder(checkBox_4, checkBox_5);
        QWidget::setTabOrder(checkBox_5, checkBox_6);
        QWidget::setTabOrder(checkBox_6, checkBox_7);
        QWidget::setTabOrder(checkBox_7, checkBox_8);
        QWidget::setTabOrder(checkBox_8, checkBox_9);
        QWidget::setTabOrder(checkBox_9, checkBox_10);

        retranslateUi(Viewer);

        QMetaObject::connectSlotsByName(Viewer);
    } // setupUi

    void retranslateUi(QMainWindow *Viewer)
    {
        Viewer->setWindowTitle(QCoreApplication::translate("Viewer", "Viewer", nullptr));
        label->setText(QCoreApplication::translate("Viewer", "temp no use", nullptr));
        addEquationButton->setText(QCoreApplication::translate("Viewer", "Add", nullptr));
        pushButton->setText(QCoreApplication::translate("Viewer", "D", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Viewer", "D", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Viewer", "D", nullptr));
        pushButton_4->setText(QCoreApplication::translate("Viewer", "D", nullptr));
        pushButton_5->setText(QCoreApplication::translate("Viewer", "D", nullptr));
        pushButton_6->setText(QCoreApplication::translate("Viewer", "D", nullptr));
        pushButton_7->setText(QCoreApplication::translate("Viewer", "D", nullptr));
        pushButton_8->setText(QCoreApplication::translate("Viewer", "D", nullptr));
        pushButton_9->setText(QCoreApplication::translate("Viewer", "D", nullptr));
        pushButton_10->setText(QCoreApplication::translate("Viewer", "D", nullptr));
        checkBox_1->setText(QString());
        checkBox_2->setText(QString());
        checkBox_3->setText(QString());
        checkBox_4->setText(QString());
        checkBox_5->setText(QString());
        checkBox_6->setText(QString());
        checkBox_7->setText(QString());
        checkBox_8->setText(QString());
        checkBox_9->setText(QString());
        checkBox_10->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Viewer: public Ui_Viewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWER_H
