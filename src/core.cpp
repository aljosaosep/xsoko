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
                delete [] renderer;
                this->renderer = NULL;
            }
          
            // release and delete resources
            if(resources!=NULL)
            {
                this->resources->release();
                delete [] resources;
                this->resources = NULL;
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
        
    }
}
