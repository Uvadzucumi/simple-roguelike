#ifndef GAME_LOOP_H_INCLUDED
#define GAME_LOOP_H_INCLUDED

#include "game_db.h"
#include "char_generation.h"
#include "creature.h"
#include "worldmap.h"


class CGameLoop{
        CCreature *m_hero;
        CWorldMap *m_world_map;
    public:
        CGameLoop(CWorldMap *world_map, CCreature *hero);
        EGameState Events(int key);

        CCreature *getHero(){
            return m_hero;
        }
};

#endif // GAME_LOOP_H_INCLUDED
