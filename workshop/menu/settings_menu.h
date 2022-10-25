#ifndef SETTINGS_MENU_H
#define SETTINGS_MENU_H

#include "base_menu.h"

class SettingsMenu : public BaseMenu
{
public:
	SettingsMenu();
	BaseMenu* getNextMenu(int choice, bool& isQuitOptionSelected);
};

#endif /*SETTINGS_MENU_H*/