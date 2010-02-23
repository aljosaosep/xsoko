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
#include <cstdio>
#include <cmath>
#include "gui/forms.h"
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <fstream>
#include "config.h"
#include "zip/zipfile.h"
#include <boost/filesystem.hpp>


using namespace PacGame;
using namespace boost::filesystem;

namespace PacGame
{
      namespace GameClasses
      {
          // constructors
          PGame::PGame() :
            gamepack(false), camera(NULL), levelLoaded(false), gameQuit(false)
          { }

          bool PGame::initialize(int _width, int _height, string _title)
          {
              Messages::mainTitleMessage();
              windowTitle = _title;

              #ifdef _WINDOWS
                  homepath = string(getenv("HOMEDRIVE")) + "\\" + string(getenv("HOMEPATH")) + "\.xsoko";
              #else
                  homepath = string(getenv("HOME")) + "/.xsoko";
              #endif
              path dir_path(homepath);
              if(!exists(dir_path) && !create_directory(dir_path)) {
                  Messages::errorMessage("Could not find home directory!");
                  return false;
              }

              if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)  // was SDL initialization successful?
              {
                  Messages::initMessage("SDL", false); // in case, it is not
                  Messages::initMessage("SDL audio", false); // in case, it is not
                  terminate(); // terminate and return false
                  return false;
              }

              Messages::initMessage("SDL", true); // prints out that initialization was success
              Messages::initMessage("SDL audio", true);

              if(!Config::ReadConfig(homepath + "/xsoko.conf"))
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

              Messages::infoMessage("Initialiazing GUI...");
              const SDL_VideoInfo* vi = SDL_GetVideoInfo();
              Gui::getInst().onResolutionChange(vi->current_w, vi->current_h);
              #if defined(Linux_Release) || defined(Windows_Release) || defined(_RELEASE)
                  SDL_ShowCursor(SDL_DISABLE);
              #endif

              mainMenu = new MainMenu();
              gameMenu = new GameMenu();

              sm = SoundManager();
              sm.loadEffect("bomb","data/sound/bombtiq.wav"); //TODO: nalaganje soudna bombe se naj izvede samo, če so kake bombe v levelu
              sm.loadMusic("guardian","data/sound/mirror.mp3");
              //sm.playMusic("guardian");
              sm.loadMusic("mortal","data/sound/mortal_kombat.mp3");
              sm.playMusic("mortal");

              level.reset(new PLevel());
              level->initialize();
              input.setLevel(level.get());
              camera = level->getGameCoreHandle()->getCamera();

              Messages::initMessage("Game", true);
              return true;
          }

