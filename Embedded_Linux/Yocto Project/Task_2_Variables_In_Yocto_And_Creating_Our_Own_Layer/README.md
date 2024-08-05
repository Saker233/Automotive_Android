# Variables with Bitbake


We have 2 Types of variables which bitbake can deal with

  1- Global Variable
      Any Variable in a file which its extension ".conf" is a global variable


    
  2- Local Variable
      Any variable in a file which its extension (.bb // .bbappend // .class) is considred as local variable





 ## How to assign a variable

```
myvar = "<string>"
```

all variables are strings and has to be between double qutations


## How to read the global variables ?

There is a bitbake command which will go and search in any file with the extension .conf and read the varible in it

```
bitbake-getvar <variable name>

```



