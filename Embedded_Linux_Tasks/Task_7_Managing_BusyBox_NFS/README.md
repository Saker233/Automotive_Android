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
