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
CC=
CCC=
CXX=
FC=
AS=

# Macros
CND_PLATFORM=Cygwin-Linux-x86
CND_CONF=Windows_Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/zip/ioapi.o \
	${OBJECTDIR}/src/camera.o \
	${OBJECTDIR}/src/gui/gui.o \
	${OBJECTDIR}/src/game.o \
	${OBJECTDIR}/src/gui/radiobuttongroup.o \
	${OBJECTDIR}/src/md2loader/md2model.o \
	${OBJECTDIR}/src/zip/unzip.o \
	${OBJECTDIR}/src/gui/msgbox.o \
	${OBJECTDIR}/src/resource.o \
	${OBJECTDIR}/src/input.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/gui/checkbox.o \
	${OBJECTDIR}/src/gui/component.o \
	${OBJECTDIR}/src/zip/zipfile.o \
	${OBJECTDIR}/src/gui/fonts.o \
	${OBJECTDIR}/src/level.o \
	${OBJECTDIR}/src/vector.o \
	${OBJECTDIR}/src/gui/editbox.o \
	${OBJECTDIR}/src/player.o \
	${OBJECTDIR}/src/object.o \
	${OBJECTDIR}/src/gui/guirender.o \
	${OBJECTDIR}/src/gui/text.o \
	${OBJECTDIR}/src/gui/forms.o \
	${OBJECTDIR}/src/messages.o \
	${OBJECTDIR}/src/gui/window.o \
	${OBJECTDIR}/src/core.o \
	${OBJECTDIR}/src/gui/scrollbar.o \
	${OBJECTDIR}/src/renderer/renderer-texture.o \
	${OBJECTDIR}/src/gui/container.o \
	${OBJECTDIR}/src/gui/button.o \
	${OBJECTDIR}/src/gui/listbox.o \
	${OBJECTDIR}/src/CommonStructures.o \
	${OBJECTDIR}/src/renderer/particle.o \
	${OBJECTDIR}/src/config.o \
	${OBJECTDIR}/src/levelbox.o \
	${OBJECTDIR}/src/gui/radiobutton.o \
	${OBJECTDIR}/src/renderer/renderer-core.o \
	${OBJECTDIR}/src/gui/panel.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/usr/local/lib -lglfw -lz -lboost_filesystem-gcc-mt -lopengl32 -lglu32 -lALut -lopenal32

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Windows_Debug.mk dist/Windows_Debug/Cygwin-Linux-x86/xsoko

dist/Windows_Debug/Cygwin-Linux-x86/xsoko: ${OBJECTFILES}
	${MKDIR} -p dist/Windows_Debug/Cygwin-Linux-x86
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/xsoko ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/md2loader/Anorms.h.gch: nbproject/Makefile-${CND_CONF}.mk src/md2loader/Anorms.h 
	${MKDIR} -p ${OBJECTDIR}/src/md2loader
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o $@ src/md2loader/Anorms.h

${OBJECTDIR}/src/gui/forms.h.gch: nbproject/Makefile-${CND_CONF}.mk src/gui/forms.h 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o $@ src/gui/forms.h

${OBJECTDIR}/src/zip/ioapi.o: nbproject/Makefile-${CND_CONF}.mk src/zip/ioapi.c 
	${MKDIR} -p ${OBJECTDIR}/src/zip
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/zip/ioapi.o src/zip/ioapi.c

${OBJECTDIR}/src/camera.o: nbproject/Makefile-${CND_CONF}.mk src/camera.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/camera.o src/camera.cpp

${OBJECTDIR}/src/gui/text.h.gch: nbproject/Makefile-${CND_CONF}.mk src/gui/text.h 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o $@ src/gui/text.h

${OBJECTDIR}/src/gui/gui.o: nbproject/Makefile-${CND_CONF}.mk src/gui/gui.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gui/gui.o src/gui/gui.cpp

${OBJECTDIR}/src/game.o: nbproject/Makefile-${CND_CONF}.mk src/game.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/game.o src/game.cpp

${OBJECTDIR}/src/gui/radiobuttongroup.o: nbproject/Makefile-${CND_CONF}.mk src/gui/radiobuttongroup.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gui/radiobuttongroup.o src/gui/radiobuttongroup.cpp

${OBJECTDIR}/src/md2loader/md2model.o: nbproject/Makefile-${CND_CONF}.mk src/md2loader/md2model.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/md2loader
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/md2loader/md2model.o src/md2loader/md2model.cpp

