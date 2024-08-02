# Making a kernel Image for Raspberry PI 4


First thing to do is to clone the raspberry pi linux repo

```
git clone --depth=1 https://github.com/raspberrypi/linux
cd linux

```
After that we need to configure our architectiure and the cross compiler

```
export CROSS_COMPILE=arm-linux-gnueabihf-
export ARCH=arm
```

and we need to configure the broadcom for raspberry pi

```
make bcm2711_defconfig
```
We need to set our configuration
1- make the compression type "xz"
2- make the kernel mount the devtmpfs
3- change the kernel name into your customized name

```
make menuconfig
```



Also we maximize the number of file descriptors

```
ulimit -n 8192

```

Then start to run and make our kernel

```
make -j4 zImage modules dtbs
```





