
#include "game_loop.h"

CGameLoop::CGameLoop(CWorldMap *world_map, CCreature *hero){
   m_hero=hero;
   m_world_map=world_map;
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
