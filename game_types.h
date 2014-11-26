#ifndef TILES_LIST_H_INCLUDED
#define TILES_LIST_H_INCLUDED

#include <inttypes.h>

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
    GT_Biome_Beach,          // ellow .
    GT_Biome_Plains,         // green .
    GT_Biome_Forest,         // green *
    GT_Biome_Hills,          // brown ~
    GT_Biome_Mountain        // silver ^
};

enum EGameState{
    EGS_None,
    EGS_MainMenu,
    EGS_Pause,          // Save/Continue Game menu
    EGS_WorldMap,
    EGS_Exit
};
/*
enum EWorldMapObjects{
    WMO_CastleCity
    WMO_CIty,
    WMO_Villadge,
    WMO_Cave,
}
*/
// define types

struct Coords2i{
    int x, y;
};

struct Tile{
    char ch;
    uint32_t color;
};

struct WorldMapBiome{
    WM_Biome biome;     // biome type
    bool is_viewed;     // player view this map location
    int data;           // temporary data
};

#endif // TILES_LIST_H_INCLUDED
