/* 
 * File:   camera.h
 * Author: aljosa
 *
 * Created on September 7, 2008, 4:34 PM
 *
 * Inspired by camera tutorial by Allen Sherrod
 * www.UltimateGameProgramming.com
 */

#ifndef __CAMERA_H
#define	__CAMERA_H

#include <cmath>
#include "vector.h"

#define UP 0.1
#define DOWN -0.1
#define LEFT 0.1
#define RIGHT -0.1

namespace PacGame
{
    namespace GameClasses
    {
        class PCamera
        {
        private:
        public:
            void setCamera(PVector3D position, PVector3D view, PVector3D up);
            void moveCamera(float direction);
            void rotateCamera(float angle, PVector3D speed);
            
            PVector3D position;
            PVector3D view;
            PVector3D up;
        };
        
    }
}



#endif	/* _CAMERA_H */

