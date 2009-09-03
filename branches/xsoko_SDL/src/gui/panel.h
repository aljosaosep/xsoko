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
 * File:   panel.h
 * Author: jernej
 *
 * Created on Ponedeljek, 20 julij 2009, 23:33
 */

#ifndef _PANEL_H
#define	_PANEL_H

#include "container.h"

class Panel: public Container{
private:
    //for rendering
    Rect vertex[5];
    Rect texture[5];
protected:
    void onRender();
public:
    //constructors and destructor
    Panel(int x, int y, int width, int height);

    //events support
    void invalidate();
};

#endif	/* _PANEL_H */

