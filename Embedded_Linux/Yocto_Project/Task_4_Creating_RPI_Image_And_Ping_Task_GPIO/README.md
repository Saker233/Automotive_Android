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
  /home/saker/meta_iti              \
  /home/saker/poky/meta-openembedded/meta-oe \
  /home/saker/poky/meta-openembedded/meta-python  \
  /home/saker/poky/meta-openembedded/meta-networking  \
  "


```

Now the bitbake can see the layer which we added and it will include it during the build process


Now we need to configure our distro to be customized as we need then we will create under conf a directory called "distro" and under distro we will add file "almaza.conf"






![Screenshot from 2024-08-13 04-48-13](https://github.com/user-attachments/assets/92843043-f569-45ed-9347-c84612ed22c9)







and access this file with any editor

```
require conf/distro/poky.conf

DISTRO = "Saker_Distro"
DISTRO_VERSION = "1.0"
MAINTAINER = "Mohamed Saker https://github.com/Saker233"


```
require will include the poky.conf which has a lot of variables related to the distro genration

we will override some of these variables like DISTRO_NAME DISTRO_VERSION MAINTAINER

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
## local.conf


In this file we will do most of our work in it


first thing we need to define the machine we will work wiht which is the raspberry PI and in my case it raspberry pi 4 (change it according to your target)


So, the first varibale to change is MACHINE

```
MACHINE ?= "raspberrypi4-64"

```

Our image will not run on a virtual target it will run on a real target so we need to define also the root filesystem which we will use

```
IMAGE_FSTYPES = "tar.bz2 ext4 rpi-sdimg"

```

We will also define the multithreading build to fast the image build (as we have done before)

don't copy and paste first check how many cores and threds do you have and also check Is your CPU support hyperthreading or not

In my case I have 6 cores and 12 thread then I will use 8 threds to be allocated to the build process

```
BB_NUMBER_THREADS ?= "8"
PARALLEL_MAKE ?= "-j 8"


```



OPTIONAL: I need some applications to be on the image when its run (python, ssh, apt, bash, git) if you need them then add these following lines if you don't skip this

Warning: it will add in space and time while buildiing

```
IMAGE_INSTALL:append = " python3"

IMAGE_INSTALL:append = " openssh"

IMAGE_INSTALL:append = " apt bash git"
```


We will aslo change some distro features like we will use systemd as the init process and if its fail we will use system V as a fallback and some other dependecies


```
DISTRO_FEATURES:append = " systemd"
DISTRO_FEATURES_BACKFILL_CONSIDERED += "sysvinit"
VIRTUAL-RUNTIME_init_manager = "systemd"
VIRTUAL-RUNTIME_initscripts = "systemd-compat-units"
IMAGE_INSTALL += " packagegroup-core-boot"



```



The last but not least, In my first build for the QEMU I already downloaded a lot of files from internet to be flashed on the Image


I don't want to download all of them again, these files are already located in the last build directory under 2 directories (downloads and sstate-cache)



```
DL_DIR ?= "/home/saker/poky/build/downloads"


SSTATE_DIR ?= "/home/saker/poky/build/sstate-cache"


```

This will skip the downloads and go to fetch the files he needs from this directoreies





All of the last steps will be added in the local.conf file


local.conf:

```
#
# This file is your local configuration file and is where all local user settings
# are placed. The comments in this file give some guide to the options a new user
# to the system might want to change but pretty much any configuration option can
# be set in this file. More adventurous users can look at
# local.conf.sample.extended which contains other examples of configuration which
# can be placed in this file but new users likely won't need any of them
# initially.
#
# Lines starting with the '#' character are commented out and in some cases the
# default values are provided as comments to show people example syntax. Enabling
# the option is a question of removing the # character and making any change to the
# variable as required.

