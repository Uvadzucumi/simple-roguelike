
#include "game.h"

#include <iostream>

void CRLGame::RenderScene(){
    if(this->Render==NULL) return;
    if(m_scene_changed){

        switch(m_game_state){
            case EGS_WorldMap:
                this->Render->WorldMap(m_world_map);
                break;
            case EGS_MainMenu:
                this->Render->Menu(this->m_menu_main);
                break;
            case EGS_CharGeneration:
                if(m_char_generation==NULL){
                    m_char_generation=new CCharGeneration();
                }
                this->Render->CharGeneration(m_char_generation);
                break;
            case EGS_Game:
                if(m_game_loop==NULL){
                    // create world map
                    if(m_world_map==NULL){
                        m_world_map=new CWorldMap(80,25);
                        m_world_map->Generate();
                    }
                    m_hero=new CCreature;
                    m_hero->setClass(m_char_generation->getClass());
                    m_hero->setSkills(m_char_generation->getSelectedSkillsList());
                    m_game_loop=new CGameLoop(m_hero);
                }
                this->Render->GameLoop(m_game_loop);
                break;
            default:
                break;
        }

        terminal_refresh();
        m_scene_changed=false;
    }
}

//
void CRLGame::Update(double DeltaTime){

}

void CRLGame::CheckEvents(){

    if(terminal_has_input()){

        int key = terminal_read();

        if(key == TK_CLOSE){
            this->SetGameState(EGS_Exit);
            return;
        }

        if(key == TK_Q){
            if (terminal_state(TK_SHIFT)){
                this->SetGameState(EGS_Exit);
                return;
            }
        }

        // state events
        switch(this->m_game_state){
            case EGS_MainMenu:
                if(this->m_menu_main->MenuEvents(this, key)){
                    this->SceneChanged();
                }
                break;
            case EGS_CharGeneration:
                if(this->m_char_generation!=NULL){
                    m_char_generation->Events(key);
                    if(this->m_char_generation->getStatus()==4){
                        this->SetGameState(EGS_Game);
                    }
                    this->SceneChanged();
                }
            case EGS_WorldMap:
                if(key==TK_ESCAPE){
                    if(!m_world_map->getState()){ // state = 0
                        this->SetGameState(EGS_Game);
                    }else{
                        m_world_map->setState(0);
                        this->SceneChanged();
                    }
                }else if(key==TK_SLASH && terminal_state(TK_SHIFT)){
                    m_world_map->setState(1); // display world info
                    this->SceneChanged();
                }
                break;
            case EGS_Game:
                if(this->m_game_loop!=NULL){
                    EGameState tmp=m_game_loop->Events(key);
                    if(tmp!=EGS_Game){
                        this->SetGameState(tmp);
                    }
                }
            default:
                break;
        };

    }
}
