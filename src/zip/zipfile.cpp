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
        if(unzGetCurrentFileInfo(zipf,&file_info,NULL,0,NULL,0,NULL,0)==UNZ_OK)
            return file_info.uncompressed_size;
        else
            return UNZ_ERRNO;
    } else
        return UNZ_ERRNO;
}
