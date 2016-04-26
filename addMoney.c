//
//  addMoney.c
//  5thlab
//
//  Created by Admin on 28.03.16.
//  Copyright © 2016 Admin. All rights reserved.
//

#include <stdio.h>
#include "cli.h"
//int callback(void *data, int argc, char **argv, char **azColName){
//    return 0;
//}

BOOL startAddMoney(){
    printf("Enter account's id:\t");
    int id;
    scanf("%d", &id);
    double sum;
    printf("Enter adding sum:\t");
    scanf("%lf", &sum);
    while ( sum <= 0 ){
        printf("Please, reenter adding sum (it should be more, than 0): ");
        scanf("%lf", &sum);
    }
    return addMoney(id, sum);
}
BOOL addMoney(int accountId, double addingSum){
    BOOL success = FALSE;
    char sql[200];
    char str[200] = "update bank_accounts_tbl set balance = balance + %.2lf where id = %d ;";
    char firstStr[200] = "select clientId from bank_accounts_tbl where id = %d;";
    //sprintf(sql, str, addingSum, accountId);
    sprintf(sql, firstStr, accountId);
    char *zErrMsg;
    sqlite3_stmt *res;
    int rc = -1;
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    int step = sqlite3_step(res);
    if ( step == SQLITE_ROW && sqlite3_column_int(res, 0) != NULL){
        sprintf(sql, str, addingSum, accountId);
        rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
        if ( rc == SQLITE_OK){
            success = TRUE;
            printf("Success adding sum %.2lf to account #%d\n", addingSum, accountId);
        }
        else{
            printf("ERROR: %s\n", sqlite3_errmsg(db));
        }
    }
    else{
        printf("Account with id %d not found\n", accountId);
    }
    return success;
}
