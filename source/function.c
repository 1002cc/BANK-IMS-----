#include "../include/function.h"

bool system_login() //管理员登陆
{
    char getaccount[10] = {admin_name};
    char getpassword[7] = {admin_password};
    int count_one = 0, count_two = 0;
    char input_account[10] = {0};
    char input_password[7] = {0};
    for (int i = 0; i < N; i++)
    {
        MOVERIGHT(28);
        printf("请输入账号：");
        scanf("%s", input_account);
        MOVERIGHT(28);
        printf("请输入密码：");
        scanf("%s", input_password);
        count_one = strcmp(input_account, getaccount);
        count_two = strcmp(input_password, getpassword);
        if (count_one == 0 && count_two == 0)
        {
            return true;
            break;
        }
        else
        {
            MOVERIGHT(28);
            printf("账号或密码错误，请重新输入！！！！\n");
        }
    }
    return false;
}

int open_an_account(P_BANK_DATABASE_T p_bank_database) //开户
{
    int count1 = 1, count = 1, count6 = 0;
    int result1 = 0, result2 = 0;
    char name[24] = {0}, phone[12] = {0}, password[7] = {0};
    for (int i = 0; i < count; i++)
    {
        int count3 = 1, count4 = 1, count5 = 1;
        MOVERIGHT(28);
        printf("---------------------开户--------------------\n");
        for (int i = 0; i < count5; i++)
        {
            MOVERIGHT(28);
            printf("请输入名字：");
            scanf("%s", name);
            for (int j = 0; j < (p_bank_database->user_number); j++)
            {
                result2 = strcmp(name, p_bank_database->user[j].name);
                if (result2 == 0)
                {
                    MOVERIGHT(28);
                    printf("该用户已注册\n");
                    MOVERIGHT(28);
                    printf("重名继续输入:1 重新输入:0\n");
                    MOVERIGHT(28);
                    scanf("%d", &count6);
                    if (count6 == 1)
                    {
                        break;
                    }
                    else
                    {
                        count5++;
                        break;
                    }
                }
            }
        }
        strcpy(p_bank_database->user[p_bank_database->user_number].name, name);

        for (int j = 0; j < count4; j++) //设置11位数手机号码
        {
            MOVERIGHT(28);
            printf("请输入11位手机号:");
            scanf("%s", phone);
            if (strlen(phone) != 11)
            {
                MOVERIGHT(28);
                printf("输入错误!请输入11位手机号\n");
                count4++;
            }
            else
            {
                for (int n = 0; n < (p_bank_database->user_number); n++)
                {
                    result1 = strcmp(phone, p_bank_database->user[n].phone);
                    if (result1 == 0)
                    {
                        MOVERIGHT(28);
                        printf("该电话号码已注册\n");
                        count4++;
                        break;
                    }
                }
            }
        }
        strcpy(p_bank_database->user[p_bank_database->user_number].phone, phone);

        for (int j = 0; j < count3; j++)
        {
            MOVERIGHT(28);
            printf("请输入六位数密码：");
            scanf("%s", password);
            if (strlen(password) != 6)
            {
                MOVERIGHT(28);
                printf("输入错误！请输入六位数密码\n");
                count3++;
            }
            else
            {
                break;
            }
        }
        strcpy(p_bank_database->user[p_bank_database->user_number].password, password);
        getbank_card(p_bank_database);

        p_bank_database->user_number++;
        MOVERIGHT(28);
        printf("继续输入请输入:1  返回请输入:0  \n");
        MOVERIGHT(28);
        scanf("%d", &count1);
        if (count1 == 0)
        {
            user_log(p_bank_database);
            write_data(p_bank_database);
            return 1;
        }
        else
        {
            count++;
        }
    }
}

