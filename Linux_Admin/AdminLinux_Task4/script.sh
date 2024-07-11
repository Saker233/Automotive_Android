#!/bin/bash



read -p "Please Enter the username of the new user: " USRNAME

read -p "Please Enter the name of the group: " GROUP

if [ -n "$GROUP" ]; then
	sudo groupadd "$GROUP"
else
	echo "Group Already Exist"
fi

if [ $(cat /etc/passwd | grep "$USRNAME" | wc -l) -gt 0 ]; then
	echo "Username already exist"
else
	sudo useradd "$USRNAME"
	echo "User Created"
fi
sudo usermod -aG "$GROUP" "$USRNAME"

echo "User Created"


