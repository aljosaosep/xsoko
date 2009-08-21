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
        step(1),position(0),orient(Vertical), upPressed(false), downPressed(false)
{
    invalidate();
}

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

void Scrollbar::invalidate(){
    //upper button
    //left
    vertex[0].x1 = 0;
    vertex[0].y1 = 0;
    vertex[0].x2 = 6;
    vertex[0].y2 = 16;

    //middle
    vertex[1].x1 = 6;
    vertex[1].y1 = 0;
    vertex[1].x2 = width-6;
    vertex[1].y2 = 16;

    //right
    vertex[2].x1 = width-6;
    vertex[2].y1 = 0;
    vertex[2].x2 = width;
    vertex[2].y2 = 16;

    //arrow
    vertex[3].x1 = 0;
    vertex[3].y1 = 0;
    vertex[3].x2 = width;
    vertex[3].y2 = 16;

    //lover button
    //left
    vertex[4].x1 = 0;
    vertex[4].y1 = height-16;
    vertex[4].x2 = 6;
    vertex[4].y2 = height;

    //middle
    vertex[5].x1 = 6;
    vertex[5].y1 = height-16;
    vertex[5].x2 = width-6;
    vertex[5].y2 = height;

    //right
    vertex[6].x1 = width-6;
    vertex[6].y1 = height-16;
    vertex[6].x2 = width;
    vertex[6].y2 = height;

    //arrow
    vertex[7].x1 = 0;
    vertex[7].y1 = height-16;
    vertex[7].x2 = width;
    vertex[7].y2 = height;

    //body
    vertex[8].x1 = (float)width/2;
    vertex[8].y1 = 16;
    vertex[8].x2 = (float)width/2-1;
    vertex[8].y2 = height-16;

    recalculatePosition();

    texture[0] = GuiRender::getInstance().getTextureLocation("buttonPL");
    texture[1] = GuiRender::getInstance().getTextureLocation("buttonPM");
    texture[2] = GuiRender::getInstance().getTextureLocation("buttonPR");
    texture[3] = GuiRender::getInstance().getTextureLocation("buttonUL");
    texture[4] = GuiRender::getInstance().getTextureLocation("buttonUM");
    texture[5] = GuiRender::getInstance().getTextureLocation("buttonUR");
    texture[6] = GuiRender::getInstance().getTextureLocation("scrollUA");
    texture[7] = GuiRender::getInstance().getTextureLocation("scrollDA");
    texture[8] = GuiRender::getInstance().getTextureLocation("scrollB");
    texture[9] = GuiRender::getInstance().getTextureLocation("scrollP");
}

void Scrollbar::recalculatePosition(){
    //position
    float dy = ((float)(height - 42) / (max - min)) * (position-min);
    vertex[9].x1 = (float)width/2-5;
    vertex[9].y1 = dy+16;
    vertex[9].x2 = (float)width/2+5;
    vertex[9].y2 = dy+26;
}

void Scrollbar::onRender(){
    drawButton(0,upPressed,true);
    drawButton(4,downPressed,false);
    GuiRender::getInstance().drawImage(texture[8],vertex[8]); //body
    GuiRender::getInstance().nextLayer();
    GuiRender::getInstance().drawImage(texture[0],vertex[9]); //positon
}

void Scrollbar::drawButton(int verIndex, bool pressed,bool upArrow)
{
  GuiRender::getInstance().saveState();
  if (pressed)
  {
      GuiRender::getInstance().drawImage(texture[0],vertex[verIndex]); // left side
      GuiRender::getInstance().drawImage(texture[1],vertex[verIndex+1]); // middle
      GuiRender::getInstance().drawImage(texture[2],vertex[verIndex+2]); // right side
      GuiRender::getInstance().move(0,-1);
  }
  else
  {
      GuiRender::getInstance().drawImage(texture[3],vertex[verIndex]); // left side
      GuiRender::getInstance().drawImage(texture[4],vertex[verIndex+1]); // middle
      GuiRender::getInstance().drawImage(texture[5],vertex[verIndex+2]); // right side
  }

  GuiRender::getInstance().nextLayer();
  if(upArrow)
      GuiRender::getInstance().drawImage(texture[6],vertex[verIndex+3]);
  else
      GuiRender::getInstance().drawImage(texture[7],vertex[verIndex+3]);
  GuiRender::getInstance().restoreState();
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
        recalculatePosition();
        if(oldPos != position)
            PositionChanged(this,position);
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
                recalculatePosition();
                PositionChanged(this, position);
            }
            downPressed= false;
            break;
        case GLFW_KEY_UP:
            if(position - step >= min){
                position -= step;
                recalculatePosition();
                PositionChanged(this, position);
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
            recalculatePosition();
            PositionChanged(this, position);
        }
        upPressed= false;
    }
    if(downPressed){
        if(position + step <= max){
            position += step;
            recalculatePosition();
            PositionChanged(this, position);
        }
        downPressed= false;
    }
}
