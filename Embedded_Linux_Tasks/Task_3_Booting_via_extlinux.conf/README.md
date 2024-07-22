sudo qemu-system-arm -M vexpress-a9 -nographic -net nic -net tap,script=~/Desktop/A9/script_new.sh -kernel ~/Desktop/A9/u-boot -sd ~/sd.img

# We can boot the QEMU via The extlinux.conf and the bootflow scan command


Firstly we will create a directory on our FAT16 boot partition called extlinux

and inside that dir we will touch a file called extlinux.conf


![Screenshot from 2024-07-22 00-06-25](https://github.com/user-attachments/assets/a17e2eb7-1f5f-491c-8933-1b1043e9254b)




We also have to make our extlinux script to make it load the Zimage and the dtb file

```                            
LABEL boot
        KERNEL ../zImage
        FDT ../myfile.dtb

```
then we will launch QEMU 

```
sudo qemu-system-arm -M vexpress-a9 -nographic -net nic -net tap,script=./script_new.sh -kernel ./u-boot -sd ~/sd.img

```

#Issues I encountred and How I overcome


The bootflow scan was somehow scanning my whole partition of EFI not the virtual SD Card which I made the extlinux directory on it

so I noticed that there was an envrionmnmet called "boot_targets" which was the paths that booflow scan search for flows on it

I made

```
setenv boot_targets mmc0
```

To force the bootflow scan searching for flows in my virual sd card and finally After hassle
