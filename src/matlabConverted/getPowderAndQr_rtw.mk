###########################################################################
## Makefile generated for MATLAB file/project 'getPowderAndQr'. 
## 
## Makefile     : getPowderAndQr_rtw.mk
## Generated on : Fri Oct 23 01:56:01 2015
## MATLAB Coder version: 2.7 (R2014b)
## 
## Build Info:
## 
## Final product: $(RELATIVE_PATH_TO_ANCHOR)\getPowderAndQr.lib
## Product type : static-library
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# COMPUTER                Computer type. See the MATLAB "computer" command.
# PERL                    PERL Tool
# GEN_LNK_SCRIPT          Perl script to generate the command file
# CMD_FILE                Command file

PRODUCT_NAME              = getPowderAndQr
MAKEFILE                  = getPowderAndQr_rtw.mk
COMPUTER                  = PCWIN64
MATLAB_ROOT               = C:\PROGRA~1\MATLAB\R2014b
MATLAB_BIN                = C:\PROGRA~1\MATLAB\R2014b\bin
MATLAB_ARCH_BIN           = C:\PROGRA~1\MATLAB\R2014b\bin\win64
MASTER_ANCHOR_DIR         = 
START_DIR                 = C:\Users\cwwong\Dropbox\temp\PUF_code_conversion
ARCH                      = win64
RELATIVE_PATH_TO_ANCHOR   = .
PERL                      = $(MATLAB_ROOT)\sys\perl\win32\bin\perl.exe
GEN_LNK_SCRIPT            = $(MATLAB_ROOT)\rtw\c\tools\mkvc_lnk.pl
CMD_FILE                  = $(PRODUCT_NAME).lnk
NODEBUG                   = 1

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          Microsoft Visual C++ 2013 v12.0 | nmake (64-bit Windows)
# Supported Version(s):    12.0
# ToolchainInfo Version:   R2014b
# Specification Revision:  1.0
# 

!include $(MATLAB_ROOT)\rtw\c\tools\vcdefs.mak


#-------------------------------------------
# Macros assumed to be defined elsewhere
#-------------------------------------------

# NODEBUG
# cvarsdll
# cvarsmt
# conlibsmt
# ldebug
# conflags
# cflags

#-----------
# MACROS
#-----------

MEX_OPTS_FILE       = $(MATLAB_ROOT)\bin\$(ARCH)\mexopts\msvc2013.xml
MW_EXTERNLIB_DIR    = $(MATLAB_ROOT)\extern\lib\win64\microsoft
MW_LIB_DIR          = $(MATLAB_ROOT)\lib\win64
MEX_ARCH            = -win64
CPU                 = AMD64
APPVER              = 5.02
CVARSFLAG           = $(cvarsmt)
CFLAGS_ADDITIONAL   = -D_CRT_SECURE_NO_WARNINGS
CPPFLAGS_ADDITIONAL = -EHs -D_CRT_SECURE_NO_WARNINGS
LIBS_TOOLCHAIN      = $(conlibs)

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: Microsoft Visual C Compiler
CC = cl

# Linker: Microsoft Visual C Linker
LD = link

# C++ Compiler: Microsoft Visual C++ Compiler
CPP = cl

# C++ Linker: Microsoft Visual C++ Linker
CPP_LD = link

# Archiver: Microsoft Visual C/C++ Archiver
AR = lib

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_BIN)
MEX = $(MEX_PATH)\mex

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: NMAKE Utility
MAKE = nmake


#-------------------------
# Directives/Utilities
#-------------------------

CDEBUG              = -Zi
C_OUTPUT_FLAG       = -Fo
LDDEBUG             = /DEBUG
OUTPUT_FLAG         = -out:
CPPDEBUG            = -Zi
CPP_OUTPUT_FLAG     = -Fo
CPPLDDEBUG          = /DEBUG
OUTPUT_FLAG         = -out:
ARDEBUG             =
STATICLIB_OUTPUT_FLAG = -out:
MEX_DEBUG           = -g
RM                  = @del
ECHO                = @echo
MV                  = @ren
RUN                 = @cmd /C

#----------------------------------------
# "Faster Builds" Build Configuration
#----------------------------------------

ARFLAGS              = /nologo
CFLAGS               = $(cflags) $(CVARSFLAG) $(CFLAGS_ADDITIONAL) \
                       /Od /Oy-
CPPFLAGS             = /TP $(cflags) $(CVARSFLAG) $(CPPFLAGS_ADDITIONAL) \
                       /Od /Oy-
