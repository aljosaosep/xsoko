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

#include "button.h"
#include "gui.h"

/*------------------------------------------------------------------*
 *  initialise a button                                             *
 *------------------------------------------------------------------*/
Button::Button(int x, int y, int width, int height, string caption) : Component(x,y,width,height)
{
  this->pressed = false;
  this->caption = caption;
  this->action = NULL;
  fnt = new Font("font");
}

Button::~Button(){
    delete fnt;
}


/*------------------------------------------------------------------*
 *  Render the button                                               *
 *------------------------------------------------------------------*/
void Button::Render()
{
  if(!visible)
      return;

  glColor3f(1,1,1);
  if (pressed)
  {
    glBegin(GL_QUADS);
      // left side
      glTexCoord2f((float)57/128, (float)95/128); glVertex2i(x, -y);
      glTexCoord2f((float)57/128, (float)70/128); glVertex2i(x, -y-height);
      glTexCoord2f((float)62/128, (float)70/128); glVertex2i(x+6,-y-height);
      glTexCoord2f((float)62/128, (float)95/128); glVertex2i(x+6, -y);

      // middle
      glTexCoord2f((float)62/128, (float)95/128); glVertex2i(x+6, -y);
      glTexCoord2f((float)62/128, (float)70/128); glVertex2i(x+6, -y-height);
      glTexCoord2f((float)66/128, (float)70/128); glVertex2i(x+width-6, -y-height);
      glTexCoord2f((float)66/128, (float)95/128); glVertex2i(x+width-6, -y);

      // right side
      glTexCoord2f((float)66/128, (float)95/128); glVertex2i(x+width-6, -y);
      glTexCoord2f((float)66/128, (float)70/128); glVertex2i(x+width-6, -y-height);
      glTexCoord2f((float)71/128, (float)70/128); glVertex2i(x+width, -y-height);
      glTexCoord2f((float)71/128, (float)95/128); glVertex2i(x+width, -y);
    glEnd();

    fnt->writeText(x+1+(int)(width - fnt->stringWidth(caption))/2, -y-21, caption);
  }
  else
  {
    glBegin(GL_QUADS);
      // left side
      glTexCoord2f((float)41/128, (float)95/128); glVertex2i(x, -y);
      glTexCoord2f((float)41/128, (float)70/128); glVertex2i(x, -y-height);
      glTexCoord2f((float)46/128, (float)70/128); glVertex2i(x+6,-y-height);
      glTexCoord2f((float)46/128, (float)95/128); glVertex2i(x+6, -y);

      // middle
      glTexCoord2f((float)46/128, (float)95/128); glVertex2i(x+6, -y);
      glTexCoord2f((float)46/128, (float)70/128); glVertex2i(x+6, -y-height);
      glTexCoord2f((float)50/128, (float)70/128); glVertex2i(x+width-6, -y-height);
      glTexCoord2f((float)50/128, (float)95/128); glVertex2i(x+width-6, -y);

      // right side
      glTexCoord2f((float)50/128, (float)95/128); glVertex2i(x+width-6, -y);
      glTexCoord2f((float)50/128, (float)70/128); glVertex2i(x+width-6, -y-height);
      glTexCoord2f((float)55/128, (float)70/128); glVertex2i(x+width, -y-height);
      glTexCoord2f((float)55/128, (float)95/128); glVertex2i(x+width, -y);
    glEnd();

    fnt->writeText(x + (int)(width-fnt->stringWidth(caption))/2, -y-20, caption);
  }
  glBindTexture(GL_TEXTURE_2D,Gui::skinTextureID);
  if(focused){
    glColor3f(1,0,0);
    glTranslatef(0,0, 0.02f);
    glBegin(GL_LINE_STRIP);
    glVertex2i(x+5,-y-5);
    glVertex2i(x+width-5,-y-5);
    glVertex2i(x+width-5,-y-height+5);
    glVertex2i(x+5,-y-height+5);
    glVertex2i(x+5,-y-5);
    glEnd();
  }
}

void Button::onMouseDown(int mx, int my){
    pressed = true;
}

void Button::onMouseUp(int mx, int my){
    pressed = false;
    if(action != NULL)
        action->onAction(this);
}

string Button::getCaption(){
    return caption;
}

void Button::setCaption(const string& caption){
    this->caption = caption;
}

void Button::setAction(ButtonClick* action){
    this->action = action;
}

Font* Button::getFont(){
    return fnt;
}

void Button::onKeyUp(int key){
    switch(key){
        case GLFW_KEY_ENTER:
            pressed = false;
            if(action != NULL)
                action->onAction(this);
            break;
        case GLFW_KEY_UP:
            parent->focusPrevious();
            break;
        case GLFW_KEY_DOWN:
        case GLFW_KEY_TAB:
            parent->focusNext();
            break;
    }
}

void Button::onKeyDown(int key){
    switch(key){
        case GLFW_KEY_ENTER:
            pressed = true;
            break;
    }
}
