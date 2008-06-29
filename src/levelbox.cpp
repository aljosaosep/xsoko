/*
 * Codename: xSoko
 * File: levelbox.cpp
 *
 * Summary:
 * Includes levelbox objects implementation
 *
 * Author: Aljosa Osep 2008
*/

#include "levelbox.h"
#include "level.h"


namespace PacGame
{
    namespace GameClasses
    {
        /*****************************************
         PLevelBox methods
         *****************************************/			  
        void PLevelObject::setIndex(unsigned i, unsigned j) // index setter
        {
                this->i = i;
                this->j = j;
        }

        void PLevelObject::setI(unsigned i)  // i index setter
        {
                this->i = i;
        }

        void PLevelObject::setJ(unsigned j)  // j index setter
        {
                this->j = j;
        }

        unsigned PLevelObject::getI() const  // i index getter
        {
                return this->i;
        }

        unsigned PLevelObject::getJ() const  // j index getter
        {
                return this->j;
        }
          
        unsigned short PLevelObject::getId() const
        {
            return id;
        }

        void PLevelObject::getIndex(unsigned &i, unsigned &j)  // both index getter
        {
                i = this->i;
                j = this->j;
        }
          
          
        /*****************************************
         PTeleport methods
         *****************************************/	
        // TODO: implement
        bool PTeleport::initialize()
        {
            return true;
        }
        
        void PTeleport::draw()
        {

        }
        
        void PTeleport::print()
        {

        }
    }
}


