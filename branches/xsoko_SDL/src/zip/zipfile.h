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
 * File: zipfile.h
 *
 * Summary:
 * Includes zip file class definition
 *
 * Author: Jernej Skrabec June 19 2008
 */

#ifndef _zipfile_H
#define _zipfile_H

#include "unzip.h"
#include <string>
#include <streambuf>
#include <iostream>

using namespace std;

#define UNZ_OK                          (0)
#define UNZ_END_OF_LIST_OF_FILE         (-100)
#define UNZ_ERRNO                       (Z_ERRNO)
#define UNZ_EOF                         (0)
#define UNZ_PARAMERROR                  (-102)
#define UNZ_BADZIPFILE                  (-103)
#define UNZ_INTERNALERROR               (-104)
#define UNZ_CRCERROR                    (-105)

 /**********************************************************
* ZipFile
*
* Wrapper class for zip manipulation functions
* --------------------------------------------------------
* Jernej Skrabec 2008
* ********************************************************/
class ZipFile{
private:
	unzFile zipf;
        bool opened;
public:
        //contructors
	ZipFile();
	ZipFile(const char*);
        
        //destructor
	~ZipFile();
        
        //methods
	int openZip(const char*);
        void closeZip();
        int openFile(const char*);
        void closeFile();
        int readFile(void*,unsigned);
        bool isFileOpened();
        int getFileSize();
};

class zipstreambuf : public streambuf {
private:
    unzFile zipf;
    char* base;
    streamsize length;
protected:
    virtual int underflow();
    virtual streambuf* setbuf(char* b, streamsize len);
public:
    zipstreambuf(unzFile file);
    virtual ~zipstreambuf() {}
};

class zifstream : public istream {
private:
    zipstreambuf* zsb;
    unzFile zipf;
    bool opened_ok;
public:
    zifstream();
    zifstream(string zipfile, string file);
    void open(string zipfile, string file);
    void close();
    bool is_open();
    virtual ~zifstream();
};

#endif
