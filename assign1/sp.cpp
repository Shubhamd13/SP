/*
1. Write a program to implement Pass-I of Two-pass assembler for Symbols and Literal processing (
For hypothetical instruction set from Dhamdhere) considering following cases
i. Forward references
ii. DS and DC statement
iii. START, EQU, LTORG, END.
iv. Error handling: symbol used but not defined, invalid instruction/register etc
*/
#include <iostream>
#include <stdio.h>
#include <fstream>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include <string>
#include <string.h>
using namespace std;
/* A utility function to reverse a string  */
void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        swap(*(str+start), *(str+end));
        start++;
        end--;
    }
}
// Implementation of itoa()
char* itoa(int num, char* str, int base)
{
    sprintf( str, "%d", num );
    return str;
}
//--------------
struct optab{
    string mnemonic;
    string classs;
    string info;
    string searchval(){return mnemonic;}
};
struct symtab{
    string symbol;
    int address;
    int length;
    string searchval(){return symbol;}
};
struct littab{
    string  value;
    int address;
    string searchval(){return value;}//remove
};
struct pooltab{
    int first;
    int num_literal;
};
int opreand_to_code(string reg){
    if(reg=="AREG")
        return 1;
    if(reg=="BREG")
        return 2;
    if(reg=="CREG")
        return 3;
    if(reg=="DREG")
        return 4;
    return 0;
}
int cond_to_code(string condn){
    if(condn=="EQ")
        return 1;
    if(condn=="LT")
        return 2;
    if(condn=="GT")
        return 3;
    if(condn=="LE")
        return 4;
	if(condn=="GE")
        return 5;
	if(condn=="NE")
        return 6;
    if(condn=="ANY")
        return 7;
    return 0;
}
//-------template func for all tables
template <class T>
int srchtab(vector<T> vec, string key) {
    int i;
    for (i=0; i < vec.size();i++){
        if(vec[i].searchval()==key)
           return i;
    }
    return -1;
}
class assembler{
private:
    vector<optab> opcode_table;
    vector<symtab> symbol_table;
    vector<littab> literal_table;
    vector<pooltab> pool_table;
	string intermediate_code;
    ifstream myfile;
    void init_table();
    void read_file();
    void print_optable();
    void print_file();
    void print_symtab();
    void print_littab();
    void print_pooltab();
    public:
    assembler();
    void process();
    void print();
	void printtofiles();
};
assembler::assembler(){
    init_table();
    read_file();
}
void assembler::init_table(){
    //-----AD----------------
    opcode_table.push_back(optab{"START" ,"AD","01"});
    opcode_table.push_back(optab{"END"   ,"AD","02"});
    opcode_table.push_back(optab{"ORIGIN","AD","03"});
    opcode_table.push_back(optab{"EQU"   ,"AD","04"});
    opcode_table.push_back(optab{"LTORG" ,"AD","05"});
    //-----IS----------------
    opcode_table.push_back(optab{"STOP" ,"IS","00"});
    opcode_table.push_back(optab{"ADD"  ,"IS","01"});
    opcode_table.push_back(optab{"SUB"  ,"IS","02"});
    opcode_table.push_back(optab{"MULT" ,"IS","03"});
    opcode_table.push_back(optab{"MOVER","IS","04"});
    opcode_table.push_back(optab{"MOVEM","IS","05"});
    opcode_table.push_back(optab{"COMP" ,"IS","06"});
    opcode_table.push_back(optab{"BC"   ,"IS","07"});
    opcode_table.push_back(optab{"DIV"  ,"IS","08"});
    opcode_table.push_back(optab{"READ" ,"IS","09"});
    opcode_table.push_back(optab{"PRINT","IS","10"});
    //-----DL----------------
    opcode_table.push_back(optab{"DC","DL","01"});
    opcode_table.push_back(optab{"DS","DL","02"});
    //---------------POOL TABLE----------------------
    pool_table.push_back(pooltab{0,0});
}
void assembler::read_file(){

    myfile.open("file.asm");
    if (!myfile.is_open()){
        cout<<"file did not open";
        exit(0);
    }
}
void assembler::process(){
    int lc=0,i,pos,pooltable_pointer=0;
    string line;
    cout<<"-----------------------------";
    cout<<"\n Processing...\n";
    if(myfile.is_open()){
        while ( getline (myfile,line) ){
            i=0;
            cout<<lc<<"\t"<<line<<endl;
			char arr[20];
			//adiition
			itoa(lc,arr,10);
			intermediate_code+=string(arr);
			intermediate_code+="\t";
		
            if((line[0])!='\t'){//label
                //add to symbol table
                cout<<"label found"<<endl;
                string label;
                while((line[i])!='\t'){
                        label+=line[i];
                        i++;
                }
                if(srchtab(symbol_table,label)==-1){
                    symbol_table.push_back(symtab{label,lc,0});
                    cout<<"Adding to symbol table\n";
                }else{
                    symbol_table[srchtab(symbol_table,label)].address=lc;
                }
            }
            i++;
            string mnemonic;
            while(line[i]!='\t'&&i<line.size()-1){
                mnemonic+=line[i];
                i++;
            }
            pos=srchtab(opcode_table,mnemonic);
            if(pos!=-1){
                intermediate_code+="("+opcode_table[pos].classs+","+opcode_table[pos].info+")";
                cout<<("("+opcode_table[pos].classs+","+opcode_table[pos].info+")")<<"\n";
            }else{
                cout<<"Invalid instruction:\'"+mnemonic+"\'"<<endl;
                break;
            }
            i++;
            if(opcode_table[pos].classs=="IS"){
                    lc++;
                    string operand1;
                    string operand2;
		    if(mnemonic=="BC"){
			    int regno;
			    string operand1,operand2;
			while(line[i]!=','){
                            operand1+=line[i];
                            i++;
                        }
			regno=cond_to_code(operand1);
			char arr[20];
			//adiition
			itoa(regno,arr,10);
                        intermediate_code+="("+string(arr)+")";
                        i++;
                        while(i<line.size()-1){
                            operand2+=line[i];
                            i++;
                        }
                        if(operand2[0]=='='){
                            literal_table.push_back(littab{operand2,0});
                            char arr[20];
                            itoa(literal_table.size()-1,arr,10);
                            intermediate_code+="(L,"+string(arr)+")";
                            pool_table[pooltable_pointer].num_literal++;
                        }else{
                            if(srchtab(symbol_table,operand2)==-1){
                                symbol_table.push_back(symtab{operand2,0,0});
                            }
                            int pos=srchtab(symbol_table,operand2);
                            char arr[20];
                            itoa(pos,arr,10);
                            intermediate_code+="(S,"+string(arr)+")";
                        }
		    }else if(mnemonic=="STOP"){
                    }else if(mnemonic=="READ"||mnemonic=="PRINT"){
                        while(i<line.size()-1){
                            operand2+=line[i];
                            i++;
                        }
                        if(operand2[0]=='='){
                            literal_table.push_back(littab{operand2,0});
                            char arr[20];
                            itoa(literal_table.size()-1,arr,10);
                            intermediate_code+="(L,"+string(arr)+")";
                            pool_table[pooltable_pointer].num_literal++;
                        }else{
                            if(srchtab(symbol_table,operand2)==-1){
                                symbol_table.push_back(symtab{operand2,0,0});
                            }
                            int pos=srchtab(symbol_table,operand2);
                            char arr[20];
                            itoa(pos,arr,10);
                            intermediate_code+="(S,"+string(arr)+")";
                        }

                    }else{
                        int regno;
                        while(line[i]!=','){
                            operand1+=line[i];
                            i++;
                        }
                        char arr[20];
                        regno=opreand_to_code(operand1);
			if(regno==0){
				cout<<"Invalid register"<<endl;
				exit(0);
			}
                        itoa(regno,arr,10);
                        intermediate_code+="("+string(arr)+")";
                        i++;
                        while(i<line.size()-1){
                            operand2+=line[i];
                            i++;
                        }
                        if(operand2[0]=='='){
                            literal_table.push_back(littab{operand2,0});
                            char arr[20];
                            itoa(literal_table.size()-1,arr,10);
                            intermediate_code+="(L,"+string(arr)+")";
                            pool_table[pooltable_pointer].num_literal++;
                        }else{
                            if(srchtab(symbol_table,operand2)==-1){
                                symbol_table.push_back(symtab{operand2,0,0});
                            }
                            int pos=srchtab(symbol_table,operand2);
                            char arr[20];
                            itoa(pos,arr,10);
                            intermediate_code+="(S,"+string(arr)+")";
                        }

                    }
            }else if(opcode_table[pos].classs=="DL"){
                while(!isdigit(line[i]))
                    i++;
                string len=line.substr(i,line.size());

                int length=atoi(len.c_str());
                char arr[20];
		cout<<"\n"+length<<" "<<len<<endl;
                itoa(length,arr,10);
                lc+=length;
                i=0;
                string label;
                while((line[i])!='\t'){
                        label+=line[i];
                        i++;
                }
                symbol_table[srchtab(symbol_table,label)].length=length;
                intermediate_code+="(C,"+string(arr)+")";
            }else{
                if(mnemonic=="START"||mnemonic=="ORIGIN"){
                    string len=line.substr(i,line.size());
                    int length=atoi(len.c_str());
                    char arr[20];
                    itoa(length,arr,10);
                    lc=length;
                    intermediate_code+="(C,"+string(arr)+")";
                }
                if(mnemonic=="EQU"){
                    string label;
                    int j=0;
                    while((line[j])!='\t'){
                        label+=line[j];
                        j++;
                    }
                    j++;
                    while((line[j])!='\t')j++;
                    j++;
                    string old_label;
                    while(j<line.size()){
                        old_label+=line[j];
                        j++;
                    }
                    symbol_table[srchtab(symbol_table,label)].address=
                    symbol_table[srchtab(symbol_table,old_label)].address;
                    symbol_table[srchtab(symbol_table,label)].length=1;
                }
                if(mnemonic=="END"||mnemonic=="LTORG"){
                    //process literals
		    cout<<"\nprocess literals\n";
                    if(pool_table[pooltable_pointer].num_literal>0){
                        int start;
                        for(start=pool_table[pooltable_pointer].first;start<pool_table[pooltable_pointer].num_literal+pool_table[pooltable_pointer].first;start++){
                            literal_table[start].address=lc;
                            lc++;
                        }
                        pool_table.push_back(pooltab{start,0});
						pooltable_pointer++;
						print_littab();
						print_pooltab();
                    }
                }
            }
            intermediate_code+="\n";
        }
    }
	vector<symtab>::iterator ptr;
    for (ptr = symbol_table.begin(); ptr < symbol_table.end(); ptr++)
		if(ptr->address==0){
			cout<<"Symbol:"<<ptr->symbol<<" used but not declared"<<endl;
			exit(0);
		}


    cout<<"----------INTERMEDIATE CODE---------------------"<<endl;
    cout<<intermediate_code<<endl;
}
void assembler::print_pooltab(){
	vector<pooltab>::iterator ptr;
    cout<<"---------FIRST NUMLIT------------------"<<endl;
	for (ptr = pool_table.begin(); ptr < pool_table.end(); ptr++)
        cout <<ptr->first << "\t"<< ptr->num_literal<<endl;
    cout<<"-------------------------------------------------"<<endl;
}
void assembler::print_optable(){
    vector<optab>::iterator ptr;
    cout<<"---------MNEMONIC OPCODE TABLE------------------"<<endl;
    cout<<"Mnemonic  Class  Info"<<endl;
    for (ptr = opcode_table.begin(); ptr < opcode_table.end(); ptr++)
        cout <<ptr->mnemonic << "\t"<< ptr->classs<<"\t"<<ptr->info<<endl;
    cout<<"-------------------------------------------------"<<endl;
}
void assembler::print_littab(){
    vector<littab>::iterator ptr;
    cout<<"-----------LITERAL TABLE------------------------"<<endl;
    cout<<"Literal  address"<<endl;
    for (ptr = literal_table.begin(); ptr < literal_table.end(); ptr++)
        cout <<ptr->value << "\t"<< ptr->address<<endl;
    cout<<"------------------------------------------------"<<endl;
}
void assembler::print_symtab(){
    vector<symtab>::iterator ptr;
    cout<<"-----------SYMBOL TABLE-------------------------"<<endl;
    cout<<"Symbol  address  length"<<endl;
    for (ptr = symbol_table.begin(); ptr < symbol_table.end(); ptr++)
        cout <<ptr->symbol << "\t"<< ptr->address<<"\t"<<ptr->length<<endl;
    cout<<"------------------------------------------------"<<endl;
}
void assembler::print(){
    print_optable();
    print_symtab();
    print_littab();
}
void assembler::printtofiles(){
	ofstream myfile;
	myfile.open("Intemediate.txt");
	myfile<<intermediate_code<<endl;
	myfile.close();
	myfile.open("Symbols.txt");
	vector<symtab>::iterator ptr;
    for (ptr = symbol_table.begin(); ptr < symbol_table.end(); ptr++)
        myfile <<ptr->symbol << "\t"<< ptr->address<<"\t"<<ptr->length<<endl;
    myfile.close();
	myfile.open("Literals.txt");
	vector<littab>::iterator ptr1;
    for (ptr1 = literal_table.begin(); ptr1 < literal_table.end(); ptr1++)
        myfile <<ptr1->value << "\t"<< ptr1->address<<endl;
	myfile.close();
	
}
int main()
{
    assembler a;
    a.process();
    a.print();
    a.printtofiles();
}