${OBJECTDIR}/src/gui/editbox.h.gch: nbproject/Makefile-${CND_CONF}.mk src/gui/editbox.h 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o $@ src/gui/editbox.h

${OBJECTDIR}/src/zip/unzip.o: nbproject/Makefile-${CND_CONF}.mk src/zip/unzip.c 
	${MKDIR} -p ${OBJECTDIR}/src/zip
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/zip/unzip.o src/zip/unzip.c

${OBJECTDIR}/src/gui/msgbox.o: nbproject/Makefile-${CND_CONF}.mk src/gui/msgbox.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gui/msgbox.o src/gui/msgbox.cpp

${OBJECTDIR}/src/gui/guirender.h.gch: nbproject/Makefile-${CND_CONF}.mk src/gui/guirender.h 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o $@ src/gui/guirender.h

${OBJECTDIR}/src/gui/commongui.h.gch: nbproject/Makefile-${CND_CONF}.mk src/gui/commongui.h 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o $@ src/gui/commongui.h

${OBJECTDIR}/src/resource.o: nbproject/Makefile-${CND_CONF}.mk src/resource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/resource.o src/resource.cpp

${OBJECTDIR}/src/input.o: nbproject/Makefile-${CND_CONF}.mk src/input.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/input.o src/input.cpp

${OBJECTDIR}/src/main.o: nbproject/Makefile-${CND_CONF}.mk src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/gui/checkbox.o: nbproject/Makefile-${CND_CONF}.mk src/gui/checkbox.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gui/checkbox.o src/gui/checkbox.cpp

${OBJECTDIR}/src/gui/component.o: nbproject/Makefile-${CND_CONF}.mk src/gui/component.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gui/component.o src/gui/component.cpp

${OBJECTDIR}/src/gui/msgbox.h.gch: nbproject/Makefile-${CND_CONF}.mk src/gui/msgbox.h 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o $@ src/gui/msgbox.h

${OBJECTDIR}/src/zip/zipfile.o: nbproject/Makefile-${CND_CONF}.mk src/zip/zipfile.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/zip
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/zip/zipfile.o src/zip/zipfile.cpp

${OBJECTDIR}/src/gui/radiobutton.h.gch: nbproject/Makefile-${CND_CONF}.mk src/gui/radiobutton.h 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o $@ src/gui/radiobutton.h

${OBJECTDIR}/src/gui/fonts.o: nbproject/Makefile-${CND_CONF}.mk src/gui/fonts.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gui/fonts.o src/gui/fonts.cpp

${OBJECTDIR}/src/level.o: nbproject/Makefile-${CND_CONF}.mk src/level.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/level.o src/level.cpp

${OBJECTDIR}/src/gui/button.h.gch: nbproject/Makefile-${CND_CONF}.mk src/gui/button.h 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o $@ src/gui/button.h

${OBJECTDIR}/src/gui/panel.h.gch: nbproject/Makefile-${CND_CONF}.mk src/gui/panel.h 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o $@ src/gui/panel.h

${OBJECTDIR}/src/vector.o: nbproject/Makefile-${CND_CONF}.mk src/vector.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/vector.o src/vector.cpp

${OBJECTDIR}/src/gui/editbox.o: nbproject/Makefile-${CND_CONF}.mk src/gui/editbox.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gui/editbox.o src/gui/editbox.cpp

${OBJECTDIR}/src/player.o: nbproject/Makefile-${CND_CONF}.mk src/player.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/player.o src/player.cpp

${OBJECTDIR}/src/object.o: nbproject/Makefile-${CND_CONF}.mk src/object.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/object.o src/object.cpp

${OBJECTDIR}/src/md2loader/md2model.h.gch: nbproject/Makefile-${CND_CONF}.mk src/md2loader/md2model.h 
	${MKDIR} -p ${OBJECTDIR}/src/md2loader
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o $@ src/md2loader/md2model.h

${OBJECTDIR}/src/gui/guirender.o: nbproject/Makefile-${CND_CONF}.mk src/gui/guirender.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gui/guirender.o src/gui/guirender.cpp

${OBJECTDIR}/src/gui/text.o: nbproject/Makefile-${CND_CONF}.mk src/gui/text.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gui/text.o src/gui/text.cpp

${OBJECTDIR}/src/gui/radiobuttongroup.h.gch: nbproject/Makefile-${CND_CONF}.mk src/gui/radiobuttongroup.h 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o $@ src/gui/radiobuttongroup.h

