![Screenshot_8](https://github.com/Saker233/Embedded-Linux/assets/130178079/31ce3083-be15-442a-a076-8dc5c8622d70)#DayOneQuestions


1. List three Linux Distributions

    1 - Ubuntu
    2 - Fedora
    3 - Kali Linux
    4 - Red Hat
    5 - Arch Linux


2. From the slides what is the man command used for?

     It's a System wide documentation system which provides short reference mauals for individual commands, API functions, concepts, configuration file syntax and is organized in sections

3. What is the difference between rm and rmdir using man command?

     rm:
       ![Screenshot_1](https://github.com/Saker233/Embedded-Linux/assets/130178079/cd33660e-c20b-4396-8957-53f2385521ed)

   rmdir:
   
![Screenshot_2](https://github.com/Saker233/Embedded-Linux/assets/130178079/9e99033f-577a-499b-851f-bf393853c01e)



4.1
![Screenshot_3](https://github.com/Saker233/Embedded-Linux/assets/130178079/a3534097-fd66-4dcb-b797-4baae593776c)

a. 
![Screenshot_4](https://github.com/Saker233/Embedded-Linux/assets/130178079/3da93a4d-6b20-4fdf-8efc-c1a246633900)

I cant remove the directory becauase it is not empty
![Screenshot_5](https://github.com/Saker233/Embedded-Linux/assets/130178079/5d9a9abd-6857-46f4-a338-0276315e7dd7)
So I have tio delete it recursivley with the option -r

b.
![Screenshot_7](https://github.com/Saker233/Embedded-Linux/assets/130178079/5c271792-90d6-413e-96b0-f44860961553)
Here something really intersting ... the option -p with rmdir is also deleting the whole parental directories
Here when we used rmdir -p on OldFiles this also deleted the Document directory



c.  
![Screenshot_8](https://github.com/Saker233/Embedded-Linux/assets/130178079/e019a298-6c31-47df-8542-4b55d499c97a)
The relative path: /home/saker/docs/mycv
The absolute Path: /docs/mycv

5.
6.
![Screenshot_9](https://github.com/Saker233/Embedded-Linux/assets/130178079/d428818f-ee3b-409d-94e6-5ae467489faf)


7.
  1 - cd ~
  2 - cd /home/saker
  3 - cd .. --------- cd .. -------- cd home/saker


8.
![Screenshot_10](https://github.com/Saker233/Embedded-Linux/assets/130178079/e50ab152-fab6-4e69-bb85-6ea8ee529a86)



9. What command type are used for?
    1- Alias -> Are executed before anything else, Generally it is an alias name for another command (ls = ls --color=auto)
    2- Internal -> Commands that is part of the shell itself and deosnt have to be loaded from disk separately
    3- External -> Commands that exist as an executalbe file on the disk


10. Show 2 types of command file in /usr/bin that start with letter c

     ![Screenshot_11](https://github.com/Saker233/Embedded-Linux/assets/130178079/4d3096b0-031e-4631-b996-91dff94abc8a)

11.

man -k read files


12.
apropos command is doing exaclty like man -k which is search tyhe manual pages on a seach keyword





     
     
