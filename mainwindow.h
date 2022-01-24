#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include<QPen>
#include"menutable.h"
#include<QMessageBox>
#include<setting.h>
#include<add.h>
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void initial();
private slots:
    void on_closeButton_clicked();

    void on_setButton_clicked();

    void on_pushButton_clicked();

    void editfinished();

    void checked();

    void receivecolor(int mode,QColor c);

    void on_pushButton_back_clicked();

    void on_pushButton_next_clicked();

private:
    Add *adding;
    Setting *setting;
    MenuTable menu;
    QColor backgroundcolor,barcolor;
    QPoint dragPosition;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
