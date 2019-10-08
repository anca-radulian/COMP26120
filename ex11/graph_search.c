#include "graph.h"
/* Good luck */
// #define DFS
// #undef BFS

 #define BFS
 #undef DFS


List *search_list;
int  *visited;

List* insert_list(List *search_list, int index)
{

  List *newitem = (List *)malloc(sizeof(List));
  check(newitem, "new list item");
  newitem->index = index;

  // first element in the search list
  if(search_list == NULL)
  {
    search_list = newitem;
    newitem->next = NULL;
    return search_list;
  }

  // Choose between the two search methods
  #ifdef DFS
    newitem->next = search_list;
    search_list = newitem;
  #endif

  #ifdef BFS
    newitem->next = NULL;
    List *current = search_list;
    while(current->next !=NULL)
      current = current->next;
    current->next = newitem;
  #endif

  return search_list;
}

// Return the first element from the search list
List* top(List *search_list, int *index)
{
  *index = search_list->index;
  search_list = search_list->next;
  return search_list;
}

void search_graph(Graph *mygraph, int index)
{
   // Alocate memory for the search list and visited array
   visited = (int *)calloc(mygraph->MaxSize + 1,sizeof(int));
   check(visited, "integer array");
   search_list = (List *)malloc(sizeof(List));
   check(search_list, "search list");

   // Add the first element in the search list
   search_list->index = index;
   search_list->next = NULL;
   visited[index] = 1;

   while(search_list!=NULL)
   {
     int current_index = 0;
     search_list = top(search_list, &current_index);
     printf("Node %d - out degree = %d\n", current_index,
             mygraph->table[current_index].outdegree);
     List *adj_list = mygraph->table[current_index].outlist;

     while(adj_list!= NULL)
     {
       if(visited[adj_list->index]== 0)
       {
         visited[adj_list->index] = 1;
         search_list = insert_list(search_list, adj_list->index);
       }
       adj_list = adj_list->next;
     }
   }
}
