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
 * File:   editbox.cpp
 * Author: jernej
 * 
 * Created on Torek, 28 julij 2009, 17:54
 */

#include "editbox.h"
#include "container.h"
#include "gui.h"

EditBox::EditBox(int x, int y, int width, int height) : Component(x,y,width,height), fnt(new Font("font")),
        text(""), carrotPos(0)
{
    invalidate();
}

EditBox::~EditBox() {
    delete fnt;
}

void EditBox::setText(string text){
    this->text = text;
    while(fnt->stringWidth(text) > width-8){
        text.erase(text.begin()+(text.size()-1));
    }
    carrotPos = text.length();
}

string EditBox::getText(){
    return text;
}

Font* EditBox::getFont(){
    return fnt;
}

void EditBox::invalidate(){
    // top of panel.
    vertex[0].x1 = 2;
    vertex[0].y1 = 0;
    vertex[0].x2 = width-2;
    vertex[0].y2 = 2;

    // left side of panel.
    vertex[1].x1 = 0;
    vertex[1].y1 = 0;
    vertex[1].x2 = 2;
    vertex[1].y2 = height-2;

    // middle of panel.
    vertex[2].x1 = 2;
    vertex[2].y1 = 2;
    vertex[2].x2 = width-2;
    vertex[2].y2 = height-2;

    // right side of panel.
    vertex[3].x1 = width-2;
    vertex[3].y1 = 0;
    vertex[3].x2 = width;
    vertex[3].y2 = height-2;

    // bottom middle of panel.
    vertex[4].x1 = 2;
    vertex[4].y1 = height-2;
    vertex[4].x2 = width;
    vertex[4].y2 = height;

    texture[0] = GuiRender::getInstance().getTextureLocation("panelT");
    texture[1] = GuiRender::getInstance().getTextureLocation("panelL");
    texture[2] = GuiRender::getInstance().getTextureLocation("panelM");
    texture[3] = GuiRender::getInstance().getTextureLocation("panelR");
    texture[4] = GuiRender::getInstance().getTextureLocation("panelB");
}

void EditBox::onRender(){
    GuiRender::getInstance().drawImage(texture[0],vertex[0]); // top of panel.
    GuiRender::getInstance().drawImage(texture[1],vertex[1]); // left side of panel.
    GuiRender::getInstance().drawImage(texture[2],vertex[2]); // middle of panel.
    GuiRender::getInstance().drawImage(texture[3],vertex[3]); // right side of panel.
    GuiRender::getInstance().drawImage(texture[4],vertex[4]); // bottom middle of panel.

    int deltay = (height - fnt->getSize())/2 + fnt->getSize();
    fnt->writeText(3,deltay,text);

    //draw carrot
    if(focused && !((int)((glfwGetTime()-time)/0.5)&1)){
        GuiRender::getInstance().saveState();
        GuiRender::getInstance().nextLayer();
        string first = text.substr(0,carrotPos);
        int offset = fnt->stringWidth(first) + 4;

        GuiRender::getInstance().setColor(0,0,0,1);
        GuiRender::getInstance().drawLine(offset,deltay,offset,deltay-fnt->getSize(),2);
        GuiRender::getInstance().restoreState();
    }
}

void EditBox::onKeyUp(int key){
    switch(key){
        case GLFW_KEY_TAB:
            parent->focusNext();
            break;
        case GLFW_KEY_BACKSPACE:
            if(carrotPos>0){
                text.erase(text.begin()+(carrotPos-1));
                carrotPos--;
            }
            break;
        case GLFW_KEY_DEL:
            if(carrotPos < text.size()){
                text.erase(text.begin()+carrotPos);
            }
            break;
        case GLFW_KEY_LEFT:
            if(carrotPos > 0){
                carrotPos--;
            }
            break;
        case GLFW_KEY_RIGHT:
            if(carrotPos < text.size()){
                carrotPos++;
            }
            break;
    }
    KeyUp(this,key);
    time = glfwGetTime();
}

void EditBox::onCharClick(int c){
    //only ascii characters
    //if(c < 256){
        text.insert(text.begin()+(carrotPos++),(char)c);
        if(fnt->stringWidth(text) > width - 8)
            text.erase(text.begin()+(--carrotPos));
    //}
}

void EditBox::focusGain(){
    Component::focusGain();
    time = glfwGetTime();
}

void EditBox::setSize(int width, int height){
    this->width = width;
    this->height = height;
    if(height < fnt->getSize()+4)
        this->height = fnt->getSize()+4;
}
