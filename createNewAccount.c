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


BOOL startCreateNewAccount()
{
    double balance;
    int clientId;
    char type[15];
    
    printf ("\n=======CREATING A NEW ACCOUNT=======\n");
    
    printf ("Enter 0 for cancel\n");
    printf ("Enter id of client: ");
    scanf ("%d", &clientId);
    if (clientId == 0)
    {
        printf ("Cancel.");
        return 0;
    }
    
    printf ("Enter balance: ");
    scanf ("%lf", &balance);
    if (balance == 0.0)
    {
        printf ("Cancel.");
        return 0;
    }
    
    do
    {
    printf ("Enter type of account (SAVING or ACTUAL): ");
    scanf ("%s", type);
    if (strcmp(type, "0") == 0)
    {
        printf ("Cancel.");
        return 0;
    }
    } while (strcmp(type, "saving") != 0 && strcmp(type, "actual") != 0);
    
    
       
    if (createNewAccount(balance, clientId, type) == 1)
    {
        printf("Success creating of new account!\n");
        return 1;
    }
    else{
        printf("Invalid creating of new account!\n");
        return 0;
    }
    
}

BOOL createNewAccount(double balance, int clientId, char* type)
{
    
    char *err_msg = 0;
    sqlite3_stmt *res;
    

    int rc = -1;
    
    char *sql = "SELECT firstname, lastname FROM BANK_CLIENTS_TBL WHERE id = ?";
    
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    
    if (rc == SQLITE_OK) {        
        sqlite3_bind_int(res, 1, clientId);
    } else {        
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    
    int step = sqlite3_step(res);
    
    if (step == SQLITE_ROW) {        
        printf("A client: %s %s.\n", sqlite3_column_text(res, 0), sqlite3_column_text(res, 1));
    }
    else{
        printf("A client NOT FIND.\n");
        return 0;
    }
    
    
    char *sql1 =  "INSERT INTO BANK_ACCOUNTS_TBL(clientID, balance, type) VALUES(";
    
    char *str = malloc (sizeof(char) * 300);
    
    sprintf(str, "%s '%d', %lf, '%s');", sql1, clientId, balance, type);
    //printf(str);
    
   rc = -1;
    rc = sqlite3_exec(db, str, callback, 0, &zErrMsg);
    
  
    
    if (rc != SQLITE_OK)
    {
        printf ("SQL ERROR: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        free(str);
        return 0;
        
    }
    else
    {
        printf ("\nNew account is successfuly created!\n");
        free(str);
        return 1;
    }
   
    
}
