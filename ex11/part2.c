#include "graph.h"

extern void search_graph(Graph *mygraph, int index);

int main(int argc,char *argv[])
{
  Graph mygraph;
  read_graph(&mygraph,argv[1]);


  // Calculate the node with the smallest out degree
  int node_index = 1;
  int min_outdegree = mygraph.table[1].outdegree;
  for(int i = 2; i <= mygraph.MaxSize; i++)
  {
    if(min_outdegree > mygraph.table[i].outdegree
        && mygraph.table[i].outdegree != 0)
    {
      min_outdegree = mygraph.table[i].outdegree;
      node_index = i;
    }
  }
  printf("The node with the smallest out degree is %d\n",node_index );
  printf("Nodes reachable from this mode are: \n");
  search_graph(&mygraph, node_index);

  //print_graph(&mygraph);


  return(0);
}
