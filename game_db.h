#ifndef GAME_DB_H_INCLUDED
#define GAME_DB_H_INCLUDED

#include "game_types.h"
#include <vector>

struct CharacterClass{
    int id;
    const char *name;
};

struct CharacterSkill{
    int id;
    const char *name;
};

struct CharacterEffect{
    int id;
    const char *name;
};

extern std::vector<CharacterClass> CharacterClasses;
extern std::vector<CharacterSkill> CharSkills;
extern std::vector<CharacterEffect> CharEffects;


#endif // GAME_DB_H_INCLUDED
