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
            this->init();
        }
        
        void PParticleEngine::init()
        {
            srand(time(NULL));
            
            this->slowdown = 2.0;
            this->xspeed = 10.0;
            this->yspeed = 10.0;
            this->zoom = 0.0;
         
            for(int i=0; i<MAX_PARTICLES; i++)
            {
                this->particles[i].active = true;   // set all particles live at beginning
                this->particles[i].life = 1.0;      // all particles has full life at beginning
                this->particles[i].fade = (rand()%100 / 1000) + 0.003;   // very little random value; how fast particle fades out
                
                /// set color!
                particles[i].r = (rand()%10)/10;
                particles[i].g = (rand()%10)/10;
                particles[i].b = (rand()%10)/10;                
                
                this->particles[i].vector.setCoordX((rand()%50 - 26)*10);   // set motion vector, coord x
                this->particles[i].vector.setCoordY((rand()%50 - 26)*10);   // set motion vector, coord y
                this->particles[i].vector.setCoordZ((rand()%50 - 26)*10);   // set motion vector, coord z
                
                this->particles[i].gravity.setCoordX(0.0);  // no gravity in X dir at begginning
                this->particles[i].gravity.setCoordX(-0.8); // slight Y-negative gravity
                this->particles[i].gravity.setCoordX(0.0);  // no gravity in Z dir at beginning
            }
        }
        
        bool PParticleEngine::process()
        {
            for(int i=0; i<MAX_PARTICLES; i++)
            {
                if(particles[i].active == true)
                {
                    PVector3D currentParticlePos = particles[i].position;
                    cout<<"particle pos: "<<particles[i].position.getCoordX()<<' '<<particles[i].position.getCoordY()<<' '<<particles[i].position.getCoordZ()<<' '<<endl;
             /*       currentParticlePos.setCoordX(particles[i].position.getCoordX());
                    currentParticlePos.setCoordY(particles[i].position.getCoordY());
                    currentParticlePos.setCoordZ(particles[i].position.getCoordZ()+this->zoom); */    

                    glPushMatrix();
               //     glTranslatef(0.0, 0.0, 0.0);
                        glColor4f(this->particles[i].r, this->particles[i].g, this->particles[i].b, 1.0);
                      //  RenderMaschine::PRenderer rndr;
                    //    rndr.drawCube(0.0, 0.0, 1.0, 0.0);
                        glPointSize(50.0);
                        glBegin(GL_POINTS);
                            glVertex3f(currentParticlePos.getCoordX(), currentParticlePos.getCoordY(), currentParticlePos.getCoordZ());
                        glEnd();
                    glPopMatrix();
                    
                    particles[i].position = particles[i].position + (particles[i].vector / (slowdown*1000));
                    particles[i].vector = particles[i].vector + particles[i].gravity;
                    
                    particles[i].life -= particles[i].fade;      // we take a little of life away
                    
                    if(particles[i].life < 0.0)
                    {
                        particles[i].life = 1.0;
                        particles[i].fade = (rand()%100 / 1000) + 0.003;
                        particles[i].position.setCoordinates(0.0, 0.0, 0.0);
                        
                        /*				particle[loop].xi=xspeed+float((rand()%60)-32.0f);	// X Axis Speed And Direction
				particle[loop].yi=yspeed+float((rand()%60)-30.0f);	// Y Axis Speed And Direction
				particle[loop].zi=float((rand()%60)-30.0f);		*/
                        particles[i].vector.setCoordX(this->xspeed + float((rand()%60)-32.0));
                        particles[i].vector.setCoordX(this->yspeed + float((rand()%60)-32.0));   
                        particles[i].vector.setCoordZ(float((rand()%60)-30.0));                           
                    }
                    
                }
            }
            return true;
        }
    }
}
