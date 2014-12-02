#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include "game_db.h"
#include "worldmap.h"
#include "menu.h"
#include "char_generation.h"
#include "game_loop.h"

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
    void GameLoop(CGameLoop *game_loop);

// return tile by tile id
    TileDisplay getTileById(EGameTile tile_id){
        if(tile_id>=0 && tile_id<GameTiles.size()){
            return GameTiles[tile_id];
        }else{
            return GameTiles[0];
        }
    }
};

#endif // RENDER_H_INCLUDED
