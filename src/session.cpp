/* 
 * File:   session.cpp
 * Author: aljosa
 *
 * Created on July 18, 2008, 12:16 AM
 */

#include "level.h"


#include "session.h"
#include <cstdio>
#include <cmath>



namespace PacGame
{
    namespace GameClasses
    {
        void PGameSession::mainLoop()
        {
            Messages::infoMessage("Entering main loop...");
            // the time of the previous frame
            double old_time = glfwGetTime();   
            
            float width=(float)this->level->getWidth()-1, height=(float)this->level->getHeight()-1; // tmp
            
            float bigger = width > height ? width : height;  // tmp
            
            unsigned frames = 0;
            
            while(1/*this->isGameRunning*/)
            {
                // calculate time elapsed, and the amount by which stuff rotates
                double current_time = glfwGetTime(),
                delta_rotate = (current_time - old_time) * rotations_per_tick * 360;
                
              cout<<"FPS: "<<(double) frames /  old_time<<endl;
                this->level->processBombs(current_time);
                old_time = current_time;
                
                // is game over? or level done?
                if(this->level->getEndgameFlag())
                    break;
                
                // check for input every time
                this->input->process();

                // clear the buffer
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glLoadIdentity(); // reset view matrix

                this->camera->setCamera(PVector3D(height, -width,  2*bigger+6),PVector3D(height,-width, 0.0), PVector3D(0.0, 1.0, 0.0));

                gluLookAt(this->camera->view.getCoordX(), this->camera->view.getCoordY(), this->camera->view.getCoordZ(), 
                        this->camera->position.getCoordX(), this->camera->position.getCoordY(), this->camera->position.getCoordZ(), 
                        this->camera->up.getCoordX(), this->camera->up.getCoordY(), this->camera->up.getCoordZ());

                glRotatef(-90.0, 0.0, 0.0, 1.0);

                this->level->draw();
                frames ++;
              
                glfwSwapBuffers();
            }
        }
        
        bool PGameSession::initialize()
        {    
            return true;
        }
        
        bool PGameSession::run()
        {
            // first, we init level, because witohut it, there is no game
            if(!level->initialize())
                return false;
            
            // next, we initiate session
            if(!this->initialize())
            {
                Messages::initMessage("Game session", false);
                return false;
            }
            else
                Messages::initMessage("Game session", true);
            
            
            // at last(but not at least;)), we trigger main loop
            // down there, code is not finished yet!!!!
            this->mainLoop();
            
            return true;
        }
        
        // setters
        // sets session's level
        void PGameSession::setLevel(PLevel *level)
        {
            this->level = level;
            this->player = level->getPlayerHandle();
        //    level->initialize();
        }
        
        
        void PGameSession::setInput(PInputSystem *input)
        {
            this->input = input;
        }
        
        // sets session's score
        void PGameSession::setScore(unsigned score)
        {
            this->score = score;
        }
        
     /*   void PGameSession::setGameEnd()
        {
            this->isGameRunning = false;
        }*/
        
        // getters
        // return current level
        PLevel* PGameSession::getLevel() const
        {
            return this->level;
        }
        
        // returns score
        unsigned PGameSession::getScore() const
        {
            return this->score;
        }
    }
}
