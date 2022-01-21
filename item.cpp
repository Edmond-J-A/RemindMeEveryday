#include"item.h"

Item::Item()
{

}

Item::Item(string name,int priority,string timeRange,QWidget *parent,bool checkable)
{
    this->name=name;
    this->priority=priority;
    this->timeRange=timeRange;
    this->checkable=checkable;
    cbox=new QCheckBox(parent);
    ledit=new QLineEdit(parent);
    ledit->setText(QString::fromStdString(name));
    ledit->resize(360,40);
    ledit->setObjectName(QString::number(this->ID));
    cbox->setObjectName(QString::number(this->ID));
    QObject::connect(ledit,SIGNAL(editingFinished()),parent,SLOT(editfinished()));
    QObject::connect(cbox,SIGNAL(clicked()),parent,SLOT(checked()));
    ledit->setStyleSheet(

                "QLineEdit{"
                    "border-style:outset;"
                    "border-width:4px;"
                    "border-radius:10px;"
                    "border-color:rgba(255,255,255,0); "
                    "padding:1px;"
                    "background:transparent;"
                    "font: 18pt \"黑体\";"
                "}"

                "QLineEdit:pressed{"

                    "border-color:rgba(255,255,255,0);"
                    "border-style:inset;"
                    "background:transparent;"
                    "font: 18pt \"黑体\";"
                "}"
                //鼠标悬停样式
                "QLineEdit:hover"
                "{"
                    "border-color:rgba(255,255,255,0);"
                    "background:transparent;"
                    "font: 18pt \"黑体\";"
                "}"
                );

    ledit->setVisible(0);
    cbox->setVisible(0);
    cbox->setStyleSheet(
                "QCheckBox{"
                    "border: none;/*最外层边框*/"
                "}"
                "QCheckBox::indicator{/*选择框尺寸*/"
                    "background-color: rgba(255, 255, 255, 0);"
                    "border: 0px solid #b1b1b1;"
                    "width: 30px;"
                    "height: 30px;"
                "}"
                "QCheckBox:enabled:checked{"
                    "color: rgb(255, 255, 255);"
                "}"
                "QCheckBox:enabled:!checked{"
                    "color: rgb(255, 255, 255);"
                "}"
                "QCheckBox:enabled:hover{"
                    "color: rgb(0, 200, 0);"
                "}"
                "QCheckBox:!enabled{"
                    "color: rgb(80, 80, 80);"
                "}"

                "QCheckBox::indicator:unchecked {"
                        "image: url(:/new/prefix1/resource/checkbox-blank-circle-outline .png);"
                "}"
                "QCheckBox::indicator:unchecked:hover {"
                        "image: url(:/new/prefix1/resource/checkbox-blank-circle-outline .png);"
                "}"
                "QCheckBox::indicator:unchecked:pressed {"
                        "image: url(:/new/prefix1/resource/checkbox-blank-circle-outline .png);"
                "}"
                "QCheckBox::indicator:checked {"
                        "image: url(:/new/prefix1/resource/checkbox-marked-circle-outline.png);"
                "}"
                "QCheckBox::indicator:checked:hover {"
                        "image: url(:/new/prefix1/resource/checkbox-marked-circle-outline.png);"
                "}"
                "QCheckBox::indicator:checked:pressed {"
                        "image: url(:/new/prefix1/resource/checkbox-marked-circle-outline.png);"
                "} "
                );
    cbox->resize(31,31);
}

Item::Item(string name,int priority,string timeRange,QWidget *parent,int ID,bool checkable)
{
    this->name=name;
    this->priority=priority;
    this->timeRange=timeRange;
    this->checkable=checkable;
    cbox=new QCheckBox(parent);
    ledit=new QLineEdit(parent);
    ledit->setText(QString::fromStdString(name));
    ledit->resize(360,40);
    this->ID=ID;
    ledit->setObjectName(QString::number(this->ID));
    cbox->setObjectName(QString::number(this->ID));
    QObject::connect(ledit,SIGNAL(editingFinished()),parent,SLOT(editfinished()));
    QObject::connect(cbox,SIGNAL(clicked()),parent,SLOT(checked()));
    ledit->setStyleSheet(

                "QLineEdit{"
                    "border-style:outset;"
                    "border-width:4px;"
                    "border-radius:10px;"
                    "border-color:rgba(255,255,255,0); "
                    "padding:1px;"
                    "background:transparent;"
                    "font: 18pt \"黑体\";"
                "}"

                "QLineEdit:pressed{"

                    "border-color:rgba(255,255,255,0);"
                    "border-style:inset;"
                    "background:transparent;"
                    "font: 18pt \"黑体\";"
                "}"
                //鼠标悬停样式
                "QLineEdit:hover"
                "{"
                    "border-color:rgba(255,255,255,0);"
                    "background:transparent;"
                    "font: 18pt \"黑体\";"
                "}"
                );

    ledit->setVisible(0);
    cbox->setVisible(0);
    cbox->setStyleSheet(
                "QCheckBox{"
                    "border: none;/*最外层边框*/"
                "}"
                "QCheckBox::indicator{/*选择框尺寸*/"
                    "background-color: rgba(255, 255, 255, 0);"
                    "border: 0px solid #b1b1b1;"
                    "width: 30px;"
                    "height: 30px;"
                "}"
                "QCheckBox:enabled:checked{"
                    "color: rgb(255, 255, 255);"
                "}"
                "QCheckBox:enabled:!checked{"
                    "color: rgb(255, 255, 255);"
                "}"
                "QCheckBox:enabled:hover{"
                    "color: rgb(0, 200, 0);"
                "}"
                "QCheckBox:!enabled{"
                    "color: rgb(80, 80, 80);"
                "}"

                "QCheckBox::indicator:unchecked {"
                        "image: url(:/new/prefix1/resource/checkbox-blank-circle-outline .png);"
                "}"
                "QCheckBox::indicator:unchecked:hover {"
                        "image: url(:/new/prefix1/resource/checkbox-blank-circle-outline .png);"
                "}"
                "QCheckBox::indicator:unchecked:pressed {"
                        "image: url(:/new/prefix1/resource/checkbox-blank-circle-outline .png);"
                "}"
                "QCheckBox::indicator:checked {"
                        "image: url(:/new/prefix1/resource/checkbox-marked-circle-outline.png);"
                "}"
                "QCheckBox::indicator:checked:hover {"
                        "image: url(:/new/prefix1/resource/checkbox-marked-circle-outline.png);"
                "}"
                "QCheckBox::indicator:checked:pressed {"
                        "image: url(:/new/prefix1/resource/checkbox-marked-circle-outline.png);"
                "} "
                );
    cbox->resize(31,31);

}

void Item::Setvisible(bool visible)
{
    this->isvisible=visible;
    this->ledit->setVisible(visible);
    this->cbox->setVisible(visible);
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
    ledit->setObjectName(QString::number(this->ID));
    cbox->setObjectName(QString::number(this->ID));
}

string Item::Getname()
{
    return  this->name;
}

void Item::Setname(string newname)
{
    this->name=newname;
    this->ledit->setText(QString::fromStdString(newname));
}

vector<int> Item::Stringtimetoint()
{

}

QCheckBox* Item::Getcbox()
{
    return cbox;
}

QLineEdit* Item::Getledit()
{
    return ledit;
}

void Item::Settime(string time)
{
    this->timeRange=time;
}
