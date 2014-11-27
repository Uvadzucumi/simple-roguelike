#ifndef CHAR_GENERATION_H_INCLUDED
#define CHAR_GENERATION_H_INCLUDED

class CRLGame;

#include <iostream>

class CCharGeneration{

        std::string char_name;
        int m_status;

    public:

        CCharGeneration(){
            m_status=0;
        }

        int getStatus(){ return m_status; }
        void setStatus(int status){ m_status=status; }

        void Events(CRLGame *g, int key){
            std::cout << "key: " << key << std::endl;

        }
        void setName(const char *name){
            char_name=name;
        }
        const char *getName(){
            return char_name.c_str();
        }

};


#endif // CHAR_GENERATION_H_INCLUDED
