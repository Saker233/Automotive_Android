# Embedded Linux System: Creating a Minimal Root Filesystem

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
The shell allows launching other programs. To make the shell useful, you need approximately 50 utilities. BusyBox helps overcome the hassle of tracking down and cross-compiling each command.

### BusyBox
BusyBox combines tiny versions of many common UNIX utilities into a single small executable. It provides replacements for most utilities found in GNU fileutils, shellutils, etc.

## Libraries for the Root Filesystem

Some programs run dependently on some libraries, but initially, we don't have a rootfs. One option is to compile everything statically, but this takes more storage. Another option is to copy the required `.so` files from `sysroot` into our staging rootfs.

## The proc and sysfs Filesystems

`proc` and `sysfs` are pseudo directories created while booting and must be mounted manually in the rootfs:

```
mount -t proc proc /proc 
mount -t sysfs sysfs /sys
```



