#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include <QtGui>
#include<QPen>
#include<QMessageBox>
#include<QColorDialog>
namespace Ui {
class Setting;
}

class Setting : public QWidget
{
    Q_OBJECT

public:
    explicit Setting(QColor bar,QColor back,QWidget *parent = 0);
    ~Setting();
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void changebarcolor(QColor c=QColor(255, 213, 129));
private slots:
    void on_closeButton_clicked();

    void on_changebarButton_clicked();

    void on_changebackButton_clicked();

signals:
    void  sendcolor(int mode,QColor c);
private:
    QColor backgroundcolor,barcolor;
    Ui::Setting *ui;
    QPoint dragPosition;
};

#endif // SETTING_H
