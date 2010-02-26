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
 * File:   container.h
 * Author: jernej
 *
 * Created on Ponedeljek, 20 julij 2009, 23:19
 */

#ifndef _CONTAINER_H
#define	_CONTAINER_H

#include "component.h"

class Container : public Component{
private:
    Component* mainFocusComp;
    Component* mouseFocusComp;
    int mousex, mousey;
private:
    void refreshMouseFocus();
    void focusGainEvent(Component* sender);
    void focusLostEvent(Component* sender);
protected:
    vector<Component*> components;
protected:
    bool pointOnComponent(int px, int py, Component* component);
public:
    //constructors and destructor
    Container(int x, int y, int width, int height);
    ~Container();

    //methods
    void addComponent(Component* component);
    void focusNext();
    void focusPrevious();
    virtual void focusGain();
    virtual void focusLost();

    //event support
    virtual void onMouseDown(int mx, int my);
    virtual void onMouseUp(int mx, int my);
    virtual void onMouseMove(int mx, int my);
    virtual void onKeyDown(int key);
    virtual void onKeyUp(int key);
    virtual void onCharClick(int c);
};

#endif	/* _CONTAINER_H */