${OBJECTDIR}/src/gui/forms.o: nbproject/Makefile-${CND_CONF}.mk src/gui/forms.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gui/forms.o src/gui/forms.cpp

${OBJECTDIR}/src/gui/window.h.gch: nbproject/Makefile-${CND_CONF}.mk src/gui/window.h 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o $@ src/gui/window.h

${OBJECTDIR}/src/messages.o: nbproject/Makefile-${CND_CONF}.mk src/messages.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/messages.o src/messages.cpp

${OBJECTDIR}/src/config.h.gch: nbproject/Makefile-${CND_CONF}.mk src/config.h 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o $@ src/config.h

${OBJECTDIR}/src/gui/window.o: nbproject/Makefile-${CND_CONF}.mk src/gui/window.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gui/window.o src/gui/window.cpp

${OBJECTDIR}/src/core.o: nbproject/Makefile-${CND_CONF}.mk src/core.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/core.o src/core.cpp

${OBJECTDIR}/src/gui/scrollbar.o: nbproject/Makefile-${CND_CONF}.mk src/gui/scrollbar.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gui/scrollbar.o src/gui/scrollbar.cpp

${OBJECTDIR}/src/renderer/renderer-texture.o: nbproject/Makefile-${CND_CONF}.mk src/renderer/renderer-texture.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/renderer
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/renderer/renderer-texture.o src/renderer/renderer-texture.cpp

${OBJECTDIR}/src/gui/scrollbar.h.gch: nbproject/Makefile-${CND_CONF}.mk src/gui/scrollbar.h 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o $@ src/gui/scrollbar.h

${OBJECTDIR}/src/gui/container.o: nbproject/Makefile-${CND_CONF}.mk src/gui/container.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gui/container.o src/gui/container.cpp

${OBJECTDIR}/src/gui/container.h.gch: nbproject/Makefile-${CND_CONF}.mk src/gui/container.h 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o $@ src/gui/container.h

${OBJECTDIR}/src/gui/button.o: nbproject/Makefile-${CND_CONF}.mk src/gui/button.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gui/button.o src/gui/button.cpp

${OBJECTDIR}/src/gui/listbox.o: nbproject/Makefile-${CND_CONF}.mk src/gui/listbox.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gui/listbox.o src/gui/listbox.cpp

${OBJECTDIR}/src/gui/checkbox.h.gch: nbproject/Makefile-${CND_CONF}.mk src/gui/checkbox.h 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o $@ src/gui/checkbox.h

${OBJECTDIR}/src/gui/component.h.gch: nbproject/Makefile-${CND_CONF}.mk src/gui/component.h 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o $@ src/gui/component.h

${OBJECTDIR}/src/gui/listbox.h.gch: nbproject/Makefile-${CND_CONF}.mk src/gui/listbox.h 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o $@ src/gui/listbox.h

${OBJECTDIR}/src/CommonStructures.o: nbproject/Makefile-${CND_CONF}.mk src/CommonStructures.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/CommonStructures.o src/CommonStructures.cpp

${OBJECTDIR}/src/renderer/particle.o: nbproject/Makefile-${CND_CONF}.mk src/renderer/particle.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/renderer
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/renderer/particle.o src/renderer/particle.cpp

${OBJECTDIR}/src/config.o: nbproject/Makefile-${CND_CONF}.mk src/config.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/config.o src/config.cpp

${OBJECTDIR}/src/levelbox.o: nbproject/Makefile-${CND_CONF}.mk src/levelbox.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/levelbox.o src/levelbox.cpp

${OBJECTDIR}/src/gui/radiobutton.o: nbproject/Makefile-${CND_CONF}.mk src/gui/radiobutton.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gui/radiobutton.o src/gui/radiobutton.cpp

${OBJECTDIR}/src/renderer/renderer-core.o: nbproject/Makefile-${CND_CONF}.mk src/renderer/renderer-core.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/renderer
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/renderer/renderer-core.o src/renderer/renderer-core.cpp

${OBJECTDIR}/src/gui/panel.o: nbproject/Makefile-${CND_CONF}.mk src/gui/panel.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DWindows_Debug -I/E/cygwin/usr/include/boost-1_33_1 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/gui/panel.o src/gui/panel.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Windows_Debug
	${RM} dist/Windows_Debug/Cygwin-Linux-x86/xsoko

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
