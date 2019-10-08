#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>
#include <math.h>

#include "speller.h"
#include "dict.h"

//Used for hashing
#define prime_num (33)
#define prime_num2 (41)
#define RESIZE_FACTOR 2

// Used for stats
int no_collisons;

typedef unsigned int Table_size; // type for size-of or index-into hash table

typedef struct
{ // hash-table entry
  Key_Type element; // only data is the key itself
  enum {empty, in_use, deleted} state;
} cell;


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

  // Initialize all cells to empty
  for(int i = 0; i< table_size; i++)
    table->cells[i].state = empty;
  return table;
}

//------------------------------- utilities ------------------------------------

// Find a prime number for the table size which is smaller than the provided
// number.
Table_size prime(Table_size table_size)
{
  Boolean found = FALSE;
  Table_size new_table_size = table_size;

  while(!found)
  {
    Boolean prime = TRUE;
    for(int i = 2; i < new_table_size / 2; i++ )
      if(new_table_size % i == 0)
        prime = FALSE;

    if(prime)
      break;
    else
      new_table_size--;
  }

  return new_table_size;
}

// Resize the table
Table resize(Table table)
{
  // Reevaluate the number of collisons for the new table
  no_collisons = 0;
  Table new_table = initialize_table(prime(RESIZE_FACTOR * table->table_size));
  for(int i = 0; i < table->table_size; i++)
    if(table->cells[i].state!=empty)
      new_table = insert(table->cells[i].element, new_table);

  // Free the previous table
  free(table);

  return new_table;
}

//--------------------------- hash method --------------------------------------

Table_size hash_code(Key_Type key, Table table)
{

  int i = 0;
  int length = strlen(key) - 1;
  Table_size hash_index = 0;

  // Calculate the hash code using a polynomial approach
  while (length >= 0)
  {
    hash_index+= key[length] * (int)pow(prime_num, i);
    i++;
    length--;
  }

  // Compression map using two prime constants
  hash_index = ((prime_num)*hash_index + prime_num2) % table->table_size;

  return hash_index;
}

//------------------------------- insert ---------------------------------------
Table insert (Key_Type key, Table table)
{
  // If the load factor is bigger than 0.5 resize
  if(((double)table->num_entries / table->table_size) >= 0.5)
    table = resize(table);

  Table_size hash_index = hash_code(key, table);

  // Insertion complexity O(1)
  if(table->cells[hash_index].state == empty)
  {
    table->cells[hash_index].element = strdup(key);
    table->cells[hash_index].state = in_use;
    table->num_entries++;
  }
  else
  {
    // Collision handling using different strategies
    int j = 0;
    Table_size d_hash_index;
    switch (mode)
    {
       // Liniar probing
      case 1:

        while(table->cells[hash_index].state!=empty &&
              strcmp(table->cells[hash_index].element,key)!=0)
        {
          no_collisons++  ;
          hash_index++;
          hash_index = hash_index % table->table_size;
        }
        break;

      // Quadratic probing
      case 2:
        j = 0;
        while(table->cells[hash_index].state!=empty &&
              strcmp(table->cells[hash_index].element,key)!=0)
        {
          no_collisons++;
          j++;
          hash_index = (hash_index+ j*j) % table->table_size;
        }
        break;

     // Double hashing
     case 3:
       // New hash code h' = q - (h % q)
       d_hash_index = prime(table->table_size) -
                          (hash_index % prime(table->table_size));
       j = 1;
       while (table->cells[hash_index].state != empty
              && strcmp(table->cells[hash_index].element,key)!=0)
        {
          no_collisons++;
          j++;
          hash_index = (hash_index + j*d_hash_index)%table->table_size;
        }
       break;
     }

    // insert the element after finding a new space
    if(table->cells[hash_index].state==empty)
    {
      table->cells[hash_index].element = strdup(key);
      table->cells[hash_index].state = in_use;
      table->num_entries++;
    }
  }

  return table;
}

Boolean find (Key_Type key, Table table)
{
  Table_size hash_index = hash_code(key, table);

  int j = 0;
  Table_size d_hash_index;
  switch (mode)
  {
    // Liniar probing
    case 1:
      while (table->cells[hash_index].state != empty)
       {
         if(strcmp(table->cells[hash_index].element, key) == 0)
          return TRUE;
         hash_index++;
         hash_index %= table->table_size;
       }
      break;

    // Quadratic probing
    case 2:
      j = 0;
      while (table->cells[hash_index].state != empty)
       {
         if(strcmp(table->cells[hash_index].element, key) == 0)
          return TRUE;
         j++;
         hash_index = (hash_index + j*j)%table->table_size;
       }
      break;

      // Double hashing
      case 3:
        // New hash code
        d_hash_index = prime(table->table_size) -
                         (hash_index % prime(table->table_size));
        j = 1;
        while (table->cells[hash_index].state != empty)
         {
           if(strcmp(table->cells[hash_index].element, key) == 0)
            return TRUE;
           j++;
           hash_index = (hash_index + j*d_hash_index)%table->table_size;
         }
        break;
  }

  return FALSE;
}

void print_table (Table table)
{

  for(int i= 0; i < table->table_size;i++)
  {
    printf("Element of cell %2d: %s\n",i,table->cells[i].element);
  }
}

void print_stats (Table table)
{
  double average =(double)no_collisons / table->num_entries;
  printf("Number of collisons %d\n", no_collisons);
  printf("Average number of collisons per insert: %.2f\n", average);
}
