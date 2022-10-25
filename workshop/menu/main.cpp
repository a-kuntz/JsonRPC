#include <iostream>
#include "main_menu.h"
#include "base_menu.h"

int main (int argc, char **argv){
    BaseMenu* aCurrentMenu = new MainMenu;
    bool isQuitOptionSelected = false;
    while (!isQuitOptionSelected)
    {
        aCurrentMenu->printText();
        int choice = 0;
        std::cin >> choice;
        BaseMenu* aNewMenuPointer = aCurrentMenu->getNextMenu(choice, isQuitOptionSelected);

        if (aNewMenuPointer)
        {
            delete aCurrentMenu;
            aCurrentMenu = aNewMenuPointer;
        }
        
    }

    return true;
    
}