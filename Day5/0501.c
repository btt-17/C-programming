#include<stdio.h>
#include<stdlib.h>
#include<time.h> 

//the coordinates's upper and lower
#define Upper 550.0
#define Lower 50.0

//N's upper and lower
#define N_Upper 100
#define N_Lower 3

// Postscript commands
#define color "setrgbcolor"
#define moveto "moveto"
#define lineto "lineto"
#define stroke "stroke"
#define closepath "closepath"
#define showpage "showpage"

// Open File
FILE * OpenFile(){
    /*create the "output.ps" file*/
    FILE * fp;
    char * filename = "output.ps"; 
    /*Write in file*/
    if((fp=fopen(filename,"w"))==NULL){
        printf("File open error\n");
        exit(1);
    }
    return fp;
}

// define the struct of the triangle
typedef struct Triangle {
    double x1, y1, x2, y2, x3, y3; // the coordinates
    double R, G, B; /*R: Red, G: Green, B: Blue*/
    struct Triangle *next;
} Tr, *TrP;

// create a new node
TrP NewNode(){
    TrP node = (TrP) malloc(sizeof(Tr));
    
    /*Get the values of the coordinates (x1,y1), (x2,y2), (x3,y3)randomly*/
    node->x1 = (double)(rand() / (double) RAND_MAX )* (Upper-Lower) + Lower;
    node->y1 = (double)(rand() / (double) RAND_MAX )* (Upper-Lower) + Lower;
    node->x2 = (double)(rand() / (double) RAND_MAX )* (Upper-Lower) + Lower;
    node->y2 = (double)(rand() / (double) RAND_MAX )* (Upper-Lower) + Lower;
    node->x3 = (double)(rand() / (double) RAND_MAX )* (Upper-Lower) + Lower;
    node->y3 = (double)(rand() / (double) RAND_MAX )* (Upper-Lower) + Lower;

    /*Get the values of the 3 colors red,green and blue randomly*/
    node->R = (double)(rand() / (double) RAND_MAX );
    node->G = (double)(rand() / (double) RAND_MAX );
    node->B = (double)(rand() / (double) RAND_MAX );

    node->next = NULL;
    return node;
}

// insert a node to a linear list
TrP insertNode(TrP parent, TrP n){
    if(parent == NULL){
        return n;
    } else {
        parent->next = insertNode(parent->next,n); //Recusrion
        return parent;
    }
}

// create a postscript file
void createPs(FILE *fp, TrP list){
    if(list != NULL){
        /* Write Postscript commands */
        fprintf(fp,"%.1f %.1f %.1f %s\n",list->R,list->G,list->B,color);
        fprintf(fp,"%.1f %.1f %s\n",list->x1,list->y1,moveto);
        fprintf(fp,"%.1f %.1f %s\n",list->x2,list->y2,lineto);
        fprintf(fp,"%.1f %.1f %s\n",list->x3,list->y3,lineto);
        fprintf(fp,"%s\n",closepath);
        fprintf(fp,"%s\n",stroke);

        //Recusrion
        createPs(fp,list->next);
    }
    fprintf(fp,"%s\n",showpage); 
    fclose(fp);
}

// print a list
void printList(TrP List){
    if(List!=NULL){
        printf("%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\n",
                  List->x1,List->y1,List->x2,List->y2,List->x3,List->y3, 
                  List->R, List->G,List->B);
        printList(List->next); //Recusrion
    }
}

// create a linear list with the number of node
TrP createList(TrP parent, int N){
    TrP n = NULL;
    for(int i = 0; i<N;i++){
        n = NewNode();
        parent = insertNode(parent,n);
    }
    return parent;
}

//free a list
void freeList(TrP list){
     if(list != NULL){
        freeList(list->next);
        free(list);
    }
}

//the main function
int main(void){
    TrP parent = NULL;
    /*Open the output file*/
    FILE *fp = OpenFile();

    srand((unsigned)time(NULL)); 
    /* Get N randomly */
    int N;
    N = (rand()%(N_Upper - N_Lower + 1 )) + 3;
    printf("N is %d\n", N);

    /*print the data*/
    printf("x1\t\ty1\t\tx2\t\ty2\t\tx3\t\ty3\t\tR\tG\tB\n");
    parent = createList(parent, N); // create the list
    printList(parent);

    /*create the postscript file*/
    createPs(fp,parent);

    freeList(parent);
    return 0;
}