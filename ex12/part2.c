#include "graph.h"
#include <math.h>

int check_for_target(int target, List *outlist)
{
    while (outlist !=NULL)
    {
      if(target == outlist->index)
        return 1;
      outlist = outlist->next;
    }
    return 0;
}

void heuristic_path_finder(Graph *mygraph, int source, int target, float *distance)
{
  int visited[mygraph->MaxSize +1];
  for(int i = 1; i <= mygraph->MaxSize; i++ )
    visited[i] = 0;

  *distance = 0;
  if(source == target)
    return;

  visited[source] = 1;
  List *current_outlist = mygraph->table[source].outlist;

  while(!check_for_target(target, current_outlist) && current_outlist!= NULL)
  {
    *distance = *distance +1;
    int max_outdegree = -1;
    int maxout = 0;
    while(current_outlist != NULL)
    {
      if(visited[current_outlist->index] == 0 &&
          max_outdegree < mygraph->table[current_outlist->index].outdegree)
      {
        max_outdegree = mygraph->table[current_outlist->index].outdegree;
        maxout = current_outlist->index;
      }
      current_outlist = current_outlist->next;
    }

    visited[maxout] = 1;
    current_outlist = mygraph->table[maxout].outlist;

  }

  if(current_outlist == NULL)
    *distance = INFINITY;
  else
    *distance = *distance +1;


}

// -----------------------------------------------------------------------------

int main(int argc,char *argv[])
{
  Graph mygraph;
  read_graph(&mygraph,argv[1]);
  float distance = 0;
  int paths_less_than_6 = 0;
  double social_network_percentage;

  if(strstr(argv[1], "Oklahoma.gx"))
  {
    printf("Call heuristic path finder method for the first node.\n");
    int j;
    for(j = 2; j <= mygraph.MaxSize; j++)
    {
      printf("\rCalculating heuristic path to node %d.", j );
      heuristic_path_finder(&mygraph, 1, j, &distance);
      if(distance <= 6)
        paths_less_than_6 ++;
    }

    social_network_percentage = (double)paths_less_than_6 / mygraph.MaxSize;
    printf("\nThere are %d paths with less than 6 nodes for node 1.\n", paths_less_than_6);
    printf("Percentage of a small-world network: %.2f%%\n",social_network_percentage * 100);

    return(0);
  }

  int i,j;
  for(i = 1 ; i <= mygraph.MaxSize; i++)
  {
    for(j = 1; j <=mygraph.MaxSize; j++)
    {
        printf("\rCalculating heuristic path from node %d to all nodes.", i );
        heuristic_path_finder(&mygraph, i, j, &distance);
        if(distance <= 6)
          paths_less_than_6++;

    }
  }

  social_network_percentage = (double)paths_less_than_6 /( mygraph.MaxSize * mygraph.MaxSize);
  printf("\nThere are %d paths with less than 6 nodes.\n", paths_less_than_6);
  printf("Percentage of a small-world network: %.2f%%\n",social_network_percentage * 100);

  return(0);
}
