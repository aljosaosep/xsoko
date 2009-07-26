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

#include "checkbox.h"

/*------------------------------------------------------------------*
 *  initialise a checkbox                                           *
 *------------------------------------------------------------------*/
CheckBox::CheckBox(int x,int y,bool checked) : Component(x,y,16,16)
{
  this->checked = false;
  action = NULL;
}

void CheckBox::setAction(CheckBoxClick* action){
    this->action = action;
}


/*------------------------------------------------------------------*
 *  Render a Checkbox                                               *
 *------------------------------------------------------------------*/
void CheckBox::Render()
{
  if(visible)
  {
    glColor3f(1,1,1);
    if (checked)
    {
      glBegin(GL_QUADS);
        glTexCoord2f((float)88/128, (float)96/128);		glVertex2i(x, -y);
        glTexCoord2f((float)88/128, (float)80/128);		glVertex2i(x, -y-16);
        glTexCoord2f((float)104/128, (float)80/128);	glVertex2i(x+16,-y-16);
        glTexCoord2f((float)104/128, (float)96/128);	glVertex2i(x+16, -y);
      glEnd();
    }
    else
    {
      glBegin(GL_QUADS);
        glTexCoord2f((float)72/128, (float)96/128); glVertex2i(x, -y);
        glTexCoord2f((float)72/128, (float)80/128); glVertex2i(x, -y-16);
        glTexCoord2f((float)88/128, (float)80/128); glVertex2i(x+16,-y-16);
        glTexCoord2f((float)88/128, (float)96/128); glVertex2i(x+16, -y);
      glEnd();
    }
  }
}

void CheckBox::onMouseDown(int mx, int my){
    checked = !checked;
    if(action != NULL)
        action->onAction(this,checked);
}

bool CheckBox::isChecked(){
    return checked;
}

void CheckBox::setChecked(bool checked){
    this->checked = checked;
}

