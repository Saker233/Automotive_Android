# Task1: How to create a tap connection between QEMU and linux

To establish a connection between your Linux machine and QEMU without an Ethernet cable or NIC, follow these steps:

### On the Linux Machine

1. Create a TAP port connection:

```bash

ip a add 192.168.1.8/24 dev tap

```

1. Set the TAP port up:

```bash

ip link set tap up

```

1. Verify the connection by running:

```bash

ifconfig

```

You should see the TAP interface listed.

![Screenshot from 2024-07-17 01-57-01](https://github.com/user-attachments/assets/24b9967a-9636-461e-8764-10f82a74c243)




### On the QEMU Side

1. If needed, delete an existing TAP connection to avoid conflicts:

```bash

sudo ip link delete <tap_name>

```

1. Create a bash script for TAP connection initialization. Save the following script as `script_new.sh`:

```bash
bashCopy code
#!/bin/bash

ip a add 192.168.1.8/24 dev $1
ip link set $1 up

```

1. Launch QEMU with the following command:

```bash

sudo qemu-system-arm -M vexpress-a9 -nographic -net nic -net tap,script=./script_new.sh -kernel ~/u-boot/u-boot -sd ~/sd.img

```

This setup will establish a network connection between your Linux machine and QEMU using a TAP interface.

---

How to load a file into QEMU RAM

firstly we will create the file in the virtual sd card

```bash
sudo touch myscript
```

Then we will run QEMU emulator

```bash
sudo qemu-system-arm -M vexpress-a9 -nographic -net nic -net tap,script=./script_new.sh -kernel ~/u-boot/u-boot -sd ~/sd.img
```

```bash
bdinfo
```

will show all the board inforamtion and sepcifically the DRAM start address which is 0x60000000


![Screenshot from 2024-07-17 03-05-12](https://github.com/user-attachments/assets/aba25f54-3a49-435e-b98c-e5d6f46da0ca)




```bash
fatload mmc 0:1 0x60000000 myscript
```

This will go and write the file “myscript” into the specific memory address

```bash
md 0x60000000
```

This will show the specific address 


![Screenshot from 2024-07-17 03-07-13](https://github.com/user-attachments/assets/cf36702f-acea-496f-aa41-554ecd49293c)


----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Task2: How to make a file (u-boot script) on the virtual SD Card and make it run once QEMU Boots

1- we gonna create our script on the FAT16 partition in the virtual SD Card -> myscript.txt



![Screenshot from 2024-07-17 16-36-25](https://github.com/user-attachments/assets/1e314ace-63c2-4ab8-9305-89d7d92694f6)




2- we will launch QEMU emulator with the command



```bash
sudo qemu-system-arm -M vexpress-a9 -nographic -net nic -net tap,script=./script_new.sh -kernel ~/u-boot/u-boot -sd ~/sd.img
```


3- we will write our script in myscript.txt (the script written in u-boot commands not bash)

```bash
if mmc dev; then
    fatload mmc 0:1 0x60002000 zImage
    fatload mmc 0:1 0x60002500 myfile.dtp
elif ping 192.168.1.8; then
    echo "load from network"
else
    echo "No Option"
fi

setenv loadbootsc no
saveenv


```
 The use of loadbootsc is not being executing the script twice while booting

 ![Screenshot from 2024-07-17 23-52-17](https://github.com/user-attachments/assets/e46d8edd-a734-47fa-91a9-343f2feaccf1)

So now we have to generate our bootscript as an image, it's now a .txt file the u-boot don't understand this format
So we have a command called mkimage to generate our image from a .txt file so we will use the scrip as follows

```bash
mkimage -T script -n "Bootscript" -C none -d myscript.txt vxpress-bootscript

```

after we create our script as an image to be loaded we have 2 do 2 things
  1- change the bootcmd command by setenv
      ```bash
        fatload mmc 0:1 0x60003000 vxpress-bootscript; source 0x60003000
        ```
        This means that if bootcmd gonna run it will
            1- load the file vxpress-bootscript into RAM at address 0x60003000
            2- run the script fromt the same address
            3- saveenv to save the variable


After we closed QEMU and Launched again we can see clearly that the our script ran successfully

The autoboot process
![Screenshot from 2024-07-18 00-35-07](https://github.com/user-attachments/assets/28f97888-42e6-44b9-80d6-629004a82cc0)



ZImage
![Screenshot from 2024-07-18 00-35-32](https://github.com/user-attachments/assets/90e93492-9fca-469a-8101-6e94710408dd)


myfile.dtp
![Screenshot from 2024-07-18 00-35-59](https://github.com/user-attachments/assets/29dd333a-0bfb-421c-a2de-3acee8590fa1)




The script(Image)
![Screenshot from 2024-07-18 00-36-24](https://github.com/user-attachments/assets/48411e64-1daa-4ca5-992a-0894219774a2)







