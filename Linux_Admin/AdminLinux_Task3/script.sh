#!/bin/bash



if [ -f ~/.bashrc ]; then
	echo "export HELLO=HOSTNAME" >> ~/.bashrc
	echo "LOCAL=$(whoami)" >> ~/.bashrc
	
	
fi

gnome-terminal
