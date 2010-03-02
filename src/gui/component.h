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
 * File:   component.h
 * Author: jernej
 *
 * Created on Ponedeljek, 20 julij 2009, 23:15
 */

#ifndef _COMPONENT_H
#define	_COMPONENT_H

#include "commongui.h"
#include "guirender.h"

class Container;

class Component {
protected:
    int x, y;
    int width, height;
    bool visible;
    Container* parent;
    string name;
    bool focusable;
    bool focused;
    GuiRender &renderer;
    auto_ptr<Font> fnt;

    virtual void onRender() = 0;
public:
    Component(int xx, int yy, int width, int height);

    //getters
    Position    getPosition();
    Size        getSize();
    Container*  getParent();
    string      getName();
    bool        isVisible();
    bool        isFocusable();
    Font*       getFont();

    //setters
    void setPosition(int x, int y);
    void setParent(Container* parent);
    void setName(const string& name);
    void setFocusable(bool focus);
    void setFont(Font* font);
    virtual void setSize(int width, int height);
    virtual void setVisible(bool visible);

    void Render();

    virtual void focusGain();
    virtual void focusLost();
    virtual void invalidate() {}
    virtual void onMouseDown(int mx, int my);
    virtual void onMouseUp(int mx, int my);
    virtual void onMouseMove(int mx, int my);
    virtual void onMouseEnter(int mx, int my);
    virtual void onMouseExit();
    virtual void onKeyDown(int key);
    virtual void onKeyUp(int key);
    virtual void onCharClick(int c) {}

    //events
    //Focus events
    signal<void(Component*,bool) > FocusChange;
    //signal<void(Component*) > FocusLost;
    signal<void(Component*,bool) > VisibilityChange;
    //Mouse events
    signal<void(Component*,int,int) > MouseDown;
    signal<void(Component*,int,int) > MouseUp;
    signal<void(Component*,int,int) > MouseMove;
    signal<void(Component*,int,int) > MouseEnter;
    signal<void(Component*) >         MouseExit;
    //Keyboard events
    signal<void(Component*,int) > KeyDown;
    signal<void(Component*,int) > KeyUp;
};

#endif	/* _COMPONENT_H */