int write_data(P_BANK_DATABASE_T p_bank_database)
{
    FILE *fp = fopen("database.txt", "w");
    if (!fp)
        return -1;
    fprintf(fp, "%d\n", p_bank_database->user_number);
    for (int i = 0; i < p_bank_database->user_number; ++i)
    {
        fprintf(fp, "%s\n%s\n%s\n%s\n%d\n", p_bank_database->user[i].name, p_bank_database->user[i].phone, p_bank_database->user[i].password, p_bank_database->user[i].bank_card, p_bank_database->user[i].money);
    }
    fclose(fp);
}

int read_data(P_BANK_DATABASE_T p_bank_database)
{
    int n = 0, i = 0;
    char buf[100] = {0};
    FILE *fp = fopen("database.txt", "r");
    MOVERIGHT(7);
    printf("正在加载数据----\n");
    if (!fp)
        return -1;
    memset(buf, 0, 100);
    buf[strlen(buf) - 1] = '\0';
    fgets(buf, 100, fp);
    sscanf(buf, "%d", &p_bank_database->user_number);
    MOVERIGHT(35);
    printf("user_number:%d", p_bank_database->user_number);
    while (!feof(fp))
    {
        memset(buf, 0, 100);
        fgets(buf, 100, fp);
        buf[strlen(buf) - 1] = '\0';
        strcpy(p_bank_database->user[i].name, buf);

        memset(buf, 0, 100);
        fgets(buf, 100, fp);
        buf[strlen(buf) - 1] = '\0';
        strcpy(p_bank_database->user[i].phone, buf);

        memset(buf, 0, 100);
        fgets(buf, 100, fp);
        buf[strlen(buf) - 1] = '\0';
        strcpy(p_bank_database->user[i].password, buf);

        memset(buf, 0, 100);
        fgets(buf, 100, fp);
        buf[strlen(buf) - 1] = '\0';
        strcpy(p_bank_database->user[i].bank_card, buf);

        memset(buf, 0, 100);
        fgets(buf, 100, fp);
        buf[strlen(buf) - 1] = '\0';
        sscanf(buf, "%d", &p_bank_database->user[i].money);

        i++;
    }

    wiat();
    MOVERIGHT(35);
    printf("数据加载完成\n");
    fclose(fp);
}

int account_cancellation(P_BANK_DATABASE_T p_bank_database) //销户
{
    MOVERIGHT(28);
    printf("---------------------销户--------------------\n");
    if (p_bank_database->user_number == 0)
    {
        MOVERIGHT(28);
        printf("数据库中没有一个用户\n");
        return 1;
    }
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < p_bank_database->user_number; i++)
    {
        printf("第%d位用户\n用户名:%s\n", i + 1, (p_bank_database->user[i].name));
    }
    printf("-------------------------------------------------------------\n");
    int result = 0, k = 1, count = 1;
    char delete_account[24] = {0};

    for (int j = 0; j < count; j++)
    {
        printf("请输入要删除的用户：");
        result = scanf("%s", delete_account);
        if (result == 0)
        {
            while ((result = getchar()) != '\n')
                ;
            printf("输入错误，请重新输入！\n");
            count++;
        }
        for (int i = 0; i < p_bank_database->user_number; i++)
        {
            if ((strcmp(delete_account, (p_bank_database->user[i].name)) == 0) || (strcmp(delete_account, (p_bank_database->user[i].phone)) == 0))
            {
                printf("正在删除----\n");
                user_log_del(p_bank_database,i);
                for (int j = 0; j < p_bank_database->user_number; j++)
                {
                    strcpy((p_bank_database->user[i].name), (p_bank_database->user[i + 1].name));
                    strcpy((p_bank_database->user[i].password), (p_bank_database->user[i + 1].password));
                    strcpy((p_bank_database->user[i].phone), (p_bank_database->user[i + 1].phone));
                    strcpy((p_bank_database->user[i].bank_card), (p_bank_database->user[i + 1].bank_card));
                    p_bank_database->user[i].money = 0;
                    i++;
                }
                k = 0;
                (p_bank_database->user_number)--;
                printf("删除完成\n");
                break;
            }
        }
        if (k == 1)
        {
            printf("没有找到该用户!!\n");
        }
    }
    sleep(1);
    return 1;
}

