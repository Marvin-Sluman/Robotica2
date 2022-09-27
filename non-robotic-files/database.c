#include <mariadb/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char option;
char input[255];
char addInput[15][50];
char query[300];
char driverRef[255];
int number;
char code[3];
char forename[255];
char surname[255];
char date[20];
char nationality[255];
char url[255];

char columns[15][50];

MYSQL *con;
MYSQL_RES *result;
MYSQL_ROW row;

void finish_with_error(MYSQL *con){
  printf("%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

void show_tables(){
  if(mysql_query(con, "SHOW TABLES")){
    finish_with_error(con);
  }
  result = mysql_store_result(con);
  if(result == NULL){
    finish_with_error(con);
  }

  while((row = mysql_fetch_row(result))){
      printf("%s ", row[0]); 
    printf("\n");
  }
  printf("\n");
  mysql_free_result(result);
}

void show_columns(){
  sprintf(query, "SHOW COLUMNS FROM %s", input);
  if(mysql_query(con, query)){
  }
  result = mysql_store_result(con);
  if(result == NULL){
    finish_with_error(con);
  }

  for(int i = 0; (row = mysql_fetch_row(result)); i++){
      strcpy(columns[i], row[0]);
      printf("%s ", row[0]); //Not interested in columns information except the column name
    printf("\n");
  }
  printf("\n");
  mysql_free_result(result);
} 

char get_option(){
  printf("What do you want to do? Add (A), Modify (M), Delete (D) or View (V)? : ");
  scanf(" %c", &option);
  return option;
}

void add_data(){
  sprintf(query, "INSERT INTO %s (%s", input, columns[0]);
  for(int i = 1; i < 9; i++){
    printf("%s  ", columns[i]); //Ignore i=0, because it's auto incrementing ID
    strcat(query, ", ");
    strcat(query, columns[i]);
    scanf("%s", addInput[i-1]);
  }
  strcat(query, ") VALUES (NULL");
  for(int i = 1; i < 9; i++){
      strcat(query, ", '");
      strcat(query, addInput[i-1]);
      strcat(query, "'");
  }
  strcat(query, ")");

  printf("\n%s\n", query);
  if(mysql_query(con, query)){
    finish_with_error(con);
  }

  /*
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
  */
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

  show_tables();
  
  printf("Please select the table you want to use: ");
  scanf("%s", input);
  printf("\n");

  show_columns();

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
