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

namespace PacGame
{
    namespace RenderMaschine
    {
        void PParticleEngine::init()
        {
         
            for(int i=0; i<MAX_PARTICLES; i++)
            {
                this->particles[i].active = true;   // set all particles live at beginning
                this->particles[i].life = 1.0;      // all particles has full life at beginning
                this->particles[i].fade = (rand()%100 / 1000) + 0.003;   // very little random value; how fast particle fades out
                /// set color!
           //     this->particles[i].vector.
            }
        }
    }
}
