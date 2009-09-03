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
 * Codename: xSoko
 * File: zipfile.cpp
 *
 * Summary:
 * Includes zip file methods implementation
 *
 * Author: Jernej Skrabec June 19 2008
 */

#include "zipfile.h"

ZipFile::ZipFile(){
    zipf = 0;
    opened = false;
}

ZipFile::ZipFile(const char* path){
    zipf = 0;
    opened = false;
    openZip(path);
}

ZipFile::~ZipFile(){
    closeZip();
}

int ZipFile::openZip(const char* path){
    if(!path && zipf){
            return UNZ_ERRNO;
    }
    if((zipf = unzOpen(path)) != 0)
        return UNZ_OK;
    else
        return UNZ_ERRNO;
}

void ZipFile::closeZip(){
    if(zipf){
        closeFile();
        unzClose(zipf);
        zipf = 0;
    }
}

int ZipFile::openFile(const char* filename){
    if(zipf && (!opened)){
        if(unzLocateFile(zipf,filename,0)==UNZ_END_OF_LIST_OF_FILE){
            return UNZ_END_OF_LIST_OF_FILE;
        }
        int ret = unzOpenCurrentFile(zipf);
        if(ret!=UNZ_OK)
            opened = false;
        else
            opened = true;
        return ret;
    } else
        return UNZ_ERRNO;
}

void ZipFile::closeFile(){
    if(opened){
        opened = false;
        unzCloseCurrentFile(zipf);
    }
}

int ZipFile::readFile(void* buffer, unsigned length){
    if(opened)
        return unzReadCurrentFile(zipf,buffer,length); 
    else
        return UNZ_ERRNO;
}

bool ZipFile::isFileOpened(){
    return opened;
}

int ZipFile::getFileSize(){
    if(opened){
        unz_file_info file_info;
        if(unzGetCurrentFileInfo(zipf,&file_info,0,0,0,0,0,0)==UNZ_OK)
            return file_info.uncompressed_size;
        else
            return UNZ_ERRNO;
    } else
        return UNZ_ERRNO;
}
