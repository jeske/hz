# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=laux31 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to laux31 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "laux31 - Win32 Release" && "$(CFG)" != "laux31 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "laux31.mak" CFG="laux31 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "laux31 - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "laux31 - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
CPP=cl.exe

!IF  "$(CFG)" == "laux31 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\laux31.lib"

CLEAN : 
	-@erase ".\Release\laux31.lib"
	-@erase ".\Release\lstrlib.obj"
	-@erase ".\Release\lmathlib.obj"
	-@erase ".\Release\liolib.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/laux31.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/laux31.bsc" 
BSC32_SBRS=
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/laux31.lib" 
LIB32_OBJS= \
	"$(INTDIR)/lstrlib.obj" \
	"$(INTDIR)/lmathlib.obj" \
	"$(INTDIR)/liolib.obj"

"$(OUTDIR)\laux31.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "laux31 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "laux31__"
# PROP BASE Intermediate_Dir "laux31__"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "laux31__"
# PROP Intermediate_Dir "laux31__"
# PROP Target_Dir ""
OUTDIR=.\laux31__
INTDIR=.\laux31__

ALL : "$(OUTDIR)\laux31.lib"

CLEAN : 
	-@erase ".\laux31__\laux31.lib"
	-@erase ".\laux31__\lstrlib.obj"
	-@erase ".\laux31__\lmathlib.obj"
	-@erase ".\laux31__\liolib.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MLd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/laux31.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\laux31__/
CPP_SBRS=
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/laux31.bsc" 
BSC32_SBRS=
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/laux31.lib" 
LIB32_OBJS= \
	"$(INTDIR)/lstrlib.obj" \
	"$(INTDIR)/lmathlib.obj" \
	"$(INTDIR)/liolib.obj"

"$(OUTDIR)\laux31.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "laux31 - Win32 Release"
# Name "laux31 - Win32 Debug"

!IF  "$(CFG)" == "laux31 - Win32 Release"

!ELSEIF  "$(CFG)" == "laux31 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\lstrlib.c
DEP_CPP_LSTRL=\
	{$(INCLUDE)}"\lauxlib.h"\
	{$(INCLUDE)}"\lua.h"\
	{$(INCLUDE)}"\lualib.h"\
	

"$(INTDIR)\lstrlib.obj" : $(SOURCE) $(DEP_CPP_LSTRL) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\lmathlib.c
DEP_CPP_LMATH=\
	{$(INCLUDE)}"\lauxlib.h"\
	{$(INCLUDE)}"\lua.h"\
	{$(INCLUDE)}"\lualib.h"\
	

"$(INTDIR)\lmathlib.obj" : $(SOURCE) $(DEP_CPP_LMATH) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\liolib.c
DEP_CPP_LIOLI=\
	{$(INCLUDE)}"\lauxlib.h"\
	{$(INCLUDE)}"\lua.h"\
	{$(INCLUDE)}"\luadebug.h"\
	{$(INCLUDE)}"\lualib.h"\
	

"$(INTDIR)\liolib.obj" : $(SOURCE) $(DEP_CPP_LIOLI) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