int unfreeze_the_account(P_BANK_DATABASE_T p_bank_database) //解冻
{
    char unfreeze_account[20] = {0};
    MOVERIGHT(28);
    printf("------------------解冻账号-----------------\n");
    MOVERIGHT(28);
    printf("冻结账户:%d\n", p_bank_database->frozen_count);
    for (int i = 0; i < p_bank_database->frozen_count; i++)
    {
        printf("%s\n", p_bank_database->frozen_account[i].frozen_data);
    }
    if (p_bank_database->frozen_count == 0)
    {
        MOVERIGHT(28);
        printf("没有账号被冻结\n");
        sleep(2);
        return 1;
    }
    MOVERIGHT(28);
    printf("请输入解冻账号:");
    scanf("%s", unfreeze_account);
    for (int i = 0; i < p_bank_database->frozen_count; i++)
    {
        if (strcmp(unfreeze_account, p_bank_database->frozen_account[i].frozen_data) == 0)
        {
            memset(p_bank_database->frozen_account[i].frozen_data, '\0', sizeof(FROZEN_T));
            p_bank_database->frozen_count--;
            MOVERIGHT(28);
            printf("解冻成功!!\n");
            return 1;
        }
    }
    sleep(2);
    return 1;
}

int search(P_BANK_DATABASE_T p_bank_database) //查询用户
{
    MOVERIGHT(28);
    printf("-------------------查看用户------------------\n");
    int flag = 0;
    if (p_bank_database->user_number == 0)
    {
        MOVERIGHT(28);
        printf("数据库中没有一个用户\n");
        return 1;
    }
    char inquire_user[20] = {0}, all[4] = {"all"}, frozen[7] = {"frozen"};
    MOVERIGHT(28);
    printf("当前用户数:%d\n", p_bank_database->user_number);
    MOVERIGHT(28);
    printf("请输入要查询的用户(all为全部显示)(frozen显示冻结账户):");
    scanf("%s", inquire_user);
    if (strcmp(inquire_user, all) == 0)
    {
        for (int i = 0; i < p_bank_database->user_number; i++)
        {
            printf("-------------------------------------------------------------\n");
            printf("第%d个用户名是:%s\n电话号码是:%s\n密码是:%s\n银行卡号:%s\n金额%d\n", i + 1,
                   (p_bank_database->user[i].name), (p_bank_database->user[i].phone),
                   (p_bank_database->user[i].password), (p_bank_database->user[i].bank_card), (p_bank_database->user[i].money));
            printf("-------------------------------------------------------------\n");
        }
    }
    else if (strcmp(inquire_user, frozen) == 0)
    {
        MOVERIGHT(28);
        printf("冻结账户:%d\n", p_bank_database->frozen_count);
        for (int i = 0; i < p_bank_database->frozen_count; i++)
        {
            printf("%s\n", p_bank_database->frozen_account[i].frozen_data);
        }
    }
    else
    {
        for (int i = 0; i < p_bank_database->user_number; i++)
        {
            if (strcmp(p_bank_database->user[i].name, inquire_user) == 0)
            {
                flag = 1;
                printf("-------------------------------------------------------------\n");
                printf("第%d个用户名是:%s\n电话号码是:%s\n密码是:%s\n银行卡号:%s\n", i + 1,
                       (p_bank_database->user[i].name), (p_bank_database->user[i].phone),
                       (p_bank_database->user[i].password), (p_bank_database->user[i].bank_card));
                printf("-------------------------------------------------------------\n");
                break;
            }
        }
        if (flag == 0)
        {
            MOVERIGHT(28);
            printf("没有该用户\n");
        }
    }
    int count = 0;
    printf("返回:0\n");
    printf("请输入" BLINK ":" DEFAULT_MODE);
    scanf("%d", &count);
    if (count == 0)
    {
    }
    return 1;
}

