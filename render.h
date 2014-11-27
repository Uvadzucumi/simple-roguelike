#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include "game_types.h"
#include "worldmap.h"
#include "menu.h"
#include "char_generation.h"

#include "include/BearLibTerminal.h"

#include <iostream>

class CRender{
    public:

    ~CRender(){
        terminal_close();
    }

    bool Init(){
        if(!terminal_open()){
            return false;
        }else{
            terminal_refresh();
            terminal_set("window: size=80x25, cellsize=auto, title='Simple RL Game'; font: default");
            terminal_color("white");
        }
        return true;
    }

    void WorldMap(CWorldMap *wm);                   // render worldmap screen
    void CharGeneration(CCharGeneration *ch);       //
    void Menu(CMenu *m);

// return tile by tile id
    Tile getTileById(EGameTile tile_id){
        Tile tile;
        switch(tile_id){
            case GT_Biome_DeepWater:
                tile.ch='~';
                tile.color=color_from_name("blue");
                break;
            case GT_Biome_ShallowWater:
                tile.ch='~';
                tile.color=color_from_name("light azure");
                break;
            case GT_Biome_Beach:
                tile.ch='.';
                tile.color=color_from_name("yellow");
                break;
            case GT_Biome_Plains:
                tile.ch='.';
                tile.color=color_from_name("green");
                break;
            case GT_Biome_Forest:
                tile.ch='*';
                tile.color=color_from_name("green");
                break;
            case GT_Biome_Hills:
                tile.ch='~';
                //tile.color=color_from_name("flame");
                tile.color=color_from_name("orange");
                break;
            case GT_Biome_Mountain:
                tile.ch='^';
                tile.color=color_from_name("white");
                break;
            default:
                tile.ch='X';
                tile.color=color_from_name("red");
                break;
        }
        return tile;
    }

};

#endif // RENDER_H_INCLUDED
