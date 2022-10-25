#include <iostream>
#include <string>

#include "base_menu.h"

BaseMenu::BaseMenu()
{
	MenuText = "Dont show this!";
};

BaseMenu::~BaseMenu(){};

void BaseMenu::printText()
{
	std::cout << BaseMenu::MenuText << std::endl;
};

