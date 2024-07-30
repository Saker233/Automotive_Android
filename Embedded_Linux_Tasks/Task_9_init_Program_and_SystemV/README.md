# Starting Up -The init Program

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

In System V we have several modes (Run Levels) each one of them has its own init process (we will discus how in a matter of time)