int change_all(P_BANK_DATABASE_T p_bank_database) //选择
{
    int result = 0, count = 0, count1 = 1;
    int result1 = 0;
    int flag = 0, flag1 = 0;
    char change_user_name[24] = {0};
    if (p_bank_database->user_number == 0)
    {
        MOVERIGHT(28);
        printf("数据库中没有一个用户\n");
        return 1;
    }
    MOVERIGHT(28);
    printf("-----------------修改------------------\n");
    MOVERIGHT(28);
    printf("请输入用户名" BLINK ":" DEFAULT_MODE );
    scanf("%s", change_user_name);
    for (int i = 0; i < p_bank_database->user_number; i++)
    {
        result1 = strcmp(change_user_name, p_bank_database->user[i].name);
        if (result1 == 0)
        {
            do
            {
                change();
                printf("请输入" BLINK ":" DEFAULT_MODE);
                result = scanf("%d", &count);
                if (result != 1)
                {
                    while ((result = getchar()) != '\n')
                        ;
                    MOVERIGHT(28);
                    printf("输入错误，请重新输入！\n");
                }
                switch (count)
                {
                case 0:
                    count1 = 0;
                    break;
                case 1:
                    change_password(p_bank_database, i);
                    break;
                case 2:
                    change_name(p_bank_database, i);
                    break;
                case 3:
                    change_phone(p_bank_database, i);
                    break;
                default:
                    MOVERIGHT(28);
                    printf("没有这个选择！\n");
                    break;
                }
            } while (count1);
            break;
        }
        else if (result1 != 0 && i + 1 == p_bank_database->user_number)
        {
            printf("没有该用户！\n");
            break;
        }
    }
    return 1;
}

void change_two_all(P_BANK_DATABASE_T p_bank_database, int *xianzai)
{
    int result = 0;
    int count = 0, count1 = 1;
    while (count1)
    {
        change();
        printf("请输入" BLINK ":" DEFAULT_MODE);
        result = scanf("%d", &count);
        if (result != 1)
        {
            while ((result = getchar()) != '\n')
                ;
            MOVERIGHT(28);
            printf("输入错误，请重新输入！\n");
        }
        switch (count)
        {
        case 0:
            count1 = 0;
            break;
        case 1:
            change_password(p_bank_database, *xianzai);
            break;
        case 2:
            change_name(p_bank_database, *xianzai);
            break;
        case 3:
            change_phone(p_bank_database, *xianzai);
            break;
        default:
        MOVERIGHT(28);
            printf("没有这个选择！\n");
            break;
        }
    }
}

void change_password(P_BANK_DATABASE_T p_bank_database, int flang) //修改密码
{
    int result = 0, k = 1, count6 = 1, count7 = 1;
    int count1 = 0;
    char changepassword1[1024] = {0};
    char changepassword2[1024] = {0};
    char name[1024] = {0};
    MOVERIGHT(28);
    printf("--------------------修改---------------------\n");
    MOVERIGHT(28);
    printf("用户：%s\n", (p_bank_database->user[flang].name));
    MOVERIGHT(28);
    printf("原密码：%s\n", (p_bank_database->user[flang].password));
    do
    {
        for (int j = 0; j < count6; j++)
        {
            MOVERIGHT(28);
            printf("请输入六位数密码：");
            scanf("%s", changepassword1);
            if (strlen(changepassword1) != 6)
            {
                MOVERIGHT(28);
                printf("输入错误！请输入六位数密码\n");
                count6++;
            }
        }
        for (int j = 0; j < count7; j++)
        {
            MOVERIGHT(28);
            printf("请再次输入密码：");
            scanf("%s", changepassword2);
            if (strlen(changepassword2) != 6)
            {
                MOVERIGHT(28);
                printf("输入错误！请输入六位数密码\n");
                count7++;
            }
        }
        if (strcmp(changepassword1, changepassword2) != 0)
        {
            MOVERIGHT(28);
            printf("两次密码不一致，请重新输入\n");
            k = 3;
            count1 = 1;
        }
        else
        {
            strcpy((p_bank_database->user[flang].password), changepassword2);
            k = 0;
            MOVERIGHT(28);
            printf("修改密码成功！！\n");
            count1 = 0;
        }

    } while (count1);
}

