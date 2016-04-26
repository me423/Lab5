//
//  deliverMoney.c
//  5thlab
//
//  Created by Admin on 28.03.16.
//  Copyright © 2016 Admin. All rights reserved.
//

#include <stdio.h>
#include "cli.h"

int callback(void *data, int argc, char **argv, char **azColName){
    return 0;
}


BOOL deliverMoneyFromAcToAc(int srcAcNumber, int dstAcNumber, double sum){
    BOOL success = FALSE;
    char sql[200] = "SELECT balance FROM BANK_ACCOUNTS_TBL WHERE id = ?";
    char str[300] = "update bank_accounts_tbl set balance = case id when %d then balance - %.2lf when %d then balance + %.2lf end where id in (%d, %d);";
    /*
     update bank_accounts_tbl set balance = case id when 5 then balance + 200 when 1 then balance - 200 end  where id in (5,1);
     */
    char last_sql[500];
    sqlite3_stmt *res;
    int rc = -1;
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    
    if (rc == SQLITE_OK) {
        sqlite3_bind_int(res, 1, srcAcNumber);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        return success;
    }
    
    int step = sqlite3_step(res);
    
    if (step == SQLITE_ROW) {
        if (sum > sqlite3_column_double(res, 0)){
            printf("FAILED: Delivering sum %.2lf more than account balance %.2lf\n", sum, sqlite3_column_double(res, 0));
        }
        else{
            sprintf(last_sql, str, srcAcNumber, sum, dstAcNumber, sum, srcAcNumber, dstAcNumber);
            //printf("%s\n", last_sql);
            char *zErrMsg;
            rc = sqlite3_exec(db, last_sql, callback, 0, &zErrMsg);
            if ( rc == SQLITE_OK){
                printf("Success delivering money\n");
                success = TRUE;
            }
            else{
                printf("ERROR: %s\n", sqlite3_errmsg(db));
            }
        }
    }
    else{
        printf("An account not found.\n");
        return 0;
    }
    return success;
    
}

BOOL startDeliverMoney(){
    int srcAcNum, dstAcNum;
    double sum;
    printf("Enter source account id: ");
    scanf("%d", &srcAcNum);
    printf("Enter destination account id: ");
    scanf("%d", &dstAcNum);
    printf("Enter sum: ");
    scanf("%lf", &sum);
    return deliverMoneyFromAcToAc(srcAcNum, dstAcNum, sum);
}