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
        //qDebug() << "connect works: " << connect(Field,SIGNAL(editingFinished()),this ,SLOT(testLine()));
        /* Your perfectPanel class has some layout where the existing LineEdit rows
           are. I'm assuming m_Layout is a pointer to that layout here. */
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
    //進入算式處理
    //算式處理結果儲存
    //有y就讓viewer畫圖
    Parser parser(1);
    parser.process();

    QCustomPlot* customPlot  = ui->customPlot;
        // add two new graphs and set their look:
        customPlot->graph(1)->setPen(QPen(Qt::green)); // line color blue for first graph
        // generate some points of data (y0 for first, y1 for second graph):
        QVector<double> x(451), y0(451);
        for (int i=0; i<251; ++i)
        {
          x[i] = i;
          y0[i] = qExp(-i/150.0)*qCos(i/10.0); // exponentially decaying cosine

        }
        for (int i=251; i<451; ++i)
        {
          x[i] = -(i-251);
          y0[i] = qExp((i-251)/150.0)*qCos(-(i-251)/10.0); // exponentially decaying cosine

        }
        // pass data points to graphs:
        customPlot->graph(1)->setData(x, y0);
        // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
        //customPlot->graph(1)->rescaleAxes();
        customPlot->xAxis->setRange(0,100);
        customPlot->yAxis->setRange(0,1);
    customPlot->replot();
}


void Viewer::on_Equation2_editingFinished()
{
    equationInput[2]=ui->Equation1->text();
    //進入算式處理
    //算式處理結果儲存
    //有y就讓viewer畫圖
    Parser parser(2);
    parser.process();

    QCustomPlot* customPlot  = ui->customPlot;

        // add two new graphs and set their look:
        customPlot->graph(2)->setPen(QPen(Qt::red)); // line color red for second graph
        // generate some points of data (y0 for first, y1 for second graph):
        QVector<double> x(251), y1(251);
        for (int i=0; i<251; ++i)
        {
          x[i] = i;
          y1[i] = qExp(-i/150.0);              // exponential envelope
        }

        customPlot->graph(2)->setData(x, y1);
        // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
        //customPlot->graph(2)->rescaleAxes(true);
        customPlot->xAxis->setRange(0,50);
        customPlot->yAxis->setRange(0,1);
        customPlot->replot();
}

void Viewer::on_Equation3_editingFinished()
{
    equationInput[3]=ui->Equation1->text();
    QCustomPlot* customPlot  = ui->customPlot;

    Parser parser(3);
    parser.process();
    if(parser.needDraw)
    {
        customPlot->graph(3)->setData(parser.x, parser.y);
        customPlot->graph(3)->rescaleAxes();
        customPlot->replot();
    }
}

void Viewer::on_Equation4_editingFinished()
{
    equationInput[4]=ui->Equation1->text();
    QCustomPlot* customPlot  = ui->customPlot;

    Parser parser(4);
    parser.process();
    if(parser.needDraw)
    {
        customPlot->graph(3)->setData(parser.x, parser.y);
        customPlot->graph(3)->rescaleAxes();
        customPlot->replot();
    }
}

void Viewer::on_Equation5_editingFinished()
{
    equationInput[5]=ui->Equation1->text();
    QCustomPlot* customPlot  = ui->customPlot;

    Parser parser(5);
    parser.process();
    if(parser.needDraw)
    {
        customPlot->graph(3)->setData(parser.x, parser.y);
        customPlot->graph(3)->rescaleAxes();
        customPlot->replot();
    }
}

void Viewer::on_Equation6_editingFinished()
{
    equationInput[6]=ui->Equation1->text();
    QCustomPlot* customPlot  = ui->customPlot;

    Parser parser(6);
    parser.process();
    if(parser.needDraw)
    {
        customPlot->graph(3)->setData(parser.x, parser.y);
        customPlot->graph(3)->rescaleAxes();
        customPlot->replot();
    }
}

void Viewer::on_Equation7_editingFinished()
{
    equationInput[7]=ui->Equation1->text();
    QCustomPlot* customPlot  = ui->customPlot;

    Parser parser(7);
    parser.process();
    if(parser.needDraw)
    {
        customPlot->graph(3)->setData(parser.x, parser.y);
        customPlot->graph(3)->rescaleAxes();
        customPlot->replot();
    }
}

void Viewer::on_Equation8_editingFinished()
{
    equationInput[8]=ui->Equation1->text();
    QCustomPlot* customPlot  = ui->customPlot;

    Parser parser(8);
    parser.process();
    if(parser.needDraw)
    {
        customPlot->graph(3)->setData(parser.x, parser.y);
        customPlot->graph(3)->rescaleAxes();
        customPlot->replot();
    }
}

void Viewer::on_Equation9_editingFinished()
{
    equationInput[9]=ui->Equation1->text();
    QCustomPlot* customPlot  = ui->customPlot;

    Parser parser(9);
    parser.process();
    if(parser.needDraw)
    {
        customPlot->graph(3)->setData(parser.x, parser.y);
        customPlot->graph(3)->rescaleAxes();
        customPlot->replot();
    }
}

void Viewer::on_Equation10_editingFinished()
{
    equationInput[10]=ui->Equation1->text();
    QCustomPlot* customPlot  = ui->customPlot;

    Parser parser(10);
    parser.process();
    if(parser.needDraw)
    {
        customPlot->graph(3)->setData(parser.x, parser.y);
        customPlot->graph(3)->rescaleAxes();
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