void change_name(P_BANK_DATABASE_T p_bank_database, int flang) //修改用户名
{
    int count5 = 1, result2 = 0, count6 = 0;
    char change_user_name[24] = {0};
    MOVERIGHT(28);
    printf("-----------------修改用户名------------------\n");
    MOVERIGHT(28);
    printf("原用户名：%s\n", (p_bank_database->user[flang].name));
    for (int i = 0; i < count5; i++)
    {
        MOVERIGHT(28);
        printf("请输入名字：");
        scanf("%s", change_user_name);
        for (int j = 0; j < p_bank_database->user_number; j++)
        {
            result2 = strcmp(change_user_name, (p_bank_database->user[j].name));
            if (result2 == 0)
            {
                MOVERIGHT(28);
                printf("该用户已注册\n");
                MOVERIGHT(28);
                printf("重名继续:1 重新输入:0\n");
                MOVERIGHT(28);
                scanf("%d", &count6);
                if (count6 == 1)
                {
                    break;
                }
                else
                {
                    count5++;
                    break;
                }
            }
        }
        strcpy((p_bank_database->user[flang].name), change_user_name);
        MOVERIGHT(28);
        printf("修改成功！\n");
    }
}

void change_phone(P_BANK_DATABASE_T p_bank_database, int flang) //修改电话号码
{
    char name[24] = {0}, newphone[12] = {0};
    int result = 0, count6 = 1, result1 = 0, result2 = 0, result3 = 0, count4 = 0, k = 0;
    MOVERIGHT(28);
    printf("-----------------修改电话号码------------------\n");
    MOVERIGHT(28);
    printf("用户：%s\n", (p_bank_database->user[flang].name));
    MOVERIGHT(28);
    printf("原电话号码:%s\n", (p_bank_database->user[flang].phone));
    for (int j = 0; j < count6; j++)
    {
        MOVERIGHT(28);
        printf("请输入新电话号码:\n");
        scanf("%s", newphone);
        if (strlen(newphone) != 11)
        {
            MOVERIGHT(28);
            printf("输入错误!请输入11位数电话号码\n");
            count6++;
        }
        else
        {
            for (int n = 0; n < p_bank_database->user_number; n++)
            {
                result3 = strcmp(newphone, (p_bank_database->user[n].phone));
                if (result3 == 0)
                {
                    MOVERIGHT(28);
                    printf("该电话号码已注册\n");
                    k = 1;
                    break;
                }
            }
            if (k == 0)
            {
                strcpy((p_bank_database->user[flang].phone), newphone);
                MOVERIGHT(28);
                printf("修改成功\n");
            }
        }
    }
    sleep(1);
}

bool login(P_BANK_DATABASE_T p_bank_database, int *xianzai) //登陆
{
    system("clear");
    int bnm = 0, i = 0, lop = 2;
    do
    {
        int count_one = 1, count_two = 1, count_four = 1;
        char input_account[20] = {0};
        char input_password[20] = {0};
        MOVERIGHT(28);
        printf("-------------------登陆--------------------\n");
        MOVERIGHT(28);
        printf("请输入用户名或手机号:");
        scanf("%s", input_account);
        MOVERIGHT(28);
        printf("请输入密码：");
        scanf("%s", input_password);
        for (int i = 0; i < p_bank_database->frozen_count; i++)
        {
            if (strcmp(input_account, p_bank_database->frozen_account[i].frozen_data) == 0)
            {
                MOVERIGHT(28);
                printf("该用户已被冻结,请联系管理员\n");
                sleep(2);
                return false;
            }
        }
        for (i = 0; i < p_bank_database->user_number; i++)
        {
            count_one = (strcmp(input_account, p_bank_database->user[i].name));
            count_four = (strcmp(input_account, p_bank_database->user[i].phone));
            count_two = (strcmp(input_password, p_bank_database->user[i].password));
            if ((count_one == 0 || count_four == 0) && count_two == 0)
            {
                lop = 1;
                *xianzai = i;
                return true;
            }
            else
            {
                lop = 0;
            }
        }
        if (lop == 0)
        {
            MOVERIGHT(28);
            printf("账号密码错误，请重新输入！！！！\n");
            bnm++;
            if (bnm >= N)
            {
                MOVERIGHT(28);
                printf("输入错误三次，账号已被冻结\n");
                int k = p_bank_database->frozen_count;
                strcpy(p_bank_database->frozen_account[k].frozen_data, input_account);
                p_bank_database->frozen_count++;
                sleep(2);
                return false;
                bnm = 0;
            }
        }
    } while (bnm);
}

