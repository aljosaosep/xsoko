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
 * File:   button.h
 * Author: jernej
 *
 * Created on Ponedeljek, 20 julij 2009, 23:27
 */

#ifndef _BUTTON_H
#define	_BUTTON_H

#include "component.h"

class Button : public Component{
private:
    bool pressed;
    string caption;
    Font* fnt;
public:
    Button(int x, int y, int width, int height, string caption);
    ~Button();
    string getCaption();
    Font* getFont();
    void setCaption(const string& caption);
    void Render();
    void onMouseDown(int mx, int my);
    void onMouseUp(int mx, int my);
    void onKeyUp(int key);
    void onKeyDown(int key);

    //event
    signal<void (Component*) > onPressed;
};

#endif	/* _BUTTON_H */

