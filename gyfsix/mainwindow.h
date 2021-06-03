#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPushButton>
#include<QWidget>
#include"rule.h"
#include<QMouseEvent>
#include<QEvent>
#include"mainpage.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    const int chessboard_size=21;  //棋盘线条数
    const int boundary=40;  //棋盘距离边缘的距离
    const int square_length=40;  //棋盘格子大小
    const int mouseOk=30; //鼠标的有效点击距离
    const int flag_length=11; //落子标记边长
    const int r=17; //棋子半径
    const int ai_time=700;  //模拟ai思考时间

    int qizi=0;
    rule *game; //游戏指针
    QTimer *time1;  //定时器
    void paintEvent(QPaintEvent *); //绘图
    void mouseReleaseEvent(QMouseEvent *event);  //鼠标点击
    void mouseMoveEvent(QMouseEvent *event);
    char game_style;  //游戏类型
    int clickPosX, clickPosY; //鼠标将点击位置
    void initgame(); //初始化游戏
    char game_type; //游戏类型

    void init(char type);//初始化PVP
    void start_EVE();

    void isEnd();  //判断游戏是否结束



private slots:
    void playByPerson();  //人下棋
    void playByAI();  //AI下棋
    void aiai();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
    void myslot();


public slots:
    void topage();
private:
    Ui::MainWindow *ui;
    mainpage page;
    QPushButton  *back;
    QPushButton *Pushbutton_4;
    QPushButton *black0;
    QPushButton *white0;
    QPushButton *btn;
    QPushButton *btn0;
};

#endif // MAINWINDOW_H
