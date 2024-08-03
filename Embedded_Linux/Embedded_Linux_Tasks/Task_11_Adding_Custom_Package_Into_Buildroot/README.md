# Buildroot Packages

Buildroot is an open-source tool that simplifies the process of building embedded Linux systems.
It automates the creation of a complete and customizable Linux system for embedded devices
Including the cross-compilation toolchain, the bootloader, the kernel, and the root filesystem


In Buildroot, packages are software components that you can include in your root filesystem.
They range from basic utilities and libraries to full-fledged applications and daemons.
Buildroot provides a comprehensive set of packages organized into various categories.


But what if I have my own application and I want to merge to the rootfile system


Here is the recipe:

At first let's see where the packages are located in the buildroot and what it's consist of

```
cd ~/buildroot/packages
```

and for example let's take "nano" as example

![Screenshot from 2024-08-04 01-34-41](https://github.com/user-attachments/assets/828593c4-8c29-4b61-ba69-4b1118ea76b7)



It's consist of
  1- That patch file is the application itslef and could be anuthing else (in our task it will be a cpp file of multithreading)

  2- nano.hash -> it's the hash algorith which is calaulated to ensure the data integrity 

  3- Config.in -> configuration file used by Buildroot to define options and settings for packages (will be discuused shortly)

  4- nano.mk -> the Makefile which will define how the the package gonna be built



Now we understanded the anatomy of the buildroot package, Now it's time to do our custom package




firstly we will create a multithreading application in CPP





Simple multithreading application to print hello world in 3 threads even we didn't use mutex or semaphore


we will go under:

```
cd ~/buildroot/package

mkdir Demoapp

cd Demoapp

touch Demoapp.cpp

touch Demoapp.mk

touch Makefile

```


![Screenshot from 2024-08-04 02-02-33](https://github.com/user-attachments/assets/7245db6b-5510-4a82-b7e0-875ecaad1de9)






```
sudo nano Demoapp.cpp
```


```
#include <iostream>
#include <thread>

void printHelloWorld() {
    std::cout << "Hello, World!" << std::endl;
}

int main() {
    // Create three threads
    std::thread t1(printHelloWorld);
    std::thread t2(printHelloWorld);
    std::thread t3(printHelloWorld);

    // Wait for all threads to finish
    t1.join();
    t2.join();
    t3.join();

    return 0;
}


```

Then we will create our Makefile
```
.PHONY: clean
.PHONY: Demoapp

embeddedinn: Demoapp.cpp
    $(CC) -o '$@' '$<'

clean:
    -rm Demoapp

```



