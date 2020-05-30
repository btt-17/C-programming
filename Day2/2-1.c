/*　REPORT 2-1
  * fgets()関数により 1行ずつ読み込み、行毎に文字列を逆順にして出力するプログラム
    を作成する。
  * reverse(char *s)を作成する
*/

#include<stdio.h>

#define MAX_LENGTH 256

// Declare a function
void reverse(char *str);
int len_of_string(char *str);

// len_of_string(): finding the length of the given string
int len_of_string(char *str) {
    int i = 0;
    while(str[i] != '\0'){
        i++;
    }
    return i;
}

// Reverse(): reversing the given string
void reverse(char *str) {
    char temp;
    int len = len_of_string(str);
    for(int i = 0; i < len/2; i++) {
        temp = str[i];
        str[i] = str[len-i-1];
        str[len-i-1] = temp ;
    }
}

int main(void){
    FILE *fp = fopen("Alice.txt", "r"); /* Open Alice.txt file*/
    char moji[MAX_LENGTH]; 
    if(fp == NULL) {
        printf("Can not open the file.");
        return -1;
    } 
    while(fgets(moji, MAX_LENGTH,fp) != NULL) {
        //reverse and print the content of the file
        reverse(moji);  
        printf("%s",moji);
    }
    fclose(fp);
    return 0;
}