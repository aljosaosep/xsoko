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
        void PLevelObject::setIndex(int i, int j) // index setter
        {
                this->i = i;
                this->j = j;
        }

        void PLevelObject::setI(int i)  // i index setter
        {
                this->i = i;
        }

        void PLevelObject::setJ(int j)  // j index setter
        {
                this->j = j;
        }

        int PLevelObject::getI() const  // i index getter
        {
                return this->i;
        }

        int PLevelObject::getJ() const  // j index getter
        {
                return this->j;
        }
          
        unsigned short PLevelObject::getId() const
        {
            return id;
        }

      /*  void PLevelObject::getIndex(unsigned &i, unsigned &j)  // both index getter
        {
                i = this->i;
                j = this->j;
        }*/
        
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
        int PTeleport::getId() 
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
            cout<<"| T"<<this->teleport_id<<' ';
        }
        
        short PTeleport::isPlayerMovePossible()
        {
            /// tmp
            return 0;            
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
        
        short PFloor::isPlayerMovePossible() 
        {
            return 1;
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
        
        short POnewayFloor::isPlayerMovePossible() 
        {
            /// tmp
            return 0;
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

        short PSolidWall::isPlayerMovePossible() 
        {
            return 0;
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
        
        short PUnsolidWall::isPlayerMovePossible() 
        {
            /// tmp
            return 0;
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
        
        short PBridge::isPlayerMovePossible() 
        {
            /// tmp
            return 0;
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
            cout<<"|     ";
        } 
        
        short PVoid::isPlayerMovePossible() 
        {
            /// tmp
            return 0;
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
        
        short PCubeHolder::isPlayerMovePossible() 
        {
            /// tmp
            return 0;
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
        
    /*    short PCube::isPlayerMovePossible() 
        {
            /// tmp
            return 0;
        }*/
        
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

    /*    short POnewayCube::isPlayerMovePossible() 
        {
            /// tmp
            return 0;
        }*/
        
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
        
     /*   short POnewayFloor::isPlayerMovePossible() 
        {
            /// tmp
            return f;
        }*/
        
        /*****************************************
         PNoData methods
         *****************************************/
     /*   void PNoData::print()
        {
            cout<<"|_NULL";
        } */
        
        
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

