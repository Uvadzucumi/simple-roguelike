#ifndef WORLDMAP_H_INCLUDED
#define WORLDMAP_H_INCLUDED

#include <stdlib.h>

#include "game_types.h"

class CWorldMap{
        int m_width;
        int m_height;
        WorldMapBiome *m_map;

    public:
        CWorldMap(int width, int height){
            m_map=NULL;
            this->setSize(width, height);
        }

        void setSize(int width, int height){
            if(m_map!=NULL){
                delete[] m_map;
            }
            m_map = new WorldMapBiome[width*height];
            m_width=width;
            m_height=height;
        }

        EGameTile getTileId(int x, int y);

        int getWidth(){ return m_width; }
        int getHeight(){ return m_height; }



        WM_Biome getBiomeByHeight(int height, int water_line_height=120);
        void Generate();
        void Dump();

        void setMapBiome(int data_value, WM_Biome new_biome);
        void setMapTmpData(int value); // set value to all world map field
        int CheckIslandWave(int start_x, int start_y, int marker);

        void Render();


};

#endif // WORLDMAP_H_INCLUDED
