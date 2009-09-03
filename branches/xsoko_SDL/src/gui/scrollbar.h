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

class Scrollbar : public Component {
private:
    int min;
    int max;
    int step;
    int position;
    Orientation orient;
    bool upPressed;
    bool downPressed;
    void drawButton(int verIndex,bool pressed,bool upArrow);
    void recalculatePosition();

    Rect vertex[10];
    Rect texture[10];
protected:
    void onRender();
public:
    //constructors and destructors
    Scrollbar(int x, int y, int width, int height);
    ~Scrollbar();

    //setters
    void setLimits(int min, int max);
    void setStep(int step);
    void setPosition(int position);
    void setOrientation(Orientation orientation);

    //getters
    int getMinLimit();
    int getMaxLimit();
    int getStep();
    int getPosition();
    Orientation getOrientation();

    //events support
    void invalidate();
    void onMouseDown(int mx, int my);
    void onMouseUp(int mx, int my);
    void onKeyDown(int key);
    void onKeyUp(int key);

    //events
    signal<void(Component*,int)> PositionChanged;
};

#endif	/* _SCROLLBAR_H */

