#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/*********************************************
 * David White
 * CS325_400_S2018
 * HW2-stoogesort
 *********************************************/
int *parseString(char* lineIn,int* num);
void printArray(int* arrIn,int num,FILE* outputFile);
void stoogesort(int* arrIn,int low, int high);
void swap(int* arrIn, int num1, int num2);

int main(){
    int num=-99;
    char* line;
    size_t len=0;
    FILE* inputFile=NULL;
    FILE* outputFile=NULL;
    int* newarr=NULL;
    printf("********************\nHW2-stoogesort\nDavid White\nCS325_400_S2018\n"
            "********************\n");
    if((inputFile=fopen("data.txt","r"))==NULL){
        perror("data.txt won't open");
        return(1);
    }
    if((outputFile=fopen("stooge.out","w"))==NULL){
        perror("stooge.out won't open");
        return(1);
    }
    else{
        while(getline(&line, &len, inputFile) != -1){
            newarr = parseString(line,&num);
            if(newarr!=NULL){
                printf("Starting sort\n");
                stoogesort(newarr,0,num-1);
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
 * swap()
 *
 * *******************************************/
void swap(int*arrIn, int num1, int num2){
    int temp;
    printf("swap:%i %i\n",arrIn[num1],arrIn[num2]);
    temp = arrIn[num1];
    arrIn[num1]= arrIn[num2];
    arrIn[num2]= temp;
}

/*********************************************
 * stoogesort()
 *
 *********************************************/
void stoogesort(int* arrIn, int low, int high){
    int m;
    int n=high-low+1;
    if((n==2)&& arrIn[low]>arrIn[high])
        swap(arrIn,low,high);
    else if(n >2){
        m=(int)ceil( (2.0 * (float)n ) / 3.0)  ;
        stoogesort(arrIn, low, low + m - 1);
        stoogesort(arrIn, high - m + 1, high);
        stoogesort(arrIn, low, low + m - 1);
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
