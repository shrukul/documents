// A C / C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph
 
#include <stdio.h>
#include <limits.h>
 
// Number of vertices in the graph
#define V 20
 
// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[])
{
   // Initialize min value
   int min = INT_MAX, min_index;
 
   for (int v = 0; v < V; v++)
     if (sptSet[v] == false && dist[v] <= min)
         min = dist[v], min_index = v;
 
   return min_index;
}
 
// A utility function to print the constructed distance array
int printSolution(int dist[], int n)
{
   printf("Vertex   Distance from Source\n");
   for (int i = 0; i < V; i++)
      printf("%d \t\t %d\n", i, dist[i]);
}
 
// Funtion that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int graph[V][V], int src)
{
     int dist[V];     // The output array.  dist[i] will hold the shortest
                      // distance from src to i
 
     bool sptSet[V]; // sptSet[i] will true if vertex i is included in shortest
                     // path tree or shortest distance from src to i is finalized
 
     // Initialize all distances as INFINITE and stpSet[] as false
     for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
 
     // Distance of source vertex from itself is always 0
     dist[src] = 0;
 
     // Find shortest path for all vertices
     for (int count = 0; count < V-1; count++)
     {
       // Pick the minimum distance vertex from the set of vertices not
       // yet processed. u is always equal to src in first iteration.
       int u = minDistance(dist, sptSet);
 
       // Mark the picked vertex as processed
       sptSet[u] = true;
 
       // Update dist value of the adjacent vertices of the picked vertex.
       for (int v = 0; v < V; v++)
 
         // Update dist[v] only if is not in sptSet, there is an edge from 
         // u to v, and total weight of path from src to  v through u is 
         // smaller than current value of dist[v]
         if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX 
                                       && dist[u]+graph[u][v] < dist[v])
            dist[v] = dist[u] + graph[u][v];
     }
 
     // print the constructed distance array
     printSolution(dist, V);
}
 
// driver program to test above function
int main()
{
   /* Let us create the example graph discussed above */
   int graph[V][V] = {// 0001020304050607080910111213141516171819
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},   // 00
	{1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,1},   // 01
	{1,9,9,1,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1},   // 02
	{1,9,9,1,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1},   // 03
	{1,9,1,1,1,1,9,9,1,9,1,9,1,1,1,1,9,9,1,1},   // 04
	{1,9,1,1,9,1,1,1,1,9,1,1,1,1,9,1,1,1,1,1},   // 05
	{1,9,9,9,9,1,1,1,1,1,1,9,9,9,9,1,1,1,1,1},   // 06
	{1,9,9,9,9,9,9,9,9,1,1,1,9,9,9,9,9,9,9,1},   // 07
	{1,9,1,1,1,1,1,1,1,1,1,9,1,1,1,1,1,1,1,1},   // 08
	{1,9,1,9,9,9,9,9,9,9,1,1,9,9,9,9,9,9,9,1},   // 09
	{1,9,1,1,1,1,9,1,1,9,1,1,1,1,1,1,1,1,1,1},   // 10
	{1,9,9,9,9,9,1,9,1,9,1,9,9,9,9,9,1,1,1,1},   // 11
	{1,9,1,9,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1},   // 12
	{1,9,1,9,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1},   // 13
	{1,9,1,1,1,1,9,9,1,9,1,9,1,1,1,1,9,9,1,1},   // 14
	{1,9,1,1,9,1,1,1,1,9,1,1,1,1,9,1,1,1,1,1},   // 15
	{1,9,9,9,9,1,1,1,1,1,1,9,9,9,9,1,1,1,1,1},   // 16
	{1,1,9,9,9,9,9,9,9,1,1,1,9,9,9,1,9,9,9,9},   // 17
	{1,9,1,1,1,1,1,1,1,1,1,9,1,1,1,1,1,1,1,1},   // 18
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}   // 19
                     };
 
    dijkstra(graph, 0);
 
    return 0;
}
