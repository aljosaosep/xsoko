#
# Gererated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/Linux_Debug/GNU-Linux-x86

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/zip/zlib/infback.o \
	${OBJECTDIR}/src/zip/ioapi.o \
	${OBJECTDIR}/src/zip/zlib/compress.o \
	${OBJECTDIR}/src/game.o \
	${OBJECTDIR}/src/zip/zlib/deflate.o \
	${OBJECTDIR}/src/zip/unzip.o \
	${OBJECTDIR}/src/zip/zlib/crc32.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/zip/zlib/gzio.o \
	${OBJECTDIR}/src/zip/zlib/zutil.o \
	${OBJECTDIR}/src/zip/zlib/inflate.o \
	${OBJECTDIR}/src/zip/zlib/inffast.o \
	${OBJECTDIR}/src/zip/zipfile.o \
	${OBJECTDIR}/src/level.o \
	${OBJECTDIR}/src/zip/zlib/uncompr.o \
	${OBJECTDIR}/src/vector.o \
	${OBJECTDIR}/src/zip/zlib/inftrees.o \
	${OBJECTDIR}/src/player.o \
	${OBJECTDIR}/src/object.o \
	${OBJECTDIR}/src/zip/zlib/adler32.o \
	${OBJECTDIR}/src/zip/zlib/trees.o \
	${OBJECTDIR}/src/game-render.o \
	${OBJECTDIR}/src/io.o \
	${OBJECTDIR}/src/renderer/renderer-texture.o \
	${OBJECTDIR}/src/game-init.o \
	${OBJECTDIR}/src/CommonStructures.o \
	${OBJECTDIR}/src/levelbox.o \
	${OBJECTDIR}/src/renderer/renderer-core.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lglfw -lGL -lGLU -lXxf86vm -lm -lXrandr -lglfw

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS} dist/Linux_Debug/GNU-Linux-x86/xsoko

dist/Linux_Debug/GNU-Linux-x86/xsoko: ${OBJECTFILES}
	${MKDIR} -p dist/Linux_Debug/GNU-Linux-x86
	${LINK.cc} -o dist/Linux_Debug/GNU-Linux-x86/xsoko ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/zip/zlib/infback.o: src/zip/zlib/infback.c 
	${MKDIR} -p ${OBJECTDIR}/src/zip/zlib
	$(COMPILE.c) -g -o ${OBJECTDIR}/src/zip/zlib/infback.o src/zip/zlib/infback.c

${OBJECTDIR}/src/zip/ioapi.o: src/zip/ioapi.c 
	${MKDIR} -p ${OBJECTDIR}/src/zip
	$(COMPILE.c) -g -o ${OBJECTDIR}/src/zip/ioapi.o src/zip/ioapi.c

${OBJECTDIR}/src/zip/zlib/compress.o: src/zip/zlib/compress.c 
	${MKDIR} -p ${OBJECTDIR}/src/zip/zlib
	$(COMPILE.c) -g -o ${OBJECTDIR}/src/zip/zlib/compress.o src/zip/zlib/compress.c

${OBJECTDIR}/src/game.o: src/game.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -Wall -o ${OBJECTDIR}/src/game.o src/game.cpp

${OBJECTDIR}/src/zip/zlib/deflate.o: src/zip/zlib/deflate.c 
	${MKDIR} -p ${OBJECTDIR}/src/zip/zlib
	$(COMPILE.c) -g -o ${OBJECTDIR}/src/zip/zlib/deflate.o src/zip/zlib/deflate.c

${OBJECTDIR}/src/zip/unzip.o: src/zip/unzip.c 
	${MKDIR} -p ${OBJECTDIR}/src/zip
	$(COMPILE.c) -g -o ${OBJECTDIR}/src/zip/unzip.o src/zip/unzip.c

${OBJECTDIR}/src/zip/zlib/crc32.o: src/zip/zlib/crc32.c 
	${MKDIR} -p ${OBJECTDIR}/src/zip/zlib
	$(COMPILE.c) -g -o ${OBJECTDIR}/src/zip/zlib/crc32.o src/zip/zlib/crc32.c

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -Wall -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/zip/zlib/gzio.o: src/zip/zlib/gzio.c 
	${MKDIR} -p ${OBJECTDIR}/src/zip/zlib
	$(COMPILE.c) -g -o ${OBJECTDIR}/src/zip/zlib/gzio.o src/zip/zlib/gzio.c

