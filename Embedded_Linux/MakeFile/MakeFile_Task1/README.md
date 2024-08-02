# MakeFile
## Task_One (and the only)

[![N|Solid](https://www.devopsschool.com/trainer/assets/images/makefiles-logo.png)](https://nodesource.com/products/nsolid)

[![Build Status](https://travis-ci.org/joemccann/dillinger.svg?branch=master)](https://travis-ci.org/joemccann/dillinger)



We have 4 directories:
- src:   store the source files (*.c)
- include: store the header files(*.h)
- bin: store the object files
- build: store the executable files

## Solution

This is the structure of the directories before any build process
![Screenshot_1](https://github.com/Saker233/Embedded-Linux/assets/130178079/a440cd63-9844-488e-b524-d236ddec6d3f)

![Screenshot_2](https://github.com/Saker233/Embedded-Linux/assets/130178079/c5a85df1-fefb-439b-bf39-f8f09388b769)

And this is the output files after the build each file in its proper directory
And we see that the build is done
![Screenshot_3](https://github.com/Saker233/Embedded-Linux/assets/130178079/705d8dc9-9a36-49f2-811e-02934ba0b22b)

And this the after I ran the exceutable file for the simple calculator
![Screenshot_4](https://github.com/Saker233/Embedded-Linux/assets/130178079/af76fc26-a578-408b-b9ad-bf88efd317a3)

This is the Phony pattern clean, cleaning the files from different directoris
![Screenshot_5](https://github.com/Saker233/Embedded-Linux/assets/130178079/76798a6f-6e91-45b5-aa3a-ce3634441847)




I made a variable reference for every relative path of each directory
and to get object files I made a foreach function to loop on all the source files and sustitute them to object files

we compile the source files to get the object files with its relative pathes because they are not on the same directories

I didnt include the header file stdio.h in the source file so I had to gave it as an option to the compilation rule 

last rule is to get the exceutable from the object files


