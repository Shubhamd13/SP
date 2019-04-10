/*
5. Write a program to implement a Recursive Descent Parser .
*/
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
char input[100];
int i;
int errors=0;
void Ed();
void T();
void Td();
void F();
void E(){
    T();
    Ed();
}
void Ed(){
    if(input[i]=='+'){
        i++;
        T();
        Ed();
    }else{
        return;
    }
}
void T(){
    F();
    Td();
}
void Td(){
    if(input[i]=='*'){
        i++;
        F();
        Td();
    }else{
        return;
    }
}
void F(){
    if(input[i]=='('){
        i++;
        E();
        if(input[i]==')'){
            i++;
        }
    }else if(input[i]=='a'){
        i++;
    }else{
        errors=1;
    }
}
int main()
{
    i=0;
    printf("enter the input string");
    scanf("%s",input);
    E();
    if(i==strlen(input)&&errors==0)
        printf("\n string accepted");
    else
        printf("\n rejected");
}

