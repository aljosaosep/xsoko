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

#include <GL/glfw.h>


#include "gui.h"

Gui::~Gui(){
    glDeleteTextures(1,&skinTextureID);
    delete fnt;
    skinTextureID = 0;
}

Gui::Gui(/*const char* guiTextureFileName*/) : mVisible(true), num(0), focusedWin(NULL) {
      //glClearColor(0.0, 0.0, 0.0, 0.0); 	   // Black Background
      //glShadeModel(GL_SMOOTH);                 // Enables Smooth Color Shading
      glClearDepth(1.0);                       // Depth Buffer Setup
      glEnable(GL_DEPTH_TEST);                 // Enable Depth Buffer
      //glDepthFunc(GL_LESS);		           // The Type Of Depth Test To Do

      glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);   //Realy Nice perspective calculations

      //glEnable(GL_TEXTURE_2D);

    glGenTextures(1,&skinTextureID);
    glBindTexture(GL_TEXTURE_2D,skinTextureID);
    if(glfwLoadTexture2D("data/GUI.tga", GLFW_ORIGIN_UL_BIT)){
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
       glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    }

    fnt = new Font("font");

    glfwGetWindowSize(&wndWidth,&wndHeight);
}

/*------------------------------------------------------------------*
 *  Procedure to render the GUI                                     *
 *------------------------------------------------------------------*/
void Gui::Render()
{
    if(mVisible){
      if(!mprocessed){
          switch(mclick){
            case GLFW_PRESS:
                onMouseDown();
                break;
            case GLFW_RELEASE:
                for(unsigned i=0;i<windows.size();i++)
                    windows[i]->onMouseUp(mouseX,mouseY);
                break;
          }
          mprocessed = true;
      }
      if(moved){
          for(unsigned i=0;i<windows.size();i++){
              Position pos = windows[i]->getPosition();
              windows[i]->onMouseMove(mouseX-pos.x,mouseY-pos.y);
          }
          moved = false;
      }
    }

    if(!kprocessed){
        if(focusedWin != NULL){
            switch(kclick){
              case GLFW_PRESS:
                  focusedWin->onKeyDown(key);
                  break;
              case GLFW_RELEASE:
                  focusedWin->onKeyUp(key);
                  break;
            }
        }
        kprocessed = true;
    }

  glMatrixMode(GL_PROJECTION);  // Change Matrix Mode to Projection
  glLoadIdentity();             // Reset View
  glOrtho(0, wndWidth, 0, wndHeight, 0, 100);
  glMatrixMode(GL_MODELVIEW);   // Change Projection to Matrix Mode
  glLoadIdentity();
          
  glTranslatef(0, 0, -1);
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,skinTextureID);
  for(unsigned i=0;i<windows.size();i++)
          windows[i]->Render();

  if(mVisible){
      //draw the mouse
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glEnable(GL_TEXTURE_2D);
      glColor4f(1,1,1,1);
      glBegin(GL_QUADS);
        glTexCoord2f((float)41/128, (float)64/128); glVertex3i(mouseX,    wndHeight - mouseY, 1);
        glTexCoord2f((float)72/128, (float)64/128); glVertex3i(mouseX+32, wndHeight - mouseY, 1);
        glTexCoord2f((float)72/128, (float)32/128); glVertex3i(mouseX+32, wndHeight - mouseY-32, 1);
        glTexCoord2f((float)41/128, (float)32/128); glVertex3i(mouseX,    wndHeight - mouseY-32, 1);
      glEnd();
      glDisable(GL_BLEND);
  }
}

Font* Gui::getFont(){
    return fnt;
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
            if ((mouseY - 26 > winPos.y) && (mouseY - 26 < winPos.y + winSize.height))
                modals.back()->onMouseDown(mouseX, mouseY);
        return;
    }
  for(unsigned i=0;i<windows.size();i++){
      if(windows[i]->isVisible()){
          Position winPos = windows[i]->getPosition();
          Size winSize = windows[i]->getSize();
          if ((mouseX > winPos.x) && (mouseX < winPos.x + winSize.width))
              if ((mouseY - 26 > winPos.y) && (mouseY - 26 < winPos.y + winSize.height)){
                  if(focusedWin != NULL)
                      focusedWin->focusLost();
                  focusedWin = windows[i];
                  focusedWin->focusGain();
                  focusedWin->onMouseDown(mouseX-winPos.x, mouseY-winPos.y);
                  break;
              }
      }
  }
}

