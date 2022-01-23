#include "setting.h"
#include "ui_setting.h"

Setting::Setting(QColor bar,QColor back,QWidget *parent) :
    QWidget(parent,Qt::FramelessWindowHint),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
    backgroundcolor=back;
    barcolor=bar;
}

Setting::~Setting()
{
    delete ui;
}

//make the window dragable
void Setting::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton) //LeftButton clicked
    {
         dragPosition = event->globalPos() - frameGeometry().topLeft();
         //globalPos()获取根窗口的相对路径，frameGeometry().topLeft()获取主窗口左上角的位置
         event->accept();   //get mouse event
    }
}

//make the window dragable
void Setting::mouseMoveEvent(QMouseEvent * event)
{
    if (event->buttons() == Qt::LeftButton) //LeftButton clicked
    {
         move(event->globalPos() - dragPosition);//move the window
         event->accept();
    }
}

//draw UI
void Setting::paintEvent(QPaintEvent *event)
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

void Setting::on_closeButton_clicked()
{
    close();
}

void Setting::changebarcolor(QColor c)
{
    QString ccolortxt="background-color:rgb("+QString::number(c.red())+"," +QString::number(c.green())+"," +QString::number(c.blue())+") ;";
    ui->label->setStyleSheet(
                ccolortxt
                );
}

void Setting::on_changebarButton_clicked()
{
    QColorDialog *a;
    a=new QColorDialog(this);
    QColor c = a->getColor();
    barcolor=c;
    QString ccolortxt="background-color:rgb("+QString::number(c.red())+"," +QString::number(c.green())+"," +QString::number(c.blue())+") ;";
    ui->changebarButton->setStyleSheet(
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
                );
    changebarcolor(c);
    emit sendcolor(1,c);
}



void Setting::on_changebackButton_clicked()
{
    QColorDialog *a;
    a=new QColorDialog(this);
    QColor c = a->getColor();
    backgroundcolor=c;
    QString ccolortxt="background-color:rgb("+QString::number(c.red())+"," +QString::number(c.green())+"," +QString::number(c.blue())+") ;";
    ui->changebackButton->setStyleSheet(
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
                );
    repaint();
    emit sendcolor(0,c);
}

