#ifndef BASE_MENU_H
#define BASE_MENU_H

#include <string>

class BaseMenu
{
public:
	BaseMenu();
	virtual ~BaseMenu();
	virtual BaseMenu* getNextMenu(int choice, bool& isQuitOptionSelected) = 0;
	virtual void      printText();
protected:
	std::string MenuText;
};

#endif /* BASE_MENU_H */