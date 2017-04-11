#!/bin/bash

#Need to install prerequisit python packages matplotlib and pyserial

#matplotlib
sudo apt-get install -y python-matplotlib
sudo apt-get install -y python-tk

#pyserial
if hash pip 2>/dev/null; then
	pip install pyserial
elif hash easy_install 2>/dev/null; then
	easy_install -U pyserial
else
	echo "Neither pip or easy_install available, installing from source"
	wget https://pypi.python.org/packages/ce/9c/694ce79a9d4a164e109aeba1a40fba23336f3b7554978553e22a5d41d54d/pyserial-3.1.tar.gz#md5=e849af7f8b7ec75cbc7a53da67c51a51 
	tar -zxvf ./pyserial*.tar.gz
	rm ./pyserial*.tar.gz
	cd pyserial*
	sudo python setup.py install
fi

