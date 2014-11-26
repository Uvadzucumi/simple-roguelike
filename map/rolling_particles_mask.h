#ifndef ROLLING_PARTICLES_MASK_H_INCLUDED
#define ROLLING_PARTICLES_MASK_H_INCLUDED

#include "../game_types.h"

#include <vector>
#include <iostream>
#include <stdlib.h>

#include "mask.h"

class CRollParticlesMask : public CMask{
    public:
        CRollParticlesMask(int width, int height):CMask(width, height){}
        void Generate(int particle_count, int particle_life);
};

#endif // ROLLING_PARTICLES_MASK_H_INCLUDED
