# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=lua31 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to lua31 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "lua31 - Win32 Release" && "$(CFG)" != "lua31 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "lua31.mak" CFG="lua31 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "lua31 - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "lua31 - Win32 Debug" (based on "Win32 (x86) Static Library")
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
# PROP Target_Last_Scanned "lua31 - Win32 Debug"
CPP=cl.exe

!IF  "$(CFG)" == "lua31 - Win32 Release"

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

ALL : "$(OUTDIR)\lua31.lib"

CLEAN : 
	-@erase ".\Release\lua31.lib"
	-@erase ".\Release\lmem.obj"
	-@erase ".\Release\lvm.obj"
	-@erase ".\Release\lbuffer.obj"
	-@erase ".\Release\lzio.obj"
	-@erase ".\Release\lstate.obj"
	-@erase ".\Release\lauxlib.obj"
	-@erase ".\Release\ltable.obj"
	-@erase ".\Release\lapi.obj"
	-@erase ".\Release\lobject.obj"
	-@erase ".\Release\lfunc.obj"
	-@erase ".\Release\lgc.obj"
	-@erase ".\Release\lundump.obj"
	-@erase ".\Release\ltm.obj"
	-@erase ".\Release\ldo.obj"
	-@erase ".\Release\lstx.obj"
	-@erase ".\Release\llex.obj"
	-@erase ".\Release\lbuiltin.obj"
	-@erase ".\Release\lstring.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/lua31.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/lua31.bsc" 
BSC32_SBRS=
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/lua31.lib" 
LIB32_OBJS= \
	"$(INTDIR)/lmem.obj" \
	"$(INTDIR)/lvm.obj" \
	"$(INTDIR)/lbuffer.obj" \
	"$(INTDIR)/lzio.obj" \
	"$(INTDIR)/lstate.obj" \
	"$(INTDIR)/lauxlib.obj" \
	"$(INTDIR)/ltable.obj" \
	"$(INTDIR)/lapi.obj" \
	"$(INTDIR)/lobject.obj" \
	"$(INTDIR)/lfunc.obj" \
	"$(INTDIR)/lgc.obj" \
	"$(INTDIR)/lundump.obj" \
	"$(INTDIR)/ltm.obj" \
	"$(INTDIR)/ldo.obj" \
	"$(INTDIR)/lstx.obj" \
	"$(INTDIR)/llex.obj" \
	"$(INTDIR)/lbuiltin.obj" \
	"$(INTDIR)/lstring.obj"

"$(OUTDIR)\lua31.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "lua31 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "lua31___"
# PROP BASE Intermediate_Dir "lua31___"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "lua31___"
# PROP Intermediate_Dir "lua31___"
# PROP Target_Dir ""
OUTDIR=.\lua31___
INTDIR=.\lua31___

ALL : "$(OUTDIR)\lua31.lib"

CLEAN : 
	-@erase ".\lua31___\lua31.lib"
	-@erase ".\lua31___\ltable.obj"
	-@erase ".\lua31___\lstx.obj"
	-@erase ".\lua31___\lapi.obj"
	-@erase ".\lua31___\lvm.obj"
	-@erase ".\lua31___\lstring.obj"
	-@erase ".\lua31___\lobject.obj"
	-@erase ".\lua31___\lmem.obj"
	-@erase ".\lua31___\lzio.obj"
	-@erase ".\lua31___\lauxlib.obj"
	-@erase ".\lua31___\llex.obj"
	-@erase ".\lua31___\lgc.obj"
	-@erase ".\lua31___\ltm.obj"
	-@erase ".\lua31___\lfunc.obj"
	-@erase ".\lua31___\ldo.obj"
	-@erase ".\lua31___\lbuiltin.obj"
	-@erase ".\lua31___\lundump.obj"
	-@erase ".\lua31___\lstate.obj"
	-@erase ".\lua31___\lbuffer.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MLd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/lua31.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\lua31___/