int Gui::mouseX = 0;
int Gui::mouseY = 0;
int Gui::wndWidth = 0;
int Gui::wndHeight = 0;
int Gui::mclick = GLFW_RELEASE;
int Gui::kclick = GLFW_RELEASE;
int Gui::key = 0;
bool Gui::mprocessed = true;
bool Gui::kprocessed = true;
bool Gui::sizeRefreshed = false;
bool Gui::moved = false;
GLuint Gui::skinTextureID = 0;

void Gui::setMouseVisible(bool visible){
    mVisible = visible;
}

void Gui::onMouseMove(int x, int y){
  mouseX = x > 0 ? x : 0;
  if(x > wndWidth)
      mouseX = wndWidth;
  mouseY = y > 0 ? y : 0;
  if(y>wndHeight)
      mouseY = wndHeight;
  moved = true;
}

void Gui::onMouseClick(int button, int action){
    mclick = action;
    mprocessed = false;
}

void Gui::onKeyClick(int kkey, int action){
    kclick = action;
    key = kkey;
    kprocessed = false;
}

Gui& Gui::getInstance(){
    static Gui gui;
    return gui;
}

/*{------------------------------------------------------------------}
{  Handle window resize                                            }
{------------------------------------------------------------------}*/
void Gui::glResizeWnd(int Width, int Height){
  if (Height == 0)               // prevent divide by zero exception
    Height = 1;
  glViewport(0, 0, Width, Height);    // Set the viewport for the OpenGL window
  glMatrixMode(GL_PROJECTION);        // Change Matrix Mode to Projection
  glLoadIdentity();                   // Reset View
  gluPerspective(45.0, Width/Height, 1.0, 100.0);  // Do the perspective calculations. Last value = max clipping depth
  wndWidth = Width;
  wndHeight = Height;
  sizeRefreshed = true;
  
  glMatrixMode(GL_MODELVIEW);         // Return to the modelview matrix
  glLoadIdentity();                   // Reset View
}

unsigned Gui::showMessage(string title, string msg){
    int width = (int)fnt->stringWidth(msg)+50;
    Window* dlg = new Window(wndWidth/2-width/2,wndHeight/2-64,width,100,title);
    dlg->AddComponent(new Text(25,35,msg));
    Button* btn = new Button(width/2-25,60,50,25,"OK");
    btn->setAction(this);
    dlg->AddComponent(btn);
    windows.push_back(dlg);
    //FIX: this...
    modals.push_back(dlg);
    if(!++num)  //ok, it could be if(num+1 == 0) num += 2 else ++num;
        ++num;
    msgHandle* hnd = new msgHandle;
    hnd->id = num;
    hnd->ptr = dlg;
    msgnum.push_back(hnd);
    return num;
}

void Gui::onAction(Component* button){
    Container* wnd = button->getParent();
    wnd->setVisible(false);
    for(unsigned i=0;i<modals.size();i++)
        if(modals[i] == wnd)
            modals.erase (modals.begin()+i);
    for(unsigned i=0;i<windows.size();i++)
        if(windows[i] == wnd){
            delete windows[i];
            windows.erase (windows.begin()+i);
        }
    for(unsigned i=0;i<msgnum.size();i++)
        if(msgnum[i]->ptr == wnd){
            delete msgnum[i];
            msgnum.erase(msgnum.begin()+i);
        }
}

bool Gui::isMessageActive(unsigned id){
    for(unsigned i=0;i<msgnum.size();i++){
        if(msgnum[i]->id == id)
            return true;
    }
    return false;
}

void Gui::addWindow(Window* win){
    win->setFocusHandler(this);
    windows.push_back(win);
    if(focusedWin == NULL){
        focusedWin = win;
        win->focusGain();
    }
}
    
void Gui::registerInput(){
    glfwSetMouseButtonCallback(Gui::onMouseClick);
    glfwSetMousePosCallback(Gui::onMouseMove);
    glfwSetKeyCallback(Gui::onKeyClick);
}

void Gui::unregisterInput(){
    glfwSetMouseButtonCallback(NULL);
    glfwSetMousePosCallback(NULL);
    glfwSetKeyCallback(NULL);
}

void Gui::focusGain(Window* sender){
    if(focusedWin == NULL){
        focusedWin = sender;
    }

    if(focusedWin != sender){
        focusQueue.push_back(focusedWin);
        focusedWin->focusLost();
        focusedWin = sender;
    }
}

void Gui::focusLost(Window* sender){
    if(!focusQueue.empty()){
        focusedWin = focusQueue.back();
        focusQueue.pop_back();
        focusedWin->focusGain();
    }
    /*if(windows.size()>1){
        for(unsigned i=0;i<windows.size();i++)
            if(windows[i] != sender){

            }
    }*/
}
