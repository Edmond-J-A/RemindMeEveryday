#ifndef MENUTABLE_H
#define MENUTABLE_H
#include"item.h"
#include<vector>
#include<qlineedit.h>
#include <regex>
using namespace std;
class MenuTable
{
private:
    vector<Item> table,donetable;
    int nowID=0;
    int page=0;
public:
    MenuTable(){}
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
};


#endif // MENUTABLE_H
