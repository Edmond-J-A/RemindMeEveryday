#include"menutable.h"
#include<QCoreApplication>

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
        if(i<int(this->table.size()))
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
    qDebug()<<this->table.size();
    qDebug()<<this->donetable.size();
}

//add an item
void MenuTable::Additem(Item newitem)
{

    newitem.SetID(this->nowID);
    this->table.push_back(newitem);
    this->nowID++;
    this->Sort();
}

void MenuTable::AdditemwithoutID(Item newitem)
{
    this->table.push_back(newitem);
    this->Sort();
}

void MenuTable::Additemtodone(Item newitem)
{
    this->donetable.push_back(newitem);
    this->Sort();
}

//be called when an item is finished
void MenuTable::Doneitem(int itemID,QWidget *parent)
{
    for(int i=0;i<int(this->table.size());i++)
    {
        if(itemID==this->table[i].GetID()&&this->table[i].Getname()!="")
        {
            Item temp(this->table[i]);
            this->table[i].Setvisible(0);
            this->table.erase(this->table.begin()+i);
            this->donetable.push_back(temp);
        }
    }
    this->Show(parent);
}

//delete an item
void MenuTable::Deleteitem(int itemID,QWidget *parent)
{
    for(int i = 0 ;i < int(this->table.size());i++)
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
    for(int i = 0 ;i < int(this->table.size());i++)
    {
        if(itemID == (this->donetable[i]).GetID())
        {
            this->donetable.erase(this->donetable.begin()+i);
        }
        else if(itemID < (this->table[i]).GetID())
        {
            this->donetable[i].SetID(this->donetable[i].GetID()-1);
        }
    }
    this->Show(parent);
    this->nowID--;
}

//Edit a exist item
void MenuTable::Edititem(int itemID,QWidget *parent,string name,string time)
{
    for(int i=0;i<int(this->table.size());i++)
    {
        if(itemID==this->table[i].GetID())
        {
            if(name.size()!=0)
            {
                this->table[i].Setname(name);
            }
            if(time.size()!=0)
            {
                this->table[i].Settime(time);
            }
        }

    }
    Show(parent);
}

//Find a exist item by return its ID
int MenuTable::Finditem(string name)
{
    for(int i=0;i<int(this->table.size());i++)
    {
        if(table[i].Getname()==name)
        {
            return table[i].GetID();
        }
    }
    return -1;
}


//save the items to txt when closed
void MenuTable::Savetofile()
{
    ofstream txt(":/new/prefix1/save/savetable.txt");
    if(txt.is_open())
    {
        for(int i=0;i<int(table.size());i++)
        {
            txt<<table[i].GetID()<<","<<table[i].Getname()<<","<<table[i].Getpriority()<<","<<table[i].Gettime()<<","<<table[i].Getcheckable()<<"\r\n";
        }
    }
    txt.close();
    ofstream txt1(":/new/prefix1/save/savedonetable.txt");
    if(txt1.is_open())
    {
        for(int i=0;i<int(donetable.size());i++)
        {
            txt1<<donetable[i].GetID()<<","<<donetable[i].Getname()<<","<<donetable[i].Getpriority()<<","<<donetable[i].Gettime()<<","<<donetable[i].Getcheckable()<<"\r\n";
        }
    }
    txt1.close();
}

//read items from txt when started
void MenuTable::Loadbyfile(QWidget *parent)
{
    int getidmax=0;
    QFile file(":/new/prefix1/save/savetable.txt");
    if (!file.open(QIODevice::ReadOnly ))
    {

    }
    else
    {
        while (!file.atEnd())
        {
            QByteArray line = file.readLine();
            QString str(line);
            QStringList sections = str.split(QRegExp("[,]"));
            if(sections.size()==5)
            {
                if(getidmax<sections[0].toInt())
                {
                    getidmax=sections[0].toInt();
                }
                Item temp(sections[1].toStdString(),sections[2].toInt(),sections[3].toStdString(),parent,sections[0].toInt(),sections[4].toInt());
                qDebug()<<temp.GetID()<<QString::fromStdString(temp.Getname());
                this->AdditemwithoutID(temp);
            }
        }
    }
    QFile file1(":/new/prefix1/save/savedonetable.txt");
    if (!file1.open(QIODevice::ReadOnly ))
    {

    }
    else
    {
        while (!file1.atEnd())
        {
            QByteArray line = file1.readLine();
            QString str(line);
            QStringList sections = str.split(QRegExp("[,]"));
            if(sections.size()==5)
            {
                if(getidmax<sections[0].toInt())
                {
                    getidmax=sections[0].toInt();
                }
                Item temp(sections[1].toStdString(),sections[2].toInt(),sections[3].toStdString(),parent,sections[0].toInt(),sections[4].toInt());
                this->Additemtodone(temp);
            }
        }
    }
    this->nowID=getidmax+1;
    qDebug()<<nowID;
}
