
#include "game_loop.h"

CGameLoop::CGameLoop(CCharGeneration *char_gen){
    // create character by character generation class
}

void CGameLoop::Events(int key){
    std::cout << "GameLoop event: " << key << std::endl;
}
