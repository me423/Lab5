#include "sysFunctions.h"
#include "cli.h"
#include "sqlite3.h"
#include <stdio.h>

BOOL checkBalance(int accountNumber, double *balance)
{
    char *sql = "SELECT balance FROM BANK_ACCOUNTS_TBL WHERE id = ?";
    int ans;
    sqlite3_stmt * res;
    
    ans = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (ans != SQLITE_OK)
    {
        sqlite3_finalize(res);
        return FALSE;
    }
    
    sqlite3_bind_int(res, 1, accountNumber);
    
    
    if (sqlite3_step(res) == SQLITE_ROW)
        *balance = sqlite3_column_double(res, 0);
    else
        return FALSE;
    sqlite3_finalize(res);
    return TRUE;
}

BOOL startCheckBalance()
{
    int accountNumber;
    BOOL result;
    double balance = 0;
    printf("Enter account number: ");
    scanf("%d", &accountNumber);
    getchar();
    result = checkBalance(accountNumber, &balance);
    if (result == FALSE)
        printf("Ooops! Some error. Check your account number.\n");
    else
        printf("Balance on the account %d is %.2lf\n", accountNumber, balance);
    return result;
}