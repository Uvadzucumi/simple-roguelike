#ifndef CREATURE_H_INCLUDED
#define CREATURE_H_INCLUDED

#include "game_types.h"
#include <vector>

class CCreature{
        char name[100];
        std::vector<CharacterSkill> m_skills;
        ECharClass m_class;
    public:
        CCreature(){};
        void setClass(ECharClass creature_class){
            m_class=creature_class;
        }
        void setSkills(std::vector<CharacterSkill> skills){
            m_skills=skills;
        }
        void addSkill(CharacterSkill skill){
            m_skills.push_back(skill);
        }
};

#endif // CREATURE_H_INCLUDED
