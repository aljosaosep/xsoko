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

#include "radiobutton.h"
#include "radiobuttongroup.h"

/*------------------------------------------------------------------*
 *  initialise a Radio Button                                       *
 *------------------------------------------------------------------*/
RadioButton::RadioButton(int x, int y,RadioButtonGroup* group,bool checked) : Component(x,y,16,16)
{
  this->group = group;
  group->addToGroup(this);
  setChecked(checked);
  action = NULL;
}

void RadioButton::setAction(RadioButtonClick* action){
    this->action = action;
}

/*------------------------------------------------------------------*
 *  Render Radio Button                                             *
 *------------------------------------------------------------------*/
void RadioButton::Render()
{
  if(visible)
  {
    glColor3f(1,1,1);
    if(checked)
    {
      glBegin(GL_QUADS);
        glTexCoord2f((float)88/128, (float)80/128);		glVertex2i(x, -y);
        glTexCoord2f((float)88/128, (float)64/128);		glVertex2i(x, -y-16);
        glTexCoord2f((float)104/128, (float)64/128);	glVertex2i(x+16,-y-16);
        glTexCoord2f((float)104/128, (float)80/128);	glVertex2i(x+16, -y);
      glEnd();
    }
    else
    {
      glBegin(GL_QUADS);
        glTexCoord2f((float)72/128, (float)80/128); glVertex2i(x, -y);
        glTexCoord2f((float)72/128, (float)64/128); glVertex2i(x, -y-16);
        glTexCoord2f((float)88/128, (float)64/128); glVertex2i(x+16,-y-16);
        glTexCoord2f((float)88/128, (float)80/128); glVertex2i(x+16, -y);
      glEnd();
    }
  }
}

void RadioButton::onMouseDown(int mx, int my){
    setChecked(true);
    if(action != NULL){
        action->onAction(this,true);
    }
}

bool RadioButton::isChecked(){
    return checked;
}

void RadioButton::setChecked(bool checked){
    if(checked && group != NULL){
        vector<RadioButton*>* radioButtons = group->getRadioButtons();
        for(unsigned i=0;i<radioButtons->size();i++) {
            radioButtons->at(i)->checked = false;
        }
    }
    this->checked = checked;
}

RadioButtonGroup* RadioButton::getRadioButtonGroup(){
    return group;
}

void RadioButton::setRadioButtonGroup(RadioButtonGroup* group){
    if(this->group != NULL){
        this->group->removeFromGroup(this);
    }
    this->group = group;
    group->addToGroup(this);
}

