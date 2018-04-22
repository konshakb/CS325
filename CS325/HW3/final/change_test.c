#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <time.h>

/*********************************************
 * David White
 * CS325_400_S2018
 * HW3-Change
 *********************************************/
int *parseString(char* lineIn,int* num);
void change(int* arrIn,int low, int high);
void printOutput(FILE* outputFile, int* change, int num, int*numCoins, 
        int* coinNum, int amount);
void makeChange(int* coins, int num, int val, int* numCoins, int* coinNum);

int main(int argc, char* argv[]){
    int num=10,amount=atoi(argv[1]);
    int change[]={1,3,10,15,25,7,29,20,23,19};
//    char* line;
//    size_t len=0;
//    FILE* inputFile=NULL;
//    FILE* outputFile=NULL;
//    int* change=NULL;           //array of denominations
    int* numCoins=NULL;         //array of number of coins for n
    int* coinNum=NULL;          //denominations for n
    int i;
    clock_t start,stop;
    double final,total;
    //Open files
/*    if((inputFile=fopen("amount.txt","r"))==NULL){
        perror("amount.txt won't open");
        return(1);
    }
    if((outputFile=fopen("change.out","w"))==NULL){
        perror("change.out won't open");
        return(1);
    }
    else{
        while(getline(&line, &len, inputFile) != -1){       //input line of denomination
            change = parseString(line,&num);                //parse the line
            fgets(line,10,inputFile);                       //input amount to calculate
     */
     //       amount=atoi(line);
     //       numCoins=malloc(sizeof(int)*amount+1);          //allocate space
     //       coinNum=malloc(sizeof(int)*amount+1);
            printf("%i,%i,",amount,num);
            for(i=0;i<3;i++){
                start=clock();
                makeChange(change,num,amount,numCoins,coinNum);
                stop=clock();
                final=((double)(stop-start))/(double)CLOCKS_PER_SEC;
                printf("%f,",final);
                total+=final;
            }
            printf("%f\n",total/3.0);
            
   //         printOutput(outputFile, change, num, numCoins, coinNum, amount);
   //         free(change);               //free data
            free(numCoins);
            free(coinNum);
  //      }
  //      fclose(inputFile);              //close files
  //      fclose(outputFile);

 //   }

return 0;
}
/*********************************************
 * makeChange()
 *
 * ******************************************/
void makeChange(int* coins, int num, int val,int* t, int* r){
        int i,j;
        t=malloc(sizeof(int)*val+1);
        r=malloc(sizeof(int)*val+1);
        t[0]=0;
        for(i=1;i<=val;i++){        //initilize data
            t[i]=INT_MAX-1;
            r[i]=-1;
        }
        for(j=0;j<num;j++){         //create table-number of denominations
            for(i=1;i<= val; i++){  //amount to be converted
                if(i>=coins[j]){    //if value is greater than coin value
                    if(t[i-coins[j]]+1 < t[i]){ 
                        t[i]=1+t[i-coins[j]];
                        r[i]=j;
                    }
                }
            }
        }
} 

/*********************************************
 * printInput()
 *
 * *******************************************/
void printOutput(FILE* outputFile, int* change, int num, int* numCoins, int* coinNum, int amount){
    int i,location;
    int* results=malloc(sizeof(int)*num);
    //print denominations
    for(i=0;i<num;i++){
        fprintf(outputFile,"%i ",change[i]);
    }
    //print amount
    fprintf(outputFile,"\n%i\n",amount);
    //print min coins for amount
    for(i=0;i<num;i++)              //initialize results array
        results[i]=0;
    location=amount;
    while(location!=0){
        i=coinNum[location];
        results[i]=results[i]+1;        //count the number of coins in each denominatoin
        location=location-change[i];
    }
    for(i=0;i<num;i++){
        fprintf(outputFile,"%i ",results[i]);
    }
    //print min number of coin for amount
    fprintf(outputFile,"\n%i\n",numCoins[amount]);
}

/*********************************************
 * parseString()
 *
 *********************************************/
int *parseString(char* lineIn,int* num){
    char* token;
    int i=0;
    int* dataout=(int*) malloc(100*sizeof(int));
    //extract # of data values in line
    token=strtok(lineIn," ");
    if(token!=NULL)
        dataout[i++]=atoi(token);
    while((token=strtok(NULL," "))!=NULL){        //extract values from file
        dataout[i++]=atoi(token);
    }
    *num=i;
    return dataout;
}