CPP_LDFLAGS          = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN)
CPP_SHAREDLIB_LDFLAGS  = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN) \
                         -dll -def:$(DEF_FILE)
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN)
MEX_CFLAGS           = $(MEX_ARCH) OPTIMFLAGS="/Od /Oy- $(MDFLAG) $(DEFINES)" $(MEX_OPTS_FLAG)
MEX_LDFLAGS          = LDFLAGS=='$$LDFLAGS'
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN) \
                       -dll -def:$(DEF_FILE)

#--------------------
# File extensions
#--------------------

H_EXT               = .h
OBJ_EXT             = .obj
C_EXT               = .c
EXE_EXT             = .exe
SHAREDLIB_EXT       = .dll
HPP_EXT             = .hpp
OBJ_EXT             = .obj
CPP_EXT             = .cpp
EXE_EXT             = .exe
SHAREDLIB_EXT       = .dll
STATICLIB_EXT       = .lib
MEX_EXT             = .mexw64
MAKE_EXT            = .mk


###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = $(RELATIVE_PATH_TO_ANCHOR)\getPowderAndQr.lib
PRODUCT_TYPE = "static-library"
BUILD_TYPE = "Static Library"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = $(START_DIR);$(START_DIR)\codegen\lib\getPowderAndQr;$(MATLAB_ROOT)\toolbox\dsp\include;$(MATLAB_ROOT)\toolbox\vision\visionrt\export\include\visionrt;$(MATLAB_ROOT)\toolbox\shared\dsp\vision\matlab\include;$(MATLAB_ROOT)\toolbox\vision\include;$(MATLAB_ROOT)\toolbox\vision\visionrt\export\include;$(MATLAB_ROOT)\extern\include;$(MATLAB_ROOT)\simulink\include;$(MATLAB_ROOT)\rtw\c\src;$(MATLAB_ROOT)\rtw\c\src\ext_mode\common;$(MATLAB_ROOT)\rtw\c\ert

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_STANDARD = -DMODEL=getPowderAndQr -DHAVESTDIO -DUSE_RTMODEL

