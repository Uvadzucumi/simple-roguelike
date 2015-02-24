
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
    // movement section
    if((key>=TK_KP_1 && key<=TK_KP_9) || (key>=TK_RIGHT && key<=TK_UP)){
        int dx=0;
        int dy=0;
        switch(key){
            case TK_LEFT:
            case TK_KP_4: // move left
                dx=-1;
                break;
            case TK_RIGHT:
            case TK_KP_6: // move right
                dx=1;
                break;
            case TK_UP:
            case TK_KP_8: // move up
                dy=-1;
                break;
            case TK_DOWN:
            case TK_KP_2: // move down
                dy=1;
                break;
            case TK_KP_7: // move left up
                dx=-1; dy=-1;
                break;
            case TK_KP_9: // move right up
                dx=1; dy=-1;
                break;
            case TK_KP_1: // move left down
                dx=-1; dy=1;
                break;
            case TK_KP_3: // move right down
                dx=1; dy=1;
                break;
            default:
                printf("NOT FOUND ACTION!!!\n");
            break;
        }
        //printf("DX=%d DY=%d\n",dx,dy);
        if(dx!=0 || dy!=0){
            Coords2i new_pos=m_hero->getWorldPosition();
            new_pos.x+=dx;
            new_pos.y+=dy;
            if(m_world_map->isCanMove(new_pos.x, new_pos.y)){
                //m_hero->Move(dx, dy);
                m_hero->setWorldPosition(new_pos.x, new_pos.y);
            }else{
                printf("Way blocked!!!");
            }
        }
    }



    return EGS_Game;
}
