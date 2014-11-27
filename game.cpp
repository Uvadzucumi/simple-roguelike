
#include "game.h"

#include <iostream>

void CRLGame::RenderScene(){
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
                this->isSceneChanged();
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
                    m_char_generation->Events(this, key);
                    this->SceneChanged();
                }
            default:
                break;
        };

    }
}
