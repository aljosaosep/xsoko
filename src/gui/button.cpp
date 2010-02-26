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

#include "button.h"
#include "container.h"

/*------------------------------------------------------------------*
 *  initialise a button                                             *
 *------------------------------------------------------------------*/
Button::Button(int x, int y, int width, int height, string bCaption) : Component(x,y,width,height), pressed(false),
        caption(bCaption)
{
  invalidate();
}

void Button::invalidate(){
    //left
    vertex[0].x1 = 0;
    vertex[0].y1 = 0;
    vertex[0].x2 = 6;
    vertex[0].y2 = height;

    //middle
    vertex[1].x1 = 6;
    vertex[1].y1 = 0;
    vertex[1].x2 = width-6;
    vertex[1].y2 = height;

    //right
    vertex[2].x1 = width-6;
    vertex[2].y1 = 0;
    vertex[2].x2 = width;
    vertex[2].y2 = height;

    //focus
    vertex[3].x1 = 3;
    vertex[3].y1 = 5;
    vertex[3].x2 = width-3;
    vertex[3].y2 = height-5;
}


/*------------------------------------------------------------------*
 *  Render the button                                               *
 *------------------------------------------------------------------*/
void Button::onRender()
{
  if (pressed)
  {
      renderer.drawImage(GUI_TEX_BTN_PRESSED_LEFT,  vertex[0]);
      renderer.drawImage(GUI_TEX_BTN_PRESSED_MIDDLE,vertex[1]);
      renderer.drawImage(GUI_TEX_BTN_PRESSED_RIGHT, vertex[2]);
      renderer.move(0,-1);
  }
  else
  {
      renderer.drawImage(GUI_TEX_BTN_UNPRESSED_LEFT,  vertex[0]);
      renderer.drawImage(GUI_TEX_BTN_UNPRESSED_MIDDLE,vertex[1]);
      renderer.drawImage(GUI_TEX_BTN_UNPRESSED_RIGHT, vertex[2]);
  }
  
  int deltay = (height - fnt->getSize())/2 + fnt->getSize();
  fnt->writeText((int)(width-fnt->stringWidth(caption))/2, deltay, caption);

  if(focused){
      renderer.setColor(0,0,0,1);
      renderer.drawRect(vertex[3], 1);
  }
}

void Button::onMouseDown(int mx, int my){
    pressed = true;
}

void Button::onMouseUp(int mx, int my){
    if(pressed) {
        pressed = false;
        onPressed(this);
    }
}

void Button::onMouseExit(){
    Component::onMouseExit();
    pressed = false;
}

string Button::getCaption(){
    return caption;
}

void Button::setCaption(const string& caption){
    this->caption = caption;
}

void Button::onKeyUp(int key){
    switch(key){
        case SDLK_RETURN:
            pressed = false;
            onPressed(this);
            break;
        case SDLK_UP:
            parent->focusPrevious();
            break;
        case SDLK_DOWN:
        case SDLK_TAB:
            parent->focusNext();
            break;
    }
}

void Button::onKeyDown(int key){
    switch(key){
        case SDLK_RETURN:
            pressed = true;
            break;
    }
}
