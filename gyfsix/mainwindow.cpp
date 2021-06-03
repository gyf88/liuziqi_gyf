#include "mainwindow.h"
#include"mainpage.h"
#include "ui_mainwindow.h"
#include<QAction>
#include<QPainter>
#include<QPen>
#include<QPaintEvent>
#include<QLabel>
#include<QBitmap>
#include<QPixmap>
#include<QPushButton>
#include<qmath.h>
#include<QBrush>
#include<QDebug>
#include<QMouseEvent>
#include<QMessageBox>
#include<QMenuBar>
#include<QMenu>
#include<QIcon>
#include<qtimer.h>


#define BACK_PNG  ":/Image/background.png"  //背景图片路径



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   this->setFixedSize(2*boundary+(chessboard_size-1)*square_length+400,2*boundary+(chessboard_size-1)*square_length);
    this->setWindowIcon(QPixmap(":/new/prefix1/Image/little.png")); //设置应用图标
    ui->pushButton->setText("双人对决");
    ui->pushButton->setFont(QFont("方正粗黑宋简体",20,700));
    ui->pushButton->setGeometry(900,150,300,60); //设置按钮位置和尺寸
    ui->pushButton_2->setText("人机对决");
    ui->pushButton_2->setGeometry(900,350,300,60);
    ui->pushButton_2->setFont(QFont("方正粗黑宋简体",20,700));
    ui->pushButton_3->setText("智能对决");
    ui->pushButton_3->setGeometry(900,550,300,60);
    ui->pushButton_3->setFont(QFont("方正粗黑宋简体",20,700));
    ui->pushButton->setFlat(true);  //设置按钮透明
    ui->pushButton_2->setFlat(true);
    ui->pushButton_3->setFlat(true);
    Pushbutton_4=new QPushButton(this);
    Pushbutton_4->setParent(this);
    Pushbutton_4->setGeometry(1080,800,150,50);
    Pushbutton_4->setText("关闭游戏");
    Pushbutton_4->setFont(QFont("华文彩云",20,400));
    Pushbutton_4->setFlat(true);
    back=new QPushButton(this);
    back->setParent(this);
    back->setGeometry(900,800,150,50);
    back->setText("返回界面");
    back->setFont(QFont("华文彩云",20,400));
    back->setFlat(true);
    connect(Pushbutton_4,&QPushButton::clicked,this,&MainWindow::close);
    black0=new QPushButton(this);
    white0=new QPushButton(this);
    black0->setGeometry(880,75,150,50);
    black0->setText("黑子");
    black0->setFont(QFont("隶书",20,400));
    black0->setFlat(true);
    white0->setGeometry(1050,75,150,50);
    white0->setText("白子");
    white0->setFont(QFont("隶书",20,400));
    white0->setFlat(true);
    black0->close();
    white0->close();
    btn=new QPushButton(this);
    btn->setGeometry(980,50,150,50);
    btn->setText("规则");
    btn->setFont(QFont("华文彩云",20,400));
    btn->setFlat(true);


    connect(black0,&QPushButton::clicked,this,[=](){
        qizi=1;
        black0->close();
        white0->close();
    });
    connect(white0,&QPushButton::clicked,this,[=](){
        qizi=-1;
        QTimer::singleShot(ai_time, this, SLOT(playByAI()));
        black0->close();
        white0->close();
    });



    QMenuBar *menubar=menuBar();  //设置菜单栏
    QMenu *menu_1=menubar->addMenu("六子棋"); //设置菜单
    QAction *action_0=menu_1->addAction("游戏简介");
    QString str_0=  "游戏简介：\n"
                    "    此游戏名为《六子棋》，规则与五子棋类似，详情见“规则介绍”。支持双人对战、人机对战、机机对战三种模式。";

    connect(action_0,&QAction::triggered,
            [=]()
            {
                QMessageBox::about(this,"游戏简介",str_0);
            }
            );
    QAction *action_1=menu_1->addAction("规则介绍");  //菜单下的按钮
    QString str=          "规则:\n"
                           "1.对峙双方谁的六个棋子先连在一条线即为胜者。\n"
                           "2.当有四个子连成一条直线时，就应采取防守，堵住四子的一端，否则就会输掉比赛。\n"
                           "3.应当避免在比赛内出现四四禁手、五五禁手等情况，否则就会不小心输掉比赛。\n"
                           "4.关于禁手:指对局中禁止先行一方（黑方）使用的战术，具体包括黑方一子落下时同时形成双四、双五或长连等三种棋形。禁手只对黑方有效，白方无禁手。黑方禁手的位置称为禁手点。";
              //规则介绍
    connect(action_1,&QAction::triggered,
            [=]()
            {
                QMessageBox::about(this,"游戏规则",str);
            }
            );   //弹出游戏规则内容

    connect(btn,&QPushButton::clicked,this,
            [=]()
            {
                QMessageBox::about(this,"游戏规则",str);
            }
            );   //弹出游戏规则内容

    initgame();  //默认初始化
    this->hide();
    page.show();
    connect(back,&QPushButton::clicked,this,&MainWindow::topage);   //连接信号和槽
    connect(&page,&mainpage::mysignal,this,&MainWindow::myslot);


}

