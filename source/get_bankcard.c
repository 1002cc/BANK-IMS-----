#include "../include/get_bankcard.h"
#include "../include/function.h"

extern void getbank_card(P_BANK_DATABASE_T p_bank_database)
{
    char buf[10245] = {0};
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
    strcat((p_bank_database->user[(p_bank_database->user_number)].bank_card), BIN);
    strcat((p_bank_database->user[(p_bank_database->user_number)].bank_card), buf);
    strncat((p_bank_database->user[(p_bank_database->user_number)].bank_card), &parity_bit, 1);
    printf("生成的银行卡号为:%s\n", (p_bank_database->user[(p_bank_database->user_number)].bank_card));
}
