#!/usr/bin/bash

sudo apt update

sudo apt install -y \
	cmake \
	git \
	git-gui \
	gitk \
	python3-pip

sudo snap install code --classic

pip3 install conan

if $(grep -q .local/bin ~/.bashrc)
then
	echo 'PATH=${PATH}:${HOME}/.local/bin' >> ~/.bashrc
	source ~/.bashrc
fi
