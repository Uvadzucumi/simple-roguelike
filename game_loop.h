#ifndef GAME_LOOP_H_INCLUDED
#define GAME_LOOP_H_INCLUDED

#include "game_types.h"
#include "char_generation.h"
#include "creature.h"


class CGameLoop{
        CCreature *m_hero;
    public:
        CGameLoop(CCreature *hero);
        EGameState Events(int key);
};

#endif // GAME_LOOP_H_INCLUDED
