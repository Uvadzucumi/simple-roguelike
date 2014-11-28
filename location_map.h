#ifndef LOCATION_MAP_H_INCLUDED
#define LOCATION_MAP_H_INCLUDED

#include "game_types.h"

#define BUILD_MAP_HEIGHT 128
#define BUILD_MAP_WIDTH 128

enum ELocationTileType{
    LTT_None,
    LTT_Grass,
    LTT_Road,
    LTT_Tree,
    LTT_Brash,
    LTT_Water,
    LTT_Sand,
    LTT_WallTree,
    LTT_WallStone,
    // portals
    LTT_DoorClosed,
    LTT_DoorOpened,
    LTT_DoorBroken,
    LTT_WindowClosed,
    LTT_WindowOpened,
    LTT_WindowBroken,
    LTT_StairsRight,
    LTT_StairsLeft
};

struct SLocationTile{
    ELocationTileType type;
    bool is_visible;
    bool is_block_view;
    bool is_block_movement;
    int portal_to;
    int portal_to_point;
};

class Portal{
    public:
        int w, h;
        SLocationTile *portal_tiles;
        char *name;
        bool outdor;
        Coords2i map_biome;
    bool LoadFromFile(const char *file_name){
        return true;
    }
};

class CLocation{
        int x, y;   // global map coordinates
    public:
        SLocationTile m_map[BUILD_MAP_HEIGHT*BUILD_MAP_WIDTH];
        BuildMap(int current_portal, int player_x, int player_y);
};

extern std::vector<Portal> PortalTypes;

#endif // LOCATION_MAP_H_INCLUDED
