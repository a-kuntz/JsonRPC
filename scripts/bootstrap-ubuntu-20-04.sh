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
conan config init
conan profile update settings.compiler.libcxx=libstdc++11 default

if $(grep -q .local/bin ~/.bashrc)
then
	echo 'PATH=${PATH}:${HOME}/.local/bin' >> ~/.bashrc
	source ~/.bashrc
fi
