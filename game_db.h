#ifndef GAME_DB_H_INCLUDED
#define GAME_DB_H_INCLUDED

#include "game_types.h"
#include <vector>

#define COLOR_RED           0xffff0000
#define COLOR_FLAME         0xffff3f00
#define COLOR_ORANGE        0xffff7f00
#define COLOR_AMBER         0xffffbf00
#define COLOR_YELLOW        0xffffff00
#define COLOR_LIME          0xffbfff00
#define COLOR_CHARTREUSE    0xff7fff00
#define COLOR_GREEN         0xff00ff00
#define COLOR_SEA           0xff00ff7f
#define COLOR_TURQUOISE     0xff00ffbf
#define COLOR_CYAN          0xff00ffff
#define COLOR_SKY           0xff00bfff
#define COLOR_AZURE         0xff007fff
#define COLOR_BLUE          0xff0000ff
#define COLOR_HAN           0xff4f00ff
#define COLOR_VIOLET        0xff7f00ff
#define COLOR_PURPLE        0xffbf00ff
#define COLOR_FUCHSIA       0xffff00ff
#define COLOR_MACHETA       0xffff00bf
#define COLOR_PINK          0xffff007f
#define COLOR_CRIMSON       0xffff003f
#define COLOR_GREY          0xff7f7f7f
#define COLOR_BLACK         0xff000000
#define COLOR_WHITE         0xffffffff

#define COLOR_BRASS         0xffbf9760
#define COLOR_COOPER        0xffc4887c
#define COLOR_GOLD          0xffe5bf00
#define COLOR_SILVER        0xffcbcbcb


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

extern std::vector<Tile> GameTiles;



#endif // GAME_DB_H_INCLUDED

