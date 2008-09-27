/* 
 * File:   input.cpp
 * Author: aljosa
 *
 * Created on July 20, 2008, 5:50 PM
 */

#include "level.h"


#include "input.h"
#include "level.h"
#include <AL/alut.h>

using namespace PacGame::GameClasses::GameObjects;

namespace PacGame
{
    namespace GameClasses
    {
        void PInputSystem::process()
        {
            // gets renderer handle, for camera
             PRenderer *rn = this->level->getGameCoreHandle()->getRenderer();
            
            glfwEnable(GLFW_STICKY_KEYS);  // enables sticky keys
            
            // in next lines, we check if some keys has been pressed
            if((glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS) && (glfwGetKey(GLFW_KEY_UP) == GLFW_RELEASE))  // checks up key
            {
                this->level->moveObject(Aliases::up, this->level->getPlayerHandle());  // move object player up
            }
            else if((glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS) && (glfwGetKey(GLFW_KEY_DOWN) == GLFW_RELEASE)) // checks down key
            {
                this->level->moveObject(Aliases::down, this->level->getPlayerHandle()); // move object player down             
            }
            else if((glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS) && (glfwGetKey(GLFW_KEY_LEFT) == GLFW_RELEASE)) // checks left key
            {
                this->level->moveObject(Aliases::left, this->level->getPlayerHandle()); // move object player left             
            }
            else if((glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS) && (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_RELEASE)) // checks right key
            {
                this->level->moveObject(Aliases::right, this->level->getPlayerHandle()); // move object player right                  
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
                    this->level->addDroppedBomb(this->getLevel()->getPlayerHandle()->getI(), this->getLevel()->getPlayerHandle()->getJ());
                    this->level->getPlayerHandle()->decBombs();
                    
                    // vsekaj zvok
                    ALuint helloBuffer, helloSource;
                    ALenum error;
                    helloBuffer = alutCreateBufferFromFile("sound/bombtiq.wav");
                    if (helloBuffer == AL_NONE)
                    {
                        error = alutGetError();
                        cout << "Napaka: " << alutGetErrorString(error) << endl;
                    }
                    alGenSources (1, &helloSource);
                    alSourcei (helloSource, AL_BUFFER, helloBuffer);
                    alSourcePlay (helloSource);
                    
                }
              //  this->level->setDetonatedBomb()
            }
            
            // camera values; if you need to move camera, uncomment this code
            else if((glfwGetKey('W') == GLFW_PRESS) && (glfwGetKey('W') == GLFW_RELEASE))
            {              
                rn->setCameraY(rn->getCameraY()-0.9);           
            }
            else if((glfwGetKey('S') == GLFW_PRESS) && (glfwGetKey('S') == GLFW_RELEASE))
            {              
                rn->setCameraY(rn->getCameraY()+0.9);           
            }
            
            else if((glfwGetKey('A') == GLFW_PRESS) && (glfwGetKey('A') == GLFW_RELEASE))
            {              
                rn->setCameraX(rn->getCameraX()-0.9);           
            }
            else if((glfwGetKey('F') == GLFW_PRESS) && (glfwGetKey('F') == GLFW_RELEASE))
            {              
                rn->setCameraX(rn->getCameraX()+0.9);           
            }
            
            else if((glfwGetKey('Q') == GLFW_PRESS) && (glfwGetKey('Q') == GLFW_RELEASE))
            {              
                rn->setCameraZ(rn->getCameraZ()-0.9);           
            }
            else if((glfwGetKey('Z') == GLFW_PRESS) && (glfwGetKey('Z') == GLFW_RELEASE))
            {              
                rn->setCameraZ(rn->getCameraZ()+0.9);           
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
    }
}
