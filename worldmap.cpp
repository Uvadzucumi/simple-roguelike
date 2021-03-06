
#include "worldmap.h"

#include "map/noise_mask.h"
#include "map/rolling_particles_mask.h"

#include <iostream>
#include <cmath>

#define CITIES_DENSITY          10
#define CITIES_MIN_DISTANCE     5

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
            m_map[index].biome=this->getBiomeByHeight(h);   // set biome
            m_map[index].biome_seed=rand()%RAND_MAX;        // nedd for build biome outside map
            // set water, not water - for calculate islands & remove small islands
            if( m_map[index].biome==WMB_DeepWater || m_map[index].biome==WMB_ShallowWater){
                m_map[index].island=-1; // water
            }else{
                m_map[index].island=0; // not water
            }
            height_map[index]=h;
            if(max_height2<h){
                max_height2=h;
            }
        }
    }
    // calculate islands
    m_islands.clear();
    int islands_count=0;
    bool not_found=true;
    do{
        for(int y=0; y < m_height; y++){
            for(int x=0; x < m_width; x++){
                if(m_map[y*m_width+x].island==0){ // founded ground
                    islands_count++;
                    std::cout << "Island: " << islands_count << " In coords: " << x << "," << y << std::endl;
                    int island_size=this->CheckIslandWave(x, y,islands_count+1);
                    std::cout << " ISLAND size: " << island_size << std::endl;
                    if(island_size<5){ // small island - need remove
                        this->setMapBiome(islands_count+1,WMB_ShallowWater);
                        std::cout << " ISLAND removed " << std::endl;
                        islands_count--;
                    }else{
                        Island i;
                        i.name=this->GenerateName();
                        i.size=island_size;
                        i.bbox[0]={m_width,m_height};
                        i.bbox[1]={0,0};
                        m_islands.push_back(i);
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

    m_main_island_id=0;
    // detect main island & calculate islands bbox
    for(int i=0; i<(int)m_islands.size(); i++){
        // calculate island bbox
        for(int y=0; y < m_height; y++){
            for(int x=0; x < m_width; x++){
                int index=y*m_width+x;
                if(m_map[index].island==i+2){
                    // top-left
                    if(x<m_islands[i].bbox[0].x){
                        m_islands[i].bbox[0].x=x;
                    }
                    if(y<m_islands[i].bbox[0].y){
                        m_islands[i].bbox[0].y=y;
                    }
                    // right-bottom
                    if(x>m_islands[i].bbox[1].x){
                        m_islands[i].bbox[1].x=x;
                    }
                    if(y>m_islands[i].bbox[1].y){
                        m_islands[i].bbox[1].y=y;
                    }
                }
            }
        }
        // check for main island
        if(m_islands[i].size > m_islands[m_main_island_id].size){
            m_main_island_id=i;
        }
    }

    this->m_cities_count=0;

    for(unsigned int i=0; i < m_islands.size(); i++){
        int cities_count = int(((float) m_islands[i].size / (float)(m_width * m_height)) * (float) CITIES_DENSITY + 0.5);
        std::cout << "Island: " << m_islands[i].name << " int( (" << m_islands[i].size << " / " << (m_width * m_height) << ") * " << CITIES_DENSITY << " + 0.5) = sities: " << cities_count << std::endl;
        for(int c=0; c < cities_count; c++){
            this->AddCityToIsland(i);
            this->m_cities_count++;
        }
    }

}

void CWorldMap::AddCityToIsland(int island_id){
    int city_pos_x;
    int city_pos_y;

    std::cout << "Island: " << island_id << " bbox[" <<
               m_islands[island_id].bbox[0].x << "," << m_islands[island_id].bbox[0].y << "]x[" <<
               m_islands[island_id].bbox[1].x << ","<< m_islands[island_id].bbox[1].y <<"]" << std::endl;

    City city;

    while(true){
        int dx=0; int dy=0;
        //if(true){ // city near ocean
            if(rand()%2==0){ // random side - Y
                std::cout << "random side Y" << std::endl;
                if(rand()%2==0){
                    std::cout << "left X" << std::endl;
                    city_pos_x=m_islands[island_id].bbox[0].x; // left side
                    dx=1;
                }else{
                    std::cout << "right X" << std::endl;
                    city_pos_x=m_islands[island_id].bbox[1].x; // right side
                    dx=-1;
                }
                city_pos_y=city.biome_coord.y=m_islands[island_id].bbox[0].y+rand()%(m_islands[island_id].bbox[1].y-m_islands[island_id].bbox[0].y);
            }else{ // random side X
                std::cout << "random side X" << std::endl;
                if(rand()%2==0){
                    std::cout << "top Y" << std::endl;
                    city_pos_y=m_islands[island_id].bbox[0].y; // top side
                    dy=1;
                }else{
                    std::cout << "bottom Y" << std::endl;
                    city_pos_y=m_islands[island_id].bbox[1].y; // bottom side
                    dy=-1;
                }
                city_pos_x=m_islands[island_id].bbox[0].x+rand()%(m_islands[island_id].bbox[1].x-m_islands[island_id].bbox[0].x);
            }
            std::cout << "island: " << island_id << " City coords: " << city_pos_x << "," << city_pos_y << std::endl;
            // move city to island
            do{
                int index=m_width*city_pos_y+city_pos_x;
                //std::cout << "coord: " << city_pos_x << "," << city_pos_y << " island: " << m_map[index].island << std::endl;
                if(m_map[index].island==island_id+2){
                    break;
                }
                city_pos_x+=dx;
                city_pos_y+=dy;
            }while(city_pos_x >= 0 && city_pos_x < m_width && city_pos_y >= 0 && city_pos_y < m_height);

            std::cout << "island: " << island_id << " City coords: " << city_pos_x << "," << city_pos_y << std::endl;
            if(city_pos_y==m_height-1){ // hack for menu
                city_pos_y--;
            }

        //}else{ // generate city inside island

        //}

        if(checkDistanceToCity(island_id, city_pos_x, city_pos_y)){ // else - repeat city coords generation
            city.biome_coord.x=city_pos_x;
            city.biome_coord.y=city_pos_y;
            city.name=this->GenerateName();
            m_islands[island_id].cities.push_back(city);
            break;
        }else{
            std::cout << "Wrong distance. Recreate city coords" << std::endl;
        }

    }

}

bool CWorldMap::checkDistanceToCity(int island_id, int city_pos_x, int city_pos_y){
    if(m_islands[island_id].cities.size()){
        std::cout << "Check distance from " << city_pos_x << ", " << city_pos_y << " in island " <<  island_id << "." << std::endl;
    }
    for(int i=0; i < (int)m_islands[island_id].cities.size(); i++){
        int x=m_islands[island_id].cities[i].biome_coord.x;
        int y=m_islands[island_id].cities[i].biome_coord.y;
        std::cout << m_islands[island_id].cities[i].biome_coord << " - ";
        float distance=sqrt( (city_pos_x-x)*(city_pos_x-x) + (city_pos_y-y)*(city_pos_y-y) );
        std::cout << "    distance = " << distance << std::endl;
        if( distance < CITIES_MIN_DISTANCE){
            return false;
        }
    }
    return true;
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
/*
void CWorldMap::setMapTmpData(int value){
    for(int y=0; y<m_height-1; y++){
        for(int x=0; x< m_width; x++){
            m_map[y*m_width+x].island=value;
        }
    }
}
*/
void CWorldMap::setMapBiome(int data_value, WM_Biome new_biome){
    for(int y=0; y<m_height-1; y++){
        for(int x=0; x< m_width; x++){
            if(m_map[y*m_width+x].island==data_value){
                m_map[y*m_width+x].biome=new_biome;
                m_map[y*m_width+x].island=-1;
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
    m_map[start_x+start_y*m_width].island=marker;
    // current wave
    int fields_cnt=1;
    do{
        step++;
        //std::cout << " step: " << step << " wave size: " << wave.size() << std::endl;
        next_wave.clear();
        for(unsigned int i=0; i<wave.size(); i++){
        // check positions
            for(unsigned int j=0; j<check.size(); j++){
                int y_index=wave[i].y+check[j].y;
                int x_index=wave[i].x+check[j].x;
                if(x_index >= 0 && x_index < m_width && y_index >= 0 && y_index < m_height){
                    int index=y_index*m_width+x_index;
                    if(m_map[index].island==0){
                        m_map[index].island=marker;
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

std::string CWorldMap::GenerateName(){
    vector<std::string> names=m_namegen->generate(1);
    return m_namegen->toCyrilic(names[0]);
}

City CWorldMap::getRandomCity(){
    // calculati sities
    City founded;
    int city_cnt=0;
    int city_num=rand()%m_cities_count;
    for(unsigned int i = 0; i < m_islands.size(); i++){
        for(unsigned int c = 0; c < m_islands[i].cities.size(); c++){
            if(city_num==city_cnt){
                founded=m_islands[i].cities[c];
                break;
            }
            city_cnt++;
        }
    }
    return founded;
}

// helper function for create biome ///////////////////////////////////////////////

// fill biome using special tile
void CWorldMap::BiomeMapFill(TileGame *biome_map, EGameTile tile_type){
    for(int y = 0; y < BIOME_HEIGHT; ++y){
        for(int x = 0; x < BIOME_WIDTH; ++x){
            int map_index=y*BIOME_WIDTH+x;
            biome_map[map_index].tile_type=tile_type;
            biome_map[map_index].is_viewed=false;
            biome_map[map_index].is_view=false;
        }
    }
}

// add special tiles to biome in random points
void CWorldMap::BiomeMapAdd(TileGame *biome_map, EGameTile tile_type, int item_count){
    int map_index;
    for(int i=0; i < item_count; ++i){
        map_index=(rand()%BIOME_HEIGHT) * BIOME_WIDTH + rand()%BIOME_WIDTH;
        biome_map[map_index].tile_type=tile_type;
    }
}

// return out map for current biome (in world map biome coords x,y)
TileGame* CWorldMap::getBiomeOutMap(int biome_x, int biome_y){

    int index=biome_y*m_width+biome_x;
    if(m_map[index].biome_map==NULL){
        // generate biome

        m_map[index].biome_map=new TileGame[BIOME_WIDTH*BIOME_HEIGHT];
        srand(m_map[index].biome_seed); // set biome randomize
        std::cout << "Created map for biome [" << biome_x << "," << biome_y << "] ";
        int item_count;
        switch(m_map[index].biome){
            case WMB_Hills:
                 std::cout << "(Hills)";
                 BiomeMapFill(m_map[index].biome_map, GT_Ground);
                 item_count=(BIOME_WIDTH*BIOME_HEIGHT)*0.1; // 10%
                 BiomeMapAdd(m_map[index].biome_map, GT_Bush, item_count);
                 std::cout << " Bush = " << item_count;
                 item_count=(BIOME_WIDTH*BIOME_HEIGHT)*0.2; // 20%
                 BiomeMapAdd(m_map[index].biome_map, GT_Grass, item_count);
                 std::cout << " Grass = " << item_count << std::endl;
                 break;
            case WMB_Mountain:
                 BiomeMapFill(m_map[index].biome_map, GT_Biome_Mountain);
                 std::cout << "(Mountain)" << std::endl;
                 break;
            case WMB_Forest:
                 BiomeMapFill(m_map[index].biome_map, GT_Tree);
                 std::cout << "(Forest)";
                 // add grass
                 //item_count=(BIOME_WIDTH*BIOME_HEIGHT)*((float)(1+rand()%3)/10);
                 item_count=(BIOME_WIDTH*BIOME_HEIGHT)*0.1; // 10%
                 BiomeMapAdd(m_map[index].biome_map, GT_Grass, item_count);
                 std::cout << " Grass = " << item_count;
                 // add bush
                 //item_count=(BIOME_WIDTH*BIOME_HEIGHT)*((float)(1+rand()%3)/10);
                 item_count=(BIOME_WIDTH*BIOME_HEIGHT)*0.1; // 10%
                 BiomeMapAdd(m_map[index].biome_map, GT_Bush, item_count);
                 std::cout << " Bush = " << item_count << std::endl;
                 break;
            case WMB_Beach:
                 std::cout << "(Beach)";
                 BiomeMapFill(m_map[index].biome_map, GT_Sand);
                 // add bush
                 item_count=(BIOME_WIDTH*BIOME_HEIGHT)*((float)(1+rand()%3)/400);
                 BiomeMapAdd(m_map[index].biome_map, GT_Bush, item_count);
                 std::cout << " Bush = " << item_count;
                 // add grass
                 item_count=(BIOME_WIDTH*BIOME_HEIGHT)*((float)(1+rand()%3)/10);
                 BiomeMapAdd(m_map[index].biome_map, GT_Grass, item_count);
                 std::cout << " Grass = " << item_count << std::endl;
                 break;
            case WMB_ShallowWater:
                 BiomeMapFill(m_map[index].biome_map, GT_Biome_ShallowWater);
                 std::cout << "(ShallowWater)";
                 item_count=(BIOME_WIDTH*BIOME_HEIGHT)*0.1; // 10%
                 BiomeMapAdd(m_map[index].biome_map, GT_Biome_DeepWater, item_count);
                 std::cout << " DeepWater = " << item_count << std::endl;
                 break;
            case WMB_DeepWater:
                 BiomeMapFill(m_map[index].biome_map, GT_Biome_DeepWater);
                 std::cout << "(DeepWater)";
                 item_count=(BIOME_WIDTH*BIOME_HEIGHT)*0.1; // 10%
                 BiomeMapAdd(m_map[index].biome_map, GT_Biome_ShallowWater, item_count);
                 std::cout << " ShallowWater = " << item_count << std::endl;
                 break;
            case WMB_Plains:
                std::cout << "(Plains)";
                BiomeMapFill(m_map[index].biome_map, GT_Grass);
                // add trees
                item_count=(BIOME_WIDTH*BIOME_HEIGHT)*((float)(1+rand()%3)/200);
                BiomeMapAdd(m_map[index].biome_map, GT_Tree, item_count);
                std::cout << " Trees = " << item_count;
                // add bushes
                item_count=(BIOME_WIDTH*BIOME_HEIGHT)*((float)(1+rand()%3)/300);
                BiomeMapAdd(m_map[index].biome_map, GT_Bush, item_count);
                std::cout << " Bush = " << item_count << std::endl;
                break;
            default:
                BiomeMapFill(m_map[index].biome_map, GT_None);
            break;
        }

    }
    return m_map[biome_y*m_width+biome_x].biome_map;
}

// return game tile by world coordinates
TileGame CWorldMap::getMapTile(int world_coord_x, int world_coord_y){
    int biome_x=world_coord_x/BIOME_WIDTH;
    int biome_y=world_coord_y/BIOME_HEIGHT;

    int local_x=world_coord_x-biome_x*BIOME_WIDTH;
    int local_y=world_coord_y-biome_y*BIOME_HEIGHT;

    TileGame *biome_map=this->getBiomeOutMap(biome_x, biome_y);
    return biome_map[local_y*BIOME_WIDTH+local_x];
}

bool CWorldMap::isCanMove(int world_coord_x, int world_coord_y){

    EGameTile tile_id=getMapTile(world_coord_x, world_coord_y).tile_type;
    // get tile description by tile_id
    if(tile_id>=0 && tile_id<GameTiles.size()){
        return GameTiles[tile_id].is_can_move;
    }else{
        return GameTiles[0].is_can_move;
    }
    //return tile.is_can_move;
}

