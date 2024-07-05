Q1:

Questiuon one has 2 parts first one to implement the binary search algorithm and this is the easy part, second part is implementing it with vim editor and this is the hard part

1- first we make source file called binary search and we enter this file with vim

vim has mainly 3 modes
   1 - Normal(Command) mode -> used to control the file with commands
   2 - Insert mode -> used to actual write or edit in the file
   3 - Read Mode -> used to read the file only


![vim-modes](https://github.com/Saker233/Embedded-Linux/assets/130178079/d2723308-dbd4-46b5-9e8e-960cd5d9edf3)



So we first enter vim the default mode is the normal mode 


![Screenshot_2](https://github.com/Saker233/Embedded-Linux/assets/130178079/f4e5305a-de62-43a7-abf8-aac2e4c81eb9)


but we want to edit and write our own program so we want to switch to insert mode by pressing 'i'


![Screenshot_3](https://github.com/Saker233/Embedded-Linux/assets/130178079/21d8c268-8640-4d5f-8f6a-6fc58b5ff85d)


in the insert mode you are free to type and navigate in the whole file freely 

![Screenshot_4](https://github.com/Saker233/Embedded-Linux/assets/130178079/7711d34f-77a4-4321-953e-26d4bde21df9)


![Screenshot_5](https://github.com/Saker233/Embedded-Linux/assets/130178079/687f3bfe-b82f-47aa-a152-4fb4719b048e)

After you wrote your program and want to save and exit you have to go back to normal mode again by pressing "ESC"
To make vim let you save and exit we have to write a specific command ":wq" this mean I want to write and quite


![Screenshot_6](https://github.com/Saker233/Embedded-Linux/assets/130178079/d8fdbfa1-4b82-42fc-a8c7-49330a051fde)


So we go back to terminal and compile our file then execute the program easily and we see it working proprely



![Screenshot_7](https://github.com/Saker233/Embedded-Linux/assets/130178079/6817d149-bcd1-4a41-9087-5d1c783a7829)



Q2:


We moved the a.out binary from the building folder into /usr/local/bin by using the super user privilige
then I went back to the home directory and I attempted to execute that bianry and it works from anywhere!



![Screenshot_8](https://github.com/Saker233/Embedded-Linux/assets/130178079/56a68eed-895d-4702-af30-90b2d27ffac4)


The reason behind why it works from anywhere is that environment variable PATH which the system uses to detect the location of any command we ececute on the terminal
In the above screen shot I printed PATH and we can see /usr/local/bin in the PATH so when we wrote a.out the kernel went to check /usr/local/bin and found that a.out and executed it






# Na2na2a

1- List all the available shells

We can get all avalilabe shells from the file shells which is in /etc/shells
So we use the command cat to print the file content on the terminal "cat /etc/shells"



![Screenshot_1](https://github.com/Saker233/Embedded-Linux/assets/130178079/29ea26ab-e5c1-44d4-9226-5f6e5709fd1a)





2 - List all the environment varialbles in the system we use the command printenv




![Screenshot_2](https://github.com/Saker233/Embedded-Linux/assets/130178079/67bc2d4b-6be2-43eb-8506-766e5f437c93)







3 - Display your cuurent shell name

The current shell name or location is being stored in an environment varilable called SHELL so we easily print this variable



![Screenshot_3](https://github.com/Saker233/Embedded-Linux/assets/130178079/4ec4f2d5-14aa-4c5b-83f8-89602f90d154)







4- 

The backslash here as an escape sequnece for a new line to let you enter what echo gonna print


![Screenshot_4](https://github.com/Saker233/Embedded-Linux/assets/130178079/20645122-cf79-4644-96ea-390d2d08ba6a)






5-


![Screenshot_5](https://github.com/Saker233/Embedded-Linux/assets/130178079/0827fcd8-e1e3-4270-be5a-606a371d62d6)








