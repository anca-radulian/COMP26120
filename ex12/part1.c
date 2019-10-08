#include "graph.h"
#include <math.h>
#include <string.h>

//------------------------- Priority queue methods -----------------------------

// Keep track of the elements of the queue
int queue_size = 0;

// Reorders elements after an insert
void up_priority_queue(int index, int* priority_queue, float* distances, int *positions)
{
  int parent = index/2;
  while(parent >= 1)
  {
    if(distances[priority_queue[parent]] > distances[priority_queue[index]])
    {
      // Swap positions
      int temp_pos = positions[priority_queue[parent]];
      positions[priority_queue[parent]] = positions[priority_queue[index]];
      positions[priority_queue[index]] = temp_pos;

      // Swap in priority queue
      int temp_node = priority_queue[parent];
      priority_queue[parent] = priority_queue[index];
      priority_queue[index] = temp_node;
    }
      else break;

    index = parent;
    parent = index /2;
  }
}

// Reorders elements after a removal
void down_priority_queue(int index, int *priority_queue, float *distances, int* positions)
{
  int left_child = index * 2;
  int right_child = index * 2 + 1;
  int smallest = left_child;
  while(smallest <= queue_size)
  {

    if(right_child <= queue_size &&
       distances[priority_queue[smallest]] > distances[priority_queue[right_child]])
       smallest = right_child;

    if(distances[priority_queue[index]] < distances[priority_queue[smallest]])
      break;
    else
    {
      // Swap positions
      int temp_pos = positions[priority_queue[smallest]];
      positions[priority_queue[smallest]] = positions[priority_queue[index]];
      positions[priority_queue[index]] = temp_pos;

      // Swap in priority queue
      int temp_node = priority_queue[smallest];
      priority_queue[smallest] = priority_queue[index];
      priority_queue[index] = temp_node;
    }
    index = smallest;
    left_child = index *2;
    right_child = index *2 +1;
    smallest = left_child;
  }
}


int removeMin(int* priority_queue, float* distances, int* positions)
{
  int min = priority_queue[1];
  priority_queue[1] = priority_queue[queue_size--];
  down_priority_queue(1,priority_queue, distances, positions);
  return min;
}

// ----------------------- Dijkstra's Algorithm --------------------------------

void dijkstra_algorithm(int source, Graph *mygraph, float *distances)
{
  // Define the priority queue
  int priority_queue[mygraph->MaxSize + 1];

  // Keep track of the positions of nodes in the heap and of the visited nodes
  int positions[mygraph->MaxSize + 1];
  int visited[mygraph->MaxSize + 1];

  // Add the source node to the heap
  priority_queue[++queue_size] = source;
  distances[source] = 0;
  positions[source] = queue_size;

  // Initialize the distances
  for(int i = 1; i <= mygraph->MaxSize; i++)
  {
    visited[i] = 0;
    positions[i] = 0;
    if(i != source)
    {
      priority_queue[++queue_size] = i;
      positions[i] = queue_size;
      distances[i] = INFINITY;
    }
  }

  while(queue_size != 0)
  {

    int current_node = removeMin(priority_queue, distances, positions);
    visited[current_node] = 1;
    List *adj_list= mygraph->table[current_node].outlist;
    while (adj_list!=NULL)
    {
      if(visited[adj_list->index] == 0 &&
          distances[current_node] + 1 < distances[adj_list->index])

      {
        distances[adj_list->index] = distances[current_node] + 1;
        up_priority_queue(positions[adj_list->index], priority_queue,
                            distances, positions);
      }
      adj_list= adj_list->next;
    }
  }
}

//------------------------------------------------------------------------------
int main(int argc,char *argv[])
{
  Graph mygraph;
  int paths_less_than_6 = 0;

  read_graph(&mygraph,argv[1]);
  float distances[mygraph.MaxSize + 1];

  if(strstr(argv[1], "Oklahoma.gx"))
  {
    printf("Call Dijkstra for the first node.\n");
    dijkstra_algorithm(1, &mygraph, distances);
    for(int j = 1; j <= mygraph.MaxSize; j++)
    {
      if(distances[j] <= 6)
        paths_less_than_6 ++;
    }

    double social_network_percentage = (double)paths_less_than_6 / mygraph.MaxSize;
    printf("There are %d paths with less than 6 nodes for node 1.\n", paths_less_than_6);
    printf("Percentage of a small-world network: %.2f%%\n",social_network_percentage * 100);
    printf("\n");

    printf("Call Dijkstra for the node 9619.\n");
    paths_less_than_6 = 0;
    dijkstra_algorithm(9619, &mygraph, distances);
    for(int j = 1; j <= mygraph.MaxSize; j++)
    {
      if(distances[j] <= 6)
        paths_less_than_6 ++;
    }

    social_network_percentage = (double)paths_less_than_6 / mygraph.MaxSize;
    printf("There are %d paths with less than 6 nodes for node 9619.\n", paths_less_than_6);
    printf("Percentage of a small-world network: %.2f%%\n",social_network_percentage * 100);


    return (0);
  }

  for(int i = 1; i <=mygraph.MaxSize; i++)
  {
    dijkstra_algorithm(i, &mygraph, distances);
    for(int j = 1; j <= mygraph.MaxSize; j++)
    {
      if(distances[j] <= 6)
        paths_less_than_6 ++;
    }
  }

  double social_network_percentage = (double)paths_less_than_6 /
                                            (mygraph.MaxSize * mygraph.MaxSize);

  printf("There are %d paths with less than 6 nodes.\n", paths_less_than_6);
  printf("Percentage of a small-world network: %.2f%%\n",social_network_percentage * 100);

  return(0);
}
