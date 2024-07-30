# Starting Up - The init Program

Now we have finally started our kernel and the rootfs and accessed a shell

But something always comes up which is the init program

Now its time to look at the init in more detail and discover why its very important to the rest of the system



There are many possible ways to implement init we will discuss 3 of them
  1- BusyBox init
	2- System V init
	3- systemd


 ## After The Kernel Boots

The init program is the first program to ever run and it has a root privilege and it PID is 1

If for some reason init cannot be started the kernel will panic

The init program is the ancestor of all other processes



In other words, init manages the life cycle of the system from boot up to shutdown. 
The current thinking is that init is well placed to handle other runtime events, 
such as a new hardware and the loading and unloading of modules. This is what systemd does.



## Introducing the init programs

As we said we have 3 ways to implement the init program,
but buildroot has options to build all three of them with init BusyBox as default,
Yocto allows you to choose between the System V init and systemd with System V as default



![Screenshot from 2024-07-27 23-57-57](https://github.com/user-attachments/assets/c8f1e534-887e-46b0-a9b6-1e713606bf24)



## BusyBox init


BusyBox as we seen has a minimal init program that uses a configuration file /etc/inittab to define rules to start programs at boot up and to stop them at shutdown,
Usually the actual work is done by shell scripts which by convention are placed in the /etc/init.d



init begins by reading /etc/inittab this conatins a list of programs to run one per line with the format -> <id>::<action>:<program>


id: This is the controlling Terminal for the command 
action: This is the conditions to run this command, as shown in the following paragraph program: This is the program to run



## SystemV


The BusyBox init not really used nowadays due to its very limitations

But what are the limitation of it ?

Let's first imagine a secenario if we have
	1- bluetooth initialization
 	2- WIFI inititalzation
  	3- Ethernet inititalzation
   	4- ETC.....

We need sometimes to initialize one of them and other times 2 of them and other times the Full functionalioty
But in BusyBox we cant do that -> we can initialize them all or not inititalzing anything

That concept of configuration called "Run level" in some specific Run Level we need some functionality and other Run level we need another functionalioty

We have migrated to that concept for 2 Reasons
	1- CPU utilization -> to not add a hassle to the CPU with some addition processes I dont need it at the time like the GUI process
 	2- RAM Usage -> Any addition process opens a stack frame in the RAM and if I don't need that process so I'm consuming memory for nothing


## System V for the rescue!

In System V we have several modes (Run Levels) each one of them has its own init process (we will discuss how in a matter of time)


0 -> shutdown
1 -> single user
2 -> multi user without network
3 -> multi user
4 -> user defined
5 -> GUI
6 -> Reset

So, How to make each run level?

We have the directory init.d which is under /etc/ which has all the scripts for different initialization




![Screenshot from 2024-07-30 14-46-28](https://github.com/user-attachments/assets/d039a88a-a263-4852-b543-2663fa1c4ee3)



This is the inittab in System V after we build our Buildroot in System V


we will notice this command

```
rcS:12345:wait:/etc/init.d/rcS


```

This will initialize our 1,2,3,4,5 run levels through the script rcS

but what is that script ?

this is script is located under -> /etc/init.d/rcS


![Screenshot from 2024-07-30 14-49-17](https://github.com/user-attachments/assets/a49b7fa4-de01-4db0-8c0b-45b0b3428a83)




This script will loop on all the other initialization beside rcS and decide to start them or stop them 



![Screenshot from 2024-07-30 14-51-36](https://github.com/user-attachments/assets/5e69a621-5c57-47c3-90b8-444745827f39)



This all the options we can do to each initialization scripts (Start - Stop - Restart)





![Screenshot from 2024-07-30 14-54-20](https://github.com/user-attachments/assets/c1ff2b71-818a-487b-9166-c39952fd9fec)





-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
This is all fine, but, how we can manually make a customized run level ?

under /etc/

we will create our different run levels

```
mkdir /etc/rc1.d

mkdir /etc/rc2.d

mkdir /etc/rc3.d
```

Each run level has its own folder

So, in run level 1 we don't need tftp but we need ssh (For example and illustration only not applicalple example)

So, we will make soft link for both of them but the soft link for network will be start with K and the ssh start with S

K -> Kill
S -> Start

```
ln -s /etc/init.d/network k01tftpd-hpa

ln -s /etc/init.d/ssh s02ssh
```


what that numbers after s and k ?
it's the priority which one will executed first the highest priority is 00


So, we will go through each run level we made with our own customized application S for start K for kill



![Screenshot from 2024-07-30 15-03-19](https://github.com/user-attachments/assets/647be57b-2cb1-4ed9-8acd-14670ce3e6d4)



NOTE: we only make soft links to scripts not to the original application because the original application is under /usr/bin


Now we have our own run level with its S's and K's

After that we will create a script rc.c to execute each run level


```
switch (run level)

1)
parsing for any file starts with k with for loop and when finding it it stop it

another for loop for any file starts by s with respect to the priority and when finding it we start it

```


So, to summarize System V:
	1- The kernel will firslty boots on "init" which is a System V init
 	2- init will go and parse the inittab
  	3- The inittab has sysinit action which will mount everything from rcS then run init 2 and get back to init again
   	4- init 2 this time will not execute sysinit action but will execute the wait action which will run rc.c script to initialize every script we
    		made to it a soft link, will start everything with S and kill everything with K, According to the run level we gave before the wait action

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------






