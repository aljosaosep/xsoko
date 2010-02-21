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
        /*
         *             float slowdown; // spawn ratio (?)
            float xpseed, yspeed; // direction of the "tail"
            float zoom;

            unsigned int col;
            unsigned int delay;
            unsigned int loop;

            Particle particles[MAX_PARTICLES];

            PVector3D position;
         */

        /// Abstract particle class implementation
        PParticleEffect::PParticleEffect(const PVector3D &pos) : slowdown(2.0f), zoom(-40.0f), position(pos), xspeed(0.0f), yspeed(0.0f)  {
            this->numParticles = MAX_PARTICLES;
        }
            
        

        /// PParticleExplosion implementation
        PParticleExplosion::PParticleExplosion(const PVector3D &pos) : PParticleEffect(pos) {
            this->init();
        }

        void PParticleExplosion::init() {
            // init particles
            for (int i=0; i<MAX_PARTICLES; i++ ) {
                particles[i].active = true; // activate the bastard
                particles[i].life = 1.0f;
                particles[i].fade = float(rand()%100)/1000.0f+0.003f;

                // fix
                particles[i].r = (float)(rand()%255) / 255.0f;
                particles[i].g = (float)(rand()%255) / 255.0f;
                particles[i].b = (float)(rand()%255) / 255.0f;

                particles[i].dir.x = float((rand()%50)-26.0f)*10.0f;	// *10 -> explosion
		particles[i].dir.y = float((rand()%50)-25.0f)*10.0f;
		particles[i].dir.z = float((rand()%50)-25.0f)*10.0f;

                particles[i].grav.x =0.0f;						// Set Horizontal Pull To Zero
		particles[i].grav.y =- 0.8f;					// Set Vertical Pull Downward
		particles[i].grav.z = 0.0f;

                               particles[i].pos.x =0.0f;						// Set Horizontal Pull To Zero
		particles[i].pos.y = 0.0f;					// Set Vertical Pull Downward
		particles[i].pos.z = 0.0f;
            }

        }

        int PParticleExplosion::getNumParticles()  {
            return this->numParticles;
        }

        void PParticleExplosion::draw() {
            glDisable(GL_TEXTURE_2D);
            glPushMatrix();
            glTranslatef(position.x, position.y, position.z);

            // Particle stuff
            for (int i=0; i<MAX_PARTICLES; i++ ) {
                if (particles[i].active) {
                    // Update
                    float x=particles[i].pos.x;				// Grab Our Particle X Position
                    float y=particles[i].pos.y;				// Grab Our Particle Y Position
                    float z=particles[i].pos.z ;

                    glColor4f(particles[i].r,particles[i].g,particles[i].b,particles[i].life);

                    float psize = 0.2f;
                    glBegin(GL_TRIANGLE_STRIP);
                    glTexCoord2d(1,1); glVertex3f(x+psize,y+psize,z); // Top Right
                    glTexCoord2d(0,1); glVertex3f(x-psize,y+psize,z); // Top Left
                    glTexCoord2d(1,0); glVertex3f(x+psize,y-psize,z); // Bottom Right
                    glTexCoord2d(0,0); glVertex3f(x-psize,y-psize,z); // Bottom Left
                    glEnd();

                  /*  glBegin(GL_TRIANGLE_STRIP);
              

                    glTexCoord2d(1,1); glVertex3f(x+0.5f,y+0.5f,z); // Top Right
				glTexCoord2d(0,1); glVertex3f(x-0.5f,y+0.5f,z); // Top Left
				glTexCoord2d(1,0); glVertex3f(x+0.5f,y-0.5f,z); // Bottom Right
				glTexCoord2d(0,0); glVertex3f(x-0.5f,y-0.5f,z); // Bottom Left
                    glEnd();*/

                    /*glBegin(GL_POINT);
                    glVertex3f(0.0f, 0.0f, 0.0f);
                    glEnd();*/

                    particles[i].pos.x += particles[i].dir.x/(slowdown*400);	// Move On The X Axis By X Speed
                    particles[i].pos.y += particles[i].dir.y/(slowdown*400);	// Move On The Y Axis By Y Speed
                    particles[i].pos.z += particles[i].dir.z/(slowdown*400);	// Move On The Z Axis By Z Speed

                  /*  particles[i].dir.x += particles[i].grav.x;			// Take Pull On X Axis Into Account
                    particles[i].dir.y += particles[i].grav.y;			// Take Pull On Y Axis Into Account
                    particles[i].dir.z += particles[i].grav.z;
*/
                    particles[i].life -= particles[i].fade;

                  if (particles[i].life<0.0f) {
                      if (particles[i].active == true)
                          this->numParticles --;
                      else
                          particles[i].active = false;
                  }

                  /*      particles[i].life = 1.0f;				// Give It New Life
			particles[i].fade = float(rand()%100)/1000.0f+0.003f;

                        particles[i].pos.x = 0.0f;					// Center On X Axis
			particles[i].pos.y = 0.0f;					// Center On Y Axis
			particles[i].pos.z = 0.0f;

                        particles[i].dir.x = xspeed+float((rand()%60)-32.0f);	// X Axis Speed And Direction
			particles[i].dir.y = yspeed+float((rand()%60)-30.0f);	// Y Axis Speed And Direction
			particles[i].dir.z = float((rand()%60)-30.0f);		// Z Axis Speed And Direction
                   */

                    
                }
            }

            glPopMatrix();
            glEnable(GL_TEXTURE_2D);

        }
        
        
 
    }
}

