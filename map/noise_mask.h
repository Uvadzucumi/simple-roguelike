#ifndef NOISE_MASK_H_INCLUDED
#define NOISE_MASK_H_INCLUDED

#include "mask.h"

class CNoiseMask : public CMask{
    public:
        CNoiseMask(int width, int height):CMask(width, height){}
        void Generate();
};

#endif // NOISE_MASK_H_INCLUDED
