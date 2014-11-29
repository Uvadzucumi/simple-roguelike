#ifndef CHAR_GENERATION_H_INCLUDED
#define CHAR_GENERATION_H_INCLUDED

class CRLGame;

#include "include/BearLibTerminal.h"   // for events constants
#include "game_db.h"
#include <iostream>

class CCharGeneration{

        std::string char_name;
        ECharClass m_class;
        int m_status;
        int m_menu_index;
        std::vector<CharacterSkill> m_selected_skills;
        std::vector<CharacterSkill> m_class_skills;
    public:

        CCharGeneration(){
            m_status=0;
            m_menu_index=0;
        }

        int getStatus(){ return m_status; }
        void setStatus(int status){ m_status=status; m_menu_index=0; }

        void Events(int key);

        int getMenuIndex(){
            return m_menu_index;
        }
        void setName(const char *name){
            char_name=name;
        }
        const char *getName(){
            return char_name.c_str();
        }

        void SelectCharClass(ECharClass character_class);

        std::vector<CharacterSkill> getClassSkillsList(){
            return m_class_skills;
        }

        std::vector<CharacterSkill> getSelectedSkillsList(){
            return m_selected_skills;
        }

        bool isSkillSelected(int skill_id);

        ECharClass getClass(){
            return m_class;
        }

};


#endif // CHAR_GENERATION_H_INCLUDED
