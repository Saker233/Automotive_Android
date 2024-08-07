# Character Device Driver


A character device is typically transfers data to and from user application instantly reading or writing the byte data in character by character stream


They provide the framework for many typical drivers such as video capture or audio devices 


We will disscus the character device and how it can be used to pass inforamtion between user space and LKM which is running in the kernel space


Example

C user space application sends a string to LKM, The LKM then responds with the message that was sent along with the number of letters that the message contains



## Major and Minor Numbers

Device drivers have an assosiated major and minor numbers

For Example /dev/ram0 and /dev/null are assosiated with a driver with major number 1 and /dev/tty0 and /dev/ttyS0 are associated with a driver with major number 4


Tha major number is used by the kernel to identify the correct device driver when the device is accessed


The role of the minor number is device dependent and is handled internally within the driver




![Screenshot from 2024-08-07 03-58-28](https://github.com/user-attachments/assets/dab6d468-e369-4411-b4eb-64bc46862759)







![Screenshot from 2024-08-07 03-59-15](https://github.com/user-attachments/assets/c205e863-b409-4e79-affc-094c1bd8c0e5)









Each device has ID of 32 bits [ Major 12bits, Minor 20bits]






![Screenshot from 2024-08-07 04-01-32](https://github.com/user-attachments/assets/2a37234f-fe53-4639-b22f-767ecff8a6be)





The ID stored in a variable from type dev_t which is uint32



## How to give ID to a device


Gladly the kernel provide us with a function to do such a thing


```
# this function check dynamically for free location and allocate
alloc_chrdev_regoin(&mydevice_id , 0 , 1 , "iti_driver" );

# this function return bool , 0 if sucess , -1 if failed to allo
# arg 1 >> variable of type dev_t that will store ID generated
# arg 2 >> base minor 0 ,, start count devices from 0
# arg 3 >> number of devices this driver responsbile for
# arg 4 >> driver name

```
this function will create Major number for this device , and Minor number 0 ,
cuz its first device and start from 0 


To print this IDs

```
printk(" %d , %d \n",MAJOR(mydevice_id) , MINOR(mydevice_id )

```



But when exit we must deallcate the stored ID


```
# arg 1 >> variable that store device id
# arg 2 number of devices

unregister_chrdev_regoin(mydevice_id,1);

```



## File Operations

The file_operations data structure that is defined in /linux/fs.h holds pointers to functions (function pointers) within a driver that allows you to define the behavior of certain file operations


```
 // Note: __user refers to a user-space address.
struct file_operations {
   struct module *owner;                             // Pointer to the LKM that owns the structure
   loff_t (*llseek) (struct file *, loff_t, int);    // Change current read/write position in a file
   ssize_t (*read) (struct file *, char __user *, size_t, loff_t *);    // Used to retrieve data from the device
   ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *);   // Used to send data to the device
   ssize_t (*aio_read) (struct kiocb *, const struct iovec *, unsigned long, loff_t);  // Asynchronous read
   ssize_t (*aio_write) (struct kiocb *, const struct iovec *, unsigned long, loff_t); // Asynchronous write
   ssize_t (*read_iter) (struct kiocb *, struct iov_iter *);            // possibly asynchronous read
   ssize_t (*write_iter) (struct kiocb *, struct iov_iter *);           // possibly asynchronous write
   int (*iterate) (struct file *, struct dir_context *);                // called when VFS needs to read the directory contents
   unsigned int (*poll) (struct file *, struct poll_table_struct *);    // Does a read or write block?
   long (*unlocked_ioctl) (struct file *, unsigned int, unsigned long); // Called by the ioctl system call
   long (*compat_ioctl) (struct file *, unsigned int, unsigned long);   // Called by the ioctl system call
   int (*mmap) (struct file *, struct vm_area_struct *);                // Called by mmap system call
   int (*mremap)(struct file *, struct vm_area_struct *);               // Called by memory remap system call
   int (*open) (struct inode *, struct file *);             // first operation performed on a device file
   int (*flush) (struct file *, fl_owner_t id);             // called when a process closes its copy of the descriptor
   int (*release) (struct inode *, struct file *);          // called when a file structure is being released
   int (*fsync) (struct file *, loff_t, loff_t, int datasync);  // notify device of change in its FASYNC flag
   int (*aio_fsync) (struct kiocb *, int datasync);         // synchronous notify device of change in its FASYNC flag
   int (*fasync) (int, struct file *, int);                 // asynchronous notify device of change in its FASYNC flag
   int (*lock) (struct file *, int, struct file_lock *);    // used to implement file locking
   …
};

```


The driver we will implement for the read and write functions is the implementation of this function, If you didnt provide implementation to the functions above simply it will point to NULL



## udev


Its a service from systemd services which act like a device manager to create any character device

We want udev to make a file for our virtual device


Under /sys/class 

there are several categories: Network // GPIO // tty // I2C


![Screenshot from 2024-08-07 04-27-49](https://github.com/user-attachments/assets/569e7dd2-1cfe-484f-adf0-6c31f31a9835)




To create a class:


```
# variable of type class to recive return in it
struct class *iti_class;

# create class
iti_class = class_create("iti_class");
if(iti_class==NULL) >> printk("couldn't create class \n");

# now the class is created but empty
# create directory under class
device_create(iti_class,NULL,mydevice_id,NULL , dirname);

# it return bool also 


```

Each driver create a directory of these category under /sys/class





![Screenshot from 2024-08-07 04-32-15](https://github.com/user-attachments/assets/afd27cd4-a74b-40aa-9137-8fa361a05a44)




or manually

```
mknod filename c 5 0
# c >> character device
# 5 >> Major number
# 0 >> Minor

```


And eventually we have to destroy it in the end

```
device_destroy(iti_class,mydevice_id )
class_destroy(iti_class);

```

Now we have the ID of the device (major and minor)


we can do this

```
echo 1 > /dev/file

```


But what actually happen here, To answer this we have to explain the VFS



## VFS -> Virtual File System && Device Nodes


The Virtual File System (VFS) in Linux is an abstraction layer that provides a common interface for different file systems. 
It allows applications to access different types of file systems in a uniform way, without needing to know the specifics of the underlying file system



In Linux, the Virtual File System (VFS) and device nodes are closely related concepts that help manage hardware devices in a uniform way through the file system interface



Device nodes are special file system entries that represent hardware devices. They allow the kernel to interface with device drivers using standard file I/O operations


Device nodes use major and minor numbers to identify the specific device driver and device instance


## Interaction Between VFS and Device Nodes


VFS allows device nodes to be accessed using the same system calls (open, read, write, etc.) as regular files, providing a uniform interface for hardware interaction


When a device node is accessed, VFS routes the request to the appropriate device driver based on the major and minor numbers



So, Generally, The VFS use the file operations struct to get its methods which will be used with the device nodes


----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


# Device Driver Implementation



we will create 3 files

     1- File_Operations.c
     2- File_Operations.h
     3- main.c


THe driver will be File_Operations and the main.c is the user space application which we will interact with

