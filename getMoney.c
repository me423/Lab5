#include <stdio.h>
#include "cli.h"
//int callback(void *data, int argc, char **argv, char **azColName){
//    return 0;
//}


BOOL getMoney(int accountNumber, double sum){
    BOOL success = FALSE;
    char sql[200] = "SELECT balance FROM BANK_ACCOUNTS_TBL WHERE id = ?";
    char str[200] = "update bank_accounts_tbl set balance = balance - %lf where id = %d;";
    sqlite3_stmt *res;
    int rc = -1;
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    
    if (rc == SQLITE_OK) {
        sqlite3_bind_int(res, 1, accountNumber);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        return success;
    }
    
    int step = sqlite3_step(res);
    
    if (step == SQLITE_ROW) {
        if (sum > sqlite3_column_double(res, 0)){
            printf("FAILED: Getting sum %.2lf more than account balance %.2lf\n", sum, sqlite3_column_double(res, 0));
        }
        else{
            sprintf(sql, str, sum, accountNumber, sum);
            char *zErrMsg;
            rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
            if ( rc == SQLITE_OK){
                printf("Success getting money\n");
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

BOOL startGetMoney(){
    printf("Enter account's id:\t");
    int id;
    scanf("%d", &id);
    double sum;
    printf("Enter sum you want to get:\t");
    scanf("%lf", &sum);
    while ( sum <= 0 ){
        printf("Please, reenter adding sum (it should be more, than 0): ");
        scanf("%lf", &sum);
    }
    return getMoney(id, sum);
    
}
