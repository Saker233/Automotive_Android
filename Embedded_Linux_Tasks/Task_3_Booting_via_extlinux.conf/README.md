# We can boot the QEMU via The extlinux.conf and the bootflow scan command


Firstly we will create a directory on our FAT16 boot partition called extlinux

and inside that dir we will touch a file called extlinux.conf


![Screenshot from 2024-07-22 00-06-25](https://github.com/user-attachments/assets/a17e2eb7-1f5f-491c-8933-1b1043e9254b)




We also have to make our extlinux script to make it load the Zimage and the dtb file

```                            
LABEL boot
        KERNEL ../zImage
        fdtdir ../myfile.dtb

```


