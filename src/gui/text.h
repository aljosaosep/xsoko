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
 * File:   text.h
 * Author: jernej
 *
 * Created on Ponedeljek, 20 julij 2009, 23:29
 */

#ifndef _TEXT_H
#define	_TEXT_H

#include "component.h"

class Text : public Component{
private:
    string caption;
    bool autoResize;
protected:
    void onRender();
public:
    //constructors and destructor
    Text(int x,int y,string text);

    //getters
    string  getText();
    bool    isAutoResize();

    //setters
    void setText(const string& text);
    void setAutoResize(bool autoResize);
};

#endif	/* _TEXT_H */

