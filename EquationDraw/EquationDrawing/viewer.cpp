#include "viewer.h"
#include "ui_viewer.h"

//畫圖介面名稱 ui->customPlot
//算式排列的範圍Widget ui->equationWidget
//static
vector<QString> Viewer::equationInput(11);//最多10個([1]~[10],[0]no use)
vector<string> Viewer::validEquationOrNot(11);//存true或錯誤訊息

Viewer::Viewer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Viewer)
{
    ui->setupUi(this);
    lineLayout=new QVBoxLayout;
    test();
    //QToolButton *showButton=new QToolButton(ui->Equation1);
    //ui->checkBox_1->setCheckState(Qt::Checked);
    //qDebug() << "connect works: " <<connect(ui->checkBox_1, SIGNAL(stateChanged()), this, SLOT(testLine()));
    //showButton->setVisible(!ui->Equation1->text().isEmpty());


}

Viewer::~Viewer()
{
    delete ui;
}

void Viewer::test()
{
    QCustomPlot* customPlot  = ui->customPlot;
    QPen pen;//xy軸加粗用
    pen.setWidth(3);
    pen.setColor(Qt::black);
    customPlot->xAxis->grid()->setZeroLinePen(pen);
    customPlot->yAxis->grid()->setZeroLinePen(pen);
        // add two new graphs and set their look:
    for(int i=0;i<11;i++)
        customPlot->addGraph();//1~10,0 no use

    customPlot->xAxis2->setVisible(true);
    customPlot->xAxis2->setTickLabels(false);
    customPlot->yAxis2->setVisible(true);
    customPlot->yAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}


void Viewer::on_addEquationButton_clicked()
{

    //增加新的算式輸入格
    /* The "this" argument is needed to prevent memory leaks */

        QLineEdit* Field = new QLineEdit(ui->equationWidget);
        lineLayout->addStretch();
        lineLayout->addWidget(Field);
        //lineLayout->addWidget(Field);
        equationEditLine.push_back(Field);
        //Field->show();
       ui->equationWidget->setLayout(lineLayout);
       ui->equationWidget->update();
}


void Viewer::on_Equation1_editingFinished()
{
    equationInput[1]=ui->Equation1->text();
    QCustomPlot* customPlot  = ui->customPlot;
    customPlot->graph(1)->setPen(QPen(QColor(0,0,255)));
    Parser parser(1);
    parser.process();
    if(parser.needDraw == true)
    {
        customPlot->graph(1)->setData(parser.x, parser.y);
//        customPlot->graph(1)->rescaleAxes();
        customPlot->xAxis->setRange(-20,20);
        customPlot->yAxis->setRange(-20,20);
        customPlot->replot();
    }
    else
    {
        QVector<double>x, y;
        customPlot->graph(1)->setData(x, y);
        customPlot->xAxis->setRange(-20,20);
        customPlot->yAxis->setRange(-20,20);
        customPlot->replot();
    }
}


void Viewer::on_Equation2_editingFinished()
{
    equationInput[2]=ui->Equation2->text();
    QCustomPlot* customPlot  = ui->customPlot;
    customPlot->graph(2)->setPen(QPen(QColor(255,0,0)));
    Parser parser(2);
    parser.process();
    if(parser.needDraw == true)
    {
        customPlot->graph(2)->setData(parser.x, parser.y);
        customPlot->xAxis->setRange(-20,20);
        customPlot->yAxis->setRange(-20,20);
        customPlot->replot();
    }
    else
    {
        QVector<double>x, y;
        customPlot->graph(2)->setData(x, y);
        customPlot->xAxis->setRange(-20,20);
        customPlot->yAxis->setRange(-20,20);
        customPlot->replot();
    }
}

void Viewer::on_Equation3_editingFinished()
{
    equationInput[3]=ui->Equation3->text();
    QCustomPlot* customPlot  = ui->customPlot;
    customPlot->graph(3)->setPen(QColor(0,238,0));
    Parser parser(3);
    parser.process();
    if(parser.needDraw == true)
    {
        customPlot->graph(3)->setData(parser.x, parser.y);
        customPlot->xAxis->setRange(-20,20);
        customPlot->yAxis->setRange(-20,20);
        customPlot->replot();
    }
    else
    {
        QVector<double>x, y;
        customPlot->graph(3)->setData(x, y);
        customPlot->xAxis->setRange(-20,20);
        customPlot->yAxis->setRange(-20,20);
        customPlot->replot();
    }
}

