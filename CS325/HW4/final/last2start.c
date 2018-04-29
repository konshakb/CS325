#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
/*********************************************
 * David White
 * CS325_400_S2018
 * HW4-last2start.c
 *********************************************/
struct activity{
    int index;
    int start;
    int finish;    
};

int* last2start(struct activity* in, int* num);
int* first2start(struct activity* in, int* num);
int mergesort(struct activity* in, int num);
void merge(struct activity* left, int l_length, struct activity* right, int r_length, struct activity* arrIn, int a_length);
void printArray(int* in, int num);

int main(){
    struct activity* Activities;
    int num=-99;
    FILE* inputFile=NULL;
    int i,st,sp,ind;
    int* last_list=NULL;

    //Open files
    if((inputFile=fopen("act.txt","r"))==NULL){
        perror("act.txt won't open");
        return(1);
    }
    else{
        while(fscanf(inputFile, "%d\n", &num) != EOF){
            Activities=malloc(sizeof(struct activity)*num); //array of structures to hold input
            for(i=0;i<num;i++){
                fscanf(inputFile,"%d %d %d\n",&Activities[i].index,&Activities[i].start,
                        &Activities[i].finish);
            }
            mergesort(Activities,num);      //sort activities in decending order
           /* for(i=0;i<num;i++){
                printf("%d s:%d f:%d\n",Activities[i].index, Activities[i].start, 
                        Activities[i].finish);fflush(stdout);
            }*/
            last_list=last2start(Activities,&num);      
            printArray(last_list,num);
            free(last_list);            //free dynamic memory
            last_list=NULL;
            free(Activities);
            Activities=NULL;
            
       }
        fclose(inputFile);              //close files

    }

return 0;
}

/**********************************
 * printArray()
 *
 * ********************************/
void printArray(int*in,int num){
    int i;
    for(i=num-1;i>=0;i--){
        if(i>0)
            fprintf(stdout,"%i, ",in[i]);
        else
            fprintf(stdout,"%i\n",in[i]);
    }
}

/**********************************
 * mergesort()
 *
 * ********************************/
int mergesort(struct activity* in,int length){
    int middle, i, right_count=0;
    struct activity* left=NULL;
    struct activity* right=NULL;
    if(length==1)
        return 0;
    else{
        middle=(length)/2;
        left= malloc(sizeof(struct activity) * middle);
        right= malloc(sizeof(struct activity)* (length-middle+1));
        for(i=0;i<middle;i++){
            left[i]=in[i];
        }
        for(i=middle;i<=length;i++){
            right[right_count] = in[i];
            right_count++;
        }
        mergesort(left, middle);
        mergesort(right,length-middle);
        merge(left,middle, right, length-middle, in, length);
        free(left);
        free(right);
    }
}

/***********************************
 * merge()
 *
 * *********************************/
void merge(struct activity* left, int l_length, struct activity* right, int r_length, struct activity* arrIn, int a_length){
    int i=0, j=0,k;
    for(k=0;k<a_length;k++){
        if((i<l_length) && ((j==r_length) || (left[i].start >= right[j].start))){
            arrIn[k] = left[i];
            i++;
        }
        else{
            arrIn[k]=right[j];
            j++;
        }
    }
}

/***********************************
 *first2start()
 *      I used pseudo code form CLRS 
 *      do first2start before I 
 *      made last2start to iron out 
 *      sorting issues.
 * *********************************/
int* first2start(struct activity* in, int* num){
    int* listOut=NULL;
    int i=1,m,k=0;
    listOut=malloc(sizeof(int) * (*num));
    listOut[0]=in[0].index;
    for(m=1;m<*num;m++){
        if(in[m].start>=in[k].finish){
            listOut[i++]=in[m].index;
            k=m;
        }            
    }    
    *num=i;
    return listOut;
}


/***************************************
 *last2start()
 *
 * ************************************/
 int* last2start(struct activity* in, int* num){
    int* listOut=NULL;
    int i=1,m,k=0;              //m index of activity to compare
                                //i index of output array
                                //k index of activity to compare
    listOut=malloc(sizeof(int) * (*num));
    listOut[0]=in[0].index;
    for(m=1;m<*num;m++){
        if(in[m].finish<=in[k].start){   //compares the current activity(k)
                                        //to the next activity(m) 
            listOut[i++]=in[m].index;   
            k=m;                        //set the current activity to the compatable activity
        }            
    }    
    *num=i;
    return listOut;
}
   
