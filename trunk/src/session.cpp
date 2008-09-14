/* 
 * File:   session.cpp
 * Author: aljosa
 *
 * Created on July 18, 2008, 12:16 AM
 */

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
            /*
             * ALL CODE IN THIS FUNCTION IS HERE JUST FOR TESTING PURPOSES
             *
             */
            
            // the time of the previous frame
            double old_time = glfwGetTime();   
            float angle = 0.0;
            
            // game official begins here! this is so called main game loop
            while(1/*this->isGameRunning*/)
            {
                // calculate time elapsed, and the amount by which stuff rotates
                double current_time = glfwGetTime(),
                delta_rotate = (current_time - old_time) * rotations_per_tick * 360;
                
                if(this->level->getDroppedBombLen() != 0)  // are there any bombs to trigger?
                {
                    // apparently they are!
                    if(round(current_time-this->level->getFirstDroppedBomb()->dropTime) == 3)  // is it time to trigger bomb yet?
                    {
                      //  if(this->level->)
                        cout<<endl;
                        cout<<"current: "<<current_time<<endl;
                        cout<<"drop: "<<this->level->getFirstDroppedBomb()->dropTime<<endl;
                        cout<<"KABOOOOOOOOOOOM!!!!"<<endl;
                        cout<<endl;
                        
                        cout<<"PLayer: "<<this->level->getPlayerHandle()->getI()<<' '<<this->level->getPlayerHandle()->getJ()<<endl;
                        
                        // check bomb surrounding fields
                        cout<<"check at: "<<level->getFirstDroppedBomb()->i-1<<' '<<level->getFirstDroppedBomb()->j<<endl;
                        this->level->checkAndApplyBombBlast(level->getFirstDroppedBomb()->i-1, level->getFirstDroppedBomb()->j);
                        
                        
                        cout<<"check at: "<<level->getFirstDroppedBomb()->i+1<<' '<<level->getFirstDroppedBomb()->j<<endl;                       
                        this->level->checkAndApplyBombBlast(level->getFirstDroppedBomb()->i+1, level->getFirstDroppedBomb()->j);
                        
                         cout<<"check at: "<<level->getFirstDroppedBomb()->i<<' '<<level->getFirstDroppedBomb()->j-1<<endl;  
                        this->level->checkAndApplyBombBlast(level->getFirstDroppedBomb()->i, level->getFirstDroppedBomb()->j-1);
                        
                            cout<<"check at: "<<level->getFirstDroppedBomb()->i<<' '<<level->getFirstDroppedBomb()->j+1<<endl;                      
                        this->level->checkAndApplyBombBlast(level->getFirstDroppedBomb()->i, level->getFirstDroppedBomb()->j+1);
                        
                        this->level->removeFirstDroppedBomb();
                    }
                }
                
                
/*                if(round(current_time-input->getBombDropTime()) == 3)
                {
                    cout<<endl;
                    cout<<"current: "<<current_time<<endl;
//                    cout<<"drop: "<<input->getBombDropTime()<<endl;
                    cout<<"KABOOOOOOOOOOOM!!!!"<<endl;
                    cout<<endl;
                }*/
                
           //                     cout<<"Cas:"<<current_time-old_time<<endl;
                old_time = current_time;
                

                
                // is game over? or level done?
                if(this->level->getEndgameFlag())
                    break;
                
                // check for input every time
                input->process();


                // clear the buffer
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glLoadIdentity(); // reset view matrix

                // gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, -5.0, 0.0, 1.0, 0.0);
                // moves camera
       //         glTranslatef(this->renderer->getCameraX(), this->renderer->getCameraY(), this->renderer->getCameraZ());
                glTranslatef(-10.0, 6.0, -25.0);                
                // this->renderer->drawCube(0.0, 0.0, 0.5, angle);
                
              //  glRotatef(angle, 1.0, 1.0, 1.0);
                
                glRotatef(-90.0, 0.0, 0.0, 1.0);

                this->level->draw();
              
                glfwSwapBuffers();
                angle+=delta_rotate;
            }
        }
        
        bool PGameSession::initialize()
        {
            // set renderer to game session
        //    this->setRenderer();

            
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
        
        /*void PGameSession::setRenderer()
        {
            this->renderer = level->getRendererHandle();
        }*/
        
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
        
        /*PRenderer *PGameSession::getRendererHandle()
        {
            return this->renderer;
        }*/
    }
}
