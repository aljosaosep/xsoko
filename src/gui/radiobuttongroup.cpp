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

#include "radiobuttongroup.h"
#include "radiobutton.h"

void RadioButtonGroup::addToGroup(RadioButton* radioButton){
    radioButtons.push_back(radioButton);
}

void RadioButtonGroup::removeFromGroup(RadioButton* radioButton){
    for(unsigned i=0;i<radioButtons.size();i++) {
        if(radioButtons[i] == radioButton)
            radioButtons.erase(radioButtons.begin() + i);
    }
}

vector<RadioButton*>* RadioButtonGroup::getRadioButtons(){
    return &radioButtons;
}

