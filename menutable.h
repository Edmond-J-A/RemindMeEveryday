#ifndef MENUTABLE_H
#define MENUTABLE_H
#include"item.h"
#include<vector>
#include<qlineedit.h>
#include <regex>
#include<QDateTime>
using namespace std;
class MenuTable
{
private:
    vector<Item> table,donetable;
    int nowID=0;
    int page=0;
    int current_week=-1;

public:
    MenuTable(){
        QDateTime current_date_time = QDateTime::currentDateTime();
        if(current_date_time.toString("ddd")=="周一")
        {
            current_week=0;
        }
        else if(current_date_time.toString("ddd")=="周二")
        {
            current_week=1;
        }
        else if(current_date_time.toString("ddd")=="周三")
        {
            current_week=2;
        }
        else if(current_date_time.toString("ddd")=="周四")
        {
            current_week=3;
        }
        else if(current_date_time.toString("ddd")=="周五")
        {
            current_week=4;
        }
        else if(current_date_time.toString("ddd")=="周六")
        {
            current_week=5;
        }
        else if(current_date_time.toString("ddd")=="周日")
        {
            current_week=6;
        }
    }
    void Sort(int method=0);
    void Show(QWidget *parent);
    void Additem(Item newitem);
    void Doneitem(int itemID,QWidget *parent);
    void Deleteitem(int itemID,QWidget *parent);
    void Edititem(int itemID,QWidget *parent,string name="",string time="");
    int Finditem(string name);
    void Loadbyfile(QWidget *parent);
    void AdditemwithoutID(Item newitem);
    void Additemtodone(Item newitem);
    void Savetofile();
    void addpage(QWidget *parent);
    void subpage(QWidget *parent);
    void ShowAdditem(Item newitem);
};


#endif // MENUTABLE_H
