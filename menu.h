#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "game_types.h"
class CRLGame;

#include <vector>
#include <iostream>
#include "include/BearLibTerminal.h"

class CMenu{
        std::vector<MenuEntry> m_items;
        int m_selected;
        Coords2i m_bbox_pos;
    public:
        Coords2i Position;
        CMenu(){
            m_selected=-1;
        }

        void Add(const char *item_name, void (CRLGame::*func)())
        {
            MenuEntry item;
            item.func=func;
            item.name=item_name;
            m_items.push_back(item);
        }

        bool SelectPosition(int index){
            m_selected=index;
        }

        void onMouse(int mouse_x, int mouse_y){
            int x_pos=mouse_x-Position.x;
            int y_pos=mouse_y-Position.y;
            if(y_pos>=m_items.size()){
                SelectPosition(y_pos);
            }
        }

        const int ItemsCount(){
            return m_items.size();
        }

        MenuEntry items(int index){
            return m_items[index];
        }

        bool MenuEvents(CRLGame *g, int key){
            bool changed=false;
            if (key >= TK_A && key <= TK_Z)
			{
				int index = key-TK_A;
				if (index >= 0 && index < m_items.size() && m_items[index].func)
				{
                    changed=true;
                    (g->*m_items[index].func)();
				}
			}
			// cursor keys
			if(key==TK_UP){
                m_selected--;
                if(m_selected < 0) m_selected=m_items.size()-1;
                changed=true;
			}
			if(key==TK_DOWN){
                m_selected++;
                if(m_selected == m_items.size()) m_selected=0;
                changed=true;
			}
            if(key==TK_ENTER){
                changed=true;
                if(m_items[m_selected].func!=NULL){
                    (g->*m_items[m_selected].func)();
                }
            }
            return changed;
        }

        bool isSelected(int index){
            return index==m_selected;
        }

};


#endif // MENU_H_INCLUDED
