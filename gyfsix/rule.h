#ifndef RULE_H
#define RULE_H


class rule
{
public:
    rule();
    char game_type; //游戏类型  r人机，z智能，s双人
    int state; //游戏状态，1为正在进行，0为未进行
    bool player; //下棋方
    int white,black;
    int board[21][21];  //数组记录棋盘棋子，空白为0，白子为-1，黑子为1
    int score[21][21];  //数组记录棋盘落子得分

    bool Win(int x,int y);//判断是否输赢
    bool HeQi();  //判断是否和棋
    bool JinShou(int x,int y); //判断是否禁手

    void startgame(char type);  //开始游戏


    void Personaction(int x,int  y); //人进行操作
    void AIaction(int &clickX,int &clickY); //AI操作
    void playEVE(int &clickx,int &clicky);  //AI对AI
    void getScore();

    void clear();  //清理棋盘
    void clearScore();  //清空score数组
    void updateMap(int x, int y); //更新棋盘




};

#endif // RULE_H
