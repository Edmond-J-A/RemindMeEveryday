#ifndef ITEM_H
#define ITEM_H
#include<iostream>
#include<vector>
#include<QWidget>
#include<QLineEdit>
#include<QCheckBox>
#include<QObject>
#include<QDebug>
using namespace std;
class Item
{
private:
    string name;
    int priority;
    string timeRange;
    bool checkable=1;
    bool isvisible=0;
    int ID;
    bool done=0;
    bool repeat[7]={0};
    QCheckBox *cbox;
    QLineEdit *ledit;
public:
    Item();

    Item(string name,int priority,string timeRange,QWidget *parent,bool checkable=1);
    void Setvisible(bool visible);
    void Edit(string name,int priority,string timeRange,bool checkable);
    int GetID();
    void SetID(int ID);
    string Getname();
    ~Item();
    vector<int> Stringtimetoint();
    QCheckBox* Getcbox();
    QLineEdit* Getledit();
    void Settime(string time);
    void Setname(string newname);

};
#endif // ITEM_H
