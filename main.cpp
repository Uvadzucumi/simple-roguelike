#include <iostream>

#define GAME_TITLE "Simple Roguelike Game by Fantik (c) 2014"

#include "items.h"
#include "game.h"

using namespace std;

int main()
{
    cout << GAME_TITLE << endl;

    CRLGame *game=new CRLGame();
    if(game->isError()){
        cout << "Create Game error: " << game->getLastError() << std::endl;
        return -1;
    }
    return game->Run();

}
