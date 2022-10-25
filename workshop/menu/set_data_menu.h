#ifndef SET_DATA_MENU_H
#define SET_DATA_MENU_H

#include "base_menu.h"


class SetDataMenu : public BaseMenu {
public:
  SetDataMenu();
  BaseMenu *getNextMenu(int choice, bool &isQuitOptionSelected);

};

#endif /*SET_DATA_MENU_H*/