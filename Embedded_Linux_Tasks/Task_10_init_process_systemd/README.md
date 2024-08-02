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


