#include <iostream>
#include <string>

#include "main_menu.h"
#include "set_data_menu.h"
#include "settings_menu.h"

MainMenu::MainMenu()
{
	MenuText = {"Main Menu \n"
				"Please make your Selection\n"
				"1 - setData\n"
				"2 - Settings\n"
				"3 - Quit\n"
				"Selection: \n"};
}

BaseMenu* MainMenu::getNextMenu(int choice, bool& isQuitOptionSelected)
{
	BaseMenu* aNewMenu = 0;

	switch (choice)
	{
		case 1:
			aNewMenu = new SetDataMenu();
			break;
		case 2:
			aNewMenu = new SettingsMenu();
			break;
		case 3:
			isQuitOptionSelected = true;
		default: {
		}
	}
	return aNewMenu;
}