int double_menu(P_BANK_DATABASE_T p_bank_database)
{
    if (p_bank_database->user_number == 0)
    {
        MOVERIGHT(28);
        printf("数据库中没有一个用户\n");
        return 1;
    }
    bool login_user = false;
    int xianzai = 0; //判断现在登陆的用户是谁
    login_user = login(p_bank_database, &xianzai);
    if (login_user == true)
    {
        progress_bar();
        int chi = 1;
        do
        {
            int choose1 = 0, result = 0;
            user_menu();
            printf("请输入" BLINK ":" DEFAULT_MODE);
            while (1)
            {
                result = scanf("%d", &choose1);
                if (result != 1)
                {
                    while ((result = getchar()) != '\n')
                        ; /*清空缓冲区*/
                    MOVERIGHT(28);
                    printf("数据输入错误，请重新输入!\n");
                }
                else
                {
                    break;
                }
            }
            write_data(p_bank_database);
            switch (choose1)
            {
            case 0:
                chi = 0;
                break;
            case 1:
                save_money(p_bank_database, &xianzai);
                break;
            case 2:
                draw_money(p_bank_database, &xianzai);
                break;
            case 3:
                transfer_accounts(p_bank_database, &xianzai);
                break;
            case 4:
                search_money(p_bank_database, &xianzai);
                break;
            case 5:
                change_two_all(p_bank_database, &xianzai);
                break;
            default:
            MOVERIGHT(28);
                printf("没有这个选择\n");
                break;
            }
        } while (chi);
    }
    else
    {

        MOVERIGHT(28);
        printf("登陆失败\n");
    }
}

int save_money(P_BANK_DATABASE_T p_bank_database, int *xincon) //存钱
{

    int money = 0;
    MOVERIGHT(28);
    printf("-------------------存钱--------------------\n");
    MOVERIGHT(28);
    printf("你的余额为：%d\n", (p_bank_database->user[*xincon].money));
    MOVERIGHT(28);
    printf("请输入你要存的金额：");
    scanf("%d", &money);
    p_bank_database->user[*xincon].money += money;
    MOVERIGHT(28);
    printf("当前余额为：%d\n", (p_bank_database->user[*xincon].money));
    sleep(1);
}

int draw_money(P_BANK_DATABASE_T p_bank_database, int *xincon) //取钱
{
    int money = 0;
    int n = 0, i = 0, j = 0;
    MOVERIGHT(28);
    printf("-------------------取钱--------------------\n");
    MOVERIGHT(28);
    printf("你的余额为：%d\n", (p_bank_database->user[*xincon].money));
    MOVERIGHT(28);
    printf("请输入你要取的金额：");
    scanf("%d", &money);
    if (money > p_bank_database->user[*xincon].money)
    {
        MOVERIGHT(28);
        printf("余额不足\n");
    }
    else
    {
        p_bank_database->user[*xincon].money -= money;
        MOVERIGHT(28);
        printf("当前余额为：%d\n", (p_bank_database->user[*xincon].money));
    }
    sleep(1);
}

