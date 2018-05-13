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
    char* rivalries[25];
};

void initWrestlers(struct wrestler* Wrestlers, int num);
void setRival(struct wrestler* Wrestlers, int num, char* rival1, char* rival2);

int main(int argc, char* argv[]){
    FILE* inputFile=NULL;
    int i,j, num;
    struct wrestler* Wrestlers;
    char input1[25];
    char input2[25];

    //Open files
    if((inputFile=fopen(argv[1],"r"))==NULL){
        perror("Input file won't open");
        return(1);
    }
    else{
        fscanf(inputFile, "%d\n", &num);
        Wrestlers = malloc(sizeof(struct wrestler) * num);
        initWrestlers(Wrestlers,num); 
        for(i=0;i<num;i++){
            fscanf(inputFile,"%s\n",&input1);
            strcpy(Wrestlers[i].name, input1);
            
        }
        fscanf(inputFile,"%d\n", &num);
        for(i=0;i<num;i++){
            fscanf(inputFile,"%s %s\n",&input1,&input2);
            setRival(Wrestlers,num,input1,input2);
           
        }
        for(i=0;i<num;i++){
            printf("\nWrestler: %s\n",Wrestlers[i].name);
            for(j=0;j< Wrestlers[i].numR;j++){
                printf("Rival: %s\n",Wrestlers[i].rivalries[j]);
            }
        }   
       
        fclose(inputFile);              //close files

    }

return 0;
}

/*****************************************************
 * initWrestlers()
 *
 * ***************************************************/

void initWrestlers(struct wrestler* Wrestlers,int num){
    int i,j,k;
    for(i=0;i<num;i++){
        Wrestlers[i].name=malloc(sizeof(char)*STRING_SIZE);
        for(j=0;j<STRING_SIZE;j++){
            Wrestlers[i].name[j]='\0';
        }
        Wrestlers[i].color='w';
        Wrestlers[i].typeW=malloc(sizeof(char)*10);
        Wrestlers[i].numR=0;
        for(j=0;j<STRING_SIZE;j++){
            Wrestlers[i].rivalries[j]=NULL;
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
        if(strcmp(Wrestlers[i].name, rival1)==0){
            numrivals=Wrestlers[i].numR;
            Wrestlers[i].rivalries[numrivals]=malloc(sizeof(char)*STRING_SIZE);
            strcpy(Wrestlers[i].rivalries[numrivals],rival2);
            Wrestlers[i].numR++;
        }
        if(strcmp(Wrestlers[i].name,rival2)==0){
            numrivals=Wrestlers[i].numR;
            Wrestlers[i].rivalries[numrivals]=malloc(sizeof(char)*STRING_SIZE);
            strcpy(Wrestlers[i].rivalries[numrivals],rival1);
            Wrestlers[i].numR++;
        }
    }

}
