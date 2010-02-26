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
/* 
 * File:   listbox.h
 * Author: jernej
 *
 * Created on Ponedeljek, 20 julij 2009, 23:34
 */

#ifndef _LISTBOX_H
#define	_LISTBOX_H

#include "scrollbar.h"

class Item{
public:
    virtual string toString()= 0;
    virtual bool equals(Item* item) = 0;
};

class ListBox: public Component{
private:
    vector<Item*> items;
    unsigned selected;
    unsigned drawIndex;
    unsigned canShow;
    auto_ptr<Scrollbar> scroll;

    Rect vertex[5];
private:
    void onScrollChange(Component*, int position);
protected:
    void onRender();
public:
    static const unsigned unselected;
public:
    //constructors and destructor
    ListBox(int x, int y, int width, int height);

    //methods
    void addItem(Item* item);

    //setters
    void setSelectedItem(unsigned index);
    void setSelectedItem(Item* item);

    //getters
    Item* getSelectedItem();

    //events support
    void invalidate();
    void onMouseDown(int mx, int my);
    void onMouseUp(int mx, int my);
    void onKeyUp(int key);

    //event
    signal<void (Component*, Item*)> onItemSelect;
};

#endif	/* _LISTBOX_H */

