SRC =  authorization.c balanceCheck.c clientAccountsShow.c mainprg.c addClient.c createNewAccount.c deleteAccount.c deleteClient.c deleteUser.c registration.c addMoney.c deliverMoney.c getMoney.c onOverdraft.c provideOverdraft.c
main: $(SRC)
	gcc -w $(SRC) -l sqlite3 -o ReleaseVersion2