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
#ifdef _WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
#endif

#include <GL/glfw.h>


#include "input.h"



/* 
 * File:   session.cpp
 * Author: aljosa
 *
 * Created on July 18, 2008, 12:16 AM
 */

#include "level.h"
#include "session.h"
#include "renderer/particle.h"
#include "messages.h"
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
        
        PGameSession::PGameSession() :
            level(NULL), player(NULL), camera(NULL), input(new PInputSystem()),  moves(0),
            rotations_per_tick(0.1), levelLoaded(false), gameQuit(false)//, gui(Gui::getInstance())
        {
            prepareGui();
        }
        
        void PGameSession::prepareGui(){
            Messages::infoMessage("Initialiazing GUI...");
            glfwSetWindowSizeCallback(Gui::glResizeWnd);
            Gui::getInstance().registerInput();

            #if defined(Linux_Release) || defined(Windows_Release) || defined(_RELEASE)
                glfwDisable(GLFW_MOUSE_CURSOR);
            #endif
            
            mainMenu = new Window(333, 200, 135, 200, "Main Menu");
            
            Button* btn = new Button(30, 40, 75, 25, "Campaing");
            btn->setName("campaing");
            btn->onPressed.connect(bind(&PGameSession::onAction, this, _1));
            btn->setFocusIndex(1);
            mainMenu->AddComponent(btn);

            btn = new Button(30, 75, 75, 25, "Freeplay");
            btn->setName("freeplay");
            btn->onPressed.connect(bind(&PGameSession::onAction, this, _1));
            btn->setFocusIndex(2);
            mainMenu->AddComponent(btn);

			btn = new Button(30, 110, 75, 25, "Credits");
            btn->setName("credits");
            btn->onPressed.connect(bind(&PGameSession::onAction, this, _1));
            btn->setFocusIndex(3);
            mainMenu->AddComponent(btn);

            btn = new Button(30, 145, 75, 25, "Exit");
            btn->setName("guiExit");
            btn->onPressed.connect(bind(&PGameSession::onAction, this, _1));
            btn->setFocusIndex(4);
            mainMenu->AddComponent(btn);
            
            Gui::getInstance().addWindow(mainMenu);

            freeMenu = new Window(235, 200, 330, 200, "Freeplay");
            freeMenu->setVisible(false);

            listbox = new ListBox(10,36,200,132);
            listbox->KeyUp.connect(bind(&PGameSession::onKeyClick, this, _1, _2));
            listbox->setFocusIndex(1);
            path dir_path("data");
            if(exists(dir_path)){
                    directory_iterator end_itr; // default construction yields past-the-end
                    for (directory_iterator itr(dir_path);itr != end_itr; ++itr )
                    {
                      if ( !is_directory(*itr) && extension(*itr) == ".lvl" )
                      {
                            string filename = itr->path().leaf();
                            listbox->addItem(filename.substr(0,filename.find_last_of('.')));
                      }
                    }
            } else {
                    Messages::infoMessage("WARNING - Cannot find data directory!");
            }
            freeMenu->AddComponent(listbox);

            btn = new Button(230,40,75,25,"Play");
            btn->setName("play");
            btn->setFocusIndex(2);
            btn->onPressed.connect(bind(&PGameSession::onAction, this, _1));
            freeMenu->AddComponent(btn);

            btn = new Button(230,70,75,25,"Back");
            btn->setName("back");
            btn->setFocusIndex(3);
            btn->onPressed.connect(bind(&PGameSession::onAction, this, _1));
            freeMenu->AddComponent(btn);

            Gui::getInstance().addWindow(freeMenu);
            
            gameMenu = new Window(253, 158, 135, 165, "Menu");
            gameMenu->setVisible(false);
            gameMenu->setEnableCloseButton(false);

            btn = new Button(30, 40, 75, 25, "Save");
            btn->setName("save");
            btn->setFocusIndex(1);
            btn->onPressed.connect(bind(&PGameSession::onAction, this, _1));
            gameMenu->AddComponent(btn);

            btn = new Button(30, 75, 75, 25, "Reset");
            btn->setName("reset");
            btn->setFocusIndex(2);
            btn->onPressed.connect(bind(&PGameSession::onAction, this, _1));
            gameMenu->AddComponent(btn);

            btn = new Button(30, 110, 75, 25, "Exit");
            btn->setName("gameExit");
            btn->setFocusIndex(3);
            btn->onPressed.connect(bind(&PGameSession::onAction, this, _1));
            gameMenu->AddComponent(btn);

			Gui::getInstance().addWindow(gameMenu);

			Text* label = new Text(25,35,"Programmers:\nAljosa Osep\nJernej Skrabec\nJernej Halozan\nMartin Savc\n\nLevel designers:\nCrtomir Osep\nNevena Sreckovic");
			int width = label->getSize().width;
			int height = label->getSize().height;
			
			creditsWnd = new Window(400-width/2-25,300-height/2-45,width+50,height+90,"Credits");
			creditsWnd->setVisible(false);
			creditsWnd->AddComponent(label);
			
			btn = new Button(width/2,height+50,50,25,"OK");
			btn->setName("creditsBack");
			btn->onPressed.connect(bind(&PGameSession::onAction, this, _1));
			
			creditsWnd->AddComponent(btn);
            
            Gui::getInstance().addWindow(creditsWnd);
        }
            
        void PGameSession::mainLoop()
        {
            Messages::infoMessage("Entering main loop...");

            // the time of the previous frame
            double old_time = glfwGetTime();   
            double old_time_FPS = old_time;

            #if defined(Linux_Debug) || defined(Windows_Debug) || defined(_DEBUG)
                unsigned frames = 0;
                string title;
            #endif
            
            unsigned msgid = 0;
            bool menuVisible = false;
            
            //RenderMaschine::PParticleEngine particles(5.0, 7.0, 9.0);

            while(!gameQuit)
            {
                double current_time = glfwGetTime();
                double diff_time = current_time - old_time;
                old_time = current_time;

                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glLoadIdentity(); // reset view matrix

                #if defined(Linux_Debug) || defined(Windows_Debug) || defined(_DEBUG)
                    if(current_time - old_time_FPS >= 1){
                      title = "xSoko project FPS: " + Functions::toString<int>(frames);
                      glfwSetWindowTitle(title.c_str());
                      old_time_FPS = current_time;
                      frames = 0;
                    } else
                        frames ++;
                #endif
                
                

                if(levelLoaded || msgid){
                    Gui::getInstance().unregisterInput();
                    // calculate time elapsed, and the amount by which stuff rotates
                    //delta_rotate = (current_time - old_time) * rotations_per_tick * 360;

                    //if no win message is shown, check for input etc.
                    if(!msgid){

                        this->level->processBombs(current_time);

                        // check for input every time
                        this->input->process();

                        if(this->input->toggleGameMenu() != menuVisible){
                            menuVisible = !menuVisible;
                            gameMenu->setVisible(menuVisible);
                            Gui::getInstance().setMouseVisible(menuVisible);
                        }

                        // is game over? or level done?
                        if(this->level->getEndgameFlag() || forceLevelQuit){
                            levelLoaded = false;
                            gameMenu->setVisible(false);
                            if(level->getEndgameFlag())
								msgid = Gui::getInstance().showMessage("xSoko", "Congratulations, you won!");
                            else
                               mainMenu->setVisible(true);
                            Gui::getInstance().setMouseVisible(true);
                        }

                    }

                    gluLookAt(this->camera->view.getCoordX(), this->camera->view.getCoordY(), this->camera->view.getCoordZ(),
                            this->camera->position.getCoordX(), this->camera->position.getCoordY(), this->camera->position.getCoordZ(),
                            this->camera->up.getCoordX(), this->camera->up.getCoordY(), this->camera->up.getCoordZ());

                    glRotatef(-90.0, 0.0, 0.0, 1.0);
                    this->level->animate(diff_time);
                    this->level->draw();
                    

                    //particles.process(delta_rotate*10);
                }

                if(msgid && !Gui::getInstance().isMessageActive(msgid)){
                        msgid = 0;
                        mainMenu->setVisible(true);
                }

                Gui::getInstance().registerInput();
                Gui::getInstance().Render();

                if(levelLoaded || msgid){
                    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
                    glLoadIdentity();                                                         // Reset The Projection Matrix
                    // Calculate The Aspect Ratio Of The Window
                    gluPerspective(45.0f,640.0f/480,0.1f,100.0f);
                    glMatrixMode(GL_MODELVIEW);						// Select The Modelview Matrix
                    glLoadIdentity();
                    // Aljosa: two lines that follows are blend-gui-to-game fix ;)
                    //glEnable(GL_DEPTH_TEST);    // after drawing GUI, enable depth test
                    //glEnable(GL_BLEND);         // and blending
                }
              
                glfwSwapBuffers();
            }
        }
        
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
        /*void PGameSession::setScore(unsigned score)
        {
            this->score = score;
        }*/
        
     /*   void PGameSession::setGameEnd()
        {
            this->isGameRunning = false;
        }*/
        
        // getters
        // return current level
        /*PLevel* PGameSession::getLevel() const
        {
            return this->level;
        }*/
        
        // returns score
        /*unsigned PGameSession::getScore() const
        {
            return this->score;
        }*/
        
        void PGameSession::LoadLevel(string levelPath){

            //removeCallBacks();
            //gui.unregisterInput();
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

            //this->camera->fitCameraToLevel(this->level->getWidth(), this->level->getHeight());        // moved to PLevel::reloadLevel()
			input->closeGameMenu();
            levelLoaded = true;
            forceLevelQuit = false;
            Gui::getInstance().setMouseVisible(false);
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
			if(button->getName() == "credits"){
                mainMenu->setVisible(false);
                creditsWnd->setVisible(true);
                return;
            }
            if(button->getName() == "guiExit"){
                gameQuit = true;
                return;
            }
			if(button->getName() == "creditsBack"){
				creditsWnd->setVisible(false);
                mainMenu->setVisible(true);
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
                Gui::getInstance().setMouseVisible(false);
                gameMenu->setVisible(false);
		input->closeGameMenu();
                return;
            }
            if(button->getName() == "gameExit"){
                forceLevelQuit = true;
                return;
            }
        }

        PGameSession::~PGameSession()
        {
            //delete freeMenu;
            //delete gameMenu;
            //delete mainMenu;
            #if defined(Linux_Release) || defined(Windows_Release) || defined(_RELEASE)
                glfwEnable(GLFW_MOUSE_CURSOR);
            #endif
        }

        void PGameSession::onKeyClick(Component* listBox, int key){
            switch(key){
                case GLFW_KEY_ENTER:
                    listBox->setName("play");
                    onAction(listBox);
                    break;
                case GLFW_KEY_ESC:
                    listBox->setName("back");
                    onAction(listBox);
                    break;
            }
        }
    }
}
