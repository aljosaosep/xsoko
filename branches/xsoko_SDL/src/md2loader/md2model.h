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
 * File:   md2model.h
 * Author: Martin Šavc
 * 
 * Summary: Loader class for Md2 file format.
 *
 * Done with instructions by David Henry (http://tfc.duke.free.fr/coding/md2-specs-en.html).
 * 
 * Created on Tuesday, June 16 2009
 */

#ifndef MD2MODEL_H_
#define MD2MODEL_H_

#include <iostream>
#include "../CommonStructures.h"



using namespace std;

namespace PacGame
{
	namespace Md2Format
	{
		/*********************************
		 * Md2 data structures
		 * 
		 * These are structures, that are used in the 
		 * md2 format.
		 * 
		 * Created by David Henry
		 * *******************************/
		/* MD2 header */
		struct md2_header_t
		{
			int ident;                  /* magic number: "IDP2" */
			int version;                /* version: must be 8 */

			int skinwidth;              /* texture width */
			int skinheight;             /* texture height */

			int framesize;              /* size in bytes of a frame */

			int num_skins;              /* number of skins */
			int num_vertices;           /* number of vertices per frame */
			int num_st;                 /* number of texture coordinates */
			int num_tris;               /* number of triangles */
			int num_glcmds;             /* number of opengl commands */
			int num_frames;             /* number of frames */

			int offset_skins;           /* offset skin data */
			int offset_st;              /* offset texture coordinate data */
			int offset_tris;            /* offset triangle data */
			int offset_frames;          /* offset frame data */
			int offset_glcmds;          /* offset OpenGL command data */
			int offset_end;             /* offset end of file */
		};
		
		/* Vector */
		typedef float vec3_t[3];
		
		/* Texture name */
		struct md2_skin_t
		{
			char name[64];              /* texture file name */
		};
		
		/* Texture coords */
		struct md2_texCoord_t
		{
			short s;
			short t;
		};
		
		/* Triangle info */
		struct md2_triangle_t
		{
			unsigned short vertex[3];   /* vertex indices of the triangle */
			unsigned short st[3];       /* tex. coord. indices */
		};
		
		/* Compressed vertex */
		struct md2_vertex_t
		{
			unsigned char v[3];         /* position */
			unsigned char normalIndex;  /* normal vector index */
		};
		
		/* Model frame */
		struct md2_frame_t
		{
			vec3_t scale;               /* scale factor */
			vec3_t translate;           /* translation vector */
			char name[16];              /* frame name */
			struct md2_vertex_t *verts; /* list of frame's vertices */
		};
		/*************************************
		 *  Md2File
		 * 
		 *  This class read the file, check for md2
		 *  and stores valuable information.
		 * 
		 * Martin Šavc
		 * ************************************/
		class Md2Model
		{
		private:
			md2_header_t md2Header;	// pointer to the header information
			
			md2_skin_t* texture_file_names;
			md2_texCoord_t* texture_coordinates;
			
			md2_frame_t* frames;
			md2_triangle_t* triangles;
			int* oglCommands;
			
			bool textured;
			int textureId;
			
			float *model_vertex_array;
			float *model_normal_array;
			float *model_skin_array;
		
		public:
			Md2Model(istream& md2data);
			~Md2Model();
			
			void SetTexture(int id); // set the texture number
			char* GetTextureName(int index); // get the name of the texture from file
			
			int GetNumberOfFrames(); // number of static frames available
			void DrawFrame(float frame);	//draw a frame of the model 
			void DrawFrameOGLC(float frame); // !!! not implemented !!! draw the frame with OpenGL commands
			
			void FileInformation(ostream& output_stream);
		};
	}




        class LWObject
        {
        public:
                PacGame::Structures::VECTOR *pts;    // oglisca
                PacGame::Structures::POLYGON *plys;  // mnogokotniki
                PacGame::Structures::SURFACE *srfs;  // povrsja

                int numpoints, numpolygons, numsurfaces;
                int activeSurfIndex;
                float scalef;

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
        };
}

#endif
