# For Linux only
## To install lex and yacc
```
sudo apt-get install bison flex
```
calc.l and calc.y are files to be written  
other files are generated upon compilation  
## Compile using following commands
```
lex calc.l
yacc -d calc.y
gcc lex.yy.c y.tab.c -w -ll -ly
```
## Example
```
shubham@shubham:~/github/sp/assign6$ lex calc.l
shubham@shubham:~/github/sp/assign6$ yacc -d calc.y
shubham@shubham:~/github/sp/assign6$ gcc lex.yy.c y.tab.c -w -ll -ly
shubham@shubham:~/github/sp/assign6$ ./a.out
1+1*3

Result=4
shubham@shubham:~/github/sp/assign6$ ./a.out
(1 + 1)*3 

Result=6

//Negive numbers accepted
shubham@shubham:~/github/sp/assign6$ ./a.out
1+-1

Result=0
shubham@shubham:~/github/sp/assign6$ ./a.out
1++1

Wrong input
```
