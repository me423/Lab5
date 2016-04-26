#include "sysFunctions.h"
#include "cli.h"
#include "sqlite3.h"
#include <stdio.h>
#include <string.h>

static int displayClientAccounts(void *NotUsed, int argc, char **argv, char **ColName)
{
    int i;
    for (i = 0; i < argc; i++)
        printf ("\t%s = %s\n", ColName[i], argv[i] ? argv[i] : "NULL");
    printf("\n");
    return 0;
}

BOOL startShowClientsAccount()
{
    char passportNumber[100];
    printf("Enter passport number: ");
    scanf("%s", passportNumber);
    BOOL result = showClientsAccount(passportNumber);
    if (result == FALSE)
        printf("Ooops! Some error. Please, check your passport number\n");
    return result;
}

BOOL showClientsAccount(char *passportNumber)
{
    char *sql = "select BANK_ACCOUNTS_TBL.id,BANK_ACCOUNTS_TBL.balance,BANK_ACCOUNTS_TBL.type from BANK_ACCOUNTS_TBL inner join BANK_CLIENTS_TBL on BANK_ACCOUNTS_TBL.clientId = BANK_CLIENTS_TBL.id WHERE BANK_CLIENTS_TBL.passportNumber = '%s'";
    char trueSql[300];
    sprintf(trueSql, sql, passportNumber);
    char *zErrMsg = 0;
    printf("Client's accounts:\n");
    int ans = sqlite3_exec(db, trueSql, displayClientAccounts, 0, &zErrMsg);
    if (ans != SQLITE_OK)
    {
        sqlite3_free(zErrMsg);
        return FALSE;
    }
    return TRUE;
}