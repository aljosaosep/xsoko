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
/* 
 * File:   GuiRender.h
 * Author: jernej
 *
 * Created on Petek, 14 avgust 2009, 23:08
 */

#ifndef _GUIRENDER_H
#define	_GUIRENDER_H

#include "commongui.h"

struct State {
        float x,y,z;
    };

class GuiRender {
private:
    struct texInfo {
        string name;
        Rect location;
        bool operator< (const texInfo &x) { return (name < x.name);}
    };

    struct myclass {
        bool operator() (const texInfo &i, const texInfo &j) { return (i.name < j.name);}
    } sortObj;

    GLuint skinID;
    float r,g,b,alpha;
    float x,y,z;
    vector<State> savedStates;
    vector<texInfo> textureInfo;

    GuiRender();
    ~GuiRender() {}
public:
    void loadSkin(unsigned skin, string skinFile);
    void drawImage(Rect textureRect, Rect drawRect);
    void drawRect(Rect rectangle, int width);
    void drawFilledRect(Rect rectangle);
    void drawLine(int x1, int y1, int x2, int y2, int width);
    void setColor(float r, float g, float b, float alpha);
    void nextLayer();
    void move(float x, float y);
    void saveState();
    void restoreState();
    void initRendering();
    void deinitRendering();
    void mouseDepth();
    State getCurrentState();
    Rect getTextureLocation(string name);
    static GuiRender& getInstance();
};


#endif	/* _GUIRENDER_H */

