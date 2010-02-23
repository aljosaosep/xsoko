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

#include <vector>
#include <algorithm>
#include "gui.h"
#include "guirender.h"

Gui::Gui() : mVisible(true), num(0), focusedWin(NULL) {
    GuiRender::getInstance().loadSkin("data/GUI.tga", "data/skin.position");
    
    SDL_GetMouseState(&mouseX, &mouseY);
    mouseVer.x1 = mouseX;
    mouseVer.y1 = mouseY;
    mouseVer.x2 = mouseX + 32;
    mouseVer.y2 = mouseY + 32;

    const SDL_VideoInfo* window_info = SDL_GetVideoInfo();
    GuiRender::getInstance().setWindowSize(window_info->current_w, window_info->current_h);
}

/*------------------------------------------------------------------*
 *  Procedure to render the GUI                                     *
 *------------------------------------------------------------------*/
void Gui::Render()
{
  GuiRender::getInstance().initRendering();

  vector<Window*>::const_iterator it;
  for(it = windows.begin(); it != windows.end(); ++it)
      (*it)->Render();

  // draw the mouse
  if(mVisible) {
      GuiRender::getInstance().setColor(1,1,1,1);
      GuiRender::getInstance().drawImage(GUI_TEX_MOUSE,mouseVer);
  }

  GuiRender::getInstance().deinitRendering();
}

/*------------------------------------------------------------------*
 *  Procedure to check if the user clicked in a window or object    *
 *------------------------------------------------------------------*/
void Gui::onMouseDown()
{
  // test to see if user clicked in a window
    if(!modals.empty()){
        Position winPos = modals.back()->getPosition();
        Size winSize = modals.back()->getSize();
        if ((mouseX > winPos.x) && (mouseX < winPos.x + winSize.width))
            if ((mouseY > winPos.y) && (mouseY < winPos.y + winSize.height))
                modals.back()->onMouseDown(mouseX-winPos.x, mouseY-winPos.y);
        return;
    }
  vector<Window*>::const_iterator it;
  for(it = windows.begin(); it != windows.end(); ++it) {
      if((*it)->isVisible()){
          Position winPos = (*it)->getPosition();
          Size winSize = (*it)->getSize();
          if ((mouseX > winPos.x) && (mouseX < winPos.x + winSize.width) &&
              (mouseY > winPos.y) && (mouseY < winPos.y + winSize.height)) {
                  if(focusedWin != (*it))
                  {
                      if(focusedWin != NULL)
                          focusedWin->focusLost();
                      focusedWin = (*it);
                      focusedWin->focusGain();
                  }
                  focusedWin->onMouseDown(mouseX-winPos.x, mouseY-winPos.y);
                  break;
              }
      }
  }
}

void Gui::setMouseVisible(bool visible){
    mVisible = visible;
}

void Gui::onMouseMove(int x, int y){
    if(!mVisible) return;
    mouseX = x > 0 ? x : 0;
    if(x > wndWidth)
        mouseX = wndWidth;
    mouseY = y > 0 ? y : 0;
    if(y>wndHeight)
        mouseY = wndHeight;

    vector<Window*>::const_iterator it;
    for(it = windows.begin(); it != windows.end(); ++it)
    {
        Position pos = (*it)->getPosition();
        (*it)->onMouseMove(mouseX-pos.x,mouseY-pos.y);
    }
    mouseVer.x1 = mouseX;
    mouseVer.y1 = mouseY;
    mouseVer.x2 = mouseX + 32;
    mouseVer.y2 = mouseY + 32;
}

void Gui::onMouseClick(int button, int action){
    if(!mVisible) return;
    switch(action){
        case SDL_MOUSEBUTTONDOWN:
            onMouseDown();
            break;
        case SDL_MOUSEBUTTONUP:
            vector<Window*>::const_iterator it;
            for(it = windows.begin(); it != windows.end(); ++it)
                (*it)->onMouseUp(mouseX,mouseY);
            break;
    }
}

void Gui::onKeyClick(int kkey, int action){
    if(focusedWin != NULL && focusedWin->isVisible()){
        switch(action){
          case SDL_KEYDOWN:
              focusedWin->onKeyDown(kkey);
              break;
          case SDL_KEYUP:
              focusedWin->onKeyUp(kkey);
              break;
        }
    }
}

