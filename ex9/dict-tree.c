#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>
#include "speller.h"
#include "dict.h"

typedef struct node *tree_ptr;

int height_node(tree_ptr tree_node);

//------------------------------- Structs --------------------------------------

struct node
{
  Key_Type element; // only data is the key itself
  tree_ptr left, right;
  int height;   // only used for AVL trees
};

struct table
{
  tree_ptr head; // points to the head of the tree
  double average_comapares_insert;
  double average_comapares_find;
  int height;
  int no_nodes;
};


//------------------------------- Variables ------------------------------------

// Used for statistics
int no_compares = 0;
double total_comapares_insert= 0;
double total_comapares_find = 0;
int find_calls =0;

// Check for duplicates
Boolean duplicate = FALSE;

//------------------------------- Init methods ---------------------------------

Table initialize_table(/*ignore parameter*/)
{
  Table new_table = (Table)malloc(sizeof(struct table));
  new_table->head = NULL;
  new_table->average_comapares_find =0;
  new_table->average_comapares_insert =0;
  new_table->no_nodes = 0;
  return new_table;
}

tree_ptr initialize_node(Key_Type data)
{
  tree_ptr new_node = (tree_ptr)malloc(sizeof(struct node));
  new_node->element = strdup(data);
  new_node->left = NULL;
  new_node->right = NULL;
  return new_node;
}
//---------------------------- AVL Tree ----------------------------------------
tree_ptr rotate_left(tree_ptr tree_node)
{
  // The variables that are rotating
  tree_ptr new_root = tree_node->right;
  tree_ptr rotate_node = new_root->left;

  // Execute rotate
  new_root->left = tree_node;
  tree_node->right = rotate_node;


  // Modify heights
  if(height_node(new_root->left) > height_node(new_root->right))
    new_root->height = height_node(new_root->left)+1;
  else
    new_root->height = height_node(new_root->right)+1;

  if(height_node(tree_node->left) > height_node(tree_node->right))
    tree_node->height = height_node(tree_node->left)+1;
  else
    tree_node->height = height_node(tree_node->right)+1;

  return new_root;
}

tree_ptr rotate_right(tree_ptr tree_node)
{
  // The variables that are rotating
  tree_ptr new_root = tree_node->left;
  tree_ptr rotate_node = new_root->right;

  // Execute rotate
  new_root->right = tree_node;
  tree_node->left = rotate_node;

  // Modify heights
  if(height_node(new_root->left) > height_node(new_root->right))
    new_root->height = height_node(new_root->left)+1;
  else
    new_root->height = height_node(new_root->right)+1;

  if(height_node(tree_node->left) > height_node(tree_node->right))
    tree_node->height = height_node(tree_node->left)+1;
  else
    tree_node->height = height_node(tree_node->right)+1;

  return new_root;
}


tree_ptr avl_balence_tree(Key_Type key, tree_ptr tree_node)
{
  // update height of the current node
  if(height_node(tree_node->left) > height_node(tree_node->right))
    tree_node->height = 1 + height_node(tree_node->left);
  else
    tree_node->height = 1 + height_node(tree_node->right);

  // see the balancing factor
  int balance_factor = height_node(tree_node->left) - height_node(tree_node->right);

  // LL case
  if(balance_factor > 1 && strcmp(key,tree_node->left->element) <0)
  {
    return rotate_right(tree_node);
  }
  // LR case
  if(balance_factor > 1 && strcmp(key,tree_node->left->element) >0)
  {
    tree_node->left = rotate_left(tree_node->left);
    return rotate_right(tree_node);
  }
  // RR case
  if(balance_factor < -1 && strcmp(key,tree_node->right->element) >0)
  {
    return rotate_left(tree_node);
  }

  // RL case
  if(balance_factor < -1 &&strcmp(key,tree_node->right->element) <0)
  {
    tree_node->right = rotate_right(tree_node->right);
    return rotate_left(tree_node);
  }

  // Unchanged node
  return tree_node;

}

//------------------------------- Insertion ------------------------------------
tree_ptr insert_node(Key_Type key, tree_ptr tree_node)
{
  if(tree_node == NULL)
  {
    tree_node = initialize_node(key);
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

  if(mode == 2)
  {
    return avl_balence_tree(key, tree_node);
  }

    return tree_node;
}


Table insert(Key_Type key,Table table)
{
  // If it is the first element, i.e the root
  if(table->head == NULL)
  {
    table->head = initialize_node(key);
  }
  else
      table->head=insert_node(key, table->head);

  // Calculate the number of nodes
  if(!duplicate)
  {
    table->no_nodes++;
  }
  else
    duplicate = FALSE;
  return table;
}

//------------------------------- Find -----------------------------------------
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
  // Used to calculate the average for find compares
  find_calls++;
  if(strcmp(table->head->element, key) == 0)
  {
    total_comapares_find++;
    return TRUE;
  }
  else
    return find_node(key, table->head);
}

//------------------------------- Utilities ------------------------------------

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
      printf("Right value: %s\n\n", tree_node->right->element);
    else
      printf("Right value: NULL\n\n" );

    if (tree_node->right!=NULL) {
      print_node(tree_node->right);
    }
}
void print_table(Table table)
{
    print_node(table->head);
}


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
//------------------------------- End ------------------------------------------
