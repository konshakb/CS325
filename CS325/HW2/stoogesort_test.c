#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <limits.h>
/************************************************
 * David White
 * CS325_400_S2018
 * HW1-Mergesort
 * *********************************************/


int *parseString(char* lineIn,int* num);
void printArray(int* arrIn,int num,FILE* outputFile);
void stoogesort(int* arrIn,int low, int high);
void swap(int* arrIn, int num1, int num2);

int main(int argc, char* argv[]){
    int num=atoi(argv[1]);
    clock_t t;
//    char* line;
//    size_t len=0;
//    FILE* inputFile=NULL;
    FILE* outputFile=NULL;
    int* newarr=NULL;
    float times[3];
    int i;
    float total_time;
    newarr=(int*) malloc(sizeof(int) * num);
    srand(time(0));

    printf("********************\nHW1-Mergesort\nDavid White\nCS325_400_S2018\n"
            "********************\n");
/*    if((inputFile=fopen("data.txt","r"))==NULL){
        perror("data.txt won't open");
        return(1);
    }
*/
    printf("Creating %d random numbers\n",num);
    for(i=0;i<num;i++){
        newarr[i]=rand()%10000;
    }    

    if((outputFile=fopen("ss_test.out","w"))==NULL){
        perror("ss_test.out won't open");
        return(1);
    }
    else{
//        while(getline(&line, &len, inputFile) != -1){
//            newarr = parseString(line,&num);
            if(newarr!=NULL){
                printf("Starting sort\n");
                for(i=0;i<3;i++){
                    t=clock();
                    stoogesort(newarr,0,num-1);
                    t=clock()-t;
                    double time=((double)t)/CLOCKS_PER_SEC; 
                    times[i]=time;
                    total_time+=time;
                }
                
                for(i=0;i<3;i++){
                    printf("time: %f \n",times[i]);
                }
                printf("Sort Complete: %f\n",total_time/3.0);
                
                printArray(newarr,num,outputFile);

                free(newarr);
                newarr=NULL;
            }
//        }
//        fclose(inputFile);
        fclose(outputFile);
    }

return 0;
}

/*********************************************
 ** swap()
 **
 *********************************************/
void swap(int*arrIn, int num1, int num2){
    int temp;
    temp = arrIn[num1];
    arrIn[num1]= arrIn[num2];
    arrIn[num2]= temp;
}

/*********************************************
 ** stoogesort()
 **
 **********************************************/
void stoogesort(int* arrIn, int low, int high){
    int m;
    int n=high-low+1;
    if((n==2)&& arrIn[low]>arrIn[high])
        swap(arrIn,low,high);
    else if(n >2){
        m=(int)ceil( (2.0 * (float)n ) / 3.0);
        stoogesort(arrIn, low, low + m - 1); 
        stoogesort(arrIn, high - m + 1, high);
        stoogesort(arrIn, low, low + m - 1); 
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
