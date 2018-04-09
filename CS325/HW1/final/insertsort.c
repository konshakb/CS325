#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*********************************************
 * David White
 * CS325_400_S2018
 * HW1-Insertsort
 *********************************************/
int *parseString(char* lineIn,int* num);
void printArray(int* arrIn,int num,FILE* outputFile);
void insertsort(int* arrIn, int length);

int main(){
    int num=-99;
    char* line;
    size_t len=0;
    FILE* inputFile=NULL;
    FILE* outputFile=NULL;
    int* newarr=NULL;
    printf("********************\nHW1-Mergesort\nDavid White\nCS325_400_S2018\n"
            "********************\n");
    if((inputFile=fopen("data.txt","r"))==NULL){
        perror("data.txt won't open");
        return(1);
    }
    if((outputFile=fopen("insert.out","w"))==NULL){
        perror("insert.out won't open");
        return(1);
    }
    else{
        while(getline(&line, &len, inputFile) != -1){
            newarr = parseString(line,&num);
            if(newarr!=NULL){
                printf("Starting sort\n");
                insertsort(newarr,num);
                printf("Sort Complete\n");
                printArray(newarr,num,outputFile);

                free(newarr);
                newarr=NULL;
            }
        }
        fclose(inputFile);
        fclose(outputFile);

    }

return 0;
}

/*********************************************
 * insertsort()
 *
 *********************************************/
void insertsort(int* arrIn, int length){
    int key,i,j;
    
    for(i=1;i<length;i++){
        key = arrIn[i];             //get key to compare
        j=i-1;
        while(j>=0 && arrIn[j] > key){  //compare key to values to the left
            arrIn[j+1] = arrIn[j];      //move value to right to make room for key
            j= j-1;                     //move to next to left
        }
        arrIn[j+1] = key;               //assign value to proper spot
    }
}

/*********************************************
 * parseString()
 *
 *********************************************/
int *parseString(char* lineIn,int* num){
    char* token;
    int i;
    int* dataout=NULL;
    //extract # of data values in line
    token=strtok(lineIn," ");
    *num=atoi(token);
    dataout=(int*)malloc(sizeof(int) * (*num)); //create array
    for(i=0;i<*num;i++){                        //extract values from file
        token=strtok(NULL," ");
        dataout[i]=atoi(token);
    }
    return dataout;
}

void printArray(int* arrIn,int num, FILE* output){
    int i;
    for(i=0;i<num;i++){
        if((i%20==0) && (i != 0)){              //20 values per line
            fprintf(output,"%d\n",arrIn[i]);fflush(stdout);}
        else if(i==num-1){                      //last value in array
            fprintf(output,"%d\n",arrIn[i]);fflush(stdout);}
        else{                                   //everything else
            fprintf(output,"%d ", arrIn[i]);fflush(stdout);}
    }
    
}
