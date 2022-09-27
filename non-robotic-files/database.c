#include <mariadb/mysql.h>
#include <stdio.h>
#include <stdlib.h>

char option;
char query[300];
char driverRef[255];
int number;
char code[3];
char forename[255];
char surname[255];
char date[20];
char nationality[255];
char url[255];

MYSQL *con;
MYSQL_RES *result;
MYSQL_ROW row;

char get_option(){
  printf("What do you want to do? Add (A), Modify (M), Delete (D) or View (V)? : ");
  scanf("%c", &option);
  return option;
}

void finish_with_error(MYSQL *con){
  printf("%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

void add_data(){
  printf("driverRef ");
  scanf("%s", driverRef);
  printf("number ");
  scanf("%d", &number);
  printf("code ");
  scanf("%s", code);
  printf("forename ");
  scanf("%s", forename);
  printf("surname ");
  scanf("%s", surname);
  printf("date ");
  scanf("%s", date);
  printf("nationality ");
  scanf("%s", nationality);
  printf("url ");
  scanf("%s", url);
  sprintf(query, "INSERT INTO drivers VALUES (NULL, '%s', '%d', '%s', '%s', '%s', '%s', '%s', '%s')", driverRef, number, code, forename, surname, date, nationality, url);
  if(mysql_query(con, query)){
    finish_with_error(con);
  }
}

void delete_data(){

}

void modify_data(){

}

void view_data(){
  printf("surname ");
  scanf("%s", surname);
  sprintf(query, "SELECT * FROM drivers WHERE surname = '%s'", surname);
  if (mysql_query(con, query)){
    finish_with_error(con);
  }
  result = mysql_store_result(con);
  if(result == NULL){
    finish_with_error(con);
  }

  int num_fields = mysql_num_fields(result);

  while((row = mysql_fetch_row(result))){
    for(int i = 0; i < num_fields; i++){
      printf("%s ", row[i] ? row[i] : "NULL");
    }
    printf("\n");
  }
  mysql_free_result(result);
}

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

  mysql_close(con);
  exit(0);
}
