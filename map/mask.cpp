
#include "mask.h"

#include <iostream>
#include <stdio.h>

float CMask::getMaxHeight(){
    float max_height=m_mask[0];
    int cells_count=m_width*m_height;
    for(int i=0; i < cells_count; i++){
        if(m_mask[i] > max_height){
            max_height = m_mask[i];
        }
    }
    return max_height;
}

float CMask::getMinHeight(){
    float min_height=m_mask[0];
    int cells_count=m_width*m_height;
    for(int i=0; i < cells_count; i++){
        if(m_mask[i] < min_height){
            min_height = m_mask[i];
        }
    }
    return min_height;
}

void CMask::Free(){
    if(m_mask!=NULL){
        delete[] m_mask;
    }
    m_mask=NULL;
}

void CMask::Clear(){
    for(unsigned int i=0; i<m_width*m_height; i++){
        m_mask[i]=0;
    }
}

void CMask::SetSize(int width, int height){
    m_width=width;
    m_height=height;
    this->Free();
    m_mask=new float[m_width*m_height];
}

CMask::CMask(int width, int height){
    m_mask=NULL;
    this->SetSize(width, height);
            // fill directions
    Coords2i tmp;
    tmp.x=0; tmp.y=1; check.push_back(tmp);
    tmp.x=0; tmp.y=-1; check.push_back(tmp);
    tmp.x=1; tmp.y=0; check.push_back(tmp);
    tmp.x=-1; tmp.y=0; check.push_back(tmp);
}

CMask::~CMask(){
    this->Free();
}

float CMask::getHeight(int x, int y){
    if(x<m_width && y<m_height){
        return m_mask[y*m_width+x];
    }else{
        return 0;
    }
}

void CMask::Normalize(){
    float max_height=this->getMaxHeight();
    if(max_height){
        for(unsigned int i=0; i<m_width*m_height; i++){
            m_mask[i]/=max_height;
        }
    }
}

void CMask::Dump(){
    for(int y=0; y<m_height; y++){
        for(int x=0; x< m_width; x++){
            float h=m_mask[y*m_width+x];
            if(h<0.1){
                printf("~");
            }else if(h<0.3){
                printf(".");
            }else if(h<0.5){
                printf(":");
            }else if(h<0.8){
                printf("$");
            }else{
                if(h<0.9){
                    printf("#");
                }else{
                    printf("^");
                }
            }
        }
        printf("\n");
    }
}
