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
        visible(true), parent(NULL), focusable(true), focused(false),
        renderer(GuiRender::getInstance()), fnt(new Font("font"))
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
    if(!focusable || focused) return;
    focused = true;
    FocusChange(this,focused);
}

void Component::focusLost(){
    if(!focusable || !focused) return;
    focused = false;
    FocusChange(this,focused);
}

void Component::setFocusable(bool focus){
    focusable = focus;
}

bool Component::isFocusable() {
    return focusable;
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

Font* Component::getFont() {
    return fnt.get();
}

void Component::setFont(Font* font) {
    fnt.reset(font);
}

void Component::Render(){
    if(!visible) return;
    renderer.saveState();
    renderer.move(x,y);
    renderer.setClipping(0,0,width,height);
    onRender();
    renderer.restoreClipping();
    renderer.restoreState();
}

void Component::onKeyUp(int key){
    if(key == SDLK_TAB)
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

void Component::onMouseMove(int mx, int my){
    MouseMove(this,mx,my);
}

void Component::onMouseEnter(int mx, int my) {
    MouseEnter(this,mx,my);
}

void Component::onMouseExit() {
    MouseExit(this);
}

void Component::onKeyDown(int key){
    KeyDown(this,key);
}
