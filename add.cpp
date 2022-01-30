#include "add.h"
#include "ui_add.h"

Add::Add(QColor bar,QColor back,QWidget *parent) :
    QWidget(parent,Qt::FramelessWindowHint),
    ui(new Ui::Add)
{
    ui->setupUi(this);
    this->move(x()+600, y()+500);
    backgroundcolor=back;
    barcolor=bar;
    QString ccolortxt="background-color:rgb("+QString::number(bar.red())+"," +QString::number(bar.green())+"," +QString::number(bar.blue())+") ;";
    ui->label->setStyleSheet(
                ccolortxt
                );
    ccolortxt="background-color:rgb("+QString::number(barcolor.red())+"," +QString::number(barcolor.green())+"," +QString::number(barcolor.blue())+") ;";
    QString hovercolortxt="background-color:rgb("+QString::number(backgroundcolor.red())+"," +QString::number(backgroundcolor.green())+"," +QString::number(backgroundcolor.blue())+") ;";
    ui->pushButton->setStyleSheet(
                "QPushButton{"
                    +ccolortxt+
                    "border-style:outset;"
                    "border-width:4px;"
                    "border-radius:20px;"
                    "border-color:rgba(0,0,0);"
                    "color:rgba(0,0,0,100);"
                    "padding:1px;"
                    "font:1000 15pt \"黑体\";"
                "}"
                    "QPushButton:pressed{"
                        +hovercolortxt+
                        "border-style:outset;"
                        "border-width:4px;"
                        "border-radius:20px;"
                        "border-color:rgba(0,0,0);"
                        +hovercolortxt+
                        "padding:1px;"
                        "font:1000 15pt \"黑体\";"
                    "}"
                );
}

Add::~Add()
{
    delete ui;
}

void Add::on_closeButton_clicked()
{
    close();
}

//make the window dragable
void Add::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton) //LeftButton clicked
    {
         dragPosition = event->globalPos() - frameGeometry().topLeft();
         //globalPos()获取根窗口的相对路径，frameGeometry().topLeft()获取主窗口左上角的位置
         event->accept();   //get mouse event
    }
}

//make the window dragable
void Add::mouseMoveEvent(QMouseEvent * event)
{
    if (event->buttons() == Qt::LeftButton) //LeftButton clicked
    {
         move(event->globalPos() - dragPosition);//move the window
         event->accept();
    }
}

void Add::paintEvent(QPaintEvent *event)
{
    QPainter p1(this);
    p1.setPen(Qt::NoPen);
    p1.setBrush(backgroundcolor);
    p1.drawRect(rect());
    QPen drawLine1;
    drawLine1.setColor(barcolor);
    drawLine1.setWidth(4);
    p1.setPen(drawLine1);
    p1.drawLine(0,110,400,110);
}

void Add::on_pushButton_clicked()
{
    string name=ui->nameEdit->text().toStdString();
    if(name=="")
    {
        return;
    }
    QString time1=ui->timeEdit->text(),time2=ui->timeEdit_2->text();
    QStringList sections1 = time1.split(QRegExp("[:]")),sections2 = time2.split(QRegExp("[:]"));
    if(sections1[0].toInt()==sections2[0].toInt()&&sections1[1]>sections2[1])
    {
        swap(time1,time2);
        ui->timeEdit->setTime(QTime(sections2[0].toInt(),sections2[1].toInt()));
        ui->timeEdit_2->setTime(QTime(sections1[0].toInt(),sections1[1].toInt()));
    }
    else if(sections1[0].toInt()>sections2[0].toInt())
    {
        swap(time1,time2);
        ui->timeEdit->setTime(QTime(sections2[0].toInt(),sections2[1].toInt()));
        ui->timeEdit_2->setTime(QTime(sections1[0].toInt(),sections1[1].toInt()));
    }
    int priority=ui->spinBox->text().toInt();
    string timeRange=(time1+"-"+time2).toStdString();
    bool checkable=1;
    bool repeatmap[7]={0};
    repeatmap[0]=ui->checkBox->checkState();
    repeatmap[1]=ui->checkBox_2->checkState();
    repeatmap[2]=ui->checkBox_3->checkState();
    repeatmap[3]=ui->checkBox_4->checkState();
    repeatmap[4]=ui->checkBox_5->checkState();
    repeatmap[5]=ui->checkBox_6->checkState();
    repeatmap[6]=ui->checkBox_7->checkState();
    emit senditem(name,priority,timeRange,checkable,repeatmap);
}
