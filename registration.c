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


BOOL startRegistration()
{
    
    char firstname[15], lastname[15], login[15], password[15];
    BOOL isAdmin = 0;
    
    printf ("\n=======REGISTRATION A NEW USER=======\n");
    
    printf ("Enter 0 for cancel\n");
    printf ("Enter firstname: ");
    scanf ("%s", firstname);
    if (strcmp(firstname, "0") == 0)
    {
        printf ("Cancel.");
        return 0;
    }
    
    printf ("Enter lastname: ");
    scanf ("%s", lastname);
    if (strcmp(lastname, "0") == 0)
    {
        printf ("Cancel.");
        return 0;
    }
    
    printf ("Enter login: ");
    scanf ("%s", login);
    if (strcmp(login, "0") == 0)
    {
        printf ("Cancel.");
        return 0;
    }
    
    printf ("Enter password: ");
    scanf ("%s", password);
    if (strcmp(password, "0") == 0)
    {
        printf ("Cancel.");
        return 0;
    }
    do
    {
        printf ("Is Admin? (0 No, 1 Yes): ");
        scanf ("%d", &isAdmin);
    } while(isAdmin != 0 && isAdmin != 1);
    
       
    if (registration(firstname, lastname, login, password, isAdmin) == 1)
    {
        printf("Success registration!\n");
        return 1;
    }
    else{
        printf("Invalid registration!\n");
        return 0;
    }
    
}

BOOL registration(char* firstname, char* lastname, char* login, char* password, BOOL isAdmin)
{
    sql = "INSERT INTO BANK_USERS_TBL(firstname, lastname, login, password, isAdmin) VALUES(";
    char *str = malloc (sizeof(char) * 300);
 
    sprintf(str, "%s '%s', '%s', '%s', '%s', %d);", sql, firstname, lastname, login, password, isAdmin);
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
        printf ("\nRecords is successfull add!\n");
        return 1;
    }
    free(str);
}


