/*
 * codename: xSoko
 * Copyright (C) Aljosa Osep, Jernej Skrabec, Jernej Halozan 2008 <aljosa.osep@gmail.com, jernej.skrabec@gmail.com, jernej.halozan@gmail.com>
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
 * File:   forms.h
 * Author: jernej
 *
 * Created on Torek, 15 september 2009, 20:15
 */

#ifndef _FORMS_H
#define	_FORMS_H

#include "window.h"
#include "button.h"
#include "listbox.h"
#include "scrollbar.h"
#include "editbox.h"
#include "checkbox.h"
#include "text.h"
#include "../CommonStructures.h"

using namespace PacGame;

class MainMenu : public Window {
private:
    Button* btnCampaign;
    Button* btnFreeplay;
    Button* btnOptions;
    Button* btnCredits;
    Button* btnExit;

    //another windows
    Window* freeplay;
    Window* options;
    Window* credits;
private:
    void initializeComponents();
    void btnCampaignClick(Component* sender);
    void btnFreeplayClick(Component* sender);
    void btnOptionsClick(Component* sender);
    void btnCreditsClick(Component* sender);
    void btnExitClick(Component* sender);
public:
    MainMenu();
};

class FreeplayWnd: public Window {
private:
    class LevelItem : public Item {
    private:
        string _name;
    public:
        LevelItem(string name) : _name(name) {}
        string toString() {
            return _name;
        }
        bool equals(Item* item){
            LevelItem* x = (LevelItem*) item;
            return (x->_name == _name);
        }
    };
private:
    ListBox* lstLevels;
    Button* btnBack;
    Button* btnPlay;

    //main menu
    Window* mainMenu;
private:
    void initializeComponents();
    void btnBackClick(Component* sender);
    void btnPlayClick(Component* sender);
    void lstLevelsKeyUp(Component* sender, int key);
public:
    FreeplayWnd();
};

class OptionsWnd : public Window {
private:
    class ResItem : public Item {
    public:
        ResItem(int x, int y) : resx(x), resy(y) {}
        int resx, resy;
        string toString() {
            return Functions::toString(resx) + "x" + Functions::toString(resy);
        }
        bool equals(Item* item){
            ResItem *x = (ResItem*) item;
            return (item) ? (resx == x->resx && resy == x->resy) : false;
        }
    };

private:
    //components
    Button* btnApply;
    Button* btnBack;
    ListBox* lstModes;
    CheckBox* chkFullscreen;
    Text* label1;
    Text* label2;

    //main menu
    Window* mainMenu;
private:
    void initializeComponents();
    void btnApplyClick(Component* sender);
    void btnBackClick(Component* sender);
    void wndVisible(Component* sender);
public:
    OptionsWnd();
};

class CreditsWnd : public Window {
private:
    Text* label;
    Button* btnOK;

    //main menu
    Window* mainMenu;
private:
    void intializeComponents();
    void btnOKClick(Component* sender);
public:
    CreditsWnd();
};

class GameMenu : public Window {
private:
    Button* btnSave;
    Button* btnReset;
    Button* btnExit;
private:
    void initializeComponents();
    void btnResetClick(Component* sender);
    void btnExitClick(Component* sender);
public:
    GameMenu();
};

#endif	/* _FORMS_H */

