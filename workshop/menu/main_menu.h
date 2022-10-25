#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "base_menu.h"

class MainMenu : public BaseMenu
{
    public:
    MainMenu();
    BaseMenu* getNextMenu(int choice, bool& isQuitOptionSelected);
};

#endif /*MAIN_MENU_H*/