void Viewer::on_Equation4_editingFinished()
{
    equationInput[4]=ui->Equation4->text();
    QCustomPlot* customPlot  = ui->customPlot;
    customPlot->graph(4)->setPen(QPen(QColor(105,105,105)));
    Parser parser(4);
    parser.process();
    if(parser.needDraw)
    {
        customPlot->graph(4)->setData(parser.x, parser.y);
        customPlot->xAxis->setRange(-20,20);
        customPlot->yAxis->setRange(-20,20);
        customPlot->replot();
    }
    else
    {
        QVector<double>x, y;
        customPlot->graph(4)->setData(x, y);
        customPlot->xAxis->setRange(-20,20);
        customPlot->yAxis->setRange(-20,20);
        customPlot->replot();
    }
}

void Viewer::on_Equation5_editingFinished()
{
    equationInput[5]=ui->Equation5->text();
    QCustomPlot* customPlot  = ui->customPlot;
    customPlot->graph(5)->setPen(QPen(QColor(174,120,255)));
    Parser parser(5);
    parser.process();
    if(parser.needDraw)
    {
        customPlot->graph(5)->setData(parser.x, parser.y);
        customPlot->xAxis->setRange(-20,20);
        customPlot->yAxis->setRange(-20,20);
        customPlot->replot();
    }
    else
    {
        QVector<double>x, y;
        customPlot->graph(5)->setData(x, y);
        customPlot->xAxis->setRange(-20,20);
        customPlot->yAxis->setRange(-20,20);
        customPlot->replot();
    }
}

void Viewer::on_Equation6_editingFinished()
{
    equationInput[6]=ui->Equation6->text();
    QCustomPlot* customPlot  = ui->customPlot;
    customPlot->graph(6)->setPen(QPen(QColor(255,165,79)));
    Parser parser(6);
    parser.process();
    if(parser.needDraw)
    {
        customPlot->graph(6)->setData(parser.x, parser.y);
        customPlot->xAxis->setRange(-20,20);
        customPlot->yAxis->setRange(-20,20);
        customPlot->replot();
    }
    else
    {
        QVector<double>x, y;
        customPlot->graph(6)->setData(x, y);
        customPlot->xAxis->setRange(-20,20);
        customPlot->yAxis->setRange(-20,20);
        customPlot->replot();
    }
}

void Viewer::on_Equation7_editingFinished()
{
    equationInput[7]=ui->Equation7->text();
    QCustomPlot* customPlot  = ui->customPlot;
    customPlot->graph(7)->setPen(QPen(QColor(151,219,242)));
    Parser parser(7);
    parser.process();
    if(parser.needDraw)
    {
        customPlot->graph(7)->setData(parser.x, parser.y);
        customPlot->xAxis->setRange(-20,20);
        customPlot->yAxis->setRange(-20,20);
        customPlot->replot();
    }
    else
    {
        QVector<double>x, y;
        customPlot->graph(7)->setData(x, y);
        customPlot->xAxis->setRange(-20,20);
        customPlot->yAxis->setRange(-20,20);
        customPlot->replot();
    }
}

void Viewer::on_Equation8_editingFinished()
{
    equationInput[8]=ui->Equation8->text();
    QCustomPlot* customPlot  = ui->customPlot;
    customPlot->graph(8)->setPen(QPen(QColor(255,193,193)));
    Parser parser(8);
    parser.process();
    if(parser.needDraw)
    {
        customPlot->graph(8)->setData(parser.x, parser.y);
        customPlot->xAxis->setRange(-20,20);
        customPlot->yAxis->setRange(-20,20);
        customPlot->replot();
    }
    else
    {
        QVector<double>x, y;
        customPlot->graph(8)->setData(x, y);
        customPlot->xAxis->setRange(-20,20);
        customPlot->yAxis->setRange(-20,20);
        customPlot->replot();
    }
}

void Viewer::on_Equation9_editingFinished()
{
    equationInput[9]=ui->Equation9->text();
    QCustomPlot* customPlot  = ui->customPlot;
    customPlot->graph(9)->setPen(QPen(QColor(46,139,87)));
    Parser parser(9);
    parser.process();
    if(parser.needDraw)
    {
        customPlot->graph(9)->setData(parser.x, parser.y);
        customPlot->xAxis->setRange(-20,20);
        customPlot->yAxis->setRange(-20,20);
        customPlot->replot();
    }
    else
    {
        QVector<double>x, y;
        customPlot->graph(9)->setData(x, y);
        customPlot->xAxis->setRange(-20,20);
        customPlot->yAxis->setRange(-20,20);
        customPlot->replot();
    }
}

