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
    int i=0;
    for(int j = 0;j < table.size();j++)
    {
        if(j>=this->page*11&&j<this->page*11+11)
        {
            this->table[j].Setvisible(1);
            this->table[j].Getledit()->move(30,i*30+25);
            this->table[j].Getcbox()->move(5,i*30+30);
            i++;
        }
        else
        {
            this->table[j].Setvisible(0);
        }
    }
    while (i<11) {
        Item temp("",0,"00:00-0:00",parent);
        temp.Setvisible(1);
        temp.Getledit()->move(30,i*30+25);
        temp.Getcbox()->move(5,i*30+30);
        this->ShowAdditem(temp);
        i++;
    }
}

void MenuTable::ShowAdditem(Item newitem)
{
    newitem.SetID(this->nowID);
    this->table.push_back(newitem);
    this->nowID++;
    this->Sort();
}

//add an item
void MenuTable::Additem(Item newitem)
{
    for(int i=0;i<int(this->table.size());i++)
    {
        if(this->table[i].Getname()=="")
        {
            for(int j=0;j<7;j++)
            {
                this->table[i].Setrepeat(j,newitem.Getrepeat(j));
                qDebug()<<newitem.Getrepeat(j);
            }
            this->table[i].Setpriority(newitem.Getpriority());
            this->table[i].Setname(newitem.Getname());
            this->table[i].Getledit()->setText(QString::fromStdString(newitem.Getname()));
            this->table[i].Settime(newitem.Gettime());
            qDebug()<<"test1";
            this->Sort();
            return;
        }
    }
    newitem.SetID(this->nowID);
    this->table.push_back(newitem);
    this->nowID++;
    this->Sort();

}

//for load function to load items which already have ID
void MenuTable::AdditemwithoutID(Item newitem)
{
    this->table.push_back(newitem);
    this->Sort();
}

//load done items to donetable
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
            temp.SetDone(1);
            this->donetable.push_back(temp);
            break;
        }
        else if(itemID==this->table[i].GetID()&&this->table[i].Getname()=="")
        {
            this->table[i].Getcbox()->setChecked(0);
            break;
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
    QString wrt="";
    string path=getenv("USERPROFILE");
    path+=+"\\AppData\\Local\\RME\\savetable.item";
    QFile file(QString::fromStdString(path));
    file.resize(0);
    if(file.open( QIODevice::ReadWrite| QIODevice::Text))
    {
        for(int i=0;i<int(table.size());i++)
        {
            if(table[i].Getname().size()==0)
            {
                continue;
            }
            wrt+=QString::number(table[i].GetID())+","+QString::fromStdString(table[i].Getname())+","+QString::number(table[i].Getpriority())+","+QString::fromStdString(table[i].Gettime())+","+QString::number(table[i].Getcheckable());
            for(int j=0;j<7;j++)
            {
                wrt+=","+QString::number(table[i].Getrepeat(j));
            }
            wrt+=","+QString::number(table[i].GetDone())+"\n";
            file.write(wrt.toUtf8());
            wrt.clear();
        }
        wrt.clear();
        for(int i=0;i<int(donetable.size());i++)
        {
            if(donetable[i].Getname().size()==0)
            {
                continue;
            }
            wrt+=QString::number(donetable[i].GetID())+","+QString::fromStdString(donetable[i].Getname())+","+QString::number(donetable[i].Getpriority())+","+QString::fromStdString(donetable[i].Gettime())+","+QString::number(donetable[i].Getcheckable());
            for(int j=0;j<7;j++)
            {
                wrt+=","+QString::number(donetable[i].Getrepeat(j));
            }
            wrt+=","+QString::number(donetable[i].GetDone())+"\n";
            file.write(wrt.toUtf8());
            wrt.clear();
        }
    }

}

//read items from txt when started
void MenuTable::Loadbyfile(QWidget *parent)
{
    int getidmax=0;
    string path=getenv("USERPROFILE");
    path+="\\AppData\\Local\\RME\\savetable.item";
    QFile file(QString::fromStdString(path));
    if (!file.open(QIODevice::ReadOnly))
    {
    }
    else
    {
        while (!file.atEnd())
        {
            QByteArray line = file.readLine();
            QString str(line);
            QStringList sections = str.split(QRegExp("[,]"));
            if(sections.size()>=5)
            {
                if(getidmax<sections[0].toInt())
                {
                    getidmax=sections[0].toInt();
                }
                bool temprepeat[7]={0};
                if(sections.size()==13)
                {
                    for(int i=0;i<7;i++)
                    {
                        temprepeat[i]=sections[5+i].toInt();
                    }
                }
                Item temp(sections[1].toStdString(),sections[2].toInt(),sections[3].toStdString(),parent,sections[0].toInt(),sections[4].toInt(),temprepeat);
                if(sections[12].toInt()==1)
                {
                    temp.SetDone(1);
                    this->Additemtodone(temp);
                }
                else
                {
                    temp.SetDone(0);
                    this->AdditemwithoutID(temp);

                }
            }
        }
    }
    this->nowID=getidmax+1;
}

//show next page
void MenuTable::addpage(QWidget *parent)
{
    if((this->page+1)*11<this->table.size())
    {
        this->page++;
    }
    this->Show(parent);
}

//show last page
void MenuTable::subpage(QWidget *parent)
{
    if(this->page>0)
    {
        this->page--;
    }
    this->Show(parent);
}
