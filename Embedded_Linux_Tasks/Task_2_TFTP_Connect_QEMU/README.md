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

