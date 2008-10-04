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
 * File:   core.h
 * Author: aljosa
 *
 * Created on September 05, 2008, 8:58 PM
 */

#include "core.h"

using namespace PacGame::RenderMaschine;

namespace PacGame
{
    namespace GameClasses
    {
        /*****************************************************************
         * Constructor
         * It creates objects
         *****************************************************************/
        PCore::PCore()
        {
            this->renderer = new PacGame::RenderMaschine::PRenderer;
            this->resources = new PResourceManager();
            this->camera = new PCamera;
        }
        
        /*****************************************************************
         * Destructor
         * It releases data from memory
         *****************************************************************/
        PCore::~PCore()
        {
            this->release();
        }
        
        /*****************************************************************
         * release()
         * Cleans core systems from memory
         *****************************************************************/ 
        void PCore::release()
        {
            // delete renderer
            if(renderer!=NULL)
            {
                delete renderer;
                this->renderer = NULL;
            }
          
            // release and delete resources
            if(resources!=NULL)
            {
                this->resources->release();
                delete resources;
                this->resources = NULL;
            }
            
            if(camera!=NULL)
            {
                delete camera;
                this->camera = NULL;
            }
        }
        
        /*****************************************************************
         * release()
         * Cleans core systems from memory
         *****************************************************************/ 
        bool PCore::init()
        {
            // initiates renderer
            if(!this->renderer->init())
            {
                this->release();
                Messages::initMessage("Renderer", false);
                return false;
            }
            else
                Messages::initMessage("Renderer", true);
            
            return true; // if everything is ok, return true
        }
        
        /*****************************************************************
         * getters
         *****************************************************************/ 
        PRenderer *PCore::getRenderer()
        {
            return this->renderer;
        }
        
        PResourceManager *PCore::getResources()
        {
            return this->resources;
        }
        
        PCamera *PCore::getCamera()
        {
            return this->camera;
        }
    }
}
