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
#include <fstream>
#include "../zip/zipfile.h"

#if defined(Windows_Release) || defined(Windows_Debug)
    #define BOOST_WINDOWS_API
#endif
#include <boost/filesystem.hpp>

using namespace PacGame;
using namespace PacGame::GameClasses;
using namespace boost::filesystem;

MainMenu::MainMenu():Window(333, 183, 135, 235, "Main Menu"), freeplay(NULL),
        options(NULL), credits(NULL), gamepack(NULL)
{
    initializeComponents();
    setInCenter(true);
    setVisible(true);
    setName("mainMenu");

    options = new OptionsWnd(this);
    freeplay = new FreeplayWnd(this);
    gamepack = new GamePackWnd(this);
    credits = new CreditsWnd(this);
}

void MainMenu::initializeComponents(){
    btnCampaign = new Button(30, 10, 75, 25, "Campaing");
    btnCampaign->onPressed.connect(bind(&MainMenu::btnCampaignClick, this, _1));
    btnCampaign->setFocusable(1);
    addComponent(btnCampaign);

    btnFreeplay = new Button(30, 45, 75, 25, "Freeplay");
    btnFreeplay->onPressed.connect(bind(&MainMenu::btnFreeplayClick, this, _1));
    btnFreeplay->setFocusable(2);
    addComponent(btnFreeplay);

    btnOptions = new Button(30, 80, 75, 25, "Options");
    btnOptions->onPressed.connect(bind(&MainMenu::btnOptionsClick, this, _1));
    btnOptions->setFocusable(3);
    addComponent(btnOptions);

    btnCredits = new Button(30, 115, 75, 25, "Credits");
    btnCredits->onPressed.connect(bind(&MainMenu::btnCreditsClick, this, _1));
    btnCredits->setFocusable(4);
    addComponent(btnCredits);

    btnExit = new Button(30, 150, 75, 25, "Exit");
    btnExit->onPressed.connect(bind(&MainMenu::btnExitClick, this, _1));
    btnExit->setFocusable(5);
    addComponent(btnExit);
}

void MainMenu::btnCampaignClick(Component* sender){
    setVisible(false);
    gamepack->setVisible(true);
}

void MainMenu::btnFreeplayClick(Component* sender){
    setVisible(false);
    freeplay->setVisible(true);
}

void MainMenu::btnOptionsClick(Component* sender){
    setVisible(false);
    options->setVisible(true);
}

void MainMenu::btnCreditsClick(Component* sender){
    setVisible(false);
    credits->setVisible(true);
}

void MainMenu::btnExitClick(Component* sender){
    PGame::getInstance().quit();
}

OptionsWnd::OptionsWnd(Window* main) : Window(300,175,200,250,"Options"), mainMenu(main)
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
    addComponent(chkFullscreen);

    label1 = new Text(27,17,"Fullscreen");
    addComponent(label1);

    label2 = new Text(10,45,"Video modes:");
    addComponent(label2);

    lstModes = new ListBox(10,60,180,100);
    addComponent(lstModes);

    btnBack = new Button(25,170,50,25,"Back");
    btnBack->onPressed.connect(bind(&OptionsWnd::btnBackClick, this, _1));
    addComponent(btnBack);

    btnApply = new Button(100,170,50,25,"Apply");
    btnApply->onPressed.connect(bind(&OptionsWnd::btnApplyClick, this, _1));
    addComponent(btnApply);

    FocusGain.connect(bind(&OptionsWnd::wndVisible, this, _1));
}

void OptionsWnd::wndVisible(Component* sender)
{
    lstModes->setSelectedItem(new ResItem(Config::GetValueInt("xres"),Config::GetValueInt("yres")));
    chkFullscreen->setChecked(Config::GetValueBool("fullscreen"));
}

void OptionsWnd::btnApplyClick(Component* sender) {
    ResItem* newRes = (ResItem*) lstModes->getSelectedItem();
    PGame::getInstance().setResolution(newRes->resx,newRes->resy,chkFullscreen->isChecked());
}

void OptionsWnd::btnBackClick(Component* sender) {
    setVisible(false);
    mainMenu->setVisible(true);
}

CreditsWnd::CreditsWnd(Window* main) : Window(0,0,1,1,"Credits"), mainMenu(main)
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
    addComponent(label);

    int width = label->getSize().width;
    int height = label->getSize().height;
    btnOK = new Button(width/2,height+20,50,25,"OK");
    btnOK->onPressed.connect(bind(&CreditsWnd::btnOKClick, this, _1));
    addComponent(btnOK);
}

void CreditsWnd::btnOKClick(Component* sender){
    setVisible(false);
    mainMenu->setVisible(true);
}

GamePackWnd::GamePackWnd(Window* main) : Window(235, 200, 330, 200, "Campaign"), mainMenu(main)
{
    initializeComponents();
    setName("gamepack");
    setInCenter(true);

    path dir_path("data");
    if(exists(dir_path)){
        for (directory_iterator itr(dir_path), end;itr != end; ++itr )
        {
            if ( !is_directory(*itr) && extension(*itr) == ".pak" )
            {
                  string filename = itr->path().leaf();
                  lstLevels->addItem(new LevelItem(filename.substr(0,filename.find_last_of('.')), getAuthor("data/"+filename)));
            }
        }
        lstLevels->setSelectedItem((unsigned)0);
    } else {
        Messages::infoMessage("WARNING - Cannot find data directory!");
    }
}