DEFINES = $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)\codegen\lib\getPowderAndQr\getPowderAndQr_rtwutil.c $(START_DIR)\codegen\lib\getPowderAndQr\getPowderAndQr_data.c $(START_DIR)\codegen\lib\getPowderAndQr\getPowderAndQr_initialize.c $(START_DIR)\codegen\lib\getPowderAndQr\getPowderAndQr_terminate.c $(START_DIR)\codegen\lib\getPowderAndQr\getPowderAndQr.c $(START_DIR)\codegen\lib\getPowderAndQr\AlignWorker_v2.c $(START_DIR)\codegen\lib\getPowderAndQr\getRefMarkersAntiAlias.c $(START_DIR)\codegen\lib\getPowderAndQr\repmat.c $(START_DIR)\codegen\lib\getPowderAndQr\rdivide.c $(START_DIR)\codegen\lib\getPowderAndQr\round.c $(START_DIR)\codegen\lib\getPowderAndQr\imgDetrend_v2.c $(START_DIR)\codegen\lib\getPowderAndQr\abs.c $(START_DIR)\codegen\lib\getPowderAndQr\eps.c $(START_DIR)\codegen\lib\getPowderAndQr\median.c $(START_DIR)\codegen\lib\getPowderAndQr\mean.c $(START_DIR)\codegen\lib\getPowderAndQr\meshgrid.c $(START_DIR)\codegen\lib\getPowderAndQr\ransacFit_quad.c $(START_DIR)\codegen\lib\getPowderAndQr\power.c $(START_DIR)\codegen\lib\getPowderAndQr\rand.c $(START_DIR)\codegen\lib\getPowderAndQr\eml_rand_mt19937ar_stateful.c $(START_DIR)\codegen\lib\getPowderAndQr\rcond.c $(START_DIR)\codegen\lib\getPowderAndQr\norm.c $(START_DIR)\codegen\lib\getPowderAndQr\mldivide.c $(START_DIR)\codegen\lib\getPowderAndQr\SystemCore.c $(START_DIR)\codegen\lib\getPowderAndQr\Nondirect.c $(START_DIR)\codegen\lib\getPowderAndQr\findFourLines_v2.c $(START_DIR)\codegen\lib\getPowderAndQr\LocalMaximaFinder.c $(START_DIR)\codegen\lib\getPowderAndQr\fliplr.c $(START_DIR)\codegen\lib\getPowderAndQr\getMorePreciseMaxPoints.c $(START_DIR)\codegen\lib\getPowderAndQr\interp2.c $(START_DIR)\codegen\lib\getPowderAndQr\isplaid.c $(START_DIR)\codegen\lib\getPowderAndQr\spline.c $(START_DIR)\codegen\lib\getPowderAndQr\TensorGriddedInterp.c $(START_DIR)\codegen\lib\getPowderAndQr\pwchcore.c $(START_DIR)\codegen\lib\getPowderAndQr\ppval.c $(START_DIR)\codegen\lib\getPowderAndQr\houghlines_precise.c $(START_DIR)\codegen\lib\getPowderAndQr\sortrows.c $(START_DIR)\codegen\lib\getPowderAndQr\diff.c $(START_DIR)\codegen\lib\getPowderAndQr\sum.c $(START_DIR)\codegen\lib\getPowderAndQr\sqrt.c $(START_DIR)\codegen\lib\getPowderAndQr\findPointOnTheLine.c $(START_DIR)\codegen\lib\getPowderAndQr\eliminateDuplicatedLines_new.c $(START_DIR)\codegen\lib\getPowderAndQr\groupParallelLines.c $(START_DIR)\codegen\lib\getPowderAndQr\sortLinesInOrder.c $(START_DIR)\codegen\lib\getPowderAndQr\calcIntersectionUsingTwoLines.c $(START_DIR)\codegen\lib\getPowderAndQr\det.c $(START_DIR)\codegen\lib\getPowderAndQr\eml_sort.c $(START_DIR)\codegen\lib\getPowderAndQr\pickOutAPossiblePairOfGroups.c $(START_DIR)\codegen\lib\getPowderAndQr\fitgeotrans.c $(START_DIR)\codegen\lib\getPowderAndQr\normalizeControlPoints.c $(START_DIR)\codegen\lib\getPowderAndQr\svd.c $(START_DIR)\codegen\lib\getPowderAndQr\inv.c $(START_DIR)\codegen\lib\getPowderAndQr\projective2d.c $(START_DIR)\codegen\lib\getPowderAndQr\imref2d.c $(START_DIR)\codegen\lib\getPowderAndQr\imwarp.c $(START_DIR)\codegen\lib\getPowderAndQr\interp2d.c $(START_DIR)\codegen\lib\getPowderAndQr\correlationSearch.c $(START_DIR)\codegen\lib\getPowderAndQr\patchCorr.c $(START_DIR)\codegen\lib\getPowderAndQr\patchCorr_oneSearchMaskOnTheOther.c $(START_DIR)\codegen\lib\getPowderAndQr\calcPearsonCorr.c $(START_DIR)\codegen\lib\getPowderAndQr\patchOrientationCorection.c $(START_DIR)\codegen\lib\getPowderAndQr\flipud.c $(START_DIR)\codegen\lib\getPowderAndQr\myImresize.c $(START_DIR)\codegen\lib\getPowderAndQr\DigitalDevice.c $(START_DIR)\codegen\lib\getPowderAndQr\removeReflectivePoints.c $(START_DIR)\codegen\lib\getPowderAndQr\hist.c $(START_DIR)\codegen\lib\getPowderAndQr\histc.c $(START_DIR)\codegen\lib\getPowderAndQr\BlobAnalysis.c $(START_DIR)\codegen\lib\getPowderAndQr\ransacFit_plane.c $(START_DIR)\codegen\lib\getPowderAndQr\getPowderAndQr_emxutil.c $(START_DIR)\codegen\lib\getPowderAndQr\getPowderAndQr_emxAPI.c $(MATLAB_ROOT)\toolbox\vision\visionrt\viphough\hough_d_rt.c $(MATLAB_ROOT)\toolbox\vision\visionrt\viphough\hough_r_rt.c $(START_DIR)\codegen\lib\getPowderAndQr\rt_nonfinite.c $(START_DIR)\codegen\lib\getPowderAndQr\rtGetNaN.c $(START_DIR)\codegen\lib\getPowderAndQr\rtGetInf.c

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = getPowderAndQr_rtwutil.obj getPowderAndQr_data.obj getPowderAndQr_initialize.obj getPowderAndQr_terminate.obj getPowderAndQr.obj AlignWorker_v2.obj getRefMarkersAntiAlias.obj repmat.obj rdivide.obj round.obj imgDetrend_v2.obj abs.obj eps.obj median.obj mean.obj meshgrid.obj ransacFit_quad.obj power.obj rand.obj eml_rand_mt19937ar_stateful.obj rcond.obj norm.obj mldivide.obj SystemCore.obj Nondirect.obj findFourLines_v2.obj LocalMaximaFinder.obj fliplr.obj getMorePreciseMaxPoints.obj interp2.obj isplaid.obj spline.obj TensorGriddedInterp.obj pwchcore.obj ppval.obj houghlines_precise.obj sortrows.obj diff.obj sum.obj sqrt.obj findPointOnTheLine.obj eliminateDuplicatedLines_new.obj groupParallelLines.obj sortLinesInOrder.obj calcIntersectionUsingTwoLines.obj det.obj eml_sort.obj pickOutAPossiblePairOfGroups.obj fitgeotrans.obj normalizeControlPoints.obj svd.obj inv.obj projective2d.obj imref2d.obj imwarp.obj interp2d.obj correlationSearch.obj patchCorr.obj patchCorr_oneSearchMaskOnTheOther.obj calcPearsonCorr.obj patchOrientationCorection.obj flipud.obj myImresize.obj DigitalDevice.obj removeReflectivePoints.obj hist.obj histc.obj BlobAnalysis.obj ransacFit_plane.obj getPowderAndQr_emxutil.obj getPowderAndQr_emxAPI.obj hough_d_rt.obj hough_r_rt.obj rt_nonfinite.obj rtGetNaN.obj rtGetInf.obj

