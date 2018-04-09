#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/************************************************
 * David White
 * CS325_400_S2018
 * HW1-Mergesort
 * *********************************************/

/*Mergesort and merge are based off of the pseudo code in "Problem Solvin in Data Structures
 * & Algorithms Using C*/

int *parseString(char* lineIn,int* num);
void printArray(int* arrIn,int num,FILE* outputFile);
int mergesort(int* arrIn, int length);
void merge(int* left, int l_length,int* right, int r_length, int* arrIn, int a_length);

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
    if((outputFile=fopen("merge.out","w"))==NULL){
        perror("merge.out won't open");
        return(1);
    }
    else{
        while(getline(&line, &len, inputFile) != -1){
            newarr = parseString(line,&num);
            if(newarr!=NULL){
                printf("Starting sort\n");
                mergesort(newarr,num);
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

/***************************************
 * mergesort()
 *
 **************************************/
int mergesort(int* arrIn, int length){
    int middle,i,right_count=0;
    int* left=NULL;
    int* right=NULL;
    //If the array is length, no need to sort
    if(length==1)
        return 0;
    else{
        middle=(length)/2;                          //find the middle
        left=malloc(sizeof(int)*middle);            //create a temp left array
        right=malloc(sizeof(int)*(length-middle+1));  //create a temp right array
        for(i=0;i<middle;i++){                      //assign values to left array
            left[i] = arrIn[i];
        }
        for(i=middle;i<=length;i++){                //assign values to right array
            right[right_count] = arrIn[i];
            right_count++;
        }
        mergesort(left,middle);                     //recursive call left
        mergesort(right,length-middle);             //recursive call right
        merge(left,middle,right,length-middle,arrIn,length);    //merge halves
        free(left);                                 //free memory
        free(right);
    }
    return 0;
}

/********************************************
 * merge()
 *
 ********************************************/
void merge(int* left, int l_length,int* right, int r_length, int* arrIn, int a_length){
        int i=0,j=0,k;     //i count for left, j count for right, k count for sorted array    
        for(k=0;k<a_length;k++){                //for length of final array merge 
            //left counter less than left length
            //right array empty or left value less than right value
            if((i<l_length) && ((j==r_length) || (left[i] <= right[j]))){
                    arrIn[k]=left[i];
                    i++;
            }
            //everything else
            else{
                arrIn[k]=right[j];
                j++;
            }
        }
}

/********************************************
 * parseSring()
 *
 ********************************************/
int *parseString(char* lineIn,int* num){
    char* token;
    int i;
    int* dataout=NULL;
    //extract # of data values in line
    token=strtok(lineIn," ");
    *num=atoi(token);
    dataout=(int*)malloc(sizeof(int) * (*num));     //create array
    for(i=0;i<*num;i++){                            //extract values from file
        token=strtok(NULL," ");
        dataout[i]=atoi(token);
    }
    return dataout;
}

/*********************************************
 * printArray()
 *
 *********************************************/
void printArray(int* arrIn,int num, FILE* output){
    int i;
    for(i=0;i<num;i++){
        if((i%20==0) && (i != 0)){          //20 values per line
            fprintf(output,"%d\n",arrIn[i]);fflush(stdout);}    
        else if(i==num-1){                  //endline for last value
            fprintf(output,"%d\n",arrIn[i]);fflush(stdout);}
        else{                               //everything else
            fprintf(output,"%d ", arrIn[i]);fflush(stdout);}
    }
    
}
