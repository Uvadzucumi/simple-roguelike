
#include "render.h"
#include "game_db.h"

// render world map screen
void CRender::WorldMap(CWorldMap *wm){
    TileDisplay tile;
    terminal_clear();
    //terminal_color(color_from_name("light green"));
    if(!wm->getState()){
        for(int y = 0; y < wm->getHeight(); y++){
            for(int x = 0; x < wm->getWidth(); x++){
                tile=this->getTileById(wm->getTileId(x, y));
                terminal_color(tile.color);
                terminal_put(x, y, tile.ch);
            }
        }

        // display cities
        for(int i=0; i < wm->getIslandsCount(); i++ ){
            Island isl=wm->getIsland(i);
            if(isl.cities.size() > 0){
                for(int j=0; j < (int)isl.cities.size(); j++){
                    terminal_printf(isl.cities[j].biome_coord.x, isl.cities[j].biome_coord.y, "[color=white]#");
                }
            }
        }
        terminal_print(50, 24, "[color=yellow][[[color=azure]?[color=yellow]]] - Информация");
    }else{ // display world info
        terminal_printf(1, 1, "[color=yellow]Островов: [color=azure]%d",wm->getIslandsCount());
        int city_dy=0;
        for(int i=0; i < wm->getIslandsCount(); i++ ){
            Island isl=wm->getIsland(i);
            terminal_printf(5, 2+i+city_dy, "[color=yellow]Остров: [color=azure]%s [color=yellow]размер: [color=azure]%d", wm->getIslandName(i), wm->getIslandSize(i));
            if(isl.cities.size()>0){
                for(int j=0; j < (int)isl.cities.size(); j++){
                    terminal_printf(8,3+i+city_dy,"[color=green]%s [color=yellow][[%d,%d]]",isl.cities[j].name.c_str(),isl.cities[j].biome_coord.x, isl.cities[j].biome_coord.y);
                    city_dy++;
                }
            }
        }
    }

    terminal_print(67,24,"[color=yellow][[[color=azure]ESC[color=yellow]]] - Выход");
}

void CRender::Menu(CMenu *m){
    if(m==NULL) return;

    terminal_clear();

    uint32_t color=color_from_name("orange");           // menu items color
    uint32_t color_disabled=color_from_name("gray");    // disabled menu item
    uint32_t color_selected=color_from_name("yellow");  // selected menu item


    for (int i=0; i < m->ItemsCount(); i++){
		uint32_t mi_name_color=color;
        uint32_t mi_shorcut_color=color;

		char shortcut = 'a'+i;

		if(m->isSelected(i)){
            mi_name_color=color_selected;
            mi_shorcut_color=color_selected;
		}
		if(m->items(i).func==NULL){
            mi_name_color=color_disabled;
		}

		terminal_color(mi_shorcut_color);
		terminal_printf(m->Position.x, m->Position.y+i,"%c)", shortcut);
		terminal_color(mi_name_color);
        terminal_printf(m->Position.x+3, m->Position.y+i, "%s", m->items(i).name);
    }
}

void CRender::CharGeneration(CCharGeneration *ch){

    if(ch == NULL) return;

    terminal_clear();

    uint32_t menu_color=color_from_name("orange");
    uint32_t menu_disabled_color=color_from_name("gray");
    uint32_t menu_selected_color=color_from_name("yellow");

    uint32_t menu_item_color, menu_item_name_color;

    if(ch->getStatus()>0){
        terminal_printf(5,1,"[color=yellow]Имя персонажа: [color=azure]%s",ch->getName());
    }
    if(ch->getStatus()>1){
        terminal_printf(5,2,"[color=yellow]Класс: [color=azure]%s", CharClasses[ch->getClass()].name);
    }

    std::vector<CharacterSkill> char_skills=ch->getSelectedSkillsList();

    if(ch->getStatus()>1){ // show selected skills
        terminal_printf(5,3,"[color=yellow]Навыки персонажа:");
        for(int i = 0; i < (int)char_skills.size(); i++){
            terminal_printf(23, 3+i, "[color=azure]%s", char_skills[i].name);
        }
    }

    std::vector<CharacterSkill> skills_list=ch->getClassSkillsList();

    size_t name_len;
    char buffer[50]={0};

    int x,y;    // menu items draw variable

    switch(ch->getStatus()){
        case 0:
            terminal_printf(5,1,"[color=yellow]Имя персонажа:");

            terminal_color(color_from_name("azure"));

            name_len=terminal_read_str(20, 1, buffer, 20);

            std::cout << "Entered : " << name_len << " letters. Имя: " << buffer << std::endl;

            if(name_len){
                ch->setName(buffer);
                ch->setStatus(1);
            }
            break;
        case 1:
            terminal_printf(5,2,"[color=yellow]Выберите класс персонажа:");
            // display character classes
            for( int i=0; i < (int)CharClasses.size(); i++){
                if(i==ch->getMenuIndex()){
                    terminal_color(menu_selected_color);
                }else{
                    terminal_color(menu_color);
                }
                terminal_printf(20,3+i,"%c) %s",'a'+i, CharClasses[i].name);
            }
            break;
        case 2:
            terminal_printf(5,7,"[color=yellow]Выберите дополнительные навыки ([color=green]%d[color=yellow]):",4-char_skills.size());
            x=0; y=0;
            for(int i=0; i < (int)skills_list.size(); i++){
                if(i==ch->getMenuIndex()){
                    menu_item_color=menu_selected_color;
                }else{
                    menu_item_color=menu_color;
                }

                if(ch->isSkillSelected(skills_list[i].id)){
                    menu_item_name_color=menu_disabled_color;
                }else{
                    menu_item_name_color=menu_item_color;
                }

                terminal_color(menu_item_color);
                terminal_printf(15+x,8+y,"%c)",'a'+i);
                terminal_color(menu_item_name_color);
                terminal_printf(18+x,8+y,"%s", skills_list[i].name);
                y++;
                if(y==10){ // 10 manu items in column
                    x+=25;
                    y=0;
                }
            }
            break;
        default:
            terminal_printf(5,7,"[color=yellow]Все верно? ([color=azure]y[color=yellow]/[color=azure]n[color=yellow])");
            break;
    }
}

void CRender::GameLoop(CGameLoop *game_loop){
    terminal_clear();
    terminal_printf(0,0,"[color=yellow]Игра!!!");
}
