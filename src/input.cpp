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
#include <AL/alut.h>

using namespace PacGame::GameClasses::GameObjects;

namespace PacGame
{
    namespace GameClasses
    {

        void PInputSystem::process()
        {
            // gets renderer handle, for camera
//             PRenderer *rn = this->level->getGameCoreHandle()->getRenderer();

            glfwEnable(GLFW_STICKY_KEYS);  // enables sticky keys            

            // in next lines, we check if some keys has been pressed
            if(!toggleMenu){
                if((glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS) /*&& (glfwGetKey(GLFW_KEY_UP) == GLFW_RELEASE)*/)  // checks up key
                {
                    //if(
                    this->level->setButtonFlag(KB_UP);
                    //this->level->moveObject(Aliases::up, this->level->getPlayerHandle());
                    //)  // move object player up
                    //this->level->getGameCoreHandle()->getCamera()->rotateViewY(0.5);
                }
                else if((glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS) /*&& (glfwGetKey(GLFW_KEY_DOWN) == GLFW_RELEASE)*/) // checks down key
                {
                    //if(
                    this->level->setButtonFlag(KB_DOWN);
                    //this->level->moveObject(Aliases::down, this->level->getPlayerHandle());
                    //) // move object player down
                        //this->level->getGameCoreHandle()->getCamera()->rotateViewY(-0.5);
                }
                else if((glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS) /*&& (glfwGetKey(GLFW_KEY_LEFT) == GLFW_RELEASE)*/) // checks left key
                {
                    //if(
                    this->level->setButtonFlag(KB_LEFT);
                    //this->level->moveObject(Aliases::left, this->level->getPlayerHandle());
                    //) // move object player left
                    //this->level->getGameCoreHandle()->getCamera()->rotateViewX(-0.5);
                }
                else if((glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS) /*&& (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_RELEASE)*/) // checks right key
                {
                    //if(
                    this->level->setButtonFlag(KB_RIGHT);
                    //this->level->moveObject(Aliases::right, this->level->getPlayerHandle());
                    //) // move object player right
                    //this->level->getGameCoreHandle()->getCamera()->rotateViewX(0.5);
                }
                 else if(glfwGetKey(GLFW_KEY_UP) == GLFW_RELEASE) 
                {
                    this->level->resetButtonFlag(KB_UP);
                }
                else if(glfwGetKey(GLFW_KEY_DOWN) == GLFW_RELEASE) 
                {
                    this->level->resetButtonFlag(KB_DOWN);
                }
                else if(glfwGetKey(GLFW_KEY_LEFT) == GLFW_RELEASE)
                {
                    this->level->resetButtonFlag(KB_LEFT);
                }
                else if(glfwGetKey(GLFW_KEY_RIGHT) == GLFW_RELEASE)
                {
                    this->level->resetButtonFlag(KB_RIGHT);
                }
                else if((glfwGetKey(GLFW_KEY_SPACE) == GLFW_PRESS) && (glfwGetKey(GLFW_KEY_SPACE) == GLFW_RELEASE))
                {
                    Messages::infoMessage("Key space pressed, dumping...");                
                    this->level->print();              
                }
                else if((glfwGetKey('D') == GLFW_PRESS) && (glfwGetKey('D') == GLFW_RELEASE))
                {
                    if(this->level->getPlayerHandle()->getBombs() > 0)
                    {
                        if(this->level->addDroppedBomb(this->getLevel()->getPlayerHandle()->getI(), this->getLevel()->getPlayerHandle()->getJ()))
                        {
                    //        this->level->
                            this->level->getPlayerHandle()->decBombs();
                            
                            

                            // vsekaj zvok
                       /*     ALuint helloBuffer, helloSource;
                            ALenum error;
                            helloBuffer = alutCreateBufferFromFile("sound/bombtiq.wav");
                            if (helloBuffer == AL_NONE)
                            {
                                error = alutGetError();
                                cout << "Napaka: " << alutGetErrorString(error) << endl;
                            }
                            alGenSources (1, &helloSource);
                            alSourcei (helloSource, AL_BUFFER, helloBuffer);
                            alSourcePlay (helloSource);*/
                        }

                    }
                  //  this->level->setDetonatedBomb()
                }
            }
            if((glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS) && (glfwGetKey(GLFW_KEY_ESC) == GLFW_RELEASE))
            {
                toggleMenu = !toggleMenu;
                glfwDisable(GLFW_STICKY_KEYS);  // enables sticky keys
            }
            
            // camera values; if you need to move camera, uncomment this code
  /*          else if((glfwGetKey('W') == GLFW_PRESS) && (glfwGetKey('W') == GLFW_RELEASE))
            {              
         
            }
            else if((glfwGetKey('S') == GLFW_PRESS) && (glfwGetKey('S') == GLFW_RELEASE))
            {              
          
            }
            
            else if((glfwGetKey('A') == GLFW_PRESS) && (glfwGetKey('A') == GLFW_RELEASE))
            {              
           
            }
            else if((glfwGetKey('F') == GLFW_PRESS) && (glfwGetKey('F') == GLFW_RELEASE))
            {              
     
            }
            
            else if((glfwGetKey('Q') == GLFW_PRESS) && (glfwGetKey('Q') == GLFW_RELEASE))
            {              
         
            }
            else if((glfwGetKey('Z') == GLFW_PRESS) && (glfwGetKey('Z') == GLFW_RELEASE))
            {              
        
            } */
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
    }
}