CPP_SBRS=
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/lua31.bsc" 
BSC32_SBRS=
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/lua31.lib" 
LIB32_OBJS= \
	"$(INTDIR)/ltable.obj" \
	"$(INTDIR)/lstx.obj" \
	"$(INTDIR)/lapi.obj" \
	"$(INTDIR)/lvm.obj" \
	"$(INTDIR)/lstring.obj" \
	"$(INTDIR)/lobject.obj" \
	"$(INTDIR)/lmem.obj" \
	"$(INTDIR)/lzio.obj" \
	"$(INTDIR)/lauxlib.obj" \
	"$(INTDIR)/llex.obj" \
	"$(INTDIR)/lgc.obj" \
	"$(INTDIR)/ltm.obj" \
	"$(INTDIR)/lfunc.obj" \
	"$(INTDIR)/ldo.obj" \
	"$(INTDIR)/lbuiltin.obj" \
	"$(INTDIR)/lundump.obj" \
	"$(INTDIR)/lstate.obj" \
	"$(INTDIR)/lbuffer.obj"

"$(OUTDIR)\lua31.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
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

# Name "lua31 - Win32 Release"
# Name "lua31 - Win32 Debug"

!IF  "$(CFG)" == "lua31 - Win32 Release"

!ELSEIF  "$(CFG)" == "lua31 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\lapi.c
DEP_CPP_LAPI_=\
	".\lapi.h"\
	{$(INCLUDE)}"\lauxlib.h"\
	".\ldo.h"\
	".\lfunc.h"\
	".\lgc.h"\
	".\lmem.h"\
	".\lobject.h"\
	".\lstate.h"\
	".\lstring.h"\
	".\ltable.h"\
	".\ltm.h"\
	{$(INCLUDE)}"\lua.h"\
	{$(INCLUDE)}"\luadebug.h"\
	".\lvm.h"\
	

