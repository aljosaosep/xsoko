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
 * File:   particle.h
 * Author: aljosa
 * 
 * desc: basic class for particle effects implementation
 *
 * Created on October 5, 2008, 11:11 AM
 */

#include "particle.h"

#include "renderer.h"

namespace PacGame
{
    namespace RenderMaschine
    {
        
        PParticleEngine::PParticleEngine()
        {
            this->init(0.0, 0.0, 0.0);
        }

        PParticleEngine::PParticleEngine(float ox, float oy, float oz)
        {
            this->init(ox, oy, oz);
        }
        
        
        void PParticleEngine::init(float ox, float oy, float oz)
        {
            srand(time(NULL));
            
            this->origin.setCoordinates(ox, oy, oz);
                        
            this->PARTICLE_SIZE = 0.5;
            this->INITIAL_SPREAD = 100;
            this->SPEED_DECAY = 0.00005;
            
            // make all particles DEAD
            for(int i=0; i<NUM_PARTICLES; i++)
            {
         //       this->particles[i].position.setCoordinates(ox, oy, oz); // add. by aljosa
                this->particles[i].life = 0.0;
                this->particles[i].r = 1.0;
                this->particles[i].b = 0.0;
            }
        }
        
        void PParticleEngine::setOrgin(float x, float y, float z)
        {
            for(int i=0; i<NUM_PARTICLES; this->particles[i++].position.setCoordinates(x, y, z));      
        }
        
        void PParticleEngine::process(float ticks)
        {
 /*           
              int MaxSpread,MaxParticles,Index;
  float Spread,Angle;  */
  
            int maxSpread, maxParticles;
            float spread, angle;
            
            maxSpread = this->INITIAL_SPREAD;
            maxParticles = NUM_PARTICLES/2;

            for(int i=0; i<maxParticles; i++)
            {
                // if particle is alive and well
                if(this->particles[i].life > 0.0)
                {
              //      this->particles[i].position = this->particles[i].position + (this->particles[i].vector * ticks);
                    
                    this->particles[i].position.x += (this->particles[i].vector.x * ticks);
                    this->particles[i].position.y += (this->particles[i].vector.y * ticks);
                     this->particles[i].position.z += (this->particles[i].vector.z * ticks);   
                     
                  //                       cout<<endl<<"position after pos update: ";
               //     this->particles[i].position.printCoordinates();
                    
                    this->particles[i].vector.z -= (this->SPEED_DECAY * ticks);
                    
                  //  this->particles[i].vector.setCoordZ(this->particles[i].vector.getCoordZ() - this->decaySpeed);
                    
                    // bounce particle from floor
                    if(this->particles[i].position.x > -10.0 && this->particles[i].position.x < 10.0 &&
                        this->particles[i].position.z > -10.0 && this->particles[i].position.z < 10.0)
                    {
                        if(this->particles[i].position.y < this->PARTICLE_SIZE)
                        {
                            this->particles[i].position.y = this->PARTICLE_SIZE;
                            this->particles[i].life -= 0.01;
                            this->particles[i].vector.y *= (-0.06);
                        }
                    }
                    
                    this->particles[i].life -= (0.001 * ticks);
                }
                else  // spawn a new particle
                {

                    // reset position
                    this->particles[i].position.setCoordinates(0.0, this->PARTICLE_SIZE, 0.0); 
                    
                    spread = (float)(rand()%maxSpread)/10000;
                    angle = (float)(rand()%157)/100; // quarter of circle

                    this->particles[i].vector.x = cos(angle)*spread;
                    this->particles[i].vector.z = cos(angle)*spread;

                    // randomly reverse x and z vec
                    if(rand()%2)
                        this->particles[i].vector.x = -this->particles[i].vector.x;

                    if(rand()%2)
                        this->particles[i].vector.z = -this->particles[i].vector.z;   

                    // set initial speed
                    this->particles[i].vector.y = (float)(rand()%500)/10000;

             //       cout<<endl<<"vector initiated as: ";
             //       this->particles[i].vector.printCoordinates();
            //        cout<<endl;

                    // get random life and color
                    this->particles[i].life = (float)(rand()%100)/100.0;
                    this->particles[i].g = 0.2 + ((float)(rand()%50)/100);

               //     this->particles[i].position.setCoordY(this->particleSize);
             //       this->particles[i].position.setCoord     
                }
            }
            
            glPushMatrix();
            glDisable(GL_LIGHTING);
            glTranslatef(this->origin.x, this->origin.y, this->origin.z );
                    
            // draw particles
            for(int i=0; i<maxParticles; i++)
            {
             //   cout<<endl<<"particle pos:"<<this->particles[i].position.getCoordX()<<' '<<this->particles[i].position.getCoordY()<<' '<<this->particles[i].position.getCoordZ()<<endl;
            //    cout<<endl<<"position at drawing: ";
          //      this->particles[i].position.printCoordinates();
         //       cout<<endl;
                glPointSize(3.0);
                glPushMatrix();
                    glColor4f(this->particles[i].r, this->particles[i].g, this->particles[i].b, this->particles[i].life);
                    glTranslatef(this->particles[i].position.getCoordX(), this->particles[i].position.getCoordY(), this->particles[i].position.getCoordZ());
                    glBegin(GL_POINTS);
                        glVertex3f(0.0,0.0,0.0);
                    glEnd();

                glPopMatrix();
            }
            glEnable(GL_LIGHTING);
            glPopMatrix();
        }
    }
}

