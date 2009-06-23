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
 * File:   md2model.cpp
 * Author: Martin Šavc
 *
 * Created on Tuesday, June 16 2009
 */

#include "md2model.h"

#ifdef _WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
#endif

#include <GL/gl.h>



namespace PacGame
{
	namespace Md2Format
	{
		/* Table of precalculated normals */
		vec3_t anorms_table[162] = {
		#include "Anorms.h"
		};
		
		/*******************************
		 * Md2File constructor, destructor
		 * 
		 * Created: Martin Šavc, Tuesday, June 16 2009
		 * *****************************/
		Md2Model::Md2Model(istream& md2data)
		{
			md2data.read((char*) &md2Header, sizeof(md2_header_t));
			// check header identification and version
			if((md2Header.ident != 844121161) || (md2Header.version != 8))
			{
				return;
			}
			
			textured = false;
			textureId = -1;
			// initialize pointers to NULL
			texture_file_names = NULL;
			texture_coordinates = NULL;
			frames = NULL;
			triangles = NULL;
			oglCommands = NULL;
			
			// load texture file names
			texture_file_names = new md2_skin_t[md2Header.num_skins];
			md2data.seekg(md2Header.offset_skins);
			md2data.read((char*) texture_file_names, sizeof(md2_skin_t)*md2Header.num_skins);
			
			// load texture coordinates
			texture_coordinates = new md2_texCoord_t[md2Header.num_st];
			md2data.seekg(md2Header.offset_st);
			md2data.read((char*) texture_coordinates, sizeof(md2_texCoord_t)*md2Header.num_st);
			
			// load triangles
			triangles = new md2_triangle_t[md2Header.num_tris];
			md2data.seekg(md2Header.offset_tris);
			md2data.read((char*) triangles, sizeof(md2_triangle_t)*md2Header.num_tris);
			
			// load OpenGL commands
			oglCommands = new int[md2Header.num_glcmds];
			md2data.seekg(md2Header.offset_glcmds);
			md2data.read((char*) oglCommands, sizeof(int)*md2Header.num_glcmds);
			
			
			// load frames
			frames = new md2_frame_t[md2Header.num_frames];
			md2data.seekg(md2Header.offset_frames);
			
			// load vertices inside frames
			for(int c = 0; c < md2Header.num_frames; c++)
			{
				frames[c].verts = new md2_vertex_t[md2Header.num_vertices];
				md2data.read((char*)&frames[c].scale,sizeof(vec3_t));
				md2data.read((char*)&frames[c].translate,sizeof(vec3_t));
				md2data.read((char*)&frames[c].name,sizeof(char)*16);
				md2data.read((char*)frames[c].verts,sizeof(md2_vertex_t)*md2Header.num_vertices);
			}
			
			
				
		}	
		
		Md2Model::~Md2Model()
		{
			// clean up
			if(texture_file_names != NULL)
				delete texture_file_names;
				
			if(texture_coordinates != NULL)
				delete texture_coordinates;
				
			if(triangles != NULL)
				delete triangles;
			
			if(oglCommands != NULL)
				delete oglCommands;
				
			
			
		}
		/**************************************
		 * GetNumberOfFrames
		 * ************************************/
		int Md2Model::GetNumberOfFrames()
		{
			return md2Header.num_frames;
		}
		
