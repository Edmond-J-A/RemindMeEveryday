#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent,Qt::FramelessWindowHint),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->menu.Show(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//make the window dragable
void MainWindow::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton) //LeftButton clicked
    {
         dragPosition = event->globalPos() - frameGeometry().topLeft();
         //globalPos()获取根窗口的相对路径，frameGeometry().topLeft()获取主窗口左上角的位置
         event->accept();   //get mouse event
    }
}

//make the window dragable
void MainWindow::mouseMoveEvent(QMouseEvent * event)
{
    if (event->buttons() == Qt::LeftButton) //LeftButton clicked
    {
         move(event->globalPos() - dragPosition);//move the window
         event->accept();
    }
}

//draw UI
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setPen(Qt::NoPen);
    QColor riceYellow(255,247,209);
    p.setBrush(riceYellow);
    p.drawRect(rect());
    QPen drawLine;
    drawLine.setColor(QColor(255, 213, 129));
    drawLine.setWidth(2);
    p.setPen(drawLine);
    for(int i=1;i<12;i++)
    {
        p.drawLine(20,i*30+30,380,i*30+30);
    }
}

//close button
void MainWindow::on_closeButton_clicked()
{
    close();
}

//set button
void MainWindow::on_setButton_clicked()
{

}

void MainWindow::editfinished()
{
    QLineEdit *lineEdit=qobject_cast<QLineEdit *>(sender());
    int index=lineEdit->objectName().toInt();
    this->menu.Edititem(index,this,lineEdit->text().toStdString());
}

void MainWindow::on_pushButton_clicked()
{
    Item temp("test",0,"10:00-11:00",this,true);
    this->menu.Additem(temp);
    this->menu.Show(this);
}
