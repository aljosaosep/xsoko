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
        class PTextureResource
        {
        private:
            string filename;
            PTexture *texture;
 
        public:
            PTextureResource(string filename) : filename(filename) {}
            PTextureResource() : texture(NULL) {}
            ~PTextureResource();
            
            // setters
            void setTexture(PTexture *tex);
            void setFilename(string filename);
            
            // other
            bool load();
            unsigned getId();
            void release();
        };
            
        
        class PResourceManager
        {
        private:
            PTextureResource *textures[ELEMENTS_TEXTURES];
            
        public:
            PResourceManager();
            ~PResourceManager();
            bool loadTextureResource(PTextureResource **res, string file);
            bool loadTextureResource(int offset, string file);
            
            PTextureResource* getTextureResource(int offset);
            unsigned getTextureTesourceId(int offset);

            void release();
        }; 
    }
}

#endif	/* _RESOURCE_H */
