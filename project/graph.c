/*
 * CS 261 Data Structure
 * Assignment 7
 * Name: Bryan Konshak
 * Date: 
 */

#include "graph.h"
#include "deque.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/**
 * Clears isVisited in all nodes in the graph.
 * @param graph
 */
static void clearVisited(Graph* graph)
{
    for (int i = 0; i < graph->numVertices; ++i)
    {
        graph->vertexSet[i].isVisited = 0;
    }
}

/**
 * Recursive helper function for DfsRecursive. Determines if there is a path
 * from the given vertex to the destination using a recursive depth-first
 * search.
 * @param graph
 * @param vertex
 * @param destination
 * @return 1 if there is a path, 0 otherwise.
 */
static int DfsRecursiveHelper(Graph* graph, Vertex* vertex, Vertex* destination)
{
    vertex->isVisited = 1;
    if (vertex == destination)
    {
        return 1;
    }
    for (int i = 0; i < vertex->numNeighbors; ++i)
    {
        Vertex* neighbor = vertex->neighbors[i];
        if (!neighbor->isVisited)
        {
            if (DfsRecursiveHelper(graph, neighbor, destination) == 1)
            {
                return 1;
            }
        }
    }
    return 0;
}

/**
 * Determines if an edge (v1, v2) exists.
 * @param v1
 * @param v2
 * @return 1 if the edge exists, 0 otherwise.
 */
static int isAdjacent(Vertex* v1, Vertex* v2)
{
    if (v1 == v2)
    {
        return 1;
    }
    for (int i = 0; i < v1->numNeighbors; ++i)
    {
        if (v1->neighbors[i] == v2)
        {
            return 1;
        }
    }
    return 0;
}

/**
 * Connects two vertices by adding each other to their neighbors lists.
 * @param v1
 * @param v2
 */
void createEdge(Vertex* v1, Vertex* v2)
{
    v1->neighbors = realloc(v1->neighbors,
                            sizeof(Vertex*) * (v1->numNeighbors + 1));
    v2->neighbors = realloc(v2->neighbors,
                            sizeof(Vertex*) * (v2->numNeighbors + 1));
    v1->neighbors[v1->numNeighbors] = v2;
    v2->neighbors[v2->numNeighbors] = v1;
    ++(v1->numNeighbors);
    ++(v2->numNeighbors);
}

/**
 * Determines if there is a path from the source to the destination using a
 * recursive depth-first search starting at the source.
 * 
 * You can use this function to test the correctness of the others.
 * 
 * @param graph
 * @param source
 * @param destination
 * @return 1 if there is a path, 0 otherwise.
 */
int dfsRecursive(Graph* graph, Vertex* source, Vertex* destination)
{
    clearVisited(graph);
    return DfsRecursiveHelper(graph, source, destination);
}

/**
 * Determines if there is a path from the source to the destination using an
 * iterative depth-first search starting at the source.
 * 
 * Remember to call clearVisited() before starting the search.
 * 
 * @param graph
 * @param source
 * @param destination
 * @return 1 if there is a path, 0 otherwise.
 */
int dfsIterative(Graph* graph, Vertex* source, Vertex* destination)
{
    int i;
    if (source == destination)
        return 1;
    Deque* searchStack = dequeNew();
    clearVisited(graph);
    /*use stack properties  of deque to conduct DFS*/
    dequePushFront(searchStack, source);

    while (dequeIsEmpty(searchStack)==0)
    {
        Vertex* curVert = dequeFront(searchStack);
        dequePopFront(searchStack);
        curVert->isVisited=1;
        if (curVert == destination)
        {
            dequeDelete(searchStack);//delete deque for memory cleanup
            return 1;
        }
        for (i = 0; i <curVert->numNeighbors; i++)
        {
            if(curVert->neighbors[i]->isVisited==0)
            {
                dequePushFront(searchStack, curVert->neighbors[i]);
            }
        }
    }



    dequeDelete(searchStack);
    return 0;
}
//function to help with disjointed graphs calles bfsIterative to cycle through vertex not visited
int bfsIteratived(Graph* graph, Vertex* source, Vertex* destination, int good[], int bad[], int goodbad[], int n)
{
	int response=0;
	int i;
	int goodIt=0;
	int badIt=0;
   clearVisited(graph);
   for (i=0;i<n;i++)
   {
	   if(graph->vertexSet[i].isVisited==0)
	   {
		 response=bfsIterative(graph, &graph->vertexSet[i], &graph->vertexSet[i+1], good, bad, goodbad, &goodIt, &badIt);
		if (response==1)
			return 1;
	   }
   }
   return 0;
}





