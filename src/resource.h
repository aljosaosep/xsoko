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
 * File:   resource.h
 * Author: aljosa
 *
 * Created on August 24, 2008, 8:41 PM
 * */

#ifndef __RESOURCE_H
#define	__RESOURCE_H

#include "renderer/texture.h"
#include "md2loader/md2model.h"
#include "LWObject.h"

#include <map>

#define ELEMENTS_TEXTURES 18 // 12 + 6 fpr skybox
#define ELEMENTS_MODELS 12
#define ELEMENTS_LWOBJECTS 2

using namespace PacGame::RenderMaschine;
using namespace PacGame::Md2Format;

namespace PacGame
{
    namespace GameClasses
    {
        class PResourceManager
        {
        private:
            PTexture *textures[ELEMENTS_TEXTURES];
            LWObject *lwos[ELEMENTS_LWOBJECTS];
            Md2Model *models[ELEMENTS_MODELS];             // Added by Martin Savc, Friday, June 19 2009
            map<string, /*PacGame::LWFormat::*/LWObject> modelsLW;
          //  map<string, > modelsLW;
        public:
            PResourceManager();
            ~PResourceManager();
            bool loadTextureResource(PTexture **res, string file);
            bool loadTextureResource(int offset, string file);
            
            PTexture* getTextureResource(int offset);
            unsigned getTextureTesourceId(int offset);
            
            bool loadModelResource(int offset, string fileName);             // Added by Martin Savc, Friday, June 19 2009
            bool loadLWOResource(int offset, string fileName);

            Md2Model* getModelResource(int offset);             // Added by Martin Savc, Friday, June 19 2009

            LWObject* getModelResourceLW(int offset);

            LWObject* getModelResourceLW(string fileName /*LWObject &objRef*/);

         //   void dropResources();


            void release();
        }; 
    }
}

#endif	/* _RESOURCE_H */