void Viewer::on_Equation10_editingFinished()
{
    equationInput[10]=ui->Equation10->text();
    QCustomPlot* customPlot  = ui->customPlot;
    customPlot->graph(10)->setPen(QPen(QColor(0,0,128)));
    Parser parser(10);
    parser.process();
    if(parser.needDraw)
    {
        customPlot->graph(10)->setData(parser.x, parser.y);
        customPlot->xAxis->setRange(-20,20);
        customPlot->yAxis->setRange(-20,20);
        customPlot->replot();
    }
    else
    {
        QVector<double>x, y;
        customPlot->graph(10)->setData(x, y);
        customPlot->xAxis->setRange(-20,20);
        customPlot->yAxis->setRange(-20,20);
        customPlot->replot();
    }
}

void Viewer::on_checkBox_1_stateChanged(int arg1)
{
    if(ui->checkBox_1->isChecked())
        ui->customPlot->graph(1)->setVisible(true);
    else
        ui->customPlot->graph(1)->setVisible(false);
    ui->customPlot->replot();
}

void Viewer::on_checkBox_2_stateChanged(int arg1)
{
    if(ui->checkBox_2->isChecked())
        ui->customPlot->graph(2)->setVisible(true);
    else
        ui->customPlot->graph(2)->setVisible(false);
    ui->customPlot->replot();
}

void Viewer::on_checkBox_3_stateChanged(int arg1)
{
    if(ui->checkBox_3->isChecked())
        ui->customPlot->graph(3)->setVisible(true);
    else
        ui->customPlot->graph(3)->setVisible(false);
    ui->customPlot->replot();
}

void Viewer::on_checkBox_4_stateChanged(int arg1)
{
    if(ui->checkBox_4->isChecked())
        ui->customPlot->graph(4)->setVisible(true);
    else
        ui->customPlot->graph(4)->setVisible(false);
    ui->customPlot->replot();
}

void Viewer::on_checkBox_5_stateChanged(int arg1)
{
    if(ui->checkBox_5->isChecked())
        ui->customPlot->graph(5)->setVisible(true);
    else
        ui->customPlot->graph(5)->setVisible(false);
    ui->customPlot->replot();
}

void Viewer::on_checkBox_6_stateChanged(int arg1)
{
    if(ui->checkBox_6->isChecked())
        ui->customPlot->graph(6)->setVisible(true);
    else
        ui->customPlot->graph(6)->setVisible(false);
    ui->customPlot->replot();
}

void Viewer::on_checkBox_7_stateChanged(int arg1)
{
    if(ui->checkBox_7->isChecked())
        ui->customPlot->graph(7)->setVisible(true);
    else
        ui->customPlot->graph(7)->setVisible(false);
    ui->customPlot->replot();
}

void Viewer::on_checkBox_8_stateChanged(int arg1)
{
    if(ui->checkBox_8->isChecked())
        ui->customPlot->graph(8)->setVisible(true);
    else
        ui->customPlot->graph(8)->setVisible(false);
    ui->customPlot->replot();
}

void Viewer::on_checkBox_9_stateChanged(int arg1)
{
    if(ui->checkBox_9->isChecked())
        ui->customPlot->graph(9)->setVisible(true);
    else
        ui->customPlot->graph(9)->setVisible(false);
    ui->customPlot->replot();
}

void Viewer::on_checkBox_10_stateChanged(int arg1)
{
    if(ui->checkBox_10->isChecked())
        ui->customPlot->graph(10)->setVisible(true);
    else
        ui->customPlot->graph(10)->setVisible(false);
    ui->customPlot->replot();
}


void Viewer::on_pushButton_clicked()
{
    ui->Equation1->setText("");
    ui->checkBox_1->setChecked(false);
    equationInput[1]="";
    QCustomPlot* customPlot  = ui->customPlot;
    customPlot->graph(1)->setPen(QPen(QColor(0,0,255)));
    Parser parser(1);
  //  parser.process();
    customPlot->graph(1)->setData(parser.x, parser.y);
    customPlot->xAxis->setRange(-20,20);
    customPlot->yAxis->setRange(-20,20);
    customPlot->replot();
}


void Viewer::on_pushButton_2_clicked()
{
    ui->Equation2->setText("");
    ui->checkBox_2->setChecked(false);
    equationInput[2]=ui->Equation2->text();
    QCustomPlot* customPlot  = ui->customPlot;
    customPlot->graph(2)->setPen(QPen(QColor(255,0,0)));
    Parser parser(2);
   // parser.process();
    customPlot->graph(2)->setData(parser.x, parser.y);
    customPlot->xAxis->setRange(-20,20);
    customPlot->yAxis->setRange(-20,20);
    customPlot->replot();
}


