# systemd


We have already covered the BusyBox init and the System V init

System V was more robust than BusyBox whhic was so simple and not relevant to nowadays systemd

The problem with BusyBox as we said that it has only one run level so we cant reduce the needless consume of the CPU and RAM


But what is the problem with System V ?

The main problem with system V is the rc.c file we have just made in the last task

The rc.c file is generally a 2 for loops one to loop over all the scripts which start with 'S' and the other to loop on all the scripts starts with 'K'


This is a time consuming because we work now sequentially and we have to wait for each script to finish and go to the next


This approach is no fit or suitable in any way with the modern CPUs which has multicores and support the hyperthreading technology


We need to work on all the init processes concurrently and init the system in a parallel approach


## So let's introduce systemd 


systemd is a modern approach to deal with the init process and it's used with all the latest modern linux distros

NOTE: there is a great debate and arguning with the linux fans and the UNIX fans because the latter are seeing that System V is better but linux community is more convinced with systemd


![Screenshot from 2024-07-27 23-57-57](https://github.com/user-attachments/assets/4db89088-465f-48ce-8518-63bafcc993c7)




As we see in the table above the booting speed in SystemV is slow and medium in systemd and this why we shifted somehow to systemd



systemd init process is under -> /sbin/init

That is the same path as SystemV and BusyBox and that's the point they want to be generic and whether you use any process you can use the same path



We have 2 main directories in systemd

  1- /etc/systemd/system      -> contains the unit files that define the services, targets, and other units that systemd manages
  2- /etc/systemd/system.conf -> contains the global configuration options for systemd
  3- /lib/systemd/system      -> contains the unit files that are provided by the installed packages and copy of the unit
  4- /run/systemd/system      -> contains the runtime unit files that are created by systemd




## Unit concept

systemd has a concept called "Unit" which is located under /etc/systemd/system


What is the meaning of Unit?

First let's indroduce the types of Unit and it's determined with the suffix of the file:
  1- Service   -> .service   -> Defines a system service. This is the most common type of unit. It includes configuration for starting, stopping, and managing a service
  
  2- Socket    -> .socket    -> Describes a socket that systemd manages. Socket units create file descriptors that services can listen to, and they usually have a corresponding
  
  3- Device    -> .device    -> Represents a device that is recognized by the kernel and exposed in the sysfs or udev device tree
  
  4- Mount     -> .mount     -> Controls a mount point in the file system. These units are created automatically from /etc/fstab entries but can also be defined manually
  
  5- Automount -> .automount -> Manages an automount point that mounts a file system automatically when accessed. It is usually used in combination with a .mount unit
  
  6- Target    -> .target    -> Groups of units, Targets are similar to runlevels in SysV init systems, and they can bring the system to a specific state or coordinate the startup of multiple units
  
  7- Network   -> .network   -> Describes the configuration of a network interface. It includes settings for configuring IP addresses, routes, DNS servers, These files are typically located in /etc/systemd/network/.
  



