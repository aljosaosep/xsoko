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
OBJECTDIR=build/Windows_Release/GNU-Windows

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/player.o \
	${OBJECTDIR}/src/object.o \
	${OBJECTDIR}/src/game-funcrender.o \
	${OBJECTDIR}/src/game.o \
	${OBJECTDIR}/src/io.o \
	${OBJECTDIR}/src/renderer/renderer-texture.o \
	${OBJECTDIR}/src/game-funcinit.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/filemanagment.o \
	${OBJECTDIR}/src/CommonStructures.o \
	${OBJECTDIR}/src/openglfunc.o \
	${OBJECTDIR}/src/level.o \
	${OBJECTDIR}/src/vector.o \
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
LDLIBSOPTIONS=-lglfw -lopengl32 -lglu32

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS} dist/Windows_Release/GNU-Windows/xsoko.exe

dist/Windows_Release/GNU-Windows/xsoko.exe: ${OBJECTFILES}
	${MKDIR} -p dist/Windows_Release/GNU-Windows
	${LINK.cc} -o dist/Windows_Release/GNU-Windows/xsoko ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/player.o: src/player.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/player.o src/player.cpp

${OBJECTDIR}/src/object.o: src/object.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/object.o src/object.cpp

${OBJECTDIR}/src/game-funcrender.o: src/game-funcrender.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/game-funcrender.o src/game-funcrender.cpp

${OBJECTDIR}/src/game.o: src/game.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/game.o src/game.cpp

${OBJECTDIR}/src/io.o: src/io.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/io.o src/io.cpp

${OBJECTDIR}/src/renderer/renderer-texture.o: src/renderer/renderer-texture.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/renderer
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/renderer/renderer-texture.o src/renderer/renderer-texture.cpp

${OBJECTDIR}/src/game-funcinit.o: src/game-funcinit.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/game-funcinit.o src/game-funcinit.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/filemanagment.o: src/filemanagment.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/filemanagment.o src/filemanagment.cpp

${OBJECTDIR}/src/CommonStructures.o: src/CommonStructures.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/CommonStructures.o src/CommonStructures.cpp

${OBJECTDIR}/src/openglfunc.o: src/openglfunc.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/openglfunc.o src/openglfunc.cpp

${OBJECTDIR}/src/level.o: src/level.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/level.o src/level.cpp

${OBJECTDIR}/src/vector.o: src/vector.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/vector.o src/vector.cpp

${OBJECTDIR}/src/levelbox.o: src/levelbox.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/levelbox.o src/levelbox.cpp

${OBJECTDIR}/src/renderer/renderer-core.o: src/renderer/renderer-core.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/renderer
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/renderer/renderer-core.o src/renderer/renderer-core.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Windows_Release
	${RM} dist/Windows_Release/GNU-Windows/xsoko.exe

# Subprojects
.clean-subprojects:
