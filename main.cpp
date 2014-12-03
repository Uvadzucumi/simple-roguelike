#include <iostream>

#define GAME_TITLE "Simple Roguelike Game by Fantik (c) 2014"

#include "items.h"
#include "game.h"

using namespace std;

int main(int argc, char **argv){
/*
    printf("Аргументов: %d\n",argc);
    for(int i=0;i<argc;i++){
        printf("\t%d. %s\n",i,argv[i]);
    }
*/

    cout << GAME_TITLE << endl;

    unsigned int world_seed=0;

    if(argc > 1){
        world_seed = atoi(argv[1]);
    }

    if(!world_seed){
        srand(time(NULL));
        world_seed=rand()%RAND_MAX;
    }

//    world_seed=297785060;

    CRLGame *game=new CRLGame(world_seed);
    if(game->isError()){
        cout << "Create Game error: " << game->getLastError() << std::endl;
        return -1;
    }
    return game->Run();

}
