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
Text::Text(int x,int y,string text) : Component(x,y,0,0), caption(text),
        fnt(new Font("font"))
{
    focusIndex = -1;
    setSize(fnt->stringWidth(text),fnt->getSize());
}

Text::~Text(){
    delete fnt;
}

/*------------------------------------------------------------------*
 *  Render Radio Text                                               *
 *------------------------------------------------------------------*/
void Text::onRender()
{
    fnt->writeText(0, fnt->getSize(), caption);
}

string Text::getText(){
    return caption;
}

void Text::setText(const string& text){
    caption = text;
}

Font* Text::getFont(){
    return fnt;
}

