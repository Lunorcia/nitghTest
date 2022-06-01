#ifndef VIEWER_H
#define VIEWER_H
#include "qcustomplot.h"
#include <QMainWindow>
#include <vector>
#include <string>
#include <QGridLayout>
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
    void testLine(){QMessageBox Q;Q.setText("done");Q.exec();};

private slots:

    void on_addEquationButton_clicked();

    void on_Equation1_editingFinished();

private:
    Ui::Viewer *ui;
};
#endif // VIEWER_H
