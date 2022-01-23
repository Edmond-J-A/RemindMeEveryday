#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent,Qt::FramelessWindowHint),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initial();
}

void MainWindow::initial()
{
    backgroundcolor=QColor(255,247,209);
    barcolor=QColor(255, 213, 129);
    string path=getenv("USERPROFILE");
    path+="\\AppData\\preference.style";
    QFile file(QString::fromStdString(path));
    if (!file.open(QIODevice::ReadOnly))
    {
    }
    else
    {
        int lineindex=0;
        while (!file.atEnd())
        {
            QByteArray line = file.readLine();
            QString str(line);
            QStringList sections = str.split(QRegExp("[,]"));
            if(lineindex==0&&sections.size()==3)
            {
                QColor a(sections[0].toInt(),sections[1].toInt(),sections[2].toInt());
                backgroundcolor=a;
            }
            else if(lineindex==1&&sections.size()==3)
            {
                QColor a(sections[0].toInt(),sections[1].toInt(),sections[2].toInt());
                barcolor=a;
            }
            lineindex++;
        }
    }
    this->menu.Loadbyfile(this);
    this->menu.Show(this);

    setting=new Setting(barcolor,backgroundcolor);
    QString barcolortxt="background-color:rgb("+QString::number(barcolor.red())+"," +QString::number(barcolor.green())+"," +QString::number(barcolor.blue())+") ;";
    ui->label->setStyleSheet(
                barcolortxt
                );
    this->setting->changebarcolor(barcolor);
    connect(setting,SIGNAL(sendcolor(int,QColor)),this,SLOT(receivecolor(int,QColor)));

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
    p.setBrush(this->backgroundcolor);
    p.drawRect(rect());
    QPen drawLine;
    drawLine.setColor(this->barcolor);
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
    this->menu.Savetofile();
    this->setting->close();
    QString wrt="";
    string path=getenv("USERPROFILE");
    path+=+"\\AppData\\preference.style";
    QFile file(QString::fromStdString(path));
    file.resize(0);
    if(file.open( QIODevice::ReadWrite| QIODevice::Text))
    {
        wrt+=QString::number(backgroundcolor.red())+","+QString::number(backgroundcolor.green())+","+QString::number(backgroundcolor.blue())+"\n";
        file.write(wrt.toUtf8());
        wrt.clear();
        wrt+=QString::number(barcolor.red())+","+QString::number(barcolor.green())+","+QString::number(barcolor.blue())+"\n";
        file.write(wrt.toUtf8());
        wrt.clear();

    }


    close();
}

//set button
void MainWindow::on_setButton_clicked()
{
    setting->show();
}

void MainWindow::editfinished()
{
    QLineEdit *lineEdit=qobject_cast<QLineEdit *>(sender());
    int index=lineEdit->objectName().toInt();
    this->menu.Edititem(index,this,lineEdit->text().toStdString());
}

//test
void MainWindow::on_pushButton_clicked()
{
    if(this->menu.Finditem("")!=-1)
    {
        this->menu.Edititem(this->menu.Finditem(""),this,"test","10:00-11:00");
    }
    else
    {
        Item temp("test",0,"10:00-11:00",this,true);
        this->menu.Additem(temp);
        this->menu.Show(this);
    }
}

void MainWindow::checked()
{
    QCheckBox *checkb=qobject_cast<QCheckBox *>(sender());
    int index=checkb->objectName().toInt();
    QTime _Timer = QTime::currentTime().addMSecs(300);
    while( QTime::currentTime() < _Timer );
    this->menu.Doneitem(index,this);
}

void MainWindow::receivecolor(int mode,QColor c)
{
    if(mode==0)
    {
        this->backgroundcolor=c;
        repaint();
    }
    else if(mode==1)
    {
        this->barcolor=c;
        QString barcolortxt="background-color:rgb("+QString::number(barcolor.red())+"," +QString::number(barcolor.green())+"," +QString::number(barcolor.blue())+") ;";
        ui->label->setStyleSheet(
                    barcolortxt
                    );
        repaint();
    }
}
