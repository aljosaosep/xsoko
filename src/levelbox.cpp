/*
 * codename: xSoko
 * Copyright (C) Aljosa Osep, Jernej Skrabec, Jernej Halozan 2008 <aljosa.osep@gmail.com, jernej.skrabec@gmail.com, jernej.halozan@gmail.com>
 * 
 * xSoko project is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * xSoko project is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
        namespace GameObjects
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
            
            
            void PLevelObject::setRealI(float realI)
            {
                    this->realI = realI;
            }
            
            void PLevelObject::setRealJ(float realJ)
            {
                    this->realJ = realJ;
            }
            
            void PLevelObject::toogleBombActivity()
            {
                this->containsActiveBomb == false ? this->containsActiveBomb = true : this->containsActiveBomb = false;
            }

            int PLevelObject::getI() const  // i index getter
            {
                    return this->i;
            }

            int PLevelObject::getJ() const  // j index getter
            {
                    return this->j;
            }
            
            float PLevelObject::getRealI() const  // i index getter
            {
                    return this->realI;
            }

            float PLevelObject::getRealJ() const  // j index getter
            {
                    return this->realJ;
            }
            
            bool PLevelObject::isActiveBomb() const
            {
                return this->containsActiveBomb;
            }

            unsigned short PLevelObject::getId() const
            {
                return id;
            }

             void PLevelObject::moveObject(int direction)
             {
                     // set the direction of the object and the move bit
                     this->direction = direction;
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

            void PTeleport::draw()
            {
                glColor4f(0.0, 0.0, 1.0, 0.4f);
                glBindTexture(GL_TEXTURE_2D, this->core->getResources()->getTextureTesourceId(TELEPORT_RES));
                this->core->getRenderer()->drawCube(0.0, 0.0, 1.0);   
            }

            void PTeleport::print()
            {
                cout<<"| T"<<this->teleport_id<<' ';
            }

             
             short PTeleport::isPlayerMovePossible(int direction)
            {
                if(returnFirstChild() == NULL)
                {
                        if(containsActiveBomb)
                                return 0;
                        return 8;
                }
                        
                return 8 | static_cast<PLevelObject*>(returnFirstChild())->isPlayerMovePossible(direction);
            }
            /*****************************************
             PFloor methods
             *****************************************/	
            void PFloor::draw()
            {
                glColor3f(1.0, 1.0, 1.0);
                glBindTexture(GL_TEXTURE_2D, this->core->getResources()->getTextureTesourceId(FLOOR_RES));
                this->core->getRenderer()->drawFloor(0.0, 0.0, 1.0);
            }

            void PFloor::print()
            {
                cout<<"|     ";
            }

            
            short PFloor::isPlayerMovePossible(int direction)
            {
                if(returnFirstChild() == NULL)
                {
                         if(containsActiveBomb)
                                return 0;
                        return 1;
                }else
                {
                        return static_cast<PLevelObject*>(returnFirstChild())->isPlayerMovePossible(direction);
                }
            }
            /*****************************************
             POnewayFloor methods
             *****************************************/	       
            void POnewayFloor::draw()
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
                            
                        default:
                        break;
                }
                glBindTexture(GL_TEXTURE_2D, this->core->getResources()->getTextureTesourceId(OW_FLOOR_RES));
                this->core->getRenderer()->drawFloor(0.0, 0.0, 1.0);
            }

            void POnewayFloor::print()
            {
                cout<<"| OWF ";
            }
            
            short POnewayFloor::isPlayerMovePossible(int direction)
            {
                    // if the direction is not the same as the direction of the floor, no move is possible
                    if(direction != dir)
                        return 0;
                        
                    if(returnFirstChild() == NULL)
                    {
                             if(containsActiveBomb)
                                return 0;
                        return 1;
                    }else
                    {
                         return static_cast<PLevelObject*>(returnFirstChild())->isPlayerMovePossible(direction);
                   } 
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
            void PSolidWall::draw()
            {
                glColor3f(0.9f, 0.87f, 0.87f);
                glBindTexture(GL_TEXTURE_2D, this->core->getResources()->getTextureTesourceId(S_WALL_RES));
                this->core->getRenderer()->drawCube(0.0, 0.0, 1.0);
            }

            void PSolidWall::print()
            {
                cout<<"| SW  ";
            }

            
            short PSolidWall::isPlayerMovePossible(int direction)
            {
                return 0;
            }

            /*****************************************
             PUnsolidWall methods
             *****************************************/	
            void PUnsolidWall::draw()
            {
                glColor3f(0.7f, 0.6f, 0.6f);
                glBindTexture(GL_TEXTURE_2D, this->core->getResources()->getTextureTesourceId(U_WALL_RES));
                this->core->getRenderer()->drawCube(0.0, 0.0, 1.0);
            }

            void PUnsolidWall::print()
            {
                cout<<"| USW ";
            }  

                
            
            short PUnsolidWall::isPlayerMovePossible(int direction)
            {
                return 0;
            }
            /*****************************************
             PBridge methods
             *****************************************/	 
            void PBridge::draw()
            {
                glColor4f(1.0, 1.0, 1.0, 0.8f);
                glBindTexture(GL_TEXTURE_2D, this->core->getResources()->getTextureTesourceId(BRIDGE_RES));
                this->core->getRenderer()->drawFloor(0.0, 0.0, 1.0);

            }

            void PBridge::print()
            {
                cout<<"|  B  ";
            }  
            
            short PBridge::isPlayerMovePossible(int direction)
            {
                    if(returnFirstChild() == NULL)
                    {
                             if(containsActiveBomb)
                                return 0;
                        return 1;
                }else
                {
                        /// todo
                         return static_cast<PLevelObject*>(returnFirstChild())->isPlayerMovePossible(direction);
                }
            }

            /*****************************************
             PVoid methods
             *****************************************/	
            void PVoid::draw() { }

            void PVoid::print()
            {
                cout<<"|     ";
            }   
            
            short PVoid::isPlayerMovePossible(int direction)
            {
                return 0;
            }


            /*****************************************
             PCubeHolder methods
             *****************************************/	   
            void PCubeHolder::draw()
            {
                glColor3f(1.0, 0.4f, 0.4f);
                glBindTexture(GL_TEXTURE_2D, this->core->getResources()->getTextureTesourceId(CUBE_RES));
                this->core->getRenderer()->drawFloor(0.0, 0.0, 1.0);
            }

            void PCubeHolder::print()
            {
                cout<<"| CH  ";
            }  
            
            short PCubeHolder::isPlayerMovePossible(int direction)
            {
                    if(returnFirstChild() == NULL)
                    {
                             if(containsActiveBomb)
                                return 0;
                        return 1;
                    }else
                    {
                        /// todo
                         return static_cast<PLevelObject*>(returnFirstChild())->isPlayerMovePossible(direction);
                }
            }

            /*****************************************
             * MATRIX II. ELEMENTS METHODS IMPLEMENTATION
             *
             *****************************************/
            /*****************************************
             PCube methods
             *****************************************/	  
            void PCube::draw()
            {
                glColor3f(1.0, 1.0, 1.0);
                glBindTexture(GL_TEXTURE_2D, this->core->getResources()->getTextureTesourceId(CUBE_RES));
                this->core->getRenderer()->drawCube(0.0, 0.0, 1.0);
            }


        bool PCube::animate(double time)
        {
                      bool end_of_movement = false;
              
              
                      double moveOffset = OBJECT_SPEED*time; // speed = 0.1
                    
                        if(realI != (float)i) 
                        {
                                if(realI > (float)i)
                                {
                                        realI -= moveOffset;
                                        if(realI <= (float)i)
                                        {
                                                realI = (float)i;
                                                end_of_movement = true;
                                        }
                                }
                                else
                                {
                                        realI += moveOffset;
                                        if(realI >= (float)i)
                                        {
                                                realI = (float)i;
                                                end_of_movement = true;
                                        }
                                }
                        }
                        
                        if(realJ != (float)j)
                        {
                                if(realJ > (float)j)
                                {
                                        realJ -=moveOffset;
                                        if(realJ <= (float)j)
                                        {
                                                realJ = (float)j;
                                                end_of_movement = true;
                                        }
                                }
                                else
                                {
                                        realJ +=moveOffset;
                                        if(realJ >= (float)j)
                                        {
                                                realJ = (float)j;
                                                end_of_movement = true;
                                        }
                                }
                        }
                return end_of_movement;
        }

            void PCube::print()
            {
                cout<<"|  C  ";
            } 
            
            short PCube::isPlayerMovePossible(int direction) 
            {
                return 2;
            }

            /*****************************************
             POnewayCube methods
             *****************************************/	 
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
                        default:
                        break;
                }
                glBindTexture(GL_TEXTURE_2D, this->core->getResources()->getTextureTesourceId(OW_CUBE_RES));
                this->core->getRenderer()->drawCube(0.0, 0.0, 1.0);
            }
            
            
            bool POnewayCube::animate(double time)
        {
                  bool end_of_movement = false;
              
              
                      double moveOffset = OBJECT_SPEED*time; // speed = 0.1
                    
                        if(realI != (float)i)
                        {
                                if(realI > (float)i)
                                {
                                        realI -= moveOffset;
                                        if(realI <= (float)i)
                                        {
                                                realI = (float)i;
                                                end_of_movement = true;
                                        }
                                }
                                else
                                {
                                        realI += moveOffset;
                                        if(realI >= (float)i)
                                        {
                                                realI = (float)i;
                                                end_of_movement = true;
                                        }
                                }
                        }
                        
                        if(realJ != (float)j)
                        {
                                if(realJ > (float)j)
                                {
                                        realJ -=moveOffset;
                                        if(realJ <= (float)j)
                                        {
                                                realJ = (float)j;
                                                end_of_movement = true;
                                        }
                                }
                                else
                                {
                                        realJ +=moveOffset;
                                        if(realJ >= (float)j)
                                        {
                                                realJ = (float)j;
                                                end_of_movement = true;
                                        }
                                }
                        }
                return end_of_movement;
        }

            void POnewayCube::print()
            {
                cout<<"| OWC ";
            } 
            
            short POnewayCube::isPlayerMovePossible(int direction)
            {
                    // if the direction of movement is the same as the direction of the one way cube, we can try to move it
                    // we return 2
                   
                    if(dir == direction)
                        return 2;
                    return 0;
            }

            PDirection POnewayCube::getDirection()
            {
                return this->dir;
            }

            /*****************************************
             PBomb methods
             *****************************************/	 
            void PBomb::draw()
            {
                glColor3f(1.0, 1.0, 1.0);
                glBindTexture(GL_TEXTURE_2D, this->core->getResources()->getTextureTesourceId(BOMB_RES));
                this->core->getRenderer()->drawCube(0.0, 0.0, 1.0);
            }

            void PBomb::print()
            {
                cout<<"|  B  ";
            } 
            
            short PBomb::isPlayerMovePossible(int direction) 
            {
                return 4;
            } 
            
            
            /*****************************************
             PDetonatedBomb methods
             *****************************************/
            void PDetonatedBomb::draw() { /* override */ }
            
            void PDetonatedBomb::print()
            {
                cout<<"| D_B ";
            }
            
            short PDetonatedBomb::isPlayerMovePossible(int direction) 
            { 
                return 0; 
            } 
        }
    }
}

