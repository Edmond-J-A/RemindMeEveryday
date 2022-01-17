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

vector<QLineEdit *> MenuTable::Show()
{
    vector<QLineEdit *> result;
    for(int i = 0;i < 11;i++)
    {
        QLineEdit *newedit=new QLineEdit;
        newedit->resize(360,40);
        newedit->move(20,i*30+25);
        if(i<this->table.size())
        {
            newedit->setText(QString::fromStdString(this->table[i].Getname()));
            result.push_back(newedit);
        }
        else
        {
            newedit->setText(QString(""));
            result.push_back(newedit);
        }
    }
    return result;
}

void MenuTable::Additem(Item newitem)
{

    newitem.SetID(this->nowID);
    this->table.push_back(newitem);
    this->nowID++;
    this->Sort();
}

void MenuTable::Doneitem(int itemID)
{

}

void MenuTable::Deleteitem(int itemID)
{
    for(int i = 0 ;i < this->table.size();i++)
    {
        if(itemID == (this->table[i]).GetID())
        {
            this->table.erase(this->table.begin()+i);
        }
    }
                                //此处ID重新排列

    this->nowID--;
}

void MenuTable::Edititem(int itemID)
{

}

int MenuTable::Finditem(string name)
{

}

void MenuTable::Savetofile(string filename)
{

}

void MenuTable::Loadbyfile(string filename)
{

}
