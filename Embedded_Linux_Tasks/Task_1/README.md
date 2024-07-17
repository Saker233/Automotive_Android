# How to create a tap connection between QEMU and linux

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