void Viewer::on_pushButton_4_clicked()
{
    ui->Equation3->setText("");
    ui->checkBox_3->setChecked(false);
    equationInput[3]=ui->Equation3->text();
    QCustomPlot* customPlot  = ui->customPlot;
    customPlot->graph(3)->setPen(QColor(0,238,0));
    Parser parser(3);
  //  parser.process();
    customPlot->graph(3)->setData(parser.x, parser.y);
    customPlot->xAxis->setRange(-20,20);
    customPlot->yAxis->setRange(-20,20);
    customPlot->replot();
}


void Viewer::on_pushButton_3_clicked()
{
    ui->Equation4->setText("");
    ui->checkBox_4->setChecked(false);
    equationInput[4]=ui->Equation4->text();
    QCustomPlot* customPlot  = ui->customPlot;
    customPlot->graph(4)->setPen(QPen(QColor(105,105,105)));
    Parser parser(4);
 //   parser.process();
    customPlot->graph(4)->setData(parser.x, parser.y);
    customPlot->xAxis->setRange(-20,20);
    customPlot->yAxis->setRange(-20,20);
    customPlot->replot();
}


void Viewer::on_pushButton_10_clicked()
{
    ui->Equation5->setText("");
    ui->checkBox_5->setChecked(false);
    equationInput[5]=ui->Equation5->text();
    QCustomPlot* customPlot  = ui->customPlot;
    customPlot->graph(5)->setPen(QPen(QColor(174,120,255)));
    Parser parser(5);
   // parser.process();
    customPlot->graph(5)->setData(parser.x, parser.y);
    customPlot->xAxis->setRange(-20,20);
    customPlot->yAxis->setRange(-20,20);
    customPlot->replot();
}




void Viewer::on_pushButton_9_clicked()
{
    ui->Equation6->setText("");
    ui->checkBox_6->setChecked(false);
    equationInput[6]=ui->Equation6->text();
    QCustomPlot* customPlot  = ui->customPlot;
    customPlot->graph(6)->setPen(QPen(QColor(255,165,79)));
    Parser parser(6);
   // parser.process();
    customPlot->graph(6)->setData(parser.x, parser.y);
    customPlot->xAxis->setRange(-20,20);
    customPlot->yAxis->setRange(-20,20);
    customPlot->replot();
}


void Viewer::on_pushButton_8_clicked()
{
    ui->Equation7->setText("");
    ui->checkBox_7->setChecked(false);
    equationInput[7]=ui->Equation7->text();
    QCustomPlot* customPlot  = ui->customPlot;
    customPlot->graph(7)->setPen(QPen(QColor(151,219,242)));
    Parser parser(7);
  //  parser.process();
    customPlot->graph(7)->setData(parser.x, parser.y);
    customPlot->xAxis->setRange(-20,20);
    customPlot->yAxis->setRange(-20,20);
    customPlot->replot();
}


void Viewer::on_pushButton_7_clicked()
{
    ui->Equation8->setText("");
    ui->checkBox_8->setChecked(false);
    equationInput[8]=ui->Equation8->text();
    QCustomPlot* customPlot  = ui->customPlot;
    customPlot->graph(8)->setPen(QPen(QColor(255,193,193)));
    Parser parser(8);
   // parser.process();
    customPlot->graph(8)->setData(parser.x, parser.y);
    customPlot->xAxis->setRange(-20,20);
    customPlot->yAxis->setRange(-20,20);
    customPlot->replot();
}


void Viewer::on_pushButton_5_clicked()
{
    ui->Equation9->setText("");
    ui->checkBox_9->setChecked(false);
    equationInput[9]=ui->Equation9->text();
    QCustomPlot* customPlot  = ui->customPlot;
    customPlot->graph(9)->setPen(QPen(QColor(46,139,87)));
    Parser parser(9);
  //  parser.process();
    customPlot->graph(9)->setData(parser.x, parser.y);
    customPlot->xAxis->setRange(-20,20);
    customPlot->yAxis->setRange(-20,20);
    customPlot->replot();
}


void Viewer::on_pushButton_6_clicked()
{
    ui->Equation10->setText("");
    ui->checkBox_10->setChecked(false);
    equationInput[10]=ui->Equation10->text();
    QCustomPlot* customPlot  = ui->customPlot;
    Parser parser(10);
  //  parser.process();
    customPlot->graph(10)->setData(parser.x, parser.y);
    customPlot->xAxis->setRange(-20,20);
    customPlot->yAxis->setRange(-20,20);
    customPlot->replot();
}