void MainWindow::myslot()
{
    this->show();  //游戏界面显示
    page.hide();   //子窗口隐藏
}
void MainWindow::topage()  //返回主界面
{
    this->hide();
    page.show();
}
MainWindow::~MainWindow()
{
    delete ui;
    if(game)   //撤销游戏指针
    {
        delete game;
        game = nullptr;
    }
    if(time1)
    {
        delete time1;
        time1=nullptr;
    }
}
void MainWindow::paintEvent(QPaintEvent *)
{
    if(ui->pushButton->underMouse())
    {
        ui->pushButton->setFlat(false);
    }
    else
    {
        ui->pushButton->setFlat(true);
    }
    if(ui->pushButton_2->underMouse())
    {
        ui->pushButton_2->setFlat(false);
    }
    else
    {
        ui->pushButton_2->setFlat(true);
    }
    if(ui->pushButton_3->underMouse())
    {
        ui->pushButton_3->setFlat(false);
    }
    else
    {
        ui->pushButton_3->setFlat(true);
    }
    if(back->underMouse())
    {
        back->setFlat(false);
    }
    else
    {
        back->setFlat(true);
    }
    if(Pushbutton_4->underMouse())
    {
        Pushbutton_4->setFlat(false);
    }
    else
    {
        Pushbutton_4->setFlat(true);
    }
    if(black0->underMouse())
    {
        black0->setFlat(false);
    }
    else
    {
        black0->setFlat(true);
    }
    if(white0->underMouse())
    {
        white0->setFlat(false);
    }
    else
    {
        white0->setFlat(true);
    }
    if(btn->underMouse())
    {
        btn->setFlat(false);
    }
    else
    {
        btn->setFlat(true);
    }
    QPainter painter(this); //画家
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(BACK_PNG));
    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿,防止图像走样
    painter.drawPixmap(950,750,250,100,QPixmap(":/new/prefix1/image/title.png"));  //画logo
    QPen pen; //画笔
    pen.setWidth(2);  //画笔的线条宽度
    pen.setColor(Qt::black);
    painter.setPen(pen);  //将画笔交给画家
    for(int i=0;i<chessboard_size;i++)
    {
        painter.drawLine(boundary,boundary+i*square_length,boundary+(chessboard_size-1)*square_length,boundary+i*square_length);  //画横线
        painter.drawLine(boundary+i*square_length,boundary,boundary+i*square_length,boundary+(chessboard_size-1)*square_length);//画竖线

    }
    QBrush brush; //笔刷
    brush.setStyle(Qt::SolidPattern);
    if(clickPosX>=0&&clickPosX<chessboard_size&&clickPosY>=0&&clickPosY<chessboard_size&&game->state==1&&game->board[clickPosX][clickPosY]==0)  //范围内有效，绘制鼠标将要落子的标记点
    {
        if(game->player&&game_type=='s')
        {
            brush.setColor(Qt::yellow);
            painter.setBrush(brush);
            painter.drawEllipse(boundary + square_length * clickPosX-7,boundary + square_length * clickPosY-7,15,15);
        }
        else if(game->player==false&&game_type=='s')
        {
            brush.setColor(Qt::blue);
            painter.setBrush(brush);
            painter.drawEllipse(boundary + square_length * clickPosX-7,boundary + square_length * clickPosY-7,15,15);
        }
        else if(game->player&&game_type=='r'&&qizi==1)
        {
            brush.setColor(Qt::yellow);
            painter.setBrush(brush);
            painter.drawEllipse(boundary + square_length * clickPosX-7,boundary + square_length * clickPosY-7,15,15);
        }
        else if(game->player==false&&game_type=='r'&&qizi==-1)
        {
            brush.setColor(Qt::blue);
            painter.setBrush(brush);
            painter.drawEllipse(boundary + square_length * clickPosX-7,boundary + square_length * clickPosY-7,15,15);
        }

    }
    //根据数组情况绘制黑白棋子
    for(int i=0;i<chessboard_size;i++)
    {
        for(int j=0;j<chessboard_size;j++)
        {

            if(game->board[i][j]==1&&game->state==1) //游戏进行中才允许绘制棋子
           {
              brush.setColor(Qt::black);
              painter.setBrush(brush);
              painter.drawEllipse(QPoint(boundary + square_length * i ,boundary + square_length * j),r,r);
           }
            else if(game->board[i][j]==-1&&game->state==1)
            {
                brush.setColor(Qt::white);
                painter.setBrush(brush);
                painter.drawEllipse(QPoint(boundary + square_length * i ,boundary + square_length * j),r,r);
            }
        }
    }
    update();

}




