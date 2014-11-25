#ifndef WORLDMAP_H_INCLUDED
#define WORLDMAP_H_INCLUDED

#include <stdlib.h>

enum WM_Biome{
    WMB_DeepWater,      // blue ~
    WMB_ShallowWater,   // white-blue ~
    WMB_Beach,          // ellow .
    WMB_Plains,         // green .
    WMB_Forest,         // green *
    WMB_Hills,          // brown ~
    WMB_Mountain        // silver ^
};

class CWorldMap{
        int m_width;
        int m_height;
        WM_Biome *m_map;

    public:
        CWorldMap(int width, int height){
            m_map=NULL;
            this->setSize(width, height);
        }

        void setSize(int width, int height){
            if(m_map!=NULL){
                delete[] m_map;
            }
            m_map = new WM_Biome[width*height];
            m_width=width;
            m_height=height;
        }

        WM_Biome getBiomeByHeight(int height, int water_line_height=100);
        void Generate();
        void Dump();

};

#endif // WORLDMAP_H_INCLUDED
