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


BOOL startDeleteClient()
{
    
    char numberPassport[15];
    
    printf ("\n=======DELETE A CLIENT=======\n");
    
    printf ("Enter 0 for cancel\n");
    printf ("Enter number of passport for deleting: ");
    scanf ("%s", numberPassport);
    if (strcmp(numberPassport, "0") == 0)
    {
        printf ("Cancel.");
        return 0;
    }
    
    
    if (deleteClient(numberPassport) == 1)
    {
        printf("This client was delete from database!\n");
        return 1;
    }
    else{
        printf("Invalid deleting!\n");
        return 0;
    }
    
}

BOOL deleteClient(char* numberOfPassport)
{
    sql = "DELETE FROM BANK_CLIENTS_TBL WHERE passportNumber = ";
    char *str = malloc (sizeof(char) * 300);
    
    sprintf(str, "%s'%s';", sql, numberOfPassport);
    //printf(str);
    
    int rc = -1;
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