ALL_OBJS = $(OBJS)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = $(MATLAB_ROOT)\extern\lib\win64\microsoft\libmwremaptbb.lib

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS = 

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_BASIC = $(DEFINES) 

CFLAGS = $(CFLAGS) $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_BASIC = $(DEFINES) 

CPPFLAGS = $(CPPFLAGS) $(CPPFLAGS_BASIC)

###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build clean info prebuild download execute set_environment_variables


all : build
	@cmd /C "@echo ### Successfully generated all binary outputs."


build : set_environment_variables prebuild $(PRODUCT)


prebuild : 


download : build


execute : download


set_environment_variables : 
	@set INCLUDE=$(INCLUDES);$(INCLUDE)
	@set LIB=$(LIB)


###########################################################################
## FINAL TARGET
###########################################################################

#---------------------------------
# Create a static library         
#---------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS) $(LIBS)
	$(PERL) $(GEN_LNK_SCRIPT) $(CMD_FILE) $(OBJS)
	@cmd /C "@echo ### Creating static library "$(PRODUCT)" ..."
	$(AR) $(ARFLAGS) -out:$(PRODUCT) @$(CMD_FILE)
	@cmd /C "@echo ### Created: $(PRODUCT)"
	$(RM) $(CMD_FILE)


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(RELATIVE_PATH_TO_ANCHOR)}.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


{$(RELATIVE_PATH_TO_ANCHOR)}.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(MATLAB_ROOT)\rtw\c\src}.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


{$(MATLAB_ROOT)\rtw\c\src}.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(MATLAB_ROOT)\toolbox\vision\visionrt\viphough}.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


{$(MATLAB_ROOT)\toolbox\vision\visionrt\viphough}.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(START_DIR)}.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


{$(START_DIR)}.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(START_DIR)\codegen\lib\getPowderAndQr}.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


{$(START_DIR)\codegen\lib\getPowderAndQr}.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : $(MAKEFILE) rtw_proj.tmw


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@cmd /C "@echo ### PRODUCT = $(PRODUCT)"
	@cmd /C "@echo ### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@cmd /C "@echo ### BUILD_TYPE = $(BUILD_TYPE)"
	@cmd /C "@echo ### INCLUDES = $(INCLUDES)"
	@cmd /C "@echo ### DEFINES = $(DEFINES)"
	@cmd /C "@echo ### ALL_SRCS = $(ALL_SRCS)"
	@cmd /C "@echo ### ALL_OBJS = $(ALL_OBJS)"
	@cmd /C "@echo ### LIBS = $(LIBS)"
	@cmd /C "@echo ### MODELREF_LIBS = $(MODELREF_LIBS)"
	@cmd /C "@echo ### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@cmd /C "@echo ### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@cmd /C "@echo ### CFLAGS = $(CFLAGS)"
	@cmd /C "@echo ### LDFLAGS = $(LDFLAGS)"
	@cmd /C "@echo ### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@cmd /C "@echo ### CPPFLAGS = $(CPPFLAGS)"
	@cmd /C "@echo ### CPP_LDFLAGS = $(CPP_LDFLAGS)"
	@cmd /C "@echo ### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS)"
	@cmd /C "@echo ### ARFLAGS = $(ARFLAGS)"
	@cmd /C "@echo ### MEX_CFLAGS = $(MEX_CFLAGS)"
	@cmd /C "@echo ### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@cmd /C "@echo ### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@cmd /C "@echo ### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@cmd /C "@echo ### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files..."
	@if exist $(PRODUCT) $(RM) $(PRODUCT)
	$(RM) $(ALL_OBJS)
	$(ECHO) "### Deleted all derived files."