#
# Machine Selection
#
# You need to select a specific machine to target the build with. There are a selection
# of emulated machines available which can boot and run in the QEMU emulator:
#
#MACHINE ?= "qemuarm"
#MACHINE ?= "qemuarm64"
#MACHINE ?= "qemumips"
#MACHINE ?= "qemumips64"
#MACHINE ?= "qemuppc"
#MACHINE ?= "qemux86"
#MACHINE ?= "qemux86-64"
#
# There are also the following hardware board target machines included for 
# demonstration purposes:
#
#MACHINE ?= "beaglebone-yocto"
#MACHINE ?= "genericx86"
#MACHINE ?= "genericx86-64"
#MACHINE ?= "edgerouter"
#
# This sets the default machine to be qemux86-64 if no other machine is selected:


#
# Where to place downloads
#
# During a first build the system will download many different source code tarballs
# from various upstream projects. This can take a while, particularly if your network
# connection is slow. These are all stored in DL_DIR. When wiping and rebuilding you
# can preserve this directory to speed up this part of subsequent builds. This directory
# is safe to share between multiple builds on the same machine too.
#
# The default is a downloads directory under TOPDIR which is the build directory.
#
#DL_DIR ?= "${TOPDIR}/downloads"

#
# Where to place shared-state files
#
# BitBake has the capability to accelerate builds based on previously built output.
# This is done using "shared state" files which can be thought of as cache objects
# and this option determines where those files are placed.
#
# You can wipe out TMPDIR leaving this directory intact and the build would regenerate
# from these files if no changes were made to the configuration. If changes were made
# to the configuration, only shared state files where the state was still valid would
# be used (done using checksums).
#
# The default is a sstate-cache directory under TOPDIR.
#
#SSTATE_DIR ?= "${TOPDIR}/sstate-cache"

#
# Where to place the build output
#
# This option specifies where the bulk of the building work should be done and
# where BitBake should place its temporary files and output. Keep in mind that
# this includes the extraction and compilation of many applications and the toolchain
# which can use Gigabytes of hard disk space.
#
# The default is a tmp directory under TOPDIR.
#
#TMPDIR = "${TOPDIR}/tmp"

#
# Default policy config
#
# The distribution setting controls which policy settings are used as defaults.
# The default value is fine for general Yocto project use, at least initially.
# Ultimately when creating custom policy, people will likely end up subclassing 
# these defaults.
#


DISTRO ?= "poky"
# As an example of a subclass there is a "bleeding" edge policy configuration
# where many versions are set to the absolute latest code from the upstream 
# source control systems. This is just mentioned here as an example, its not
# useful to most new users.
# DISTRO ?= "poky-bleeding"

#
# Package Management configuration
#
# This variable lists which packaging formats to enable. Multiple package backends
# can be enabled at once and the first item listed in the variable will be used
# to generate the root filesystems.
# Options are:
#  - 'package_deb' for debian style deb files
#  - 'package_ipk' for ipk files are used by opkg (a debian style embedded package manager)
#  - 'package_rpm' for rpm style packages
# E.g.: PACKAGE_CLASSES ?= "package_rpm package_deb package_ipk"
# We default to rpm:

PACKAGE_CLASSES ?= "package_rpm"

#
# SDK target architecture
#
# This variable specifies the architecture to build SDK items for and means
# you can build the SDK packages for architectures other than the machine you are
# running the build on (i.e. building i686 packages on an x86_64 host).
# Supported values are i686, x86_64, aarch64
#SDKMACHINE ?= "i686"

