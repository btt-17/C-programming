/*　REPORT 2-1
  * fgets()関数により 1行ずつ読み込み、行毎に文字列を逆順にして出力するプログラム
    を作成する。
  * reverse(char *s)を作成する
*/

#include<stdio.h>
#define MAX_LENGTH 256

//find string in string
int str_in_str(char *str1, char *str2);

int str_in_str(char *str1, char *str2){
    int c = 0;
    int i = 0, j;
    if(str2[0] == '\0') return 0;
    while(str1[i]){
        j = 0;
        while((str1[i+j] == str2[j]) && str1[i+j]!='\0'){
            if(str2[++j] == '\0') {
                c += 1 ;
            }
        }
        i++;
    }
    return c;
}

int main(void){
    FILE *fp = fopen("Alice.txt", "r"); /* Open Alice.txt file*/
    char str1[3][MAX_LENGTH] = {"Alice", "wonder", "self"}; // set
    int count[3] = {};  /* Alice: count[1], wonder: count[2], 
                           self: count[3] */
    char moji[MAX_LENGTH] = {} ;
    int i;

    if(fp == NULL) {
        printf("Can not open the file.\n");
    } 
    while(fgets(moji,MAX_LENGTH,fp) != NULL) {
        // reverse and print the content of the file
        for(i = 0; i < 3 ; i++){
            if(str_in_str(moji,str1[i])) {
                count[i] += str_in_str(moji,str1[i]);
            }
        }
    }
    for(i = 0; i < 3; i++){
        printf(" '%s' : %d \n", str1[i], count[i]);
    }
    fclose(fp);
    return 0;
}