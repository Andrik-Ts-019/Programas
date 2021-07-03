
#include <stdio.h> 
#include <limits.h> 
#include <stdbool.h> 
// Number of vertices 
// in the graph 
#define V 11 


int minDistance(int dist[], bool sptSet[]) 
{ 
	int v;
	// Initialize min value 
	int min = INT_MAX, min_index; 

	for (v = 0; v < V; v++) 
		if (sptSet[v] == false && dist[v] <= min) 
			min = dist[v], min_index = v; 

	return min_index; 
} 

void printPath(int parent[], int j) 
{ 
	 
	if (parent[j] == - 1) 
		return; 

	printPath(parent, parent[j]); 

	printf("->%d ", j); 
} 

int printSolution(int dist[], int parent[], int src) 
{ 
	int i; 
	printf("Vertex\t Distance\tPath"); 
	i=6;
		printf("\n%d -> %d \t\t %d\t\t%d ", src, i, dist[i], src); 
		printPath(parent, i); 
} 

void dijkstra(int graph[V][V], int src) 
{ 
	
	int dist[V]; 

	bool sptSet[V]; 

	int parent[V]; 

	int i;
	for (i = 0; i < V; i++) 
	{ 
		parent[src] = -1; 
		dist[i] = INT_MAX; 
		sptSet[i] = false; 
	} 
 
	dist[src] = 0; 

	int count;
	for (count = 0; count < V - 1; count++) 
	{ 
		 
		int u = minDistance(dist, sptSet); 

		sptSet[u] = true; 

		// Update dist value of the 
		// adjacent vertices of the 
		// picked vertex. 
		int v;
		for (v = 0; v < V; v++) 

			if (!sptSet[v] && graph[u][v] && 
				dist[u] + graph[u][v] < dist[v]) 
			{ 
				parent[v] = u; 
				dist[v] = dist[u] + graph[u][v]; 
			} 
	} 

	// print the constructed 
	// distance array 
	printSolution(dist, parent, src); 
} 

// Driver Code 
int main() 
{ 
	// Let us create the example 
	// graph discussed above 
	int graph[V][V] = {
      					{0, 600, 0, 0, 0, 0, 0, 0, 0, 0, 800}, 
						{600, 0, 600, 0, 0, 0, 0, 0, 0, 700, 0}, 
						{0, 600, 0, 450, 0, 0, 0, 0, 0, 0, 0}, 
						{0, 0, 450, 0, 600, 0, 0, 650, 0, 750, 0}, 
						{0, 0, 0, 600, 0, 750, 0, 0, 0, 0, 0}, 
						{0, 0, 0, 0, 750, 0, 850, 0, 0, 0, 0}, 
						{0, 0, 0, 0, 0, 850, 0, 900, 0, 0, 0}, 
						{0, 0, 0, 650, 0, 0, 900, 0, 500, 0, 0}, 
						{0, 0, 0, 0, 0, 0, 0, 500, 0, 1000, 0},
                       	{0, 700, 0, 750, 0, 0, 0, 0, 1000, 0, 400},
                       	{800, 0, 0, 0, 0, 0, 0, 0, 0, 400, 0}
					}; 

	dijkstra(graph, 0); 
	return 0; 
} 
