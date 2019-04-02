# For Linux only
## Compile using following commands
```
g++ sp5.cpp
```
For the grammar  
E ->  TE'  
E'	->	+TE'|NULL  
T	->	FT'  
T'	->	\*FT'|NULL  
F	->	(E)|a  
Accepet strings  
a+a\*a
a\*a+a  
Rejected strings  
aa  
++  
a++

