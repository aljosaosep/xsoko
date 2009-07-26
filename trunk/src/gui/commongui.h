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
 * File:   commongui.h
 * Author: jernej
 *
 * Created on Ponedeljek, 20 julij 2009, 23:22
 */

#ifndef _COMMONGUI_H
#define	_COMMONGUI_H

//common includes for gui
#ifdef _WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glfw.h>
#include "fonts.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

//common structures
struct Position{
    int x,y;
};

struct Size{
    int width, height;
};

struct MouseDrag{
    bool drag;     // window draggin enabled
    int x,y;   // X and Y coords when drag started
};

#endif	/* _COMMONGUI_H */

