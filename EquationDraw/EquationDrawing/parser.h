#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <cmath>
#include <QObject>
#include <vector>
#include <string>
using namespace std;
class Parser
{
public:
    Parser();
    vector<string> equationPart;//拆解後的字串
    QVector<double> x,y;//存計算的座標點數值
    static vector<pair<string,vector<string>>> variableList;
        //static 儲存變數(變數,拆解後的字串)
        //一個textline對應一個變數,最多10個([1]~[10],[0]no use)
        //沒設定變數的話要把那一格變回空的""(不要erase,對應順序會亂
    void process();//暫定總處理函式

    //拆字串
    //檢查輸入合法
    //是不是設定變數
    //一個變數只能定義一次(避免循環定義)
    //有錯誤
    //變數有套用x以外的變數就先替換(ex: a=5+x; b=a+3>>b=5+x+3)
    //equation有y出現的時候再計算

    bool needDraw;//預設false,有y設true


};

#endif // PARSER_H
