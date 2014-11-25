
#include "worldmap.h"

#include "map/noise_mask.h"
#include "map/rolling_particles_mask.h"

#include <iostream>

using namespace std;

void CWorldMap::Generate(){
    // create temp height map
    float *height_map=new float[m_width*m_height];

    CRollParticlesMask *rp=new CRollParticlesMask(m_width,m_height);
    rp->Generate(2000,40);
    cout << "max height: " << rp->getMaxHeight() << endl;
    rp->Normalize();
    cout << "max height after normalize: " << rp->getMaxHeight() << endl;
    rp->Dump();

    cout << "Generate Height Map" << endl;
    CNoiseMask *noise=new CNoiseMask(m_width, m_height);
    noise->Generate();
    cout << "max height: " << noise->getMaxHeight();
    noise->Normalize();
    cout << "max height after normalize: " << noise->getMaxHeight() << endl;
    noise->Dump();

    float max_height=0;

    for(int y=0; y < m_height; y++){
        for(int x=0; x < m_width; x++){
            int index=y*m_width+x;
            float height=noise->getHeight(x, y)*rp->getHeight(x, y);
            height_map[index]=height;
            if(max_height<height){
                max_height=height;
            }
        }
    }
    //
    cout << "max height: " << max_height << endl;

    // normalize to int 0-255
    int max_height2=0;
    for(int y=0; y < m_height; y++){
        for(int x=0; x < m_width; x++){
            int index=y*m_width+x;
            int h=255/max_height*height_map[index];
            cout << "255 / " << max_height << " * " << height_map[index] << " = " << h << "(index = " << index << ")" << endl;
            height_map[index]=h;
            if(max_height2<h){
                max_height2=h;
            }
            // set map biome
            m_map[index]=this->getBiomeByHeight(h);
        }
    }
    cout << "max height after normalize 255: " << max_height2 << endl;
    // clear data
    delete[] height_map;
    delete rp;
    delete noise;
}

WM_Biome CWorldMap::getBiomeByHeight(int height, int water_line_height){
    WM_Biome ret;
    if(height < (water_line_height-40)){
        ret=WMB_DeepWater;
    }else if(height < water_line_height){
        ret=WMB_ShallowWater;
    }else if(height < (water_line_height+15)){
        ret=WMB_Beach;
    }else if(height < (water_line_height+35)){
        ret=WMB_Plains;
    }else if (height < 206){
        ret=WMB_Forest;
    }else if(height < 226){
        ret=WMB_Hills;
    }else {
        ret=WMB_Mountain;
    }
    //cout << "height: " << height << " ret=" << ret << ", ";
}

void CWorldMap::Dump(){
    char c;
    for(int y=0; y < m_height; y++){
        for(int x=0; x<m_width; x++){
            switch(m_map[y*m_width+x]){
                case WMB_DeepWater:
                    c='~';
                    break;
                case WMB_ShallowWater:
                    c=',';
                    break;
                case WMB_Beach:
                    c='.';
                    break;
                case WMB_Plains:
                    c=':';
                    break;
                case WMB_Forest:
                    c='*';
                case WMB_Hills:
                    c='$';
                case WMB_Mountain:
                    c='^';
                    break;
                default:
                    c='x';
            }
            cout << c;
        }
        cout << endl;
    }

}
