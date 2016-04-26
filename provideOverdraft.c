#include <stdio.h>
#include "cli.h"

char* sql;
char* zErrMsg;

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    for(i=0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}


BOOL startProvideOverdraft()
{
    int idAccount;
    double sum;
    
    printf ("\n=======PROVIDE OVERDRAFT=======\n");
    
    printf ("Enter 0 for cancel\n");
    do
    {
        printf ("Enter id of account for provide overdraft: ");
        scanf ("%d", &idAccount);
        if (idAccount == 0)
        {
            printf ("Cancel.");
            return 0;
        }
    }while (idAccount < 0);
    
    do
    {
        printf ("Enter the sum of overdraft (1 - 200): ");
        scanf ("%lf", &sum);
        if (sum == 0)
        {
            printf ("Cancel.");
            return 0;
        }
    }while (sum < 1 || sum > 200);
    
    if (provideOverdraft(idAccount, sum) == 1)
    {
        printf("Success provide overdraft to account %d.\n", idAccount);
        return 1;
    }
    else{
        printf("Invalid provide overdraft!\n");
        return 0;
    }
    
}

BOOL provideOverdraft(int idAccount, double sum)
{
    
    char *err_msg = 0;
    sqlite3_stmt *res;
    
    
    int rc = -1;
    
    char *sql = "SELECT type, balance FROM BANK_ACCOUNTS_TBL WHERE id = ?";
    
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    
    if (rc == SQLITE_OK) {
        sqlite3_bind_int(res, 1, idAccount);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    
    int step = sqlite3_step(res);
    double newBalance = 0;
    
    if (step == SQLITE_ROW) {
        if (strcmp(sqlite3_column_text(res, 0), "saving") == 0)
        {
            printf("In this account is OFF overdraft!\n");
            return 0;
        }
        newBalance = sqlite3_column_double(res, 1);
    }
    else{
        printf("An account NOT FOUND.\n");
        return 0;
    }
    newBalance -= sum;
    
    sql = "UPDATE BANK_ACCOUNTS_TBL SET balance = ";
    char str[300];
    sprintf(str, "%s'%lf' WHERE id = %d;", sql, newBalance, idAccount);
    //printf(str);
    
    
    rc = -1;
    rc = sqlite3_exec(db, str, callback, 0, &zErrMsg);
    
    if (rc != SQLITE_OK)
    {
        printf ("SQL ERROR: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 0;
        
    }
    else
    {
        return 1;
    }
    
}
/*
int main()
{
    int rc = 0;
    rc = sqlite3_open("/Users/ivanMatyash/Desktop/lab5/lab5/BANK_DB.db", &db);
    
    startProvideOverdraft();
    
    
    sqlite3_close(db);
    return 0;
}
*/
