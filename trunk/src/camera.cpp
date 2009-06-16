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
 * File:   camera.h
 * Author: aljosa
 *
 * Created on September 7, 2008, 4:34 PM
 *
 * Inspired by camera tutorial by Allen Sherrod
 * www.UltimateGameProgramming.com
 * Thank you!
 */

#include "vector.h"
#include "camera.h"

namespace PacGame
{
    namespace GameClasses
    {
        // setter
        void PCamera::setCamera(PVector3D view, PVector3D position, PVector3D up)
        {
            this->position = position;
            this->view = view;
            this->up = up;

            this->cameraRotateValue = 1.0; // temporary
        }
        
        // move camera
        void PCamera::moveCamera(float direction)
        {
            PVector3D lookDirection;  // direction we're looking at
            
            // direction is vector, where we're looking - vector, where we are
            lookDirection.setCoordX(this->view.getCoordX()-this->position.getCoordX());
            lookDirection.setCoordY(this->view.getCoordY()-this->position.getCoordY());
            lookDirection.setCoordZ(this->view.getCoordZ()-this->position.getCoordZ());
            
            // normalize the direction
            float dp = 1 / (float)sqrt(lookDirection.getCoordX()*lookDirection.getCoordX() +
                                       lookDirection.getCoordY()*lookDirection.getCoordY() +
                                       lookDirection.getCoordZ()*lookDirection.getCoordZ()); 
            
            lookDirection.setCoordX(lookDirection.getCoordX()*dp);
            lookDirection.setCoordY(lookDirection.getCoordY()*dp);            
            lookDirection.setCoordZ(lookDirection.getCoordZ()*dp);
            
            // move position
            this->position.setCoordX(this->position.getCoordX() + (lookDirection.getCoordX()*direction));
            this->position.setCoordY(this->position.getCoordY() + (lookDirection.getCoordY()*direction));            
            this->position.setCoordZ(this->position.getCoordZ() + (lookDirection.getCoordZ()*direction));
            
            // and view
            this->view.setCoordX(this->view.getCoordX() + (lookDirection.getCoordX()*direction));
            this->view.setCoordY(this->view.getCoordY() + (lookDirection.getCoordY()*direction));            
            this->view.setCoordZ(this->view.getCoordZ() + (lookDirection.getCoordZ()*direction));
        }
        
        void PCamera::rotateCamera(float angle, PVector3D speed)
        {
            PVector3D lookDirection;
            PVector3D newLookDirection;
            
            float angle_cos = 0, angle_sin = 0; // cosinus ans sinus of angle
            
            // calculate cosinus and sinus of angle
            angle_cos = (float)cos(angle);
            angle_sin = (float)cos(angle);
            
            // direction is vector, where we're looking - vector, where we are
            lookDirection = this->view - this->position;
            
            // normalize the direction
            float dp = 1 / (float)sqrt(lookDirection.getCoordX()*lookDirection.getCoordX() +
                                       lookDirection.getCoordY()*lookDirection.getCoordY() +
                                       lookDirection.getCoordZ()*lookDirection.getCoordZ()); 
            
            lookDirection.setCoordinates(lookDirection*dp);
            
            newLookDirection.setCoordX((angle_cos + (1 - angle_cos) * speed.getCoordX()) * lookDirection.getCoordX());
          //  newLookDirection.setCoordX(newLookDirection.getCoordX() + ((1 - angle_cos) * speed.getCoordX() * speed.getCoordY() + speed.getCoordZ() * angle_sin)*)
            
            
            
            
            	// Calculate the new X position.
	/*xNewLookDirection = (CosineAngle + (1 - CosineAngle) * xSpeed) * xLookDirection;
	xNewLookDirection += ((1 - CosineAngle) * xSpeed * ySpeed - zSpeed * SineAngle)* yLookDirection;
	xNewLookDirection += ((1 - CosineAngle) * xSpeed * zSpeed + ySpeed * SineAngle) * zLookDirection;

	// Calculate the new Y position.
	yNewLookDirection = ((1 - CosineAngle) * xSpeed * ySpeed + zSpeed * SineAngle) * xLookDirection;
	yNewLookDirection += (CosineAngle + (1 - CosineAngle) * ySpeed) * yLookDirection;
	yNewLookDirection += ((1 - CosineAngle) * ySpeed * zSpeed - xSpeed * SineAngle) * zLookDirection;

	// Calculate the new Z position.
	zNewLookDirection = ((1 - CosineAngle) * xSpeed * zSpeed - ySpeed * SineAngle) * xLookDirection;
	zNewLookDirection += ((1 - CosineAngle) * ySpeed * zSpeed + xSpeed * SineAngle) * yLookDirection;
	zNewLookDirection += (CosineAngle + (1 - CosineAngle) * zSpeed) * zLookDirection;

	// Last we add the new rotations to the old view to correctly rotate the camera.
	xView = xPos + xNewLookDirection;
	yView = yPos + yNewLookDirection;
	zView = zPos + zNewLookDirection;*/
            

            
            
        }
 
        void PCamera::fitCameraToLevel(int width, int height)
        {
            width --;
            height --;
            

            float bigger = (width > height ? width : height) + 1;  // tmp 
            
            this->position.setCoordinates((float)height/2, (float)-width/2, 0.0);
            this->view.setCoordinates((float)height/2, (float)-width/2,  bigger+6);
            this->up.setCoordinates(0.0, 1.0, 0.0);
        }

        void PCamera::rotateViewX(float val)
        {
            this->view.x += val;
        }

        void PCamera::rotateViewY(float val)
        {
            this->view.y += val;
        }

        void PCamera::rotateViewX(float val, int times)
        {
            this->view.x += val * times;
        }

        void PCamera::rotateViewY(float val, int times)
        {
            this->view.y += val * times;
        }

        float PCamera::getRotateValue()
        {
            return this->cameraRotateValue;
        }
    }
}