void MainWindow::initgame()   //初始化
{

        game=new rule;
        time1=nullptr;
}
void MainWindow::init(char type)
{
    if(game)
    {
        delete game;
    }
    game=new rule;
    game->game_type=type;
    game->state=1;
    if(time1)
    {
        delete time1;
        time1=nullptr;
    }
    clickPosX=-1;
    clickPosY=-1;
    game->startgame(type);
    update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    //this->setMouseTracking(true);
    int x=event->x();
    int y=event->y();
    //qDebug()<<x<<y;

    //qDebug()<<x<<" "<<y;
    //保证鼠标在有效范围内,且棋盘边缘不落子
    if (x >= boundary-mouseOk  &&
            x <= boundary+(chessboard_size-1)*square_length+mouseOk  &&
            y >= boundary-mouseOk  &&
            y <= boundary+(chessboard_size-1)*square_length+mouseOk&&game->state==1)
    {

        // 获取距离最近的左上角的点
        int row = (x) / square_length;
        int col =( y) / square_length;


        int leftTopPosX = boundary + square_length * row;
        int leftTopPosY = boundary + square_length * col;
        //qDebug()<<leftTopPosX<<" "<<leftTopPosY;
        // 根据距离算出合适的点击位置,一共四个点，根据两点距离选最近的
        clickPosX = -1; // 初始化
        clickPosY = -1;
        int len = 0;

        // 确定一个误差在范围内的点，且只可能确定一个出来
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < mouseOk)  //在有效点范围内
        {
            clickPosX = row;
            clickPosY = col;
        }
        len = sqrt((x - leftTopPosX - square_length) * (x - leftTopPosX - square_length) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < mouseOk)
        {
            clickPosX = row+1;
            clickPosY = col;
        }
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY - square_length) * (y - leftTopPosY - square_length));
        if (len < mouseOk)
        {
            clickPosX = row;
            clickPosY = col+1;
        }
        len = sqrt((x - leftTopPosX - square_length) * (x - leftTopPosX - square_length) + (y - leftTopPosY - square_length) * (y - leftTopPosY - square_length));
        if (len < mouseOk)
        {
            clickPosX = row + 1;
            clickPosY = col + 1;
        }

    }
        update();

}
    //qDebug()<<clickPosX<<" "<<clickPosY;

    // 存了坐标后更新界面



