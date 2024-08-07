# Network Filesystem


What is a Network Filesystem in Linux?
A Network Filesystem (NFS) in Linux allows files to be shared across a network. This means that a file system on a server can be accessed by clients over the network as if it were a local filesystem. 
NFS is commonly used for centralized storage solutions, enabling multiple clients to access and share files seamlessly.


The staging directory can be exported to the network via an
NFS server and mounted by the target at boot time. This is often done during the
development phase, in preference to repeated cycles of creating a disk image and
reloading it onto the mass storage device, which is quite a slow process.


if your device has a network interface, it is often useful to mount the root filesystem over
the network during development. It gives you access to the almost unlimited storage on
your host machine, so you can add in debug tools and executables with large symbol tables.
As an added bonus, updates made to the root filesystem on the development machine are
made available on the target immediately. You can also access all the target's log files from
the host.


The NFS server needs to be told which directories are being exported to the network, which
is controlled by

```
/etc/exports
```
Now we have to make our task which is load our kernel and dtb file via TFTP and load our rootfs via NFS like a network expert


First thing we need the package which allow us to use NFS

```
sudo apt install nfs-kernel-server
```


![Screenshot from 2024-07-24 19-56-09](https://github.com/user-attachments/assets/210269ef-4a04-4e18-a23e-bf331abbb061)


Then we have to make the nfs run as daemon in the background to be permnantely active

```
systemctl status nfs-kernel-server
```

![Screenshot from 2024-07-24 19-58-25](https://github.com/user-attachments/assets/646a9d54-da3c-4821-b2c5-79ba84f70bc4)



After the installation and the active statue of the NFS all its configuration should be under /etc/exports
```
cat /etc/exports
```


Then we have to go and make a directory called nfs-share under /srv/ -beside the tftp if you remember-

```
sudo mkdir /srv/nfs-share
```


and we will copy the satgging rootfs content into that directory in odrer to make QEMU able to see this rootfs

```
sudo cp -rp ~/rootfs/* /srv/nfs-share
```


Now we have to configure both host and target IPs

to get the host IP

```
ifconfig
```

That's my personal IP

![Screenshot from 2024-07-24 20-10-48](https://github.com/user-attachments/assets/24ffc69e-4963-4fbc-87b8-8cf78f32dc22)



And we will configure any IP with the same subnet to QEMU but make sure it's not assigned to any other device

The assignation of NFS will be the /etc/exports


```
sudo nano /etc/exports

```
```
/srv/nfs-share 192.168.1.100(rw,no_root_squash,no_subtree_check)
```
![Screenshot from 2024-07-24 20-13-37](https://github.com/user-attachments/assets/2e4c6927-092b-46d5-8a11-f1a0de153d7e)




Then we have to restart the NFS to make the configuration applied

```
sudo systemctl restart nfs-kernel-server

```


All of that was on the host x86 linux machine now we will run into QEMU




## On QEMU




and launch QEMU

```
sudo qemu-system-arm -M vexpress-a9 -nographic -net nic -net tap,script=./script_new.sh -kernel ./u-boot -sd ~/sd.img

```


In Qemu

```
setenv serverip 192.168.100.58
setenv ipaddr 192.168.1.100
setenv bootargs 'console=ttyAMA0  root=/dev/nfs ip=192.168.1.100:::::eth0 nfsroot=192.168.1.8:/srv/nfs-share,nfsvers=3,tcp rw init=/sbin/init'
setenv Zimag_RAM_Add 60000000
setenv dtb_hardware_Add 65000000
saveenv
```

console=ttyAMA0: Specifies the console device. This is typically the serial console.
root=/dev/nfs: Indicates that the root filesystem is located on an NFS server.
ip=192.168.1.100:::::eth0: Specifies the IP address and network configuration. Here, the device IP is 192.168.1.100 and the network interface is eth0.
nfsroot=192.168.1.8:/srv/nfs-share,nfsvers=3,tcp rw: Specifies the NFS server and the path to the shared directory. The NFS server IP is 192.168.1.8, and the shared directory is /srv/nfs-share. The NFS version is set to 3, and TCP is used. The rw option means the filesystem will be mounted read-write.
init=/sbin/init: Specifies the initial program to run after the kernel is booted, which is /sbin/init.


Then we will load our zImage and dtb file via TFTP protocol

```
tftp $Zimag_RAM_Add /qemu/zImage
tftp $dtb_hardware_Add /qemu/vexpress-v2p-ca9.dtb
```


and to get rid of the hassle of each launch we will set our bootcmd with that

```
setenv bootcmd "echo "tftp $Zimag_RAM_Add /qemu/zImage;tftp $dtb_hardware_Add /qemu/vexpress-v2p-ca9.dtb"

saveenv
```



And finally to load both kernel // dtb //rootfs

```
bootz $Zimag_RAM_Add - $dtb_hardware_Add

```



![Screenshot from 2024-07-24 21-01-13](https://github.com/user-attachments/assets/bfdae336-3240-43dd-8616-f569202da67e)



![Screenshot from 2024-07-24 21-01-44](https://github.com/user-attachments/assets/dea485d1-0926-423a-a6ac-35b73bb6f79c)



VOILAAAAA we made the kernel and rootfs UPP with NFS and TFTP

![Screenshot from 2024-07-24 21-11-58](https://github.com/user-attachments/assets/dee496b2-c76b-45af-a94d-20685f96543b)

