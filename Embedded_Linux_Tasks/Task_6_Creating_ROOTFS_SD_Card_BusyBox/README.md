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



