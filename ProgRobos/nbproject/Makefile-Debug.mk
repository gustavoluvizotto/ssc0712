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
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/PerdeuRastro.o \
	${OBJECTDIR}/Estado.o \
	${OBJECTDIR}/Robo.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/Navegacao.o \
	${OBJECTDIR}/Perseguicao.o \
	${OBJECTDIR}/EvitarColisao.o \
	${OBJECTDIR}/Andar.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-std=c++0x -Wextra
CXXFLAGS=-std=c++0x -Wextra

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=`pkg-config --libs opencv` `pkg-config --libs playerc++`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/progrobos

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/progrobos: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/progrobos ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/PerdeuRastro.o: PerdeuRastro.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall `pkg-config --cflags opencv` `pkg-config --cflags playerc++`  -std=c++0x -Wextra -MMD -MP -MF $@.d -o ${OBJECTDIR}/PerdeuRastro.o PerdeuRastro.cpp

${OBJECTDIR}/Estado.o: Estado.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall `pkg-config --cflags opencv` `pkg-config --cflags playerc++`  -std=c++0x -Wextra -MMD -MP -MF $@.d -o ${OBJECTDIR}/Estado.o Estado.cpp

${OBJECTDIR}/Robo.o: Robo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall `pkg-config --cflags opencv` `pkg-config --cflags playerc++`  -std=c++0x -Wextra -MMD -MP -MF $@.d -o ${OBJECTDIR}/Robo.o Robo.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall `pkg-config --cflags opencv` `pkg-config --cflags playerc++`  -std=c++0x -Wextra -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/Navegacao.o: Navegacao.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall `pkg-config --cflags opencv` `pkg-config --cflags playerc++`  -std=c++0x -Wextra -MMD -MP -MF $@.d -o ${OBJECTDIR}/Navegacao.o Navegacao.cpp

${OBJECTDIR}/Perseguicao.o: Perseguicao.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall `pkg-config --cflags opencv` `pkg-config --cflags playerc++`  -std=c++0x -Wextra -MMD -MP -MF $@.d -o ${OBJECTDIR}/Perseguicao.o Perseguicao.cpp

${OBJECTDIR}/EvitarColisao.o: EvitarColisao.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall `pkg-config --cflags opencv` `pkg-config --cflags playerc++`  -std=c++0x -Wextra -MMD -MP -MF $@.d -o ${OBJECTDIR}/EvitarColisao.o EvitarColisao.cpp

${OBJECTDIR}/Andar.o: Andar.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall `pkg-config --cflags opencv` `pkg-config --cflags playerc++`  -std=c++0x -Wextra -MMD -MP -MF $@.d -o ${OBJECTDIR}/Andar.o Andar.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/progrobos

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
