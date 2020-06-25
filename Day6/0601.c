#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

//ファイルを開く
FILE* Openfile(char *filename){
    FILE* fp;
    fp = fopen(filename,"r");
    if(fp == NULL)
    {
        printf("Error in creating the file\n");
        exit(1);
    }
    return fp;
}

//ファイルのサイズ
long int size_file(char *filename) {
    FILE *fp = Openfile(filename);
    fpos_t sz;
    fseek(fp,0,SEEK_END);
    fgetpos(fp,&sz);
    fclose(fp);
    return sz;
}

//ファイルのデータをメモリに読み込む
void get_text(char *text, char *filename, int size){
    FILE *fp = Openfile(filename);
    int i = 0;
    fread(text,sizeof(char),size,fp);
    fclose(fp);
}

/* 力まかせ検索- Brute-Force */
void bf_search(char *text, char *pattern, int filesize){
    int n,len,i; 
    clock_t t1,t2;
    len = strlen(pattern);
    n = 0;
    t1 = clock();
    for (i = 0; i < filesize; i++) {
        if (strncmp(text + i, pattern, len) == 0) { 
            n++;
        }
    }
    t2 = clock();
    printf("力まかせ検索:\n");
    printf("\"%s\" found %d times!\n", pattern, n); 
    printf("Used CPU time: %.10f\n",(double)(t2 - t1) / CLOCKS_PER_SEC);
    printf("================================\n");
}

//文字列に文字の後ろ側の位置を求める
int last_ch(char*str, char c, int len){
    int i ;
    for(i = len-1; i>=0;i--){
        if(str[i] == c) return i;
    }
    return -1;
}

//skipテーブルを作成する
void skip_init(int *skip, char *pattern,char*text){
    int i ;
    int len = strlen(pattern);
    for(i = 0; i< 256; i++){
        skip[i] = len;
    }
    for(i=0; i< len;i++){
        skip[pattern[i]] = len-1-last_ch(pattern,pattern[i],len);
    }
}


/* Boyer-Moore 検索 */
void bm_search(char *text, char *pattern, int filesize){
    clock_t t3,t4;
    int len= strlen(pattern);
    int i = len-1, j = len-1, count = 0,m,d;

    int skip[256] = {0};

    skip_init(skip,pattern,text);

    t3 = clock();
    while(i < filesize){
        j = len-1;
        m = i;
        while(text[i] == pattern[j]){
            if(j==0) {
                count++;
                break;
            }
            j--;
            i--;
        } 
        i += skip[text[i]];
        if (i<= m) i = m +1;;    
    }
    t4 = clock();
    printf("Boyer-Moore検索:\n");
    printf("\"%s\" found %d times!\n", pattern,count); 
    printf("Used CPU time: %.10f\n",(double)(t4 - t3) / CLOCKS_PER_SEC);
    printf("================================\n");
}

int main(int argc, char *argv[]){
    char *text, *pattern, *filename;
    filename = argv[1];
    
    int filesize;
    filesize = size_file(filename);
   
    text = (char*)malloc(filesize * sizeof(char));
    get_text(text,filename,filesize);

    pattern = argv[2];

    //力まかせ検索
    bf_search(text,pattern,filesize);

    //boyer-moore検索
    bm_search(text,pattern,filesize);

    //メモリを解放する
    free(text);
    return 0;
}

