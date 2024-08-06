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
