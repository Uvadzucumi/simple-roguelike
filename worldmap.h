#ifndef WORLDMAP_H_INCLUDED
#define WORLDMAP_H_INCLUDED

#include <stdlib.h>

#include "game_types.h"
#include <vector>
#include <string>

#include "map/name_gen.h"

class CWorldMap{
        int m_width;
        int m_height;
        WorldMapBiome *m_map;
        int m_islands_count;
        std::vector<int> m_islands_size;
        std::vector<std::string> m_islands_names;
        int m_state;
        CWeightedLetterNamegen *m_namegen;

    public:
        CWorldMap(int width, int height){
            m_namegen=new CWeightedLetterNamegen();
            m_state=0;
            m_map=NULL;
            this->setSize(width, height);
        }

        ~CWorldMap(){
            delete m_namegen;
            if(m_map!=NULL){
                delete m_map;
            }
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

        int getState(){
            return m_state;
        };

        void setState(int state){
            m_state=state;
        }

        int getIslandsCount(){ return m_islands_count; }
        int getIslandSize(int island_no){ return m_islands_size[island_no]; }
        const char* getIslandName(int island_no){ return m_islands_names[island_no].c_str(); }

        WM_Biome getBiomeByHeight(int height, int water_line_height=120);
        void Generate();
        void Dump();

        void setMapBiome(int data_value, WM_Biome new_biome);
        void setMapTmpData(int value); // set value to all world map field
        int CheckIslandWave(int start_x, int start_y, int marker);

        std::string GenerateName();

};

#endif // WORLDMAP_H_INCLUDED
