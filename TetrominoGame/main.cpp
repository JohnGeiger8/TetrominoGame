//
//  main.cpp
//  TetrominoGame
//
//  Created by John Geiger on 10/1/21.
//

#include <iostream>
#include "TetrominoApp.hpp"

//extern GlobalsMap g_pCvars;

int main(int argc, const char * argv[])
{
    // Initialize CVars map
    g_cvars = GlobalsMap();
    
    TetrominoApp* pTetrominoApp(new TetrominoApp(600));
    
    if (!pTetrominoApp->InitGame())
    {
        printf("Game Initialization failed.");
        return -1;
    }
    
    pTetrominoApp->MainLoop();
    
    delete(pTetrominoApp);
    pTetrominoApp = NULL;
    
    printf("Game over in Main");
    return 0;
}