void Gui::onCharacterSend(int c, int action){
    if(action == SDL_KEYUP && focusedWin != NULL)
        focusedWin->onCharClick(c);
}

Gui& Gui::getInst(){
    static Gui gui;
    return gui;
}

void Gui::onResolutionChange(int Width, int Height){
  wndWidth = Width;
  wndHeight = Height;
  GuiRender::getInstance().setWindowSize(Width,Height);
  ResolutionChange(Width,Height);
}

int Gui::getXResolution() const
{
    return wndWidth;
}

int Gui::getYResolution() const
{
    return wndHeight;
}

unsigned Gui::showMessage(string title, string msg){
    Text* label = new Text(25,15,msg);
    int width = label->getSize().width;
    int height = label->getSize().height;
    Window* dlg = new Window(wndWidth/2-width/2,wndHeight/2-64,width+50,height+90,title);
    dlg->AddComponent(label);
    Button* btn = new Button(width/2,height + 30,50,25,"OK");
    btn->onPressed.connect(bind(&Gui::onAction, this, _1));
    dlg->AddComponent(btn);


    //FIX: this...
    modals.push_back(dlg);
    if(focusedWin != NULL) {
        focusQueue.push_back(focusedWin);
        focusedWin->focusLost();
        focusedWin = NULL;
    }

    addWindow(dlg);
    dlg->setVisible(true);
    if(!++num)  //ok, it could be if(num+1 == 0) num += 2 else ++num;
        ++num;
    msgnum.push_back(make_pair(num,dlg));
    return num;
}

void Gui::onAction(Component* button){
    Container* wnd = button->getParent();
    wnd->setVisible(false);

    // we cannot delete window and then continue to handle events...
    modals.erase(remove(modals.begin(), modals.end(), wnd), modals.end());

    /*for(unsigned i=0;i<windows.size();i++)
        if(windows[i] == wnd){
            delete windows[i];
            windows.erase (windows.begin()+i);
        }
    for(unsigned i=0;i<msgnum.size();i++)
        if(msgnum[i]->ptr == wnd){
            delete msgnum[i];
            msgnum.erase(msgnum.begin()+i);
        }*/
    for(unsigned i=0;i<msgnum.size();i++)
        if(msgnum[i].second == wnd) {
            msgnum[i].first = 0;
            break;
        }
}

bool Gui::isMessageActive(unsigned id){
    for(unsigned i=0;i<msgnum.size();i++)
        if(msgnum[i].first == id)
            return true;
    return false;
}

void Gui::addWindow(Window* win){
    win->FocusGain.connect(bind(&Gui::focusGain,this,_1));
    win->FocusLost.connect(bind(&Gui::focusLost,this,_1));
    windows.push_back(win);
    if(focusedWin == NULL){
        focusedWin = win;
        win->focusGain();
    }
}

void Gui::removeWindow(Window* win) {
    windows.erase(remove(windows.begin(), windows.end(), win), windows.end());
    if(focusedWin == win && windows.size())
        if(focusQueue.size()) {
            focusedWin = focusQueue.back();
            focusQueue.pop_back();
        } else {
            vector<Window*>::const_iterator it;
            for(it = windows.begin(); it != windows.end(); ++it)
                if((*it)->isVisible()) {
                    focusedWin = *it;
                    focusedWin->focusGain();
                    break;
                }
        }
    else
        focusedWin = NULL;
}
    
void Gui::focusGain(Component* sender){
    if(focusedWin == NULL)
        focusedWin = sender;
    if(focusedWin != sender){
        focusQueue.push_back(focusedWin);
        focusedWin->focusLost();
        focusedWin = sender;
    }
}

void Gui::focusLost(Component* sender) {
    focusedWin = NULL;
    if(!focusQueue.empty()){
        focusedWin = focusQueue.back();
        focusQueue.pop_back();
        focusedWin->focusGain();
    }
}

/*Window* Gui::findWindowByName(string name) {
    vector<Window*>::const_iterator it;
    for(it = windows.begin(); it != windows.end(); ++it)
        if((*it)->getName() == name)
            return *it;
    return NULL;
}*/

Gui::~Gui() {
    for(unsigned i=0;i<msgnum.size();i++) {
        delete msgnum[i].second;
    }
}
