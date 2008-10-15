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
            
            this->slowdown = 2.0;
            this->xspeed = 0.0;
            this->yspeed = 0.0;
      //      this->zoom = -40.0;
            
         
            for(int i=0; i<MAX_PARTICLES; i++)
            {
                this->particles[i].position.setCoordinates(ox, oy, oz);

                this->particles[i].active = true;   // set all particles live at beginning
                this->particles[i].life = 1.0;      // all particles has full life at beginning
                this->particles[i].fade = float(rand()%100) / 1000.0 + 0.003;   // very little random value; how fast particle fades out
                
                /// set color!
                particles[i].r = 1.0;//(rand()%10)/10;
                particles[i].g = (rand()%10)/10;
                particles[i].b = (rand()%10)/10;
                
                this->particles[i].vector.setCoordinates((rand()%50 - 26)*10,(rand()%50 - 26)*10,(rand()%50 - 26)*10);
                
            /*    this->particles[i].vector.setCoordX((rand()%50 - 26)*10);   // set motion vector, coord x
                this->particles[i].vector.setCoordY((rand()%50 - 26)*10);   // set motion vector, coord y
                this->particles[i].vector.setCoordZ((rand()%50 - 26)*10);   // set motion vector, coord z */
                
                this->particles[i].gravity.setCoordX(0.0);  // no gravity in X dir at begginning
                this->particles[i].gravity.setCoordX(-0.8); // slight Y-negative gravity
                this->particles[i].gravity.setCoordX(0.0);  // no gravity in Z dir at beginning
            }
        }
        
        void PParticleEngine::setOrgin(float x, float y, float z)
        {
            for(int i=0; i<MAX_PARTICLES; this->particles[i++].position.setCoordinates(x, y, z));      
        }
        
        bool PParticleEngine::process()
        {
            for(int i=0; i<MAX_PARTICLES; i++)
            {
                if(particles[i].active == true)
                {
                    PVector3D currentParticlePos = particles[i].position;
                    cout<<"particle pos: "<<particles[i].position.getCoordX()<<' '<<particles[i].position.getCoordY()<<' '<<particles[i].position.getCoordZ()<<' '<<endl;
                    cout<<"fade:" <<particles[i].fade<<endl;
                    cout<<"life:" <<particles[i].life<<endl;
            //        glPointSize(10.0);
                    glPushMatrix();
                    glTranslatef(0.0, 0.0, 0.0);
                        glPointSize(2.0);
                        glBegin(GL_POINTS);
                            glColor4f(1.0, (float((rand()%10))/10.0), (float((rand()%10))/10.0), particles[i].life);
                            glVertex3f(currentParticlePos.getCoordX(),currentParticlePos.getCoordY(),currentParticlePos.getCoordZ());
                        glEnd();
                    glPopMatrix();
                    
                    particles[i].position = particles[i].position + particles[i].vector/(slowdown*1500);	

                    particles[i].vector = particles[i].vector + particles[i].gravity;
                    
                    particles[i].life -= particles[i].fade;      // we take a little of life away
                    
                    if(particles[i].life < 0.0)
                    {
                        particles[i].active = false;
                       
          /*              particles[i].life = 1.0;
                        particles[i].fade = float(rand()%100) / 1000.0 + 0.003;

                        particles[i].vector.setCoordX(this->xspeed + float((rand()%60)-32.0));
                        particles[i].vector.setCoordX(this->yspeed + float((rand()%60)-32.0));   
                        particles[i].vector.setCoordZ(float((rand()%60)-30.0));                */   
                    }
                    
                }
            }
            return true;
        }
    }
}

