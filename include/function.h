#ifndef __FUNCTION__H
#define __FUNCTION__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <time.h>
#include "get_bankcard.h"
#include "show.h"
#include "../include/auto.h"

#define N 3 //登陆次数
#define admin_name "chen"
#define admin_password "123456"

#define RAND(min, max) (rand() % ((int)(max + 1) - (int)(min)) + (int)(min))
typedef struct bank_user_info
{
    char name[1024];
    char password[1024];
    char phone[1024];
    char bank_card[1024];
    char money[1024];
} BANK_INFO_T, *P_BANK_INFO_T, **PP_BANK_INFO_T;

typedef struct bank_database
{
    BANK_INFO_T user[1024];
    int user_number;
} BANK_DATABASE_T, *P_BANK_DATABASE_T, **PP_BANK_DATABASE_T;

extern void getbank_card(P_BANK_DATABASE_T p_bank_database);

extern bool system_login();                                         //管理员登陆
extern int open_an_account(P_BANK_DATABASE_T p_bank_database);      //开户;              //开户
extern int account_cancellation(P_BANK_DATABASE_T p_bank_database); //销户
extern int search(P_BANK_DATABASE_T p_bank_database);               //查询用户

extern void change_password(P_BANK_DATABASE_T p_bank_database, int flang); //修改密码
extern bool login(P_BANK_DATABASE_T p_bank_database, int *xianzai);        //登陆

extern int save_money(P_BANK_DATABASE_T p_bank_database, int *xincon);        //存钱
extern int draw_money(P_BANK_DATABASE_T p_bank_database, int *xincon);        //取钱
extern int transfer_accounts(P_BANK_DATABASE_T p_bank_database, int *xincon); //转账
extern int search_money(P_BANK_DATABASE_T p_bank_database, int *xincon);      //查钱

extern void change_name(P_BANK_DATABASE_T p_bank_database, int flang);          //修改用户名
extern int two_change_password(P_BANK_DATABASE_T p_bank_database, int *xincon); //修改密码
extern void change_phone(P_BANK_DATABASE_T p_bank_databaseg, int flang);        //修改电话

extern void change_two_all(P_BANK_DATABASE_T p_bank_database, int *xiancon); //客户端修改
extern int change_all(P_BANK_DATABASE_T p_bank_database);                    //修改
extern int double_menu(P_BANK_DATABASE_T p_bank_database);                   //客户端选择

extern int reverse(char *p_left, char *p_right); //数据反转

int auto_all(P_BANK_DATABASE_T p_bank_database);
void random_name(char save_name[][1024], int num);
void random_phone(P_BANK_DATABASE_T p_bank_database, int num);
void random_password(P_BANK_DATABASE_T p_bank_database, int num);

#endif
