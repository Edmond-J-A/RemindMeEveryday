#include"menutable.h"


//method will make sort uses different way to sort items
void MenuTable::Sort(int method)
{
    switch (method) {
    case 1:                 //sort by ID

        break;
    case 2:                 //sort by priority

        break;
    case 3:                 //sort by name

        break;
    default:                //sort by timerange

        break;
    }
}

//return the top 11 items' iterater to show in UI
void MenuTable::Show(QWidget *parent)
{
    for(int i = 0;i < 11;i++)
    {
        if(i<this->table.size())
        {
            this->table[i].Setvisible(1);
            this->table[i].Getledit()->move(30,i*30+25);
            this->table[i].Getcbox()->move(5,i*30+30);
        }
        else
        {
            Item temp("",0,"00:00-0:00",parent);
            temp.Setvisible(1);
            temp.Getledit()->move(30,i*30+25);
            temp.Getcbox()->move(5,i*30+30);
            this->Additem(temp);
        }

    }
}

//add an item
void MenuTable::Additem(Item newitem)
{

    newitem.SetID(this->nowID);
    this->table.push_back(newitem);
    this->nowID++;
    this->Sort();
}

//be called when an item is finished
void MenuTable::Doneitem(int itemID)
{

}

//delete an item
void MenuTable::Deleteitem(int itemID,QWidget *parent)
{
    for(int i = 0 ;i < this->table.size();i++)
    {
        if(itemID == (this->table[i]).GetID())
        {
            this->table.erase(this->table.begin()+i);
        }
        else if(itemID < (this->table[i]).GetID())
        {
            this->table[i].SetID(this->table[i].GetID()-1);
        }
    }
    this->Show(parent);
    this->nowID--;
}

//Edit a exist item
void MenuTable::Edititem(int itemID,QWidget *parent,string name,string ID,string time)
{
    if(name.size()!=0)
    {
        this->table[itemID].Setname(name);
    }
    if(ID.size()!=0)
    {
        this->table[itemID].SetID(QString::fromStdString(ID).toInt());
    }
    if(time.size()!=0)
    {
        this->table[itemID].Settime(time);
    }
    Show(parent);
}

//Find a exist item by return its ID
int MenuTable::Finditem(string name)
{
    for(int i=0;i<table.size();i++)
    {
        if(table[i].Getname()==name)
        {
            return table[i].GetID();
        }
    }
    return -1;
}


//save the items to txt when closed
void MenuTable::Savetofile(string filename)
{

}

//read items from txt when started
void MenuTable::Loadbyfile(string filename)
{

}
