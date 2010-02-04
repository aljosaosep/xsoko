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
                PObject::draw();
                float color[] = {0.0, 0.0, 1.0, 0.6};
                this->core->getRenderer()->drawCube(0.0, 0.0, 1.0, color, this->core->getResources()->getTextureTesourceId(TELEPORT_RES) );
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
                        
                return 8 | (returnFirstChild())->isPlayerMovePossible(direction);
            }
            /*****************************************
             PFloor methods
             *****************************************/	
            void PFloor::draw()
            {
                PObject::draw();
                float color[] = { 1.0, 1.0, 1.0, 1.0 };
                this->core->getRenderer()->drawFloor(0.0, 0.0, 1.0, color, this->core->getResources()->getTextureTesourceId(FLOOR_RES) );
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
                        return (returnFirstChild())->isPlayerMovePossible(direction);
                }
            }
            /*****************************************
             POnewayFloor methods
             *****************************************/	       
            void POnewayFloor::draw()
            {
                PObject::draw();

                float color[] = { 1.0, 1.0, 1.0, 1.0 };

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
                this->core->getRenderer()->drawFloor(0.0, 0.0, 1.0, color, this->core->getResources()->getTextureTesourceId(OW_FLOOR_RES) );
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
                         return (returnFirstChild())->isPlayerMovePossible(direction);
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
                PObject::draw();

                float color[] = { 0.9f, 0.87f, 0.87f, 1.0 };
                this->core->getRenderer()->drawCube(0.0, 0.0, 1.0, color, this->core->getResources()->getTextureTesourceId(S_WALL_RES));
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
                PObject::draw();

                float color[] = { 0.7f, 0.6f, 0.6f, 1.0 };
                this->core->getRenderer()->drawCube(0.0, 0.0, 1.0, color, this->core->getResources()->getTextureTesourceId(U_WALL_RES));
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
                PObject::draw();

                float color[] = { 1.0, 1.0, 1.0, 0.8f };
                this->core->getRenderer()->drawFloor(0.0, 0.0, 1.0, color, this->core->getResources()->getTextureTesourceId(BRIDGE_RES));

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
                         return (returnFirstChild())->isPlayerMovePossible(direction);
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
                PObject::draw();

                float color[] = { 1.0, 0.4, 0.4, 1.0f };
                this->core->getRenderer()->drawFloor(0.0, 0.0, 1.0, color, this->core->getResources()->getTextureTesourceId(CUBE_RES));
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
                         return (returnFirstChild())->isPlayerMovePossible(direction);
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
                PObject::draw();

                float color[] = { 1.0, 0.6, 0.7, 0.9f };
                this->core->getRenderer()->drawCube(0.0, 0.0, 1.0, color, this->core->getResources()->getTextureTesourceId(CUBE_RES));
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
                PObject::draw();

                float color[] = { 1.0, 0.6, 0.7, 0.9f };
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
                this->core->getRenderer()->drawCube(0.0, 0.0, 1.0, color, this->core->getResources()->getTextureTesourceId(OW_CUBE_RES));
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
                PObject::draw();
                
                float color[] = { 1.0, 1.0, 1.0, 1.0f };
       
                this->core->getRenderer()->drawCube(0.0, 0.0, 0.8, color, this->core->getResources()->getTextureTesourceId(BOMB_RES));
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

