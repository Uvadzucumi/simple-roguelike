#ifndef TILES_LIST_H_INCLUDED
#define TILES_LIST_H_INCLUDED

#include <inttypes.h>

class CRLGame;

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

// Game Tiles
enum EGameTile{
    GT_None,
    // WorldMap tiles
    GT_Biome_DeepWater,      // blue ~
    GT_Biome_ShallowWater,   // white-blue ~
    GT_Biome_Beach,          // yellow .
    GT_Biome_Plains,         // green .
    GT_Biome_Forest,         // green *
    GT_Biome_Hills,          // brown ~
    GT_Biome_Mountain        // silver ^
};

enum EGameState{
    EGS_None,
    EGS_MainMenu,
    EGS_CharGeneration,
    EGS_Pause,          // Save/Continue Game menu
    EGS_Game,
    EGS_WorldMap,
    EGS_Exit
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

// define types

struct Coords2i{
    int x, y;
    Coords2i&    operator-=(const Coords2i& c) {
        x -= c.x; y -= c.y; return *this;
    }
};

struct Tile{
    char ch;
    uint32_t color;
};

struct WorldMapBiome{
    WM_Biome biome;     // biome type
    bool is_viewed;     // player view this map location
    int island;         // temporary data
};

struct MenuEntry
{
	const char* name;
	void (CRLGame::*func)();
};




#endif // TILES_LIST_H_INCLUDED
