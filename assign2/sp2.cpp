/*
2. Write a program to implement Pass-II of Two-pass assembler for output of Assignment 1 (The subject
teacher should provide input file for this assignment )
*/
#include<iostream>
#include<fstream>
#include <sstream>
#include<string.h>
using namespace std;
string searchfile(string arr,int line_no){
    ifstream myfile(arr.c_str());
    string value,address,length;
    while(myfile.eof()==false && line_no!=-1){
            if(arr=="Symbols.txt")
                myfile>>value>>address>>length;
            else
                myfile>>value>>address;
        line_no--;
    }
    return address;
}
int main(){
    string line,res;
    ifstream intemediate_code;
    intemediate_code.open("Intemediate.txt");
    while(intemediate_code.eof()==false){
        int i=0;
        string ic,lc;
        intemediate_code>>lc>>ic;
        istringstream iss(ic);
        if(ic.find("IS")!= string::npos){
                string token,temp;
                res+=lc+")\t";
                while (getline(iss, token, ')')){
                    switch(i){
                  case 0:res+=token.substr(4,2);
                    break;
                  case 1:
                  case 2:
                      if(token[1]=='S'){
                        int num;
                        istringstream ss(token.substr(3));
                        ss >> num;
                        temp+="\t"+searchfile(("Symbols.txt"),num);
                      }else if(token[1]=='L'){
                        int num;
                        istringstream ss(token.substr(3));
                        ss >> num;
                        temp+="\t"+searchfile("Literals.txt",num);
                      }else{
                          temp+="\t";
                          temp+=token[1];
                      }
                    break;
                  default:
                    cout<<"invalid";
                    }
                    i++;
                }
                if(i==2){
                    //single operand
                    res+="\t0"+temp;
                }else {
                    res+=temp;
                }
            res+='\n';
            ofstream outfile("target.txt");
            outfile<<res;
        }
    }
    cout<<"-----------------------------\n";
    cout<<res;
}