#
# Extra image configuration defaults
#
# The EXTRA_IMAGE_FEATURES variable allows extra packages to be added to the generated
# images. Some of these options are added to certain image types automatically. The
# variable can contain the following options:
#  "dbg-pkgs"       - add -dbg packages for all installed packages
#                     (adds symbol information for debugging/profiling)
#  "src-pkgs"       - add -src packages for all installed packages
#                     (adds source code for debugging)
#  "dev-pkgs"       - add -dev packages for all installed packages
#                     (useful if you want to develop against libs in the image)
#  "ptest-pkgs"     - add -ptest packages for all ptest-enabled packages
#                     (useful if you want to run the package test suites)
#  "tools-sdk"      - add development tools (gcc, make, pkgconfig etc.)
#  "tools-debug"    - add debugging tools (gdb, strace)
#  "eclipse-debug"  - add Eclipse remote debugging support
#  "tools-profile"  - add profiling tools (oprofile, lttng, valgrind)
#  "tools-testapps" - add useful testing tools (ts_print, aplay, arecord etc.)
#  "debug-tweaks"   - make an image suitable for development
#                     e.g. ssh root access has a blank password
# There are other application targets that can be used here too, see
# meta/classes/image.bbclass and meta/classes/core-image.bbclass for more details.
# We default to enabling the debugging tweaks.
EXTRA_IMAGE_FEATURES ?= "debug-tweaks"

#
# Additional image features
#
# The following is a list of additional classes to use when building images which
# enable extra features. Some available options which can be included in this variable
# are:
#   - 'buildstats' collect build statistics
USER_CLASSES ?= "buildstats"

#
# Runtime testing of images
#
# The build system can test booting virtual machine images under qemu (an emulator)
# after any root filesystems are created and run tests against those images. It can also
# run tests against any SDK that are built. To enable this uncomment these lines.
# See classes/test{image,sdk}.bbclass for further details.
#IMAGE_CLASSES += "testimage testsdk"
#TESTIMAGE_AUTO:qemuall = "1"

#
# Interactive shell configuration
#
# Under certain circumstances the system may need input from you and to do this it
# can launch an interactive shell. It needs to do this since the build is
# multithreaded and needs to be able to handle the case where more than one parallel
# process may require the user's attention. The default is iterate over the available
# terminal types to find one that works.
#
# Examples of the occasions this may happen are when resolving patches which cannot
# be applied, to use the devshell or the kernel menuconfig
#
# Supported values are auto, gnome, xfce, rxvt, screen, konsole (KDE 3.x only), none
# Note: currently, Konsole support only works for KDE 3.x due to the way
# newer Konsole versions behave
#OE_TERMINAL = "auto"
# By default disable interactive patch resolution (tasks will just fail instead):
PATCHRESOLVE = "noop"

#
# Disk Space Monitoring during the build
#
# Monitor the disk space during the build. If there is less that 1GB of space or less
# than 100K inodes in any key build location (TMPDIR, DL_DIR, SSTATE_DIR), gracefully
# shutdown the build. If there is less than 100MB or 1K inodes, perform a hard halt
# of the build. The reason for this is that running completely out of space can corrupt
# files and damages the build in ways which may not be easily recoverable.
# It's necessary to monitor /tmp, if there is no space left the build will fail
# with very exotic errors.
BB_DISKMON_DIRS ??= "\
    STOPTASKS,${TMPDIR},1G,100K \
    STOPTASKS,${DL_DIR},1G,100K \
    STOPTASKS,${SSTATE_DIR},1G,100K \
    STOPTASKS,/tmp,100M,100K \
    HALT,${TMPDIR},100M,1K \
    HALT,${DL_DIR},100M,1K \
    HALT,${SSTATE_DIR},100M,1K \
    HALT,/tmp,10M,1K"

#
# Shared-state files from other locations
#
# As mentioned above, shared state files are prebuilt cache data objects which can be
# used to accelerate build time. This variable can be used to configure the system
# to search other mirror locations for these objects before it builds the data itself.
#
# This can be a filesystem directory, or a remote url such as https or ftp. These
# would contain the sstate-cache results from previous builds (possibly from other
# machines). This variable works like fetcher MIRRORS/PREMIRRORS and points to the
# cache locations to check for the shared objects.
# NOTE: if the mirror uses the same structure as SSTATE_DIR, you need to add PATH
# at the end as shown in the examples below. This will be substituted with the
# correct path within the directory structure.
#SSTATE_MIRRORS ?= "\
#file://.* https://someserver.tld/share/sstate/PATH;downloadfilename=PATH \
#file://.* file:///some/local/dir/sstate/PATH"