/**
 * Determines if there is a path from the source to the destination using an
 * iterative breadth-first search starting at the source.
 * 
 * Remember to call clearVisited() before starting the search.
 * 
 * @param graph
 * @param source
 * @param destination
 * array to keep track of good and bad
 * @return 1 if not possible, 0 otherwise.
 *
 */
int bfsIterative(Graph* graph, Vertex* source, Vertex* destination, int good[], int bad[], int goodbad[], int * goodIt, int * badIt)
{
    int i;
    int j=0;
    // good[100];
      //goodIt=0;
      //badIt=0;
     int goodo= 0;
     int bado = 0;
    // bad[100];
    //if (source == destination)
    //    return 1;
    /*use queue properties  of deque to conduct BFS*/
    Deque* searchStack = dequeNew();
//    clearVisited(graph);
    dequePushBack(searchStack, source);
    source->isEven=j;
    good[goodo]=source->label;
//    printf("Good: %d\n", good[0]);
    goodo++;

    while (dequeIsEmpty(searchStack)==0)
    {
        Vertex* curVert = dequeFront(searchStack);//add to stack
        dequePopFront(searchStack);
        curVert->isVisited=1;//first node
        if (curVert == destination)
        {
           // dequeDelete(searchStack);//delete the deque to avoid memory leaks
           // return 1;
        }
        for (i = 0; i <curVert->numNeighbors; i++)//check neighbors odd or even, heal or baby face
        {
            if(curVert->neighbors[i]->isVisited==0)//current is babyface
            {
		    if(curVert->isEven==0 && (curVert->neighbors[i]->isEven < 0 || curVert->neighbors[i]->isEven==1))//if current even, then make neighbors 
		    {
			    if (curVert->neighbors[i]->isEven < 0)//add neighbors to heals
			    {
				    bad[bado]=curVert->neighbors[i]->label;
    				    //printf("Bad: %d\n", bad[badIt]);
				    bado++;
			    }
			    curVert->neighbors[i]->isEven=1;
		    }
		    else if(curVert->isEven==1 && (curVert->neighbors[i]->isEven < 0 || curVert->neighbors[i]->isEven==0))//current is heal
		    {
			    if (curVert->neighbors[i]->isEven < 0)
			    {
				    good[goodo]=curVert->neighbors[i]->label;//add neighbors to babyface
    			//	    printf("Good: %d\n", good[goodIt]);
				    goodo++;
			    }
			    curVert->neighbors[i]->isEven=0;
		    }
		    else
		    {
    			dequeDelete(searchStack);
			    return 1;
		    }

                dequePushBack(searchStack, curVert->neighbors[i]);
            }
        }
    }
				    goodbad[0]=goodo;//arrays to print indexes of string names
				    goodbad[1]=bado;
    dequeDelete(searchStack);
    return 0;
}

typedef struct Edge Edge;

struct Edge
{
    int i;
    int j;
};

/**
 * Generates a set of random unique edges of size numEdges sampled from the
 * set of all possible edges.
 * @param numVertices
 * @param numEdges
 * @return An array of numEdges edges.
 */
Edge* randomEdges(int numVertices, int numEdges)
{
    assert(numVertices > 0);
    int maxEdges = numVertices * (numVertices - 1) / 2;
    assert(numEdges >= 0);
    assert(numEdges <= maxEdges);
    
    // Generate all possible edges
    Edge* edges = malloc(sizeof(Edge) * maxEdges);
    int k = 0;
    for (int i = 0; i < numVertices; ++i)
    {
        for (int j = i + 1; j < numVertices; ++j)
        {
            edges[k].i = i;
            edges[k].j = j;
            ++k;
        }
    }

    // Shuffle edges
    for (int i = maxEdges - 1; i > 0; --i)
    {
        int j = rand() % (i + 1);
        Edge temp = edges[i];
        edges[i] = edges[j];
        edges[j] = temp;
    }
    
    // Take only the number of edges needed
    edges = realloc(edges, sizeof(Edge) * numEdges);
    return edges;
}

