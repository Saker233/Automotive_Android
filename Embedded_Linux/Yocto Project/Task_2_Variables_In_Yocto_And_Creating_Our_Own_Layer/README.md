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



## Variable Assignation

1- Weak Assignation

```
myvar = 3

myvar ?= 4

```
Bitbake will ignore the 4 and assign the 3 because 3 is normal assignation but the 4 is WEAK


```
myvar ?= 3

myvar ?= 4

```

Both are weak assignantion with the same rank or priority so bitbake will go with the first which is 3



```
myvar = 3

myvar = 4

```

Both are also normal assignation (same rank) but we have to assign every time so we will first assign 3 then overwrite with 4



2- weak weak assignation

```
myvar ??= 4

myvar ?= 3

```


weak weak assignation has lower rank (priority) than weak then bitbake will assign 3



```
myvar ??= 4

myvar ??= 3

```

also the same codition as weak, they are the same rank so bitbake will assign the first only




3- Append


```
myvar = 4

myvar += 5

```
here bitbake will deal differently -> he will first assign the 4 then will assign the 5 so the output will be -> "4 5"




```
myvar = 4

myvar:append = 5

```

same as the above example but the only difference will be that there is no space in appending -> "45"



```
myvar = 4

myvar += 5

myvar:append = 6

```

we can see the output -> "4 56"


4- pre append


```
myvar =+ 7
myvar:preappend = 8

```


5- Immediate Assignation

```
XAR = 4
MYVAR = "${XAR}"
XAR = 6


```


6- Remove

```
myvar = " 3 5 6"

myvar:remove = "5"
```

"3 6"


----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



# How to create a Layer ?


If we want to create our own layer we should create it OUTSIDE of Poky and dont modify in the poky itself because it has license and this should ruin the software itself


we will create a new layer called "meta_iti"


Gratefully the bitbake won't leave us to create it from scratch and he has a template to do it


```
bitbake-layers create-layer ../meta_iti

```






![Screenshot from 2024-08-06 02-19-24](https://github.com/user-attachments/assets/c3865638-5eff-46a6-9217-2b3f19d399fd)





Now bitbake already created the layer template for us and all we have to do is to modify it as our needs






![Screenshot from 2024-08-06 02-20-31](https://github.com/user-attachments/assets/bcc2b0e1-bf65-4e71-92de-18228cbf768d)




1- conf

2- COPYING.MIT 

3- README

4- recipe-examples


This is the files he created



![Screenshot from 2024-08-06 02-21-42](https://github.com/user-attachments/assets/92a322e3-7a1f-408a-9cfd-f8731d920d6e)





Under conf dir we have layer.conf which is the full descreiption to the whole layer




![Screenshot from 2024-08-06 02-22-51](https://github.com/user-attachments/assets/55214c50-68fd-463e-925f-af698099824b)



```
LAYERDEPENDS_meta_iti = "core"
```
This means that this layer is depend on another layer which is the core layer




```
BBFILES += "${LAYERDIR}/recipes-*/*/*.bb \
            ${LAYERDIR}/recipes-*/*/*.bbappend"


```


This variable which is "BBFILES" represent how to find your recipe inside your layer








































