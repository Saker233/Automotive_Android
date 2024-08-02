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


