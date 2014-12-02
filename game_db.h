#ifndef GAME_DB_H_INCLUDED
#define GAME_DB_H_INCLUDED

#include <inttypes.h>
#include <vector>
#include <iostream>

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

class CRLGame;

// main game state ////////////////////////////////////
enum EGameState{
    EGS_None,
    EGS_MainMenu,
    EGS_CharGeneration,
    EGS_Pause,          // Save/Continue Game menu
    EGS_Game,
    EGS_WorldMap,
    EGS_Exit
};

// World Map Biomes //////////////////////////////////
enum WM_Biome{
    WMB_DeepWater,      // blue ~
    WMB_ShallowWater,   // white-blue ~
    WMB_Beach,          // ellow .
    WMB_Plains,         // green .
    WMB_Forest,         // green *
    WMB_Hills,          // brown ~
    WMB_Mountain        // silver ^
};

// Characters classes
enum ECharClass{
    CC_Knight,
    CC_Paladin,
    CC_Archer,
    CC_Druid,
    CC_Cleric,
    CC_Sorcerer
};
// Character Skills
enum ECharSkills{
// weapon scills
    CS_Sword=0,
    CS_Axe,
    CS_Spear,
    CS_Mace,
    CS_Dagger,
    CS_Staff,
    CS_Archery,
    CS_Ancient,
// Armor scills
    CS_LeatherArmor,
    CS_ChainMail,
    CS_PlateArmor,
    CS_Shields,
// Magic scills
    CS_MagicFile,
    CS_MagicSky,
    CS_MagicWater,
    CS_MagicEarth,

    CS_MagicSpirit,
    CS_MagicMind,
    CS_MagicBody,

    CS_MagicLight,
    CS_MagicDark,

    CS_SKillsCount
};

enum ECharEffects{
    CE_Poison,      //
    CE_Diseased,    //
    CE_Afraid,      //
    CE_Insane,      //
    CE_Drunk,       //
    // another effects
    CE_Weak,        // -50% damage by weapon
    CE_Asleep,      // skip turns to first damage
    CE_Cursed,      // success cast spells 1/3%
    //
    CE_Unconscious,
    CE_Paralyzed,
    CE_Stoned,
    CE_Dead,
    CE_Eradicated
};

// Game Tiles //////////////////////////////////////////
enum EGameTile{
    GT_None,
    // WorldMap tiles
    GT_Biome_DeepWater,      // blue ~
    GT_Biome_ShallowWater,   // white-blue ~
    GT_Biome_Beach,          // yellow .
    GT_Biome_Plains,         // green .
    GT_Biome_Forest,         // green *
    GT_Biome_Hills,          // brown ~
    GT_Biome_Mountain,       // silver ^

    GT_Ground,
    GT_Grass,
    GT_Road,
    GT_RoadStone,
    GT_Floor,
    GT_FloorStone,
    GT_FloorMramor,
    GT_Tree,
    GT_TreeApple,
    GT_Bush,
    GT_BrushCurrant,
    GT_BrushGooseberry,

    GT_WallWoden,
    GT_WallStone,
    GT_WallOldStone,
    GT_WallMramor,

    GT_Window,
    GT_WindowOpen,

    GT_DoorWooden,
    GT_DoorWoodenOpen,
    GT_DoorStone,
    GT_DoorStoneOpen,

    GT_StairsWest,
    GT_StairsEast,
    GT_StairsNorth,
    GT_StairsSouth
};

// define types

struct Coords2i{
    int x, y;
    Coords2i& operator-=(const Coords2i& c) {
        x -= c.x; y -= c.y; return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const Coords2i& p){
        os << "[" << p.x << ", " << p.y << "]";
        return os;
    }
};

struct TileDisplay{
    char ch;
    uint32_t color;
};

struct TileGame{
    EGameTile tile_type;
    bool is_viewed;
    bool is_view;
    bool is_can_move;
};

struct WorldMapBiome{
    WM_Biome biome;     // biome type
    bool is_viewed;     // player view this map location
    int island;         // temporary data
    unsigned int biome_seed;
};

struct MenuEntry
{
	const char* name;
	void (CRLGame::*func)();
};


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

extern std::vector<TileDisplay> GameTiles;



#endif // GAME_DB_H_INCLUDED

