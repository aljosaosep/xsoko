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

#include "listbox.h"
#include "container.h"
#include "gui.h"

/*------------------------------------------------------------------*
 *  initialise a panel                                              *
 *------------------------------------------------------------------*/
ListBox::ListBox(int x, int y, int width, int height) : Component(x,y,width,height)
{
    selected = -1;
    action = NULL;
    upPressed = false;
    downPressed = false;
    drawIndex = 0;
    canShow = (height-4) / 16;
    fnt = new Font("font");
}

ListBox::~ListBox(){
    delete fnt;
    if(action != NULL)
        delete action;
}

void ListBox::setAction(ListBoxListener* action){
    this->action = action;
}

Font* ListBox::getFont(){
    return fnt;
}

/*------------------------------------------------------------------*
 *  Render the Panel                                                *
 *------------------------------------------------------------------*/
void ListBox::Render()
{
  if(visible)
  {
    glColor3f(1,1,1);
    glBegin(GL_QUADS);
      // top of panel.
      glTexCoord2f((float)10/128, (float)33/128); glVertex2i(x+2, -y);
      glTexCoord2f((float)10/128, (float)32/128); glVertex2i(x+2, -y-2);
      glTexCoord2f((float)37/128, (float)32/128); glVertex2i(x+2+(width-4), -y-2);
      glTexCoord2f((float)37/128, (float)33/128); glVertex2i(x+2+(width-4), -y);

      // left side of panel.
      glTexCoord2f((float)38/128, (float)61/128); glVertex2i(x, -y);
      glTexCoord2f((float)38/128, (float)34/128); glVertex2i(x, -y-height+2);
      glTexCoord2f((float)39/128, (float)34/128); glVertex2i(x+2, -y-height+2);
      glTexCoord2f((float)39/128, (float)61/128); glVertex2i(x+2, -y);

      // middle of panel.
      glTexCoord2f((float)18/128, (float)54/128); glVertex2i(x+2, -y-2);
      glTexCoord2f((float)18/128, (float)42/128); glVertex2i(x+2, -y-height+2);
      glTexCoord2f((float)30/128, (float)42/128); glVertex2i(x+2+(width-4), -y-height+2);
      glTexCoord2f((float)30/128, (float)54/128); glVertex2i(x+2+(width-4), -y-2);

      // right side of panel.
      glTexCoord2f((float) 8/128, (float)61/128); glVertex2i(x+width-2, -y);
      glTexCoord2f((float) 8/128, (float)34/128); glVertex2i(x+width-2, -y-height+2);
      glTexCoord2f((float) 9/128, (float)34/128); glVertex2i(x+width, -y-height+2);
      glTexCoord2f((float) 9/128, (float)61/128); glVertex2i(x+width, -y);

      // bottom middle of panel.
      glTexCoord2f((float)10/128, (float)62/128); glVertex2i(x+2, -y-height+2);
      glTexCoord2f((float)10/128, (float)63/128); glVertex2i(x+2, -y-height);
      glTexCoord2f((float)37/128, (float)63/128); glVertex2i(x+2+(width-2), -y-height);
      glTexCoord2f((float)37/128, (float)62/128); glVertex2i(x+2+(width-2), -y-height+2);

    glEnd();

    glTranslatef(0,0,0.02f);
    unsigned limit = (canShow<items.size()) ? canShow : items.size();
    for(unsigned i=0;i<limit;i++){
        if(selected == i+drawIndex)
            drawSelected(x+2,y+2+(i*16),width-20,items.at(i+drawIndex));
        else {
            fnt->writeText(x+5,-y-17-(i*16),items.at(i+drawIndex));
            glBindTexture(GL_TEXTURE_2D,Gui::skinTextureID);
        }
    }

    glColor3f(1,1,1);
    drawButton(x+width-18,y+2,upPressed,true);
    drawButton(x+width-18,y+height-18,downPressed,false);
    glColor3f(1,1,1);
    glBegin(GL_QUADS);
          glTexCoord2f((float) 8/128, (float)61/128); glVertex2i(x+width-10, -y-18);
          glTexCoord2f((float) 8/128, (float)34/128); glVertex2i(x+width-10, -y-height+18);
          glTexCoord2f((float) 9/128, (float)34/128); glVertex2i(x+width-9, -y-height+18);
          glTexCoord2f((float) 9/128, (float)61/128); glVertex2i(x+width-9, -y-18);
    glEnd();
    if(items.size() > canShow){
        float length = (float)(height - 46) / (items.size() - canShow);
        float dy = length * drawIndex;
        glTranslatef(0,0,0.02f);
        glBegin(GL_QUADS);
          glTexCoord2f((float)99/128, (float)61/128);	glVertex2f((float)x+width-14,-y-dy-18);
          glTexCoord2f((float)99/128, (float)53/128);	glVertex2f((float)x+width-14,-y-dy-28);
          glTexCoord2f((float)91/128, (float)53/128);	glVertex2f((float)x+width-4, -y-dy-28);
          glTexCoord2f((float)91/128, (float)61/128);	glVertex2f((float)x+width-4, -y-dy-18);
        glEnd();
    }
  }
}

