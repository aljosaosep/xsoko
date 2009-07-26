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
 * File:   window.h
 * Author: jernej
 *
 * Created on Ponedeljek, 20 julij 2009, 23:41
 */

#ifndef _WINDOW_H
#define	_WINDOW_H

#include "container.h"

class Window;

class FocusHandler{
public:
    virtual void focusGain(Window* sender) = 0;
    virtual void focusLost(Window* sender) = 0;
};

class Window : public Container{
private:
    float alpha;
    float zorder;
    int screenHeight;
    MouseDrag mouseDrag;
    bool enableCloseButton;
    bool modal;
    string caption;
    Font* fnt;
    FocusHandler* focusHandler;
public:
    Window(int wX, int wY, int wWidth, int wHeight, string caption);
    ~Window();
    float getAlpha();
    float getZOrder();
    void setZOrder(float zorder);
    void setAlpha(float alpha);
    void setEnableCloseButton(bool enabled);
    void setModal(bool modal);
    void setVisible(bool visible);
    void setFocusHandler(FocusHandler* handler);
    void Render();
    void onMouseDown(int mx, int my);
    void onMouseMove(int mx, int my);
    void onMouseUp(int mx, int my);
    void onScreenResize();
    void focusGain();
    void focusLost();
    Font* getFont();
};

#endif	/* _WINDOW_H */

