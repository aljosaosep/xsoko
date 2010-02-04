/*
 * File:   LWObject.h
 * Author: aljosa
 *
 * Created on February 4, 2010, 7:17 PM
 */

#ifndef _LWOBJECT_H
#define	_LWOBJECT_H

#include <cstdio>
#include <cstring>
#include <iostream>

#include "CommonStructures.h"

using namespace PacGame::Structures;
using namespace std;

/*namespace PacGame
{
    namespace LWFormat
    {*/
   /*     class LWObject
        {
        public:
                VECTOR *pts;    // oglisca
                POLYGON *plys;  // mnogokotniki
                SURFACE *srfs;  // povrsja

                int numpoints, numpolygons, numsurfaces;
                int activeSurfIndex;

                LWObject();
                //~CLWObject();  /// !!!!!!!!!!!!!!!!!!!!!!!!!!!! (memory leak warning)
                bool LoadTags(FILE *fp);
                bool FindChunk(FILE *fp, const char *chunk);
                bool FindNextChunk(FILE *fp, const char *chunk);
                int LoadPoints(FILE *fp);
                int LoadPolygons(FILE *fp);
                bool LoadSurfaces(FILE *fp);
                bool ReadInt(FILE *fp, int &i);
                bool ReadFloat(FILE * fp, float &f);
                int AddPolygon(FILE * fp);
                bool ReadShort(FILE * fp, unsigned short &s);
                bool ReadSubChunk(char *buf, unsigned short &s, FILE *fp);
                void CalcNormals();
                void Clear();
                bool Load(char *path);
        };*/
  /*  }
}*/

#endif	/* _LWOBJECT_H */


