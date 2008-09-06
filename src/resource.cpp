
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
               // this->texture->release();
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
        
        int PTextureResource::getId()
        {
            return this->texture->getTexID();
        }
        
        /******************************
         * PTextureManager resources
         *****************************/
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
        
        void PResourceManager::release()
        {
        
        }
    }
}
