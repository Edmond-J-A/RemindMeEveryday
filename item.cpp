#include"item.h"

Item::Item()
{

}

Item::Item(string name,int priority,string timeRange,bool checkable)
{
    this->name=name;
    this->priority=priority;
    this->timeRange=timeRange;
    this->checkable=checkable;
}

void Item::Setvisible(bool visible)
{
    this->isvisible=visible;
}

void Item::Edit(string name,int priority,string timeRange,bool checkable)
{
    this->name=name;
    this->priority=priority;
    this->timeRange=timeRange;
    this->checkable=checkable;
}

Item::~Item()
{

}

int Item::GetID()
{
    return  this->ID;
}

void Item::SetID(int ID)
{
      this->ID=ID;
}

string Item::Getname()
{
    return  this->name;
}

vector<int> Item::Stringtimetoint()
{

}
