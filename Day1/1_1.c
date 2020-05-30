/*
 * 科目：ソフトウェア演習Ia
 * 学籍番号・氏名：B181858・Bui Tuan Thanh
 * 課題番号：課題１−１
 * 提出日：2020年5月15日
 * 使用Cコンパイラ：C 4.2.1
 * 使用IDE: Visual Studio Code
*/

#include<stdio.h>
#include<ctype.h>

int main(void){
    char c;
    int count[127] = {};

    printf("Enter your passage here:\n");
    while(c != EOF){   //  Stop if EOF
        c = getchar(); // read the input
        if(isprint(c)) count[c] += 1; // count the times the character appears
    }

    // print the result
    for(int i = 32; i < 128; i++ ){
        printf("%c: %d\n", (char) i, count[i]);
    }
    return 0;
}