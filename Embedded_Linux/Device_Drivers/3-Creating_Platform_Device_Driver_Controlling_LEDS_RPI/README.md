# What is Platform Device Driver ?


A platform device driver in Linux is a type of device driver used to handle platform devices, 
which are typically integrated into the system's motherboard or chipset and are not discoverable through traditional mechanisms like PCI or USB. 
These devices are usually tightly coupled with the platform's hardware and have specific, well-defined resources such as memory regions, I/O ports, interrupts



## Why Use Platform Drivers?
Platform drivers are essential in embedded systems where many devices are integrated into the mainboard or SoC and require direct, low-level management by the operating system. 
They allow for a modular approach to handling hardware components, providing a clear separation between the hardware-specific code and the core kernel.






## Platform Device:

 platform device represents a device that is directly attached to the system's physical memory map and does not require bus enumeration like PCI or USB devices





## Platform Driver:

A platform driver is responsible for handling a specific platform device.
It registers itself with the kernel to handle the devices of a certain type.
The driver will probe for devices, initialize them, and provide the necessary operations (like read/write) for interacting with them.




## Components of a Platform Driver

1- Probe Function:

This function is called when a matching platform device is found.
The probe function typically initializes the hardware and registers the device with the appropriate subsystem.



2- Remove Function:

This function is called when the platform device is removed or the driver is unloaded.
It performs any necessary cleanup, such as freeing resources.





---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


# Task: Creating Platform Driver to Control 2 Leds on Raspberry PI


At first we will install Raspian OS on the target (RPI)



Then we will add our driver into the target and build it using the kernel headers but first we will ensure our kernel headers existence


First, verify your current kernel version using

```
uname -r


```


Use the package manager apt to install the kernel headers corresponding to your kernel version

```
sudo apt-get update
sudo apt-get install raspberrypi-kernel-headers


```

Then we will move to the directory where the drivers exists


and

```
make

```


Then we will have a lot of files we are concerned with the .ko files only

```
sudo insmod GPIO.ko

sudo insmod LED_RED.ko

sudo insmod LED_GREEN.ko
```


Now the kernel objects is loaded proprely


![Screenshot from 2024-08-12 02-45-23](https://github.com/user-attachments/assets/054391be-c263-4739-a832-f81e452fa582)








let's test the driver

to turn both leds on

```
echo "1" | sudo tee LED_RED


echo "1" | sudo tee LED_GREEN




```



To turn both leds off


```
echo "0" | sudo tee LED_RED


echo "0" | sudo tee LED_GREEN

```

[Watch the video on Google Drive](https://drive.google.com/file/d/1uuJ1d5BWFfqauwYR4NsMUdeyKpTEB4sf/view?usp=sharing)










