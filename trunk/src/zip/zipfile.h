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

#endif
