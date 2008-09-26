#include "resource.h"


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
        }
    }
}