#
# Yocto Project SState Mirror
#
# The Yocto Project has prebuilt artefacts available for its releases, you can enable
# use of these by uncommenting the following lines. This will mean the build uses
# the network to check for artefacts at the start of builds, which does slow it down
# equally, it will also speed up the builds by not having to build things if they are
# present in the cache. It assumes you can download something faster than you can build it
# which will depend on your network.
# Note: For this to work you also need hash-equivalence passthrough to the matching server
#
#BB_HASHSERVE_UPSTREAM = "hashserv.yocto.io:8687"
#SSTATE_MIRRORS ?= "file://.* http://sstate.yoctoproject.org/all/PATH;downloadfilename=PATH"

#
# Qemu configuration
#
# By default native qemu will build with a builtin VNC server where graphical output can be
# seen. The line below enables the SDL UI frontend too.
PACKAGECONFIG:append:pn-qemu-system-native = " sdl"
# By default libsdl2-native will be built, if you want to use your host's libSDL instead of 
# the minimal libsdl built by libsdl2-native then uncomment the ASSUME_PROVIDED line below.
#ASSUME_PROVIDED += "libsdl2-native"

# You can also enable the Gtk UI frontend, which takes somewhat longer to build, but adds
# a handy set of menus for controlling the emulator.
#PACKAGECONFIG:append:pn-qemu-system-native = " gtk+"

#
# Hash Equivalence
#
# Enable support for automatically running a local hash equivalence server and
# instruct bitbake to use a hash equivalence aware signature generator. Hash
# equivalence improves reuse of sstate by detecting when a given sstate
# artifact can be reused as equivalent, even if the current task hash doesn't
# match the one that generated the artifact.
#
# A shared hash equivalent server can be set with "<HOSTNAME>:<PORT>" format
#
#BB_HASHSERVE = "auto"
#BB_SIGNATURE_HANDLER = "OEEquivHash"

#
# Memory Resident Bitbake
#
# Bitbake's server component can stay in memory after the UI for the current command
# has completed. This means subsequent commands can run faster since there is no need
# for bitbake to reload cache files and so on. Number is in seconds, after which the
# server will shut down.
#
#BB_SERVER_TIMEOUT = "60"

# CONF_VERSION is increased each time build/conf/ changes incompatibly and is used to
# track the version of this file when it was generated. This can safely be ignored if
# this doesn't mean anything to you.
CONF_VERSION = "2"




DL_DIR ?= "/home/saker/poky/build/downloads"


SSTATE_DIR ?= "/home/saker/poky/build/sstate-cache"


MACHINE ?= "raspberrypi4-64"
IMAGE_FSTYPES = "tar.bz2 ext4 rpi-sdimg"


BB_NUMBER_THREADS ?= "8"
PARALLEL_MAKE ?= "-j 8"
IMAGE_INSTALL:append = " python3"

IMAGE_INSTALL:append = " openssh"

IMAGE_INSTALL:append = " apt bash git"


DISTRO_FEATURES:append = " systemd"
DISTRO_FEATURES_BACKFILL_CONSIDERED += "sysvinit"
VIRTUAL-RUNTIME_init_manager = "systemd"
VIRTUAL-RUNTIME_initscripts = "systemd-compat-units"
IMAGE_INSTALL += " packagegroup-core-boot"




IMAGE_INSTALL:append = " \
    python3 \
    util-linux \
    bluez5 \
    i2c-tools \
    bridge-utils \
    hostapd \
    iptables \
    wpa-supplicant \
    pi-bluetooth \
    bluez5-testtools \
    udev-rules-rpi \
    linux-firmware \
    iw \
    kernel-modules \
    linux-firmware-ralink \
    linux-firmware-rtl8192ce \
    linux-firmware-rtl8192cu \
    linux-firmware-rtl8192su \
    linux-firmware-rpidistro-bcm43455 \
    linux-firmware-bcm43455 \
    connman \
    connman-client \
    dhcpcd \
    openssh \
    psplash \
    psplash-raspberrypi \
    coreutils \
"



