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
#include <cmath>



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
			model_vertex_array = NULL;
			model_normal_array = NULL;
			model_skin_array = NULL;
			
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
			
			model_vertex_array = new float[md2Header.num_tris*3*3];
			model_normal_array = new float[md2Header.num_tris*3*3]; 
			model_skin_array =  new float[md2Header.num_tris*3*2];
				
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
				
			if(model_vertex_array != NULL)
				delete[] model_vertex_array;
			
			if(model_normal_array != NULL)
				delete[] model_normal_array;
			
			if(model_skin_array != NULL)
				delete[] model_skin_array;
				
			
			
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
				
				
				//glBegin(GL_TRIANGLES);
				// triangles
				// every tris has three vertexes, each vertex has 3 points
				
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
							//glTexCoord2f (	(float)texture_coordinates[triangles[c].st[n]].s / md2Header.skinwidth,
							//				(float)texture_coordinates[triangles[c].st[n]].t / md2Header.skinheight);
							model_skin_array[c*6+n*2 + 0] =(float)texture_coordinates[triangles[c].st[n]].s / md2Header.skinwidth;
							model_skin_array[c*6+n*2 + 1] =(float)texture_coordinates[triangles[c].st[n]].t / md2Header.skinheight;
						}

						// calculate the vertex that we actually want to draw, with interpolation
						
						// interpolated normal vector
						norm[0] = anorms_table[prev_vertex->normalIndex] [0] + interpolate * (	anorms_table[next_vertex->normalIndex] [0] -
																						anorms_table[prev_vertex->normalIndex] [0]);
						norm[1] = anorms_table[prev_vertex->normalIndex] [1] + interpolate * (	anorms_table[next_vertex->normalIndex] [1] -
																						anorms_table[prev_vertex->normalIndex] [1]);
						norm[2] = anorms_table[prev_vertex->normalIndex] [2] + interpolate * (	anorms_table[next_vertex->normalIndex] [2] -
																						anorms_table[prev_vertex->normalIndex] [2]);
						//glNormal3fv(norm);
						model_normal_array[c*9+n*3+0] = norm[0];
						model_normal_array[c*9+n*3+1] = norm[1];
						model_normal_array[c*9+n*3+2] = norm[2];
						
						
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
						
						model_vertex_array[c*9+n*3+0] = v[0];
						model_vertex_array[c*9+n*3+1] = v[1];
						model_vertex_array[c*9+n*3+2] = v[2];
						
						
						// draw the vertex
						//glVertex3fv(v);
					}
				}
				//glEnd();
				
             			 glEnable(GL_CULL_FACE);
              			glEnableClientState(GL_NORMAL_ARRAY);

             			glCullFace(GL_FRONT);
              			
				glTexCoordPointer(2, GL_FLOAT, 0, model_skin_array);
				glNormalPointer(GL_FLOAT,0,model_normal_array);
				glVertexPointer(3,GL_FLOAT,0,model_vertex_array);
				
				glDrawArrays(GL_TRIANGLES,0,md2Header.num_tris*3);
				
				
              			glDisableClientState(GL_NORMAL_ARRAY);
                  		glDisable(GL_CULL_FACE);
				
			}else //we want to draw one of the basic frames
			{
				//glBegin(GL_TRIANGLES);
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
							//glTexCoord2f (	(float)texture_coordinates[triangles[c].st[n]].s / md2Header.skinwidth,
							//				(float)texture_coordinates[triangles[c].st[n]].t / md2Header.skinheight);
							model_skin_array[c*6+n*2 + 0] =(float)texture_coordinates[triangles[c].st[n]].s / md2Header.skinwidth;
							model_skin_array[c*6+n*2 + 1] =(float)texture_coordinates[triangles[c].st[n]].t / md2Header.skinheight;
						}
						// set the normal
						model_normal_array[c*9+n*3+0] = anorms_table[prev_vertex->normalIndex][0];
						model_normal_array[c*9+n*3+1] = anorms_table[prev_vertex->normalIndex][1];
						model_normal_array[c*9+n*3+2] = anorms_table[prev_vertex->normalIndex][2];
						//glNormal3fv(anorms_table[prev_vertex->normalIndex]);
						// calculate the vertex that we actually want to draw
						v[0] = prev_frame->scale[0] * prev_vertex->v[0] + prev_frame->translate[0];
						v[1] = prev_frame->scale[1] * prev_vertex->v[1] + prev_frame->translate[1];
						v[2] = prev_frame->scale[2] * prev_vertex->v[2] + prev_frame->translate[2];
						
						model_vertex_array[c*9+n*3+0] = v[0];
						model_vertex_array[c*9+n*3+1] = v[1];
						model_vertex_array[c*9+n*3+2] = v[2];
						// draw the vertex
						//glVertex3fv(v);
					}
				}
				//glEnd();
				
             			 glEnable(GL_CULL_FACE);
              			glEnableClientState(GL_NORMAL_ARRAY);

             			glCullFace(GL_FRONT);
              			
				glTexCoordPointer(2, GL_FLOAT, 0, model_skin_array);
				glNormalPointer(GL_FLOAT,0,model_normal_array);
				glVertexPointer(3,GL_FLOAT,0,model_vertex_array);
				
				glDrawArrays(GL_TRIANGLES,0,md2Header.num_tris*3);
				
				
              			glDisableClientState(GL_NORMAL_ARRAY);
              			glDisable(GL_CULL_FACE);
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


        LWObject::LWObject()
        {
                pts = NULL;
                plys = NULL;
                srfs = NULL;
                numpoints = 0;
                numpolygons = 0;
                numsurfaces = 0;
                activeSurfIndex = 0;

                scalef = 0.37;
        }

       /* CLWObject::~CLWObject()
        {
                Clear();
        }*/

        void LWObject::Clear()
        {
                if (pts) delete [] pts;
                if (plys) delete [] plys;
                if (srfs) delete [] srfs;
                pts = NULL;
                plys = NULL;
                srfs = NULL;
                numpoints = 0;
                numpolygons = 0;
                numsurfaces = 0;
        }

        bool LWObject::Load(char *path)
        {
                FILE *fp;
                fp = fopen(path, "rb");


                // try to open file
                if (fp == NULL) { // error loading
                //    PacGame::Messages::errorMessage("Problem with loading LW object:");
                    cout<<"Problem with loading LW object: "<<path<<endl;

                    return false;
                }



                Clear();

                // file open; proceed with loading data
                LoadPoints(fp);
                if (numpoints==0){
                        Clear();
                        fclose(fp);
                        return false;
                }
                LoadPolygons(fp);
                if (numpolygons==0){
                        Clear();
                        fclose(fp);
                        return false;
                }
                if (!LoadSurfaces(fp)){
                        //Just a default surface
                        srfs = new PacGame::Structures::SURFACE;
                        numsurfaces = 1;
                        srfs->red = 200;
                        srfs->green = 200;
                        srfs->blue = 200;
                        strcpy(srfs->name,"Default");
                }
                CalcNormals();

                fclose(fp);
//                PacGame::Messages::infoMessage("LW model "+ string(path) +" in memory");
                cout<<"Model in memory: "<<path<<endl;

                return true;
        }

        bool LWObject::FindChunk(FILE *fp, const char *chunk){
                char buf[4];
                int length;

                //Go to the start
                fseek(fp,12,SEEK_SET);
                fread(buf,4,1,fp);

                while (strncmp(buf, chunk, 4)){
                        //No match so skip
                        if (!ReadInt(fp,length)) return false;
                        if (length % 2) length++;
                        if (fseek(fp, length, SEEK_CUR)) return false;
                        fread(buf,4,1,fp);
                }

                return true;
        }

        bool LWObject::FindNextChunk(FILE *fp, const char *chunk){
                char buf[4];
                int length;

                fread(buf,4,1,fp);

                while (strncmp(buf, chunk, 4)){
                        //No match so skip
                        if (!ReadInt(fp,length)) return false;
                        if (length % 2) length++;
                        if (fseek(fp, length, SEEK_CUR)) return false;
                        fread(buf,4,1,fp);
                }

                return true;
        }

        int LWObject::LoadPoints(FILE *fp)
        {
                int numpts, count, length;
                PacGame::Structures::VECTOR *pt;

                if (!FindChunk(fp, "PNTS")) return 0;

                //Must be point list
                if (!ReadInt(fp, length)) return 0;
                numpts = length/12;
                pts = new PacGame::Structures::VECTOR[numpts];
                if (!pts) return 0;

                count=0;
                pt = pts;



                while(count<length){
                        if (!ReadFloat(fp, pt->x)) return 0;
                        if (!ReadFloat(fp, pt->y)) return 0;
                        if (!ReadFloat(fp, pt->z)) return 0;

                        // scale
                        pt->x *= scalef;
                        pt->y *= scalef;
                        pt->z *= scalef;

                        pt->z = -pt->z;
                        pt++;
                        count+=12;
                }
                numpoints=numpts;

                //Must have gone OK
                return numpts;
        }

        int LWObject::LoadPolygons(FILE *fp)
        {
                int r,count,length;
                char buf[4];
                if (!FindChunk(fp, "POLS")) return 0;

                //Must be polygon list
                if (!ReadInt(fp,length)) return 0;
                if (length%2) length++;

                numpolygons=0;
                fread(buf, 1, 4, fp);
                if (strncmp(buf, "FACE", 4)!=0) return 0;
                count = 4;

                while(count<length){
                        r = AddPolygon(fp);
                        if (r==0) return 0;
                        //must be OK to point to the next one
                        count+=r;
                }
                if (!LoadTags(fp)) return 0;

                return numpolygons;
        }

        bool LWObject::ReadInt(FILE *fp, int &i)
        {
                int r;
                char rd[4], *ci = (char*)&i;
                r = fread(rd,4,1,fp);
                if (r!=1) return false;
                ci[0]=rd[3]; ci[1]=rd[2]; ci[2]=rd[1]; ci[3]=rd[0];
                return true;
        }

        bool LWObject::ReadFloat(FILE * fp, float &f)
        {
                int r;
                char rd[4], *cf = (char*)&f;

                r=fread(rd,4,1,fp);
                if (r!=1) return false;
                cf[0]=rd[3]; cf[1]=rd[2]; cf[2]=rd[1]; cf[3]=rd[0];
                return true;
        }

        int LWObject::AddPolygon(FILE * fp)
        {
                int j;
                unsigned short s, numverts;
                PacGame::Structures::POLYGON *ply;

                if (!ReadShort(fp, numverts)) return 0;

                //Update Polygon storage
                ply = new PacGame::Structures::POLYGON[numpolygons + 1];
                if (!ply) return 0;
                if (plys) memcpy(ply, plys, sizeof(PacGame::Structures::POLYGON) * numpolygons);
                delete [] plys;
                plys = ply;
                ply = &ply[numpolygons];

                for (j=0;j<numverts;j++){
                        if (!ReadShort(fp,s)) return 0;
                        if (j<4) ply->p[j]=(int)s;
                }

                ply->numverts = (numverts<5)?numverts:4;
                ply->srfID = 0;
                numpolygons++;

                return numverts * 2 + 2;
        }

        bool LWObject::ReadShort(FILE *fp, unsigned short &s)
        {
                char buf[2], *cs = (char*)&s;
                int r;

                r=fread(&buf, 2, 1, fp);
                if (r!=1) return false;
                cs[0]=buf[1]; cs[1]=buf[0];

                return true;
        }

        bool LWObject::ReadSubChunk(char *buf, unsigned short &s, FILE *fp)
        {
                //Read header
                if (!fread(buf,4,1,fp)) return false;
                //Read sub chunk length
                if (!ReadShort(fp,s)) return false;
                return true;
        }

        bool LWObject::LoadSurfaces(FILE* fp)
        {
                char buf[4];
                int i, length, count;
                float f;
                unsigned short s, e;
                PacGame::Structures::SURFACE *srf;

                while(1){
                        if (!FindNextChunk(fp, "SURF")) return true;

                        srf = new PacGame::Structures::SURFACE[numsurfaces+1];
                        if (srfs){
                                memcpy(srf, srfs, numsurfaces * sizeof(PacGame::Structures::SURFACE));
                                delete [] srfs;
                        }
                        srfs = srf;
                        srf = &srfs[numsurfaces];
                        numsurfaces++;

                        //Must be a surface
                        if (!ReadInt(fp,length)) return false;
                        if (length%2) length++;

                        //Read name
                        count=0;
                        buf[0]=1;
                        while(buf[0]){
                                fread(buf,1,1,fp);
                                srf->name[count++]=buf[0];
                        }

                        if (count%2){
                                count++;
                                fread(buf,1,1,fp);
                        }

                        //Read parent name
                        i=0;
                        buf[0]=1;
                        while(buf[0]){
                                fread(buf,1,1,fp);
                                i++;
                        }

                        count += i;
                        if (i%2){
                                count++;
                                fread(buf,1,1,fp);
                        }

                        //Read sub-chunks
                        while (count<length){
                                if (!ReadSubChunk(buf,s,fp)) return false;
                                if (s % 2) s++;
                                count += (s + 6);
                                if (strncmp(buf, "COLR", 4)==0){
                                        //Found colour
                                        if (!ReadFloat(fp, f)) return false;
                                        srf->red = (short)(f * 255.0f);
                                        if (!ReadFloat(fp, f)) return false;
                                        srf->green = (short)(f * 255.0f);
                                        if (!ReadFloat(fp, f)) return false;
                                        srf->blue = (short)(f * 255.0f);
                                        if (!ReadShort(fp, e)) return false;
                                        if (e!=0){
                                        //	AfxMessageBox("Colour envelopes not supported");
                                            cout<<"Colour envelopes not supported"<<endl;
                                                return false;
                                        }
                                        continue;
                                }
                                //If we got to here then the chunk was not found so skip by s
                                fseek(fp, s, SEEK_CUR);
                        }
                }

                return true;
        }

        void LWObject::CalcNormals()
        {
            PacGame::Structures::POLYGON *ply = plys;
            int a,b,c;
            PacGame::Structures::VECTOR v1,v2,v3;

            for (int i=0; i<this->numpoints; i++) {
                this->pts[i].px = 0.0;
                this->pts[i].py = 0.0;
                this->pts[i].pz = 0.0;
            }

            //Calculate the normal
          /*  for (int i=0; i < numpolygons;i++){
                        a=ply->p[0]; b=ply->p[1], c=ply->p[2];
                 // Vstavite izraun normal
                        ply++;
            }*/



            float r1[3],r2[3],abs; // vektorja za izracun normale
            // Vstavite izra?un normal
            for (int i=0; i < numpolygons;i++)
            {
                a = plys[i].p[0]; // indeks prvega oglisca
                b = plys[i].p[1]; // indeks drugega oglisca
                c = plys[i].p[2]; // indeks tretjega oglisca

                //Izra?un vektorjev r1 in r2
                r1[0] = this->pts[a].x - this->pts[b].x;
                r1[1] = this->pts[a].y - this->pts[b].y;
                r1[2] = this->pts[a].z - this->pts[b].z;

                r2[0] = this->pts[c].x - this->pts[b].x;
                r2[1] = this->pts[c].y - this->pts[b].y;
                r2[2] = this->pts[c].z - this->pts[b].z;

                // Izra?un vektorskega produkta r1 x r2 in normiranje
                plys[i].nx = r1[1]*r2[2] - r1[2]*r2[1];
                plys[i].ny = r1[2]*r2[0] - r1[0]*r2[2];
                plys[i].nz = r1[0]*r2[1] - r1[1]*r2[0];

                abs = sqrt(plys[i].nx*plys[i].nx + plys[i].ny*plys[i].ny + plys[i].nz*plys[i].nz); // izracun dolzine vektorja r1xr2

                // normiranje
                plys[i].nx /= abs;
                plys[i].ny /= abs;
                plys[i].nz /= abs;


                // Izra?un normale ogli??a

                // izracun nove normale prvega oglisca
                this->pts[a].px = this->pts[a].px + ((plys[i].nx - this->pts[a].px) / i+1);
                this->pts[a].py = this->pts[a].py + ((plys[i].ny - this->pts[a].py) / i+1);
                this->pts[a].pz = this->pts[a].pz + ((plys[i].nz - this->pts[a].pz) / i+1);
                // normala drugega oglisca
                this->pts[b].px = this->pts[b].px + ((plys[i].nx - this->pts[b].px) / i+1);
                this->pts[b].py = this->pts[b].py + ((plys[i].ny - this->pts[b].py) / i+1);
                this->pts[b].pz = this->pts[b].pz + ((plys[i].nz - this->pts[b].pz) / i+1);
                // normala tretjega oglisca
                this->pts[c].px = this->pts[c].px + ((plys[i].nx - this->pts[c].px) / i+1);
                this->pts[c].py = this->pts[c].py + ((plys[i].ny - this->pts[c].py) / i+1);
                this->pts[c].pz = this->pts[c].pz + ((plys[i].nz - this->pts[c].pz) / i+1);

                if (this->plys[i].numverts == 4) {
                    int d = plys[i].p[3];

                    // normala cetrtega oglisca
                    this->pts[d].px = this->pts[d].px + ((plys[i].nx - this->pts[d].px) / i+1);
                    this->pts[d].py = this->pts[d].py + ((plys[i].ny - this->pts[d].py) / i+1);
                    this->pts[d].pz = this->pts[d].pz + ((plys[i].nz - this->pts[d].pz) / i+1);
                }
            }

            // normiranje vseh normal v ogliscih
            for (int i=0; i<this->numpoints; i++)
            {
                abs = sqrt(this->pts[i].px*this->pts[i].px + this->pts[i].py*this->pts[i].py + this->pts[i].pz*this->pts[i].pz);
                this->pts[i].px /= abs;
                this->pts[i].py /= abs;
                this->pts[i].pz /= abs;
            }
        }

        bool LWObject::LoadTags(FILE *fp)
        {
                int count, length;
                unsigned short plyID, srfID;
                char buf[4];

                if (!FindNextChunk(fp, "PTAG")) return false;
                if (!ReadInt(fp, length)) return false;

                fread(buf, 4, 1, fp);
                if (strncmp(buf, "SURF", 4)!=0){
                        fseek(fp, length, SEEK_CUR);
                        return true;
                }

                count = 4;

                while (count<length){
                        if (!ReadShort(fp, plyID)) return false;
                        if (!ReadShort(fp, srfID)) return false;
                        if (plyID<numpolygons){
                                plys[plyID].srfID = srfID;
                        }
                        count += 4;
                }

                return true;
        }
}