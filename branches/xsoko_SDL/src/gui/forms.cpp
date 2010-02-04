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

#include "forms.h"
#include "../CommonStructures.h"
#include "../game.h"
#include "../messages.h"
#include "gui.h"
#include "../config.h"
#include "../game.h"

#if defined(Windows_Release) || defined(Windows_Debug)
    #define BOOST_WINDOWS_API
#endif
#include <boost/filesystem.hpp>

using namespace PacGame;
using namespace PacGame::GameClasses;
using namespace boost::filesystem;

MainMenu::MainMenu():Window(333, 183, 135, 235, "Main Menu"), freeplay(NULL), options(NULL), credits(NULL)
{
    initializeComponents();
    setInCenter(true);
    setVisible(true);
    setName("mainMenu");
}

void MainMenu::initializeComponents(){
    btnCampaign = new Button(30, 10, 75, 25, "Campaing");
    btnCampaign->onPressed.connect(bind(&MainMenu::btnCampaignClick, this, _1));
    btnCampaign->setFocusIndex(1);
    AddComponent(btnCampaign);

    btnFreeplay = new Button(30, 45, 75, 25, "Freeplay");
    btnFreeplay->onPressed.connect(bind(&MainMenu::btnFreeplayClick, this, _1));
    btnFreeplay->setFocusIndex(2);
    AddComponent(btnFreeplay);

    btnOptions = new Button(30, 80, 75, 25, "Options");
    btnOptions->onPressed.connect(bind(&MainMenu::btnOptionsClick, this, _1));
    btnOptions->setFocusIndex(3);
    AddComponent(btnOptions);

    btnCredits = new Button(30, 115, 75, 25, "Credits");
    btnCredits->onPressed.connect(bind(&MainMenu::btnCreditsClick, this, _1));
    btnCredits->setFocusIndex(4);
    AddComponent(btnCredits);

    btnExit = new Button(30, 150, 75, 25, "Exit");
    btnExit->onPressed.connect(bind(&MainMenu::btnExitClick, this, _1));
    btnExit->setFocusIndex(5);
    AddComponent(btnExit);
}

void MainMenu::btnCampaignClick(Component* sender){
    setVisible(false);
    PGame::getInstance().loadLevel("data/testlevel.lvl");
}

void MainMenu::btnFreeplayClick(Component* sender){
    if(freeplay == NULL){
        freeplay = Gui::getInstance().findWindowByName("freeplay");
        if(freeplay == NULL) return;
    }
    setVisible(false);
    freeplay->setVisible(true);
}

void MainMenu::btnOptionsClick(Component* sender){
    if(options == NULL){
        options = Gui::getInstance().findWindowByName("options");
        if(options == NULL) return;
    }
    setVisible(false);
    options->setVisible(true);
}

void MainMenu::btnCreditsClick(Component* sender){
    if(credits == NULL){
        credits = Gui::getInstance().findWindowByName("credits");
        if(credits == NULL) return;
    }
    setVisible(false);
    credits->setVisible(true);
}

void MainMenu::btnExitClick(Component* sender){
    PGame::getInstance().quit();
}

OptionsWnd::OptionsWnd() : Window(300,175,200,250,"Options"), mainMenu(NULL)
{
    initializeComponents();
    setName("options");
    setInCenter(true);
    SDL_Rect **modes = SDL_ListModes(NULL, SDL_FULLSCREEN|SDL_OPENGL);
    for(int i=0;modes[i];++i)
        lstModes->addItem(new ResItem(modes[i]->w,modes[i]->h));
}

void OptionsWnd::initializeComponents(){
    chkFullscreen = new CheckBox(10,15,false);
    AddComponent(chkFullscreen);

    label1 = new Text(27,17,"Fullscreen");
    AddComponent(label1);

    label2 = new Text(10,45,"Video modes:");
    AddComponent(label2);

    lstModes = new ListBox(10,60,180,100);
    AddComponent(lstModes);

    btnBack = new Button(25,170,50,25,"Back");
    btnBack->onPressed.connect(bind(&OptionsWnd::btnBackClick, this, _1));
    AddComponent(btnBack);

    btnApply = new Button(100,170,50,25,"Apply");
    btnApply->onPressed.connect(bind(&OptionsWnd::btnApplyClick, this, _1));
    AddComponent(btnApply);

    FocusGain.connect(bind(&OptionsWnd::wndVisible, this, _1));
}

void OptionsWnd::wndVisible(Component* sender)
{
    lstModes->setSelectedItem(new ResItem(Config::GetValueInt("xres"),Config::GetValueInt("yres")));
    chkFullscreen->setChecked(Config::GetValueBool("fullscreen"));
}

void OptionsWnd::btnApplyClick(Component* sender){
    ResItem* newRes = (ResItem*) lstModes->getSelectedItem();
    PGame::getInstance().setResolution(newRes->resx,newRes->resy,chkFullscreen->isChecked());
}

