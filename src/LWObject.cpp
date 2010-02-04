/* 
 * File:   LWObject.cpp
 * Author: aljosa
 *
 * Created on February 4, 2010, 7:20 PM
 */

// LWObject.cpp: implementation of the CLWObject class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
#include "LWObject.h"
#include <math.h>
#include "messages.h"


namespace PacGame
{
    namespace LWFormat
    {


        //////////////////////////////////////////////////////////////////////
        // Construction/Destruction
        //////////////////////////////////////////////////////////////////////

        CLWObject::CLWObject()
        {
                pts = NULL;
                plys = NULL;
                srfs = NULL;
                numpoints = 0;
                numpolygons = 0;
                numsurfaces = 0;
                activeSurfIndex = 0;
        }

        CLWObject::~CLWObject()
        {
                Clear();
        }

        void CLWObject::Clear()
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

        bool CLWObject::Load(char *path)
        {
                FILE *fp;
                fp = fopen(path, "rb");


                // try to open file
                if (fp == NULL) { // error loading
                    PacGame::Messages::errorMessage("Problem with loading LW object:");
                    cout<<path<<endl;

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
                        srfs = new SURFACE;
                        numsurfaces = 1;
                        srfs->red = 200;
                        srfs->green = 200;
                        srfs->blue = 200;
                        strcpy(srfs->name,"Default");
                }
                CalcNormals();

                fclose(fp);
                return true;
        }

        bool CLWObject::FindChunk(FILE *fp, const char *chunk){
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

        bool CLWObject::FindNextChunk(FILE *fp, const char *chunk){
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

        int CLWObject::LoadPoints(FILE *fp)
        {
                int numpts, count, length;
                VECTOR *pt;

                if (!FindChunk(fp, "PNTS")) return 0;

                //Must be point list
                if (!ReadInt(fp, length)) return 0;
                numpts = length/12;
                pts = new VECTOR[numpts];;
                if (!pts) return 0;

                count=0;
                pt = pts;

                while(count<length){
                        if (!ReadFloat(fp, pt->x)) return 0;
                        if (!ReadFloat(fp, pt->y)) return 0;
                        if (!ReadFloat(fp, pt->z)) return 0;
                        pt->z = -pt->z;
                        pt++;
                        count+=12;
                }
                numpoints=numpts;

                //Must have gone OK
                return numpts;
        }

        int CLWObject::LoadPolygons(FILE *fp)
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

        bool CLWObject::ReadInt(FILE *fp, int &i)
        {
                int r;
                char rd[4], *ci = (char*)&i;
                r = fread(rd,4,1,fp);
                if (r!=1) return false;
                ci[0]=rd[3]; ci[1]=rd[2]; ci[2]=rd[1]; ci[3]=rd[0];
                return true;
        }

        bool CLWObject::ReadFloat(FILE * fp, float &f)
        {
                int r;
                char rd[4], *cf = (char*)&f;

                r=fread(rd,4,1,fp);
                if (r!=1) return false;
                cf[0]=rd[3]; cf[1]=rd[2]; cf[2]=rd[1]; cf[3]=rd[0];
                return true;
        }

        int CLWObject::AddPolygon(FILE * fp)
        {
                int j;
                unsigned short s, numverts;
                POLYGON *ply;

                if (!ReadShort(fp, numverts)) return 0;

                //Update Polygon storage
                ply = new POLYGON[numpolygons + 1];
                if (!ply) return 0;
                if (plys) memcpy(ply, plys, sizeof(POLYGON) * numpolygons);
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

        bool CLWObject::ReadShort(FILE *fp, unsigned short &s)
        {
                char buf[2], *cs = (char*)&s;
                int r;

                r=fread(&buf, 2, 1, fp);
                if (r!=1) return false;
                cs[0]=buf[1]; cs[1]=buf[0];

                return true;
        }

        bool CLWObject::ReadSubChunk(char *buf, unsigned short &s, FILE *fp)
        {
                //Read header
                if (!fread(buf,4,1,fp)) return false;
                //Read sub chunk length
                if (!ReadShort(fp,s)) return false;
                return true;
        }

        bool CLWObject::LoadSurfaces(FILE* fp)
        {
                char buf[4];
                int i, length, count;
                float f;
                unsigned short s, e;
                SURFACE *srf;

                while(1){
                        if (!FindNextChunk(fp, "SURF")) return true;

                        srf = new SURFACE[numsurfaces+1];
                        if (srfs){
                                memcpy(srf, srfs, numsurfaces * sizeof(SURFACE));
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

        void CLWObject::CalcNormals()
        {
            POLYGON *ply = plys;
            int a,b,c;
            VECTOR v1,v2,v3;

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

        bool CLWObject::LoadTags(FILE *fp)
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
}
