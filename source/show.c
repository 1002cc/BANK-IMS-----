#include "../include/show.h"

void admin_menu(void)
{
    system("clear");
    MOVETO(5, 28);
    printf("===========银行系统(管理员)============\n");
    MOVERIGHT(28);
    printf("---*           1.状态机            *---\n");
    MOVERIGHT(28);
    printf("---*           2.开户              *---\n");
    MOVERIGHT(28);
    printf("---*           3.销户              *---\n");
    MOVERIGHT(28);
    printf("---*           4.登陆              *---\n");
    MOVERIGHT(28);
    printf("---*           5.查询              *---\n");
    MOVERIGHT(28);
    printf("---*           6.修改              *---\n");
    MOVERIGHT(28);
    printf("---*           7.解冻              *---\n");
    MOVERIGHT(28);
    printf("---*           0.退出              *---\n");
    MOVERIGHT(28);
    printf("=======================================\n");
    MOVERIGHT(28);
}
void user_menu(void)
{
    system("clear");
    MOVETO(5, 30);
    printf("------------银行系统(客户端)-------------\n");
    MOVERIGHT(28);
    printf("---*       1.存钱      2.取钱       *---\n");
    MOVERIGHT(28);
    printf("---*       3.转账      4.查询       *---\n");
    MOVERIGHT(28);
    printf("---*       5.修改      0.退出       *---\n");
    MOVERIGHT(28);
    printf("----------------------------------------\n");
    MOVERIGHT(28);
}
void Boot_animation(void)
{
    MOVETO(5, 30);
    char bank[8][20] = {"欢", "迎", "使", "用", "B", "I", "M", "S"};
    char bank1[8][20] = {"正", "在", "加", "载", "系", "统"};
    for (int i = 0; i < 13; i++)
    {
        printf("*");
        usleep(60000);
        fflush(stdout);
    }
    for (int i = 0; i < 8; i++)
    {
        printf("%s", bank[i]);
        usleep(80000);
        fflush(stdout);
    }
    for (int i = 0; i < 13; i++)
    {
        printf("*");
        usleep(60000);
        fflush(stdout);
    }
    printf("\n");
    MOVERIGHT(29);
    for (int i = 0; i < 6; i++)
    {
        printf("%s", bank1[i]);
        usleep(80000);
        fflush(stdout);
    }
    for (int i = 0; i < 4; i++)
    {
        printf(".");
        usleep(70000);
        fflush(stdout);
    }
    printf("\n");
    progress_bar();
    usleep(100000);
    system("clear");
    MOVERIGHT(28);
}

void frist_menu(void)
{
    system("clear");
    MOVETO(5, 29);
    printf("************银行信息管理系统***************\n");
    MOVERIGHT(28);
    printf("****          1.管理员登陆            ****\n");
    MOVERIGHT(28);
    printf("****           2.客户端               ****\n");
    MOVERIGHT(28);
    printf("****            0.退出                ****\n");
    MOVERIGHT(28);
    printf("*******************************************\n");
    MOVERIGHT(28);
}
void change(void)
{
    system("clear");
    MOVETO(5, 30);
    printf("------------------修改--------------\n");
    MOVERIGHT(28);
    printf("---*           1.修改密码        *---\n");
    MOVERIGHT(28);
    printf("---*          2.修改用户名       *---\n");
    MOVERIGHT(28);
    printf("---*         3.修改电话号码      *---\n");
    MOVERIGHT(28);
    printf("---*             0.退出         *---\n");
    MOVERIGHT(28);
    printf("------------------------------------\n");
    MOVERIGHT(28);
}

void progress_bar(void)
{
    unsigned int i = 0, j = 0;
    unsigned char bar[51];
    memset(bar, '\0', sizeof(bar));
    while (j <= 50)
    {
        printf("                             [%-50s][%d%%]\r", bar, i);
        fflush(stdout);
        bar[j] = '=';
        usleep(60000);
        i += 2;
        j++;
    }
    printf("\n");
}

void wiat(void)
{
    printf("\n");
    MOVERIGHT(35);
    printf("请稍后");
    for (int i = 0; i < 4; ++i)
    {
        printf(".");
        fflush(stdout);
        usleep(90000);
    }
    printf("\n");
}