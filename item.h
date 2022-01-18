#ifndef ITEM_H
#define ITEM_H
#include<iostream>
#include<vector>
using namespace std;
class Item
{
private:
    string name;
    int priority;
    string timeRange;
    bool checkable;
    bool isvisible;
    int ID;
    bool done=0;
    bool repeat[7]={0};
public:
    Item();
    Item(string name,int priority,string timeRange,bool checkable);
    void Setvisible(bool visible);
    void Edit(string name,int priority,string timeRange,bool checkable);
    int GetID();
    void SetID(int ID);
    string Getname();
    ~Item();
    vector<int> Stringtimetoint();
};
#endif // ITEM_H
