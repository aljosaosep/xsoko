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
#include <algorithm>


#include <fstream>
#include <sstream>


#include <GL/gl.h>
#include <vector>

#include "guirender.h"

GuiRender& GuiRender::getInstance(){
    static GuiRender render;
    return render;
}

void GuiRender::loadSkin(unsigned skin, string skinFile){
    skinID = skin;
    ifstream file;
    file.open(skinFile.c_str(),ios::in);
    if(file.good()){
        string vrstica;
        while(!file.eof()){
            getline(file,vrstica);
            stringstream stream(vrstica);
            texInfo info;
            stream >> info.name >> info.location.x1 >> info.location.y1 >>
                    info.location.x2 >> info.location.y2;
            textureInfo.push_back(info);
        }
    }
    sort(textureInfo.begin(),textureInfo.end(),sortObj);
}

Rect GuiRender::getTextureLocation(string name){
    //int index = 0, i = 0, j=textureInfo.size();
    texInfo temp;
    Rect empty = {0,0,0,0};
    temp.name = name;
    int index = lower_bound(textureInfo.begin(),textureInfo.end(),temp) - textureInfo.begin();
    temp = textureInfo[index];
    if(name != temp.name)
        return empty;
    else
        return temp.location;
}

void GuiRender::drawImage(Rect textureRect, Rect drawRect){
    glBindTexture(GL_TEXTURE_2D,skinID);

    glColor4f(1,1,1,alpha);
    /*int vertex[] = {drawRect.x1, -drawRect.y1,
                    drawRect.x2, -drawRect.y1,
                    drawRect.x2, -drawRect.y2,
                    drawRect.x1, -drawRect.y2};
    float texture[] = {(float)textureRect.x1/128, (float)textureRect.y1/128,
                       (float)textureRect.x2/128, (float)textureRect.y1/128,
                       (float)textureRect.x2/128, (float)textureRect.y2/128,
                       (float)textureRect.x1/128, (float)textureRect.y2/128};
    glVertexPointer(2,GL_INT,0,vertex);
    glTexCoordPointer(2,GL_FLOAT,0,texture);
    glDrawArrays(GL_QUADS,0,4);*/
    glBegin(GL_QUADS);
      glTexCoord2f((float)textureRect.x1/128, (float)textureRect.y1/128); glVertex2i(x+drawRect.x1, y-drawRect.y1);
      glTexCoord2f((float)textureRect.x2/128, (float)textureRect.y1/128); glVertex2i(x+drawRect.x2, y-drawRect.y1);
      glTexCoord2f((float)textureRect.x2/128, (float)textureRect.y2/128); glVertex2i(x+drawRect.x2, y-drawRect.y2);
      glTexCoord2f((float)textureRect.x1/128, (float)textureRect.y2/128); glVertex2i(x+drawRect.x1, y-drawRect.y2);
    glEnd();
    glColor4f(r,g,b,alpha);
}

void GuiRender::drawFilledRect(Rect rectangle){
    glBegin(GL_QUADS);
      glVertex2i(x+rectangle.x1, y-rectangle.y1);
      glVertex2i(x+rectangle.x2, y-rectangle.y1);
      glVertex2i(x+rectangle.x2, y-rectangle.y2);
      glVertex2i(x+rectangle.x1, y-rectangle.y2);
    glEnd();
}

void GuiRender::drawRect(Rect rectangle, int width){
    glLineWidth(width);
    glBegin(GL_LINE_STRIP);
        glVertex2i(x+rectangle.x1, y-rectangle.y1);
        glVertex2i(x+rectangle.x2, y-rectangle.y1);
        glVertex2i(x+rectangle.x2, y-rectangle.y2);
        glVertex2i(x+rectangle.x1, y-rectangle.y2);
        glVertex2i(x+rectangle.x1, y-rectangle.y1);
    glEnd();
    /*int vertex[] = {rectangle.x1, -rectangle.y1,
                    rectangle.x2, -rectangle.y1,
                    rectangle.x2, -rectangle.y2,
                    rectangle.x1, -rectangle.y2};
    glVertexPointer(2,GL_INT,0,vertex);
    glDrawArrays(GL_QUADS,0,4);*/
}

void GuiRender::drawLine(int x1, int y1, int x2, int y2, int width){
    glLineWidth(width);
    glBegin(GL_LINE);
        glVertex2i(x+x1,y-y1);
        glVertex2i(x+x2,y-y2);
    glEnd();
}

void GuiRender::setColor(float r, float g, float b, float alpha){
    this->r = r;
    this->g = g;
    this->b = b;
    this->alpha = alpha;
    glColor4f(r,g,b,alpha);
}

void GuiRender::nextLayer(){
    z += 0.02f;
    glTranslatef(0,0,0.02f);
}

void GuiRender::mouseDepth(){
    z += 0.75f;
    glTranslatef(0,0,0.75f);
}

void GuiRender::move(float x, float y){
    this->x += x;
    this->y -= y;
}

void GuiRender::saveState(){
    State temp = {x,y,z};
    savedStates.push_back(temp);
}

void GuiRender::restoreState(){
    if(savedStates.empty()) return;

    State restored = savedStates.back();
    savedStates.pop_back();

    glTranslatef(0,0,restored.z - z);
    x = restored.x;
    y = restored.y;
    z = restored.z;
}

State GuiRender::getCurrentState(){
    State ret = {x,y,z};
    return ret;
}

void GuiRender::initRendering(){
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glPushClientAttrib(GL_ALL_CLIENT_ATTRIB_BITS);

  glMatrixMode(GL_PROJECTION);  // Change Matrix Mode to Projection
  glLoadIdentity();             // Reset View
  glOrtho(0, 800, 0, 600, 0, 100);
  glMatrixMode(GL_MODELVIEW);   // Change Projection to Matrix Mode
  glLoadIdentity();

  glTranslatef(0, 0, -1);
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_TEXTURE_2D);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
}

void GuiRender::deinitRendering(){
    glPopClientAttrib();
    glPopAttrib();
}

GuiRender::GuiRender() : r(0),g(0),b(0),alpha(1),x(0),y(600),z(0)
{
    /*glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);*/
}
