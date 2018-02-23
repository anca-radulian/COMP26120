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
  // add anything else that you need
};

struct table
{
  tree_ptr head; // points to the head of the tree
  // add anything else that you need
};

Table initialize_table(/*ignore parameter*/)
{
  Table new_table = (Table)malloc(sizeof(struct table));
  new_table->head = NULL;
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
  }
  else if(strcmp(key, tree_node->element) < 0)
    {
      tree_node->left = insert_node(key, tree_node->left);

    }
  else if(strcmp(key, tree_node->element) > 0)
  {
    tree_node->right =insert_node(key, tree_node->right);
  }
  return tree_node;
}


Table insert(Key_Type key,Table table)
{
  // If it is the first element, i.e the root
  if(table->head == NULL)
    table->head = initialize_node(key);
  else
  {
    insert_node(key, table->head);

  }
  return table;
}

// Helper method
Boolean find_node(Key_Type key, tree_ptr tree_node)
{
  if(tree_node== NULL)
    return FALSE;
  else if(strcmp(key, tree_node->element) == 0)
    return TRUE;
  else if(strcmp(key, tree_node->element) < 0)
    return find_node(key, tree_node->left);
  else
    return find_node(key, tree_node->right);
}

Boolean find(Key_Type key, Table table)
{
  if(strcmp(table->head->element, key) == 0)
    return TRUE;
  else
    return find_node(key, table->head);
}

// Helper method
void print_node(tree_ptr tree_node)
{
    if(tree_node->left!= NULL)
      print_node(tree_node->left);
    printf("Node value: %s.\n", tree_node->element);
    if (tree_node->right!=NULL) {
      print_node(tree_node->right);
    }
}
void print_table(Table table)
{
    print_node(table->head);
}

void print_stats (Table table)
{

}
