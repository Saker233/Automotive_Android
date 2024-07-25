# Understanding initramfs in Linux

## Overview

The `initramfs` (initial RAM filesystem) is a temporary root filesystem used by the Linux kernel during the boot process. It plays a critical role in preparing the system to run the actual root filesystem. This document explains its purpose, structure, and how it fits into the boot process.

## Purpose and Functionality

- **Early User Space**: `initramfs` provides an early user-space environment, which the kernel uses immediately after the bootloader loads the kernel.
- **Kernel-User Space Interaction**: It allows the kernel to interact with user-space scripts and tools to configure devices, load modules, and mount the real root filesystem.
- **Flexibility**: It makes the boot process more flexible and portable by handling hardware detection, loading necessary modules, and setting up RAID, LVM, or network filesystems before switching to the actual root filesystem.

## Structure and Contents

`initramfs` is typically a compressed `cpio` archive containing essential directories and files for booting:

- **Directories**: Includes `/bin`, `/sbin`, `/lib`, `/lib64`, and `/etc`.
- **Kernel Modules**: Contains necessary kernel modules for accessing the root filesystem.
- **Device Nodes**: The `/dev` directory includes device nodes managed by `mdev` or `udev`.
- **Configuration Files**: Essential configuration files and scripts, including `init` or `linuxrc`, which is the first user-space program executed by the kernel.

## Boot Process with initramfs

1. **Bootloader Phase**:
   - The bootloader (e.g., GRUB, U-Boot) loads the kernel and `initramfs` into memory.
   
2. **Kernel Initialization**:
   - The kernel initializes core components and decompresses `initramfs` into a temporary RAM disk.
   
3. **Running the Init Script**:
   - The kernel executes the `/init` script from `initramfs`. This script is responsible for:
     - Mounting necessary filesystems.
     - Loading kernel modules.
     - Configuring devices and network interfaces.
     - Performing other setup tasks.
   
4. **Switching to the Real Root Filesystem**:
   - The `init` script mounts the real root filesystem (usually from a disk partition).
   - It uses `pivot_root` or `switch_root` to switch from `initramfs` to the real root filesystem.
   - Finally, the `init` script executes the real `/sbin/init` or another specified init system (e.g., `systemd`, `upstart`).

## Creating and Customizing initramfs

- **Tools**: Tools like `dracut`, `mkinitramfs`, and `busybox` are used to create and customize `initramfs`.
- **Configuration**: You can add custom scripts and configurations to handle specific hardware or boot scenarios.
- **Compression**: The `initramfs` archive is often compressed with algorithms like gzip, bzip2, or xz to save space.

## Benefits of initramfs

- **Hardware Abstraction**: Abstracts hardware differences, making the kernel boot process more hardware-agnostic.
- **Modularity**: Allows for modular loading of drivers and other components, reducing the need for monolithic kernels.
- **Rescue and Recovery**: Provides a fallback environment for system recovery and maintenance tasks.
- **Additional stage Bootloader**: Provides A bootloader stage which act as a boot manager to make decision which rootfs will boot
- **Ensure Security and Data Inyegrity**: Make always a checsum on the rootfs and decide whether its data valid or not


--------------------------------------------------------------------------------------------------------------------------------------------------------
Task: The task is about creating an initramfs which act as a boot manager between 2 physical rootfs and asks the user which rootfs to boot




firstly we will got into our stagging rootfs and create our initramfs

```
cd ~/rootfs
find . | cpio -H newc -ov --owner root:root > ../initramfs.cpio
cd ..
gzip initramfs.cpio
mkimage -A arm -O linux -T ramdisk -d initramfs.cpio.gz uRamdisk

```


**Create a CPIO archive of the root filesystem:**

    ```
    find . | cpio -H newc -ov --owner root:root > ../initramfs.cpio
    ```

    - `find .`: Lists all files and directories starting from the current directory.
    - `cpio -H newc -ov --owner root:root`: Creates a new CPIO archive in "newc" format, preserving ownership as root.
    - `> ../initramfs.cpio`: Redirects the output to a file named `initramfs.cpio` in the parent directory.



