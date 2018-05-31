


/**************************************************************
 *Author Bryan Konshak   4/8/2018		Algorithms
 * ************************************************************************/
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <algorithm>
#include<bits/stdc++.h>
using namespace std;

void error(const char *msg) { perror(msg); exit(0); } // Error function used for reporting issues
struct wrestler{
	char *name;
//	string name;
	int bad ;




};
/*
void addEdge(vector<int> adj[], int u, int v)
{
	adj[u].push_back(v);
	adj[v].push_back(u);
}
void add(vector<wrestler> adj[], char *u, char *v)
{
}


void printGraph(vector<int> adj[], int V)
{
	int i = 0;
	for (int v = 0; v < V; ++v)
	{
		cout << "\n Adjacency list of vertex "
			<< v << "\n head ";
		//	for (auto x : adj[v])
		for (i=0; i<adj[v].size(); i++)
			cout << "-> " << adj[v][i];
		printf("\n");
	}
}
*/

int main(int argc, char* argv[])
{
	if (argc != 2) { fprintf(stderr,"USAGE: %s filename\n", argv[0]); exit(0); } // Check usage & args
	FILE* fp = fopen(argv[1], "r");
	char arr[10000];
	char*ptr;
	int isn = 1;
	int wrestle=1;
	int n ;
	int i = 0;
	int j = 0;
	int K = 500;
	int m = 0;
	int p = 0;
	vector<int> graph[5];
	char edgeOne[1000];
	int vone;
	int vtwo;


	char edgeTwo[1000];
	char copies[1000];
//	vector<wrestler> wrestlers(K);
//	vector<wrestler> wrestlers2[K];
//	wrestler test;
	//test.name="hi";
//	test.bad=1;
	//	wrestlers2.push_back(test);
//	vector<char*> wrestler3[20];
	char strings[1000][1000];
	//	wrestlers2[0].bad=1;
	while ((ptr= fgets(arr, sizeof arr, fp)) !=NULL) //read each line
	{
		ptr = strtok(arr , " ");
		while(ptr)
		{
			if(isn)
			{
				n = strtol(ptr, NULL, 10);//n value on odd lines
				//wrestlers.resize[n];
				//					printf("Only once\n");
				//				printf(" %s", ptr);
				//				printf("%d n\n", n);
				ptr = strtok(NULL, " ");
				isn=0;
			}
			else
			{
				if(wrestle)
				{
					char *pos;

					strcpy(copies, ptr);
					strcpy(strings[j],copies);

					printf(" %d\n", j);
					if((pos=strchr(strings[j], '\n')) != NULL)
						*pos = '\0';
					
			//		strings[j].erase(remove(strings[j].begin(), strings[j].end(), '\n'), strings[j].end());
					//	wrestlers[j].bad=0;
					//	wrestlers[j].bad[j]=1;

					//printf(" %s", wrestlers[j].name);
					cout << "   " << strings[j];
					printf("   %d\n", j);
					if(j>0)
					printf("   %s", strings[j-1]);
					if(j>1)
					printf("   %s", strings[j-1]);
					if(j>2)
					printf("   %s", strings[j-1]);
					if(j>3)
					printf("   %s", strings[j-1]);
					if(j>4)
					printf("   %s", strings[j-1]);

					
//					printf(" %d", wrestlers[j].bad);
					j++;
					ptr = strtok(NULL, " ");
				}
				else
				{
						cout << edgeOne << strings[0]<<strings[1]<<strings[2] << "test" << endl;
					if(m%2==0)
					{
						printf("%d n here \n", n);
						//edgeOne = ptr;
						printf(" %d\n", j);
						strcpy(edgeOne, ptr);
						cout << edgeOne << strings[0]<<strings[1]<<strings[2] << "test" << endl;
						for(p=0;p<n;p++)
						{
							
							if(strcmp(edgeOne, strings[p])==0)
							{
								vone=p;
								printf("%d in the loop\n", vone);
								break;
							}
						}
					}
					else if(m%2==1)
					{
			//			edgeTwo = ptr;
			                        char *pos;			
						strcpy(edgeTwo, ptr);
					if((pos=strchr(edgeTwo, '\n')) != NULL)
						*pos = '\0';
					//	edgeTwo.erase(remove(edgeTwo.begin(), edgeTwo.end(), '\n'), edgeTwo.end());
						cout <<"hi there before loop! "<< edgeOne << "   " << edgeTwo << "  again" <<endl;
						for(p=0;p<n;p++)
						{
							
							cout <<"hi there! "<< edgeTwo << "   " << strings[p] << "  again p"<< p <<endl;
							//if(edgeTwo==strings[p])
							if(strcmp(edgeTwo, strings[p])==0)
							{
								vtwo=p;
								printf("%d hi there\n", vtwo);
								break;
							}
						}
//						addEdge(graph, vone, vtwo);
						//				add(wrestlers, edgeOne, edgeTwo);
					}
					m++;

					//		printf(" %s", ptr);
					ptr = strtok(NULL, " ");
				}

			}



		}
		i++;
		if(i==n+1)
		{
			printf("%s %s after the setup.", strings[0], strings[1]);
			i=0;
			isn=1;
			wrestle=0;
		}
	}



/*
	int V = 5;
	vector<int> adj[V];
	addEdge(adj, 0, 1);
	addEdge(adj, 0, 4);
	addEdge(adj, 1, 2);
	addEdge(adj, 1, 3);
	addEdge(adj,  1, 4);
	addEdge(adj, 2, 3);
	addEdge(adj, 3, 4);
	printGraph(adj, V);
	printGraph(graph, 5);
*/







	//	test= readInts(mergeArray, "data.txt");
}


