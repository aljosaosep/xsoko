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
 * File:   scrollbar.h
 * Author: jernej
 *
 * Created on Petek, 24 julij 2009, 23:54
 */

#ifndef _SCROLLBAR_H
#define	_SCROLLBAR_H

#include "component.h"

enum Orientation {
    Vertical = 1,
    Horizontal = 2
};

class ScrollbarEventHandler {
public:
    virtual void PositionChanged(Component* sender, int position) = 0;
};

class Scrollbar : public Component {
private:
    int min;
    int max;
    int step;
    int position;
    Orientation orient;
    ScrollbarEventHandler* eventHandler;
    bool upPressed;
    bool downPressed;
    void drawButton(int x, int y,bool pressed,bool upArrow);
public:
    Scrollbar(int x, int y, int width, int height);
    void setLimits(int min, int max);
    void setStep(int step);
    void setPosition(int position);
    void setOrientation(Orientation orientation);
    void setEventHandler(ScrollbarEventHandler* handler);
    int getMinLimit();
    int getMaxLimit();
    int getStep();
    int getPosition();
    Orientation getOrientation();
    void Render();
    void onMouseDown(int mx, int my);
    void onMouseUp(int mx, int my);
    void onKeyDown(int key);
    void onKeyUp(int key);
    ~Scrollbar();
};

#endif	/* _SCROLLBAR_H */

