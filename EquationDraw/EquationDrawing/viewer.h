#ifndef VIEWER_H
#define VIEWER_H
#include "qcustomplot.h"
#include <QMainWindow>
#include <vector>
#include <string>
#include <QGridLayout>
#include "parser.h"
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class Viewer; }
QT_END_NAMESPACE

class Viewer : public QMainWindow
{
    Q_OBJECT

public:
    Viewer(QWidget *parent = nullptr);
    ~Viewer();
    void test();
    vector<QLineEdit*> equationEditLine;
    QVBoxLayout* lineLayout;


    static vector<QString> equationInput;//最多10個([1]~[10],[0]no use)
    static vector<string> validEquationOrNot;//存true或錯誤訊息
private slots:

    void on_addEquationButton_clicked();

    void on_Equation1_editingFinished();

    void on_Equation2_editingFinished();

    void on_Equation3_editingFinished();

    void on_Equation4_editingFinished();

    void on_Equation5_editingFinished();

    void on_Equation6_editingFinished();

    void on_Equation7_editingFinished();

    void on_Equation8_editingFinished();

    void on_Equation9_editingFinished();

    void on_Equation10_editingFinished();

     void testLine(){QMessageBox Q;Q.setText("done");Q.exec();};
     void on_checkBox_1_stateChanged(int arg1);

     void on_checkBox_2_stateChanged(int arg1);

     void on_checkBox_3_stateChanged(int arg1);

     void on_checkBox_4_stateChanged(int arg1);

     void on_checkBox_5_stateChanged(int arg1);

     void on_checkBox_6_stateChanged(int arg1);

     void on_checkBox_7_stateChanged(int arg1);

     void on_checkBox_8_stateChanged(int arg1);

     void on_checkBox_9_stateChanged(int arg1);

     void on_checkBox_10_stateChanged(int arg1);

private:
    Ui::Viewer *ui;
};
#endif // VIEWER_H
