#ifndef GAME_LOOP_H_INCLUDED
#define GAME_LOOP_H_INCLUDED

#include "char_generation.h"
#include "creature.h"

class CGameLoop{
        CCreature *hero;
    public:
        CGameLoop(CCharGeneration *char_gen);
        void Events(int key);
};

#endif // GAME_LOOP_H_INCLUDED
