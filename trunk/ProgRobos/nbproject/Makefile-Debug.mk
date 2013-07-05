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
	${OBJECTDIR}/S_CollisionAvoidance.o \
	${OBJECTDIR}/S_Global.o \
	${OBJECTDIR}/S_InitialSetup.o \
	${OBJECTDIR}/S_Tracking.o \
	${OBJECTDIR}/ToolBox.o \
	${OBJECTDIR}/main.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f3

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-std=c++0x
CXXFLAGS=-std=c++0x

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

${OBJECTDIR}/S_CollisionAvoidance.o: nbproject/Makefile-${CND_CONF}.mk S_CollisionAvoidance.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I. `pkg-config --cflags opencv` `pkg-config --cflags playerc++`  -std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/S_CollisionAvoidance.o S_CollisionAvoidance.cpp

${OBJECTDIR}/S_Global.o: nbproject/Makefile-${CND_CONF}.mk S_Global.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I. `pkg-config --cflags opencv` `pkg-config --cflags playerc++`  -std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/S_Global.o S_Global.cpp

${OBJECTDIR}/S_InitialSetup.o: nbproject/Makefile-${CND_CONF}.mk S_InitialSetup.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I. `pkg-config --cflags opencv` `pkg-config --cflags playerc++`  -std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/S_InitialSetup.o S_InitialSetup.cpp

${OBJECTDIR}/S_Tracking.o: nbproject/Makefile-${CND_CONF}.mk S_Tracking.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I. `pkg-config --cflags opencv` `pkg-config --cflags playerc++`  -std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/S_Tracking.o S_Tracking.cpp

${OBJECTDIR}/ToolBox.o: nbproject/Makefile-${CND_CONF}.mk ToolBox.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I. `pkg-config --cflags opencv` `pkg-config --cflags playerc++`  -std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/ToolBox.o ToolBox.cpp

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I. `pkg-config --cflags opencv` `pkg-config --cflags playerc++`  -std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/MatrixTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/MatrixTest2.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f3: ${TESTDIR}/tests/PointTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS} 


${TESTDIR}/tests/MatrixTest.o: tests/MatrixTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I. -I. `pkg-config --cflags opencv` `pkg-config --cflags playerc++`  -std=c++0x -MMD -MP -MF $@.d -o ${TESTDIR}/tests/MatrixTest.o tests/MatrixTest.cpp


${TESTDIR}/tests/MatrixTest2.o: tests/MatrixTest2.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I. -I. `pkg-config --cflags opencv` `pkg-config --cflags playerc++`  -std=c++0x -MMD -MP -MF $@.d -o ${TESTDIR}/tests/MatrixTest2.o tests/MatrixTest2.cpp


${TESTDIR}/tests/PointTest.o: tests/PointTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I. -I. -I. `pkg-config --cflags opencv` `pkg-config --cflags playerc++`  -std=c++0x -MMD -MP -MF $@.d -o ${TESTDIR}/tests/PointTest.o tests/PointTest.cpp


${OBJECTDIR}/S_CollisionAvoidance_nomain.o: ${OBJECTDIR}/S_CollisionAvoidance.o S_CollisionAvoidance.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/S_CollisionAvoidance.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -I. `pkg-config --cflags opencv` `pkg-config --cflags playerc++`  -std=c++0x -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/S_CollisionAvoidance_nomain.o S_CollisionAvoidance.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/S_CollisionAvoidance.o ${OBJECTDIR}/S_CollisionAvoidance_nomain.o;\
	fi

${OBJECTDIR}/S_Global_nomain.o: ${OBJECTDIR}/S_Global.o S_Global.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/S_Global.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -I. `pkg-config --cflags opencv` `pkg-config --cflags playerc++`  -std=c++0x -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/S_Global_nomain.o S_Global.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/S_Global.o ${OBJECTDIR}/S_Global_nomain.o;\
	fi

${OBJECTDIR}/S_InitialSetup_nomain.o: ${OBJECTDIR}/S_InitialSetup.o S_InitialSetup.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/S_InitialSetup.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -I. `pkg-config --cflags opencv` `pkg-config --cflags playerc++`  -std=c++0x -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/S_InitialSetup_nomain.o S_InitialSetup.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/S_InitialSetup.o ${OBJECTDIR}/S_InitialSetup_nomain.o;\
	fi

${OBJECTDIR}/S_Tracking_nomain.o: ${OBJECTDIR}/S_Tracking.o S_Tracking.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/S_Tracking.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -I. `pkg-config --cflags opencv` `pkg-config --cflags playerc++`  -std=c++0x -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/S_Tracking_nomain.o S_Tracking.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/S_Tracking.o ${OBJECTDIR}/S_Tracking_nomain.o;\
	fi

${OBJECTDIR}/ToolBox_nomain.o: ${OBJECTDIR}/ToolBox.o ToolBox.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ToolBox.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -I. `pkg-config --cflags opencv` `pkg-config --cflags playerc++`  -std=c++0x -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/ToolBox_nomain.o ToolBox.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ToolBox.o ${OBJECTDIR}/ToolBox_nomain.o;\
	fi

${OBJECTDIR}/main_nomain.o: ${OBJECTDIR}/main.o main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -I. `pkg-config --cflags opencv` `pkg-config --cflags playerc++`  -std=c++0x -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/main_nomain.o main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/main.o ${OBJECTDIR}/main_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f3 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/progrobos

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
