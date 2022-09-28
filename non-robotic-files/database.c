#include <mariadb/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char option;
char input[255];
char value[255];
char addInput[15][50];
char query[300];
char currentTable[50];

char columns[15][50];
char currentColumn[50];
int amountColumns;

//Creating MYSQL objects needed for SQL queries 
MYSQL *con;
MYSQL_RES *result;
MYSQL_ROW row;

//Function to run when there's an MYSQL error
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

  printf("These are the tables you can work with: \n");
  while((row = mysql_fetch_row(result))){
      printf("%s ", row[0]); 
    printf("\n");
  }
  printf("\n");
  mysql_free_result(result);
}

void show_columns(){
  sprintf(query, "SHOW COLUMNS FROM %s", currentTable);
  if(mysql_query(con, query)){
  }
  result = mysql_store_result(con);
  if(result == NULL){
    finish_with_error(con);
  }
  printf("These are the columns within the %s table: \n", currentTable);
  amountColumns = 0;
  for(int i = 0; (row = mysql_fetch_row(result)); i++){
    strcpy(columns[i], row[0]);
    printf("%s ", row[0]); //Not interested in columns information except the column name
    printf("\n");
    amountColumns++;
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
  sprintf(query, "INSERT INTO %s (%s", currentTable, columns[0]);
  for(int i = 1; i < amountColumns; i++){
    printf("%s  ", columns[i]); //Ignore i=0, because it's auto incrementing ID
    strcat(query, ", ");
    strcat(query, columns[i]);
    scanf("%s", addInput[i-1]);
  }
  strcat(query, ") VALUES (NULL");
  for(int i = 1; i < amountColumns; i++){
      strcat(query, ", '");
      strcat(query, addInput[i-1]);
      strcat(query, "'");
  }
  strcat(query, ")");

  if(mysql_query(con, query)){
    finish_with_error(con);
  }
  printf("Data has been added succesfully\n");
}

void delete_data(){
  printf("Please give the column you want to delete data from: \n");
  scanf("%s", currentColumn);
  printf("\nPlease give the value you want to delete: \n");
  scanf("%s", value);
  sprintf(query, "SELECT * FROM %s WHERE %s = '%s'", currentTable, currentColumn, value);

  if (mysql_query(con, query)){
    finish_with_error(con);
  }
  result = mysql_store_result(con);
  if(result == NULL){
    finish_with_error(con);
  }

  int num_fields = mysql_num_fields(result);
  printf("\n");
  while((row = mysql_fetch_row(result))){
    for(int i = 0; i < num_fields; i++){
      printf("%s ", row[i] ? row[i] : "NULL");
    }
    printf("\n");
  }
  mysql_free_result(result);
  printf("\nDo you want to delete the above data? (Yes/No)\n");
  scanf("%s", input);
  if(strcmp(input, "Yes") == 0){
    sprintf(query, "DELETE FROM %s WHERE %s = '%s'", currentTable, currentColumn, value);
    if (mysql_query(con, query)){
      finish_with_error(con);
    }
    printf("%s\n", query);
    printf("Entry has been deleted\n");
  }else{
    printf("Aborted, no data altered");
    exit(0);
  }

}

void modify_data(){

}

void view_data(){
  sprintf(query, "SELECT * FROM %s", currentTable);
  printf("Please give the column you want to filter on: \n");
  scanf("%s", currentColumn);
  printf("\nPlease give the value you want to filter on: \n");
  scanf("%s", input);
  sprintf(query, "SELECT * FROM %s WHERE %s = '%s'", currentTable, currentColumn, input);

  if (mysql_query(con, query)){
    finish_with_error(con);
  }
  result = mysql_store_result(con);
  if(result == NULL){
    finish_with_error(con);
  }

  int num_fields = mysql_num_fields(result);
  printf("\n");
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
  scanf("%s", currentTable);
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
