/*
 * codename: xSoko
 * Copyright (C) Aljosa Osep, Jernej Skrabec, Jernej Halozan, Martin Šavc 2008-2009
 * <aljosa.osep@gmail.com, jernej.skrabec@gmail.com, jernej.halozan@gmail.com, martin.savc@gmail.com>
 *
 * xSoko project is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * xSoko project is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <vector>


#include "listbox.h"
#include "container.h"

ListBox::ListBox(int x, int y, int width, int height) : Component(x,y,width,height), selected(-1), drawIndex(0),
        upPressed(false), downPressed(false), fnt(new Font("font"))
{
    canShow = (height-4) / 16;
    invalidate();
}

ListBox::~ListBox(){
    delete fnt;
}

Font* ListBox::getFont(){
    return fnt;
}

void ListBox::invalidate(){
    // top of panel.
    vertex[0].x1 = 2;
    vertex[0].y1 = 0;
    vertex[0].x2 = width-2;
    vertex[0].y2 = 2;

    // left side of panel.
    vertex[1].x1 = 0;
    vertex[1].y1 = 0;
    vertex[1].x2 = 2;
    vertex[1].y2 = height-2;

    // middle of panel.
    vertex[2].x1 = 2;
    vertex[2].y1 = 2;
    vertex[2].x2 = width-2;
    vertex[2].y2 = height-2;

    // right side of panel.
    vertex[3].x1 = width-2;
    vertex[3].y1 = 0;
    vertex[3].x2 = width;
    vertex[3].y2 = height-2;

    // bottom middle of panel.
    vertex[4].x1 = 2;
    vertex[4].y1 = height-2;
    vertex[4].x2 = width;
    vertex[4].y2 = height;

    //scrollbar body
    vertex[5].x1 = width-10;
    vertex[5].y1 = 18;
    vertex[5].x2 = width-9;
    vertex[5].y2 = height-18;

    //upper button
    //left
    vertex[6].x1 = width-18;
    vertex[6].y1 = 2;
    vertex[6].x2 = width-12;
    vertex[6].y2 = 18;

    //middle
    vertex[7].x1 = width-12;
    vertex[7].y1 = 2;
    vertex[7].x2 = width-8;
    vertex[7].y2 = 18;

    //right
    vertex[8].x1 = width-8;
    vertex[8].y1 = 2;
    vertex[8].x2 = width-2;
    vertex[8].y2 = 18;

    //arrow
    vertex[9].x1 = width-18;
    vertex[9].y1 = 2;
    vertex[9].x2 = width-2;
    vertex[9].y2 = 18;

    //lover button
    //left
    vertex[10].x1 = width-18;
    vertex[10].y1 = height-18;
    vertex[10].x2 = width-12;
    vertex[10].y2 = height-2;

    //middle
    vertex[11].x1 = width-12;
    vertex[11].y1 = height-18;
    vertex[11].x2 = width-8;
    vertex[11].y2 = height-2;

    //right
    vertex[12].x1 = width-8;
    vertex[12].y1 = height-18;
    vertex[12].x2 = width-2;
    vertex[12].y2 = height-2;

    //arrow
    vertex[13].x1 = width-18;
    vertex[13].y1 = height-18;
    vertex[13].x2 = width-2;
    vertex[13].y2 = height-2;

    recalculatePosition();
}

void ListBox::recalculatePosition(){
    //position
    float dy = ((float)(height - 46) / (items.size() - canShow))*drawIndex;
    vertex[14].x1 = width-14;
    vertex[14].y1 = dy+18;
    vertex[14].x2 = width-4;
    vertex[14].y2 = dy+28;
}

void ListBox::onRender()
{
    GuiRender::getInstance().drawImage(GUI_TEX_PANEL_TOP,   vertex[0]);
    GuiRender::getInstance().drawImage(GUI_TEX_PANEL_LEFT,  vertex[1]);
    GuiRender::getInstance().drawImage(GUI_TEX_PANEL_MIDLLE,vertex[2]);
    GuiRender::getInstance().drawImage(GUI_TEX_PANEL_RIGHT, vertex[3]);
    GuiRender::getInstance().drawImage(GUI_TEX_PANEL_BOTTOM,vertex[4]);

    unsigned limit = (canShow<items.size()) ? canShow : items.size();
    for(unsigned i=0;i<limit;i++){
		GuiRender::getInstance().setClipping(2,2+(i*16),width-19,18+(i*16));
        if(selected == i+drawIndex){
            GuiRender::getInstance().setColor((float)89/255,(float)97/255,(float)102/255,1);
            GuiRender::getInstance().drawFilledRect(2,2+(i*16),width-19,18+(i*16));
            fnt->writeText(6,18+(i*16),items.at(i+drawIndex)->toString());
        } else {
            fnt->writeText(5,17+(i*16),items.at(i+drawIndex)->toString());
        }
		GuiRender::getInstance().restoreClipping();
    }

    drawButton(6,upPressed,true);
    drawButton(10,downPressed,false);

	GuiRender::getInstance().drawImage(GUI_TEX_SCROLL_BODY,vertex[5]);
    if(items.size() > canShow){
		GuiRender::getInstance().drawImage(GUI_TEX_SCROLL_POSITION,vertex[14]);
    }
}

void ListBox::onMouseDown(int mx, int my){
    if(!visible) return;

    if(mx >= 2 && mx <= width-18){
        unsigned index = (my-2) / 16 + drawIndex;
        if(index < items.size()){
            selected = index;
        }
    }
    if(mx >= width-18){
        if(my >= 2 && my <= 18){
            upPressed = true;
        }
        if(my >= height-18){
            downPressed = true;
        }
        if(my > 18 && my < height-18 && items.size() > canShow){
            int max = items.size() - canShow;
            drawIndex = (float)(max * (my - 23)) / (height - 46) + 0.5;
            if(drawIndex < 0)
                drawIndex = 0;
            if(drawIndex > max)
                drawIndex = max;
            recalculatePosition();
        }
    }
}

void ListBox::onMouseUp(int mx, int my){
    if(!visible) return;

    if(upPressed){
        if(drawIndex > 0){
            drawIndex--;
            recalculatePosition();
        }
        upPressed= false;
    }
    if(downPressed){
        if(drawIndex+canShow < items.size()){
            drawIndex++;
            recalculatePosition();
        }
        downPressed= false;
    }
}

Item*  ListBox::getSelectedItem()
{
    return items.at(selected);
}

void ListBox::setSelectedItem(int index)
{
    if(index >= 0 && index < items.size())
        selected = index;
}

void ListBox::setSelectedItem(Item* item)
{
    if(!item) return;

    for(unsigned i=0;i<items.size();i++)
        if(item->equals(items[i]))
        {
            selected = i;
            return;
        }
}

void ListBox::drawButton(int verIndex, bool pressed,bool upArrow)
{
  if (pressed)
  {
	  GuiRender::getInstance().drawImage(GUI_TEX_BTN_PRESSED_LEFT,  vertex[verIndex]);
	  GuiRender::getInstance().drawImage(GUI_TEX_BTN_PRESSED_MIDDLE,vertex[verIndex+1]);
	  GuiRender::getInstance().drawImage(GUI_TEX_BTN_PRESSED_RIGHT, vertex[verIndex+2]);
          GuiRender::getInstance().move(0,-1);
  }
  else
  {
	  GuiRender::getInstance().drawImage(GUI_TEX_BTN_UNPRESSED_LEFT,  vertex[verIndex]);
	  GuiRender::getInstance().drawImage(GUI_TEX_BTN_UNPRESSED_MIDDLE,vertex[verIndex+1]);
	  GuiRender::getInstance().drawImage(GUI_TEX_BTN_UNPRESSED_RIGHT,vertex[verIndex+2]);
  }

  if(upArrow)
	  GuiRender::getInstance().drawImage(GUI_TEX_SCROLL_UP_ARROW,vertex[verIndex+3]);
  else
	  GuiRender::getInstance().drawImage(GUI_TEX_SCROLL_DOWN_ARROW,vertex[verIndex+3]);
}



void ListBox::addItem(Item* item){
    items.push_back(item);
    if(items.size() == 1){
        selected = 0;
    }
    recalculatePosition();
}

void ListBox::onKeyUp(int key){
    unsigned size = items.size();
    switch(key){
        case SDLK_DOWN://GLFW_KEY_DOWN:
            if(selected == -1 && size > 0){
                selected = 0;
                drawIndex = 0;
                recalculatePosition();
            }
            if(selected+1 < size){
                selected++;
                if(drawIndex + canShow <= selected){
                    drawIndex = selected - canShow + 1;
                    recalculatePosition();
                }
            }
            break;
        case SDLK_UP://GLFW_KEY_UP:
            if(selected == -1 && size > 0){
                selected = size - 1;
                if(size > canShow){
                    drawIndex = size - canShow;
                    recalculatePosition();
                }
            }
            if(selected-1 >= 0){
                selected--;
                if(drawIndex > selected){
                    drawIndex = selected;
                    recalculatePosition();
                }
            }
            break;
        case SDLK_TAB://GLFW_KEY_TAB:
            parent->focusNext();
            break;
    }
    if(key != SDLK_TAB)//GLFW_KEY_TAB)
        KeyUp(this,key);
}

