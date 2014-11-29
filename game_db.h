#ifndef GAME_DB_H_INCLUDED
#define GAME_DB_H_INCLUDED

#include "game_types.h"
#include <vector>

struct CharacterClass{
    ECharClass id;
    const char *name;
    ECharSkills def_skills[2];
};

struct CharacterSkill{
    ECharSkills id;
    const char *name;
    bool class_access[6];               // skill access for character classes
    bool create_access;
};

struct CharacterEffect{
    ECharEffects id;
    const char *name;
};

extern std::vector<CharacterClass> CharClasses;
extern std::vector<CharacterSkill> CharSkills;
extern std::vector<CharacterEffect> CharEffects;



#endif // GAME_DB_H_INCLUDED
