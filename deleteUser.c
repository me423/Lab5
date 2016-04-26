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


BOOL startDeleteUser()
{
    
    char login[15];
    
    printf ("\n=======DELETE A USER=======\n");
    
    printf ("Enter 0 for cancel\n");
    printf ("Enter login for deleting: ");
    scanf ("%s", login);
    if (strcmp(login, "0") == 0)
    {
        printf ("Cancel.");
        return 0;
    }

    
    if (deleteUser(login) == 1)
    {
        printf("This user was delete from database!\n");
        return 1;
    }
    else{
        printf("Invalid deleting!\n");
        return 0;
    }
    
}

BOOL deleteUser(char* login)
{
    sql = "DELETE FROM BANK_USERS_TBL WHERE login = ";
    char *str = malloc (sizeof(char) * 300);
    
    sprintf(str, "%s'%s';", sql, login);
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

/*
int main()
{
    int rc = 0;
    rc = sqlite3_open("/Users/ivanMatyash/Desktop/lab5/lab5/BANK_DB.db", &db);
    
    startDeleteUser();
    
    
    sqlite3_close(db);
    return 0;
}
*/
