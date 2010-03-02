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

Gui::Gui() : mVisible(true), num(0), mouseFocusWin(NULL) {
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
  for(unsigned i=0;i<windows.size();i++)
      windows[i]->Render();

  // draw the mouse
  if(mVisible) {
      GuiRender::getInstance().setColor(1,1,1,1);
      GuiRender::getInstance().drawImage(GUI_TEX_MOUSE,mouseVer);
  }

  GuiRender::getInstance().deinitRendering();
}

inline bool Gui::pointOnComponent(int px, int py, Component* component) {
    Position winPos = component->getPosition();
    Size winSize = component->getSize();
    return ((px >= winPos.x) && (px <= winPos.x + winSize.width) &&
            (py >= winPos.y) && (py <= winPos.y + winSize.height) &&
            component->isVisible());
}

void Gui::setMouseVisible(bool visible){
    mVisible = visible;
}

void Gui::refreshMouseFocus() {
    vector<Window*>::reverse_iterator it;
    for(it = windows.rbegin(); it != windows.rend(); ++it)
        if(pointOnComponent(mouseX, mouseY, *it)) {
            if(mouseFocusWin != *it) {
                if(mouseFocusWin)
                    mouseFocusWin->onMouseExit();
                mouseFocusWin = *it;
                Position pos = (*it)->getPosition();
                mouseFocusWin->onMouseEnter(mouseX-pos.x,mouseY-pos.y);
            }
            return;
        }
    mouseFocusWin = NULL;
}

void Gui::onMouseMove(int x, int y){
    if(!mVisible) return;
    mouseX = x > 0 ? x : 0;
    if(x > wndWidth)
        mouseX = wndWidth;
    mouseY = y > 0 ? y : 0;
    if(y>wndHeight)
        mouseY = wndHeight;

    mouseVer.x1 = mouseX;
    mouseVer.y1 = mouseY;
    mouseVer.x2 = mouseX + 32;
    mouseVer.y2 = mouseY + 32;

    refreshMouseFocus();
    if(mouseFocusWin) {
        Position pos = mouseFocusWin->getPosition();
        mouseFocusWin->onMouseMove(mouseX-pos.x,mouseY-pos.y);
    }
}

void Gui::onMouseClick(int button, int action){
    if(mouseFocusWin && mVisible) {
        Position winPos = mouseFocusWin->getPosition();
        switch(action){
            case SDL_MOUSEBUTTONDOWN:
                if(mouseFocusWin != NULL && windows.back() != mouseFocusWin) {
                    Window* last = windows.back();
                    windows.erase(remove(windows.begin(),windows.end(),mouseFocusWin),windows.end());
                    windows.push_back((Window*)mouseFocusWin);
                    if(last != NULL)
                        last->focusLost();
                    windows.back()->focusGain();
                }
                if(windows.back() != NULL)
                    windows.back()->onMouseDown(mouseX-winPos.x, mouseY-winPos.y);
                break;
            case SDL_MOUSEBUTTONUP:
                mouseFocusWin->onMouseUp(mouseX-winPos.x, mouseY-winPos.y);
                break;
        }
    }
}

void Gui::onKeyClick(int kkey, int action){
    if(windows.back() != NULL && windows.back()->isVisible()) {
        switch(action){
          case SDL_KEYDOWN:
              windows.back()->onKeyDown(kkey);
              break;
          case SDL_KEYUP:
              windows.back()->onKeyUp(kkey);
              break;
        }
    }
}

void Gui::onCharacterSend(int c, int action){
    if(action == SDL_KEYUP && windows.back() != NULL && windows.back()->isVisible())
        windows.back()->onCharClick(c);
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
    dlg->addComponent(label);
    Button* btn = new Button(width/2,height + 30,50,25,"OK");
    btn->onPressed.connect(bind(&Gui::onAction, this, _1));
    dlg->addComponent(btn);


    //FIX: this...
    addWindow(dlg);
    //modals.push_back(dlg);
    /*if(mainFocusWin != NULL) {
        remove(windows.begin(),windows.end(), dlg); // move at the end
        mainFocusWin->focusLost();
        mainFocusWin = NULL;
    }*/

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
    //modals.erase(remove(modals.begin(), modals.end(), wnd), modals.end());

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
    win->FocusChange.connect(bind(&Gui::focusChanged,this,_1,_2));
    windows.insert(windows.begin(),win);
}

void Gui::removeWindow(Window* win) {
    windows.erase(remove(windows.begin(), windows.end(), win), windows.end());
    if(windows.back() != NULL && !windows.back()->isVisible())
        for(int i=windows.size()-2;i>=0;i--)
            if(windows[i]->isVisible()) {
                    Window* moved = windows[i];
                    windows.erase(remove(windows.begin(),windows.end(),windows[i]),windows.end());
                    windows.push_back(moved);
                    windows.back()->focusGain();
                    return;
                }
}
    
void Gui::focusChanged(Component* sender, bool focused) {
    if(focused) {
        if(windows.back() != sender) {
            Window* last = windows.back();
            windows.erase(remove(windows.begin(),windows.end(),sender),windows.end());
            windows.push_back((Window*)sender);
            if(last->isVisible())
                last->focusLost();
            refreshMouseFocus();
        }
    } else {
        if(windows.back() == sender) {
            for(int i=windows.size()-2;i>=0;i--)
                if(windows[i]->isVisible()) {
                        Window* moved = windows[i];
                        windows.erase(remove(windows.begin(),windows.end(),windows[i]),windows.end());
                        windows.push_back(moved);
                        windows.back()->focusGain();
                }
            refreshMouseFocus();
        }
    }
}

Gui::~Gui() {
    for(unsigned i=0;i<msgnum.size();i++) {
        delete msgnum[i].second;
    }
}
