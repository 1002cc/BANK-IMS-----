#include "../include/get_bankcard.h"
#include "../include/show.h"
#include "../include/function.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    bool login_success = false;

    BANK_DATABASE_T bank_database;
    bzero(&bank_database, sizeof(bank_database));
    P_BANK_DATABASE_T p_bank_database = &bank_database;
    int (*p_func[7])(P_BANK_DATABASE_T) = {open_an_account, account_cancellation, double_menu, search, change_all, auto_all, unfreeze_the_account};
    system("clear");
    Boot_animation();
    read_data(p_bank_database);
    data_log(p_bank_database);
    sleep(1);
    while (1)
    {
        int choose1 = 0, result = 0;
        frist_menu(); //首菜单
        printf("请输入" BLINK ":" DEFAULT_MODE);
        result = scanf("%d", &choose1);
        if (result != 1)
        {
            while ((result = getchar()) != '\n')
                ;
            printf("输入错误，请重新输入！\n");
            choose1 = 5;
        }
        switch (choose1)
        {
        case 0:
            write_data(p_bank_database);
            data_log1(p_bank_database);
            return 0;
            break;
        case 1:
            login_success = system_login();
            if (login_success == true)
            {
                progress_bar();
                int status = true;
                while (status)
                {
                    int result1 = 0;
                    admin_menu();
                    printf("请输入" BLINK ":" DEFAULT_MODE);
                    result1 = scanf("%d", &status);
                    if (result1 != 1)
                    {
                        while ((result1 = getchar()) != '\n')
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
                    case 7:
                        status = p_func[6](p_bank_database);
                        break;
                    case 8:
                        status = p_func[5](p_bank_database);
                        break;
                    default:
                        printf("没有这个选项！\n");
                        break;
                    }
                }
            }
            break;
        case 2:
            p_func[2](p_bank_database);
            break;
        default:
            printf("没有这个选项！\n");
            break;
        }
    }
}
