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
 * File:   radiobutton.h
 * Author: jernej
 *
 * Created on Ponedeljek, 20 julij 2009, 23:39
 */

#ifndef _RADIOBUTTON_H
#define	_RADIOBUTTON_H

#include "component.h"

class RadioButtonGroup;

class RadioButton : public Component{
private:
    RadioButtonGroup* group;
    bool checked;

    //for rendering
    Rect ver;
protected:
    void onRender();
public:
    //constructors and destructor
    RadioButton(int x, int y,RadioButtonGroup* group,bool checked);

    //getters
    RadioButtonGroup* getRadioButtonGroup();
    bool isChecked();

    //setters
    void setChecked(bool checked);
    void setRadioButtonGroup(RadioButtonGroup* group);

    //events support
    void invalidate();
    void onMouseDown(int mx, int my);

    //events
    signal<void(Component*,bool) > onAction;
};

#endif	/* _RADIOBUTTON_H */

