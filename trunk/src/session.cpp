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

#include "gui/gui.h"


#include "gui/win.h"


#include "gui/win.h"


/* 
 * File:   session.cpp
 * Author: aljosa
 *
 * Created on July 18, 2008, 12:16 AM
 */

#include "level.h"


#include "session.h"
#include "gui/gui.h"
#include "renderer/particle.h"
#include <cstdio>
#include <cmath>
//#include <boost/filesystem.hpp>

//using namespace boost::filesystem;

namespace PacGame
{
    namespace GameClasses
    {
        PGameSession::PGameSession(PLevel *level, PInputSystem *input) : level(level), camera(level->getGameCoreHandle()->getCamera()), input(input), moves(0),  rotations_per_tick(0.1), gameWin(createGameMenu())
        {}
        
        PGameSession::PGameSession() : level(NULL), player(NULL), camera(NULL), input(NULL),  moves(0),rotations_per_tick(0.1), gameWin(createGameMenu())
        {}
            
        void PGameSession::mainLoop()
        {
            Messages::infoMessage("Entering main loop...");
            // the time of the previous frame
            double old_time = glfwGetTime();   
            
            unsigned frames = 0;
            
            this->camera->fitCameraToLevel(this->level->getWidth(), this->level->getHeight());
            
            RenderMaschine::PParticleEngine particles(5.0, 7.0, 9.0);
            
            
            
            while(1/*this->isGameRunning*/)
            {
                // calculate time elapsed, and the amount by which stuff rotates
                double current_time = glfwGetTime(),
                delta_rotate = (current_time - old_time) * rotations_per_tick * 360;
                
         //     cout<<"FPS: "<<(double) frames /  old_time<<endl;
                this->level->processBombs(current_time);
                old_time = current_time;
                
                // is game over? or level done?
                if(this->level->getEndgameFlag() || forceQuit)
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
 
                   particles.process(delta_rotate*10);

                

                
                if(this->input->isGameMenuVisible()){
                    glDisable(GL_LIGHTING);
                    RenderGUI();
                    glEnable(GL_LIGHTING);
                    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
                    glLoadIdentity();                                                         // Reset The Projection Matrix
                    // Calculate The Aspect Ratio Of The Window
                    gluPerspective(45.0f,640.0f/480,0.1f,100.0f);
                    glMatrixMode(GL_MODELVIEW);						// Select The Modelview Matrix
                    
                    // Aljosa: two lines that follows are blend-gui-to-game fix ;)
                    glEnable(GL_DEPTH_TEST);    // after drawing GUI, enable depth test
                    glEnable(GL_BLEND);         // and blending
                    //glLoadIdentity();
                }
                frames ++;
              
                glfwSwapBuffers();
            }
        }
        
        void PGameSession::Quit(){
            forceQuit = true;
        }
        
        void PGameSession::resetLevel(){
            level->reset();
            input->setGameMenuVisible(false);
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
            forceQuit = false;
            setMainWindow(gameWin);
            SetGameSession(this);
            input->setGameMenuVisible(false);
            //gameWin->setVisible(false);
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
            this->camera = level->getGameCoreHandle()->getCamera();
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
        
        PGameSession::~PGameSession()
        {
            SetGameSession(NULL);
            delete gameWin;
        }
        
        PGuiSession::PGuiSession(int width, int height){
            initSuccess = false;
            if(InitGUI("data/GUI.tga","data/font.tga")){
                canQuit = false;
                setCallBacks();
                SetGuiSession(this);
                levelSession.setInput(&input);
                //glfwDisable(GLFW_MOUSE_CURSOR);
                glResizeWnd(width,height);
                
                mainWin = createMainMenu();
                setMainWindow(mainWin);
                
                initSuccess = true;
            }
        }
        
        bool PGuiSession::run(){
            if(!initSuccess)
                return false;
            
            double lastTime = glfwGetTime();
            int fps = 0;
            while(!canQuit){
                if(glfwGetTime()-lastTime>=1){
                    cout << "FPS: " << fps << endl;
                    fps = 0;
                    lastTime = glfwGetTime();
                } else
                    fps++;
                // clear the buffer
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glLoadIdentity();
                glTranslatef(0, 0, -4);
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
            //removeCallBacks();
            
            //move to better place
            glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
            glLoadIdentity();                                                         // Reset The Projection Matrix
            // Calculate The Aspect Ratio Of The Window
            gluPerspective(45.0f,640.0f/480,0.1f,100.0f);
            glMatrixMode(GL_MODELVIEW);						// Select The Modelview Matrix
            glLoadIdentity();
            
            PLevel level(levelPath);
            // input object
            input.setLevel(&level);
            // make session
            levelSession.setLevel(&level);
            levelSession.run();
            
            setMainWindow(mainWin);            
            //setCallBacks();
        }
        
        Window* PGuiSession::getMainWindow(){
            return mainWin;
        }
        
        PGuiSession::~PGuiSession(){
            SetGuiSession(NULL);
            DestroyGUI();
            removeCallBacks();
            glfwEnable(GLFW_MOUSE_CURSOR);
            delete mainWin;
        }
    }
}
