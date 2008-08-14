/*
 * Codename: xSoko
 * File: renderer-texture.cpp
 *
 * Summary:
 * Includes texture class implementation
 *
 * Author: Aljosa Osep 2007
 * Changes:
 * Aljosa 2008
 * Jernej Skrabec June 19 2008
*/

#include "renderer.h"
#include "../zip/zipfile.h"

namespace PacGame
{
      namespace RenderMaschine
      {
              // constructors
          //PTexture::PTexture() {}
          
          PTexture::PTexture(string _filename)
          {
                  type = GL_RGBA;  // sets texture type
                  filename = _filename; // sets filename
          }

          PTexture::PTexture(string _filename, string type, bool filter)
          {
                  // standard procedure
                  this->type = GL_RGBA;
                  filename = _filename;

                  // gen
                  if(type == "tga")
                          makeTgaTexture(filter);
                  else
                          Messages::errorMessage("Unknown image format type, bad texture class initialization! Blame developers for this!");

                  // gen
        /*	  switch(type)
                  {
                  case "tga":
                          makeTgaTexture(filter);
                          break;

                  default:
                          msg.errorMessage("Unknown image format type, bad texture class initialization! Blame developers for this!");
                          break;
                  }*/
          }

          PTexture::~PTexture()
          {
                //  free(texture.imageData);
                  Messages::infoMessage("Texture released from memory.");
          } 
          
          void PTexture::setPath(string filename)
          {
              this->filename = filename;
          }

          bool PTexture::loadTGA()
          {
                  GLubyte	TGAheader[12] = {0,0,2,0,0,0,0,0,0,0,0,0};		// uncompressed TGA Header
                  GLubyte	TGAcompare[12];						// for compare...
                  GLubyte	header[6];						// first 6 bits
                  unsigned	bytesPerPixel;						// number of bytes per pixel in tga image
                  int	imageSize;						// store image size
                  unsigned	temp;							
        //	  unsigned	type  = GL_RGBA; 	

                  ZipFile zFile("data/textura.zip"); // open zip file
                  zFile.openFile(filename.c_str());  // open file

                  if( (!zFile.isFileOpened()) ||							
                        zFile.readFile(TGAcompare, sizeof(TGAcompare)) != sizeof(TGAcompare) ||         // are 12 bytes readable?
                        memcmp(TGAheader,TGAcompare,sizeof(TGAheader)) != 0 ||				// header match?
                        zFile.readFile(header,sizeof(header)) != sizeof(header))				// :)
                  {
                          if (!zFile.isFileOpened())
                          {
                                  Messages::errorMessage("Texture file is empty!");
                                  return false;						// :(
                          }
                          else 
                          {
                                  Messages::errorUnknown();
                                  zFile.closeZip();
                                  return false;						
                          }
                  }

                  texture.width  = header[1] * 256 + header[0];				// get width (highbyte*256+lowbyte)
                  texture.height = header[3] * 256 + header[2];				// get height	(highbyte*256+lowbyte)

                  if(texture.width	<=0 ||						// width and height must be > 0
                         texture.height	<=0 ||						
                         (header[4]!=24 && header[4]!=32))				// 24 or 32 bit
                  {

                          Messages::errorMessage("Texture isn't 32 or 24 bit OR texture width or height isn't greater than zero :D");
                          zFile.closeZip();
                          return false;
                  } 

                  texture.bpp	= header[4];						// grab The TGA's Bits Per Pixel (24 or 32)
                  bytesPerPixel	= texture.bpp/8;					// divide By 8 To Get The Bytes Per Pixel
                  imageSize		= texture.width*texture.height*bytesPerPixel;	// Calculate The Memory Required 

                  texture.imageData=(GLubyte *)malloc(imageSize);			// reserve memory to store TGA data

                  if(texture.imageData==NULL ||					// storage memory exist... ?
                          zFile.readFile(texture.imageData, imageSize)!=imageSize)	// Does The Image Size Match The Memory Reserved?
                  {
                          if(texture.imageData!=NULL)					// release
                          {
                                  Messages::errorMessage("TGA image data is empty. Releasing memory...");
                                  free(texture.imageData);	
                          }

                          Messages::errorUnknown();							
                          zFile.closeZip();
                          return false;							
                  }

                  for(int i=0; i<imageSize; i+=bytesPerPixel)	// Swaps The 1st And 3rd Bytes, R and B
                  {
                          temp=texture.imageData[i];					
                          texture.imageData[i] = texture.imageData[i + 2];		
                          texture.imageData[i + 2] = temp;				
                  }
								
                  zFile.closeZip();
                  Messages::infoTexture(filename.c_str());
                  return true;
          }

          void PTexture::generateTextureMipmap()
          {
                  PTextureImage *texPtr  = &texture;
                  // TEXTURE BUILDING SECTION
                  glGenTextures(1, &texPtr[0].texID);					// Generate texture IDs
                  // MipMap filtering
                  glBindTexture(GL_TEXTURE_2D, texPtr[0].texID);
                  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
                  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST); 

                  if (texPtr[0].bpp==24)							// if tga is 24 bit
                  {
                          Messages::initMessage("TGA texture/Alpha channel", false);
                          type=GL_RGB;							// type je GL_RGB
                  }
                  else
                          Messages::initMessage("TGA texture/Alpha channel", true);

                  gluBuild2DMipmaps(GL_TEXTURE_2D, type, texPtr[0].width, texPtr[0].height, type, GL_UNSIGNED_BYTE, texPtr[0].imageData);
                  Messages::infoMessage("Texture was successfully generated, mipmap filtering.");

          }

          void PTexture::generateTextureLinear()
          {
                  PTextureImage *texPtr  = &texture;
                  // TEXTURE BUILDING SECTION
                  glGenTextures(1, &texPtr[0].texID);					// Generate texture IDs
                  glBindTexture(GL_TEXTURE_2D, texPtr[0].texID);				// binf texture
                  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear 
                  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	

                  if (texPtr[0].bpp==24)							// if tga is 24 bit
                  {
                          Messages::initMessage("TGA texture/Alpha channel", false);
                          type=GL_RGB;							// type je GL_RGB
                  }
                  else
                          Messages::initMessage("TGA texture/Alpha channel", true);

                  glTexImage2D(GL_TEXTURE_2D, 0, type, texPtr[0].width, texPtr[0].height, 0, type, GL_UNSIGNED_BYTE, texPtr[0].imageData);
                  Messages::infoMessage("Texture was successfully generated, linear filtering.");

          }

          bool PTexture::makeTgaTexture(bool mipmap)
          {
                  if(!loadTGA())
                  {
                          Messages::infoMessage("Texture creation failed.");
                          return false;
                  }

                  if(mipmap)
                          generateTextureMipmap();
                  else
                          generateTextureLinear();

                  Messages::infoMessage("Texture created, ready for use.");
                  return true;

          }

          // getters
          unsigned PTexture::getTexID()
          {
                  return texture.texID;
          }
      }
}
