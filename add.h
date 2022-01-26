#ifndef ADD_H
#define ADD_H

#include <QWidget>
#include <QtGui>
#include<QPen>
#include<QMessageBox>
#include<QDebug>
using namespace std;
namespace Ui {
class Add;
}

class Add : public QWidget
{
    Q_OBJECT

public:
    explicit Add(QColor bar,QColor back,QWidget *parent = 0);
    ~Add();
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);
private slots:
    void on_closeButton_clicked();

    void on_pushButton_clicked();

signals:
    void  senditem(string name,int priority,string timeRange,bool checkable=1,bool* repeatmap=NULL);

private:
    Ui::Add *ui;
    QPoint dragPosition;
    QColor backgroundcolor,barcolor;
};

#endif // ADD_H
