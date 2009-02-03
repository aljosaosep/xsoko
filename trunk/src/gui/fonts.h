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

/* 
 * File:   fonts.h
 * Author: jernej
 *
 * Created on Ponedeljek, 2 februar 2009, 13:25
 */

#ifndef _FONTS_H
#define	_FONTS_H

#include <vector>
#include <string>

using namespace std;

class Font{
private:
    struct fonts{
        string name;
        unsigned instances;
        Font* font;
    };
    
    string name;
    GLuint texIndex;
    GLuint fontList;
    static vector<fonts> openFonts;
    
    Font(const string& name, const string& texPath, const string& fntPath);
    ~Font();
    bool BuildFont(const string& path);
public:
    static Font* getInstance(string name);
    static void destroyInstance(Font* instance);
    void writeText(int x, int y, string text);
};

#endif	/* _FONTS_H */

