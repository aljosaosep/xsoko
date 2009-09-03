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

#include <vector>


#include "container.h"

Container::Container(int x, int y, int width, int height): Component(x,y,width,height), compPressed(NULL),
        focusedComp(NULL)
{}

void Container::AddComponent(Component* component){
    component->setParent(this);
    components.push_back(component);
    focusComponents.push_back(component);
    sort (focusComponents.begin(), focusComponents.end(), sortObj);
	if(focusedComp == NULL && component->getFocusIndex() != -1)
        focusedComp = component;
}

bool Container::isInArea(Position p, Size s, int x, int y){
    if ((x >= p.x) && (x <= p.x + s.width)&&
       (y >= p.y) && (y <= p.y + s.height))
        return true;
    else
        return false;
}

void Container::onMouseDown(int mx, int my){
    if(!visible)
        return;

    for(unsigned i=0;i<components.size();i++)
    {
        Position pos = components[i]->getPosition();
        if (isInArea(pos,components[i]->getSize(),mx,my))
        {
            compPressed = components[i];
            if(focusedComp != compPressed){
                if(focusedComp != NULL)
                    focusedComp->focusLost();
                focusedComp = compPressed;
                focusedComp->focusGain();
            }
            compPressed->onMouseDown(mx-pos.x,my-pos.y);
            break;
        }
    }
    MouseDown(this,mx,my);
}

void Container::onMouseUp(int mx, int my){
    if(compPressed != NULL){
        compPressed->onMouseUp(mx,my);
        compPressed = NULL;
    }
    for(unsigned i=0;i<components.size();i++)
        if(components[i]->isContainer())
            components[i]->onMouseUp(mx,my);
    MouseUp(this,mx,my);
}

Container::~Container(){
    for(unsigned i=0;i<components.size();i++){
        delete components[i];
    }
}

void Container::focusNext(){
    for(unsigned i=0;i<focusComponents.size();i++)
        if(focusComponents[i] == focusedComp){
            focusedComp->focusLost();
            if(i < focusComponents.size()-1)
                focusedComp = focusComponents[i+1];
            else
                focusedComp = focusComponents.front();
            focusedComp->focusGain();
            break;
        }
}

void Container::focusPrevious(){
    for(unsigned i=0;i<focusComponents.size();i++)
        if(focusComponents[i] == focusedComp){
            focusedComp->focusLost();
            if(i > 0)
                focusedComp = focusComponents[i-1];
            else
                focusedComp = focusComponents.back();
            focusedComp->focusGain();
            break;
        }
}

void Container::focusGain(){
    if(focusedComp != NULL)
        focusedComp->focusGain();
    Component::focusGain();
}

void Container::focusLost(){
    if(focusedComp != NULL)
        focusedComp->focusLost();
    Component::focusLost();
}

void Container::onKeyDown(int key){
    if(focusedComp != NULL)
        focusedComp->onKeyDown(key);
    else
        KeyDown(this,key);
}

void Container::onKeyUp(int key){
    if(focusedComp != NULL)
        focusedComp->onKeyUp(key);
    else
        KeyUp(this,key);
}

void Container::onCharClick(int c){
    if(focusedComp != NULL)
        focusedComp->onCharClick(c);
}
