
#include "render.h"


// render worldmap screen
void CRender::WorldMap(CWorldMap *wm){
    Tile tile;
    terminal_clear();
    terminal_color(color_from_name("light green"));
    for(int y = 0; y < wm->getHeight(); y++){
        for(int x = 0; x < wm->getWidth(); x++){
            tile=this->getTileById(wm->getTileId(x, y));
            terminal_color(tile.color);
            terminal_put(x, y, tile.ch);
        }
    }
}

void CRender::Menu(CMenu *m){
    if(m==NULL) return;

    terminal_clear();

    uint32_t color=color_from_name("orange"); // menu items color
    uint32_t color_disabled=color_from_name("gray"); // disabled menu item
    uint32_t color_selected=color_from_name("yellow"); // selected menu item


    for (size_t i=0; i < m->ItemsCount(); i++){
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

    if(ch==NULL) return;

    terminal_clear();

    if(ch->getStatus()>0){
        terminal_printf(5,5,"[color=yellow]Имя персонажа: [color=azure]%s",ch->getName());
    }

    size_t name_len;
    char buffer[50]={0};

    switch(ch->getStatus()){
        case 0:
            terminal_printf(5,5,"[color=yellow]Имя персонажа:");

            terminal_color(color_from_name("azure"));

            name_len=terminal_read_str(20, 5, buffer, 20);

            std::cout << "Entered : " << name_len << " letters. Имя: " << buffer << std::endl;

            if(name_len){
                ch->setName(buffer);
                ch->setStatus(1);
            }
            break;
        case 1:
            terminal_printf(5,6,"[color=yellow]Выберите навык основного оружия:");



            break;
        case 2:
            terminal_printf(5,7,"[color=yellow]Все верно?");
            break;
        default:
            break;
    }
}
