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
