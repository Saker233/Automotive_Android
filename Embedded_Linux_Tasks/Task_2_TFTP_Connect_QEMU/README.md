# We need to transfer files between QEMU and a Linux Machine via the protocol TFTP


# first thing to install TFTP on the linux machine

```bash
sudo apt install tftpd-hpa
```
We will notice that a new directory has beed created under /srv called tftp
and a new user has been created to the system called tftp

Now on the linux machine we have to configure the tftp to be R/W

```
sudo nano /etc/default/tftpd-hpa
```

![Screenshot from 2024-07-21 23-09-47](https://github.com/user-attachments/assets/474b6402-8a15-4d14-ad50-5bf8d2cc184c)


We will add this "--create" to options

and also to let the QEMU's TFTP Access the linux machine we will grant and access to the tftp user to the directory /srv/tftp

```
sudo chown tftp /srv/tftp
```

This will change the owner of this directory to be the tftp so he can R/W

# On the QEMU Side


We will change the bootcmd to run this

```
setenv serverip 192.168.1.8;
saveenv;
tftp $kernel_addr_r zImage;
tftp $fdt_addr_r vxpress-bootscript;

```


![Screenshot from 2024-07-21 23-44-21](https://github.com/user-attachments/assets/e2ab4c9c-78c0-449b-a5f9-2a367644fcef)








![Screenshot from 2024-07-21 23-44-48](https://github.com/user-attachments/assets/d9fb03fa-1632-441c-9e0a-558172e7ad32)











