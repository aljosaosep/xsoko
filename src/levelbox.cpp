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
        
        void PLevelObject::print()
        {
            cout<<this->id<<' ';
        }
       
        
        /*****************************************
         
         * MATRIX I. ELEMENTS METHODS IMPLEMENTATION
         *
         *****************************************/
          
        /*****************************************
         PTeleport methods
         *****************************************/
        // setters
        void PTeleport::setId(int id)
        {
            this->teleport_id = id;
        }
        
        // getters
        int PTeleport::getId() const
        {
            return this->teleport_id;
        }
        
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
            cout<<"|  T  ";
        }
        
        /*****************************************
         PFloor methods
         *****************************************/	
        // TODO: implement
        bool PFloor::initialize()
        {
            return true;
        }
        
        void PFloor::draw()
        {

        }
        
        void PFloor::print()
        {
            cout<<"|  F  ";
        }
        
        /*****************************************
         POnewayFloor methods
         *****************************************/	
        // TODO: implement
        bool POnewayFloor::initialize()
        {
            return true;
        }
        
        void POnewayFloor::draw()
        {

        }
        
        void POnewayFloor::print()
        {
            cout<<"| OWF ";
        }
        
        /*****************************************
         PSolidWall methods
         *****************************************/	
        // TODO: implement
        bool PSolidWall::initialize()
        {
            return true;
        }
        
        void PSolidWall::draw()
        {

        }
        
        void PSolidWall::print()
        {
            cout<<"| SW  ";
        }
        
        /*****************************************
         PUnsolidWall methods
         *****************************************/	
        // TODO: implement
        bool PUnsolidWall::initialize()
        {
            return true;
        }
        
        void PUnsolidWall::draw()
        {

        }
        
        void PUnsolidWall::print()
        {
            cout<<"| USW ";
        }  
        
        /*****************************************
         PBridge methods
         *****************************************/	
        // TODO: implement
        bool PBridge::initialize()
        {
            return true;
        }
        
        void PBridge::draw()
        {

        }
        
        void PBridge::print()
        {
            cout<<"|  B  ";
        } 
        
        /*****************************************
         PVoid methods
         *****************************************/	
        // TODO: implement
        bool PVoid::initialize()
        {
            return true;
        }
        
        void PVoid::draw()
        {

        }
        
        void PVoid::print()
        {
            cout<<"|XXXXX";
        } 
        
        /*****************************************
         PCubeHolder methods
         *****************************************/	
        // TODO: implement
        bool PCubeHolder::initialize()
        {
            return true;
        }
        
        void PCubeHolder::draw()
        {

        }
        
        void PCubeHolder::print()
        {
            cout<<"| CH  ";
        }  
        
        /*****************************************
         
         * MATRIX II. ELEMENTS METHODS IMPLEMENTATION
         *
         *****************************************/
        /*****************************************
         PCube methods
         *****************************************/	
        // TODO: implement
        bool PCube::initialize()
        {
            return true;
        }
        
        void PCube::draw()
        {

        }
        
        void PCube::print()
        {
            cout<<"|  C  ";
        } 
        
        /*****************************************
         POnewayCube methods
         *****************************************/	
        // TODO: implement
        bool POnewayCube::initialize()
        {
            return true;
        }
        
        void POnewayCube::draw()
        {

        }
        
        void POnewayCube::print()
        {
            cout<<"| OWC ";
        } 
        
        /*****************************************
         PBomb methods
         *****************************************/	
        // TODO: implement
        bool PBomb::initialize()
        {
            return true;
        }
        
        void PBomb::draw()
        {

        }
        
        void PBomb::print()
        {
            cout<<"|  B  ";
        } 
        
        /*****************************************
         PNoData methods
         *****************************************/
        void PNoData::print()
        {
            cout<<"|_NULL";
        } 
        
        
        /*****************************************
         PData methods
         *****************************************/
     /*   template<class T>
        void PData::print()
        {
            cout<<"|DAT"<<this->data;
        } 
        
        // in this class, this two methods exists just because they must me owerwritten
        bool PData::initialize() { return true; }
        void PData::draw() {}*/

    }
}

