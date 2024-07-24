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
