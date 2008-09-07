
#include "resource.h"

#include "resource.h"

namespace PacGame
{
    namespace GameClasses
    {
        /******************************
         * PTextureResource class
         *****************************/
        PTextureResource::~PTextureResource()
        {
            this->release();
        }
        
        void PTextureResource::release()
        {
            if(this->texture!=NULL)
            {
                this->texture->release();
                delete [] this->texture;
                this->texture = NULL;
            }
        }
        
        void PTextureResource::setFilename(string filename)
        {
            this->filename = filename;
        }
        
        void PTextureResource::setTexture(PTexture *tex)
        {
            this->texture = tex;
        }
        
        bool PTextureResource::load()
        {
            // create new object for texture
            this->texture = new PTexture(this->filename); // create object
            //  this->texture->setPath(filename);
            if(!this->texture->makeTgaTexture(true))  // create texture(generate)
            {
                cout<<"Error loading "<<this->filename<<endl;  // failed
                delete [] texture;  // delete object from memory
                return false;
            }
            
            return true; // ok :)
        }
        
        unsigned PTextureResource::getId()
        {
            return this->texture->getTexID();
        }
        
        /******************************
         * PTextureManager resources
         *****************************/
        PResourceManager::PResourceManager()
        {
            for(int i=0; i<ELEMENTS_TEXTURES; textures[i++]=NULL); 
        }
        
        PResourceManager::~PResourceManager()
        {
            this->release();
        }
        
        bool PResourceManager::loadTextureResource(PTextureResource **res, string file)
        {
            *res = new PTextureResource(file);
            if(!(*res)->load())
            {
                (*res)->release();
                delete [] (*res);
                (*res) = NULL;
                return false;
            }
            
            return true;
        }
        
        bool PResourceManager::loadTextureResource(int offset, string file)
        {
            textures[offset] = new PTextureResource(file);
            if(!((textures[offset])->load()))
            {
                (textures[offset])->release();
                delete [] textures[offset];
                textures[offset] = NULL;
                return false;
            }

            return true;
        }
        
        // getters
        PTextureResource* PResourceManager::getTextureResource(int offset)
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
        }
    }
}
