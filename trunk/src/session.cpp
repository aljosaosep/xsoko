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

#include <GL/glfw.h>


#include "input.h"



/* 
 * File:   session.cpp
 * Author: aljosa
 *
 * Created on July 18, 2008, 12:16 AM
 */

#include "level.h"
#include "gui/win.h"
#include "session.h"
#include "renderer/particle.h"
#include <cstdio>
#include <cmath>

#if !(defined(Windows_Release) || defined(Windows_Debug))
    #include <boost/filesystem.hpp>
#else
    #define BOOST_WINDOWS_API
    #include <boost/filesystem/convenience.hpp>
    #include <boost/filesystem/path.hpp>
    #include <boost/filesystem/operations.hpp>
#endif

using namespace boost::filesystem;

namespace PacGame
{
    namespace GameClasses
    {
       /* PGameSession::PGameSession(PLevel *level, PInputSystem *input) : level(level), camera(level->getGameCoreHandle()->getCamera()), input(input), moves(0),  rotations_per_tick(0.1), levelLoaded(false)//, gameWin(createGameMenu())
        {
            prepareGui();
        }*/
        
        PGameSession::PGameSession() : level(NULL), player(NULL), camera(NULL), input(new PInputSystem()),  moves(0),rotations_per_tick(0.1), levelLoaded(false), gameQuit(false)
        {
            prepareGui();
        }
        
        void PGameSession::prepareGui(){
            Messages::infoMessage("Initialiazing GUI...");
            gui = new Gui("data/GUI.tga");
            glfwSetMouseButtonCallback(Gui::onMouseClick);
            glfwSetMousePosCallback(Gui::onMouseMove);
            glfwSetWindowSizeCallback(Gui::glResizeWnd);
            //glfwDisable(GLFW_MOUSE_CURSOR);
            
            mainMenu = new Window(253, 158, 135, 165, "Main Menu");
            
            Button* btn = new Button(30, 40, 75, 25, "Campaing");
            btn->setName("campaing");
            btn->setAction(this);
            mainMenu->AddComponent(btn);

            btn = new Button(30, 75, 75, 25, "Freeplay");
            btn->setName("freeplay");
            btn->setAction(this);
            mainMenu->AddComponent(btn);

            btn = new Button(30, 110, 75, 25, "Exit");
            btn->setName("guiExit");
            btn->setAction(this);
            mainMenu->AddComponent(btn);
            
            gui->addWindow(mainMenu);

            freeMenu = new Window(210, 158, 220, 141, "Freeplay");
            freeMenu->setVisible(false);

            listbox = new ListBox(10,40,115,68);
            path dir_path("data");
            directory_iterator end_itr; // default construction yields past-the-end
            for (directory_iterator itr(dir_path);itr != end_itr; ++itr )
            {
              if ( !is_directory(*itr) && extension(*itr) == ".lvl" )
              {

#if !(defined(Windows_Release) || defined(Windows_Debug))
                  string filename = itr->path().leaf();
#else
                  string filename = itr->leaf();
#endif
                  listbox->addItem(filename.substr(0,filename.find_last_of('.')));
              }
            }
            freeMenu->AddComponent(listbox);

            btn = new Button(135,40,75,25,"Play");
            btn->setName("play");
            btn->setAction(this);
            freeMenu->AddComponent(btn);

            btn = new Button(135,70,75,25,"Back");
            btn->setName("back");
            btn->setAction(this);
            freeMenu->AddComponent(btn);

            gui->addWindow(freeMenu);
            
            gameMenu = new Window(253, 158, 135, 165, "Menu");
            gameMenu->setVisible(false);
            gameMenu->setEnableCloseButton(false);

            btn = new Button(30, 40, 75, 25, "Save");
            btn->setName("save");
            btn->setAction(this);
            gameMenu->AddComponent(btn);

            btn = new Button(30, 75, 75, 25, "Reset");
            btn->setName("reset");
            btn->setAction(this);
            gameMenu->AddComponent(btn);

            btn = new Button(30, 110, 75, 25, "Exit");
            btn->setName("gameExit");
            btn->setAction(this);
            gameMenu->AddComponent(btn);
            
            gui->addWindow(gameMenu);
        }
            
