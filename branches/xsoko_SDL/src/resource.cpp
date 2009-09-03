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

#include "resource.h"

#include <fstream>

using namespace std;

namespace PacGame
{
    namespace GameClasses
    {
        /******************************
         * PTextureManager resources
         *****************************/
        PResourceManager::PResourceManager()
        {
            for(int i=0; i<ELEMENTS_TEXTURES; textures[i++]=NULL); 
            for(int i=0; i<ELEMENTS_MODELS; models[i++]=NULL); 
        }
        
        PResourceManager::~PResourceManager()
        {
            this->release();
        }
        
        bool PResourceManager::loadTextureResource(PTexture **res, string file)
        {
            *res = new PTexture(file);
            
            if(!(*res)->makeTgaTexture(true))
       //     if(!(*res)->load())
            {
                cout<<"Error loading "<<(*res)->getFilename()<<endl;  // failed
                (*res)->release();
                delete [] (*res);
                (*res) = NULL;
                return false;
            }
            
            return true;
        }
        
        bool PResourceManager::loadTextureResource(int offset, string file)
        {
            textures[offset] = new PTexture(file);
            if(!((textures[offset])->makeTgaTexture(true)))
            {
                cout<<"Error loading "<<textures[offset]->getFilename()<<endl;  // failed
                (textures[offset])->release();
                delete [] textures[offset];
                textures[offset] = NULL;
                return false;
            }

            return true;
        }
        
        /**************************************************
         * loadModelResource
         * 
         * Loads an md2model from the file into the table at offset.
         * ************************************************/
        bool PResourceManager::loadModelResource(int offset, string fileName)
        {
                ifstream file(fileName.c_str(), ios_base::binary | ios_base::in);
                if(file.is_open())
                {
                        models[offset] = new Md2Model(file);
                        return true;
                }else
                        return false;
        }
        
        /***********************************************
         * getModelResource
         * 
         * Return a pointer to the model resource.
         * **********************************************/
        Md2Model* PResourceManager::getModelResource(int offset)
        {
                return models[offset];
        }
        
        // getters
        PTexture* PResourceManager::getTextureResource(int offset)
        {
            return this->textures[offset];
        }
        
        unsigned PResourceManager::getTextureTesourceId(int offset)
        {
            return this->textures[offset]->getId();
        }
        
        void PResourceManager::release()
        {
            // release textures
            for(int i=0; i<ELEMENTS_TEXTURES; i++)
            {
                if(this->textures[i]!=NULL)
                {
                    textures[i]->release();
                    delete textures[i];
                    textures[i] = NULL;
                }
            }
            // release models
            for(int i=0; i<ELEMENTS_MODELS; i++)
            {
                if(this->models[i]!=NULL)
                {
                    delete models[i];
                    models[i] = NULL;
                }
            }
        }
    }
}
