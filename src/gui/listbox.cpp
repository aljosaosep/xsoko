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

#include "listbox.h"
#include "container.h"

const unsigned ListBox::unselected = -1;

ListBox::ListBox(int x, int y, int width, int height) : 
    Component(x,y,width,height), selected(unselected),
    drawIndex(0), scroll(new Scrollbar(width-18,2,16,height-4))
{
    scroll->setLimits(0,0);
    scroll->PositionChanged.connect(bind(&ListBox::onScrollChange, this, _1, _2));
    canShow = (height-4) / 16;
    invalidate();
}

void ListBox::invalidate() {
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

    scroll->invalidate();
}

void ListBox::onRender() {
    renderer.drawImage(GUI_TEX_PANEL_TOP,   vertex[0]);
    renderer.drawImage(GUI_TEX_PANEL_LEFT,  vertex[1]);
    renderer.drawImage(GUI_TEX_PANEL_MIDLLE,vertex[2]);
    renderer.drawImage(GUI_TEX_PANEL_RIGHT, vertex[3]);
    renderer.drawImage(GUI_TEX_PANEL_BOTTOM,vertex[4]);

    unsigned limit = (canShow<items.size()) ? canShow : items.size();
    for(unsigned i=0;i<limit;i++) {
	renderer.setClipping(2,2+(i*16),width-19,18+(i*16));
        if(selected == i+drawIndex) {
            renderer.setColor((float)89/255,(float)97/255,(float)102/255,1);
            renderer.drawFilledRect(2,2+(i*16),width-19,18+(i*16));
            fnt->writeText(6,18+(i*16),items.at(i+drawIndex)->toString());
        } else 
            fnt->writeText(5,17+(i*16),items.at(i+drawIndex)->toString());
	renderer.restoreClipping();
    }

    scroll->Render();
}

void ListBox::onMouseDown(int mx, int my) {
    if(!visible) return;

    if(mx >= 2 && mx <= width-18 && my > 2 && my <= height-2) {
        unsigned index = (my-2) / 16 + drawIndex;
        if(index < items.size()) {
            selected = index;
            onItemSelect(this,items.at(selected));
        }
    } else
        if((mx >= width - 18) && (mx <= width  - 2) &&
           (my >= 2)          && (my <= height - 2))
            scroll->onMouseDown(mx-width+18, my-2);
    MouseDown(this,mx,my);
}

void ListBox::onMouseUp(int mx, int my) {
    if(!visible) return;

    if((mx >= width - 18) && (mx <= width  - 2) &&
       (my >= 2)          && (my <= height - 2))
        scroll->onMouseUp(mx-width+18, my-2);
    MouseDown(this,mx,my);
}

void ListBox::onScrollChange(Component*, int position) {
    drawIndex = position;
}

Item* ListBox::getSelectedItem() {
    return items.at(selected);
}

void ListBox::setSelectedItem(unsigned index) {
    if(index != selected) {
        if(index != unselected) {
            if(index < items.size()) {
                selected = index;
                if(selected < drawIndex)
                    scroll->setValue(selected);
                else if (selected >= drawIndex + canShow)
                    scroll->setValue(selected - canShow + 1);
                onItemSelect(this,items[selected]);
            }
        } else {
            selected = unselected;
            onItemSelect(this,NULL);
        }
    }
}

void ListBox::setSelectedItem(Item* item) {
    if(!item) {
        setSelectedItem(unselected);
        return;
    }
    for(unsigned i=0;i<items.size();i++)
        if(item->equals(items[i])) {
            setSelectedItem(i);
            return;
        }
}

void ListBox::addItem(Item* item) {
    items.push_back(item);
    scroll->setLimits(0, items.size()-canShow);
}

void ListBox::onKeyUp(int key) {
    unsigned size = items.size();
    if(size == 0) return;
    bool change = true;
    switch(key){
        case SDLK_DOWN:
            if(selected == unselected && size > 0)
                selected = 0;
            else if(selected+1 < size)
                selected++;
            else
                change = false;
            break;
        case SDLK_UP:
            if(selected == unselected && size > 0)
                selected = size - 1;
            else if(selected > 0 && selected != unselected)
                selected--;
            else
                change = false;
            break;
        case SDLK_TAB:
            parent->focusNext();
            return;
    }
    if(change) {
        if(drawIndex > selected)
            scroll->setValue(selected);
        else if(drawIndex + canShow <= selected)
            scroll->setValue(selected - canShow + 1);
        onItemSelect(this,items.at(selected));
    }
    KeyUp(this,key);
}
