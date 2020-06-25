#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TABLE_SIZE 10000
#define HASHSIZE 8191
#define MAX_LENGTH 256

//ハッシュのリストのノード
typedef struct node {
    char key[MAX_LENGTH];
    int value;
    struct node *next;
} NODE, *NODEP;

//使う関数
int f_index(NODEP list, char *key);
NODEP get_element(NODEP list, int fd);
void insert(char *key);
void display();
void init_table();

//ハッシュ表のstruct
typedef struct hashtable {
    NODEP head;
    NODEP tail;
} HTB,*HTBP;

//ハッシュ表
HTBP htable ;

//hash関数
int hash(char *str){
    int h = 0, n;
    for(n=0;str[n]!='\0';n++){
        h = (h*137+str[n]) % HASHSIZE;
    }
    return h;
}

//hashtableにノードをインサートする
void insert(char *key){
    int index = hash(key);
    int fd = 0;
    NODEP list = (NODEP) htable[index].head;
    NODEP item = (NODEP) malloc(sizeof(struct node));
    item->value = 1;
    //item->key = malloc(sizeof(struct node));
    strcpy(item->key, key);
    item->next = NULL;
    
    if(list == NULL){
        htable[index].head = item;
        htable[index].tail = item;
    } else {
        fd = f_index(list,key);
        if(fd == -1){
            /*
			 リストにキーがない場合
			*/
            htable[index].tail->next = item;
            htable[index].tail = item;
        } else {
            /*
			 リストにキーがある場合
			*/
            NODEP element = get_element(list, fd);
			element->value += 1;
        }
    }
}

//キーをリストに探す
int f_index(NODEP list, char *key){
    int rec = 0;
    NODEP temp = list;
    while(temp != NULL){
        if(strcmp(temp->key, key) ==0){
            return rec;
        }
        temp = temp->next;
        rec++;
    }
    return -1;
}


NODEP get_element(NODEP list, int fd){
    int i = 0;
    NODEP temp = list;
    while(i!=fd){
        temp = temp->next;
        i++;
    }
    return temp;
}

//ハッシュ表をプリントする
void display(){
    int i = 0, j = 1;
    for(i=0; i< TABLE_SIZE; i++){
        struct node *temp =  htable[i].head;
        if(temp != NULL){
            while(temp !=NULL){
                printf("%d: WORD: %s, COUNT: %d\n",j,temp->key,temp->value);
                temp = temp->next;
                j++;
            }
        }
    }
}

void init_table(){
	int i = 0;
	for (i = 0; i < TABLE_SIZE; i++){
		htable[i].head = NULL;
		htable[i].tail = NULL;
	}
}

int main(void){
    char *p;
    char *p1;
    int i = 0;
    htable = (HTBP) malloc(TABLE_SIZE * sizeof(HTB));
	init_table();

    //ファイルを開く
    FILE *fp = fopen("Alice.txt", "r"); /* Open Alice.txt file*/
    char moji[MAX_LENGTH]; 
    if(fp == NULL) {
        printf("Can not open the file.");
        return -1;
    } 
    while(fscanf(fp, "%s", moji) != EOF) insert(moji);
    display();
}