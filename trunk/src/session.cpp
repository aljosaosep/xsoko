/* 
 * File:   session.cpp
 * Author: aljosa
 *
 * Created on July 18, 2008, 12:16 AM
 */

#include "session.h"

namespace PacGame
{
    namespace GameClasses
    {
        void PGameSession::mainLoop()
        {
            Messages::infoMessage("Entering main loop...");
            /*
             * ALL CODE IN THIS FUNCTION IS HERE JUST FOR TESTING PURPOSES
             *
             */
            
            // the time of the previous frame
            // double old_time = glfwGetTime();   // ne brisat! se bo nucal!
            // this just loops as long as the program runs
            float angle = 0.0;
            while(1)
            {
                // calculate time elapsed, and the amount by which stuff rotates
                // double current_time = glfwGetTime(),
                // delta_rotate = (current_time - old_time) * rotations_per_tick * 360;
                // old_time = current_time;

                // clear the buffer
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                   
                // temporary code!!!!
                // this->level->print();

                // reset view matrix
                glLoadIdentity();

                // temp
                glTranslatef(-1.0, -2.0, -20);
                glRotatef(angle, 1.0, 1.0, 0.0);
                renderer.drawCube(0.0, 0.0, 1.0);
                //renderer.drawFloor(0.0, -1.0, 1.0);
                angle+=0.1;
         
                glfwSwapBuffers();
            }
        }
        
        bool PGameSession::initialize()
        {
            // temporary code here!
          //  this->level->initialize();
            
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
        
        // sets session's score
        void PGameSession::setScore(unsigned score)
        {
            this->score = score;
        }
        
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
