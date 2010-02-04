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
 * File: game.cpp
 *
 * Summary:
 * Includes game core implementation
 *
 * Author: Aljosa Osep 2007
 * Changes:
 * Aljosa May 28 2008
 */

#include "game.h"
//#include <AL/alut.h>
//#include "renderer/particle.h"
#include <cstdio>
#include <cmath>
#include "gui/forms.h"
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include "config.h"


using namespace PacGame;

namespace PacGame
{
      namespace GameClasses
      {
          // constructors
          PGame::PGame() :
            level(NULL), player(NULL), camera(NULL), input(new PInputSystem()),
            rotations_per_tick(0.1), levelLoaded(false), gameQuit(false)
          { }

          bool PGame::initialize(int _width, int _height, string _title)
          {
              Messages::mainTitleMessage();
              windowTitle = _title;

              if (SDL_Init(SDL_INIT_VIDEO) != 0)  // was SDL initialization successful?
              {
                  Messages::initMessage("SDL", false); // in case, it is not
                  terminate(); // terminate and return false
                  return false;
              }

              Messages::initMessage("SDL", true); // prints out that initialization was success

              if(!Config::ReadConfig("xsoko.conf"))
              {
                  Messages::errorMessage("Reading configuration file failed! (NOTE: this is ok at first run)");
                  Config::SetValueInt("xres",_width);
                  Config::SetValueInt("yres",_height);
                  Config::SetValueBool("fullscreen",false);
              }

              windowWidth = Config::GetValueInt("xres");
              windowHeight = Config::GetValueInt("yres");
              fullscreen = Config::GetValueBool("fullscreen");
              unsigned flag = fullscreen ? SDL_FULLSCREEN : 0;

              SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
              SDL_Surface* screen = SDL_SetVideoMode( windowWidth, windowHeight, 32, SDL_OPENGL | flag );

              // 800 x 600, 16 bit color, no depth, alpha or stencil buffers, windowed
              if (screen == NULL)
              {
				  Messages::infoMessage("OpenGL window creation failed. Reverting to default mode.");
				  // could not create OpenGL screen, try default mode
				  Config::SetValueInt("xres",_width);
                  Config::SetValueInt("yres",_height);
                  Config::SetValueBool("fullscreen",false);
				  windowWidth = _width;
				  windowHeight = _height;
				  fullscreen = false;
				  flag = fullscreen ? SDL_FULLSCREEN : 0;
				  screen = SDL_SetVideoMode( windowWidth, windowHeight, 32, SDL_OPENGL | flag );

					// default mode did not work either, exit
                  if (screen == NULL)
				  {
					Messages::errorMessage("OpenGL window creation failed.");  // failed
					terminate();
					return false;
				  }
              }

              Messages::initMessage("OpenGL window", true);  // prints out success
              SDL_WM_SetCaption(this->windowTitle.c_str(),this->windowTitle.c_str());

              prepareGui();

              //alutInit (NULL, NULL); // inicializacija ALUT in OpenAL API
              //alGetError(); // počisti napake

              Messages::initMessage("Game", true);
              return true;
          }

          void PGame::quit(){
              gameQuit = true;
              cout<<"set gameQuit flag"<<endl;
          }

          void PGame::setResolution(int width, int height, bool fullscreen)
          {
              bool isChange = false;

              if(fullscreen != this->fullscreen)
              {
                  this->fullscreen = fullscreen;
                  isChange = true;
              }
              unsigned flag = fullscreen ? SDL_FULLSCREEN : 0;

              if((windowWidth != width) || (windowHeight != height))
              {
                  windowWidth = width;
                  windowHeight = height;
                  isChange = true;
              }

              if(isChange)
              {
                  if(SDL_SetVideoMode( width, height, 32, SDL_OPENGL | flag ))
                      Gui::getInstance().onResolutionChange(width,height);
		  #ifdef _WINDOWS
                    GuiRender::getInstance().reloadSkin();
		    FontManager::getInstance().reload();
		  #endif
                  Config::SetValueInt("xres",width);
                  Config::SetValueInt("yres",height);
                  Config::SetValueBool("fullscreen",fullscreen);
              }
          }
          
