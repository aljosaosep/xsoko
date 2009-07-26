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

#include "component.h"

class ListBoxListener{
public:
    virtual void onAction(Component* listBox, string selected) = 0;
    virtual void onKeyClick(Component* listBox, int key) = 0;
};

class ListBox: public Component{
private:
    vector<string> items;
    int selected;
    int drawIndex;
    unsigned canShow;
    bool upPressed;
    bool downPressed;
    void drawButton(int x, int y,bool pressed,bool upArrow);
    void drawSelected(int x, int y,int width,string item);
    ListBoxListener* action;
    Font* fnt;
public:
    ListBox(int x, int y, int width, int height);
    ~ListBox();
    void addItem(string item);
    string getSelectedItem();
    Font* getFont();
    void setAction(ListBoxListener* action);
    void Render();
    void onMouseDown(int mx, int my);
    void onMouseUp(int mx, int my);
    void onKeyUp(int key);
};

#endif	/* _LISTBOX_H */

