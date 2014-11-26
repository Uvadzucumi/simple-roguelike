#ifndef MASK_H_INCLUDED
#define MASK_H_INCLUDED

#include "../types.h"
#include <vector>

class CMask{
    protected:
        int m_width, m_height;
        float *m_mask;
        std::vector <Coords2i> check;

        void Free();

    public:

        CMask(int width, int height);

        ~CMask();

        void Clear();
        void SetSize(int width, int height);

        float getMaxHeight();
        float getMinHeight();

        void Normalize();
        float getHeight(int x, int y);

        void Dump();
};

#endif // MASK_H_INCLUDED
