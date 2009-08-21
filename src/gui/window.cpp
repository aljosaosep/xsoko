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

#include "window.h"

/*------------------------------------------------------------------*
 *  initialise window and setup defaults                            *
 *------------------------------------------------------------------*/
Window::Window(int x, int y, int width, int height,string wCaption) : Container(x,y,width,height), alpha(0.9f),
        enableCloseButton(true), modal(false), caption(wCaption), fnt(new Font("font"))
{
  mouseDrag.drag = false;
  mouseDrag.x = 0;
  mouseDrag.y = 0;
  invalidate();
};

Window::~Window(){
    delete fnt;
}

void Window::setModal(bool modal){
    this->modal = modal;
}

bool Window::isModal(){
    return modal;
}

Font* Window::getFont(){
    return fnt;
}

void Window::setCaption(string caption){
    this->caption = caption;
}

string Window::getCaption(){
    return caption;
}

void Window::invalidate(){
    // top left corner of window.
    vertex[0].x1 = 0;
    vertex[0].y1 = 0;
    vertex[0].x2 = 63;
    vertex[0].y2 = 27;

    // top of window.
    vertex[1].x1 = 63;
    vertex[1].y1 = 0;
    vertex[1].x2 = width-32;
    vertex[1].y2 = 27;

    // top right corder of window.
    vertex[2].x1 = width-32;
    vertex[2].y1 = 0;
    vertex[2].x2 = width;
    vertex[2].y2 = 27;

    // left side of window.
    vertex[3].x1 = 0;
    vertex[3].y1 = 27;
    vertex[3].x2 = 6;
    vertex[3].y2 = height-27;

    // draw the main body of the window
    vertex[4].x1 = 6;
    vertex[4].y1 = 27;
    vertex[4].x2 = width-7;
    vertex[4].y2 = height-25;

    // right side of window.
    vertex[5].x1 = width-7;
    vertex[5].y1 = 27;
    vertex[5].x2 = width;
    vertex[5].y2 = height-27;

    // bottom left corner of window.
    vertex[6].x1 = 0;
    vertex[6].y1 = height-27;
    vertex[6].x2 = 63;
    vertex[6].y2 = height;

    // bottom of window.
    vertex[7].x1 = 63;
    vertex[7].y1 = height-27;
    vertex[7].x2 = width-32;
    vertex[7].y2 = height;

    // bottom right corner of window.
    vertex[8].x1 = width-32;
    vertex[8].y1 = height-27;
    vertex[8].x2 = width;
    vertex[8].y2 = height;

    texture[0] = GuiRender::getInstance().getTextureLocation("windowTL");
    texture[1] = GuiRender::getInstance().getTextureLocation("windowT");
    texture[2] = GuiRender::getInstance().getTextureLocation("windowTR");
    texture[3] = GuiRender::getInstance().getTextureLocation("windowL");
    texture[4] = GuiRender::getInstance().getTextureLocation("windowM");
    texture[5] = GuiRender::getInstance().getTextureLocation("windowR");
    texture[6] = GuiRender::getInstance().getTextureLocation("windowBL");
    texture[7] = GuiRender::getInstance().getTextureLocation("windowB");
    texture[8] = GuiRender::getInstance().getTextureLocation("windowBR");
}

/*------------------------------------------------------------------*
 *  Render the window. Calls render button, child windows ...       *
 *------------------------------------------------------------------*/
void Window::onRender()
{
    GuiRender::getInstance().setColor(1,1,1,alpha);

      GuiRender::getInstance().drawImage(texture[0],vertex[0]); // top left corner of window.
      GuiRender::getInstance().drawImage(texture[1],vertex[1]); // top of window.
      GuiRender::getInstance().drawImage(texture[2],vertex[2]); // top right corder of window.
      GuiRender::getInstance().drawImage(texture[3],vertex[3]); // left side of window.
      GuiRender::getInstance().drawImage(texture[4],vertex[4]); // draw the main body of the window
      GuiRender::getInstance().drawImage(texture[5],vertex[5]); // right side of window.
      GuiRender::getInstance().drawImage(texture[6],vertex[6]); // bottom left corner of window.
      GuiRender::getInstance().drawImage(texture[7],vertex[7]); // bottom of window.
      GuiRender::getInstance().drawImage(texture[8],vertex[8]); // bottom right corner of window.

      //glBegin(GL_QUADS);
        /*if(enableCloseButton){
            // window close button
            glTexCoord2f((float)104/128, (float)96/128); glVertex3i(width-22, -8,  0.01);
            glTexCoord2f((float)104/128, (float)80/128); glVertex3i(width-22, -24, 0.01);
            glTexCoord2f((float)120/128, (float)80/128); glVertex3i(width-6, -24, 0.01);
            glTexCoord2f((float)120/128, (float)96/128); glVertex3i(width-6, -8,  0.01);
        }*/
      //glEnd();

      fnt->writeText((int)(width-fnt->stringWidth(caption))/2,24,caption);

      GuiRender::getInstance().nextLayer();
      //glEnable(GL_SCISSOR_TEST);
      //glScissor(x+6,screenHeight-y-height,width-12,height);
      for(unsigned i=0;i<components.size();i++){
        components[i]->Render();
      }
      //glDisable(GL_SCISSOR_TEST);
}

void Window::onMouseUp(int mx, int my){
    if(mouseDrag.drag){
        mouseDrag.drag = false;
        return;
    }
    Container::onMouseUp(mx,my);
}

void Window::onMouseMove(int mx, int my){
  if (mouseDrag.drag)
  {
    x += mx - mouseDrag.x;
    y += my - mouseDrag.y;
  }
}

void Window::onMouseDown(int mx, int my){
    if(!visible)
        return;

    /*if(enableCloseButton){
        // Test to see if user clicked on window close icon
        if ((mx > width-22) && (mx < width-6))
          if ((my - 26 > 8) && (my - 26 < 24)){
            setVisible(false);
            return;
          }
    }*/

    // Test to see if user clicked in caption bar
    if (my < 26) {
        mouseDrag.drag = true;
        mouseDrag.x    = mx;
        mouseDrag.y    = my;
        return;
    }

    Container::onMouseDown(mx,my);
}

float Window::getAlpha(){
    return alpha;
}

void Window::setAlpha(float alpha){
    this->alpha = (alpha < 1) ? alpha : 1;
    if(this->alpha < 0)
        alpha = 0;
}

void Window::setEnableCloseButton(bool enabled){
    enableCloseButton = enabled;
}

bool Window::isCloseButtonEnabled(){
    return enableCloseButton;
}

void Window::focusGain(){
    if(focusedComp != NULL)
        focusedComp->focusGain();
    Component::focusGain();
}

void Window::focusLost(){
    if(!focused) return;
    
    if(focusedComp != NULL)
        focusedComp->focusLost();
    Component::focusLost();
}
