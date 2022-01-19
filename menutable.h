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
public:
    MenuTable(){}
    void Sort(int method=0);
    void Show(QWidget *parent);
    void Additem(Item newitem);
    void Doneitem(int itemID);
    void Deleteitem(int itemID,QWidget *parent);
    void Edititem(int itemID,QWidget *parent,string name="",string ID="",string time="");
    int Finditem(string name);
    void Loadbyfile(string filename);
    void Savetofile(string filename);
};


#endif // MENUTABLE_H