void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{


      if (clickPosX != -1 && clickPosY != -1&&game->state==1)
      {

          if(game_type=='s')
          {

              playByPerson();  //人执行
          }
          if(game_type=='r')
          {
              if(qizi==1)
              {
                  if(game->player==true)playByPerson();
                  if(game->player==false)QTimer::singleShot(ai_time, this, SLOT(playByAI()));
              }
              if(qizi==-1)
              {
                  if(game->player==true)

                      QTimer::singleShot(ai_time, this, SLOT(playByAI()));
                  if(game->player==false)playByPerson();
              }

          }

      }


      update();
     //人操作
       //qDebug()<<clickPosX<<" "<<clickPosY<<endl;
       //qDebug()<<game->board[clickPosX*chessboard_size+clickPosY];

}
void MainWindow::playByPerson()
{

    if (clickPosX != -1 && clickPosY != -1 && game->board[clickPosX][clickPosY] == 0)
    {
        game->Personaction(clickPosX,clickPosY); //人进行下棋
        isEnd();
        update(); //更新界面
    }
}
void MainWindow::playByAI()
{
    game->AIaction(clickPosX,clickPosY);  //落子
    isEnd();  //判断输赢
    update();
}
void MainWindow::isEnd()
{
    if(clickPosX>=0&&clickPosX<chessboard_size&&clickPosY>=0&&clickPosY<chessboard_size&&game->board[clickPosX][clickPosY]!=0) //判断游戏输赢
    {
        if(game->board[clickPosX][clickPosY]==1&&game->JinShou(clickPosX,clickPosY)&&game->state==1)  //判断黑棋落子是否禁手
        {
            if(time1)
            {
                time1->stop();
                time1=nullptr;   //关闭定时器
            }
            QMessageBox::StandardButton standar=QMessageBox::information(this,"游戏结束！","禁手！ White-player win！\n 点击Ok返回主界面！",QMessageBox::Ok);
            if(standar==QMessageBox::Ok)
            {
                game->state=0;
                game->clear();
                ui->pushButton->setText("双人对决");
                ui->pushButton_2->setText("人机对决");
                ui->pushButton_3->setText("智能对决");
            }
        }
        else if(game->Win(clickPosX,clickPosY)==true&&game->state==1)  //弹出提示框
        {
            if(time1)
            {
                time1->stop();
                time1=nullptr;   //关闭定时器
            }
            QString string;
            if(game->board[clickPosX][clickPosY]==1)
            {
                string="Black-player win!";   //黑棋胜
            }
            else
            {
                string="White-player win!";  //白棋胜
            }
            QMessageBox::StandardButton standarbutton=QMessageBox::information(this," 游戏结束！",string+"\n"+" 点击 Ok 返回主界面!",QMessageBox::Ok);
            if(standarbutton==QMessageBox::Ok)
            {
                game->state=0;
                game->clear();
                ui->pushButton->setText("双人对决");
                ui->pushButton_2->setText("人机对决");
                ui->pushButton_3->setText("智能对决");
            }
        }
        else if(game->HeQi()&&game->state==1)
        {
            if(time1)
            {
                time1->stop();
                time1=nullptr;   //关闭定时器
            }
            game->state=0;
            QMessageBox::StandardButton standarbutton=QMessageBox::information(this,"游戏结束！","该局和棋啦！\n 点击Ok返回主界面",QMessageBox::Ok);
            if(standarbutton==QMessageBox::Ok)
            {
                game->state=0;
                game->clear();
                ui->pushButton->setText("双人对决");
                ui->pushButton_2->setText("人机对决");
                ui->pushButton_3->setText("智能对决");
            }
        }
    }
}
void MainWindow::aiai()
{

    game->playEVE(clickPosX,clickPosY);
    isEnd();
}
void MainWindow::start_EVE()
{
    time1=new QTimer(this);   //设置定时器
    connect(time1,SIGNAL(timeout()),this,SLOT(aiai()));   //连接槽函数
    time1->start(ai_time);   //设置ai思考时间
}

void MainWindow::on_pushButton_clicked()
{
    if(time1)
    {
        time1->stop();
        delete time1;
        time1=nullptr;     //关闭定时器
    }
     ui->centralwidget->setMouseTracking(true); //激活鼠标追踪
     setMouseTracking(true);  //激活整个窗体的鼠标追踪
     ui->pushButton->setMouseTracking(true); //进入某个按钮时，鼠标追踪属性失效，因此我们也需要激活该按钮的鼠标追踪功能
     game_type='s';  //双人模式类型
     init(game_type);  //初始化
     update();

}

void MainWindow::on_pushButton_2_clicked()
{
    black0->show();
    white0->show();
    btn->close();
    if(time1)
    {
        time1->stop();
        delete time1;
        time1=nullptr;   //关闭定时器
    }
    ui->centralwidget->setMouseTracking(true); //激活鼠标追踪
    this->setMouseTracking(true);  //激活整个窗体的鼠标追踪
    ui->pushButton_2->setMouseTracking(true); //进入某个按钮时，鼠标追踪属性失效，因此我们也需要激活该按钮的鼠标追踪功能
    game_type='r';
    init(game_type);
    update();
}

void MainWindow::on_pushButton_3_clicked()
{
    this->setMouseTracking(false);  //关闭鼠标追踪

    game_type='z'; //智能对决
    init(game_type);
    srand((unsigned)time(nullptr));
    //电脑首次落子尽量落在棋盘中间区域
    clickPosX=chessboard_size/2+rand()%4;
    clickPosY=chessboard_size/2+rand()%4;
    game->board[clickPosX][clickPosY]=1;
    game->player=!game->player;
    start_EVE();//开始下棋
    update();
}