		/**************************************
		 * DrawFrame
		 * 
		 * Draws the frame to OpenGL screen buffer, with 
		 * linear interpolation, where required.
		 * 
		 * double frame - The number of the frame. Integer numbers
		 * represent frames saved in the Md2File, while decimal numbers 
		 * give interpolated frames. The number must be smaller or equal 
		 * to the number of frames.
		 * ************************************/
		void Md2Model::DrawFrame(float frame)
		{
			if(frame > float(md2Header.num_frames -1))
			{
				return;	
			}
			
			md2_frame_t* prev_frame,* next_frame = NULL;
			md2_vertex_t* prev_vertex,* next_vertex;
			float v[3];
			float v_p[3], v_n[3];
			float norm[3];
			float interpolate = frame - (float)((int)frame); // decimal part of frame
			
			prev_frame = &frames[(int)frame];
			
			if(textured)
			{
				glBindTexture (GL_TEXTURE_2D, textureId);
			}
			// we want to draw an interpolated frame
			if(interpolate != 0)
			{
				next_frame = &frames[(int)frame+1];
				
				
				glBegin(GL_TRIANGLES);
				// triangles
				for(int c = 0; c < md2Header.num_tris; c++)
				{
					// 3 vertexes of a triangle
					for(int n = 0; n < 3; n++)
					{
						prev_vertex = &prev_frame->verts[triangles[c].vertex[n]];
						next_vertex = &next_frame->verts[triangles[c].vertex[n]];
						
						// texture
						if(textured)
						{
							glTexCoord2f (	(float)texture_coordinates[triangles[c].st[n]].s / md2Header.skinwidth,
											(float)texture_coordinates[triangles[c].st[n]].t / md2Header.skinheight);
						}

						// calculate the vertex that we actually want to draw, with interpolation
						
						// interpolated normal vector
						norm[0] = anorms_table[prev_vertex->normalIndex] [0] + interpolate * (	anorms_table[next_vertex->normalIndex] [0] -
																						anorms_table[prev_vertex->normalIndex] [0]);
						norm[1] = anorms_table[prev_vertex->normalIndex] [1] + interpolate * (	anorms_table[next_vertex->normalIndex] [1] -
																						anorms_table[prev_vertex->normalIndex] [1]);
						norm[2] = anorms_table[prev_vertex->normalIndex] [2] + interpolate * (	anorms_table[next_vertex->normalIndex] [2] -
																						anorms_table[prev_vertex->normalIndex] [2]);
						glNormal3fv(norm);
						
						
						// vertex from previous frame
						v_p[0] = prev_frame->scale[0] * prev_vertex->v[0] + prev_frame->translate[0];
						v_p[1] = prev_frame->scale[1] * prev_vertex->v[1] + prev_frame->translate[1];
						v_p[2] = prev_frame->scale[2] * prev_vertex->v[2] + prev_frame->translate[2];
						
						// vertex from next frame
						v_n[0] = next_frame->scale[0] * next_vertex->v[0] + next_frame->translate[0];
						v_n[1] = next_frame->scale[1] * next_vertex->v[1] + next_frame->translate[1];
						v_n[2] = next_frame->scale[2] * next_vertex->v[2] + next_frame->translate[2];
						
						// interpolated vertex
						v[0] = v_p[0] + interpolate * ( v_n[0] - v_p[0]);
						v[1] = v_p[1] + interpolate * ( v_n[1] - v_p[1]);
						v[2] = v_p[2] + interpolate * ( v_n[2] - v_p[2]);
						
						// draw the vertex
						glVertex3fv(v);
					}
				}
				glEnd();
				
			}else //we want to draw one of the basic frames
			{
				glBegin(GL_TRIANGLES);
				// triangles
				for(int c = 0; c < md2Header.num_tris; c++)
				{
					// 3 vertexes of a triangle
					for(int n = 0; n < 3; n++)
					{
						prev_vertex = &prev_frame->verts[triangles[c].vertex[n]];

						// texture
						if(textured)
						{
							glTexCoord2f (	(float)texture_coordinates[triangles[c].st[n]].s / md2Header.skinwidth,
											(float)texture_coordinates[triangles[c].st[n]].t / md2Header.skinheight);
						}
						// set the normal
						glNormal3fv(anorms_table[prev_vertex->normalIndex]);
						// calculate the vertex that we actually want to draw
						v[0] = prev_frame->scale[0] * prev_vertex->v[0] + prev_frame->translate[0];
						v[1] = prev_frame->scale[1] * prev_vertex->v[1] + prev_frame->translate[1];
						v[2] = prev_frame->scale[2] * prev_vertex->v[2] + prev_frame->translate[2];
						// draw the vertex
						glVertex3fv(v);
					}
				}
				glEnd();
			}	
			
			return;
		}
		
		/**************************************
		 * DrawFrameOGLC
		 * 
		 * Draws the frame with OpenGL commands,
		 * stored in the Md2 file.
		 * 
		 * !! Not implemented !!
		 * ************************************/
		void Md2Model::DrawFrameOGLC(float frame)
		{
			
			
			return;
		}
		
		/*****************************************
		 * SetTexture
		 * 
		 * Set the texture id to argument id and
		 * enable textured rendering.
		 * ***************************************/
		void Md2Model::SetTexture(int id)
		{
			textureId = id;
			textured = true;
		}
		 
		/*****************************************
		 * GetTextureName
		 * 
		 * Get the name of the texture from file.
		 * If index is out of range, NULL is returned.
		 * ***************************************/
		char* Md2Model::GetTextureName(int index)
		{
			if(index < md2Header.num_skins && index >= 0)
			{
				return texture_file_names[index].name;
			}else
				return NULL;
		}
		
		/*******************************
		 * FileInformation
		 * 
		 * This method passes vital file information as characters to the output_stream argument.
		 * 
		 * Created: Martin Šavc, Tuesday, June 16 2009
		 * *****************************/

		void Md2Model::FileInformation(ostream& output_stream)
		{
			output_stream<<"indent: "<<(const char*) &md2Header.ident<<endl;
			output_stream<<"file version: "<<md2Header.version<<endl;
			output_stream<<endl;
			output_stream<<"texture size (w,h): ("<<md2Header.skinwidth<<","<<md2Header.skinheight<<")"<<endl;
			output_stream<<"number of textures: "<<md2Header.num_skins<<endl;
			output_stream<<"number of texture coordinates: "<<md2Header.num_st<<endl;
			output_stream<<"texture names offset: "<<md2Header.offset_skins<<endl;
			output_stream<<"texture coordinates offset: "<<md2Header.offset_st<<endl;
			output_stream<<endl;
			output_stream<<"size of frame (bytes): "<<md2Header.framesize<<endl;
			output_stream<<"number of frames: "<<md2Header.num_frames<<endl;
			output_stream<<"frames data offset: "<<md2Header.offset_frames<<endl;
			output_stream<<"number of vertices per frame: "<<md2Header.num_vertices<<endl;
			output_stream<<"number of triangles: "<<md2Header.num_tris<<endl;
			output_stream<<"triangles data offset: "<<md2Header.offset_tris<<endl;
			output_stream<<endl;
			output_stream<<"number of OpenGL commands: "<<md2Header.num_glcmds<<endl;
			output_stream<<"OpenGL commands offset: "<<md2Header.offset_glcmds<<endl;
			output_stream<<endl;
			output_stream<<"end of file offset: "<<md2Header.offset_end<<endl;
			output_stream<<endl;
			output_stream<<"frames:"<<endl;
			for(int c = 0; c < md2Header.num_frames; c++)
			{
				cout<<frames[c].name<<endl;
			}
			
		}
	}
}
