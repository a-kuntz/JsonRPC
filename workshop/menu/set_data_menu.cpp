#include <iostream>
#include <string>

#include "main_menu.h"
#include "set_data_menu.h"

SetDataMenu::SetDataMenu()
{
	MenuText = {"SetData Menu \n"
				"Please make your Selection\n"
				"1 - MainMenu\n"
				//"2 - Settings\n"
				"3 - Quit\n"
				"Selection: \n"};
}

BaseMenu* SetDataMenu::getNextMenu(int choice, bool& isQuitOptionSelected)
{
	BaseMenu* aNewMenu = 0;

	switch (choice)
	{
		case 1:
			aNewMenu = new MainMenu();
			break;
		// case 2:
		//  aNewMenu = new SettingsMenu();
		case 3:
			isQuitOptionSelected = true;
		default: {
		}
	}
  return aNewMenu;
}