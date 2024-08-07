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


| Name | Suffix | Description |
|----------|----------|----------|
| Service | .service | Defines a system service. This is the most common type of unit. It includes configuration for starting, stopping, and managing a service|
| Socket | .socket | Describes a socket that systemd manages. Socket units create file descriptors that services can listen to, and they usually have a corresponding |
| Device| .device  | Represents a device that is recognized by the kernel and exposed in the sysfs or udev device tree |
| Mount | .mount| Controls a mount point in the file system. These units are created automatically from /etc/fstab entries but can also be defined manually |
| Automount | .automount | Manages an automount point that mounts a file system automatically when accessed. It is usually used in combination with a .mount unit |
| Target | .target | Groups of units, Targets are similar to runlevels in SysV init systems, and they can bring the system to a specific state or coordinate the startup of multiple units |
| Network | .network| Describes the configuration of a network interface. It includes settings for configuring IP addresses, routes, DNS servers, These files are typically located in /etc/systemd/network/ |


But Before deep dive in the Unit concept let's first tell the different types of the processes in linux system

| Type of Process | Description |
|----------|----------|
| Foreground | A foreground process is a process that is started by the user from a terminal session and takes control of the terminal. The terminal waits for the process to complete before allowing further input. Users interact directly with foreground processes |
| Background | A background process is a process that runs independently of the terminal session. It allows the user to continue using the terminal while the process runs in the background, Like if you open google chrome and minimize it  |
| Orphan | An orphan process is a process whose parent has terminated or exited. Orphan processes are adopted by the init process (PID 1), which becomes their new parent. The init process is responsible for cleaning up orphan processes. |
| Zombie | A zombie process is a process that has completed execution but still has an entry in the process table. This occurs because the process's parent has not yet read the child's exit status using the wait() system call. The process is in a "zombie" state until the parent process reads its status and reaps the zombie process. |
| Daemon | A daemon process is a background process that is not associated with a terminal session. It typically starts at boot time and runs continuously, providing services to other processes or performing specific tasks. Daemons are often used for server tasks, like handling network requests or managing hardware. |


Let's take the Service Unit as an example to see what is the structure of the Unit


```
"Header Section"
[Unit]
Description = ""
Documentaion = ""
SourcePath = ""
After -> we give it another unit file
Before -> we give it another unit file
Wants -> we give it another unit file

[Service]
		Type
		ExecStart = <The application to run, only one on the whole Unit>
		ExecStop = <Run this application when you send stop signal to the servic>
		workdir = /usr/bin
		Restart= on-failure // always
		RestartSec = 3
```

## After
The After directive specifies that the current unit should be started after the specified units. It only affects the ordering of the units and does not imply a dependency; the specified units are not pulled in automatically.


## Before
The Before directive is the opposite of After. It specifies that the current unit should be started before the specified units. Like After, it only affects the ordering and does not imply a dependency.


## Wants
The Wants directive specifies a weak dependency. If the unit listed in Wants is available, it will be started, but if it fails or is not available, it will not cause the current unit to fail.



## Requires
The Requires directive specifies a strong dependency. If the unit listed in Requires is not available or fails to start, the current unit will also fail.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

## Type
We have 3 common types of the Type
	1- Simple
 		the application is coupled with the service, if we send kill to the service the application also will be killed
	2- forking
 		the application is not coupled with the service and if we stop the service the application can still run alone 
   	3- onehsot
    		Any application that run only one time and straight forward doesn't have any while loop or something
usually runs to initialize something then kill itself and stop the service


So, when we use systemctl stop with simple it also kill the application

When we use systemctl stop with forking the application is still running 


The daemon processes print its output to a file called "journalctl"


## ExecStart

The ExecStart directive specifies the command to execute when starting the service. This is the main process of the service
Equals to -> systemclt start


## ExecStop
The ExecStop directive specifies the command to execute when stopping the service. It is used to gracefully shut down the service
Equals to -> systemctl stop



## Restart
The Restart directive defines the restart policy for the service. It determines under which conditions systemd will attempt to restart the service if it stops

It could be:
	1- no         -> Do not restart the service automatically
 	2- always     -> Always restart the service regardless of the exit status
  	3- on-success -> Restart the service only if it exits with a successful exit status (0)
   	4- on-faliure -> Restart the service if it exits with a non-zero exit status, is terminated by a signal, or times out


## RestartSec

The RestartSec directive specifies the time to wait before attempting to restart the service after it has been stopped. This value is specified in seconds

```
[Service]
Restart=on-failure
RestartSec=5
```

![Screenshot from 2024-07-28 21-16-07](https://github.com/user-attachments/assets/289cbae4-bdcd-4abd-a634-bb21e4e6ac7d)



This is real example for a Service


--------------------------------------------------------------------------------------------------------------------------------------------------------------------
This is all fine theortical explanation of systemd, But how to actually create a service ?


## Creating a Service
We will create a service called -> myservice.service

```
cd /etc/systemd/system
sudo touch myservice.service
sudo nano  myservice.service
```

and its content will be

```
[Unit]
	Wants=mynetwork.network

[Service]
	Type=simple
	ExecStart=/usr/bin/ping 192.168.1.10 -c 3
	Restart=always
	RestartSec=3
	WorkingDirectory=/usr/bin

[Install]
	WantedBy=graphical.target

```
and we will create the other network which waneted

```
sudo touch mynetwork.network
sudo nano mynetwork.network
```

```
[Unit]
	Name="wlp0s20f3"

[Network]
	Address=192.168.100.58/24

```

Then we will start our service -> myservice.service

```
sudo systemctl start myservice.service

systemctl enable myservice.service
```
and to see the logs

```
journalctl -u myservice.service

```


![Screenshot from 2024-08-02 08-42-52](https://github.com/user-attachments/assets/4a806ce5-a010-4763-85fc-2634706c8df9)