          void PGame::quit(){
              gameQuit = true;
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
                      Gui::getInst().onResolutionChange(width,height);
		  #ifdef _WINDOWS
                    GuiRender::getInstance().reloadSkin();
		    FontManager::getInstance().reload();
                    level.reset(new PLevel());
                    input.setLevel(level.get());
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
            double old_time = ((double)SDL_GetTicks())/1000.0;
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

                 input.process();


                if(levelLoaded || msgid){

                    //if no win message is shown, check for input etc.
                    if(!msgid){

                        level->processBombs(current_time);

                        if(input.toggleGameMenu() != menuVisible){
                            menuVisible = !menuVisible;
                            gameMenu->setVisible(menuVisible);
                            Gui::getInst().setMouseVisible(menuVisible);
                        }

                        // is game over? or level done?
                        if(level->getEndgameFlag()) {
                            if(gamepack && curLevel < numLevels) {
                                zifstream file(pack,Functions::toString(++curLevel)+".lvl");
                                forceLevelQuit = file.good() ? !level->loadLevel(file) : true;
                                if(forceLevelQuit)
                                    Messages::errorMessage("Level loading failed!");
                            } else {
                                gamepack = false;
                                levelLoaded = false;
                                msgid = Gui::getInst().showMessage("xSoko", "Congratulations, you won!");
                                // openGameMenu switches controls to GUI
                                input.openGameMenu();
                                Messages::infoMessage("You won!");
                                Gui::getInst().setMouseVisible(true);
                            }
                        }
                        if(forceLevelQuit) {
                            gamepack = false;
                            levelLoaded = false;
                            gameMenu->setVisible(false);
                            mainMenu->setVisible(true);
                            input.openGameMenu();
                            Gui::getInst().setMouseVisible(true);
                        }

                    }

                    PResourceManager *rm = level->getGameCoreHandle()->getResources();
                    // FRONT, BACK, LEFT, RIGHT, TOP, BOTTOM
                    int texIDs[] = { rm->getTextureTesourceId(SKY_RES_FRONT)/*,
                                rm->getTextureTesourceId(SKY_RES_BACK),
                                rm->getTextureTesourceId(SKY_RES_LEFT),
                                rm->getTextureTesourceId(SKY_RES_RIGHT),
                                rm->getTextureTesourceId(SKY_RES_TOP),
                                rm->getTextureTesourceId(SKY_RES_BOTTOM) */};
                    level->getGameCoreHandle()->getRenderer()->drawSkyCube(0.0f, 0.0f, -55.0f, 40.0f, texIDs);

                    gluLookAt(this->camera->view.getCoordX(), this->camera->view.getCoordY(), this->camera->view.getCoordZ(),
                            this->camera->position.getCoordX(), this->camera->position.getCoordY(), this->camera->position.getCoordZ(),
                            this->camera->up.getCoordX(), this->camera->up.getCoordY(), this->camera->up.getCoordZ());

                    //this->level->getGameCoreHandle()->getResources()

                    glRotatef(-90.0, 0.0, 0.0, 1.0);
                    this->level->animate(diff_time);
                    this->level->draw();


                    //particles.process(delta_rotate*10);
                }

                if(msgid && !Gui::getInst().isMessageActive(msgid)){
                        msgid = 0;
                        mainMenu->setVisible(true);
                }

                Gui::getInst().Render();

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
               if(!Config::SaveConfig(homepath + "/xsoko.conf"))
                   Messages::errorMessage("Writing configuration file failed! Changes will NOT be saved!");

               #if defined(Linux_Release) || defined(Windows_Release) || defined(_RELEASE)
                  SDL_ShowCursor(SDL_ENABLE);
               #endif
               SDL_Quit();
          }
          
          void PGame::loadLevel(string levelPath){
            ifstream file(levelPath.c_str());
            if(!level->loadLevel(file)) {
                Messages::errorMessage("Level loading failed!");
                mainMenu->setVisible(true);
                return;
            }
            file.close();

	    input.closeGameMenu();
            levelLoaded = true;
            forceLevelQuit = false;
            Gui::getInst().setMouseVisible(false);
          }

          void PGame::loadGamePack(string packPath) {
              zifstream info(packPath,"info.txt");
              info >> numLevels;
              if(numLevels > 0) {
                  zifstream file(packPath,"1.lvl");
                  if(file.good()) {
                      pack = packPath;
                      if(!level->loadLevel(file)) {
                          mainMenu->setVisible(true);
                          return;
                      }
                      curLevel = 1;
                      gamepack = true;
                      input.closeGameMenu();
                      levelLoaded = true;
                      forceLevelQuit = false;
                      Gui::getInst().setMouseVisible(false);
                      return;
                  }
              }
              Messages::errorMessage("Level loading failed!");
              mainMenu->setVisible(true);
          }
          
          void PGame::resetLevel(){
              level->reset();
              input.closeGameMenu();
          }
          
          void PGame::exitLevel(){
              levelLoaded = false;
              gameMenu->setVisible(false);
              mainMenu->setVisible(true);
          }

          PGame& PGame::getInstance(){
              static PGame game;
              return game;
          }

          SoundManager* PGame::getSoundManagerInstance()
          {
              return &sm;
          }
      }
}