void OptionsWnd::btnBackClick(Component* sender){
    if(mainMenu == NULL){
        mainMenu = Gui::getInstance().findWindowByName("mainMenu");
        if(mainMenu == NULL) return;
    }
    setVisible(false);
    mainMenu->setVisible(true);
}

CreditsWnd::CreditsWnd():Window(0,0,1,1,"Credits"), mainMenu(NULL)
{
    intializeComponents();
    setName("credits");
    setInCenter(true);

    int width = label->getSize().width;
    int height = label->getSize().height;
    setPosition(400-width/2-25,300-height/2-45);
    setSize(width+50,height+90);
}

void CreditsWnd::intializeComponents(){
    label = new Text(25,10,"Programmers:\nAljosa Osep\nJernej Skrabec\nJernej Halozan\nMartin Savc\n\nLevel designers:\nCrtomir Osep\nNevena Sreckovic");
    AddComponent(label);

    int width = label->getSize().width;
    int height = label->getSize().height;
    btnOK = new Button(width/2,height+20,50,25,"OK");
    btnOK->onPressed.connect(bind(&CreditsWnd::btnOKClick, this, _1));
    AddComponent(btnOK);
}

void CreditsWnd::btnOKClick(Component* sender){
    if(mainMenu == NULL){
        mainMenu = Gui::getInstance().findWindowByName("mainMenu");
        if(mainMenu == NULL) return;
    }
    setVisible(false);
    mainMenu->setVisible(true);
}

FreeplayWnd::FreeplayWnd() : Window(235, 200, 330, 200, "Freeplay"), mainMenu(NULL)
{
    initializeComponents();
    setName("freeplay");
    setInCenter(true);

    path dir_path("data");
    if(exists(dir_path)){
        for (directory_iterator itr(dir_path), end;itr != end; ++itr )
        {
            if ( !is_directory(*itr) && extension(*itr) == ".lvl" )
            {
                  string filename = itr->path().leaf();
                  lstLevels->addItem(new LevelItem(filename.substr(0,filename.find_last_of('.'))));
            }
        }
    } else {
        Messages::infoMessage("WARNING - Cannot find data directory!");
    }
}

void FreeplayWnd::initializeComponents(){
    lstLevels = new ListBox(10,10,200,132);
    lstLevels->KeyUp.connect(bind(&FreeplayWnd::lstLevelsKeyUp, this, _1, _2));
    lstLevels->setFocusIndex(1);
    AddComponent(lstLevels);

    btnPlay = new Button(230,15,75,25,"Play");
    btnPlay->setFocusIndex(2);
    btnPlay->onPressed.connect(bind(&FreeplayWnd::btnPlayClick, this, _1));
    AddComponent(btnPlay);

    btnBack = new Button(230,45,75,25,"Back");
    btnBack->setFocusIndex(3);
    btnBack->onPressed.connect(bind(&FreeplayWnd::btnBackClick, this, _1));
    AddComponent(btnBack);
}

void FreeplayWnd::btnBackClick(Component* sender){
    if(mainMenu == NULL){
        mainMenu = Gui::getInstance().findWindowByName("mainMenu");
        if(mainMenu == NULL) return;
    }
    setVisible(false);
    mainMenu->setVisible(true);
}

void FreeplayWnd::btnPlayClick(Component* sender){
    setVisible(false);
    PGame::getInstance().loadLevel("data/"+lstLevels->getSelectedItem()->toString()+".lvl");
}

void FreeplayWnd::lstLevelsKeyUp(Component* sender, int key){
    switch(key){
        case SDLK_RETURN:
            btnPlayClick(sender);
            break;
        case SDLK_ESCAPE:
            btnBackClick(sender);
            break;
    }
}

GameMenu::GameMenu() : Window(253, 158, 135, 165, "Menu")
{
    initializeComponents();
    setName("gameMenu");
    setInCenter(true);
}

void GameMenu::initializeComponents(){
    btnSave = new Button(30, 10, 75, 25, "Save");
    btnSave->setFocusIndex(1);
    //btnSave->onPressed.connect(bind(&PGameSession::onAction, this, _1));
    AddComponent(btnSave);

    btnReset = new Button(30, 45, 75, 25, "Reset");
    btnReset->setFocusIndex(2);
    btnReset->onPressed.connect(bind(&GameMenu::btnResetClick, this, _1));
    AddComponent(btnReset);

    btnExit = new Button(30, 80, 75, 25, "Exit");
    btnExit->setFocusIndex(3);
    btnExit->onPressed.connect(bind(&GameMenu::btnExitClick, this, _1));
    AddComponent(btnExit);
}

void GameMenu::btnExitClick(Component* sender){
        GameClasses::PGame::getInstance().exitLevel();
}

void GameMenu::btnResetClick(Component* sender){
        GameClasses::PGame::getInstance().resetLevel();
}
