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
#include "gui.h"

/*------------------------------------------------------------------*
 *  initialise window and setup defaults                            *
 *------------------------------------------------------------------*/
Window::Window(int wX, int wY, int wWidth, int wHeight,string caption) : Container(wX,wY,wWidth,wHeight)
{
  zorder = 0;         // used if you specifically want to set a window higher
  visible = true;     // start off visible
  alpha = 0.9f;        // defult for alpha bl}ing
  onScreenResize();
  enableCloseButton = true;
  mouseDrag.drag = false;
  mouseDrag.x = 0;
  mouseDrag.y = 0;
  modal = false;
  this->caption = caption;
  fnt = new Font("font");
};

Window::~Window(){
    delete fnt;
}

void Window::setVisible(bool visible){
    this->visible = visible;
    if(visible)
        focusGain();
    else
        focusLost();
    
}

void Window::setModal(bool modal){
    this->modal = modal;
}

Font* Window::getFont(){
    return fnt;
}

/*------------------------------------------------------------------*
 *  Render the window. Calls render button, child windows ...       *
 *------------------------------------------------------------------*/
void Window::Render()
{
  if (visible)
  {
    glBindTexture(GL_TEXTURE_2D, Gui::skinTextureID);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glColor4f(1.0, 1.0, 1.0, alpha);

    glPushMatrix();
      glTranslatef((float)x, (float)screenHeight - 26 -y , zorder);
      glBegin(GL_QUADS);
        // top left corner of window.
        glTexCoord2f( 0, 1);				glVertex2i(0, 0);
        glTexCoord2f( 0, 1-(float)27/128);		glVertex2i(0, -27);
        glTexCoord2f((float)64/128, 1-(float)27/128);	glVertex2i(63, -27);
        glTexCoord2f((float)64/128, 1);			glVertex2i(63, 0);

        // top of window.
        glTexCoord2f((float)64/128, 1);			glVertex2i(63, 0);
        glTexCoord2f((float)64/128, 1-(float)27/128);	glVertex2i(63, -27);
        glTexCoord2f((float)96/128, 1-(float)27/128);	glVertex2i(width-32, -27);
        glTexCoord2f((float)96/128, 1);			glVertex2i(width-32, 0);

        // top right corder of window.
        glTexCoord2f((float)96/128, 1);			glVertex2i(width-32, 0);
        glTexCoord2f((float)96/128, 1-(float)27/128);	glVertex2i(width-32, -27);
        glTexCoord2f(1, 1-(float)27/128);		glVertex2i(width, -27);
        glTexCoord2f(1, 1);				glVertex2i(width, 0);


        // left side of window.
        glTexCoord2f(0, 1-(float)27/128);		glVertex2i(0, -27);
        glTexCoord2f(0, (float)27/128);			glVertex2i(0, -height+27);
        glTexCoord2f((float)6/128, (float)27/128);	glVertex2i(6,-height+27);
        glTexCoord2f((float)6/128, 1-(float)27/128);	glVertex2i(6, -27);

        // draw the main body of the window
        glTexCoord2f((float) 9/128, (float)96/128);     glVertex2i(6, -27);
        glTexCoord2f((float) 9/128, (float)64/128);     glVertex2i(6, 25-height);
        glTexCoord2f((float)39/128, (float)64/128);     glVertex2i(width-7, 25-height);
        glTexCoord2f((float)39/128, (float)96/128);     glVertex2i(width-7, -27);

        // right side of window.
        glTexCoord2f(1-(float)7/128, 1-(float)27/128);	glVertex2i(width-7, -27);
        glTexCoord2f(1-(float)7/128, (float)27/128);	glVertex2i(width-7, -height+27);
        glTexCoord2f(1,   (float)27/128);		glVertex2i(width,-height+27);
        glTexCoord2f(1, 1-(float)27/128);		glVertex2i(width, -27);

        // bottom left corner of window.
        glTexCoord2f( 0, (float)27/128);		glVertex2i(0, 27-height);
        glTexCoord2f( 0,  0);				glVertex2i(0, -height);
        glTexCoord2f((float)64/128,  0);		glVertex2i(63, -height);
        glTexCoord2f((float)64/128, (float)27/128);	glVertex2i(63, 27-height);

        // bottom of window.
        glTexCoord2f((float)64/128, (float)27/128);	glVertex2i(63, 27-height);
        glTexCoord2f((float)64/128, 0);			glVertex2i(63, -height);
        glTexCoord2f((float)96/128, 0);			glVertex2i(width-32, -height);
        glTexCoord2f((float)96/128, (float)27/128);	glVertex2i(width-32, 27-height);

        // bottom right corder of window.
        glTexCoord2f((float)96/128, (float)27/128);	glVertex2i(width-32, 27-height);
        glTexCoord2f((float)96/128, 0);			glVertex2i(width-32, -height);
        glTexCoord2f(1, 0);				glVertex2i(width, -height);
        glTexCoord2f(1, (float)27/128);			glVertex2i(width, 27-height);

        /*if(enableCloseButton){
            // window close button
            glTexCoord2f((float)104/128, (float)96/128); glVertex3i(width-22, -8,  0.01);
            glTexCoord2f((float)104/128, (float)80/128); glVertex3i(width-22, -24, 0.01);
            glTexCoord2f((float)120/128, (float)80/128); glVertex3i(width-6, -24, 0.01);
            glTexCoord2f((float)120/128, (float)96/128); glVertex3i(width-6, -8,  0.01);
        }*/
      glEnd();

      fnt->writeText((int)(width-fnt->stringWidth(caption))/2,-24,caption);
      glBindTexture(GL_TEXTURE_2D, Gui::skinTextureID);

      glTranslatef(0, 0, 0.02f);
      //glEnable(GL_SCISSOR_TEST);
      //glScissor(x+6,screenHeight-y-height,width-12,height);
      for(unsigned i=0;i<components.size();i++){
        components[i]->Render();
      }
      //glDisable(GL_SCISSOR_TEST);

    glPopMatrix();
    glBlendFunc(GL_ONE,GL_ONE);
    glDisable(GL_BLEND);
  }
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
    if ((my - 26 > 1) && (my - 26 < 26))
      {
        mouseDrag.drag = true;
        mouseDrag.x    = mx;
        mouseDrag.y    = my;
        return;
      }

    Container::onMouseDown(mx,my-26);
}

float Window::getAlpha(){
    return alpha;
}

void Window::setAlpha(float alpha){
    this->alpha = (alpha < 1) ? alpha : 1;
    if(this->alpha < 0)
        alpha = 0;
}

float  Window::getZOrder(){
    return zorder;
}

void  Window::setZOrder(float zorder){
    this->zorder = zorder;
}

void Window::onScreenResize(){
    int temp;
    glfwGetWindowSize(&temp,&screenHeight);
}

void Window::setEnableCloseButton(bool enabled){
    enableCloseButton = enabled;
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
