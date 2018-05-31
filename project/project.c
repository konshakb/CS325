



/**************************************************************
 *Author Bryan Konshak   5/14/2018		Algorithms
 * ************************************************************************/
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
	printf("%f\n", squareroot);
	int nearest;
	nearest = round(squareroot);
}

int main(int argc, char* argv[])
{
	int x =0, y = 10, a = 7, b=3;
	int near;
	near = nearestint(x, y, a, b);
	printf("Three? %d\n", near);

}