DISTRO_FEATURES:append = " \
    bluez5 \
    bluetooth \
    wifi \
    pi-bluetooth \
    linux-firmware-bcm43455 \
    systemd \
    usrmerge \
    ipv4 \
"

MACHINE_FEATURES:append = " \
    bluetooth \
    wifi \
"

IMAGE_FEATURES:append = " \
    splash \
"
IMAGE_INSTALL:append = " xserver-xorg xf86-video-fbdev xf86-input-evdev xterm m>



IMAGE_INSTALL += "pingled"




```



Now we are more than ready to start the build process


```
cd /build-rpi


bitbake core-image-minimal

```


It will take some times, depends on the internet speed and the CPU efficiency and the speed of the harddisk itself


------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

## Issue I encountered while building

There was a problem with my firewall preventing the port 9418 which is used for the git protocol. Some bitbake recipes are using this protocol for cloning repos



So we are making it use http instead, Run these commands before running the bitbake or after the bitbake terminated for errors

```
git config --global url."https://github.com/".insteadOf git@github.com:
git config --global url."https://".insteadOf git://

```

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

## Task -> Create e recipe to be included with the Image to ping on a specific IP when it's success Turn led on otherwise turn it off



Until now we have just created the Imgae with all its requiments only but we need to create the recipe whcih will allow is to do so




I've already created a layer outside the poky directory called "meta_iti"




![Screenshot from 2024-08-14 10-08-16](https://github.com/user-attachments/assets/5b08cef5-1fbe-484a-b7cd-d13bf4b619ac)









![Screenshot from 2024-08-14 10-09-08](https://github.com/user-attachments/assets/e48a3755-cd80-4cf3-bf0b-b7af02f35418)










I have created 2 things the recipe and the application itself



the application -> ping_led.sh

```
#!/bin/bash


LED_RED_PIN=2
LED_GREEN_PIN=3


if [ -z "$1" ]; then
    echo "Usage: $0 <IP_ADDRESS>"
    exit 1
fi


IP_ADDRESS="$1"


setup_gpio() {
    echo "$LED_RED_PIN" > /sys/class/gpio/export
    echo "$LED_GREEN_PIN" > /sys/class/gpio/export
    echo "out" > /sys/class/gpio/gpio$LED_RED_PIN/direction
    echo "out" > /sys/class/gpio/gpio$LED_GREEN_PIN/direction
}


cleanup_gpio() {
    echo "$LED_RED_PIN" > /sys/class/gpio/unexport
    echo "$LED_GREEN_PIN" > /sys/class/gpio/unexport
}


control_leds() {
    if ping -c 1 "$IP_ADDRESS" > /dev/null 2>&1; then
        echo "1" > /sys/class/gpio/gpio$LED_GREEN_PIN/value
        echo "0" > /sys/class/gpio/gpio$LED_RED_PIN/value
    else
        echo "0" > /sys/class/gpio/gpio$LED_GREEN_PIN/value
        echo "1" > /sys/class/gpio/gpio$LED_RED_PIN/value
    fi
}


main() {
    setup_gpio

    while true; do
        control_leds
        sleep 10  
    done
}


trap cleanup_gpio EXIT

main


```



Then we create our recipe which will provide the image of the existence of the applciation to be included inside the image building process


```
SUMMARY = "A script to ping an IP and control LEDs based on the result"
DESCRIPTION = "This recipe installs a Python script that pings a specified IP and controls LEDs on a Raspberry Pi."


LICENSE = "CLOSED"


SRC_URI = "file://ping_led.sh"

# Set the destination directory for the script
do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${WORKDIR}/ping_led.py ${D}${bindir}/ping_led.sh
}


```
This recipe suposed to load the application inside the image under /usr/bin




[Watch the video on Google Drive](https://drive.google.com/file/d/1GJgNccpXLCKmGiETpylUMbr_EcdPz0vL/view?usp=sharing)