**Compress the CPIO archive using gzip:**

    ```
    gzip initramfs.cpio
    ```

    This creates `initramfs.cpio.gz`.

**Create a U-Boot image from the compressed initramfs:**

    ```
    mkimage -A arm -O linux -T ramdisk -d initramfs.cpio.gz uRamdisk
    ```

    - `-A arm`: Specifies the architecture (ARM in this case).
    - `-O linux`: Specifies the operating system (Linux).
    - `-T ramdisk`: Specifies the image type (ramdisk).
    - `-d initramfs.cpio.gz`: Specifies the input file.
    - `uRamdisk`: Specifies the output file name.



Now we have uRamdisk which will do everything in u-boot


We will copy uRamdisk in our FAT16 boot partition in the virtual SD Card

and we will launch QEMUUUU

```
sudo qemu-system-arm -M vexpress-a9 -nographic -net nic -net tap,script=./script_new.sh -kernel ./u-boot -sd ~/sd.img


```

We have to set some variables first

```
setenv initramfs 0x60800000


fatload mmc 0:1 $kernel_addr_r zImage
fatload mmc 0:1 $fdt_addr_r vexpress-v2p-ca9.dtb
fatload mmc 0:1 $initramfs uRamdisk


setenv bootargs "console=ttyAMA0 rdinit=/bin/sh"


bootz $kernel_addr_r $initramfs $fdt_addr_r



```


If we make the above variables and launched our kernel it will work proprelyyyy




