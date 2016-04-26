//
//  deleteAccount.c
//  lab5
//
//  Created by Иван Матяш on 3/27/16.
//  Copyright (c) 2016 Иван Матяш. All rights reserved.
//

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


BOOL startDeleteAccount()
{
    int idAccount;
    
    printf ("\n=======DELETE ACCOUNT=======\n");
    
    printf ("Enter 0 for cancel\n");
    do
    {
    printf ("Enter id of account for deleting: ");
    scanf ("%d", &idAccount);
    if (idAccount == 0)
    {
        printf ("Cancel.");
        return 0;
    }
    }while (idAccount < 0);
    
    if (deleteAccount(idAccount) == 1)
    {
        printf("This account with number %d was delete from database!\n", idAccount);
        return 1;
    }
    else{
        printf("Invalid deleting!\n");
        return 0;
    }
    
}

BOOL deleteAccount(int idAccount)
{
    
    char *err_msg = 0;
    sqlite3_stmt *res;
    
    
    int rc = -1;
    
    char *sql = "SELECT balance, type FROM BANK_ACCOUNTS_TBL WHERE id = ?";
    
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    
    if (rc == SQLITE_OK) {
        sqlite3_bind_int(res, 1, idAccount);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    
    int step = sqlite3_step(res);
    
    if (step == SQLITE_ROW) {
        printf("Account: balance = %.2lf, type = %s.\n", sqlite3_column_double(res, 0), sqlite3_column_text(res, 1));
    }
    else{
        printf("A account NOT FIND.\n");
        return 0;
    }
    
    sql = "DELETE FROM BANK_ACCOUNTS_TBL WHERE id = ";
    char *str = malloc (sizeof(char) * 300);
    
    sprintf(str, "%s'%d';", sql, idAccount);
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
    free(str);
}
/*
int main()
{
    int rc = 0;
    rc = sqlite3_open("/Users/ivanMatyash/Desktop/lab5/lab5/BANK_DB.db", &db);
    
    startDeleteAccount();
    
    
    sqlite3_close(db);
    return 0;
}
*/
