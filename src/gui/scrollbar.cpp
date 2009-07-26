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
 * File:   scrollbar.cpp
 * Author: jernej
 * 
 * Created on Petek, 24 julij 2009, 23:54
 */

#include "scrollbar.h"
#include "container.h"

Scrollbar::Scrollbar(int x, int y, int width, int height) : Component(x,y,width,height), min(0), max(100),
        step(1),position(0),orient(Vertical), eventHandler(NULL), upPressed(false), downPressed(false)
{ }

Scrollbar::~Scrollbar() {
}

void Scrollbar::setLimits(int min, int max){
    if(min < max){
        this->min = min;
        this->max = max;
    } else {
        this->min = max;
        this->max = min;
    }
    if(position < min)
        position = min;
    if(position > max)
        position = max;
}

void Scrollbar::setStep(int step){
    if(step <= (max - min))
        this->step = step;
}

void Scrollbar::setPosition(int position){
    if(position < max)
        this->position = position;
}

void Scrollbar::setOrientation(Orientation orientation){
    orient = orientation;
}

void Scrollbar::setEventHandler(ScrollbarEventHandler* handler){
    eventHandler = handler;
}

int Scrollbar::getMinLimit(){
    return min;
}

int Scrollbar::getMaxLimit(){
    return max;
}

int Scrollbar::getStep(){
    return step;
}

int Scrollbar::getPosition(){
    return position;
}

Orientation Scrollbar::getOrientation(){
    return orient;
}

void Scrollbar::Render(){
    glColor3f(1,1,1);
    drawButton(x,y,upPressed,true);
    drawButton(x,y+height-16,downPressed,false);
    glColor3f(1,1,1);
    glBegin(GL_QUADS);
          glTexCoord2f((float) 8/128, (float)61/128); glVertex2i(x+(float)width/2,  -y-16);
          glTexCoord2f((float) 8/128, (float)34/128); glVertex2i(x+(float)width/2,  -y-height+16);
          glTexCoord2f((float) 9/128, (float)34/128); glVertex2i(x+(float)width/2-1,-y-height+16);
          glTexCoord2f((float) 9/128, (float)61/128); glVertex2i(x+(float)width/2-1,-y-16);
    glEnd();
    float dy = ((float)(height - 42) / (max - min)) * (position-min);
    glTranslatef(0,0,0.02f);
    glBegin(GL_QUADS);
      glTexCoord2f((float)99/128, (float)61/128);	glVertex2f(x+(float)width/2-5,-y-dy-16);
      glTexCoord2f((float)99/128, (float)53/128);	glVertex2f(x+(float)width/2-5,-y-dy-26);
      glTexCoord2f((float)91/128, (float)53/128);	glVertex2f(x+(float)width/2+5,-y-dy-26);
      glTexCoord2f((float)91/128, (float)61/128);	glVertex2f(x+(float)width/2+5,-y-dy-16);
    glEnd();
}

