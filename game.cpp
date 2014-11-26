
#include "game.h"

#include <iostream>

void CRLGame::RenderScene(){
    if(m_scene_changed){

        switch(m_game_state){
            case EGS_WorldMap:
                this->Render->WorldMap(m_world_map);
                std::cout << "Render WorldMap" << std::endl;
                break;
            default:
                break;
        }

        terminal_refresh();
        m_scene_changed=false;
    }
}

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
    }
}
