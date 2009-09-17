# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Windows_Release.mk dist/Windows_Release/${PLATFORM}/xsoko_sdl.exe

dist/Windows_Release/${PLATFORM}/xsoko_sdl.exe: ${OBJECTFILES}
	${MKDIR} -p dist/Windows_Release/${PLATFORM}
	${LINK.cc} -o dist/Windows_Release/${PLATFORM}/xsoko_sdl ${OBJECTFILES} ${LDLIBSOPTIONS} 

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Windows_Release
	${RM} dist/Windows_Release/${PLATFORM}/xsoko_sdl.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
