


/**************************************************************
 *Author Bryan Konshak   5/14/2018		Algorithms
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
#include <math.h>
//#include <algorithm>
//#include<bits/stdc++.h>
//using namespace std;

void error(const char *msg) { perror(msg); exit(0); } // Error function used for reporting issues
/*main function pulls lines from file and parses them into wrestler arrays*/
int nearestint(int x, int x2, int y, int y2)
{
	double squareroot=sqrt(((x-x2)*(x-x2))+((y-y2)*(y-y2)));
	//	printf("%f\n", squareroot);
	int nearest;
	nearest = round(squareroot);
}
int nearestint2(struct Vertex one, Vertex two)
{
	nearestint(one.x, two.x, one.y, two.y);
}
//using namespace std;

struct wrestler{
	char *name;
	//	string name;
	int bad ;

};
/*main function pulls lines from file and parses them into wrestler arrays*/
int main(int argc, char* argv[])
{
	if (argc != 2) { fprintf(stderr,"USAGE: %s filename\n", argv[0]); exit(0); } // Check usage & args
	FILE* fp = fopen(argv[1], "r");

	int var1 = 5, var2 = 10, var3 = 15, var4 = 20;
	int answer;
	answer = nearestint(var1, var2, var3, var4);
	printf("Answer is: %d\n", answer);

	char arr[10000];
	char*ptr;
	int isn = 1;
	int wrestle=1;
	int n ;
	int i = 0;
	int j = 0;
	//	int K = 500;
	int m = 0;
	int p = 0;
	//	vector<int> graph[5];
	char edgeOne[1000];
	int vone;
	int vtwo;
	char edgeTwo[1000];
	char copies[1000];
	Graph* graphs;
	Vertex* vertex ;
	int result;
	int count = 0;
	int number[200000];
	int x[200000];
	int y[200000];
	char c;
	if(fp)
	{
		for (c = getc(fp); c != EOF; c = getc(fp))
			if (c=='\n')
				count = count + 1;
		fclose(fp);
		printf("Line count: %d\n", count);
	}
	else(printf("cannot open\n"));

	fp = fopen(argv[1], "r");
	if(fp)
	{
		char strings[1000][1000];
		//	wrestlers2[0].bad=1;
		while ((ptr= fgets(arr, sizeof arr, fp)) !=NULL) //read each line
		{
			ptr = strtok(arr , " ");
			while(ptr)
			{
				n = strtol(ptr, NULL, 10);//n values
				if(i%3==0)
				{
					printf("N:  %d \n", n);
					number[j]=n;
				}
				if(i%3==1)
				{
					printf("X:  %d \n", n);
					x[j]=n;
				}
				if(i%3==2)
				{
					printf("Y:  %d \n", n);
					y[j]=n;
					j++;
				}
				ptr = strtok(NULL, " ");
				i++;
			}

fclose(fp);
}
else{printf("File does not exist\n");}
for(i=0;i<count;i++)
{
	printf("%d %d %d\n", number[i], x[i], y[i]);
}
printf("%d\n", count);
graphs=initGraph(count, x, y);
printf("Ultimate test: x is %d\n", graphs->vertexSet[count-1].y);
for(i=0;i<count;i++)
{
	printf("%d %d %d\n", graphs->vertexSet[i].label, graphs->vertexSet[i].x, graphs->vertexSet[i].y);
}
int lowest=10000000;
int nearest=0;
int solve = 0;
j=1;
int islow=0;
int total=0;

graphs->vertexSet[0].isVisited=1;
struct Vertex temp;
for(j=0;j<count;j++)
{
	printf("j = %d i = %d\n", j, i);
	for (i=j+1; i<count; i++)
	{
		//	if (graphs->vertexSet[i].isVisited!=1)
		{
			//	printf("i: %d\n", i);
			solve = nearestint2(graphs->vertexSet[j], graphs->vertexSet[i]);
			//	printf("i: %d\n", i);
			if (solve < lowest)
			{
				//	printf("solve: %d  lowest: %d\n", solve, lowest);
				lowest = solve;
				//	printf("solve: %d  lowest: %d\n", solve, lowest);
				nearest = i;
				graphs->vertexSet[i].isVisited=1;
				islow=1;
			}
		}
	}
	if (islow)
	{
		total+=lowest;
		printf("Total: %d: \n", total);
		temp=graphs->vertexSet[nearest];
		graphs->vertexSet[nearest]=graphs->vertexSet[j+1];
		graphs->vertexSet[j+1]=temp;
		islow=0;
	}
//	printf("nearest = %d and i = %d\n", lowest, nearest);
	lowest=10000000;
	nearest=0;
}
for(i=0;i<count;i++)
{
	//printf("%d %d %d\n", graphs->vertexSet[i].label, graphs->vertexSet[i].x, graphs->vertexSet[i].y);
}

//printf("nearest = %d and i = %d\n", lowest, nearest);

}


