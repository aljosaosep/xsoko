/* 
 * File:   resource.h
 * Author: aljosa
 *
 * Created on August 24, 2008, 8:41 PM
 */

#ifndef __RESOURCE_H
#define	__RESOURCE_H

#include "renderer/texture.h"

#define ELEMENTS_TEXTURES 12

using namespace PacGame::RenderMaschine;

namespace PacGame
{
    namespace GameClasses
    {
        class PResourceManager
        {
        private:
            PTexture *textures[ELEMENTS_TEXTURES];
            
        public:
            PResourceManager();
            ~PResourceManager();
            bool loadTextureResource(PTexture **res, string file);
            bool loadTextureResource(int offset, string file);
            
            PTexture* getTextureResource(int offset);
            unsigned getTextureTesourceId(int offset);

            void release();
        }; 
    }
}

#endif	/* _RESOURCE_H */
