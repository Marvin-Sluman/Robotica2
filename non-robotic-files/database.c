#include <mariadb/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

char userInput[255];
//Creating MYSQL objects needed for SQL queries 
MYSQL *con;
MYSQL_RES *result;
MYSQL_ROW row;

int main(int argc, char **argv)
{
  con = mysql_init(NULL);
  if(con == NULL){
    printf("%s\n", mysql_error(con));
  }

  if(mysql_real_connect(con, "localhost", "pipo", "theclown", "f1", 0, NULL, 0) == NULL){
    printf("%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
  } 
  while(1){
    start_program();
    switch (get_option()){
      case 'A':
        add_data();
        break;
      case 'M':
        modify_data();
        break;
      case 'D':
        delete_data();
        break;
      case 'V':
        view_data();
        break; 
    }

    printf("\n\nDo you want to continue?: Yes(Y)/No(N) ");
    scanf(" %c", &userInput);
    if(strcmp(userInput, "N") == 1){
      mysql_close(con);
      exit(0);
    }

    printf("\n\nRESTARTING..........................\n\n\n");
  }
}
