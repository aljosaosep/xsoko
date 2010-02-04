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

#define GUI_TEX_BTN_PRESSED_LEFT		0
#define GUI_TEX_BTN_PRESSED_MIDDLE		1
#define GUI_TEX_BTN_PRESSED_RIGHT		2
#define GUI_TEX_BTN_UNPRESSED_LEFT		3
#define GUI_TEX_BTN_UNPRESSED_MIDDLE	4
#define GUI_TEX_BTN_UNPRESSED_RIGHT		5
#define GUI_TEX_WINDOW_TOP_LEFT			6
#define GUI_TEX_WINDOW_TOP_MIDLLE		7
#define GUI_TEX_WINDOW_TOP_RIGHT		8
#define GUI_TEX_WINDOW_LEFT				9
#define GUI_TEX_WINDOW_MIDLLE			10
#define GUI_TEX_WINDOW_RIGHT			11
#define GUI_TEX_WINDOW_BOTTOM_LEFT		12
#define GUI_TEX_WINDOW_BOTTOM_MIDLLE	13
#define GUI_TEX_WINDOW_BOTTOM_RIGHT		14
#define GUI_TEX_PANEL_TOP				15
#define GUI_TEX_PANEL_LEFT				16
#define GUI_TEX_PANEL_MIDLLE			17
#define GUI_TEX_PANEL_RIGHT				18
#define GUI_TEX_PANEL_BOTTOM			19
#define GUI_TEX_SCROLL_UP_ARROW			20
#define GUI_TEX_SCROLL_DOWN_ARROW		21
#define GUI_TEX_SCROLL_BODY				22
#define GUI_TEX_SCROLL_POSITION			23
#define GUI_TEX_RADIOBTN_UNCHECKED		24
#define GUI_TEX_RADIOBTN_CHECKED		25
#define GUI_TEX_CHECKBOX_UNCHECKED		26
#define GUI_TEX_CHECKBOX_CHECKED		27
#define GUI_TEX_MOUSE					28

struct State {
        int x,y;
    };

class GuiRender {
private:
    GLuint skinID;
    float r,g,b,alpha;
    int x,y;
    vector<State> savedStates;
	vector<Rect> clippingPlace;
	float textures[29][8];
	int width, height;
	string skimg, skfile;

	GuiRender();
    ~GuiRender();
public:
    void loadSkin(string skinImage, string skinFile);
	void reloadSkin();
    void drawImage(int index, Rect drawRect);
    void drawRect(Rect rectangle, int width);
    void drawFilledRect(int x1, int y1, int x2, int y2);
    void setColor(float r, float g, float b, float alpha);
	void setClipping(int x1, int y1, int x2, int y2);
	void restoreClipping();
    void move(int x, int y);
    void saveState();
    void restoreState();
	void setWindowSize(int width, int height);
    void initRendering();
    void deinitRendering();
    State getCurrentState();
    static GuiRender& getInstance();
};


#endif	/* _GUIRENDER_H */

