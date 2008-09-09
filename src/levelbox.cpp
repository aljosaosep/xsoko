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
        
        void PTeleport::setChildTeleport(PTeleport *child)
        {
            this->childTeleport = child;
        }
        
        // getters
        int PTeleport::getId() 
        {
            return this->teleport_id;
        }
        
        PTeleport* PTeleport::getChildTeleport() const
        {
            return this->childTeleport;
        }
        
        // TODO: implement
        bool PTeleport::initialize()
        {
            return true;
        }
        
        void PTeleport::draw()
        {
            glColor4f(0.0, 0.0, 1.0, 0.4);
            glBindTexture(GL_TEXTURE_2D, this->core->getResources()->getTextureTesourceId(4));
            this->core->getRenderer()->drawCube(0.0, 0.0, 1.0, 0.0);
            
        }
        
        void PTeleport::print()
        {
            cout<<"| T"<<this->teleport_id<<' ';
        }

        short PTeleport::isPlayerMovePossible()
        {
            /// tmp
            return 3;            
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
            glColor3f(0.5, 0.5, 0.4);
            glBindTexture(GL_TEXTURE_2D, this->core->getResources()->getTextureTesourceId(0));
            this->core->getRenderer()->drawFloor(0.0, 0.0, 1.0);
        }
        
        void PFloor::print()
        {
            cout<<"|     ";
        }
        
        short PFloor::isPlayerMovePossible() 
        {
            return 2;
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
            glColor3f(0.5, 0.5, 0.4);
            switch(this->dir)
            {
                    case Aliases::left:
                        glRotatef(180.0, 0.0, 0.0, 1.0);
                        break;
                        
                    case Aliases::up:
                        glRotatef(90.0, 0.0, 0.0, 1.0);
                        break;
                            
                    case Aliases::down:
                        glRotatef(-90.0, 0.0, 0.0, 1.0);
                        break;
            }
            glBindTexture(GL_TEXTURE_2D, this->core->getResources()->getTextureTesourceId(10));
            this->core->getRenderer()->drawFloor(0.0, 0.0, 1.0);
        }
        
        void POnewayFloor::print()
        {
            cout<<"| OWF ";
        }      
        
        short POnewayFloor::isPlayerMovePossible() 
        {
            return 5;
        }
        
        Aliases::PDirection POnewayFloor::getDirection()
        {
            return this->dir;
        }
        
        void POnewayFloor::setDirection(Aliases::PDirection dir)
        {
            this->dir = dir;
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
            glColor3f(0.9, 0.9, 0.9);
            glBindTexture(GL_TEXTURE_2D, this->core->getResources()->getTextureTesourceId(2));
            this->core->getRenderer()->drawCube(0.0, 0.0, 1.0, 0.0);
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
            glColor4f(1.0, 1.0, 1.0, 0.5);
            glBindTexture(GL_TEXTURE_2D, this->core->getResources()->getTextureTesourceId(5));
            this->core->getRenderer()->drawFloor(0.0, 0.0, 1.0);

        }
        
        void PBridge::print()
        {
            cout<<"|  B  ";
        } 

        short PBridge::isPlayerMovePossible() 
        {
            return 2;
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
          //  glColor3f(0.0, 0.0, 0.0);
          //  this->renderer.drawFloor(0.0, 0.0, 1.0);
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
            glColor3f(0.3, 0.0, 0.0);
            glBindTexture(GL_TEXTURE_2D, this->core->getResources()->getTextureTesourceId(9));
            this->core->getRenderer()->drawFloor(0.0, 0.0, 1.0);
        }
        
        void PCubeHolder::print()
        {
            cout<<"| CH  ";
        }  

        short PCubeHolder::isPlayerMovePossible() 
        {
            return 6;
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
          /*  this->texture.setPath("test.tga");
            if(!this->texture.makeTgaTexture(true))
            {
                Messages::errorMessage("Cube texture error!");
                return false;
            }*/
            return true;
        }
        
        void PCube::draw()
        {
            glColor3f(1.0, 1.0, 1.0);
            glBindTexture(GL_TEXTURE_2D, this->core->getResources()->getTextureTesourceId(9));
            this->core->getRenderer()->drawCube(0.0, 0.0, 1.0, 0.0);
        }
        
        void PCube::print()
        {
            cout<<"|  C  ";
        } 

        short PCube::isPlayerMovePossible() 
        {
   
            return 2;
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
            glColor3f(1.0, 1.0, 1.0);
            switch(this->dir)
            {
                    case Aliases::left:
                        glRotatef(180.0, 0.0, 0.0, 1.0);
                        break;
                        
                    case Aliases::up:
                        glRotatef(90.0, 0.0, 0.0, 1.0);
                        break;
                            
                    case Aliases::down:
                        glRotatef(-90.0, 0.0, 0.0, 1.0);
                        break;
            }
            glBindTexture(GL_TEXTURE_2D, this->core->getResources()->getTextureTesourceId(10));
            this->core->getRenderer()->drawCube(0.0, 0.0, 1.0, 0.0);
        }
        
        void POnewayCube::print()
        {
            cout<<"| OWC ";
        } 

        short POnewayCube::isPlayerMovePossible() 
        {
            return 3;
        }
        
        PDirection POnewayCube::getDirection()
        {
            return this->dir;
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
              
     /*   short POnewayFloor::isPlayerMovePossible() 
        {
            /// tmp
            return f;
        }*/
        


    }
}

