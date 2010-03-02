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

#include "msgbox.h"
#include "button.h"
#include "text.h"
#include "gui.h"
#include "../messages.h"

Window* MsgBox::showMessage(Window* parent, string title, string message, int buttons) {
    Text* label = new Text(25,15,message);
    int width = label->getSize().width;
    int height = label->getSize().height;
    int wndWidth = Gui::getInst().getXResolution();
    int wndHeight = Gui::getInst().getYResolution();

    Window* dlg = new Window(wndWidth/2-width/2,wndHeight/2-64,width+50,height+90,title);
    dlg->addComponent(label);
    Button* btn;
    switch(buttons) {
        case MSG_BTN_OK:
            btn = new Button(width/2,height + 30,50,25,"Ok");
            //btn->onPressed.connect(bind(&Gui::onAction, this, _1));
            dlg->addComponent(btn);
            break;
        case MSG_BTN_OK_CANCEL:
            btn = new Button(width/2-30,height + 30,50,25,"Ok");
            //btn->onPressed.connect(bind(&Gui::onAction, this, _1));
            dlg->addComponent(btn);
            btn = new Button(width/2+30,height + 30,50,25,"Cancel");
            //btn->onPressed.connect(bind(&Gui::onAction, this, _1));
            dlg->addComponent(btn);
            break;
        default:
            return NULL;
    }

    if(parent) {
       dlg->setModal(true);
       dlg->setParent(parent);
    }

    return dlg;
}

Window* MsgBox::showMessage(Window* parent, string title, string message) {
    showMessage(parent, title, message, MSG_BTN_OK);
}

Window* MsgBox::showMessage(Window* parent, string message) {
    showMessage(parent,"xSoko", message, MSG_BTN_OK);
}
