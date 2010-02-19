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

#include "camera.h"


/* 
 * File:   input.cpp
 * Author: aljosa
 *
 * Created on July 20, 2008, 5:50 PM
 */

#include "level.h"
#include "input.h"
#include "gui/gui.h"
#include "game.h"
#include <iostream>

using namespace PacGame::GameClasses::GameObjects;

namespace PacGame
{
    namespace GameClasses
    {

        void PInputSystem::process()
        {
                SDL_Event event;
                while(SDL_PollEvent(&event))
                {
                        if(!toggleMenu)
                        {
                                switch(event.type)
                                {
                                        case SDL_QUIT:
                                                 toggleMenu = !toggleMenu;
                                        break;
                                        case SDL_KEYDOWN:
                                                if(event.key.keysym.sym == SDLK_UP)
                                                {
                                                        this->level->setButtonFlag(KB_UP);
                                                }else
                                                if(event.key.keysym.sym == SDLK_DOWN)
                                                {
                                                        this->level->setButtonFlag(KB_DOWN);
                                                }else
                                                if(event.key.keysym.sym == SDLK_LEFT)
                                                {
                                                        this->level->setButtonFlag(KB_LEFT);
                                                }else
                                                if(event.key.keysym.sym == SDLK_RIGHT)
                                                {
                                                        this->level->setButtonFlag(KB_RIGHT);
                                                }
                                        break;
                                        case SDL_KEYUP:
                                                if(event.key.keysym.sym == SDLK_UP)
                                                {
                                                        this->level->resetButtonFlag(KB_UP);
                                                }else
                                                if(event.key.keysym.sym == SDLK_DOWN)
                                                {
                                                        this->level->resetButtonFlag(KB_DOWN);
                                                }else
                                                if(event.key.keysym.sym == SDLK_LEFT)
                                                {
                                                        this->level->resetButtonFlag(KB_LEFT);
                                                }else
                                                if(event.key.keysym.sym == SDLK_RIGHT)
                                                {
                                                        this->level->resetButtonFlag(KB_RIGHT);
                                                }else
                                                if(event.key.keysym.sym == SDLK_d)
                                                {
                                                    if(this->level->addDroppedBomb())
                                                        PGame::getInstance().getSoundManagerInstance()->playEffect("bomb");
                                                }else
                                                if(event.key.keysym.sym == SDLK_ESCAPE)
                                                { 
                                                        toggleMenu = !toggleMenu;
                                                }else
                                                if(event.key.keysym.sym == SDLK_x)
                                                {
                                                    bool musicStatus = PGame::getInstance().getSoundManagerInstance()->getMusicStatus();
                                                    if (musicStatus) {
                                                        PGame::getInstance().getSoundManagerInstance()->stopMusic();
                                                    } else {
                                                        PGame::getInstance().getSoundManagerInstance()->playMusic();
                                                    }
                                                }else
                                                if (event.key.keysym.sym == SDLK_y)
                                                {
                                                    PGame::getInstance().getSoundManagerInstance()->playPreviousMusic();

                                                }else
                                                if (event.key.keysym.sym == SDLK_c)
                                                {
                                                    PGame::getInstance().getSoundManagerInstance()->playNextMusic();
                                                }
                                        break;
                                }
                        }else
                        {
                                switch(event.type)
                                {
                                        case SDL_QUIT:
                                                 //toggleMenu = !toggleMenu;
                                        break;
                                        case SDL_KEYUP:
                                                if(event.key.keysym.sym == SDLK_ESCAPE)
                                                { 
                                                        toggleMenu = !toggleMenu;
                                                        break;
                                                }
                                        case SDL_KEYDOWN:
                                                Gui::getInstance().onKeyClick(event.key.keysym.sym,event.key.type);
                                                //GUI::onCharacterSend();
                                        break;
                                        case SDL_MOUSEBUTTONUP:
                                        case SDL_MOUSEBUTTONDOWN:
                                                  Gui::getInstance().onMouseClick(event.button.button,event.button.type);
                                        break;
                                        case SDL_MOUSEMOTION:
                                                Gui::getInstance().onMouseMove(event.motion.x, event.motion.y);
                                        break;
                                }
                        }
                }
        }
        
        // setters
        void PInputSystem::setLevel(PLevel *level)
        {
            this->level = level;
        }
        
        // getters
        PLevel* PInputSystem::getLevel() const
        {
            return this->level;
        }
        
        bool PInputSystem::toggleGameMenu(){
            return toggleMenu;
        }

		void PInputSystem::closeGameMenu(){
            toggleMenu = false;
        }
        
        void PInputSystem::openGameMenu(){
            toggleMenu = true;
        }
    }
}