${OBJECTDIR}/src/zip/zlib/zutil.o: src/zip/zlib/zutil.c 
	${MKDIR} -p ${OBJECTDIR}/src/zip/zlib
	$(COMPILE.c) -g -o ${OBJECTDIR}/src/zip/zlib/zutil.o src/zip/zlib/zutil.c

${OBJECTDIR}/src/zip/zlib/inflate.o: src/zip/zlib/inflate.c 
	${MKDIR} -p ${OBJECTDIR}/src/zip/zlib
	$(COMPILE.c) -g -o ${OBJECTDIR}/src/zip/zlib/inflate.o src/zip/zlib/inflate.c

${OBJECTDIR}/src/zip/zlib/inffast.o: src/zip/zlib/inffast.c 
	${MKDIR} -p ${OBJECTDIR}/src/zip/zlib
	$(COMPILE.c) -g -o ${OBJECTDIR}/src/zip/zlib/inffast.o src/zip/zlib/inffast.c

${OBJECTDIR}/src/zip/zipfile.o: src/zip/zipfile.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/zip
	$(COMPILE.cc) -g -Wall -o ${OBJECTDIR}/src/zip/zipfile.o src/zip/zipfile.cpp

${OBJECTDIR}/src/level.o: src/level.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -Wall -o ${OBJECTDIR}/src/level.o src/level.cpp

${OBJECTDIR}/src/zip/zlib/uncompr.o: src/zip/zlib/uncompr.c 
	${MKDIR} -p ${OBJECTDIR}/src/zip/zlib
	$(COMPILE.c) -g -o ${OBJECTDIR}/src/zip/zlib/uncompr.o src/zip/zlib/uncompr.c

${OBJECTDIR}/src/vector.o: src/vector.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -Wall -o ${OBJECTDIR}/src/vector.o src/vector.cpp

${OBJECTDIR}/src/zip/zlib/inftrees.o: src/zip/zlib/inftrees.c 
	${MKDIR} -p ${OBJECTDIR}/src/zip/zlib
	$(COMPILE.c) -g -o ${OBJECTDIR}/src/zip/zlib/inftrees.o src/zip/zlib/inftrees.c

${OBJECTDIR}/src/player.o: src/player.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -Wall -o ${OBJECTDIR}/src/player.o src/player.cpp

${OBJECTDIR}/src/object.o: src/object.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -Wall -o ${OBJECTDIR}/src/object.o src/object.cpp

${OBJECTDIR}/src/zip/zlib/adler32.o: src/zip/zlib/adler32.c 
	${MKDIR} -p ${OBJECTDIR}/src/zip/zlib
	$(COMPILE.c) -g -o ${OBJECTDIR}/src/zip/zlib/adler32.o src/zip/zlib/adler32.c

${OBJECTDIR}/src/zip/zlib/trees.o: src/zip/zlib/trees.c 
	${MKDIR} -p ${OBJECTDIR}/src/zip/zlib
	$(COMPILE.c) -g -o ${OBJECTDIR}/src/zip/zlib/trees.o src/zip/zlib/trees.c

${OBJECTDIR}/src/game-render.o: src/game-render.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -Wall -o ${OBJECTDIR}/src/game-render.o src/game-render.cpp

${OBJECTDIR}/src/io.o: src/io.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -Wall -o ${OBJECTDIR}/src/io.o src/io.cpp

${OBJECTDIR}/src/renderer/renderer-texture.o: src/renderer/renderer-texture.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/renderer
	$(COMPILE.cc) -g -Wall -o ${OBJECTDIR}/src/renderer/renderer-texture.o src/renderer/renderer-texture.cpp

${OBJECTDIR}/src/game-init.o: src/game-init.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -Wall -o ${OBJECTDIR}/src/game-init.o src/game-init.cpp

${OBJECTDIR}/src/CommonStructures.o: src/CommonStructures.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -Wall -o ${OBJECTDIR}/src/CommonStructures.o src/CommonStructures.cpp

${OBJECTDIR}/src/levelbox.o: src/levelbox.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -Wall -o ${OBJECTDIR}/src/levelbox.o src/levelbox.cpp

${OBJECTDIR}/src/renderer/renderer-core.o: src/renderer/renderer-core.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/renderer
	$(COMPILE.cc) -g -Wall -o ${OBJECTDIR}/src/renderer/renderer-core.o src/renderer/renderer-core.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Linux_Debug
	${RM} dist/Linux_Debug/GNU-Linux-x86/xsoko

# Subprojects
.clean-subprojects:
