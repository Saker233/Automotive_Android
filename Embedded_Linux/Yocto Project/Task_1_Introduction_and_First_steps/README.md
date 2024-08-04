# Yocto Project

Let's first summarize the what we have done to make our image run probrely without a customization tool

we first created our cross compiler via the tool Croostool-NG then we went to create our target bootloader which was the u-boot

Then we created our target kernel image which will the bootloader flsh it via the sd card flash memory or via a network communication protocol which was the TFTP

Now we are ready we have the kernel image and the bootloader which will load it but we miss one thing which was the rootfs

How we get the rootfs ? simply by configuring the BusyBox tool which auto generate the rootfs based on some configuration we done in some checkboxes


Now we have

  1- Cross compiler
  
  2- Bootloader
  
  3- Kernel Image
  
  4- Rootfs
  


And that are the main components of any embedded linux system and we have already done that and worked proprely as it should

Not only but also we deep dived into the initramfs which was an additional step into the booting sequenec which has several advantages like we chose our rootfs if we have more than one
Or doing checksum calculations on the rootfs to make sure of the data integrity and other advantages also


After that we studied the init process which was a crucial topic and essential thing in anu linux booting process and we had 3 types

  1- BusyBox init
  
  2- System V
  
  3- systemd
  


and we illustrated each one of them briefly 

Can't you see the problem ? IT'S A LOT OF HASSLE

to get the image run on a rootfile system we encountred a lot of steps and a lot of building processes and a lot of configuration


So we needed a shift into automate that process and make it much easier which is The Auto Build Tools



---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
## Open Embedded To The Rescue!



Before deep dive in Yocto Project let's understand first the Auto Build Tools

In 2003 there was a community called OpenEmedded who decided to create a tool that customize the linux kernel to create custom images


The tool they created is consisst of some scripts wriiten in python and the name of that tool was -> bitbake


The main concept was we get to the tool some inputs and that inputs called layers (configuration, metadata)

The bitbake will read that inputs and know its dependencies and clone each one and run the scripts on the cloned data then the output will be the desired image


Untill now we are not talking on any specific hardaware all targets will share the same steps


So, we now have to clone also the board support package (BSP) which is the layer which will configure our target architecture



Until now we have 2 types of layers

  1- BSP -> hardware space

  2- Application layer -> user space



The cross compiler is considred as BSP


In general the layers will be only one BSP and unlimited number of Applications


----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
## Yocto

This is all fine and open embedded can actually get the job done, But what is the importance of yocto and why this all fame ?

Yocto is another community who made the documentation on how to use Open Embedded, Yocto itself doeesnt create images but the open embedded tools dooes

So, Yocto only tells you the way on how to use the open embedded tool effieciently

But also, Yocto created some new layers to make the job easier

They created a repo called "Poky" which has

  1- bitbake

  2- meta-poky

  3- meta-yocto-bsp

  4- meta-core

  5- meta-skeleton



## Bitbake

BitBake is a build tool that is used by the Yocto Project to build packages and images.
It is similar to tools like make but designed specifically for embedded Linux and the needs of the Yocto Project.
BitBake parses recipes (files with .bb extension) to determine how to build software components, managing dependencies and fetching sources, compiling, and creating packages




## meta-poky

meta-poky is a reference distribution layer provided by the Yocto Project. 
It includes configuration files, classes, and recipes to build a basic but fully functional Linux distribution. 
It serves as a starting point and example for developers to create their own custom layers and distributions.




## meta-yocto-bsp

Board Support Package (BSP) layer provided by the Yocto Project. 
It contains support for various hardware platforms, including configuration files and recipes specific to those platforms. 
This layer helps in setting up the hardware-specific parts of the build process, such as kernel configurations and bootloader settings





## meta-core

contains the fundamental components and base recipes required to build a Linux distribution using the Yocto Project. 
It includes essential packages, tools, and libraries that form the foundation of any Yocto-based build, like python which is essential to run the scripts



## meta-skeleton

template or example layer provided by the Yocto Project. It is intended to help developers create their own custom layers. 
It includes sample recipes, configurations, and documentation that demonstrate best practices for developing custom layers and recipes



-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

## Layers or Metadata


what is the meaning of layers ?

Layers are collections of recipes, configuration files, and other related files that are used by BitBake to build software. 
Each layer can provide support for different aspects of the build process, such as hardware support, specific software packages, or custom configurations. 
Layers allow developers to modularize and organize their build environment, making it easier to manage, maintain, and extend



Let's now deep dive in the types of layers

  1- User Configuration files -> Any file with the .conf file used to define various settings and variables that control the build process

  2- Application files -> any file with the extension .bb  which is the recipe itself -> define how to build software packages. Each recipe provides the instructions for fetching, configuring, compiling, and packaging a particular piece of software


  3- Classes -> Discussed Later



So now the main concept is the bitbake will get its congiguration file (layers) as an input and he will parse them to know what he will actually do according to the recipe we gave


But generally the steps will be:
  1- Unpack -> Decompress -> Extracts the source code from the archives specified in the recipe -> will be in 'S' Directory

  2- Patch -> If he has any modifications to the decopressed data before even processe it -> will be in 'S' Directory

  3- Configure -> Prepares the source code for building by configuring it according to the target environment and build settings -> will be in 'S' Directory

  4- Build -> Compiles the source code into executable binaries or libraries -> will be in 'B' Directory

  5- Install -> Installs the compiled binaries, libraries, and other files into the appropriate directories for packaging -> will be in 'D' Directory

  6- Package Feeder -> has 2 paths to go 1- Image if we don't need the debugging symbols 2- SDK if we need the debugging symbols







