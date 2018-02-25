#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>
#include <math.h>

#include "speller.h"
#include "dict.h"

#define prime_num (33)
typedef struct
{ // hash-table entry
  Key_Type element; // only data is the key itself
  enum {empty, in_use, deleted} state;
} cell;

typedef unsigned int Table_size; // type for size-of or index-into hash table

struct table
{
  cell *cells; Table_size table_size; // cell cells [table_size];
  Table_size num_entries; // number of cells in_use
  // add anything else that you need
};

Table initialize_table (Table_size table_size)
{
  Table table = (Table)malloc(sizeof(struct table));
  table->table_size = table_size;
  table->num_entries = 0;
  table->cells = (cell *)calloc(table_size, sizeof(cell));
  for(int i = 0; i< table_size; i++)
  {
    table->cells[i].state = empty;
  }
  return table;
}
//--------------------------- insert -------------------------------------------

Table_size hash_code(Key_Type key, Table table)
{

  int i = 0;
  int length = strlen(key) - 1;
  Table_size hash_index = 0;


  while (length >= 0)
  {
    hash_index+= key[length] * (int)pow(prime_num, i);
    i++;
    length--;
  }
  hash_index = hash_index % table->table_size;
  printf("For key %s hash code is: %d\n",key, hash_index );
  return hash_index;
}

Table insert (Key_Type key, Table table)
{
  // The table is full
  if(table->num_entries == table->table_size)
    return table;

  Table_size hash_index = hash_code(key, table);
  if(table->cells[hash_index].state == empty)
  {
    table->cells[hash_index].element = strdup(key);
    table->cells[hash_index].state = in_use;
    table->num_entries++;
  }
  else
  {
    switch (mode)
     {
       // Liniar probing
       case 1:

          while(table->cells[hash_index].state!=empty &&
                strcmp(table->cells[hash_index].element,key)!=0)
          {
            hash_index++;
            hash_index = hash_index % table->table_size;
          }
          if(table->cells[hash_index].state==empty)
          {
            table->cells[hash_index].element = strdup(key);
            table->cells[hash_index].state = in_use;
            table->num_entries++;
          }
          break;
     }
  }

  return table;
}

Boolean find (Key_Type key, Table table)
{

//  printf(" print size find : %d\n",table->table_size );
  return TRUE;
}

void print_table (Table table)
{

  for(int i= 0; i < table->table_size;i++)
  {
  //  printf("state for cel %d: %d\n",i,table->cells[i].state);
    printf("element for cel %d: %s\n",i,table->cells[i].element);

  }
}

void print_stats (Table table)
{
}
