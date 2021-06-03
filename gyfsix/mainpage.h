#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include<QPushButton>
#include"ui_mainpage.h"
namespace Ui {
class mainpage;
}


class mainpage : public QWidget
{
    Q_OBJECT
public:
    explicit mainpage(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);  //绘图
    QPushButton *button;  //按钮


private:
Ui::mainpage *ui;

signals:
    void mysignal();  //自定义信号
public slots:
     void sendslot();  //发出信号
private slots:
     void on_pushButton_clicked();
};

#endif // MAINPAGE_H
