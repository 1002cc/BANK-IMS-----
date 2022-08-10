#include "../include/get_bankcard.h"
#include "../include/show.h"
#include "../include/function.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


int main(int argc, char *argv[])
{
    int uers_number = 0; //用户数量
    int loi = 1;         //判断管理员是否登陆成功
    bool login_success = false;

    BANK_DATABASE_T bank_database;
    bzero(&bank_database, sizeof(bank_database));
    P_BANK_DATABASE_T p_bank_database = &bank_database;
    for (int i = 0; i < 1024; ++i)
    {
       memset(p_bank_database->user[i].money,48,1);  //money清零
    }

    int (*p_func[5])(P_BANK_DATABASE_T) ={open_an_account,account_cancellation,double_menu,search,change_all};
    while (1)
    {
        int choose1 = 0, result10 = 0;
        frist_menu(); //首菜单
        printf("请选择：");
        result10 = scanf("%d", &choose1);
        if (result10 != 1)
        {
            while ((result10 = getchar()) != '\n')
                ;
            printf("输入错误，请重新输入！\n");
        }
        switch (choose1)
        {
        case 0:
            return 0;
            break;
        case 1:
            login_success = system_login();
            if (login_success == true)
            {
                int status = true;
                while (status)
                {
                    int result9 = 0;
                    admin_menu();
                    printf("请输入：\n");
                    result9 = scanf("%d", &status);
                    if (result9 != 1)
                    {
                        while ((result9 = getchar()) != '\n')
                            ;
                        printf("输入错误，请重新输入！\n");
                    }
                    switch (status)
                    {
                    case 0:
                        status = 0;
                        break;
                    case 1:
                        status = true;
                        break;
                    case 2:
                        status = p_func[0](p_bank_database);
                        break;
                    case 3:
                        status = p_func[1](p_bank_database);
                        break;
                    case 4:
                        status = p_func[2](p_bank_database);
                        break;
                    case 5:
                        status = p_func[3](p_bank_database);
                        break;
                    case 6:
                        status = p_func[4](p_bank_database);
                        break;
                    default:
                        printf("没有这个选项！\n");
                        break;
                    }
                }
            }
            break;
        case 2:
            double_menu(p_bank_database);
            break;
        default:
            printf("没有这个选项！\n");
            break;
        }
    }
}