string GamePackWnd::getAuthor(string filename) {
    zifstream file(filename,"info.txt");
    if(file.good()) {
        string author;
        getline(file,author);
        getline(file,author);
        if(!author.empty())
            return author;
    }
    return "Unknown";
}

void GamePackWnd::initializeComponents() {
    lstLevels = new ListBox(10,10,200,132);
    lstLevels->KeyUp.connect(bind(&GamePackWnd::lstLevelsKeyUp, this, _1, _2));
    lstLevels->onItemSelect.connect(bind(&GamePackWnd::lstLevelsItemSelect, this, _1, _2));
    lstLevels->setFocusable(1);
    addComponent(lstLevels);

    btnPlay = new Button(230,15,75,25,"Play");
    btnPlay->setFocusable(2);
    btnPlay->onPressed.connect(bind(&GamePackWnd::btnPlayClick, this, _1));
    addComponent(btnPlay);

    btnBack = new Button(230,45,75,25,"Back");
    btnBack->setFocusable(3);
    btnBack->onPressed.connect(bind(&GamePackWnd::btnBackClick, this, _1));
    addComponent(btnBack);

    lblAuthor = new Text(10,152,"Author: -");
    addComponent(lblAuthor);
}

void GamePackWnd::btnBackClick(Component* sender){
    setVisible(false);
    mainMenu->setVisible(true);
}

void GamePackWnd::btnPlayClick(Component* sender){
    setVisible(false);
    PGame::getInstance().loadGamePack("data/"+lstLevels->getSelectedItem()->toString()+".pak");
}

void GamePackWnd::lstLevelsItemSelect(Component* sender, Item* item){
    lblAuthor->setText("Author: " + ((LevelItem*)item)->getAuthor());
}

void GamePackWnd::lstLevelsKeyUp(Component* sender, int key){
    switch(key){
        case SDLK_RETURN:
            btnPlayClick(sender);
            break;
        case SDLK_ESCAPE:
            btnBackClick(sender);
            break;
    }
}

FreeplayWnd::FreeplayWnd(Window* main) : Window(235, 200, 330, 200, "Freeplay"), mainMenu(main)
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
                  lstLevels->addItem(new LevelItem(filename.substr(0,filename.find_last_of('.')), getAuthor("data/"+filename)));
            }
        }
        lstLevels->setSelectedItem((unsigned)0);
    } else {
        Messages::infoMessage("WARNING - Cannot find data directory!");
    }
}

string FreeplayWnd::getAuthor(string filename) {
    ifstream level(filename.c_str());
    if(level.good()) {
        int temp; string author;
        level >> temp;
        level >> temp;
        for(int i=0;i<temp*2+3;i++)
            getline(level,author);
        level >> temp;
        for(int i=0;i<temp+1;i++)
            getline(level,author);
        if(!level.eof()) {
            getline(level,author);
            if(!author.empty())
                return author;
        }
    }
    return "Unknown";
}

void FreeplayWnd::initializeComponents(){
    lstLevels = new ListBox(10,10,200,132);
    lstLevels->KeyUp.connect(bind(&FreeplayWnd::lstLevelsKeyUp, this, _1, _2));
    lstLevels->onItemSelect.connect(bind(&FreeplayWnd::lstLevelsItemSelect, this, _1, _2));
    lstLevels->setFocusable(1);
    addComponent(lstLevels);

    btnPlay = new Button(230,15,75,25,"Play");
    btnPlay->setFocusable(2);
    btnPlay->onPressed.connect(bind(&FreeplayWnd::btnPlayClick, this, _1));
    addComponent(btnPlay);

    btnBack = new Button(230,45,75,25,"Back");
    btnBack->setFocusable(3);
    btnBack->onPressed.connect(bind(&FreeplayWnd::btnBackClick, this, _1));
    addComponent(btnBack);

    lblAuthor = new Text(10,152,"Author: -");
    addComponent(lblAuthor);
}

void FreeplayWnd::btnBackClick(Component* sender){
    setVisible(false);
    mainMenu->setVisible(true);
}

void FreeplayWnd::btnPlayClick(Component* sender){
    setVisible(false);
    PGame::getInstance().loadLevel("data/"+lstLevels->getSelectedItem()->toString()+".lvl");
}

void FreeplayWnd::lstLevelsItemSelect(Component* sender, Item* item){
    lblAuthor->setText("Author: " + ((LevelItem*)item)->getAuthor());
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
    btnSave->setFocusable(1);
    //btnSave->onPressed.connect(bind(&PGameSession::onAction, this, _1));
    addComponent(btnSave);

    btnReset = new Button(30, 45, 75, 25, "Reset");
    btnReset->setFocusable(2);
    btnReset->onPressed.connect(bind(&GameMenu::btnResetClick, this, _1));
    addComponent(btnReset);

    btnExit = new Button(30, 80, 75, 25, "Exit");
    btnExit->setFocusable(3);
    btnExit->onPressed.connect(bind(&GameMenu::btnExitClick, this, _1));
    addComponent(btnExit);
}

void GameMenu::btnExitClick(Component* sender){
        GameClasses::PGame::getInstance().exitLevel();
}

void GameMenu::btnResetClick(Component* sender){
        GameClasses::PGame::getInstance().resetLevel();
}
