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

#include "panel.h"

/*------------------------------------------------------------------*
 *  initialise a panel                                              *
 *------------------------------------------------------------------*/
Panel::Panel(int x, int y, int width, int height) : Container(x,y,width,height)
{
    invalidate();
}

void Panel::invalidate(){
    // top of panel.
    vertex[0].x1 = 2;
    vertex[0].y1 = 0;
    vertex[0].x2 = width-2;
    vertex[0].y2 = 2;

    // left side of panel.
    vertex[1].x1 = 0;
    vertex[1].y1 = 0;
    vertex[1].x2 = 2;
    vertex[1].y2 = height-2;

    // middle of panel.
    vertex[2].x1 = 2;
    vertex[2].y1 = 2;
    vertex[2].x2 = width-2;
    vertex[2].y2 = height-2;

    // right side of panel.
    vertex[3].x1 = width-2;
    vertex[3].y1 = 0;
    vertex[3].x2 = width;
    vertex[3].y2 = height-2;

    // bottom middle of panel.
    vertex[4].x1 = 2;
    vertex[4].y1 = height-2;
    vertex[4].x2 = width;
    vertex[4].y2 = height;
}


/*------------------------------------------------------------------*
 *  Render the Panel                                                *
 *------------------------------------------------------------------*/
//TODO: do we really need a panel?
void Panel::onRender()
{
    renderer.drawImage(GUI_TEX_PANEL_TOP,   vertex[0]);
    renderer.drawImage(GUI_TEX_PANEL_LEFT,  vertex[1]);
    renderer.drawImage(GUI_TEX_PANEL_MIDLLE,vertex[2]);
    renderer.drawImage(GUI_TEX_PANEL_RIGHT, vertex[3]);
    renderer.drawImage(GUI_TEX_PANEL_BOTTOM,vertex[4]);
    /*glBegin(GL_QUADS);
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
      glTexCoord2f((float) 8/128, (float)42/128); glVertex2i(x, -y-height+10);
      glTexCoord2f((float)18/128, (float)42/128); glVertex2i(x+10, -y-height+10);
      glTexCoord2f((float)18/128, (float)54/128); glVertex2i(x+10, -y-10);

      // middle of panel.
      glTexCoord2f((float)18/128, (float)54/128); glVertex2i(x+10, -y-10);
      glTexCoord2f((float)18/128, (float)42/128); glVertex2i(x+10, -y-height+10);
      glTexCoord2f((float)30/128, (float)42/128); glVertex2i(x+10+(width-20), -y-height+10);
      glTexCoord2f((float)30/128, (float)54/128); glVertex2i(x+10+(width-20), -y-10);

      // right side of panel.
      glTexCoord2f((float)30/128, (float)54/128); glVertex2i(x+width-10, -y-10);
      glTexCoord2f((float)30/128, (float)42/128); glVertex2i(x+width-10, -y-height+10);
      glTexCoord2f((float)40/128, (float)42/128); glVertex2i(x+width, -y-height+10);
      glTexCoord2f((float)40/128, (float)54/128); glVertex2i(x+width, -y-10);

      // bottom left corner of panel.
      glTexCoord2f((float) 8/128, (float)42/128); glVertex2i(x, -y-height+10);
      glTexCoord2f((float) 8/128, (float)32/128); glVertex2i(x, -y-height);
      glTexCoord2f((float)18/128, (float)32/128); glVertex2i(x+10, -y-height);
      glTexCoord2f((float)18/128, (float)42/128); glVertex2i(x+10, -y-height+10);

      // bottom middle of panel.
      glTexCoord2f((float)18/128, (float)42/128); glVertex2i(x+10, -y-height+10);
      glTexCoord2f((float)18/128, (float)32/128); glVertex2i(x+10, -y-height);
      glTexCoord2f((float)30/128, (float)32/128); glVertex2i(x+10+(width-20), -y-height);
      glTexCoord2f((float)30/128, (float)42/128); glVertex2i(x+10+(width-20), -y-height+10);

      // bottom right corner of panel.
      glTexCoord2f((float)30/128, (float)42/128); glVertex2i(x+width-10, -y-height+10);
      glTexCoord2f((float)30/128, (float)32/128); glVertex2i(x+width-10, -y-height);
      glTexCoord2f((float)40/128, (float)32/128); glVertex2i(x+width, -y-height);
      glTexCoord2f((float)40/128, (float)42/128); glVertex2i(x+width, -y-height+10);

    glEnd();*/

    for(unsigned i=0;i<components.size();i++){
        components[i]->Render();
      }
}

