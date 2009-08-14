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

#include <GL/gl.h>

#include "fonts.h"

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
{ }

EditBox::~EditBox() {
    delete fnt;
}

void EditBox::setText(string text){
    this->text = text;
    carrotPos = text.length();
}

string EditBox::getText(){
    return text;
}

Font* EditBox::getFont(){
    return fnt;
}

void EditBox::Render(){
    if(visible){
        glColor3f(1,1,1);
        glBindTexture(GL_TEXTURE_2D,Gui::skinTextureID);
        glBegin(GL_QUADS);
          // top of panel.
          glTexCoord2f((float)10/128, (float)33/128); glVertex2i(x+2, -y);
          glTexCoord2f((float)10/128, (float)32/128); glVertex2i(x+2, -y-2);
          glTexCoord2f((float)37/128, (float)32/128); glVertex2i(x+2+(width-4), -y-2);
          glTexCoord2f((float)37/128, (float)33/128); glVertex2i(x+2+(width-4), -y);

          // left side of panel.
          glTexCoord2f((float)38/128, (float)61/128); glVertex2i(x, -y);
          glTexCoord2f((float)38/128, (float)34/128); glVertex2i(x, -y-height+2);
          glTexCoord2f((float)39/128, (float)34/128); glVertex2i(x+2, -y-height+2);
          glTexCoord2f((float)39/128, (float)61/128); glVertex2i(x+2, -y);

          // middle of panel.
          glTexCoord2f((float)18/128, (float)54/128); glVertex2i(x+2, -y-2);
          glTexCoord2f((float)18/128, (float)42/128); glVertex2i(x+2, -y-height+2);
          glTexCoord2f((float)30/128, (float)42/128); glVertex2i(x+2+(width-4), -y-height+2);
          glTexCoord2f((float)30/128, (float)54/128); glVertex2i(x+2+(width-4), -y-2);

          // right side of panel.
          glTexCoord2f((float) 8/128, (float)61/128); glVertex2i(x+width-2, -y);
          glTexCoord2f((float) 8/128, (float)34/128); glVertex2i(x+width-2, -y-height+2);
          glTexCoord2f((float) 9/128, (float)34/128); glVertex2i(x+width, -y-height+2);
          glTexCoord2f((float) 9/128, (float)61/128); glVertex2i(x+width, -y);

          // bottom middle of panel.
          glTexCoord2f((float)10/128, (float)62/128); glVertex2i(x+2, -y-height+2);
          glTexCoord2f((float)10/128, (float)63/128); glVertex2i(x+2, -y-height);
          glTexCoord2f((float)37/128, (float)63/128); glVertex2i(x+2+(width-2), -y-height);
          glTexCoord2f((float)37/128, (float)62/128); glVertex2i(x+2+(width-2), -y-height+2);

        glEnd();

        int deltay = (height - fnt->getSize())/2 + fnt->getSize();
        //glEnable(GL_SCISSOR_TEST);
        //glScissor(x,600-y-height,width,height);

        fnt->writeText(x+3,-y-deltay,text);

        //draw carrot
        if(focused && !((int)((glfwGetTime()-time)/0.5)&1)){
            glTranslatef(0,0,0.02f);
            string first = text.substr(0,carrotPos);
            int offset = fnt->stringWidth(first) + 4;
            
            glColor3f(0,0,0);
            glLineWidth(2);
            glBegin(GL_LINE);
            glVertex2i(x+offset,-y-deltay);
            glVertex2i(x+offset,-y-deltay+fnt->getSize());
            glEnd();
        }
        //glDisable(GL_SCISSOR_TEST);

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
