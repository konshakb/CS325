#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
/*********************************************
 * David White
 * CS325_400_S2018
 * tsp_nn.c
 *********************************************/
struct bag {
    int size;
    struct vertex* head;
};

struct vertex{
    int index;
    int x;
    int y;
    int connections;
    struct vertex* next;
};


void init_bag(struct bag* in);
void init_vert(struct vertex* in);
struct vertex* new_vert( int index, int x, int y);
void add_to_bag(struct bag* bag_in, struct vertex* vert_in);
void print_bag(struct bag* bag_in);
void delete_bag(struct bag* bag_in);

int main(int argc, char *argv[]){
    struct bag* TSP;
    int num=-99;
    FILE* inputFile=NULL;
    int index,x,y;
    int* outputFile=NULL;
    struct vertex* newVert=NULL;
 
    //Open files
    if((inputFile=fopen(argv[1],"r"))==NULL){
        perror("Input file won't open");
        return(1);
    }
    else{
        TSP=malloc(sizeof(struct bag));
        init_bag(TSP);
        while(fscanf(inputFile, "%d %d %d\n", &index,&x,&y) != EOF){
            newVert = new_vert(index,x,y);
            add_to_bag(TSP, newVert); 
       }
        print_bag(TSP);
        fclose(inputFile);              //close files

    }

return 0;
}

/*****************************************
 * init_bag
 * 
 * **************************************/
void init_bag(struct bag* in){
    in->size=0;
    in->head=new_vert(-99,-99,-99); 
}

/****************************************
 * init_vert
 * 
 * *************************************/
void init_vert(struct vertex* in){
    in->index=-99;
    in->x=-99;
    in->y=-99;
    in->connections=0;
    in->next=NULL;
}

/*****************************************
 * new_vert
 *
 * ***************************************/
struct vertex* new_vert( int index, int x, int y){
   struct vertex* vert=malloc(sizeof(struct vertex));
   init_vert(vert);
   vert->index=index;
   vert->x=x;
   vert->y=y;
   return vert;
}

/*****************************************
 * add_to_bag
 *
 * ***************************************/
void add_to_bag(struct bag* bag_in, struct vertex* vert_in){
    if(bag_in->size==0){
        bag_in->head->next = vert_in;
        bag_in->size++;
    }   
    else{
        vert_in->next=bag_in->head->next;
        bag_in->head->next=vert_in;
        bag_in->size++;
    }
}

/************************************************
 * print_bag
 *
 * *********************************************/
void print_bag(struct bag* bag_in){
    struct vertex* current = NULL;
    current = bag_in->head->next;
    while(current!=NULL){
        printf("%d %d %d\n", current->index, current->x, current->y);
        current = current->next;
    }
}
/************************************************
 * delete_bag
 *
 * *********************************************/
void delete_bag(struct bag* bag_in){
   struct vertex* current =NULL;
   current= bag_in->head->next;
   while(bag_in->head->next!=NULL){
       bag_in->head->next=current->next;
       current->next = NULL;
       free(current);
   }
   free(bag_in->head);
   free(bag_in);
}
