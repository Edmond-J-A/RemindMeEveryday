#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include<QPen>
#include"menutable.h"
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
private slots:
    void on_closeButton_clicked();

    void on_setButton_clicked();

    void on_pushButton_clicked();

private:
    MenuTable menu;
    QPoint dragPosition;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