void Scrollbar::drawButton(int x, int y,bool pressed,bool upArrow)
{
  glPushMatrix();
  if (pressed)
  {
    glBegin(GL_QUADS);
      // left side
      glTexCoord2f((float)57/128, (float)95/128); glVertex2i(x, -y);
      glTexCoord2f((float)57/128, (float)70/128); glVertex2i(x, -y-16);
      glTexCoord2f((float)62/128, (float)70/128); glVertex2i(x+6,-y-16);
      glTexCoord2f((float)62/128, (float)95/128); glVertex2i(x+6, -y);

      // middle
      glTexCoord2f((float)62/128, (float)95/128); glVertex2i(x+6, -y);
      glTexCoord2f((float)62/128, (float)70/128); glVertex2i(x+6, -y-16);
      glTexCoord2f((float)66/128, (float)70/128); glVertex2i(x+10, -y-16);
      glTexCoord2f((float)66/128, (float)95/128); glVertex2i(x+10, -y);

      // right side
      glTexCoord2f((float)66/128, (float)95/128); glVertex2i(x+10, -y);
      glTexCoord2f((float)66/128, (float)70/128); glVertex2i(x+10, -y-16);
      glTexCoord2f((float)71/128, (float)70/128); glVertex2i(x+16, -y-16);
      glTexCoord2f((float)71/128, (float)95/128); glVertex2i(x+16, -y);
    glEnd();
    glTranslatef(1,0,0.2f);
  }
  else
  {
    glBegin(GL_QUADS);
      // left side
      glTexCoord2f((float)41/128, (float)95/128); glVertex2i(x, -y);
      glTexCoord2f((float)41/128, (float)70/128); glVertex2i(x, -y-16);
      glTexCoord2f((float)46/128, (float)70/128); glVertex2i(x+6,-y-16);
      glTexCoord2f((float)46/128, (float)95/128); glVertex2i(x+6, -y);

      // middle
      glTexCoord2f((float)46/128, (float)95/128); glVertex2i(x+6, -y);
      glTexCoord2f((float)46/128, (float)70/128); glVertex2i(x+6, -y-16);
      glTexCoord2f((float)50/128, (float)70/128); glVertex2i(x+10, -y-16);
      glTexCoord2f((float)50/128, (float)95/128); glVertex2i(x+10, -y);

      // right side
      glTexCoord2f((float)50/128, (float)95/128); glVertex2i(x+10, -y);
      glTexCoord2f((float)50/128, (float)70/128); glVertex2i(x+10, -y-16);
      glTexCoord2f((float)55/128, (float)70/128); glVertex2i(x+16, -y-16);
      glTexCoord2f((float)55/128, (float)95/128); glVertex2i(x+16, -y);
    glEnd();
    glTranslatef(0,0,0.2f);
  }
  if(upArrow){
    glBegin(GL_QUADS);
      glTexCoord2f((float)117/128, (float)63/128); glVertex2i(x, -y);
      glTexCoord2f((float)117/128, (float)50/128); glVertex2i(x, -y-16);
      glTexCoord2f((float)104/128, (float)50/128); glVertex2i(x+16,-y-16);
      glTexCoord2f((float)104/128, (float)63/128); glVertex2i(x+16, -y);
    glEnd();
  } else {
      glBegin(GL_QUADS);
        glTexCoord2f((float)104/128, (float)50/128); glVertex2i(x, -y);
        glTexCoord2f((float)104/128, (float)63/128); glVertex2i(x, -y-16);
        glTexCoord2f((float)117/128, (float)63/128); glVertex2i(x+16,-y-16);
        glTexCoord2f((float)117/128, (float)50/128); glVertex2i(x+16, -y);
      glEnd();
  }
  glPopMatrix();
}

void Scrollbar::onMouseDown(int mx, int my){
    if(!visible) return;

    if(my >= 0 && my <= 16){
        upPressed = true;
    }
    if(my >= height-16){
        downPressed = true;
    }
    if(my > 16 && my < height - 16){
        int oldPos = position;
        position = (float)((max - min) * (my - 21)) / (height - 42) + min;
        position = (position > 0.0) ? floor(position + 0.5) : ceil(position - 0.5);
        if(position < min)
            position = min;
        if(position > max)
            position = max;
        if(oldPos != position && eventHandler != NULL)
            eventHandler->PositionChanged(this,position);
    }
}

void Scrollbar::onKeyDown(int key){
    switch(key){
        case GLFW_KEY_DOWN:
            downPressed = true;
            break;
        case GLFW_KEY_UP:
            upPressed = true;
            break;
    }
}

void Scrollbar::onKeyUp(int key){
    switch(key){
        case GLFW_KEY_TAB:
            parent->focusNext();
            break;
        case GLFW_KEY_DOWN:
            if(position + step <= max){
                position += step;
                if(eventHandler != NULL){
                    eventHandler->PositionChanged(this, position);
                }
            }
            downPressed= false;
            break;
        case GLFW_KEY_UP:
            if(position - step >= min){
                position -= step;
                if(eventHandler != NULL){
                    eventHandler->PositionChanged(this, position);
                }
            }
            upPressed= false;
            break;
    }
}

void Scrollbar::onMouseUp(int mx, int my){
    if(!visible) return;

    if(upPressed){
        if(position - step >= min){
            position -= step;
            if(eventHandler != NULL){
                eventHandler->PositionChanged(this, position);
            }
        }
        upPressed= false;
    }
    if(downPressed){
        if(position + step <= max){
            position += step;
            if(eventHandler != NULL){
                eventHandler->PositionChanged(this, position);
            }
        }
        downPressed= false;
    }
}
