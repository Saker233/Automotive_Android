#  Root Filesystem

The fourth and last element of embedded linux system, once we created rootfs now we are ready to deploy our embedded linux system


The main target of this chapter is to create a minimal root filesystem that is able to open a shell. Once we have a shell, we can add more scripts to include more programs or functionalities.

## What Should Be in the Root Filesystem?

The kernel will get a root filesystem no matter what. There are several ways to provide that rootfs:
1. **Initramfs**: Passed as a pointer to a block of memory from the bootloader (e.g., U-Boot).
2. **Manual Mounting**: Mount the rootfs manually using the `root=` parameter.

After obtaining its rootfs, the kernel will execute its first-ever program, `init`. After that, the kernel's job is done, and the whole process is left for `init` to complete and start other programs, bringing the system to life.

### General Requirements for a Minimal Root Filesystem
1. **Init**: The first program to be run that starts everything.
2. **Shell**: Provides a command prompt and runs the scripts which `init` asks to run.
3. **Daemons**: Background tasks.
4. **Shared Libraries**: Most programs are linked with these and must be present in rootfs.
5. **Configuration Files**: Stored in `.txt` files under `/etc` for init and daemons.
6. **Device Nodes**: Special files that give access to various device drivers.

The Linux kernel does not care about the layout of files and directories. However, we will stick with the Filesystem Hierarchy Standard (FHS).

