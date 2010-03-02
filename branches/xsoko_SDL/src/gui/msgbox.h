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
 * File:   MsgBox.h
 * Author: jernej
 *
 * Created on Petek, 21 avgust 2009, 23:39
 */

#ifndef _MSGBOX_H
#define	_MSGBOX_H

#include "window.h"

class MsgBox {
private:
    MsgBox();
    MsgBox(const MsgBox&);
    MsgBox& operator=(const MsgBox&);
public:
    static const int MSG_BTN_OK = 1;
    static const int MSG_BTN_OK_CANCEL = 2;

    static Window* showMessage(Window* parent, string title, string message, int buttons);
    static Window* showMessage(Window* parent, string title, string message);
    static Window* showMessage(Window* parent, string message);
};

#endif	/* _MSGBOX_H */