/**
 * Given a number of vertices and a number of edges, generates a graph
 * connecting random pairs of vertices. The edges are unique, and thus their is
 * a maximum number of edges allowed in proportion to the number of vertices.
 * numEdges must be in the interval [0, numVertices * (numVertices + 1) / 2].
 * @param numVertices
 * @param numEdges
 * @return 
 */
Graph* randomGraph(int numVertices, int numEdges)
{
    assert(numVertices > 0);
    assert(numEdges >= 0);
    assert(numEdges <= numVertices * (numVertices - 1) / 2);
    
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->numEdges = numEdges;
    graph->vertexSet = malloc(sizeof(Vertex) * numVertices);
    
    // Initialize vertices
    for (int i = 0; i < graph->numVertices; ++i)
    {
        Vertex* vertex = &graph->vertexSet[i];
        vertex->label = i;
        vertex->isVisited = 0;
        vertex->numNeighbors = 0;
        vertex->neighbors = NULL;
    }
    
    // Randomly connect vertices
    Edge* edges = randomEdges(numVertices, numEdges);
    for (int i = 0; i < numEdges; ++i)
    {
        Vertex* v1 = &graph->vertexSet[edges[i].i];
        Vertex* v2 = &graph->vertexSet[edges[i].j];
        createEdge(v1, v2);
    }
    free(edges);

    return graph;
}

/**Initiates graph and sets all values for babyfaces and heals
 * @return 
 */

Graph* initGraph( int n, int xin[], int yin[])
{
	int numVertices=n;
//	printf("Hello from the init\n\n");
	Graph* graph = malloc(sizeof(Graph));
	graph->numVertices = numVertices;
	graph->numEdges=0;

	graph->vertexSet = malloc(sizeof(Vertex) * numVertices);
    for (int i = 0; i < numVertices; ++i)
    {
        Vertex* vertex = &graph->vertexSet[i];
        vertex->isVisited = 0;
        vertex->label = i;
        vertex->neighbors = NULL;
        vertex->numNeighbors = 0;
	vertex->isEven = -1;
	vertex->x=xin[i];
	vertex->y=yin[i];
//	strcpy(vertex->name, strings[i]);
//	printf("%s string name", graphv[i]);
    }
    return graph;
}

	

Graph* loadGraph(const char* fileName)
{
    FILE* file = fopen(fileName, "r");
    char buffer[512];
    
    // Get the number of vertices
    fgets(buffer, sizeof buffer, file);
    int numVertices = (int) strtol(buffer, NULL, 10);
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->numEdges = 0;
    
    // Initialize vertices
    graph->vertexSet = malloc(sizeof(Vertex) * numVertices);
    for (int i = 0; i < numVertices; ++i)
    {
        Vertex* vertex = &graph->vertexSet[i];
        vertex->isVisited = 0;
        vertex->label = i;
        vertex->neighbors = NULL;
        vertex->numNeighbors = 0;
    }
    
    // Create edges
    while (fgets(buffer, sizeof buffer, file) != NULL)
    {
        char* begin = buffer;
        char* end = NULL;
        
        // Get vertex
        int i = (int) strtol(begin, &end, 10);
        Vertex* vertex = &graph->vertexSet[i];
        begin = end;
        
        // Create edges
        for (int i = (int) strtol(begin, &end, 10);
            end != begin;
            i = (int) strtol(begin, &end, 10))
        {
            Vertex* neighbor = &graph->vertexSet[i];
            if (!isAdjacent(vertex, neighbor))
            {
                createEdge(vertex, neighbor);
                ++(graph->numEdges);
            }
            begin = end;
        }
    }
    fclose(file);
    
    return graph;
}

/**
 * Frees all memory allocated for a graph and the graph itself.
 * @param graph
 */
void freeGraph(Graph* graph)
{
    for (int i = 0; i < graph->numVertices; ++i)
    {
        free(graph->vertexSet[i].neighbors);
    }
    free(graph->vertexSet);
    free(graph);
}

/**
 * Prints the vertex count, edge count, and adjacency list for each vertex.
 * @param graph
 */
void printGraph(Graph* graph)
{
    printf("Vertex count: %d\n", graph->numVertices);
    printf("Edge count: %d\n", graph->numEdges);
    for (int i = 0; i < graph->numVertices; ++i)
    {
        Vertex* vertex = &graph->vertexSet[i];
        printf("%d :", vertex->label);
        for (int j = 0; j < vertex->numNeighbors; ++j)
        {
            printf(" %d", vertex->neighbors[j]->label);
        }
        printf("\n");
    }
}
