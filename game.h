#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "include/BearLibTerminal.h"

#include "game_types.h"
#include "worldmap.h"
#include "render.h"

#include <string>
#include <iostream>


class CRLGame{

        std::string error_str;
        CWorldMap *m_world_map;

        EGameState m_game_state;

        CRender *Render;
        bool m_scene_changed;


    public:

        CRLGame(){
            m_game_state=EGS_None;
            m_world_map=NULL;
            Render=NULL;
            m_scene_changed=true;
            error_str="";
            if(this->initRender()){
                if(this->initGame()){
                    m_game_state=EGS_WorldMap;
                }
            }
        }

        ~CRLGame(){
            if(m_world_map!=NULL){
                delete m_world_map;
            }
            if(Render!=NULL){
                delete Render;
            }
        }

        bool initRender(){
            Render=new CRender();
            if(!this->Render->Init()){
                error_str="Error inicialize render system!";
                return false;
            }
            return true;
        }

        bool initGame(){
            // create worldmap
            m_world_map=new CWorldMap(80,25);
            m_world_map->Generate();
            return true;
        }

        bool isError(){
            if(error_str!=""){
                return true;
            }else{
                return false;
            }
        }

        int Run(){
            while(m_game_state!=EGS_Exit){
                this->RenderScene();
                this->CheckEvents();
                this->Update(1);
            }
            return 0;
        }

        void RenderScene(); // render current state scene
        void CheckEvents(); // check events
        void Update(double DeltaTime); // update (not game cycle update, update main draw loop - for animation)

        void SetGameState(EGameState state){
            m_game_state=state;
            m_scene_changed=true;
        }

};

#endif // GAME_H_INCLUDED
