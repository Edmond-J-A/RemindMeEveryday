#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent,Qt::FramelessWindowHint),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initial();
    day_pass=startTimer(1000);
}

void MainWindow::initial()
{
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss ddd");
    ui->label_2->setText(current_date);
    QString dest=getenv("USERPROFILE");
    dest+=+"\\AppData\\Local\\RME";
    QDir dir;
    if(!dir.exists(dest))
    {
        dir.mkpath(dest);
    }
    backgroundcolor=QColor(255,247,209);
    barcolor=QColor(255, 213, 129);
    string path=getenv("USERPROFILE");
    path+="\\AppData\\Local\\RME\\preference.style";
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
    adding=new Add(barcolor,backgroundcolor);
    setting=new Setting(barcolor,backgroundcolor);
    QString barcolortxt="background-color:rgb("+QString::number(barcolor.red())+"," +QString::number(barcolor.green())+"," +QString::number(barcolor.blue())+") ;";
    ui->label->setStyleSheet(
                barcolortxt
                );
    this->setting->changebarcolor(barcolor);
    connect(setting,SIGNAL(sendcolor(int,QColor)),this,SLOT(receivecolor(int,QColor)));
    connect(adding,SIGNAL(senditem(string,int,string,bool,bool*)),this,SLOT(receiveitem(string,int,string,bool,bool*)));
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
         //globalPos()?????????????????????????????????frameGeometry().topLeft()?????????????????????????????????
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
    this->adding->close();
    QString wrt="";
    string path=getenv("USERPROFILE");
    path+=+"\\AppData\\Local\\RME\\preference.style";
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
    adding->close();
    setting->show();
}

//this will be called when an item's editing is finished
void MainWindow::editfinished()
{
    QLineEdit *lineEdit=qobject_cast<QLineEdit *>(sender());
    int index=lineEdit->objectName().toInt();
    this->menu.Edititem(index,this,lineEdit->text().toStdString());
}

//test
void MainWindow::on_pushButton_clicked()
{
    setting->close();
    adding->show();
}

//this will be called when a check box is checked
void MainWindow::checked()
{
    QCheckBox *checkb=qobject_cast<QCheckBox *>(sender());
    int index=checkb->objectName().toInt();
    QTime _Timer = QTime::currentTime().addMSecs(300);
    while( QTime::currentTime() < _Timer );
    this->menu.Doneitem(index,this);
}

//receive bar/background color sended from setting
void MainWindow::receivecolor(int mode,QColor c)
{
    if(mode==0)
    {
        this->backgroundcolor=c;
        delete adding;
        adding=new Add(barcolor,backgroundcolor);
        repaint();
    }
    else if(mode==1)
    {
        this->barcolor=c;
        QString barcolortxt="background-color:rgb("+QString::number(barcolor.red())+"," +QString::number(barcolor.green())+"," +QString::number(barcolor.blue())+") ;";
        ui->label->setStyleSheet(
                    barcolortxt
                    );
        delete adding;
        adding=new Add(barcolor,backgroundcolor);
        repaint();
    }
}

//move to last page
void MainWindow::on_pushButton_back_clicked()
{
    this->menu.subpage(this);
}

//move to next page
void MainWindow::on_pushButton_next_clicked()
{
    this->menu.addpage(this);
}

void MainWindow::receiveitem(string name,int priority,string timeRange,bool checkable,bool* repeatmap)
{
    qDebug()<<"testhere";
    Item temp(name,priority,timeRange,this,true,repeatmap);
    this->menu.Additem(temp);
    this->menu.Show(this);
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==day_pass)
    {
        QDateTime current_date_time = QDateTime::currentDateTime();
        QString temp = current_date_time.toString("ddd");
        QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss ddd");
        ui->label_2->setText(current_date);
        if(week!=temp)
        {
            week=temp;
            //????????????
        }
    }
}
