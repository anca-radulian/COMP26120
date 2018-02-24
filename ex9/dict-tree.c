#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>
#include "speller.h"
#include "dict.h"

typedef struct node *tree_ptr;
struct node
{
  Key_Type element; // only data is the key itself
  tree_ptr left, right;
  int no_compares_insert;
  // add anything else that you need
};

struct table
{
  tree_ptr head; // points to the head of the tree
  double average_comapares_insert;
  double average_comapares_find;
  int height;
  int no_nodes;
  // add anything else that you need
};

// Used for statistics
int no_compares = 0;
double total_comapares_insert= 0;
double total_comapares_find = 0;
Boolean duplicate = FALSE;
int find_calls =0;

Table initialize_table(/*ignore parameter*/)
{
  Table new_table = (Table)malloc(sizeof(struct table));
  new_table->head = NULL;
  new_table->average_comapares_find =0;
  new_table->average_comapares_insert =0;
  new_table->no_nodes = 0;
  return new_table;
}

// Helper method
tree_ptr initialize_node(Key_Type data)
{
  tree_ptr new_node = (tree_ptr)malloc(sizeof(struct node));
  new_node->element = strdup(data);
  new_node->left = NULL;
  new_node->right = NULL;
  return new_node;
}

// Helper method
tree_ptr insert_node(Key_Type key, tree_ptr tree_node)
{
  if(tree_node == NULL)
  {
    tree_node = initialize_node(key);
    tree_node->no_compares_insert = no_compares;
    total_comapares_insert += no_compares;
    no_compares = 0;
  }
  else if(strcmp(key, tree_node->element) < 0)
    {
      no_compares++;
      tree_node->left = insert_node(key, tree_node->left);

    }
  else if(strcmp(key, tree_node->element) > 0)
  {
    no_compares++;
    tree_node->right =insert_node(key, tree_node->right);
  }
  else
  {
    duplicate = TRUE;
  }

  return tree_node;
}


Table insert(Key_Type key,Table table)
{
  // If it is the first element, i.e the root
  if(table->head == NULL)
  {
    table->head = initialize_node(key);
    table->head->no_compares_insert = 0;
  }
  else
  {
    insert_node(key, table->head);
  }

  if(!duplicate)
  {
    table->no_nodes++;
  }
  else
    duplicate = FALSE;
  return table;
}

// Helper method
Boolean find_node(Key_Type key, tree_ptr tree_node)
{
  if(tree_node== NULL)
  {
    total_comapares_find+= no_compares;
    no_compares = 0;
    return FALSE;
  }
  else if(strcmp(key, tree_node->element) == 0)
  {
    no_compares++;
    total_comapares_find+= no_compares;
    no_compares = 0;
    return TRUE;
  }
  else if(strcmp(key, tree_node->element) < 0)
  {
    no_compares++;
    return find_node(key, tree_node->left);
  }
  else
  {
    no_compares++;
    return find_node(key, tree_node->right);
  }
}

Boolean find(Key_Type key, Table table)
{
  find_calls++;
  if(strcmp(table->head->element, key) == 0)
  {
    total_comapares_find++;
    return TRUE;
  }
  else
    return find_node(key, table->head);
}

// Helper method
void print_node(tree_ptr tree_node)
{
    if(tree_node->left!= NULL)
      print_node(tree_node->left);
    printf("Node value: %s.\n", tree_node->element);
    if(tree_node->left!= NULL)
      printf("Left value: %s\n", tree_node->left->element);
    else
      printf("Left value: NULL\n");
    if(tree_node->right!= NULL)
      printf("Right value: %s\n", tree_node->right->element);
    else
      printf("Right value: NULL\n" );
    printf("Compares insert: %d\n\n", tree_node->no_compares_insert );

    if (tree_node->right!=NULL) {
      print_node(tree_node->right);
    }
}
void print_table(Table table)
{
    print_node(table->head);
}
int result = 0;
int height_node(tree_ptr tree_node)
{
  if(tree_node == NULL)
    return -1;
  int height_left = height_node(tree_node->left);
  int height_right = height_node(tree_node->right);
  if(height_left > height_right)
    return height_left +1;
  else
    return height_right +1;
}

void print_stats (Table table)
{
  table->height = height_node(table->head);
  table->average_comapares_insert = total_comapares_insert/table->no_nodes;
  table->average_comapares_find = total_comapares_find/find_calls;

  printf("The height of the tree is: %d.\n",table->height);
  printf("Number of nodes: %d\n", table->no_nodes);
  printf("Average number of compares for insert: %.2f\n",table->average_comapares_insert);
  printf("Average number of compares for find: %.2f\n\n", table->average_comapares_find);

}