          void PGame::mainLoop()
          {
            Messages::infoMessage("Entering main loop...");

            // the time of the previous frame
            double old_time = ((double)SDL_GetTicks())/1000.0;//glfwGetTime();
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
                double current_time = ((double)SDL_GetTicks())/1000.0;//glfwGetTime();
                double diff_time = current_time - old_time;
                old_time = current_time;

                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glLoadIdentity(); // reset view matrix

                #if defined(Linux_Debug) || defined(Windows_Debug) || defined(_DEBUG)
                    if(current_time - old_time_FPS >= 1){
                      title = "xSoko project FPS: " + Functions::toString<int>(frames);
                      // the second argument is the title of the minimized window
                      SDL_WM_SetCaption(title.c_str(), title.c_str());//glfwSetWindowTitle(title.c_str());
                      old_time_FPS = current_time;
                      frames = 0;
                    } else
                        frames ++;
                #endif

                 this->input->process();


                if(levelLoaded || msgid){
                    //Gui::getInstance().unregisterInput();
                    // calculate time elapsed, and the amount by which stuff rotates
                    //delta_rotate = (current_time - old_time) * rotations_per_tick * 360;

                    //if no win message is shown, check for input etc.
                    if(!msgid){

                        this->level->processBombs(current_time);

                        // check for input every time
                       // this->input->process();

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
                            {
                                                                msgid = Gui::getInstance().showMessage("xSoko", "Congratulations, you won!");
                                                                // openGameMenu switches controls to GUI
                                                                input->openGameMenu();
                                                                Messages::infoMessage("You won!");
                            }else
                               mainMenu->setVisible(true);
                            Gui::getInstance().setMouseVisible(true);
                        }

                    }

                   PResourceManager *rm =  this->level->getGameCoreHandle()->getResources();
                    // FRONT, BACK, LEFT, RIGHT, TOP, BOTTOM
                    int texIDs[] = { rm->getTextureTesourceId(SKY_RES_FRONT),
                                rm->getTextureTesourceId(SKY_RES_BACK),
                                rm->getTextureTesourceId(SKY_RES_LEFT),
                                rm->getTextureTesourceId(SKY_RES_RIGHT),
                                rm->getTextureTesourceId(SKY_RES_TOP),
                                rm->getTextureTesourceId(SKY_RES_BOTTOM) };
                    this->level->getGameCoreHandle()->getRenderer()->drawSkyCube(0.0f, 0.0f, -15.0f, 30.0f, texIDs);

                    gluLookAt(this->camera->view.getCoordX(), this->camera->view.getCoordY(), this->camera->view.getCoordZ(),
                            this->camera->position.getCoordX(), this->camera->position.getCoordY(), this->camera->position.getCoordZ(),
                            this->camera->up.getCoordX(), this->camera->up.getCoordY(), this->camera->up.getCoordZ());

                    //this->level->getGameCoreHandle()->getResources()

                    glRotatef(-90.0, 0.0, 0.0, 1.0);
                    this->level->animate(diff_time);
                    this->level->draw();


                    //particles.process(delta_rotate*10);
                }

                if(msgid && !Gui::getInstance().isMessageActive(msgid)){
                        msgid = 0;
                        mainMenu->setVisible(true);
                }

                //Gui::getInstance().registerInput();
                Gui::getInstance().Render();

                if(levelLoaded || msgid){
                    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
                    glLoadIdentity();                                                         // Reset The Projection Matrix
                    // Calculate The Aspect Ratio Of The Window
                    gluPerspective(45.0f,windowWidth/(float)windowHeight,0.1f,100.0f);
                    glMatrixMode(GL_MODELVIEW);						// Select The Modelview Matrix
                    glLoadIdentity();
                }

                SDL_GL_SwapBuffers();
            }
          }

          void PGame::terminate()
          {
               Messages::infoMessage("Termination...");
               if(!Config::SaveConfig("xsoko.conf"))
               {
                   Messages::errorMessage("Writing configuration file failed! Changes will NOT be saved!");
               }
               #if defined(Linux_Release) || defined(Windows_Release) || defined(_RELEASE)
                  SDL_ShowCursor(SDL_ENABLE);
               #endif
               //alutExit ();
               SDL_Quit();
          }
          
          void PGame::loadLevel(string levelPath){
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
          }
          
          void PGame::resetLevel(){
                  if(level != NULL)
                  {
                          level->reset();
                          input->closeGameMenu();
                  }
          }
          
          void PGame::exitLevel(){
                  if(level != NULL)
                  {
                        delete level;     
                        level = NULL;
                        levelLoaded = false;
                        gameMenu->setVisible(false);
                         mainMenu->setVisible(true);
                  }
          }

          void PGame::prepareGui(){
            Messages::infoMessage("Initialiazing GUI...");
            const SDL_VideoInfo* vi = SDL_GetVideoInfo();
            Gui::getInstance().onResolutionChange(vi->current_w, vi->current_h);
            //Gui::getInstance().registerInput();
            //input->toggleGameMenu();
            #if defined(Linux_Release) || defined(Windows_Release) || defined(_RELEASE)
                SDL_ShowCursor(SDL_DISABLE);
            #endif

            mainMenu = new MainMenu();
            gameMenu = new GameMenu();
            Gui::getInstance().addWindow(mainMenu);
            Gui::getInstance().addWindow(new FreeplayWnd());
            Gui::getInstance().addWindow(gameMenu);
            Gui::getInstance().addWindow(new CreditsWnd());
            Gui::getInstance().addWindow(new OptionsWnd());
          }

          PGame& PGame::getInstance(){
              static PGame game;
              return game;
          }
      }
}
