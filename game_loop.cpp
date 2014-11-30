
#include "game_loop.h"

CGameLoop::CGameLoop(CCreature *hero){
   m_hero=hero;
}

EGameState CGameLoop::Events(int key){
    std::cout << "GameLoop event: " << key << std::endl;
    if(key==TK_M){
        if (terminal_state(TK_SHIFT)){
            return EGS_WorldMap;
        }
    }

    return EGS_Game;
}
