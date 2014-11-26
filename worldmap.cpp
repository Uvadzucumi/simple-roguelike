
#include "worldmap.h"

#include "map/noise_mask.h"
#include "map/rolling_particles_mask.h"

#include <iostream>

using namespace std;

void CWorldMap::Generate(){
    // create temp height map
    float *height_map=new float[m_width*m_height];

    CRollParticlesMask *rp=new CRollParticlesMask(m_width,m_height);
    rp->Generate(3000,50); // 3000 particles with 50 lifetiome
    cout << "max height: " << rp->getMaxHeight() << " min height: " << rp->getMinHeight() << endl;
    rp->Normalize();
    cout << "max height after normalize: " << rp->getMaxHeight() << endl;
    rp->Dump();

    cout << "Generate Height Map" << endl;
    CNoiseMask *noise=new CNoiseMask(m_width, m_height);
    noise->Generate();
    cout << "max height: " << noise->getMaxHeight() << " min height: " << noise->getMinHeight() << endl;
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
            int h=255*height_map[index]/max_height;
            m_map[index].biome=this->getBiomeByHeight(h); // set biome
            // set water, not water - for calculate islands & remove small islands
            if( m_map[index].biome==WMB_DeepWater || m_map[index].biome==WMB_ShallowWater){
                m_map[index].data=1; // water
            }else{
                m_map[index].data=0; // not water
            }
            height_map[index]=h;
            if(max_height2<h){
                max_height2=h;
            }
        }
    }
    // calculate islands
    int islands=0;
    bool not_found=true;
    do{
        for(int y=0; y < m_height; y++){
            for(int x=0; x < m_width; x++){
                if(m_map[y*m_width+x].data==0){ // founded ground
                    islands++;
                    std::cout << "Island: " << islands << " In coords: " << x << "," << y << std::endl;
                    int island_size=this->CheckIslandWave(x, y,islands+1);
                    std::cout << " ISLAND size: " << island_size << std::endl;
                    if(island_size<5){ // small island - need remove
                        this->setMapBiome(islands+1,WMB_ShallowWater);
                        std::cout << " ISLAND removbed " << std::endl;
                        islands--;
                    }
                }
            }
        }
    }while(!not_found);

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
    return ret;
}

void CWorldMap::Dump(){
    char c;
    for(int y=0; y < m_height; y++){
        for(int x=0; x<m_width; x++){
            switch(m_map[y*m_width+x].biome){
                case WMB_DeepWater:
                    c='~';
                    break;
                case WMB_ShallowWater:
                    c='~';
                    break;
                case WMB_Beach:
                    c='.';
                    break;
                case WMB_Plains:
                    c='.';
                    break;
                case WMB_Forest:
                    c='*';
                    break;
                case WMB_Hills:
                    c='o';
                    break;
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

EGameTile CWorldMap::getTileId(int x, int y){
    EGameTile tile=GT_None;
    switch(m_map[y*m_width+x].biome){
        case WMB_DeepWater:
            tile=GT_Biome_DeepWater;
            break;
        case WMB_ShallowWater:
            tile=GT_Biome_ShallowWater;
            break;
        case WMB_Beach:
            tile=GT_Biome_Beach;
            break;
        case WMB_Plains:
            tile=GT_Biome_Plains;
            break;
        case WMB_Forest:
            tile=GT_Biome_Forest;
            break;
        case WMB_Hills:
            tile=GT_Biome_Hills;
            break;
        case WMB_Mountain:
            tile=GT_Biome_Mountain;
            break;
    }
    return tile;
}

void CWorldMap::setMapTmpData(int value){
    for(int y=0; y<m_height-1; y++){
        for(int x=0; x< m_width; x++){
            m_map[y*m_width+x].data=value;
        }
    }
}

void CWorldMap::setMapBiome(int data_value, WM_Biome new_biome){
    for(int y=0; y<m_height-1; y++){
        for(int x=0; x< m_width; x++){
            if(m_map[y*m_width+x].data==data_value){
                m_map[y*m_width+x].biome=new_biome;
                m_map[y*m_width+x].data=1;
            };
        }
    }
}

int CWorldMap::CheckIslandWave(int start_x, int start_y, int marker){
    Coords2i tmp;

    std::vector <Coords2i> check;
    tmp.x=0; tmp.y=1; check.push_back(tmp);
    tmp.x=0; tmp.y=-1; check.push_back(tmp);
    tmp.x=1; tmp.y=0; check.push_back(tmp);
    tmp.x=-1; tmp.y=0; check.push_back(tmp);
    // cross
    tmp.x=-1; tmp.y=-1; check.push_back(tmp);
    tmp.x=-1; tmp.y=+1; check.push_back(tmp);
    tmp.x=1; tmp.y=-1; check.push_back(tmp);
    tmp.x=1; tmp.y=+1; check.push_back(tmp);
    // search position
    int step=0;
    std::vector <Coords2i> wave, next_wave;
    tmp.x=start_x; tmp.y=start_y;
    wave.clear();
    wave.push_back(tmp);
    m_map[start_x+start_y*m_width].data=marker;
    // current wave
    int fields_cnt=1;
    do{
        step++;
        std::cout << " step: " << step << " wave size: " << wave.size() << std::endl;
        next_wave.clear();
        for(unsigned int i=0; i<wave.size(); i++){
        // check positions
            for(unsigned int j=0; j<check.size(); j++){
                int y_index=wave[i].y+check[j].y;
                int x_index=wave[i].x+check[j].x;
                if(x_index >= 0 && x_index < m_width && y_index >= 0 && y_index < m_height){
                    int index=y_index*m_width+x_index;
                    if(!m_map[index].data){
                        m_map[index].data=marker;
                // add to next
                        tmp.x=x_index;
                        tmp.y=y_index;
                        next_wave.push_back(tmp);
                    }
                }
            }
        }
        wave=next_wave;
        fields_cnt+=wave.size();

    }while(wave.size()!=0);

    return fields_cnt;
}

