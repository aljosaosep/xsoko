#
# Generated Makefile - do not edit!
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
CC=gcc-3.exe
CCC=g++-3.exe
CXX=g++-3.exe
FC=

# Macros
PLATFORM=Cygwin-Windows

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/Windows_Release/${PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/zip/ioapi.o \
	${OBJECTDIR}/src/camera.o \
	${OBJECTDIR}/src/game.o \
	${OBJECTDIR}/src/session.o \
	${OBJECTDIR}/src/zip/unzip.o \
	${OBJECTDIR}/src/input.o \
	${OBJECTDIR}/src/resource.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/zip/zipfile.o \
	${OBJECTDIR}/src/gui/fonts.o \
	${OBJECTDIR}/src/level.o \
	${OBJECTDIR}/src/vector.o \
	${OBJECTDIR}/src/player.o \
	${OBJECTDIR}/src/object.o \
	${OBJECTDIR}/src/messages.o \
	${OBJECTDIR}/src/game-render.o \
	${OBJECTDIR}/src/core.o \
	${OBJECTDIR}/src/gui/win.o \
	${OBJECTDIR}/src/io.o \
	${OBJECTDIR}/src/renderer/renderer-texture.o \
	${OBJECTDIR}/src/game-init.o \
	${OBJECTDIR}/src/CommonStructures.o \
	${OBJECTDIR}/src/renderer/particle.o \
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
LDLIBSOPTIONS=-lglfw -lOpenAL32 -lALut -lboost_filesystem-gcc-mt -lz -lopengl32 -lglu32

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Windows_Release.mk dist/Windows_Release/${PLATFORM}/xsoko.exe

dist/Windows_Release/${PLATFORM}/xsoko.exe: ${OBJECTFILES}
	${MKDIR} -p dist/Windows_Release/${PLATFORM}
	${LINK.cc} -o dist/Windows_Release/${PLATFORM}/xsoko ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/zip/ioapi.o: src/zip/ioapi.c 
	${MKDIR} -p ${OBJECTDIR}/src/zip
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/zip/ioapi.o src/zip/ioapi.c

${OBJECTDIR}/src/camera.o: src/camera.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -DWindows_Release -I/cygdrive/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/camera.o src/camera.cpp

${OBJECTDIR}/src/game.o: src/game.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -DWindows_Release -I/cygdrive/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/game.o src/game.cpp

${OBJECTDIR}/src/session.o: src/session.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -DWindows_Release -I/cygdrive/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/session.o src/session.cpp

${OBJECTDIR}/src/zip/unzip.o: src/zip/unzip.c 
	${MKDIR} -p ${OBJECTDIR}/src/zip
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/zip/unzip.o src/zip/unzip.c

${OBJECTDIR}/src/input.o: src/input.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -DWindows_Release -I/cygdrive/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/input.o src/input.cpp

${OBJECTDIR}/src/resource.o: src/resource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -DWindows_Release -I/cygdrive/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/resource.o src/resource.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -DWindows_Release -I/cygdrive/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/zip/zipfile.o: src/zip/zipfile.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/zip
	${RM} $@.d
	$(COMPILE.cc) -O2 -DWindows_Release -I/cygdrive/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/zip/zipfile.o src/zip/zipfile.cpp

${OBJECTDIR}/src/gui/fonts.o: src/gui/fonts.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -O2 -DWindows_Release -I/cygdrive/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gui/fonts.o src/gui/fonts.cpp

${OBJECTDIR}/src/level.o: src/level.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -DWindows_Release -I/cygdrive/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/level.o src/level.cpp

${OBJECTDIR}/src/vector.o: src/vector.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -DWindows_Release -I/cygdrive/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/vector.o src/vector.cpp

${OBJECTDIR}/src/player.o: src/player.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -DWindows_Release -I/cygdrive/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/player.o src/player.cpp

${OBJECTDIR}/src/object.o: src/object.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -DWindows_Release -I/cygdrive/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/object.o src/object.cpp

${OBJECTDIR}/src/messages.o: src/messages.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -DWindows_Release -I/cygdrive/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/messages.o src/messages.cpp

${OBJECTDIR}/src/game-render.o: src/game-render.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -DWindows_Release -I/cygdrive/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/game-render.o src/game-render.cpp

${OBJECTDIR}/src/core.o: src/core.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -DWindows_Release -I/cygdrive/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/core.o src/core.cpp

${OBJECTDIR}/src/gui/win.o: src/gui/win.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -O2 -DWindows_Release -I/cygdrive/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gui/win.o src/gui/win.cpp

${OBJECTDIR}/src/io.o: src/io.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -DWindows_Release -I/cygdrive/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/io.o src/io.cpp

${OBJECTDIR}/src/renderer/renderer-texture.o: src/renderer/renderer-texture.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/renderer
	${RM} $@.d
	$(COMPILE.cc) -O2 -DWindows_Release -I/cygdrive/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/renderer/renderer-texture.o src/renderer/renderer-texture.cpp

${OBJECTDIR}/src/game-init.o: src/game-init.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -DWindows_Release -I/cygdrive/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/game-init.o src/game-init.cpp

${OBJECTDIR}/src/CommonStructures.o: src/CommonStructures.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -DWindows_Release -I/cygdrive/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/CommonStructures.o src/CommonStructures.cpp

${OBJECTDIR}/src/renderer/particle.o: src/renderer/particle.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/renderer
	${RM} $@.d
	$(COMPILE.cc) -O2 -DWindows_Release -I/cygdrive/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/renderer/particle.o src/renderer/particle.cpp

${OBJECTDIR}/src/levelbox.o: src/levelbox.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -DWindows_Release -I/cygdrive/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/levelbox.o src/levelbox.cpp

${OBJECTDIR}/src/renderer/renderer-core.o: src/renderer/renderer-core.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/renderer
	${RM} $@.d
	$(COMPILE.cc) -O2 -DWindows_Release -I/cygdrive/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/renderer/renderer-core.o src/renderer/renderer-core.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Windows_Release
	${RM} dist/Windows_Release/${PLATFORM}/xsoko.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
