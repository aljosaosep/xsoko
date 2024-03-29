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

#ifdef _WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
#endif

#include <GL/gl.h>
#include <ft2build.h>
#include "fonts.h"
#include "gui.h"
#include "../messages.h"
#include "guirender.h"

Font::Font(const string& name){
    this->name = name;
    loadFont();
}

Font::~Font(){
    if(font != NULL)
       delete font;
}

void Font::writeText(int x, int y,string text){
    State ren = GuiRender::getInstance().getCurrentState();
    writeTextAbs(ren.x+x,ren.y-y,text);
}

void Font::writeTextAbs(int x, int y, string text){
    if(font == NULL)
        return;
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushMatrix();
    glColor3f(r/255.0f,g/255.0f,b/255.0f);
    glTranslatef(x, y, 0);
    font->Render(text.c_str());
    glPopMatrix();
    glPopAttrib();
    //glColor3f(1,1,1);
}

float Font::stringWidth(string str){
    if(font == NULL)
        return -1;
    return font->Advance(str.c_str());
}

int Font::getSize(){
    //return size;
    return font->FaceSize();
}

void Font::setSize(int size){
    this->size = size;
    if(font != NULL)
        font->FaceSize(size);
}

void Font::setColor(unsigned char R, unsigned char G, unsigned char B){
    r = R;
    g = G;
    b = B;
}

string Font::getName(){
    return name;
}

void Font::setName(string name){
    this->name = name;
    if(font != NULL)
        delete font;
    loadFont();
}

void Font::loadFont(){
    string path = "data/"+name+".ttf";

    #ifndef _WINDOWS
        font = new FTBufferFont::FTBufferFont(path.c_str());
    #else
        font = new FTBufferFont(path.c_str());
    #endif

    if(font->Error()){
        PacGame::Messages::errorMessage("Unable to load font file:"+path);
        delete font;
        font = NULL;
        return;
    }
    font->FaceSize(12);
    size = 12;
    r = g = b = 0;
    if(!font->CharMap(FT_ENCODING_UNICODE))
        PacGame::Messages::infoMessage("Warning: Font \""+name+"\" have no unicode support!");
}
