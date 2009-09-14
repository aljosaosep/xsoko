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

#include "fonts.h"


#include "text.h"

/*------------------------------------------------------------------*
 *  initialise the Text                                             *
 *------------------------------------------------------------------*/
Text::Text(int x,int y,string text) : Component(x,y,100,12),
        fnt(new Font("font")), autoResize(true)
{
    focusIndex = -1;
	setText(text);
}

Text::~Text(){
    delete fnt;
}

bool Text::isAutoResize(){
	return autoResize;
}

void Text::setAutoResize(bool autoResize){
	this->autoResize = autoResize;
}

void Text::onRender()
{
	int startofline = 0, lines = 0;
	for(int i=0;i<caption.size();i++){
            if(caption[i] == '\n'){
                    fnt->writeText(0, (++lines)*fnt->getSize(), caption.substr(startofline,i-startofline));
                    startofline = i+1;
            }
	}
	fnt->writeText(0, (lines+1)*fnt->getSize(), caption.substr(startofline));
}

string Text::getText(){
    return caption;
}

void Text::setText(const string& text){
    caption = text;
    if(autoResize){
        string test;
        int startofline = 0, maxlength = 0, lines = 0, len;
        for(int i=0;i<text.size();i++){
                if(text[i] == '\n'){
                        test = text.substr(startofline,i-startofline);
                        len = fnt->stringWidth(test);
                        if(len > maxlength)
                                maxlength = len;
                        lines ++;
                        startofline = i+1;
                }
        }
        test = text.substr(startofline);
        len = fnt->stringWidth(test);
        if(len > maxlength)
                maxlength = len;
        width = maxlength;
        height = lines*fnt->getSize();
    }
}

Font* Text::getFont(){
    return fnt;
}