void ListBox::onMouseDown(int mx, int my){
    if(!visible) return;

    if(mx >= 2 && mx <= width-18){
        unsigned index = (my-2) / 16 + drawIndex;
        if(index < items.size()){
            selected = index;
        }
    }
    if(mx >= width-18){
        if(my >= 2 && my <= 18){
            upPressed = true;
        }
        if(my >= height-18){
            downPressed = true;
        }
        if(my > 18 && my < height-18 && items.size() > canShow){
            int max = items.size() - canShow;
            drawIndex = (float)(max * (my - 23)) / (height - 46) + 0.5;
            if(drawIndex < 0)
                drawIndex = 0;
            if(drawIndex > max)
                drawIndex = max;
        }
    } else
        if(action != NULL){
            action->onAction(this,items.at(selected));
        }
}

void ListBox::onMouseUp(int mx, int my){
    if(!visible) return;

    if(upPressed){
        if(drawIndex > 0)
            drawIndex--;
        upPressed= false;
    }
    if(downPressed){
        if(drawIndex+canShow < items.size())
            drawIndex++;
        downPressed= false;
    }
}

string  ListBox::getSelectedItem(){
    return items.at(selected);
}

void ListBox::drawButton(int x, int y,bool pressed,bool upArrow)
{
  glPushMatrix();
  if (pressed)
  {
    glBegin(GL_QUADS);
      // left side
      glTexCoord2f((float)57/128, (float)95/128); glVertex2i(x, -y);
      glTexCoord2f((float)57/128, (float)70/128); glVertex2i(x, -y-16);
      glTexCoord2f((float)62/128, (float)70/128); glVertex2i(x+6,-y-16);
      glTexCoord2f((float)62/128, (float)95/128); glVertex2i(x+6, -y);

      // middle
      glTexCoord2f((float)62/128, (float)95/128); glVertex2i(x+6, -y);
      glTexCoord2f((float)62/128, (float)70/128); glVertex2i(x+6, -y-16);
      glTexCoord2f((float)66/128, (float)70/128); glVertex2i(x+10, -y-16);
      glTexCoord2f((float)66/128, (float)95/128); glVertex2i(x+10, -y);

      // right side
      glTexCoord2f((float)66/128, (float)95/128); glVertex2i(x+10, -y);
      glTexCoord2f((float)66/128, (float)70/128); glVertex2i(x+10, -y-16);
      glTexCoord2f((float)71/128, (float)70/128); glVertex2i(x+16, -y-16);
      glTexCoord2f((float)71/128, (float)95/128); glVertex2i(x+16, -y);
    glEnd();
    glTranslatef(1,0,0.2f);
  }
  else
  {
    glBegin(GL_QUADS);
      // left side
      glTexCoord2f((float)41/128, (float)95/128); glVertex2i(x, -y);
      glTexCoord2f((float)41/128, (float)70/128); glVertex2i(x, -y-16);
      glTexCoord2f((float)46/128, (float)70/128); glVertex2i(x+6,-y-16);
      glTexCoord2f((float)46/128, (float)95/128); glVertex2i(x+6, -y);

      // middle
      glTexCoord2f((float)46/128, (float)95/128); glVertex2i(x+6, -y);
      glTexCoord2f((float)46/128, (float)70/128); glVertex2i(x+6, -y-16);
      glTexCoord2f((float)50/128, (float)70/128); glVertex2i(x+10, -y-16);
      glTexCoord2f((float)50/128, (float)95/128); glVertex2i(x+10, -y);

      // right side
      glTexCoord2f((float)50/128, (float)95/128); glVertex2i(x+10, -y);
      glTexCoord2f((float)50/128, (float)70/128); glVertex2i(x+10, -y-16);
      glTexCoord2f((float)55/128, (float)70/128); glVertex2i(x+16, -y-16);
      glTexCoord2f((float)55/128, (float)95/128); glVertex2i(x+16, -y);
    glEnd();
    glTranslatef(0,0,0.2f);
  }
  if(upArrow){
    glBegin(GL_QUADS);
      glTexCoord2f((float)117/128, (float)63/128); glVertex2i(x, -y);
      glTexCoord2f((float)117/128, (float)50/128); glVertex2i(x, -y-16);
      glTexCoord2f((float)104/128, (float)50/128); glVertex2i(x+16,-y-16);
      glTexCoord2f((float)104/128, (float)63/128); glVertex2i(x+16, -y);
    glEnd();
  } else {
      glBegin(GL_QUADS);
        glTexCoord2f((float)104/128, (float)50/128); glVertex2i(x, -y);
        glTexCoord2f((float)104/128, (float)63/128); glVertex2i(x, -y-16);
        glTexCoord2f((float)117/128, (float)63/128); glVertex2i(x+16,-y-16);
        glTexCoord2f((float)117/128, (float)50/128); glVertex2i(x+16, -y);
      glEnd();
  }
  glPopMatrix();
}

