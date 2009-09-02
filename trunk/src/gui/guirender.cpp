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
#include <fstream>
#include <sstream>

#include "guirender.h"

GuiRender& GuiRender::getInstance(){
    static GuiRender render;
    return render;
}

void GuiRender::loadSkin(string skinImage, string skinFile){
    
	glGenTextures(1,&skinID);
    glBindTexture(GL_TEXTURE_2D,skinID);
	if(glfwLoadTexture2D(skinImage.c_str(), GLFW_ORIGIN_UL_BIT)){
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
       glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    }

    ifstream file;
    file.open(skinFile.c_str(),ios::in);
    if(file.good()){
        string vrstica,name;
        for(int count=0;!file.eof();count++){
            getline(file,vrstica);
            stringstream stream(vrstica);
			stream >> name >> textures[count][0] >> textures[count][1] >>
                    textures[count][4] >> textures[count][5];
			textures[count][6] = textures[count][0] /= 128;
			textures[count][3] = textures[count][1] /= 128;
			textures[count][2] = textures[count][4] /= 128;
			textures[count][7] = textures[count][5] /= 128;
        }
    }
}

void GuiRender::drawImage(int index, Rect drawRect){
    glBindTexture(GL_TEXTURE_2D,skinID);

    glColor4f(1,1,1,alpha);
    int vertex[] = {x+drawRect.x1, y-drawRect.y1,
                    x+drawRect.x2, y-drawRect.y1,
                    x+drawRect.x2, y-drawRect.y2,
                    x+drawRect.x1, y-drawRect.y2};
    glVertexPointer(2,GL_INT,0,vertex);
    glTexCoordPointer(2,GL_FLOAT,0,textures[index]);
    glDrawArrays(GL_QUADS,0,4);
    glColor4f(r,g,b,alpha);
}

void GuiRender::setClipping(int x1, int y1, int x2, int y2){
	Rect clip = {x+x1,y-y1,x+x2,y-y2};
	if(!clippingPlace.empty()){
		Rect oldClip = clippingPlace.back();
		if(!(clip.x1 > oldClip.x2 || clip.x2 < oldClip.x1 ||
			 clip.y1 < oldClip.y2 || clip.y2 > oldClip.y1))
		{
			clip.x1 = max(clip.x1, oldClip.x1);
			clip.y1 = max(clip.y1, oldClip.y1);
			clip.x2 = min(clip.x2, oldClip.x2);
			clip.y2 = min(clip.y2, oldClip.y2);
		} else {
			clip.x1 = clip.x2 = clip.y1 = clip.y2 = 0;
		}
	} else {
		glEnable(GL_SCISSOR_TEST);
	}
	glScissor(clip.x1,clip.y2,clip.x2-clip.x1,clip.y1-clip.y2);
	clippingPlace.push_back(clip);
}
	
void GuiRender::restoreClipping(){
	if(!clippingPlace.empty()){
		clippingPlace.pop_back();
		if(!clippingPlace.empty()){
			Rect restore = clippingPlace.back();
			glScissor(restore.x1,restore.y2,restore.x2-restore.x1,restore.y1-restore.y2);
		} else {
			glDisable(GL_SCISSOR_TEST);
		}
	}
}

void GuiRender::drawFilledRect(int x1, int y1, int x2, int y2){
	glDisable(GL_TEXTURE_2D);
	int vertex[] = {x+x1, y-y1, x+x2, y-y1,
					x+x2, y-y2, x+x1, y-y2};
    glVertexPointer(2,GL_INT,0,vertex);
    glDrawArrays(GL_QUADS,0,4);
	glEnable(GL_TEXTURE_2D);
}

void GuiRender::drawRect(Rect rectangle, int width){
    glLineWidth(width);
	glDisable(GL_TEXTURE_2D);
    glBegin(GL_LINE_STRIP);
        glVertex2i(x+rectangle.x1, y-rectangle.y1);
        glVertex2i(x+rectangle.x2, y-rectangle.y1);
        glVertex2i(x+rectangle.x2, y-rectangle.y2);
        glVertex2i(x+rectangle.x1, y-rectangle.y2);
        glVertex2i(x+rectangle.x1, y-rectangle.y1);
    glEnd();
	glEnable(GL_TEXTURE_2D);
    /*int vertex[] = {rectangle.x1, -rectangle.y1,
                    rectangle.x2, -rectangle.y1,
                    rectangle.x2, -rectangle.y2,
                    rectangle.x1, -rectangle.y2};
    glVertexPointer(2,GL_INT,0,vertex);
    glDrawArrays(GL_QUADS,0,4);*/
}

void GuiRender::setColor(float r, float g, float b, float alpha){
    this->r = r;
    this->g = g;
    this->b = b;
    this->alpha = alpha;
    glColor4f(r,g,b,alpha);
}

void GuiRender::move(int x, int y){
    this->x += x;
    this->y -= y;
}

void GuiRender::saveState(){
    State temp = {x,y};
    savedStates.push_back(temp);
}

void GuiRender::restoreState(){
    if(savedStates.empty()) return;

    State restored = savedStates.back();
    savedStates.pop_back();

    x = restored.x;
    y = restored.y;
}

State GuiRender::getCurrentState(){
    State ret = {x,y};
    return ret;
}

void GuiRender::initRendering(){
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glPushClientAttrib(GL_ALL_CLIENT_ATTRIB_BITS);
  glMatrixMode(GL_PROJECTION);  // Change Matrix Mode to Projection
  glLoadIdentity();             // Reset View
  glOrtho(0, width, 0, height, 0, 100);
  glMatrixMode(GL_MODELVIEW);   // Change Projection to Matrix Mode
  glLoadIdentity();

  glTranslatef(0, 0, -1);
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_DEPTH_TEST);                 // Enable Depth Buffer
  
  glEnable(GL_TEXTURE_2D);
  //glBindTexture(GL_TEXTURE_2D,skinID);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  y = height;
  x = 0;
}

void GuiRender::deinitRendering(){
    glPopClientAttrib();
    glPopAttrib();
}

void GuiRender::setWindowSize(int width, int height){
	if (height == 0)               // prevent divide by zero exception
		height = 1;
	glViewport(0, 0, width, height);    // Set the viewport for the OpenGL window
	glMatrixMode(GL_PROJECTION);        // Change Matrix Mode to Projection
	glLoadIdentity();                   // Reset View
	gluPerspective(45.0, width/height, 1.0, 100.0);  // Do the perspective calculations. Last value = max clipping depth
	glMatrixMode(GL_MODELVIEW);         // Return to the modelview matrix
	glLoadIdentity();                   // Reset View

	this->width = width;
	this->height = height;
}

GuiRender::GuiRender() : r(0),g(0),b(0),alpha(1)
{ }

GuiRender::~GuiRender(){
	glDeleteTextures(1,&skinID);
}
