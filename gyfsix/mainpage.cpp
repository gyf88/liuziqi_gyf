#include "mainpage.h"
#include<QPainter>
#include<QIcon>
#include<QPaintEvent>
#include<QAction>
#include<QMenuBar>
#include<QMenu>
#include<QMessageBox>
#include"ui_mainpage.h"


#define BACK ":/new/prefix1/image/1.png"

mainpage::mainpage(QWidget *parent) : QWidget(parent),
  ui(new Ui::mainpage)
{
  ui->setupUi(this);

    setWindowTitle("六子棋");
    this->setWindowIcon(QIcon(":/new/prefix1/Image/little.png")); //设置应用图标
    this->setFixedSize(1280,880);
    button=new QPushButton(this);
    button->move(QPoint(490,590));
    button->setFlat(true);  //透明效果
    button->setFixedSize(300,70);  //设定按钮尺寸
    button->setFont(QFont("华文彩云",30,800));
    button->setText("进入游戏");

    connect(button,&QPushButton::clicked,this,&mainpage::sendslot);  //连接信号


}
void mainpage::paintEvent(QPaintEvent *event)
{
    if(button->underMouse())
    {
        button->setFlat(false);
    }
    else
    {
        button->setFlat(true);
    }
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿,防止图像走样
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/Image/back4.png"));  //背景图片
    painter.drawPixmap(460,330,350,200,QPixmap(":/Image/title.png"));//drawPixmap:将给定像素图的矩形部分源绘制到绘图设备中的给定目标中。前面是坐标，后面是大小


}
void mainpage::sendslot()
{
    emit mysignal();   //发出信号，等待主窗口接收
}
