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
 * File:   win.h
 * Author: jernej
 * Based on delphi tutorial glWindows by Jan Horn
 *
 * Created on Nedelja, 28 september 2008, 10:49
 */

#ifndef _GUI_H
#define	_GUI_H

#include "window.h"
#include "button.h"
#include "text.h"

/**
 *singleton class
 */
class Gui {
private:
    int mouseX, mouseY;
    int wndWidth, wndHeight;
    
    vector<Window*> windows;
    //vector<Window*> modals;
    vector<pair<unsigned,Window*> > msgnum;

    bool mVisible;
    unsigned num;
    Component* mouseFocusWin;
    Rect mouseVer;
private:
    Gui();
    Gui(const Gui&);
    ~Gui();
    Gui& operator= (const Gui&);


    void onAction(Component* button);
    void focusChanged(Component* sender, bool focused);
    bool pointOnComponent(int px, int py, Component* component);
    void refreshMouseFocus();
public:
    void onMouseClick(int button, int action);
    void onMouseMove(int x, int y);
    void onResolutionChange(int Width, int Height);
    void onKeyClick(int kkey, int action);
    void onCharacterSend(int c, int action);
    static Gui& getInst();

    void Render();
    void setMouseVisible(bool visible);
    void addWindow(Window* win);
    void removeWindow(Window* win);
    unsigned showMessage(string title, string msg);
    bool isMessageActive(unsigned id);
    int getXResolution() const;
    int getYResolution() const;

    //events
    signal<void(int,int) > ResolutionChange;
};

#endif	/* _WIN_H */

