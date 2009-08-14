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
 * File:   editbox.h
 * Author: jernej
 *
 * Created on Torek, 28 julij 2009, 17:54
 */

#ifndef _EDITBOX_H
#define	_EDITBOX_H

#include "component.h"
#include "fonts.h"

class EditBox : public Component{
private:
    Font *fnt;
    string text;
    unsigned carrotPos;
    double time;
public:
    EditBox(int x, int y, int width, int height);
    void setText(string text);
    string getText();
    Font* getFont();
    void setSize(int width, int height);
    void focusGain();
    void Render();
    void onKeyUp(int key);
    void onCharClick(int c);
    virtual ~EditBox();
private:

};

#endif	/* _EDITBOX_H */

