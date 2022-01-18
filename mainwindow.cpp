#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent,Qt::FramelessWindowHint),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QList<QLineEdit*> leidts = findChildren<QLineEdit *>();
    int k=0;
    QList<QCheckBox*> checkbs = findChildren<QCheckBox *>();
    auto j=checkbs.begin();
    for(auto i = leidts.begin();i!=leidts.end();i++,j++)
    {
        (*i)->move(30,k*30+25);
        (*i)->resize(360,40);
        (*i)->setText("");
        k++;
        (*j)->setVisible(0);
        (*j)->resize(31,31);
        (*j)->move(5,k*30);
    }
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

void MainWindow::on_pushButton_clicked()
{
    Item temp("test",0,"10:00-11:00",true);
    this->menu.Additem(temp);
    vector<QLineEdit *> newlines=this->menu.Show();
    QList<QLineEdit*> leidts = findChildren<QLineEdit *>();
    QList<QCheckBox*> checkbs = findChildren<QCheckBox *>();

    int k=0;
    auto j=checkbs.begin();
    for(auto i = leidts.begin();i!=leidts.end();i++)
    {
        (*i)->move((newlines[k]->x()),(newlines[k]->y()));
        (*i)->resize((newlines[k]->width()),(newlines[k]->height()));
        (*i)->setText(newlines[k]->text());
        k++;

        if((*i)->text().size()!=0)
        {
            (*j)->setVisible(1);
        }
        j++;
    }
}
