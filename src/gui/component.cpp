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
 * File:   component.cpp
 * Author: jernej
 *
 * Created on Ponedeljek, 20 julij 2009, 23:17
 */

#include "component.h"
#include "container.h"

Component::Component(int xx, int yy, int width, int height)  : x(xx), y(yy),
        visible(true), parent(NULL), focused(false)
{ 
    setSize(width,height);
}

Position Component::getPosition(){
    Position pos;
    pos.x = this->x;
    pos.y = this->y;
    return pos;
}

void Component::focusGain(){
    if(focused) return;
    focused = true;
    FocusGain(this);
}

void Component::focusLost(){
    if(!focused) return;
    focused = false;
    FocusLost(this);
}

void Component::setFocusIndex(int index){
    focusIndex = index;
}

int Component::getFocusIndex(){
    return focusIndex;
}

Size Component::getSize(){
    Size size;
    size.width = this->width;
    size.height = this->height;
    return size;
}

Container* Component::getParent(){
    return parent;
}

void Component::setPosition(int x, int y){
    this->x = x;
    this->y = y;
}

void Component::setSize(int width, int height){
    this->width = width;
    this->height = height;
    invalidate();
}

bool Component::isVisible(){
    return this->visible;
}

void Component::setVisible(bool visible){
    this->visible = visible;
    if(visible)
        focusGain();
    else
        focusLost();
}

void Component::setParent(Container* parent){
    this->parent = parent;
}

void Component::setName(const string& name){
    this->name = name;
}

string Component::getName(){
    return name;
}

void Component::Render(){
    if(!visible) return;
    GuiRender::getInstance().saveState();
    GuiRender::getInstance().move((float)x,(float)y);
    onRender();
    GuiRender::getInstance().restoreState();
}

void Component::onKeyUp(int key){
    if(key == GLFW_KEY_TAB)
        parent->focusNext();
    else
        KeyUp(this,key);
}

void Component::onMouseDown(int mx, int my){
    MouseDown(this,mx,my);
}

void Component::onMouseUp(int mx, int my){
    MouseUp(this,mx,my);
}

void Component::onKeyDown(int key){
    KeyDown(this,key);
}
