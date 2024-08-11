# What is Platform Device Driver ?


A platform device driver in Linux is a type of device driver used to handle platform devices, 
which are typically integrated into the system's motherboard or chipset and are not discoverable through traditional mechanisms like PCI or USB. 
These devices are usually tightly coupled with the platform's hardware and have specific, well-defined resources such as memory regions, I/O ports, interrupts


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