![Screenshot from 2024-07-25 02-45-06](https://github.com/user-attachments/assets/6d93d328-fed5-4fb9-a4b5-b48053aa89ba)



Even if we unmounted our virtual SD Card the shell in QEMU still working fine

![Screenshot from 2024-07-25 02-51-28](https://github.com/user-attachments/assets/40bef411-b63a-4ac6-a6e1-63ebc65197eb)



![Screenshot from 2024-07-25 02-52-30](https://github.com/user-attachments/assets/53428169-0168-4e2c-97c8-91bc396fc755)


--------------------------------------------------------------------------------------------------------------------------------------------------------

But this was not our task -> our task was to make the initramfs boot manager and to switch between 2 aprtitions (rootfs)

So first thing we will go and split our rootfs into 2 partitions
   1- rootfs1
   2- rootfs2

go to Disks using your GUI



![Screenshot from 2024-07-25 02-47-05](https://github.com/user-attachments/assets/b8b34b2e-f3d9-4d79-8614-a87bfa4ee1de)



We will see our virtual SD Card has 2 partitions boot and rootfs we will 

   1- we will resize the rootfs partition
   
![Screenshot from 2024-07-25 02-54-32](https://github.com/user-attachments/assets/c308eb70-b781-4e87-acad-07fd96a949f5)


it's 863 megabytes we will split it in half sharply
so we will make it 431 megebytes



![Screenshot from 2024-07-25 02-56-24](https://github.com/user-attachments/assets/80e7e585-0289-4b7c-bdb4-e1c6176dc9d5)


now we have a free space with approximately the same size as rootfs we will assign the free space with
ext4 algorithm and name it rootfs2 and we also will change the name of the first to be rootfs1




![Screenshot from 2024-07-25 02-57-39](https://github.com/user-attachments/assets/7bbbac59-3dcf-4237-abcf-19f9022b4369)


And the final structure of the sd card will be:




![Screenshot from 2024-07-25 02-58-35](https://github.com/user-attachments/assets/4974583e-856e-4cf7-9b8e-0dc75e1c2fa4)



But the new rootfs is empty so we have to copy the files in the stagging area into it

```
sudo cp -r rootfs/* /media/saker/rootfs2
```


We also will make a flag or indicator in each rootfs to inform us which rootfs we are accessing now
   1- in rootfs1
      ```
      sudo touch rootfs1
      ```
   2- in rootfs2
      ```
      sudo touch rootfs2
      ```



![Screenshot from 2024-07-25 03-03-30](https://github.com/user-attachments/assets/ef6c1cfd-4fa4-4d27-82ac-d9ad24cd53d6)




![Screenshot from 2024-07-25 03-03-49](https://github.com/user-attachments/assets/cb57f9b5-a6f8-407a-a830-58121ba9bc7d)




-------------------------------------------------------------------------------------------------------------------------------------------------


Now we are done preparing and let's dive into the task itself


First thing we need to prepare our script which will handle the user input and the switch of filesystem


We will go under our stagging rootfs

```
cd ~/rootfs

sudo touch boot_manager.sh

sudo nano boot_manager.sh

```
and we will wirte our script

```

#!/bin/bash

echo "Choose the root filesystem to boot:"
echo "1) RootFS1"
echo "2) RootFS2"
read -p "Enter choice [1-2]: " choice

case "$choice" in
    1)
        ROOTFS="/mnt/rootfs1"
        ;;
    2)
        ROOTFS="/mnt/rootfs2" 
        ;;
    *)
        echo "Invalid choice"
        exit 1
        ;;
esac

echo "Switching to $ROOTFS..."
chroot "$ROOTFS"

```



![Screenshot from 2024-07-25 16-05-58](https://github.com/user-attachments/assets/1f1965e5-8aa6-4c23-93f9-b770eb64c27e)



then our initramfs is ready and we will create its image to be run in QEMU


```
cd ~/rootfs
find . | cpio -H newc -ov --owner root:root > ../initramfs.cpio
cd ..
gzip initramfs.cpio
mkimage -A arm -O linux -T ramdisk -d initramfs.cpio.gz uRamdisk


```
And we will will copy our uRamdisk into boot partition of virtual SD Card


```
sudo cp uRamdisk /media/saker/boot1

```


Then we launch QEMU


```
sudo qemu-system-arm -M vexpress-a9 -nographic -net nic -net tap,script=./script_new.sh -kernel ./u-boot -sd ~/sd.img


```


in u-boot we will initialize our kernel // dtb // initramfs and then boot

```
fatload mmc 0:1 $kernel_addr_r zImage
fatload mmc 0:1 $fdt_addr_r vexpress-v2p-ca9.dtb
fatload mmc 0:1 $initramfs uRamdisk

bootz $kernel_addr_r $initramfs $fdt_addr_r

```


then initramfs will launch easily

Untill now we didnt do anything differ from the first task but here is the new thing

![Screenshot from 2024-07-25 16-11-48](https://github.com/user-attachments/assets/ffe1b24a-b88f-4190-af42-335f0c620be3)



We will notice our script is appearing here and it's exeutable but the initramfs cant see all the parttiotions of the sd card


we will make directories for them and mount them


```
mount -t devtmpfs dev /dev

mkdir mnt/boot
mkdir mnt/rootfs1
mkdir mnt/rootfs2

mount -t ext4 /dev/mmcblk0p1 /mnt/boot
mount -t ext4 /dev/mmcblk0p2 /mnt/rootfs1
mount -t ext4 /dev/mmcblk0p3 /mnt/rootfs2

```

now all the partiotions of the sd card are mounted under /mnt


we will execute our script



![Screenshot from 2024-07-25 16-14-14](https://github.com/user-attachments/assets/3602add4-bf2c-4585-aa3a-ed84d79d9c3f)




We will chose the second rootfs


![Screenshot from 2024-07-25 16-14-36](https://github.com/user-attachments/assets/93985435-6528-4bc5-9077-d3cb3a0333e5)




Congratulations ... Now we are in the second rootfs and we opened a shell in it to do whatever you want







