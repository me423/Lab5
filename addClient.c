//
//  addClient.c
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

char* getPhoto(char* photo, int *size)
{
    FILE *fp = fopen(photo, "rb");
    
    if (fp == NULL) {
        
        fprintf(stderr, "Cannot open image file\n");
        printf("Photo will be NULL\n");
        return NULL;
    }
    
    fseek(fp, 0, SEEK_END);
    
    if (ferror(fp)) {
        
        fprintf(stderr, "fseek() failed\n");
        int r = fclose(fp);
        
        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");
        }
        printf("Photo will be NULL\n");
        return NULL;
        
    }
    
    int flen = ftell(fp);
    
    if (flen == -1) {
        
        perror("error occurred");
        int r = fclose(fp);
        
        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");
        }
        printf("Photo will be NULL\n");
        return NULL;
    }
    
    fseek(fp, 0, SEEK_SET);
    
    if (ferror(fp)) {
        
        fprintf(stderr, "fseek() failed\n");
        int r = fclose(fp);
        
        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");
        }
        printf("Photo will be NULL\n");
        
        return NULL;
        
    }
    
    char data[flen+1];
    
    *size = fread(data, 1, flen, fp);
    if (ferror(fp)) {
        
        fprintf(stderr, "fread() failed\n");
        int r = fclose(fp);
        
        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");
        }
        printf("Photo will be NULL\n");
        return NULL;
    }
    
    int r = fclose(fp);
    
    if (r == EOF) {
        fprintf(stderr, "Cannot close file handler\n");
    }
    
    return data;
}


BOOL startAddClient()
{
    
    char firstname[15], lastname[15], passportNumber[15], dateOfBirthday[15], photo[100];
    
    printf ("\n=======ADD A NEW CLIENT=======\n");
    
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
    
    printf ("Enter passport number: ");
    scanf ("%s", passportNumber);
    if (strcmp(passportNumber, "0") == 0)
    {
        printf ("Cancel.");
        return 0;
    }
    
    printf ("Enter date of birthday: ");
    scanf ("%s", dateOfBirthday);
    if (strcmp(dateOfBirthday, "0") == 0)
    {
        printf ("Cancel.");
        return 0;
    }
    
    printf ("Enter name of photo-file: ");
    scanf ("%s", photo);
    if (strcmp(photo, "0") == 0)
    {
        printf ("Cancel.");
        return 0;
    }
    
    
    if (addClient(firstname, lastname, passportNumber, dateOfBirthday, photo) == 1)
    {
        printf("Success adding!\n");
        return 1;
    }
    else{
        printf("Invalid adding!\n");
        return 0;
    }
    
}

BOOL addClient(char* firstname, char* lastname, char* passportNumber, char* dateOfBirthday, char* photo)
{
    sqlite3_stmt *pStmt;
    
    sql = "INSERT INTO BANK_CLIENTS_TBL(firstname, lastname, passportNumber, dateOfBirthday, photo) VALUES(";
    char *str = malloc (sizeof(char) * 300);
    
    sprintf(str, "%s'%s', '%s', '%s', '%s', ?);", sql, firstname, lastname, passportNumber, dateOfBirthday);
    
    int size = 0;
    
    char* data = NULL;
    
    data = getPhoto((char*)photo, &size);
   
    if (data == NULL)
    {
        sprintf(str, "%s'%s', '%s', '%s', '%s', 'NULL');", sql, firstname, lastname, passportNumber, dateOfBirthday);        
    }
    
    //printf(str);
    
    int rc = -1;
   
    rc = sqlite3_prepare(db, str, -1, &pStmt, 0);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot prepare statement: %s\n", sqlite3_errmsg(db));
        
        return 0;
    }
    
    sqlite3_bind_blob(pStmt, 1, data, size, SQLITE_STATIC);
    
    rc = sqlite3_step(pStmt);
    
    if (rc != SQLITE_DONE) {
        
        printf("Execution failed: %s. Maybe you want to add ununiqe values.\n", sqlite3_errmsg(db));
        return 0;
    }
    
    sqlite3_finalize(pStmt);
    
    free(str);
  
    return 1;
}


/*
int main()
{
    int rc = 0;
    rc = sqlite3_open("/Users/ivanMatyash/Desktop/lab5/lab5/BANK_DB.db", &db);
    
    startAddClient();
    
    
    sqlite3_close(db);
    return 0;
}
*/
