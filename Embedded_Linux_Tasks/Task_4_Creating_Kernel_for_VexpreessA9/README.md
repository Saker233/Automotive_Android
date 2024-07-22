![Screenshot from 2024-07-22 03-57-03](https://github.com/user-attachments/assets/6db35da3-c002-4594-aceb-3c2cc8201bd7)![Screenshot from 2024-07-22 03-47-11](https://github.com/user-attachments/assets/60acceb5-0e53-49ae-8a6c-5bee63e5049a)# Making a kernel Image for Vexpress A9 board running on QEMU

first we have to clone the linux repo

```
git clone --depth=1 git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git

cd linux

export CROSS_COMPILE=~/x-tools/arm-cortexa9_neon-linux-musleabihf/bin/arm-cortexa9_neon-linux-musleabihf-

export ARCH=arm
```

--depth=1 -> to get the last commit only and neglect the commits history (Reduce Size)

Then we go the configuration menu to configure Vexpress A9

```
make vexpress_defconfig
```

![Screenshot from 2024-07-22 03-19-20](https://github.com/user-attachments/assets/e84205a4-d76b-4bfa-a363-b3b8936b087f)







```
make menuconfig
```

And The configuration menu gonna show


  1- We will disable the EXT3 file system and enable only the EXT$
    ![Screenshot from 2024-07-22 03-26-14](https://github.com/user-attachments/assets/cc5c66da-8698-4f96-9024-7806c367705c)


  2- We will choose our kernel Compression type (default is gzip)
    We will chose the xz because its smaller in size by 30% than gzip
    NOTE: that doesnt differ in the end of the size of the kernel in the RAM
    but while compiling the kernel xz has an edge of smaller in size
    but also it slower in execution
    ![Screenshot from 2024-07-22 03-25-33](https://github.com/user-attachments/assets/2c37f4f8-6b42-4f9d-9a11-2d24163476f1)





    

    ![Screenshot from 2024-07-22 03-25-46](https://github.com/user-attachments/assets/34097ff0-fa44-4560-816e-0be829f22d9f)



    

  3- Change the Kernel name into you name [[OPTIONAL]]


  ![Screenshot from 2024-07-22 03-31-48](https://github.com/user-attachments/assets/b2d18251-3036-4fd4-88c8-cd61bec89891)

  

Leave everything in the default save & exit


Make and build the kernel


```
 make -j4 zImage modules dtbs
```


And it finishes successfully
![Screenshot from 2024-07-22 03-38-51](https://github.com/user-attachments/assets/305c2dcc-4598-45fa-aaa4-d5c45b780159)



we can see the output zImage on /arch/arm/boot



![Screenshot from 2024-07-22 03-44-02](https://github.com/user-attachments/assets/27f38ce3-64a7-4733-beb0-66509dd9d1c9)



and the dts we can find it under /arch/arm/boot/dts/arm "vexpress-v2p-ca9.dtb"





![Screenshot from 2024-07-22 03-47-11](https://github.com/user-attachments/assets/1d11073a-b2f9-4cbf-9110-6eab5a9bdbe1)






Now we have 2 files
  1- zImage
  2- vexpress-v2p-ca9.dtb

We can boot it on QEMU in 3 methods
  1- Flashing it Manually via fatload
  2- Flashing it by TFTP protocol
  3- Using the flow extlinux with bootflow scan





## 1- Flashing it Manually via fatload

First we gonna copy the two files into our virtual SD card

```
sudo cp vexpress-v2p-ca9.dtb /media/saker/boot1

sudo cp ~/linux/arch/arm/boot/zImage /media/saker/boot1
```


Then launch QEMU

```
sudo qemu-system-arm -M vexpress-a9 -nographic -net nic -net tap,script=./script_new.sh -kernel ./u-boot -sd ~/sd.img

```

First load the image on the address $kernel_addr_r

```
fatload mmc 0:1 $kernel_addr_r zImage
fatload mmc 0:1 $fdt_addr_r vexpress-v2p-ca9.dtb
```
![Screenshot from 2024-07-22 03-57-03](https://github.com/user-attachments/assets/76650a8b-27b1-4cab-a587-ec27054eb858)









