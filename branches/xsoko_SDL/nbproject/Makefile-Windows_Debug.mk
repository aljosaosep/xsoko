# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Windows_Debug.mk dist/Windows_Debug/${PLATFORM}/xsoko_sdl.exe

dist/Windows_Debug/${PLATFORM}/xsoko_sdl.exe: ${OBJECTFILES}
	${MKDIR} -p dist/Windows_Debug/${PLATFORM}
	${LINK.cc} -o dist/Windows_Debug/${PLATFORM}/xsoko_sdl ${OBJECTFILES} ${LDLIBSOPTIONS} 

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Windows_Debug
	${RM} dist/Windows_Debug/${PLATFORM}/xsoko_sdl.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