int transfer_accounts(P_BANK_DATABASE_T p_bank_database, int *xincon) //转账
{
    char transfer_name[1024] = {0}; //转账账号输入
    int money = 0;                  //转账金额输入
    int result1 = 0, result2 = 0, result3 = 0, result4 = 0;
    int flag = 0;
    MOVERIGHT(28);
    printf("-------------------转账--------------------\n");
    MOVERIGHT(28);
    printf("请输入转账用户名/电话号码:");
    scanf("%s", transfer_name);
    for (int k = 0; k < p_bank_database->user_number; k++)
    {
        result1 = strcmp(transfer_name, (p_bank_database->user[k].name));
        result3 = strcmp(transfer_name, (p_bank_database->user[k].phone));
        result4 = strcmp(transfer_name, (p_bank_database->user[*xincon].phone));
        result2 = strcmp(transfer_name, (p_bank_database->user[*xincon].name));
        if ((result1 == 0 || result3 == 0) && result2 != 0)
        {
            flag = 1; // /判断是否找到用户
            MOVERIGHT(28);
            printf("转账用户名：%s\n", (p_bank_database->user[k].name));
            MOVERIGHT(28);
            printf("请输入转账金额：");
            scanf("%d", &money);
            if (money > p_bank_database->user[*xincon].money)
            {
                MOVERIGHT(28);
                printf("余额不足\n");
                MOVERIGHT(28);
                printf("转账失败！\n");
            }
            else
            {
                user_log_money(p_bank_database,*xincon,k,money);
                MOVERIGHT(28);
                printf("正在转账-----\n");
                p_bank_database->user[k].money += money;
                p_bank_database->user[*xincon].money -= money;
                MOVERIGHT(28);
                printf("转账成功！\n");
                MOVERIGHT(28);
                printf("当前余额为：%d\n", (p_bank_database->user[*xincon].money));
                break;
            }
        }
        else if (result2 == 0 && k + 1 == p_bank_database->user_number)
        {
            MOVERIGHT(28);
            printf("不能给自己账号转账！，请重新输入\n");
        }
        else if (flag == 0 && k + 1 == p_bank_database->user_number)
        {
            MOVERIGHT(28);
            printf("没有找到！\n");
        }
    }
    sleep(1);
}

int search_money(P_BANK_DATABASE_T p_bank_database, int *xincon) //查看钱
{
    MOVERIGHT(28);
    printf("-------------------查询--------------------\n");
    printf("用户名:%s\n电话号码:%s\n银行卡号:%s\n", (p_bank_database->user[*xincon].name), (p_bank_database->user[*xincon].phone), (p_bank_database->user[*xincon].bank_card));
    printf("你的余额为：%d\n", (p_bank_database->user[*xincon].money));
    int count = 0;
    printf("返回:0\n");
    printf("请输入" BLINK ":" DEFAULT_MODE );
    scanf("%d", &count);
    if (count == 0)
    {
    }
}

int data_log(P_BANK_DATABASE_T p_bank_database)//日志
{
    struct tm *tmp_ptr;
    time_t tmpcal_ptr;
    time(&tmpcal_ptr);
    tmp_ptr = gmtime(&tmpcal_ptr);
    tmp_ptr = localtime(&tmpcal_ptr);
    FILE *fp = fopen("log.txt", "a+");
    if (!fp)
        return -1;
    fprintf (fp,"日期 :%d.%d.%d 登陆系统时间：", (1900+tmp_ptr->tm_year), (1+tmp_ptr->tm_mon), tmp_ptr->tm_mday);
    fprintf(fp,"%d:%d:%d\n", tmp_ptr->tm_hour, tmp_ptr->tm_min, tmp_ptr->tm_sec);
    fprintf(fp, "系统用户人数：%d\n", p_bank_database->user_number);
    fclose(fp);
}