![Screenshot from 2024-07-24 04-12-13](https://github.com/user-attachments/assets/84eaf025-1783-446d-ac2b-6266f8de336c)


## Programs for the Root Filesystem

Now we have to prepare the essential programs and supporting libraries to launch our rootfs.

### The Init Program
`init` is the first program to be run.

### Shell
We need a shell to run scripts and provide a command prompt for interacting with the system. The shell is not necessary for the production phase but is essential for development.

#### Types of Shells
1. **bash**: A powerful and famous shell used in Linux desktops.
2. **ash**: Based on Bourne shell, smaller than bash, suitable for embedded systems with limited resources.
3. **hush**: Suitable for devices with very small memory.

*Note: If you are using `ash` or `hush`, make sure to test them on the target device.*

### Utilities
The shell we have to run is just a way of launching other programs, to make shell useful you need to have access and use for the Unix commands, you need approximately 50 utilities which present 2 problems
	1- Tracking down each command and cross compile it (with the suitable CPU architecture) is a big hassle
	2- the resulting binaries of this compilation would leave megabytes of storage which was in the early days of embedded systems a big deal with the limited resources we had

To over come these 2 problems we had BusyBox


### BusyBox
BusyBox combines tiny versions of many common UNIX utilities into a single small executable. It provides replacements for most of the utilities you usually find in GNU fileutils, shellutils, etc. The utilities in BusyBox generally have fewer options than their full-featured GNU cousins; however, the options that are included provide the expected functionality and behave very much like their GNU counterparts. BusyBox provides a fairly complete environment for any small or embedded system.



## Libraries for the Root Filesystem

Some programs depend on certain libraries to run, but the issue here is that we don't have a root filesystem to begin with. One solution is to compile everything statically, but this takes up more storage space than dynamic linking. We are also very concerned with memory usage.

One option is to copy all the .so files from the sysroot into our staging root filesystem, but the problem is that libraries can be quite large, especially when using glibc with Crosstool-NG.

Another option is to be selective and only include the required libraries.




## The proc and sysfs Filesystems

proc and sysfs are 2 pseudo directories which means they are not physically on the rootfs but rather they are created while booting and therefore if you go check its size while runtime you gonna see 0

but they are window to see the inner operation of the kernel, and should be mounted manually in the rootfs while booting because busybox does not provide them 
```
mount -t proc proc /proc 
mount -t sysfs sysfs /sys
```

The original function of proc is -> to expose information about processes to user space, under proc there is a directory for each running process which contains information about the process itself -metadata about the process-

The role of sysfs -> to present the kernel driver model to user space it export hierarchy of files relating to devices and device drivers and the way they are connected to each other 




Transferring the Root Filesystem to the Target
There are three primary methods for loading the root filesystem (rootfs) onto your target:

1. Initramfs
nitramfs (initial RAM filesystem) is a temporary root filesystem loaded into memory and used by the Linux kernel during the boot process(u-boot) It provides the necessary environment for the kernel to start and mount the real root filesystem

Use Cases for Initramfs:

H1-can handle hardware initialization tasks, such as loading necessary kernel modules and setting up device drivers before the actual root filesystem is mounted
			 2- It can provide a dynamic environment where decisions can be made based on the current hardware and configuration. For example, it can decide which root filesystem to use based on available devices if we have more than one
			 3- For encrypted filesystems, initramfs can handle decryption before switching to the real root filesystem. This ensures that the decryption keys and processes are not exposed to the main operating system

    
2. Disk Image
A Disk Image is a copy of the rootfs that is formatted and ready to be loaded onto mass storage.

Example: An ext4-formatted image ready to be written to an SD card.

3. Network Filesystem (NFS)

The root filesystem can also be loaded from a network via an NFS (Network File System) server and mounted on the target during boot.






----------------------------------------------------------------------------------------------------------------------------------------------------------------

# Making a practical ROOTFS

From the last chapter we have already made our kernel which cross compiled with our cross compiler Arm-A9

but while booting the kernel PANICS because he cant find the rootfs

And here we are creating one



First thing to do is install Busybox

```
git clone https://github.com/mirror/busybox.git
```

and configure our cross compiler and the CPU architecture

```
export CROSS_COMPILE=~/x-tools/arm-cortexa9_neon-linux-musleabihf/bin/arm-cortexa9_neon-linux-musleabihf-
export ARCH=arm
```
After that we will enter the menu configuration of busybox

```
make menuconfig
```

The only thing that we will do is change the building process should be static

![Screenshot from 2024-07-24 06-26-04](https://github.com/user-attachments/assets/fbd45d80-0486-4159-8d6e-4bb6887aeaf4)



and then go to compile the whole build
```
make
```

![Screenshot from 2024-07-24 06-28-58](https://github.com/user-attachments/assets/b7cc8ead-1feb-4d71-aad3-b49e51789a6d)




and then we need to compile the binaries itself 

```
make install
```
after the make completed successfully a directory should appear under the name "_install"


we have to make a stagging rootfs in our host machine

I made it under my root and I have to copy all the binaries under _install to it

```
rsync -a ~/busybox/_install/* ~/rootfs

```


we also have to create manually all the directoreis that busybox didnt create

```
mkdir boot dev etc home mnt proc root srv sys

```


![Screenshot from 2024-07-24 06-39-43](https://github.com/user-attachments/assets/61dd8233-1966-4b90-814d-66325b8f5811)


Now we have to create the rcS script will initialize and mount the proc // sysfs

```


```
sudo mkdir etc/init.d
sudo touch etc/init.d/rcS
sudo nano etc/init.d/rcS

```
#!/bin/sh
# mount a filesystem of type `proc` to /proc
mount -t proc nodev /proc
# mount a filesystem of type `sysfs` to /sys
mount -t sysfs nodev /sys
# mount devtmpfs if you forget to configure it in Kernel menuconfig
mount -t devtmpfs devtempfs /dev

```


but this script should be executable to run


```
sudo chmod +x etc/init.d/rcS

```




The next step is to create the inittab script

```
sudo touch etc/inittab

sudo nano etc/inittab
```



```
# inittab file 
#-------------------------------------------------------
#When system startup,will execute "rcS" script
::sysinit:/etc/init.d/rcS
#Start"askfirst" shell on the console (Ask the user firslty to press any key) 
ttyAMA0::askfirst:-/bin/sh
#when restarting the init process,will execute "init" 
::restart:/sbin/init


```
Then we need to mount our virtual sd card to copy the rootfs from stagging area into the real rootfs

```
sudo losetup -f --show --partscan sd.img
```



![Screenshot from 2024-07-24 06-52-45](https://github.com/user-attachments/assets/4382190d-0971-4fdb-8444-170822df8818)



and we will go into the rootfs which is empty


The copying process:

```
cp -rp ~/rootfs/* /media/saker/rootfs

```

Now we have the zImage and .dtb file in the boot FAT16 and the rootfilesystem into rootfs now our Kernel panic issue should be solved


we run QEMU

```
sudo qemu-system-arm -M vexpress-a9 -nographic -net nic -net tap,script=./script_new.sh -kernel ./u-boot -sd ~/sd.img
```


in u-boot we have a variable called bootargs which provide the uboot with command line arguments // kernel initialization

```
setenv bootargs 'console=ttyAMA0 root=/dev/mmcblk0p2 rootfstype=ext4 rw rootwait init=/sbin/init'
saveenv
```
console=ttyAMA0 -> pecifies the console device

root=/dev/mmcblk0p2 -> Specifies the root filesystem's block device

rootfstype=ext4 -> Specifies the filesystem type of the root filesystem

rw -> read/write

rootwait ->  Causes the kernel to wait for the root device to become available before proceeding with the boot process

init=/sbin/init -> Specifies the path to the init process, which is the first process started by the Linux kernel.


![Screenshot from 2024-07-24 07-04-08](https://github.com/user-attachments/assets/ac3d5556-3c45-432b-b82f-ac0b07caa782)



We also should specify the addresses which the kernel and the dtb file will be loaded into

```
setenv kernel_addr_r 0x60000000

setenv fdt_addr_r 0x65000000

saveenv
```


and load the zImage then load the dtb

```
fatload mmc 0:1 $kernel_addr_r zImage


fatload mmc 0:1 $fdt_addr_r vexpress-v2p-ca9.dtb

```


![Screenshot from 2024-07-24 07-11-06](https://github.com/user-attachments/assets/3426114e-1713-41e4-a179-0e84d448760e)




![Screenshot from 2024-07-24 07-11-39](https://github.com/user-attachments/assets/a4995413-2e48-41a4-834d-c181b38c1b4a)





![Screenshot from 2024-07-24 07-11-39](https://github.com/user-attachments/assets/3cf8bd65-8cb7-4cf2-bfab-39a6b12709e2)



Then we need to boot the kernel

```
bootz $kernel_addr_r - $fdt_addr_r

```
AND THEN VOILAAAAA the kernel finally starts and he is accepting the commands


![Screenshot from 2024-07-24 07-15-07](https://github.com/user-attachments/assets/b77843f4-1798-4ed6-a7d5-79f4d8af1726)





![Screenshot from 2024-07-24 07-15-40](https://github.com/user-attachments/assets/59c9e6f8-239c-4c29-9eea-7d6a9f18b0d6)





We will notice that if we closed QEMU and starts again it doesnt auto boot then we will change boot cmd with

```
setenv bootcmd 'fatload mmc 0:1 $kernel_addr_r zImage; fatload mmc 0:1 $fdt_addr_r vexpress-v2p-ca9.dtb; bootz $kernel_addr_r - $fdt_addr_r'

saveenv

```
