
#include "rolling_particles_mask.h"

#include <iostream>
#include <stdio.h>

void CRollParticlesMask::Generate(int particle_count, int particle_life){

            this->Clear();

            std::vector <Coords2i> direction;
            for(int i=0; i<particle_count; i++){
                int part_life=particle_life;
                int x=rand()%m_width;
                int y=rand()%m_height;
                while(part_life > 0 &&
                        x > 0 && x < (m_width-1) &&
                        y > 0 && y < (m_height-1)){
                    part_life--;
                    int index=m_width*y+x;
                    // get current height
                    float height=m_mask[index];
                    // check nearest height
                    direction.clear();
                    for(size_t i=0; i<check.size();i++){
                        Coords2i tmp=check[i];
                        float curr_height=m_mask[index+tmp.x+tmp.y*m_width];
                        if(curr_height<=height){
                            direction.push_back(tmp);
                        }
                    }
                    if(!direction.size()){ // break - if all nearest have more height
                        m_mask[index]+=1;
                        break;
                    }
                    // get random direction
                    int dir_index=rand()%direction.size();
                    Coords2i rand_dir=direction[dir_index];
                    // set rand movement
                    x+=rand_dir.x;
                    y+=rand_dir.y;

                    // increase point height
                    m_mask[y*m_width+x]+=1;
                };
            }

}


