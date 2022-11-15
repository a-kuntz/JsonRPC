#!/usr/bin/bash

sudo apt update

sudo apt install -y \
	ccache \
	clang-format-9 \
	cmake \
	cmake-curses-gui \
	git \
	git-gui \
	gitk \
	python3-pip
sudo snap install code --classic

pip3 install conan
conan config init
conan profile update settings.compiler.libcxx=libstdc++11 default

if ! $(grep -q ccache ~/.bashrc)
then
	echo 'export PATH=/usr/lib/ccache:${PATH}' >> ~/.bashrc
	source ~/.bashrc
fi

if ! $(grep -q .local/bin ~/.bashrc)
then
	echo 'export PATH=${PATH}:${HOME}/.local/bin' >> ~/.bashrc
	source ~/.bashrc
fi