void ListBox::drawSelected(int x, int y,int width,string item){
    glTranslatef(0,0,0.02f);
	glColor3f(1,1,1);
    glBegin(GL_QUADS);
      // top left corner of panel.
      glTexCoord2f((float) 8/128, (float)64/128); glVertex2i(x, -y);
      glTexCoord2f((float) 8/128, (float)54/128); glVertex2i(x, -y-10);
      glTexCoord2f((float)18/128, (float)54/128); glVertex2i(x+10, -y-10);
      glTexCoord2f((float)18/128, (float)64/128); glVertex2i(x+10, -y);

      // top of panel.
      glTexCoord2f((float)18/128, (float)64/128); glVertex2i(x+10, -y);
      glTexCoord2f((float)18/128, (float)54/128); glVertex2i(x+10, -y-10);
      glTexCoord2f((float)30/128, (float)54/128); glVertex2i(x+10+(width-20), -y-10);
      glTexCoord2f((float)30/128, (float)64/128); glVertex2i(x+10+(width-20), -y);

      // top right corder of panel.
      glTexCoord2f((float)30/128, (float)64/128); glVertex2i(x+width-10, -y);
      glTexCoord2f((float)30/128, (float)54/128); glVertex2i(x+width-10, -y-10);
      glTexCoord2f((float)40/128, (float)54/128); glVertex2i(x+width, -y-10);
      glTexCoord2f((float)40/128, (float)64/128); glVertex2i(x+width, -y);

      // left side of panel.
      glTexCoord2f((float) 8/128, (float)54/128); glVertex2i(x, -y-10);
      glTexCoord2f((float) 8/128, (float)42/128); glVertex2i(x, -y-16+10);
      glTexCoord2f((float)18/128, (float)42/128); glVertex2i(x+10, -y-16+10);
      glTexCoord2f((float)18/128, (float)54/128); glVertex2i(x+10, -y-10);

      // right side of panel.
      glTexCoord2f((float)30/128, (float)54/128); glVertex2i(x+width-10, -y-10);
      glTexCoord2f((float)30/128, (float)42/128); glVertex2i(x+width-10, -y-16+10);
      glTexCoord2f((float)40/128, (float)42/128); glVertex2i(x+width, -y-16+10);
      glTexCoord2f((float)40/128, (float)54/128); glVertex2i(x+width, -y-10);

      // bottom left corner of panel.
      glTexCoord2f((float) 8/128, (float)42/128); glVertex2i(x, -y-16+10);
      glTexCoord2f((float) 8/128, (float)32/128); glVertex2i(x, -y-16);
      glTexCoord2f((float)18/128, (float)32/128); glVertex2i(x+10, -y-16);
      glTexCoord2f((float)18/128, (float)42/128); glVertex2i(x+10, -y-16+10);

      // bottom middle of panel.
      glTexCoord2f((float)18/128, (float)42/128); glVertex2i(x+10, -y-16+10);
      glTexCoord2f((float)18/128, (float)32/128); glVertex2i(x+10, -y-16);
      glTexCoord2f((float)30/128, (float)32/128); glVertex2i(x+10+(width-20), -y-16);
      glTexCoord2f((float)30/128, (float)42/128); glVertex2i(x+10+(width-20), -y-16+10);

      // bottom right corner of panel.
      glTexCoord2f((float)30/128, (float)42/128); glVertex2i(x+width-10, -y-16+10);
      glTexCoord2f((float)30/128, (float)32/128); glVertex2i(x+width-10, -y-16);
      glTexCoord2f((float)40/128, (float)32/128); glVertex2i(x+width, -y-16);
      glTexCoord2f((float)40/128, (float)42/128); glVertex2i(x+width, -y-16+10);

    glEnd();

    fnt->writeText(x+4,-y-16,item);
    glBindTexture(GL_TEXTURE_2D,Gui::skinTextureID);
}

void ListBox::addItem(string item){
    items.push_back(item);
    if(items.size() == 1){
        selected = 0;
        if(this->action != NULL){
            action->onAction(this,item);
        }
    }
}

void ListBox::onKeyUp(int key){
    int size = items.size();
    switch(key){
        case GLFW_KEY_DOWN:
            if(selected == -1 && size > 0){
                selected = 0;
                drawIndex = 0;
                if(action != NULL)
                    action->onAction(this,items.front());
            }
            if(selected+1 < size){
                selected++;
                if(drawIndex + canShow <= selected)
                    drawIndex = selected - canShow + 1;
                if(action != NULL)
                    action->onAction(this,items[selected]);
            }
            break;
        case GLFW_KEY_UP:
            if(selected == -1 && size > 0){
                selected = size - 1;
                if(size > canShow)
                    drawIndex = size - canShow;
                if(action != NULL)
                    action->onAction(this,items.back());
            }
            if(selected-1 >= 0){
                selected--;
                if(drawIndex > selected)
                    drawIndex = selected;
                if(action != NULL)
                    action->onAction(this,items[selected]);
            }
            break;
        case GLFW_KEY_TAB:
            parent->focusNext();
            break;
    }
    if(action != NULL && key != GLFW_KEY_TAB)
        action->onKeyClick(this,key);
}