        void PGameSession::mainLoop()
        {
            Messages::infoMessage("Entering main loop...");

            // the time of the previous frame
            double old_time = glfwGetTime();   

#if defined(Linux_Debug) || defined(Windows_Debug)
            unsigned frames = 0;
            string title;
#endif
            
            //this->camera->fitCameraToLevel(this->level->getWidth(), this->level->getHeight());
            bool toggle = false;
            unsigned msgid = 0;
            
            //RenderMaschine::PParticleEngine particles(5.0, 7.0, 9.0);

            while(!gameQuit /*1 this->isGameRunning*/)
            {
                double current_time = glfwGetTime();

                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glLoadIdentity(); // reset view matrix

#if defined(Linux_Debug) || defined(Windows_Debug)
                if(current_time - old_time >= 1){
                  title = "xSoko project FPS: " + Functions::toString<int>(frames);
                  glfwSetWindowTitle(title.c_str());
                  old_time = current_time;
                  frames = 0;
                } else
                    frames ++;
#endif
                
                if(levelLoaded || msgid){
                
                    // calculate time elapsed, and the amount by which stuff rotates
                    //delta_rotate = (current_time - old_time) * rotations_per_tick * 360;

                    //if no win message is shown, check for input etc.
                    if(!msgid){

                        this->level->processBombs(current_time);

                        // check for input every time
                        this->input->process(toggle);

                        if(this->input->toggleGameMenu()){
                            toggle = !toggle;
                            gameMenu->setVisible(toggle);
                            gui->setMouseVisible(toggle);
                        }

                        // is game over? or level done?
                        if(this->level->getEndgameFlag() || forceLevelQuit){
                            levelLoaded = false;
                            gameMenu->setVisible(false);
                            if(level->getEndgameFlag())
                               msgid = gui->showMessage("xSoko", "Congratulations, you won!");
                            else
                               mainMenu->setVisible(true);
                            gui->setMouseVisible(true);
                        }

                    }

                    gluLookAt(this->camera->view.getCoordX(), this->camera->view.getCoordY(), this->camera->view.getCoordZ(),
                            this->camera->position.getCoordX(), this->camera->position.getCoordY(), this->camera->position.getCoordZ(), 
                            this->camera->up.getCoordX(), this->camera->up.getCoordY(), this->camera->up.getCoordZ());

                    glRotatef(-90.0, 0.0, 0.0, 1.0);

                    glEnable(GL_LIGHTING);

                    this->level->draw();

                    //particles.process(delta_rotate*10);

                    glDisable(GL_LIGHTING);
                }

                if(msgid && !gui->isMessageActive(msgid)){
                        msgid = 0;
                        mainMenu->setVisible(true);
                }
                
                gui->Render();

                if(levelLoaded || msgid){
                    toggle = false;
                    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
                    glLoadIdentity();                                                         // Reset The Projection Matrix
                    // Calculate The Aspect Ratio Of The Window
                    gluPerspective(45.0f,640.0f/480,0.1f,100.0f);
                    glMatrixMode(GL_MODELVIEW);						// Select The Modelview Matrix
                    glLoadIdentity();
                    // Aljosa: two lines that follows are blend-gui-to-game fix ;)
                    glEnable(GL_DEPTH_TEST);    // after drawing GUI, enable depth test
                    glEnable(GL_BLEND);         // and blending
                }
              
                glfwSwapBuffers();
            }
        }
        
        /*bool PGameSession::initialize()
        {    
            
            return true;
        }*/
        
        // setters
        // sets session's level
        /*void PGameSession::setLevel(PLevel *level)
        {
            this->level = level;
            this->player = level->getPlayerHandle();
            this->camera = level->getGameCoreHandle()->getCamera();
        //    level->initialize();
        }*/
        
        
        /*void PGameSession::setInput(PInputSystem *input)
        {
            this->input = input;
        }*/
        
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
        
        void PGameSession::LoadLevel(string levelPath){

            //removeCallBacks();
            if(level == NULL){
                level = new PLevel(levelPath);
                if(!level->initialize())
                    return;
                input->setLevel(level);
                this->player = level->getPlayerHandle();
                this->camera = level->getGameCoreHandle()->getCamera();
            } else
                if(!level->loadLevelFromFile(levelPath))
                    return;

            this->camera->fitCameraToLevel(this->level->getWidth(), this->level->getHeight());
            levelLoaded = true;
            forceLevelQuit = false;
            gui->setMouseVisible(false);
            //setCallBacks();
        }
        
        void PGameSession::onAction(Component* button){
            if(button->getName() == "campaing"){
                mainMenu->setVisible(false);
                LoadLevel("data/testlevel.lvl");
                return;
            }
            if(button->getName() == "freeplay"){
                mainMenu->setVisible(false);
                freeMenu->setVisible(true);
                return;
            }
            if(button->getName() == "guiExit"){
                gameQuit = true;
                return;
            }
            if(button->getName() == "play"){
                LoadLevel("data/"+listbox->getSelectedItem()+".lvl");
                freeMenu->setVisible(false);
                return;
            }
            if(button->getName() == "back"){
                freeMenu->setVisible(false);
                mainMenu->setVisible(true);
                return;
            }
            if(button->getName() == "save"){
                return;
            }
            if(button->getName() == "reset"){
                level->reset();
                gui->setMouseVisible(false);
                gameMenu->setVisible(false);
                return;
            }
            if(button->getName() == "gameExit"){
                forceLevelQuit = true;
                return;
            }
        }

        PGameSession::~PGameSession()
        {
            delete gui;
            delete freeMenu;
            delete gameMenu;
            delete mainMenu;
            glfwEnable(GLFW_MOUSE_CURSOR);
        }
    }
}
