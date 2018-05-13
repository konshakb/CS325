#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
/*********************************************
 * David White
 * CS325_400_S2018
 * HW5-babyVheels.c
 *********************************************/

//CONSTANTS
#define STRING_SIZE 25

struct wrestler{
    char* name;
    char color;
    char* typeW;
    int numR;
    int rivalries[25];
};
int wrestlerBFS(struct wrestler* G, int v, int e, int s);
void initWrestlers(struct wrestler* Wrestlers, int num);
void setRival(struct wrestler* Wrestlers, int num, char* rival1, char* rival2);

int main(int argc, char* argv[]){
    FILE* inputFile=NULL;
    int i,j, num, edges, r_name,possible;
    struct wrestler* Wrestlers;
    char input1[STRING_SIZE];
    char input2[STRING_SIZE];

    //Open files
    if((inputFile=fopen(argv[1],"r"))==NULL){
        perror("Input file won't open");
        return(1);
    }
    else{
        fscanf(inputFile, "%d\n", &num);
        Wrestlers = malloc(sizeof(struct wrestler) * num);
        initWrestlers(Wrestlers,num); 
        //import from files
        for(i=0;i<num;i++){
            fscanf(inputFile,"%s\n",&input1);
            strcpy(Wrestlers[i].name, input1);
            
        }
        fscanf(inputFile,"%d\n", &edges);
        for(i=0;i<edges;i++){
            fscanf(inputFile,"%s %s\n",&input1,&input2);
            setRival(Wrestlers,num,input1,input2);
           
        }
        //test if to designate heels and babyface
        possible=wrestlerBFS(Wrestlers,num, edges, 0);
        if(possible){
            //check to see if vertexes couldn't be reached
            for(int i=0;i<num;i++){
                if(strcmp(Wrestlers[i].typeW,"empty")==0){
                    possible=wrestlerBFS(Wrestlers, num, edges, i );       
                }
            }
            //print Babyfaces and heels
            printf("Heels\n");
            for(j=0;j<num;j++){
                if(strcmp(Wrestlers[j].typeW,"Heel")==0)
                    printf("%s ",Wrestlers[j].name);
                }
                printf("\n\nBabyfaces\n");
                for(j=0;j<num;j++){
                    if(strcmp(Wrestlers[j].typeW,"Babyface")==0)
                        printf("%s ",Wrestlers[j].name);
                }
                printf("\n");

        }
        else
            printf("Not possible\n");

        fclose(inputFile);          //close files
        
        free(Wrestlers);
    }

return 0;
}

/*****************************************************
 * initWrestlers()
 *
 * ***************************************************/

void initWrestlers(struct wrestler* Wrestlers,int num){
    int i,j,k;
    //initialize wrestler struct
    for(i=0;i<num;i++){
        Wrestlers[i].name=malloc(sizeof(char)*STRING_SIZE);
        for(j=0;j<STRING_SIZE;j++){
            Wrestlers[i].name[j]='\0';
        }
        Wrestlers[i].color='w';
        Wrestlers[i].typeW=malloc(sizeof(char)*10);
        strcpy(Wrestlers[i].typeW,"empty");
        Wrestlers[i].numR=0;
        for(j=0;j<STRING_SIZE;j++){
            Wrestlers[i].rivalries[j]=-99;
        }
    }

}

/********************************************************
 *setRival()
 *
 * ******************************************************/
void setRival(struct wrestler* Wrestlers, int num, char* rival1, char* rival2){
    int i,j, numrivals;
    for(i=0;i<num;i++){
        j=0;
        while(strcmp(Wrestlers[j].name, rival2)!=0)
            j++;    
        //look for match to assign index to rivals
        if(strcmp(Wrestlers[i].name, rival1)==0){
            numrivals=Wrestlers[i].numR;
            Wrestlers[i].rivalries[numrivals]=j;
            Wrestlers[i].numR++;
            numrivals=Wrestlers[j].numR;
            Wrestlers[j].rivalries[numrivals]=i;
            Wrestlers[j].numR++;
        }
    }

}

/**********************************************************
 *wrestlers_BFS()
 *
 * ********************************************************/
int wrestlerBFS(struct wrestler* G, int vert, int edge,int s){
    int i,u,v;
    int next_in_q=0;
    int front_q=0;
    int possible = 1;
    int queue[100];
     
    //initialize queue
    for (i=0;i<100;i++){
        queue[i]=-99;
    }
    //must be more edges than verts
    if(edge < vert)
        possible = 1;
    //initialize start
    G[s].color='w'; 
    strcpy(G[s].typeW,"Babyface");
    queue[next_in_q++]=s;
    while(front_q < next_in_q && possible==1){
        u=queue[front_q++];         //assign queue
        for(i=0;i<G[u].numR;i++){   //check status of graph
            v=G[u].rivalries[i];
            
            if ((strcmp(G[v].typeW, "empty")==0) && (strcmp(G[u].typeW,"empty") == 0)){    
                strcpy(G[u].typeW,"Babyface");
                strcpy(G[v].typeW,"Heel");
            }
            
            else if((strcmp(G[v].typeW, "empty")==0) && (strcmp(G[u].typeW,"Babyface") == 0)){
                strcpy(G[v].typeW,"Heel");
            }
            
            else if((strcmp(G[v].typeW,"empty")==0) && (strcmp(G[u].typeW,"Heel")==0)){
                strcpy(G[v].typeW,"Babyface");
            }
            
            else if(strcmp(G[v].typeW,G[u].typeW)==0)   //not possible if parent is the same
                possible=0;                             //as child
            
            if(G[v].color != 'b') {                     //add to queue if it isn't black
                queue[next_in_q++]=v;
            }
        }
        G[u].color='b';
    }
    return possible;

}
