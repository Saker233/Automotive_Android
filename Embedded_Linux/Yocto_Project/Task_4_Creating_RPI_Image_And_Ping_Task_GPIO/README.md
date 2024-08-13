## Raspberry PI Image with Yocto

We have already made our custom image and successfully ran it but it was for QEMU-64

Now we need to make one but for raspberry PI and it has some changes we will deep dive in them shortly



## Prerequistes

    1- Poky (which we already has in kirkstone)

    2- meta-raspberrypi (which we will clone also kirkstone must be compatiable with poky)



To get the meta-raspberrypi we will clone it from its source


```
cd ~/poky

git clone -b kirkstone https://github.com/agherzan/meta-raspberrypi.git

```
now we have the meta-raspberypi but the poky has no idea of its existence so we will add it to our layers





![Screenshot from 2024-08-13 03-10-32](https://github.com/user-attachments/assets/3c8713f6-06c0-4002-bec7-25ed4f82d345)



first we will create our build environment for the RPI


```
source oe-init-build-env build-rpi


```


This will take you under a directory "build-rpi" which has an only one directory called "conf" and that conf has 2 importnat file

    1- local.conf

    2- bblayers.conf


to add the meta-raspberrypi access the bblayers,conf with your prefrable editor


and add your layer in the BBLAYERS variable

```
# POKY_BBLAYERS_CONF_VERSION is increased each time build/conf/bblayers.conf
# changes incompatibly
POKY_BBLAYERS_CONF_VERSION = "2"

BBPATH = "${TOPDIR}"
BBFILES ?= ""

BBLAYERS ?= " \
  /home/saker/poky/meta \
  /home/saker/poky/meta-poky \
  /home/saker/poky/meta-yocto-bsp \
  /home/saker/poky/meta-raspberrypi \
  "


```

Now the bitbake can see the layer which we added and it will include it during the build process


