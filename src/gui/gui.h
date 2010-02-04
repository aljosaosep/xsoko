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

struct msgHandle {
    unsigned id;
    Window* ptr;
};

/**
 *singleton class
 */
class Gui {
private:
    int mouseX, mouseY;
    int wndWidth, wndHeight;
    
    vector<Window*> windows;
    vector<Component*> focusQueue;
    vector<Window*> modals;
    vector<msgHandle*> msgnum;

    bool mVisible;
    Font* fnt;
    unsigned num;
    Component* focusedWin;
    Rect mouseVer;

    Gui();
    ~Gui();
    void onMouseDown();
public:
    void onMouseClick(int button, int action);
    void onMouseMove(int x, int y);
    void onResolutionChange(int Width, int Height);
    void onKeyClick(int kkey, int action);
    void onCharacterSend(int c, int action);
    static Gui& getInstance();

    void Render();
    void setMouseVisible(bool visible);
    void addWindow(Window* win);
    Window* findWindowByName(string name);
    unsigned showMessage(string title, string msg);
    bool isMessageActive(unsigned id);
    void onAction(Component* button);
    void focusGain(Component* sender);
    void focusLost(Component* sender);
    //void registerInput();
    //void unregisterInput();
    //void addModal(Window* win);
    Font* getFont();
    int getXResolution();
    int getYResolution();

    //events
    signal<void(int,int) > ResolutionChange;
};

#endif	/* _WIN_H */

