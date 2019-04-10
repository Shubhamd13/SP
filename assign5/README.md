# For Linux only
## Compile using following commands
```
gcc sp5.c
```
For the grammar  
E ->  TE'  
E'	->	+TE'|NULL  
T	->	FT'  
T'	->	\*FT'|NULL  
F	->	(E)|a  
Accepted strings  
a+a\*a
a\*a+a  
Rejected strings  
aa  
++  
a++

