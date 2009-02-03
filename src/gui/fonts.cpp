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

#include <boost/filesystem/operations.hpp>


#include <GL/glfw.h>
#include "fonts.h"
#include <boost/filesystem.hpp>

using namespace boost::filesystem;

//static variables
vector<Font::fonts> Font::openFonts;

Font::Font(const string& name, const string& texPath, const string& fntPath){
    glGenTextures(1,&texIndex);
    glBindTexture(GL_TEXTURE_2D,texIndex);
    if(glfwLoadTexture2D(texPath.c_str(), GLFW_ORIGIN_UL_BIT)){
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
       glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
       if(!BuildFont(fntPath))
           texIndex = 0;
    } else
        texIndex = 0;
    this->name = name;
}

Font::~Font(){
    glDeleteLists(fontList,256);
    glDeleteTextures(1,&texIndex);
}

bool Font::BuildFont(const string& path)
{
  FILE *fontFile = fopen(path.c_str(),"rb");
  if(fontFile == NULL)
    return false;
  
  unsigned char fontWidth[256];
  if(fread(fontWidth,1,sizeof(fontWidth),fontFile)!=sizeof(fontWidth)){
      fclose(fontFile);
      return false;
  }
  fclose(fontFile);

  // create the font display list
  fontList = glGenLists(256);               // Storage For 128 Characters
  for(int i=0;i<256;i++)
  {
    GLfloat x = (float)(i % 16) / 16;	     		// X Position Of Current Character
    GLfloat y = (float)(i / 16) / 16;	     		// Y Position Of Current Character
    glNewList(fontList+i, GL_COMPILE);       // Start Building A List
    glBegin(GL_QUADS);
      GLfloat xs = (16.0f-fontWidth[i])/2.0f/256.0f;
      glTexCoord2f(x+xs,1.0f-y-0.0625f);                                            glVertex2i(0, 0);
      glTexCoord2f(x+xs + (GLfloat)fontWidth[i]/256.0f + 1.0f/512.0f, 1.0f-y-0.0625f);  glVertex2i(fontWidth[i], 0);
      glTexCoord2f(x+xs + (GLfloat)fontWidth[i]/256.0f + 1.0f/512.0f, 1.0f-y);         glVertex2i(fontWidth[i], 16);
      glTexCoord2f(x+xs,1.0f-y);                                                   glVertex2i(0, 16);
    glEnd();
    glTranslatef(fontWidth[i], 0, 0);
    glEndList();
  }
  return true;
}

Font* Font::getInstance(string name){
    for(unsigned i=0;i<openFonts.size();i++){
        if(openFonts[i].name == name){
            openFonts[i].instances += 1;
            return openFonts[i].font;
        }
    }
    string path = "data/";
    path.append(name);
    string tex = path;
    tex.append(".tga");
    path.append(".fnt");
    if((!exists(tex)) && (!exists(path)))
        return NULL;
    fonts fnt;
    fnt.font = new Font(name,tex,path);
    fnt.name = name;
    fnt.instances = 1;
    openFonts.push_back(fnt);
    return fnt.font;
}

void Font::destroyInstance(Font* instance){
    for(unsigned i=0;i<openFonts.size();i++)
        if(openFonts[i].name == instance->name){
            openFonts[i].instances -= 1;
            if(openFonts[i].instances == 0){
                openFonts.erase(openFonts.begin()+i);
                delete instance;
            }
            break;    
        }
}

void Font::writeText(int x, int y,string text){
    if(texIndex == 0)
        return;
  glBindTexture(GL_TEXTURE_2D, texIndex);
  glPushMatrix();
    glTranslatef(x, y, 0.02);
    glListBase(fontList);
    glCallLists(text.length(), GL_BYTE, text.c_str());
  glPopMatrix();
}