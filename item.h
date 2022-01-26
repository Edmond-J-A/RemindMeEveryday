#ifndef ITEM_H
#define ITEM_H
#include<iostream>
#include<vector>
#include<QWidget>
#include<QLineEdit>
#include<QCheckBox>
#include<QObject>
#include<QDebug>
#include<fstream>
#include<QFile>
#include <sstream>
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
    bool repeat[7]={0};
    QCheckBox *cbox;
    QLineEdit *ledit;
public:
    Item();

    Item(string name,int priority,string timeRange,QWidget *parent,bool checkable=1,bool* repeatmap=NULL);
    Item(string name,int priority,string timeRange,QWidget *parent,int ID,bool checkable=1,bool* repeatmap=NULL);
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
    bool Getrepeat(int index)
    {
        if(index>=0&&index<7)
        {
            return repeat[index];
        }
        else
        {
            return 0;
        }
    }
    bool Getcheckable()
    {
        return this->checkable;
    }
    string Gettime()
    {
        return this->timeRange;
    }
    int Getpriority()
    {
        return this->priority;
    }
    void Setpriority(int prio)
    {
        priority=prio;
    }

    int Setrepeat(int index,bool state)
    {
        if(index<7&&index>=0)
        {
            repeat[index]=state;
        }
    }
};
#endif // ITEM_H
