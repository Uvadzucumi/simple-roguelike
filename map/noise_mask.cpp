
#include "noise_mask.h"

#define NOISE_OCTAVES 2
#define NOISE_FREQUENCY 1.5
#define NOISE_AMPLITUDE 2

#include "perlin.h"
#include <time.h> // for time

void CNoiseMask::Generate(){

    int noise_seed=rand()%RAND_MAX;

    Perlin *noise=new Perlin(NOISE_OCTAVES, NOISE_FREQUENCY, NOISE_AMPLITUDE, noise_seed);
    for(int y=0; y < m_height; y++){
        for(int x=0; x < m_width; x++){
            float height=noise->Get((float)x/m_width, (float)y/m_height);
            int index=y*m_width+x;
            m_mask[index]=height;
        }
    }

    float min_height=this->getMinHeight();

    if(min_height<0){
        float dh=min_height*-1;
        for(int y=0; y < m_height; y++){
            for(int x=0; x < m_width; x++){
                int index=y*m_width+x;
                m_mask[index]+=dh;
            }
        }
    }

}
