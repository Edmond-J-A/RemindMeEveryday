#ifndef MENUTABLE_H
#define MENUTABLE_H
#include"item.h"
#include<vector>
#include<qlineedit.h>
using namespace std;
class MenuTable
{
private:
    vector<Item> table;
    int nowID=0;
public:
    MenuTable(){}
    void Sort(int method=0);
    vector<QLineEdit *> Show();
    void Additem(Item newitem);
    void Doneitem(int itemID);
    void Deleteitem(int itemID);
    void Edititem(int itemID);
    int Finditem(string name);
    void Loadbyfile(string filename);
    void Savetofile(string filename);
};


#endif // MENUTABLE_H
