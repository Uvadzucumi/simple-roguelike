
#include "char_generation.h"

void CCharGeneration::Events(int key){
    std::cout << "status: " << getStatus() << " Key: " << key << std::endl;
    if(getStatus()==1){ // check select character classes
        if(key==TK_UP){
            m_menu_index--;
        }
        if(key==TK_DOWN){
            m_menu_index++;
        }
        if(m_menu_index>=(int)CharClasses.size()){
            m_menu_index=0;
        }
        if(m_menu_index<0){
            m_menu_index=CharClasses.size()-1;
        }
        if ((key >= TK_A && key <= TK_Z) || key==TK_ENTER){
            int index;
            if(key==TK_ENTER){
                index = m_menu_index;
            }else{
                index = key-TK_A;
            }
            if(index < (int) CharClasses.size() && index >= 0){
                SelectCharClass(CharClasses[index].id);
                setStatus(2);
            }
        }
    }else if(getStatus()==2){
        //std::cout << "menu iotems count: " << m_class_skills.size() << std::endl;
        if(key==TK_UP){
            m_menu_index--;
        }
        if(key==TK_DOWN){
            m_menu_index++;
        }
        if(key==TK_RIGHT){
            m_menu_index+=10;
            if(m_menu_index>(int)m_class_skills.size()-1){
                m_menu_index=m_class_skills.size()-1;
            }
        }
        if(key==TK_LEFT){
            m_menu_index-=10;
            if(m_menu_index<0){
                m_menu_index=0;
            }
        }
        if(m_menu_index>=(int)m_class_skills.size()){
            m_menu_index=0;
        }
        if(m_menu_index<0){
            m_menu_index=m_class_skills.size()-1;
        }
        if ((key >= TK_A && key <= TK_Z) || key == TK_ENTER){
            int index;
            if(key==TK_ENTER){
                index = m_menu_index;
            }else{
                index = key-TK_A;
            }
            if(index < (int)m_class_skills.size() && index >= 0){
                if(!isSkillSelected(m_class_skills[index].id)){ // if skill not selected
                    m_selected_skills.push_back(m_class_skills[index]);
                    if(m_selected_skills.size() == 4){
                        setStatus(3);
                    }
                }
            }
        }
    }else if(getStatus()==3){
        if (key == TK_N ){
            std::cout << "Recreate character! " << std::endl;
            setStatus(0);
        }else if (key == TK_Y ){
            std::cout << "Start game!" << std::endl;
            setStatus(4); // inform for start game
        }
    }
}

void CCharGeneration::SelectCharClass(ECharClass character_class){
    m_class=character_class;
    // create selected skills list
    m_selected_skills.clear();
    m_selected_skills.push_back( CharSkills[ CharClasses[character_class].def_skills[0] ] );
    m_selected_skills.push_back( CharSkills[ CharClasses[character_class].def_skills[1] ] );
    // create character skill list
    m_class_skills.clear();
    for(int i=0; i<(int)CharSkills.size(); i++){
        //std::cout << " chack skill " << i << " name: "  << CharSkills[i].name;
        if(CharSkills[i].class_access[character_class] && CharSkills[i].create_access){
            m_class_skills.push_back(CharSkills[i]);
            //std::cout << " ADDED!" << std::endl;
        }else{
            //std::cout << " skip! char class_id=" << character_class << " skill create access: " << CharSkills[i].create_access << std::endl;
        }
    }
}

// return true if character have checked skill
bool CCharGeneration::isSkillSelected(int skill_id){
    for(int i=0; i < (int)m_selected_skills.size(); i++){
        if(m_selected_skills[i].id == skill_id){
            return true;
        }
    }
    return false;
}