int user_log(P_BANK_DATABASE_T p_bank_database)
{
    FILE *fp = fopen("log.txt", "a+");
    if (!fp)
        return -1;
    struct tm *tmp_ptr;
    time_t tmpcal_ptr;
    tmp_ptr = gmtime(&tmpcal_ptr);
    tmp_ptr = localtime(&tmpcal_ptr);
    fprintf (fp,"开户日期 :%d.%d.%d 开户时间： ", (1900+tmp_ptr->tm_year), (1+tmp_ptr->tm_mon), tmp_ptr->tm_mday);
    fprintf(fp,"%d:%d:%d\n", tmp_ptr->tm_hour, tmp_ptr->tm_min, tmp_ptr->tm_sec);
    int i=p_bank_database->user_number-1;
    fprintf(fp,"增加用户：\n");
    fprintf(fp, "用户名:%s电话号码:%s密码:%s\n银行卡:%s余额:%d\n", p_bank_database->user[i].name, p_bank_database->user[i].phone, p_bank_database->user[i].password, p_bank_database->user[i].bank_card, p_bank_database->user[i].money);
    fclose(fp);
}

int user_log_del(P_BANK_DATABASE_T p_bank_database,int i)
{
    FILE *fp = fopen("log.txt", "a+");
    if (!fp)
        return -1;
    struct tm *tmp_ptr;
    time_t tmpcal_ptr;
    tmp_ptr = gmtime(&tmpcal_ptr);
    tmp_ptr = localtime(&tmpcal_ptr);
    fprintf (fp,"销户日期 :%d.%d.%d 销户时间： ", (1900+tmp_ptr->tm_year), (1+tmp_ptr->tm_mon), tmp_ptr->tm_mday);
    fprintf(fp,"%d:%d:%d\n", tmp_ptr->tm_hour, tmp_ptr->tm_min, tmp_ptr->tm_sec);
    fprintf(fp,"注销用户：\n");
    fprintf(fp, "用户名:%s电话号码:%s密码:%s\n银行卡:%s余额:%d\n", p_bank_database->user[i].name, p_bank_database->user[i].phone, p_bank_database->user[i].password, p_bank_database->user[i].bank_card, p_bank_database->user[i].money);
    fclose(fp);
}

int user_log_money(P_BANK_DATABASE_T p_bank_database,int i,int j,int money)
{
    FILE *fp = fopen("log.txt", "a+");
    if (!fp)
        return -1;
    struct tm *tmp_ptr;
    time_t tmpcal_ptr;
    tmp_ptr = gmtime(&tmpcal_ptr);
    tmp_ptr = localtime(&tmpcal_ptr);
    fprintf (fp,"转账日期 :%d.%d.%d 转账时间： ", (1900+tmp_ptr->tm_year), (1+tmp_ptr->tm_mon), tmp_ptr->tm_mday);
    fprintf(fp,"%d:%d:%d\n", tmp_ptr->tm_hour, tmp_ptr->tm_min, tmp_ptr->tm_sec);
    fprintf(fp,"客户转账记录：\n");
    fprintf(fp, "用户名:%s银行卡:%s", p_bank_database->user[i].name, p_bank_database->user[i].bank_card);
    fprintf(fp, "------>向用户名:%s银行卡:%s", p_bank_database->user[j].name, p_bank_database->user[j].bank_card);
    fprintf(fp,"转账了%d\n",money);
    fclose(fp);
}

int data_log1(P_BANK_DATABASE_T p_bank_database)//日志
{
    struct tm *tmp_ptr;
    time_t tmpcal_ptr;
    time(&tmpcal_ptr);
    tmp_ptr = gmtime(&tmpcal_ptr);
    tmp_ptr = localtime(&tmpcal_ptr);
    FILE *fp = fopen("log.txt", "a+");
    if (!fp)
        return -1;
    fprintf (fp,"日期 :%d.%d.%d 离开系统时间：", (1900+tmp_ptr->tm_year), (1+tmp_ptr->tm_mon), tmp_ptr->tm_mday);
    fprintf(fp,"%d:%d:%d\n", tmp_ptr->tm_hour, tmp_ptr->tm_min, tmp_ptr->tm_sec);
    fprintf(fp, "系统用户人数：%d\n", p_bank_database->user_number);
    fclose(fp);
}