/*
実行結果:

1. Test case 1:  文字を5回チェック 
thanhnoMacBook-Air:lesson6 thanhbui$ gcc -o 0601 0601.c
thanhnoMacBook-Air:lesson6 thanhbui$ ./0601 Alice.txt a
力まかせ検索:
"a" found 8153 times!
Used CPU time: 0.0012450000
================================
Boyer-Moore検索:
"a" found 8153 times!
Used CPU time: 0.0012140000
================================
thanhnoMacBook-Air:lesson6 thanhbui$ ./0601 Alice.txt a
力まかせ検索:
"a" found 8153 times!
Used CPU time: 0.0012680000
================================
Boyer-Moore検索:
"a" found 8153 times!
Used CPU time: 0.0017310000
================================

thanhnoMacBook-Air:lesson6 thanhbui$ ./0601 Alice.txt a
力まかせ検索:
"a" found 8153 times!
Used CPU time: 0.0014090000
================================
Boyer-Moore検索:
"a" found 8153 times!
Used CPU time: 0.0012170000
================================

thanhnoMacBook-Air:lesson6 thanhbui$ ./0601 Alice.txt a
力まかせ検索:
"a" found 8153 times!
Used CPU time: 0.0014530000
================================
Boyer-Moore検索:
"a" found 8153 times!
Used CPU time: 0.0014590000
================================

thanhnoMacBook-Air:lesson6 thanhbui$ ./0601 Alice.txt a
力まかせ検索:
"a" found 8153 times!
Used CPU time: 0.0017520000
================================
Boyer-Moore検索:
"a" found 8153 times!
Used CPU time: 0.0013720000
================================

2.Test case2: 長い文字列を5回チェック 
thanhnoMacBook-Air:lesson6 thanhbui$ ./0601 Alice.txt cucumber-frame
力まかせ検索:
"cucumber-frame" found 2 times!
Used CPU time: 0.0013260000
================================
Boyer-Moore検索:
"cucumber-frame" found 2 times!
Used CPU time: 0.0001660000
================================

thanhnoMacBook-Air:lesson6 thanhbui$ ./0601 Alice.txt cucumber-frame
力まかせ検索:
"cucumber-frame" found 2 times!
Used CPU time: 0.0011520000
================================
Boyer-Moore検索:
"cucumber-frame" found 2 times!
Used CPU time: 0.0001140000
================================

thanhnoMacBook-Air:lesson6 thanhbui$ ./0601 Alice.txt cucumber-frame
力まかせ検索:
"cucumber-frame" found 2 times!
Used CPU time: 0.0011740000
================================
Boyer-Moore検索:
"cucumber-frame" found 2 times!
Used CPU time: 0.0001420000
================================

thanhnoMacBook-Air:lesson6 thanhbui$ ./0601 Alice.txt cucumber-frame
力まかせ検索:
"cucumber-frame" found 2 times!
Used CPU time: 0.0011210000
================================
Boyer-Moore検索:
"cucumber-frame" found 2 times!
Used CPU time: 0.0001330000
================================

thanhnoMacBook-Air:lesson6 thanhbui$ ./0601 Alice.txt cucumber-frame
力まかせ検索:
"cucumber-frame" found 2 times!
Used CPU time: 0.0011970000
================================
Boyer-Moore検索:
"cucumber-frame" found 2 times!
Used CPU time: 0.0001300000
================================

3.Test case 3:  ファイルに出ない文字列  
thanhnoMacBook-Air:lesson6 thanhbui$ ./0601 Alice.txt fffffffff
力まかせ検索:
"fffffffff" found 0 times!
Used CPU time: 0.0012480000
================================
Boyer-Moore検索:
"fffffffff" found 0 times!
Used CPU time: 0.0001710000
================================
thanhnoMacBook-Air:lesson6 thanhbui$ ./0601 Alice.txt fffffffff
力まかせ検索:
"fffffffff" found 0 times!
Used CPU time: 0.0021470000
================================
Boyer-Moore検索:
"fffffffff" found 0 times!
Used CPU time: 0.0001860000
================================
thanhnoMacBook-Air:lesson6 thanhbui$ ./0601 Alice.txt fffffffff
力まかせ検索:
"fffffffff" found 0 times!
Used CPU time: 0.0013090000
================================
Boyer-Moore検索:
"fffffffff" found 0 times!
Used CPU time: 0.0002280000
================================
thanhnoMacBook-Air:lesson6 thanhbui$ ./0601 Alice.txt fffffffff
力まかせ検索:
"fffffffff" found 0 times!
Used CPU time: 0.0014960000
================================
Boyer-Moore検索:
"fffffffff" found 0 times!
Used CPU time: 0.0001330000
================================
thanhnoMacBook-Air:lesson6 thanhbui$ ./0601 Alice.txt fffffffff
力まかせ検索:
"fffffffff" found 0 times!
Used CPU time: 0.0009490000
================================
Boyer-Moore検索:
"fffffffff" found 0 times!
Used CPU time: 0.0001210000
================================

4. Test case 4: 文字列に２回以上出る文字がある
thanhnoMacBook-Air:lesson6 thanhbui$ ./0601 Alice.txt sister
力まかせ検索:
"sister" found 11 times!
Used CPU time: 0.0007620000
================================
Boyer-Moore検索:
"sister" found 11 times!
Used CPU time: 0.0002550000
================================
thanhnoMacBook-Air:lesson6 thanhbui$ ./0601 Alice.txt sister
力まかせ検索:
"sister" found 11 times!
Used CPU time: 0.0012720000
================================
Boyer-Moore検索:
"sister" found 11 times!
Used CPU time: 0.0004060000
================================
thanhnoMacBook-Air:lesson6 thanhbui$ ./0601 Alice.txt sister
力まかせ検索:
"sister" found 11 times!
Used CPU time: 0.0010090000
================================
Boyer-Moore検索:
"sister" found 11 times!
Used CPU time: 0.0003000000

*/