/* 
 * File:   resource.h
 * Author: aljosa
 *
 * Created on August 24, 2008, 8:41 PM
 */

#ifndef __RESOURCE_H
#define	__RESOURCE_H

#include "renderer/texture.h"

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
            int getId();
            void release();
        };
            
        
        class PResourceManager
        {
        private:
        public:
            bool loadTextureResource(PTextureResource **res, string file);
            
            PTextureResource *solidWall;
            
            void release();
            
        }; 
    }
}

#endif	/* _RESOURCE_H */
