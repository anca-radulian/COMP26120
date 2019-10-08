#include "graph.h"

int main(int argc,char *argv[])
{
  Graph mygraph;

  read_graph(&mygraph,argv[1]);

  // Calculate the node with the largest outdegree, laregest in degree and
  // smallest in degree.
  int max_outdegree = mygraph.table[1].outdegree;
  int max_indegree = 0;
  int min_indegree = mygraph.MaxSize;

  Node node1 = mygraph.table[1];
  Node node2;
  Node node3;
  List *current_list;
  for(int i = 1; i <= mygraph.MaxSize; i++)
  {
    if(max_outdegree < mygraph.table[i].outdegree)
    {
      max_outdegree = mygraph.table[i].outdegree;
      node1 = mygraph.table[i];
    }
    int indegree = 0;
    for(int j = 1; j<=mygraph.MaxSize; j++)
    {
      current_list= mygraph.table[j].outlist;
      while (current_list!=NULL)
      {
        if(i == current_list->index)
        {
          indegree ++;
        }
        current_list= current_list->next;
      }
    }
    if(indegree > max_indegree)
    {
      max_indegree = indegree;
      node2 = mygraph.table[i];
    }
    if(indegree < min_indegree && indegree!=0)
    {
      min_indegree = indegree;
      node3 = mygraph.table[i];
    }

  }

  printf("The node with the largest outdegree is %s.\n",node1.name );
  printf("The node with the largest indegree is %s.\n",node2.name );
  printf("The node with the smallest indegree is %s.\n",node3.name );
  return(0);
}
