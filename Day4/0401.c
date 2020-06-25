#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LENGTH 128

int order = 1; // the order of the node 
typedef char DATA;

//二分木のノードのstruct
struct node {
    DATA d[MAX_LENGTH ];
    struct node *left; //左部分木
    struct node *right; // 右部分木
    int count;
};

typedef struct node NODE; //ノード
typedef NODE *BTREE;//２分木

BTREE allocNode(DATA *x) {
    BTREE p;
    p = (BTREE)malloc(sizeof(NODE));
    strcpy(p->d,x);
    p->left = p->right = NULL;
    p->count = 1;
    return p;
}

//木にノードをインサートする
BTREE insertNode(BTREE node, DATA *x){
    BTREE p = node;
    if(p == NULL) { //insert to root
        p = allocNode(x);
        return p;
    }
    if (strcmp(x, p->d) == 0) {
        //process in the equal case
        p->count += 1;
    } else if(strcmp(x,p->d) <0) {// insert into left subtree
        p->left = insertNode(p->left,x); // Recursion
    } else { // insert into right subtree
        p->right = insertNode(p->right,x); // Recursion
    }
    return p;
}

void printBtree(BTREE p){
    if(p!=NULL){
        printBtree(p->left); //Left subtree;
        printf("%d: WORD: %s, COUNT: %d\n",order++,p->d, p->count);
        printBtree(p->right); //Right substree
    }
}

void freeBtree(BTREE p){
    if(p!=NULL){
        freeBtree(p->left); //Left subtree
        freeBtree(p->right); //Right substree
        free(p);
    }
}

int main(void){
    BTREE btr = NULL;
    int i = 0;
    DATA *p;
    DATA *p1;
    DATA *p2;
    FILE *fp = fopen("Alice.txt", "r"); /* Open Alice.txt file*/
    char moji[MAX_LENGTH]; 
    if(fp == NULL) {
        printf("Can not open the file.");
        return -1;
    } 
 
    while(fscanf(fp, "%s", moji) != EOF) btr = insertNode(btr, moji);
    printBtree(btr);
    freeBtree(btr);
    return 0;
}