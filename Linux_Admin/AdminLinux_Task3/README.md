# Task3 AdminLinux


Q1:
the bash script in the above file, I made a script to firsly check .bashrc file exist or not
if exist we gonna append >> one envrionment varialbe and one local variable
then open a new terminal to make .bashrc run again and inject these variables


![Screenshot_1](https://github.com/Saker233/Embedded-Linux/assets/130178079/420bc179-1bb5-48fe-b9cc-d45e35d9a6c4)




Q2:

1-
I got listed the /usr/bin commands and redircted them into /tmp/commands.list


![Screenshot_2](https://github.com/Saker233/Embedded-Linux/assets/130178079/553f6174-b279-4ee9-8c00-2beefbc2d8ba)



2-



3-


![Screenshot_3](https://github.com/Saker233/Embedded-Linux/assets/130178079/8bab4f19-0659-4231-a56f-0fea767f58fd)



4-
a- cat filename1 | cat filename2 -> this will display the content of filename2 only
b- ls | rm -> This will list the files in a specific dir then take this output as an input for the rm command, it will reomve all the listed files
c- ls /etc/passwd | wc-l ->> This will list all the passwords in etc then count how many lines in these passwords




5-
first we should ionstall the package mlocate to be able to use the command locate "sudo apt install mlocate"

-> locate .profile

this command search in the whole database of the system


![Screenshot_4](https://github.com/Saker233/Embedded-Linux/assets/130178079/1d5c9d4f-2f6a-4f89-a66c-0beada98db33)


6-

![Screenshot_5](https://github.com/Saker233/Embedded-Linux/assets/130178079/e5e27e55-370b-41e0-946c-5b6b64bb0a23)



->>>>>  ls -i / && ls-i /etc && ls -i /etc/hosts




7- Symbolic link


![Screenshot_6](https://github.com/Saker233/Embedded-Linux/assets/130178079/c495264b-90dd-46dd-8620-f2f7da286216)




![Screenshot_7](https://github.com/Saker233/Embedded-Linux/assets/130178079/33a826b0-62de-49ca-be5f-7a38318a6564)




8- Hard Link

I cant make a hard link here because passwd is a directory not a file and hard lonks goes only on files


9-



![Screenshot_8](https://github.com/Saker233/Embedded-Linux/assets/130178079/ff475cc9-3db9-45bb-8fb7-5e54c6e46180)











