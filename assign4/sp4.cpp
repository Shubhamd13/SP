#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

using namespace std;

int isKeyword(char buffer[]){
	char keywords[32][10] = {"auto","break","case","char","const","continue","default",
							"do","double","else","enum","extern","float","for","goto",
							"if","int","long","register","return","short","signed",
							"sizeof","static","struct","switch","typedef","union",
							"unsigned","void","volatile","while"};
	int i, flag = 0;

	for(i = 0; i < 32; ++i){
		if(strcmp(keywords[i], buffer) == 0){
			flag = 1;
			break;
		}
	}

	return flag;
}
bool isoperator(char ch){
	char operators[] = "+*-/%=,(){}><;";
	for(int i = 0; i < strlen(operators); ++i){
   			if(ch == operators[i])
   				return true;
   		}
   		return false;
}
int main(){
	char ch, buffer[15], operators[] = "+*-/%=";
	char arr[]="(){}><;,";

	ifstream fin("program.txt");
	int i,j=0;

	if(!fin.is_open()){
		cout<<"error while opening the file\n";
		exit(0);
	}

	while(!fin.eof()){
   		ch = fin.get();
        if(ch=='\"'){
            j=0;
            ch = fin.get();
            buffer[j++]=ch;
            while(ch!='\"'){
            ch = fin.get();
            buffer[j++]=ch;
            }
            buffer[j++]='\0';
            j=0;
            cout<<"\""<<buffer<<"is string\n";
        }
        if(isalnum(ch)){
   			buffer[j++] = ch;
   		}
   		else if((ch == ' ' || ch == '\n' || (isoperator(ch))) && (j != 0)){
   				buffer[j] = '\0';
   				j = 0;

   				if(isKeyword(buffer) == 1)
   					cout<<buffer<<" is keyword\n";
   				else
   					cout<<buffer<<" is indentifier\n";
   		}

        for(i = 0; i < 6; ++i){
   			if(ch == operators[i])
   				cout<<ch<<" is operator\n";
   		}
   		for(i = 0; i < strlen(arr); ++i){
   			if(ch == arr[i])
   				cout<<ch<<" is separator\n";
   		}
	}

	fin.close();

	return 0;
}


