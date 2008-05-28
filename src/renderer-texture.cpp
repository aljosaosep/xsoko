/*
  codename: Pac-Game
  Aljosa Osep 2007
*/
#include "renderer.h"

namespace PacGame
{
          namespace RenderMaschine
          {

			  PTexture::PTexture(string _filename)
			  {
				  type = GL_RGBA;
				  filename = _filename;
				  altFilename = filename.c_str();    // transform c++ string into c string, for use common use as string
				 // strcpy(filename, _filename);    // WHY THE FUCK STRCPY DOESN'T WORK???????
			  }

			  PTexture::PTexture(string _filename, string type, bool filter)
			  {
				  // standard procedure
				  type = GL_RGBA;
				  filename = _filename;
				  altFilename = filename.c_str();

				  // gen
				  if(type == "tga")
					  makeTgaTexture(filter);
				  else
					  msg.errorMessage("Unknown image format type, bad texture class initialization! Blame developers for this!");

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
				  free(texture.imageData);
				  msg.infoMessage("Texture released from memory.");
			  } 

			  bool PTexture::loadTGA()
			  {
				  GLubyte	TGAheader[12] = {0,0,2,0,0,0,0,0,0,0,0,0};		// uncompressed TGA Header
				  GLubyte	TGAcompare[12];						// for compare...
				  GLubyte	header[6];						// first 6 bits
				  unsigned	bytesPerPixel;						// number of bytes per pixel in tga image
				  unsigned	imageSize;						// store image size
				  unsigned	temp;							
			//	  unsigned	type  = GL_RGBA; 	

				  FILE *file = fopen(altFilename, "rb");					// open file

				  if(file==NULL ||							
					fread(TGAcompare, 1, sizeof(TGAcompare), file) != sizeof(TGAcompare) ||	// are 12 bytes readable?
					memcmp(TGAheader,TGAcompare,sizeof(TGAheader)) != 0 ||				// header match?
					fread(header, 1,sizeof(header), file) != sizeof(header))				// :)
				  {
					  if (file == NULL)
					  {
						  msg.errorMessage("Texture file is empty!");
						  return false;						// :(
					  }
					  else 
					  {
						  msg.errorUnknown();
						  fclose(file);						
						  return false;						
					  }
				  }

				  texture.width  = header[1] * 256 + header[0];				// get width (highbyte*256+lowbyte)
				  texture.height = header[3] * 256 + header[2];				// get height	(highbyte*256+lowbyte)
    
 				  if(texture.width	<=0 ||						// width and height must be > 0
					 texture.height	<=0 ||						
					 (header[4]!=24 && header[4]!=32))				// 24 or 32 bit
				  {

					  msg.errorMessage("Texture isn't 32 or 24 bit OR texture width or height isn't greater than zero :D");
					  fclose(file);						
					  return false;
				  } 

				  texture.bpp	= header[4];						// grab The TGA's Bits Per Pixel (24 or 32)
				  bytesPerPixel	= texture.bpp/8;					// divide By 8 To Get The Bytes Per Pixel
				  imageSize		= texture.width*texture.height*bytesPerPixel;	// Calculate The Memory Required 

				  texture.imageData=(GLubyte *)malloc(imageSize);			// reserve memory to store TGA data

				  if(texture.imageData==NULL ||					// storage memory exist... ?
					 fread(texture.imageData, 1, imageSize, file)!=imageSize)	// Does The Image Size Match The Memory Reserved?
				  {
					  if(texture.imageData!=NULL)					// release
					  {
						  msg.errorMessage("TGA image data is empty. Releasing memory...");
						  free(texture.imageData);	
					  }

					  msg.errorUnknown();
					  fclose(file);							
					  return false;							
				  }

				  for(GLuint i=0; i<int(imageSize); i+=bytesPerPixel)	// Swaps The 1st And 3rd Bytes, R and B
				  {
					  temp=texture.imageData[i];					
					  texture.imageData[i] = texture.imageData[i + 2];		
					  texture.imageData[i + 2] = temp;				
				  }

				  fclose (file);								
				  msg.infoTexture(altFilename);
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
					  msg.initMessage("TGA texture/Alpha channel", false);
					  type=GL_RGB;							// type je GL_RGB
				  }
				  else
					  msg.initMessage("TGA texture/Alpha channel", true);

				  gluBuild2DMipmaps(GL_TEXTURE_2D, type, texPtr[0].width, texPtr[0].height, type, GL_UNSIGNED_BYTE, texPtr[0].imageData);
				  msg.infoMessage("Texture was successfully generated, mipmap filtering.");

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
					  msg.initMessage("TGA texture/Alpha channel", false);
					  type=GL_RGB;							// type je GL_RGB
				  }
				  else
					  msg.initMessage("TGA texture/Alpha channel", true);

				  glTexImage2D(GL_TEXTURE_2D, 0, type, texPtr[0].width, texPtr[0].height, 0, type, GL_UNSIGNED_BYTE, texPtr[0].imageData);
				  msg.infoMessage("Texture was successfully generated, linear filtering.");

			  }

			  bool PTexture::makeTgaTexture(bool mipmap)
			  {
				  if(!loadTGA())
				  {
					  msg.infoMessage("Texture creation failed.");
					  return false;
				  }

				  if(mipmap)
					  generateTextureMipmap();
				  else
					  generateTextureLinear();

				  msg.infoMessage("Texture created, ready for use.");
				  return true;

			  }

			  // getters
			  unsigned PTexture::getTexID()
			  {
				  return texture.texID;
			  }
          }
}