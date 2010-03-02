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

#include "container.h"

Container::Container(int x, int y, int width, int height) :
    Component(x,y,width,height), mainFocusComp(NULL), mouseFocusComp(NULL)
{}

void Container::addComponent(Component* component){
    component->setParent(this);
    //component->FocusGain.connect(bind(&Container::focusGainEvent,this,_1));
    //component->FocusLost.connect(bind(&Container::focusLostEvent,this,_1));
    components.push_back(component);
    if(mainFocusComp == NULL && component->isFocusable()) {
        mainFocusComp = component;
        mainFocusComp->focusGain();
    }
}

inline bool Container::pointOnComponent(int px, int py, Component* component) {
    Position winPos = component->getPosition();
    Size winSize = component->getSize();
    return ((px >= winPos.x) && (px <= winPos.x + winSize.width) &&
            (py >= winPos.y) && (py <= winPos.y + winSize.height) &&
            component->isVisible());
}

void Container::onMouseDown(int mx, int my){
    if(visible && mouseFocusComp) {
        if(mainFocusComp != mouseFocusComp){
            if(mainFocusComp != NULL)
                mainFocusComp->focusLost();
            mainFocusComp = mouseFocusComp;
            mainFocusComp->focusGain();
        }
        Position pos = mainFocusComp->getPosition();
        mainFocusComp->onMouseDown(mx-pos.x,my-pos.y);
        MouseDown(this,mx,my);
    }
}

void Container::onMouseUp(int mx, int my){
    if(visible) {
        if(mouseFocusComp) {
            Position winPos = mouseFocusComp->getPosition();
            mouseFocusComp->onMouseUp(mx-winPos.x, my-winPos.y);
        }
        MouseUp(this,mx,my);
    }
}

void Container::onMouseMove(int mx, int my) {
    mousex = mx;
    mousey = my;
    refreshMouseFocus();
    if(mouseFocusComp) {
        Position pos = mouseFocusComp->getPosition();
        mouseFocusComp->onMouseMove(mousex-pos.x,mousey-pos.y);
    }
    MouseMove(this, mx, my);
}

void Container::refreshMouseFocus() {
    if(!mouseFocusComp || !pointOnComponent(mousex, mousey, mouseFocusComp)) {
        if(mouseFocusComp) {
            mouseFocusComp->onMouseExit();
            mouseFocusComp = NULL;
        }
        vector<Component*>::const_iterator it;
        for(it = components.begin(); it != components.end(); ++it)
            if(pointOnComponent(mousex, mousey, *it)) {
                mouseFocusComp = *it;
                Position pos = (*it)->getPosition();
                mouseFocusComp->onMouseEnter(mousex-pos.x,mousey-pos.y);
                break;
            }
    }
}

void Container::focusNext(){
    unsigned size = components.size();
    for(unsigned i=0;i<size;i++)
        if(components[i] == mainFocusComp){
            mainFocusComp->focusLost();
            for(unsigned j=1;j<=size;j++)
                if(components[(i+j) % size]->isFocusable()) {
                    mainFocusComp = components[(i+j) % size];
                    break;
                }
            mainFocusComp->focusGain();
            break;
        }
}

void Container::focusPrevious(){
    unsigned size = components.size();
    for(unsigned i=0;i<size;i++)
        if(components[i] == mainFocusComp){
            mainFocusComp->focusLost();
            for(unsigned j=1;j<=size;j++)
                if(components[(size+i-j) % size]->isFocusable()) {
                    mainFocusComp = components[(size+i-j) % size];
                    break;
                }
            mainFocusComp->focusGain();
            break;
        }
}

void Container::focusGainEvent(Component* sender){
    if(mainFocusComp == NULL)
        mainFocusComp = sender;
    if(mainFocusComp != sender){
        mainFocusComp->focusLost();
        mainFocusComp = sender;
    }
    refreshMouseFocus();
}

void Container::focusLostEvent(Component* sender) {
    mainFocusComp = NULL;
    for(int i=0;i<components.size();i++)
        if(components[i]->isFocusable() && components[i]->isVisible()) {
            mainFocusComp = components[i];
            mainFocusComp->focusGain();
            break;
        }
    refreshMouseFocus();
}

void Container::focusGain(){
    if(!focusable || focused) return;
    if(mainFocusComp != NULL)
        mainFocusComp->focusGain();
    Component::focusGain();
}

void Container::focusLost(){
    if(!focusable || !focused) return;
    if(mainFocusComp != NULL)
        mainFocusComp->focusLost();
    Component::focusLost();
}

void Container::onKeyDown(int key){
    if(mainFocusComp != NULL)
        mainFocusComp->onKeyDown(key);
    else
        KeyDown(this,key);
}

void Container::onKeyUp(int key){
    if(mainFocusComp != NULL)
        mainFocusComp->onKeyUp(key);
    else
        KeyUp(this,key);
}

void Container::onCharClick(int c){
    if(mainFocusComp != NULL)
        mainFocusComp->onCharClick(c);
}

Container::~Container(){
    for(unsigned i=0;i<components.size();i++){
        delete components[i];
    }
}
