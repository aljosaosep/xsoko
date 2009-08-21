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
CheckBox::CheckBox(int x,int y,bool checked) : Component(x,y,16,16), checked(false)
{
    invalidate();
}

/*------------------------------------------------------------------*
 *  Render a Checkbox                                               *
 *------------------------------------------------------------------*/
void CheckBox::onRender()
{
    if (checked)
      GuiRender::getInstance().drawImage(texture[0],vertex);
    else
      GuiRender::getInstance().drawImage(texture[1],vertex);
}

void CheckBox::invalidate(){
    vertex.x1 = 0;
    vertex.y1 = 0;
    vertex.x2 = width;
    vertex.y2 = height;

    texture[0] = GuiRender::getInstance().getTextureLocation("checkboxC");
    texture[1] = GuiRender::getInstance().getTextureLocation("checkboxU");
}

void CheckBox::onMouseDown(int mx, int my){
    checked = !checked;
    onAction(this,checked);
}

bool CheckBox::isChecked(){
    return checked;
}

void CheckBox::setChecked(bool checked){
    this->checked = checked;
}

