/* 
 * File:   input.cpp
 * Author: aljosa
 *
 * Created on July 20, 2008, 5:50 PM
 */

#include "input.h"
#include "level.h"

namespace PacGame
{
    namespace GameClasses
    {
        void PInputSystem::process()
        {
            glfwEnable(GLFW_STICKY_KEYS);
            if((glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS) && (glfwGetKey(GLFW_KEY_UP) == GLFW_RELEASE))  // checks up key
            {
                this->level->moveObject(Aliases::up, this->level->getPlayerHandle());
                this->level->print(); 
            }
            else if((glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS) && (glfwGetKey(GLFW_KEY_DOWN) == GLFW_RELEASE)) // checks down key
            {
                this->level->moveObject(Aliases::down, this->level->getPlayerHandle());
                this->level->print();               
            }
            else if((glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS) && (glfwGetKey(GLFW_KEY_LEFT) == GLFW_RELEASE)) // checks left key
            {
                this->level->moveObject(Aliases::left, this->level->getPlayerHandle());
                this->level->print();               
            }
            else if((glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS) && (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_RELEASE)) // checks right key
            {
                this->level->moveObject(Aliases::right, this->level->getPlayerHandle());
                this->level->print();                   
            }
            else if((glfwGetKey(GLFW_KEY_SPACE) == GLFW_PRESS) && (glfwGetKey(GLFW_KEY_SPACE) == GLFW_RELEASE))
            {
                Messages::infoMessage("Key space pressed, dumping...");                
                this->level->print();              
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