"$(INTDIR)\lapi.obj" : $(SOURCE) $(DEP_CPP_LAPI_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\lapi.h

!IF  "$(CFG)" == "lua31 - Win32 Release"

!ELSEIF  "$(CFG)" == "lua31 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lauxlib.c
DEP_CPP_LAUXL=\
	{$(INCLUDE)}"\lauxlib.h"\
	{$(INCLUDE)}"\lua.h"\
	{$(INCLUDE)}"\luadebug.h"\
	

"$(INTDIR)\lauxlib.obj" : $(SOURCE) $(DEP_CPP_LAUXL) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\lbuffer.c
DEP_CPP_LBUFF=\
	{$(INCLUDE)}"\lauxlib.h"\
	".\lmem.h"\
	".\lstate.h"\
	{$(INCLUDE)}"\lua.h"\
	".\lobject.h"\
	

"$(INTDIR)\lbuffer.obj" : $(SOURCE) $(DEP_CPP_LBUFF) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\lbuiltin.c
DEP_CPP_LBUIL=\
	".\lapi.h"\
	{$(INCLUDE)}"\lauxlib.h"\
	".\lbuiltin.h"\
	".\ldo.h"\
	".\lfunc.h"\
	".\lmem.h"\
	".\lobject.h"\
	".\lstate.h"\
	".\lstring.h"\
	".\ltable.h"\
	".\ltm.h"\
	{$(INCLUDE)}"\lua.h"\
	

"$(INTDIR)\lbuiltin.obj" : $(SOURCE) $(DEP_CPP_LBUIL) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\lbuiltin.h

!IF  "$(CFG)" == "lua31 - Win32 Release"

!ELSEIF  "$(CFG)" == "lua31 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ldo.c
DEP_CPP_LDO_C=\
	".\ldo.h"\
	".\lfunc.h"\
	".\lgc.h"\
	".\lmem.h"\
	".\lobject.h"\
	".\lparser.h"\
	".\lstate.h"\
	".\ltm.h"\
	{$(INCLUDE)}"\lua.h"\
	{$(INCLUDE)}"\luadebug.h"\
	".\lundump.h"\
	".\lvm.h"\
	".\lzio.h"\
	

"$(INTDIR)\ldo.obj" : $(SOURCE) $(DEP_CPP_LDO_C) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ldo.h

!IF  "$(CFG)" == "lua31 - Win32 Release"

!ELSEIF  "$(CFG)" == "lua31 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lfunc.c
DEP_CPP_LFUNC=\
	".\lfunc.h"\
	".\lmem.h"\
	".\lstate.h"\
	".\lobject.h"\
	{$(INCLUDE)}"\lua.h"\
	

"$(INTDIR)\lfunc.obj" : $(SOURCE) $(DEP_CPP_LFUNC) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\lfunc.h

!IF  "$(CFG)" == "lua31 - Win32 Release"

!ELSEIF  "$(CFG)" == "lua31 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lgc.c
DEP_CPP_LGC_C=\
	".\ldo.h"\
	".\lfunc.h"\
	".\lgc.h"\
	".\lmem.h"\
	".\lobject.h"\
	".\lstate.h"\
	".\lstring.h"\
	".\ltable.h"\
	".\ltm.h"\
	{$(INCLUDE)}"\lua.h"\
	

"$(INTDIR)\lgc.obj" : $(SOURCE) $(DEP_CPP_LGC_C) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\lgc.h

!IF  "$(CFG)" == "lua31 - Win32 Release"

!ELSEIF  "$(CFG)" == "lua31 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\llex.c
DEP_CPP_LLEX_=\
	{$(INCLUDE)}"\lauxlib.h"\
	".\llex.h"\
	".\lmem.h"\
	".\lobject.h"\
	".\lparser.h"\
	".\lstate.h"\
	".\lstring.h"\
	".\lstx.h"\
	{$(INCLUDE)}"\luadebug.h"\
	".\lzio.h"\
	{$(INCLUDE)}"\lua.h"\
	

"$(INTDIR)\llex.obj" : $(SOURCE) $(DEP_CPP_LLEX_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\llex.h

!IF  "$(CFG)" == "lua31 - Win32 Release"

!ELSEIF  "$(CFG)" == "lua31 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lmem.c
DEP_CPP_LMEM_=\
	".\lmem.h"\
	".\lstate.h"\
	{$(INCLUDE)}"\lua.h"\
	".\lobject.h"\
	

"$(INTDIR)\lmem.obj" : $(SOURCE) $(DEP_CPP_LMEM_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\lmem.h

!IF  "$(CFG)" == "lua31 - Win32 Release"

!ELSEIF  "$(CFG)" == "lua31 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lobject.c
DEP_CPP_LOBJE=\
	".\lobject.h"\
	{$(INCLUDE)}"\lua.h"\
	

"$(INTDIR)\lobject.obj" : $(SOURCE) $(DEP_CPP_LOBJE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\lobject.h

!IF  "$(CFG)" == "lua31 - Win32 Release"

!ELSEIF  "$(CFG)" == "lua31 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lopcodes.h

!IF  "$(CFG)" == "lua31 - Win32 Release"

!ELSEIF  "$(CFG)" == "lua31 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lparser.h

!IF  "$(CFG)" == "lua31 - Win32 Release"

!ELSEIF  "$(CFG)" == "lua31 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lstate.c
DEP_CPP_LSTAT=\
	".\lbuiltin.h"\
	".\ldo.h"\
	".\lfunc.h"\
	".\lgc.h"\
	".\llex.h"\
	".\lmem.h"\
	".\lstate.h"\
	".\lstring.h"\
	".\ltable.h"\
	".\ltm.h"\
	".\lobject.h"\
	{$(INCLUDE)}"\lua.h"\
	".\lzio.h"\
	

"$(INTDIR)\lstate.obj" : $(SOURCE) $(DEP_CPP_LSTAT) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\lstate.h

!IF  "$(CFG)" == "lua31 - Win32 Release"

!ELSEIF  "$(CFG)" == "lua31 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lstring.c
DEP_CPP_LSTRI=\
	".\lmem.h"\
	".\lobject.h"\
	".\lstate.h"\
	".\lstring.h"\
	{$(INCLUDE)}"\lua.h"\
	

"$(INTDIR)\lstring.obj" : $(SOURCE) $(DEP_CPP_LSTRI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\lstring.h

!IF  "$(CFG)" == "lua31 - Win32 Release"

!ELSEIF  "$(CFG)" == "lua31 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lstx.c
DEP_CPP_LSTX_=\
	{$(INCLUDE)}"\lauxlib.h"\
	".\ldo.h"\
	".\lfunc.h"\
	".\llex.h"\
	".\lmem.h"\
	".\lopcodes.h"\
	".\lparser.h"\
	".\lstate.h"\
	".\lstring.h"\
	{$(INCLUDE)}"\lua.h"\
	{$(INCLUDE)}"\luadebug.h"\
	".\lzio.h"\
	".\lobject.h"\
	

"$(INTDIR)\lstx.obj" : $(SOURCE) $(DEP_CPP_LSTX_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\lstx.h

!IF  "$(CFG)" == "lua31 - Win32 Release"

!ELSEIF  "$(CFG)" == "lua31 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ltable.c
DEP_CPP_LTABL=\
	{$(INCLUDE)}"\lauxlib.h"\
	".\lmem.h"\
	".\lobject.h"\
	".\lstate.h"\
	".\ltable.h"\
	{$(INCLUDE)}"\lua.h"\
	

"$(INTDIR)\ltable.obj" : $(SOURCE) $(DEP_CPP_LTABL) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ltable.h

!IF  "$(CFG)" == "lua31 - Win32 Release"

!ELSEIF  "$(CFG)" == "lua31 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ltm.c
DEP_CPP_LTM_C=\
	{$(INCLUDE)}"\lauxlib.h"\
	".\lmem.h"\
	".\lobject.h"\
	".\lstate.h"\
	".\ltm.h"\
	".\lapi.h"\
	{$(INCLUDE)}"\lua.h"\
	

"$(INTDIR)\ltm.obj" : $(SOURCE) $(DEP_CPP_LTM_C) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ltm.h

!IF  "$(CFG)" == "lua31 - Win32 Release"

!ELSEIF  "$(CFG)" == "lua31 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lundump.c
DEP_CPP_LUNDU=\
	{$(INCLUDE)}"\lauxlib.h"\
	".\lfunc.h"\
	".\lmem.h"\
	".\lstring.h"\
	".\lundump.h"\
	{$(INCLUDE)}"\lua.h"\
	".\lobject.h"\
	".\lzio.h"\
	

"$(INTDIR)\lundump.obj" : $(SOURCE) $(DEP_CPP_LUNDU) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\lundump.h

!IF  "$(CFG)" == "lua31 - Win32 Release"

!ELSEIF  "$(CFG)" == "lua31 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lvm.c
DEP_CPP_LVM_C=\
	{$(INCLUDE)}"\lauxlib.h"\
	".\ldo.h"\
	".\lfunc.h"\
	".\lgc.h"\
	".\lmem.h"\
	".\lopcodes.h"\
	".\lstate.h"\
	".\lstring.h"\
	".\ltable.h"\
	".\ltm.h"\
	{$(INCLUDE)}"\luadebug.h"\
	".\lvm.h"\
	{$(INCLUDE)}"\lua.h"\
	".\lobject.h"\
	

"$(INTDIR)\lvm.obj" : $(SOURCE) $(DEP_CPP_LVM_C) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\lvm.h

!IF  "$(CFG)" == "lua31 - Win32 Release"

!ELSEIF  "$(CFG)" == "lua31 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lzio.c
DEP_CPP_LZIO_=\
	".\lzio.h"\
	

"$(INTDIR)\lzio.obj" : $(SOURCE) $(DEP_CPP_LZIO_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\lzio.h

!IF  "$(CFG)" == "lua31 - Win32 Release"

!ELSEIF  "$(CFG)" == "lua31 - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
