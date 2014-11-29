#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "include/BearLibTerminal.h"

#include "game_types.h"
#include "worldmap.h"
#include "render.h"
#include "menu.h"
#include "game_loop.h"

#include <string>
#include <iostream>


class CRLGame{

        std::string error_str;
        CWorldMap *m_world_map;

        EGameState m_game_state;

        CRender *Render;
        bool m_scene_changed;
        CMenu *m_menu_main;
        CCharGeneration *m_char_generation;
        CGameLoop *m_game_loop;

    public:

        CRLGame(){

            m_game_state=EGS_None;
            m_world_map=NULL;
            Render=NULL;
            m_char_generation=NULL;
            m_game_loop=NULL;

            m_scene_changed=true;
            error_str="";
            if(this->initRender()){
                if(this->initGame()){
                    m_game_state=EGS_MainMenu;
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
            if(m_menu_main!=NULL){
                delete m_menu_main;
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
            // create world map
            m_world_map=new CWorldMap(80,25);
            m_world_map->Generate();
            // create main menu
            m_menu_main=new CMenu();
            m_menu_main->Position={15,5};
            // menu entry
            m_menu_main->Add("Новая игра", &CRLGame::NewGame);
            m_menu_main->Add("Продолжить", NULL);
            m_menu_main->Add("Справка", NULL);
            m_menu_main->Add("Выход", &CRLGame::Exit);

            m_menu_main->SelectPosition(0);

            return true;
        }

        bool isError(){
            if(error_str!=""){
                return true;
            }else{
                return false;
            }
        }

        std::string getLastError(){
            return this->error_str;
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


        void SceneChanged(){ m_scene_changed=true; };
        bool isSceneChanged(){ return m_scene_changed==true; };

        void SetGameState(EGameState state){
            m_game_state=state;
            SceneChanged();
        }

    protected:
        void NewGame(){
            SetGameState(EGS_CharGeneration);
        }
        void Exit(){
            SetGameState(EGS_Exit);
        }
};

#endif // GAME_H_INCLUDED
