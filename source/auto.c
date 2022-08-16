#include "../include/function.h"
#include "../include/get_bankcard.h"

int auto_all(P_BANK_DATABASE_T p_bank_database)
{
    int num = 0;
    char save_name[1024][1024] = {0};

    printf("请输入你要生成的名字数量：");
    scanf("%d", &num);

    random_name(save_name, num);
    random_password(p_bank_database, num);
    random_phone(p_bank_database, num);
    auto_getbank_card(p_bank_database, num);

    for (int i = 0; i < num; i++)
    {
        strcpy(p_bank_database->user[i].name, save_name[i]);
        p_bank_database->user_number++;
    }

    return 1;
}

void random_name(char save_name[][1024], int num)
{
    char xing[50][8] = {"赵", "钱", "孙", "李", "周", "吴", "郑", "王", "冯", "陈", "褚", "卫", "蒋",
                        "沈", "韩", "杨", "朱", "秦", "尤", "许", "何", "吕", "施", "张", "孔", "曹",
                        "严", "华", "金", "魏", "陶", "姜", "戚", "谢", "邹", "喻", "柏", "水", "窦", "章", "云", "苏", "潘", "葛"};
    char ming[200][9] = {"天", "地", "玄", "黄", "宇", "宙", "洪", "荒", "人", "之", "初", "性", "本",
                         "善", "性", "相", "近", "习", "相", "远", "勤", "有", "功", "戏", "无", "益", "戒", "哉",
                         "宜", "勉", "力", "炎", "宋", "兴", "受", "周", "禅", "十", "八", "传", "南", "北", "混", "颜", "雅",
                         "帝", "幼", "亚", "烟", "言", "妖", "姚", "耀", "瑶", "夜", "业", "页", "亦", "偶", "破", "魄", "拼",
                         "聘", "平", "凭", "帕", "牌", "派", "盘", "攀", "萨", "塞", "赛", "莎",
                         "输", "树", "书", "术", "舒", "淑", "水", "刷", "硕", "烁", "妁", "顺", "瞬", "帅", "霜", "爽", "商",
                         "尚", "裳", "丹", "单", "淡", "担", "呆", "黛", "党", "荡",
                         "凡", "房", "防", "芳", "风", "粉", "芬", "峰", "锋", "枫", "可", "怜", "三", "上", "优", "雅", "夜"};

    char ch[1024] = {0};
    char ch1[1024] = {0};
    char ch2[1024] = {0};

    char *p_ch[3] = {ch, ch1, ch2}; // p_ch[0],p_ch[1],p_ch[2]
    char(*p_save_name)[1024] = save_name;
    srand((unsigned int)time(NULL));
    for (int i = 0; i < num; i++)
    {
        int number = 0;

        number = RAND(0, 42);
        strcpy(p_ch[0], xing[number]);

        number = RAND(0, 45);
        strcpy(ch1, ming[number]);
        strcat(p_ch[0], p_ch[1]);

        number = RAND(0, 45);
        strcpy(ch2, ming[number]);
        strcat(p_ch[0], p_ch[2]);

        strcpy((*(p_save_name + i)), p_ch[0]);
        ch[0] = 0;
    }
}

void random_phone(P_BANK_DATABASE_T p_bank_database, int num)
{
    char save_phone[1024][12] = {0};
    srand((unsigned int)time(NULL));
    int i = 0, j = 0;

    for (i = 0; i < num; i++)
    {
        save_phone[i][0] = '1';
        save_phone[i][1] = '8';
        save_phone[i][2] = '9';
        for (j = 3; j < 12; j++)
        {
            save_phone[i][j] = RAND(0, 9) + '0';
        }
        save_phone[j][i] = '\0';
        strcpy(p_bank_database->user[i].phone, save_phone[i]);
    }
}

void random_password(P_BANK_DATABASE_T p_bank_database, int num)
{
    int i = 0, j = 0;
    char save_password[1024][7] = {0};
    srand((unsigned int)time(NULL));
    for (i = 0; i < num; i++)
    {
        for (j = 0; j < 6; j++)
        {
            save_password[i][j] = RAND(0, 9) + '0';
        }
        save_password[i][j] = '\0';

        strcpy(p_bank_database->user[i].password, save_password[i]);
    }
}

void auto_getbank_card(P_BANK_DATABASE_T p_bank_database, int num)
{
    char bank_card[1024][20] = {0};
    for (int k = 0; k < num; k++)
    {

        char buf[1024] = {0};
        int i;
        srand((unsigned)time(NULL));
        for (i = 0; i < 10; i++)
        {
            buf[i] = RAND(0, 9) + '0';
        }
        buf[i] = '\0';
        char number[1024] = {0};
        for (i = 1; i < strlen(buf); i += 2) //奇数部分处理
        {
            number[i] = (buf[i] - '0') * 2;
        }
        for (i = 0; i < strlen(buf); i += 2) //偶数部分处理
        {
            number[i] = buf[i] - '0';
        }
        int Luhn = 0;
        for (i = 0; i < strlen(buf); i++)
        {
            if (i % 2 != 0) //奇数
            {
                if (number[i] >= 10)
                {
                    Luhn = Luhn + (number[i] % 10) + (number[i] / 10);
                }
                else
                {
                    Luhn = Luhn + number[i];
                }
            }
            else
            { //偶数
                Luhn = Luhn + number[i];
            }
        }
        char parity_bit = '\0'; //存储校验位
        if (Luhn % 10 == 0)
        {
            parity_bit = '0';
        }
        else
        {
            parity_bit = (((Luhn / 10) + 1) * 10 - Luhn) + '0';
        }
        char BIN[7] = {0};
        strncpy(BIN, CCB, 6);
        strcat(bank_card[k], BIN);
        strcat(bank_card[k], buf);
        strncat(bank_card[k], &parity_bit, 1);
        // printf("生成的银行卡号为:%s\n", (p_bank_database->user[(p_bank_database->user_number)].bank_card));
        strcpy(p_bank_database->user[k].bank_card, bank_card[k]);
    }
}