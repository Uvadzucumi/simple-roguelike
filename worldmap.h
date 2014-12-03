#ifndef WORLDMAP_H_INCLUDED
#define WORLDMAP_H_INCLUDED

#include <stdlib.h>

#include "game_db.h"
#include <vector>
#include <string>

#include "map/name_gen.h"

#define BIOME_WIDTH     100
#define BIOME_HEIGHT    100

struct City{
    std::string name;
    Coords2i biome_coord;
};

struct Island{
    int size;
    std::string name;
    Coords2i bbox[2]; // 0 -top/left, 1 - right/bottom
    std::vector<City> cities;
};

class CWorldMap{
        int m_width;
        int m_height;
        WorldMapBiome *m_map;
        int m_state;
        std::vector<Island> m_islands;
        int m_main_island_id;
        int m_cities_count;

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

        const int getIslandsCount(){ return m_islands.size(); }
        int getIslandSize(int island_no){ return m_islands[island_no].size; }
        const char* getIslandName(int island_no){ return m_islands[island_no].name.c_str(); }
        Island getIsland(int index){ return m_islands[index]; }

        WM_Biome getBiomeByHeight(int height, int water_line_height=120);
        void Generate();
        void Dump();

        void setMapBiome(int data_value, WM_Biome new_biome);
        void setMapTmpData(int value); // set value to all world map field
        int CheckIslandWave(int start_x, int start_y, int marker);

        std::string GenerateName();

        City getRandomCity();

        void AddCityToIsland(int island_id);
        bool checkDistanceToCity(int island_id, int city_pos_x, int city_pos_y);

        TileGame* getBiomeOutMap(int biome_x, int biome_y);
        TileGame getMapTile(int world_coord_x, int world_coord_y);
};

#endif // WORLDMAP_H_INCLUDED
