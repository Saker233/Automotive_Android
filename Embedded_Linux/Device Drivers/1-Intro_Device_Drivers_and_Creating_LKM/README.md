## Device Drivers

Linux is originally a kernel which handle the tasks and interface with it during the runtime


The interfacing with the kernel done through modules or to be more clear -> Linux Kernel Modules (LKM)


We can interface with the kernel space in 2 ways


## 1- Static Kernel Module -> During Linux Compilation

  If we compiled static so the module will be inside the zImage
	So the module will become part of the linux kernel image


 pros -> The startup of the module itself will be faster because I dont have to load it into RAM
         The size of the kernel module itself will be smaller in size (discussed later)


cons -> The size of the whole zImage will be larger and takes more time for booting



## 2- Dynamic -> During Linux Runtime

  if we working dynamic then the module will be external file with the extension -> .ko


pros -> Loading the module at run time to decrease the startup time of the kernel, The loapding will be from user space rootfs

cons -> The startup of the module itself will be slower because I have to make systemcall to load it into RAM



For Example: The security modules never compiled dynamically because I want it to start fast even before anuthing else



------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


## Commands to add new kernel modules


1- insmod -> to insert new module (has to be .ko)

2- rmmod -> to remove a module

3- modprobe -> more genric command to add or remove with the flag option specify what to do

4- lsmod -> this will list all the dynmaically LKMs

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

## Why we need LKM ?


1- To extend the linux functionality

2- To increase the security

3- To use a new filesystem

4- To add new device drivers



------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


## How to write LKM (Syntax)


1- Header Section


Kernel headers are the .h in the Linux kernel source code that define the interface between the kernel and user-space applications. 
These headers provide the necessary definitions and declarations for system calls and other kernel services that user-space applications and libraries need to interact with the kernel.


first we need to know which linux version we are using to get the proper headers for it

```
uname -r
```
In my case

```
5.15.0-117-generic
```



To find the kernel header in the rootfs it will be under

```
cd /usr/src/linux-headers-5.15.0-117-generic/include/
```


![Screenshot from 2024-08-06 22-33-28](https://github.com/user-attachments/assets/bf4feb2b-72b2-4765-bee9-8ca1926057d4)






2- Code Section -> C code



Linux has some restriction when you intefacing with its kernel, He gave you a template on how to use the drivers, if you want to use a function don't make one

But use the one it provieded and if you want to make a variable dont make one but make instance of the struct he provide


LKM doesn't have a main function because all the kernel space has only one main function














