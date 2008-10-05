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
 * File:   session.cpp
 * Author: aljosa
 *
 * Created on July 18, 2008, 12:16 AM
 */

#include "level.h"


#include "session.h"
#include "gui/gui.h"
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
            
            unsigned frames = 0;
            
            this->camera->fitCameraToLevel(this->level->getWidth(), this->level->getHeight());
            
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
     /*       if(!this->initialize())
            {
                Messages::initMessage("Game session", false);
                return false;
            }
            else
                Messages::initMessage("Game session", true);*/
            
            
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
        
        PGuiSession::PGuiSession(int width, int height){
            initSuccess = false;
            if(InitGUI("data/GUI.tga","data/font.tga")){
                canQuit = false;
                setCallBacks();
                SetGuiSession(this);
                //glfwDisable(GLFW_MOUSE_CURSOR);
                glResizeWnd(width,height);
                
                mainWin = new Window(width/2 - 67, height/2 - 65, 135, 130);
                Button* btn = new Button(30, 40, 75, 25, "Run Game");
                btn->onClick = &runAction;
                mainWin->AddComponent(btn);

                btn = new Button(30, 75, 75, 25, "Exit");
                btn->onClick = &closeAction;
                mainWin->AddComponent(btn); 

                setMainWindow(mainWin);
                
                initSuccess = true;
            }
        }
        
        bool PGuiSession::run(){
            if(!initSuccess)
                return false;
            
            while(!canQuit){
                // clear the buffer
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                // draw the figure
                RenderGUI();
                glfwSwapBuffers();
            }
            return true;
        }
        
        void PGuiSession::setCallBacks(){
            glfwSetMouseButtonCallback(onMouseClick);
            glfwSetMousePosCallback(onMouseMove);
            glfwSetWindowSizeCallback(glResizeWnd);
        }
        
        void PGuiSession::removeCallBacks(){
            glfwSetMouseButtonCallback(NULL);
            glfwSetMousePosCallback(NULL);
            glfwSetWindowSizeCallback(NULL);
        }
        
        void PGuiSession::Quit(){
            canQuit = true;
        }
        
        void PGuiSession::LoadLevel(string levelPath){
            removeCallBacks();
            
            PLevel* level = new PLevel(levelPath);
            // input object
            PInputSystem input(level); 
            // make session
            PGameSession levelSession(level, &input);
            levelSession.run();
            delete level;
            
            setCallBacks();
        }
        
        PGuiSession::~PGuiSession(){
            DestroyGUI();
            removeCallBacks();
            glfwEnable(GLFW_MOUSE_CURSOR);
        }
    }
}
