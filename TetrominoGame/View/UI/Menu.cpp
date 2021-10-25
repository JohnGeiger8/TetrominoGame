//
//  Menu.cpp
//  TetrominoGame
//
//  Created by John Geiger on 10/24/21.
//

#include "Menu.hpp"

MainMenuUI::MainMenuUI()
{
    mMenuOptions = { };
}

void MainMenuUI::VUpdate()
{
    for (const ScreenElementPointer &element : mMenuOptions)
    {
        element->VUpdate();
    }
}

void MainMenuUI::AddMenuOption(ScreenElementPointer screenElement)
{
    if (screenElement != NULL)
        mMenuOptions.push_back(screenElement);
}

void MainMenuUI::RemoveMenuOption(ScreenElementPointer screenElement)
{
    // FIXME: implement
    printf("RemoveMenuOption not implemented");
}
