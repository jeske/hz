# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=HZ - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to HZ - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "HZ - Win32 Release" && "$(CFG)" != "HZ - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "hz.mak" CFG="HZ - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "HZ - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "HZ - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "HZ - Win32 Debug"
RSC=rc.exe
CPP=cl.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "HZ - Win32 Release"

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

ALL : "$(OUTDIR)\hz.exe"

CLEAN : 
	-@erase "$(INTDIR)\concmd.obj"
	-@erase "$(INTDIR)\control.obj"
	-@erase "$(INTDIR)\ddutil.obj"
	-@erase "$(INTDIR)\donuts.obj"
	-@erase "$(INTDIR)\donuts.res"
	-@erase "$(INTDIR)\drawhndl.obj"
	-@erase "$(INTDIR)\game.obj"
	-@erase "$(INTDIR)\hndlmgr.obj"
	-@erase "$(INTDIR)\i_draw.obj"
	-@erase "$(INTDIR)\i_main.obj"
	-@erase "$(INTDIR)\i_net.obj"
	-@erase "$(INTDIR)\i_sound.obj"
	-@erase "$(INTDIR)\i_sprtet.obj"
	-@erase "$(INTDIR)\i_system.obj"
	-@erase "$(INTDIR)\i_video.obj"
	-@erase "$(INTDIR)\luabase.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\map.obj"
	-@erase "$(INTDIR)\misc.obj"
	-@erase "$(INTDIR)\net.obj"
	-@erase "$(INTDIR)\platform.obj"
	-@erase "$(INTDIR)\sound.obj"
	-@erase "$(INTDIR)\sprite.obj"
	-@erase "$(INTDIR)\spritet.obj"
	-@erase "$(INTDIR)\vconsole.obj"
	-@erase "$(INTDIR)\view.obj"
	-@erase "$(OUTDIR)\hz.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "OS_WIN" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "OS_WIN" /Fp"$(INTDIR)/hz.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /i "c:\DXSDK\sdk\inc\" /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/donuts.res" /i "c:\DXSDK\sdk\inc\" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/hz.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 lua.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /nodefaultlib
LINK32_FLAGS=lua.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)/hz.pdb" /machine:I386\
 /out:"$(OUTDIR)/hz.exe" 
LINK32_OBJS= \
	"$(INTDIR)\concmd.obj" \
	"$(INTDIR)\control.obj" \
	"$(INTDIR)\ddutil.obj" \
	"$(INTDIR)\donuts.obj" \
	"$(INTDIR)\donuts.res" \
	"$(INTDIR)\drawhndl.obj" \
	"$(INTDIR)\game.obj" \
	"$(INTDIR)\hndlmgr.obj" \
	"$(INTDIR)\i_draw.obj" \
	"$(INTDIR)\i_main.obj" \
	"$(INTDIR)\i_net.obj" \
	"$(INTDIR)\i_sound.obj" \
	"$(INTDIR)\i_sprtet.obj" \
	"$(INTDIR)\i_system.obj" \
	"$(INTDIR)\i_video.obj" \
	"$(INTDIR)\luabase.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\map.obj" \
	"$(INTDIR)\misc.obj" \
	"$(INTDIR)\net.obj" \
	"$(INTDIR)\platform.obj" \
	"$(INTDIR)\sound.obj" \
	"$(INTDIR)\sprite.obj" \
	"$(INTDIR)\spritet.obj" \
	"$(INTDIR)\vconsole.obj" \
	"$(INTDIR)\view.obj"

"$(OUTDIR)\hz.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : ".\Target\HZ.exe" "$(OUTDIR)\hz.bsc"

CLEAN : 
	-@erase "$(INTDIR)\concmd.obj"
	-@erase "$(INTDIR)\concmd.sbr"
	-@erase "$(INTDIR)\control.obj"
	-@erase "$(INTDIR)\control.sbr"
	-@erase "$(INTDIR)\ddutil.obj"
	-@erase "$(INTDIR)\ddutil.sbr"
	-@erase "$(INTDIR)\donuts.obj"
	-@erase "$(INTDIR)\donuts.sbr"
	-@erase "$(INTDIR)\drawhndl.obj"
	-@erase "$(INTDIR)\drawhndl.sbr"
	-@erase "$(INTDIR)\game.obj"
	-@erase "$(INTDIR)\game.sbr"
	-@erase "$(INTDIR)\hndlmgr.obj"
	-@erase "$(INTDIR)\hndlmgr.sbr"
	-@erase "$(INTDIR)\i_draw.obj"
	-@erase "$(INTDIR)\i_draw.sbr"
	-@erase "$(INTDIR)\i_main.obj"
	-@erase "$(INTDIR)\i_main.sbr"
	-@erase "$(INTDIR)\i_net.obj"
	-@erase "$(INTDIR)\i_net.sbr"
	-@erase "$(INTDIR)\i_sound.obj"
	-@erase "$(INTDIR)\i_sound.sbr"
	-@erase "$(INTDIR)\i_sprtet.obj"
	-@erase "$(INTDIR)\i_sprtet.sbr"
	-@erase "$(INTDIR)\i_system.obj"
	-@erase "$(INTDIR)\i_system.sbr"
	-@erase "$(INTDIR)\i_video.obj"
	-@erase "$(INTDIR)\i_video.sbr"
	-@erase "$(INTDIR)\luabase.obj"
	-@erase "$(INTDIR)\luabase.sbr"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\main.sbr"
	-@erase "$(INTDIR)\map.obj"
	-@erase "$(INTDIR)\map.sbr"
	-@erase "$(INTDIR)\misc.obj"
	-@erase "$(INTDIR)\misc.sbr"
	-@erase "$(INTDIR)\net.obj"
	-@erase "$(INTDIR)\net.sbr"
	-@erase "$(INTDIR)\platform.obj"
	-@erase "$(INTDIR)\platform.sbr"
	-@erase "$(INTDIR)\sound.obj"
	-@erase "$(INTDIR)\sound.sbr"
	-@erase "$(INTDIR)\sprite.obj"
	-@erase "$(INTDIR)\sprite.sbr"
	-@erase "$(INTDIR)\spritet.obj"
	-@erase "$(INTDIR)\spritet.sbr"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\vconsole.obj"
	-@erase "$(INTDIR)\vconsole.sbr"
	-@erase "$(INTDIR)\view.obj"
	-@erase "$(INTDIR)\view.sbr"
	-@erase "$(OUTDIR)\hz.bsc"
	-@erase "$(OUTDIR)\HZ.pdb"
	-@erase ".\hz.res"
	-@erase ".\Target\HZ.exe"
	-@erase ".\Target\HZ.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /W3 /GX /Zi /Od /I "c:\dx7asdk\dxf\include" /I "..\lua31\include" /I "os_win" /D "_DEBUG" /D "LUA_COMPAT2_5" /D "WIN32" /D "_WINDOWS" /D "OS_WIN" /U "USE_DSOUND" /FR /YX /c
CPP_PROJ=/nologo /MTd /W3 /GX /Zi /Od /I "c:\dx7asdk\dxf\include" /I\
 "..\lua31\include" /I "os_win" /D "_DEBUG" /D "LUA_COMPAT2_5" /D "WIN32" /D\
 "_WINDOWS" /D "OS_WIN" /U "USE_DSOUND" /FR"$(INTDIR)/" /Fp"$(INTDIR)/hz.pch"\
 /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /fo"hz.res" /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"hz.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/hz.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\concmd.sbr" \
	"$(INTDIR)\control.sbr" \
	"$(INTDIR)\ddutil.sbr" \
	"$(INTDIR)\donuts.sbr" \
	"$(INTDIR)\drawhndl.sbr" \
	"$(INTDIR)\game.sbr" \
	"$(INTDIR)\hndlmgr.sbr" \
	"$(INTDIR)\i_draw.sbr" \
	"$(INTDIR)\i_main.sbr" \
	"$(INTDIR)\i_net.sbr" \
	"$(INTDIR)\i_sound.sbr" \
	"$(INTDIR)\i_sprtet.sbr" \
	"$(INTDIR)\i_system.sbr" \
	"$(INTDIR)\i_video.sbr" \
	"$(INTDIR)\luabase.sbr" \
	"$(INTDIR)\main.sbr" \
	"$(INTDIR)\map.sbr" \
	"$(INTDIR)\misc.sbr" \
	"$(INTDIR)\net.sbr" \
	"$(INTDIR)\platform.sbr" \
	"$(INTDIR)\sound.sbr" \
	"$(INTDIR)\sprite.sbr" \
	"$(INTDIR)\spritet.sbr" \
	"$(INTDIR)\vconsole.sbr" \
	"$(INTDIR)\view.sbr"

"$(OUTDIR)\hz.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 dplayx.lib ddraw.lib dxguid.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib lua31.lib laux31.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Target/HZ.exe"
# SUBTRACT LINK32 /pdb:none /nodefaultlib
LINK32_FLAGS=dplayx.lib ddraw.lib dxguid.lib winmm.lib kernel32.lib user32.lib\
 gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib\
 oleaut32.lib uuid.lib lua31.lib laux31.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/HZ.pdb" /debug /machine:I386\
 /out:"Target/HZ.exe" 
LINK32_OBJS= \
	"$(INTDIR)\concmd.obj" \
	"$(INTDIR)\control.obj" \
	"$(INTDIR)\ddutil.obj" \
	"$(INTDIR)\donuts.obj" \
	"$(INTDIR)\drawhndl.obj" \
	"$(INTDIR)\game.obj" \
	"$(INTDIR)\hndlmgr.obj" \
	"$(INTDIR)\i_draw.obj" \
	"$(INTDIR)\i_main.obj" \
	"$(INTDIR)\i_net.obj" \
	"$(INTDIR)\i_sound.obj" \
	"$(INTDIR)\i_sprtet.obj" \
	"$(INTDIR)\i_system.obj" \
	"$(INTDIR)\i_video.obj" \
	"$(INTDIR)\luabase.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\map.obj" \
	"$(INTDIR)\misc.obj" \
	"$(INTDIR)\net.obj" \
	"$(INTDIR)\platform.obj" \
	"$(INTDIR)\sound.obj" \
	"$(INTDIR)\sprite.obj" \
	"$(INTDIR)\spritet.obj" \
	"$(INTDIR)\vconsole.obj" \
	"$(INTDIR)\view.obj" \
	".\hz.res"

".\Target\HZ.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
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

# Name "HZ - Win32 Release"
# Name "HZ - Win32 Debug"

!IF  "$(CFG)" == "HZ - Win32 Release"

!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\view.cpp

!IF  "$(CFG)" == "HZ - Win32 Release"

DEP_CPP_VIEW_=\
	"..\lua31\include\lua.h"\
	".\drawhndl.h"\
	".\dsutil.h"\
	".\hndlmgr.h"\
	".\i_draw.h"\
	".\i_sprtet.h"\
	".\i_system.h"\
	".\i_video.h"\
	".\luabase.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\main.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\osdep.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_VIEW_=\
	".\translate.h"\
	

"$(INTDIR)\view.obj" : $(SOURCE) $(DEP_CPP_VIEW_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_VIEW_=\
	"..\lua31\include\lua.h"\
	".\luabase.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\main.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\os_win\drawhndl.h"\
	".\os_win\dsutil.h"\
	".\os_win\hndlmgr.h"\
	".\os_win\i_draw.h"\
	".\os_win\i_image.h"\
	".\os_win\i_sprtet.h"\
	".\os_win\i_system.h"\
	".\os_win\i_video.h"\
	".\osdep.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_VIEW_=\
	".\translate.h"\
	

"$(INTDIR)\view.obj" : $(SOURCE) $(DEP_CPP_VIEW_) "$(INTDIR)"

"$(INTDIR)\view.sbr" : $(SOURCE) $(DEP_CPP_VIEW_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\main.cpp

!IF  "$(CFG)" == "HZ - Win32 Release"

DEP_CPP_MAIN_=\
	"..\lua31\include\lua.h"\
	".\concmd.h"\
	".\drawhndl.h"\
	".\dsutil.h"\
	".\hndlmgr.h"\
	".\i_draw.h"\
	".\i_sprtet.h"\
	".\i_system.h"\
	".\i_video.h"\
	".\luabase.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\main.h"\
	".\os_win\..\map.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_MAIN_=\
	".\i_console.h"\
	".\resource.h"\
	".\translate.h"\
	

"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_MAIN_=\
	"..\lua31\include\lua.h"\
	".\concmd.h"\
	".\luabase.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\main.h"\
	".\os_win\..\map.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\os_win\drawhndl.h"\
	".\os_win\dsutil.h"\
	".\os_win\hndlmgr.h"\
	".\os_win\i_draw.h"\
	".\os_win\i_image.h"\
	".\os_win\i_sprtet.h"\
	".\os_win\i_system.h"\
	".\os_win\i_video.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_MAIN_=\
	".\i_console.h"\
	".\translate.h"\
	

"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"

"$(INTDIR)\main.sbr" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\donuts.cpp

!IF  "$(CFG)" == "HZ - Win32 Release"

DEP_CPP_DONUT=\
	"..\lua31\include\lua.h"\
	".\drawhndl.h"\
	".\dsutil.h"\
	".\i_draw.h"\
	".\i_sprtet.h"\
	".\i_system.h"\
	".\i_video.h"\
	".\luabase.h"\
	".\misc.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\Game.h"\
	".\os_win\..\main.h"\
	".\os_win\..\map.h"\
	".\os_win\..\net.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\osdep.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_DONUT=\
	".\resource.h"\
	".\translate.h"\
	

"$(INTDIR)\donuts.obj" : $(SOURCE) $(DEP_CPP_DONUT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_DONUT=\
	"..\lua31\include\lua.h"\
	".\luabase.h"\
	".\misc.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\Game.h"\
	".\os_win\..\main.h"\
	".\os_win\..\map.h"\
	".\os_win\..\net.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\os_win\drawhndl.h"\
	".\os_win\dsutil.h"\
	".\os_win\i_draw.h"\
	".\os_win\i_image.h"\
	".\os_win\i_sprtet.h"\
	".\os_win\i_system.h"\
	".\os_win\i_video.h"\
	".\osdep.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_DONUT=\
	".\translate.h"\
	

"$(INTDIR)\donuts.obj" : $(SOURCE) $(DEP_CPP_DONUT) "$(INTDIR)"

"$(INTDIR)\donuts.sbr" : $(SOURCE) $(DEP_CPP_DONUT) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\sprite.cpp

!IF  "$(CFG)" == "HZ - Win32 Release"

DEP_CPP_SPRIT=\
	"..\lua31\include\lua.h"\
	".\drawhndl.h"\
	".\dsutil.h"\
	".\i_sprtet.h"\
	".\luabase.h"\
	".\misc.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\main.h"\
	".\os_win\..\map.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_SPRIT=\
	".\i_video.h"\
	".\translate.h"\
	

"$(INTDIR)\sprite.obj" : $(SOURCE) $(DEP_CPP_SPRIT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_SPRIT=\
	"..\lua31\include\lua.h"\
	".\luabase.h"\
	".\misc.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\main.h"\
	".\os_win\..\map.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\os_win\drawhndl.h"\
	".\os_win\dsutil.h"\
	".\os_win\i_image.h"\
	".\os_win\i_sprtet.h"\
	".\os_win\i_video.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_SPRIT=\
	".\translate.h"\
	

"$(INTDIR)\sprite.obj" : $(SOURCE) $(DEP_CPP_SPRIT) "$(INTDIR)"

"$(INTDIR)\sprite.sbr" : $(SOURCE) $(DEP_CPP_SPRIT) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\misc.cpp

!IF  "$(CFG)" == "HZ - Win32 Release"

DEP_CPP_MISC_=\
	".\misc.h"\
	".\os_win\..\main.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	
NODEP_CPP_MISC_=\
	".\i_sprtet.h"\
	".\i_video.h"\
	".\translate.h"\
	

"$(INTDIR)\misc.obj" : $(SOURCE) $(DEP_CPP_MISC_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_MISC_=\
	".\misc.h"\
	".\os_win\..\main.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\os_win\i_image.h"\
	".\os_win\i_sprtet.h"\
	".\os_win\i_video.h"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	
NODEP_CPP_MISC_=\
	".\translate.h"\
	

"$(INTDIR)\misc.obj" : $(SOURCE) $(DEP_CPP_MISC_) "$(INTDIR)"

"$(INTDIR)\misc.sbr" : $(SOURCE) $(DEP_CPP_MISC_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\sound.cpp

!IF  "$(CFG)" == "HZ - Win32 Release"


"$(INTDIR)\sound.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"


"$(INTDIR)\sound.obj" : $(SOURCE) "$(INTDIR)"

"$(INTDIR)\sound.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\game.cpp

!IF  "$(CFG)" == "HZ - Win32 Release"

DEP_CPP_GAME_=\
	"..\lua31\include\lua.h"\
	"..\lua31\include\luadebug.h"\
	"..\lua31\include\lualib.h"\
	".\dsutil.h"\
	".\i_sprtet.h"\
	".\i_system.h"\
	".\i_video.h"\
	".\luabase.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\Game.h"\
	".\os_win\..\main.h"\
	".\os_win\..\map.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_GAME_=\
	".\i_console.h"\
	".\translate.h"\
	

"$(INTDIR)\game.obj" : $(SOURCE) $(DEP_CPP_GAME_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_GAME_=\
	"..\lua31\include\lua.h"\
	"..\lua31\include\luadebug.h"\
	"..\lua31\include\lualib.h"\
	".\luabase.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\Game.h"\
	".\os_win\..\main.h"\
	".\os_win\..\map.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\os_win\dsutil.h"\
	".\os_win\i_image.h"\
	".\os_win\i_sprtet.h"\
	".\os_win\i_system.h"\
	".\os_win\i_video.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_GAME_=\
	".\i_console.h"\
	".\translate.h"\
	

"$(INTDIR)\game.obj" : $(SOURCE) $(DEP_CPP_GAME_) "$(INTDIR)"

"$(INTDIR)\game.sbr" : $(SOURCE) $(DEP_CPP_GAME_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\map.cpp

!IF  "$(CFG)" == "HZ - Win32 Release"

DEP_CPP_MAP_C=\
	"..\lua31\include\lua.h"\
	".\drawhndl.h"\
	".\dsutil.h"\
	".\i_draw.h"\
	".\i_sprtet.h"\
	".\i_system.h"\
	".\i_video.h"\
	".\luabase.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\Game.h"\
	".\os_win\..\main.h"\
	".\os_win\..\map.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\osdep.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_MAP_C=\
	".\translate.h"\
	

"$(INTDIR)\map.obj" : $(SOURCE) $(DEP_CPP_MAP_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_MAP_C=\
	"..\lua31\include\lua.h"\
	".\luabase.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\Game.h"\
	".\os_win\..\main.h"\
	".\os_win\..\map.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\os_win\drawhndl.h"\
	".\os_win\dsutil.h"\
	".\os_win\i_draw.h"\
	".\os_win\i_image.h"\
	".\os_win\i_sprtet.h"\
	".\os_win\i_system.h"\
	".\os_win\i_video.h"\
	".\osdep.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_MAP_C=\
	".\translate.h"\
	

"$(INTDIR)\map.obj" : $(SOURCE) $(DEP_CPP_MAP_C) "$(INTDIR)"

"$(INTDIR)\map.sbr" : $(SOURCE) $(DEP_CPP_MAP_C) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\net.cpp

!IF  "$(CFG)" == "HZ - Win32 Release"

DEP_CPP_NET_C=\
	"..\lua31\include\lua.h"\
	".\dsutil.h"\
	".\i_sprtet.h"\
	".\luabase.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\main.h"\
	".\os_win\..\map.h"\
	".\os_win\..\net.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dplay.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_NET_C=\
	".\i_video.h"\
	".\translate.h"\
	

"$(INTDIR)\net.obj" : $(SOURCE) $(DEP_CPP_NET_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_NET_C=\
	"..\lua31\include\lua.h"\
	".\luabase.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\main.h"\
	".\os_win\..\map.h"\
	".\os_win\..\net.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\os_win\dsutil.h"\
	".\os_win\i_image.h"\
	".\os_win\i_sprtet.h"\
	".\os_win\i_video.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dplay.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_NET_C=\
	".\translate.h"\
	

"$(INTDIR)\net.obj" : $(SOURCE) $(DEP_CPP_NET_C) "$(INTDIR)"

"$(INTDIR)\net.sbr" : $(SOURCE) $(DEP_CPP_NET_C) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\concmd.cpp

!IF  "$(CFG)" == "HZ - Win32 Release"

DEP_CPP_CONCM=\
	"..\lua31\include\lua.h"\
	".\concmd.h"\
	".\i_sprtet.h"\
	".\luabase.h"\
	".\os_win\..\main.h"\
	".\os_win\..\map.h"\
	".\os_win\..\net.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\sprite.h"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	
NODEP_CPP_CONCM=\
	".\i_video.h"\
	".\translate.h"\
	

"$(INTDIR)\concmd.obj" : $(SOURCE) $(DEP_CPP_CONCM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_CONCM=\
	"..\lua31\include\lua.h"\
	".\concmd.h"\
	".\luabase.h"\
	".\os_win\..\main.h"\
	".\os_win\..\map.h"\
	".\os_win\..\net.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\os_win\i_image.h"\
	".\os_win\i_sprtet.h"\
	".\os_win\i_video.h"\
	".\sprite.h"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	
NODEP_CPP_CONCM=\
	".\translate.h"\
	

"$(INTDIR)\concmd.obj" : $(SOURCE) $(DEP_CPP_CONCM) "$(INTDIR)"

"$(INTDIR)\concmd.sbr" : $(SOURCE) $(DEP_CPP_CONCM) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\spritet.cpp

!IF  "$(CFG)" == "HZ - Win32 Release"

DEP_CPP_SPRITE=\
	"..\lua31\include\lua.h"\
	".\drawhndl.h"\
	".\dsutil.h"\
	".\i_draw.h"\
	".\i_sprtet.h"\
	".\luabase.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\main.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_SPRITE=\
	".\i_video.h"\
	".\translate.h"\
	

"$(INTDIR)\spritet.obj" : $(SOURCE) $(DEP_CPP_SPRITE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_SPRITE=\
	"..\lua31\include\lua.h"\
	".\luabase.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\main.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\os_win\drawhndl.h"\
	".\os_win\dsutil.h"\
	".\os_win\i_draw.h"\
	".\os_win\i_image.h"\
	".\os_win\i_sprtet.h"\
	".\os_win\i_video.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_SPRITE=\
	".\translate.h"\
	

"$(INTDIR)\spritet.obj" : $(SOURCE) $(DEP_CPP_SPRITE) "$(INTDIR)"

"$(INTDIR)\spritet.sbr" : $(SOURCE) $(DEP_CPP_SPRITE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\hz.mak

!IF  "$(CFG)" == "HZ - Win32 Release"

!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\vconsole.cpp

!IF  "$(CFG)" == "HZ - Win32 Release"

DEP_CPP_VCONS=\
	"..\lua31\include\lua.h"\
	".\drawhndl.h"\
	".\dsutil.h"\
	".\hndlmgr.h"\
	".\i_sprtet.h"\
	".\i_system.h"\
	".\i_video.h"\
	".\luabase.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\main.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\osdep.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_VCONS=\
	".\translate.h"\
	

"$(INTDIR)\vconsole.obj" : $(SOURCE) $(DEP_CPP_VCONS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_VCONS=\
	"..\lua31\include\lua.h"\
	".\luabase.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\main.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\os_win\drawhndl.h"\
	".\os_win\dsutil.h"\
	".\os_win\hndlmgr.h"\
	".\os_win\i_image.h"\
	".\os_win\i_sprtet.h"\
	".\os_win\i_system.h"\
	".\os_win\i_video.h"\
	".\osdep.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_VCONS=\
	".\translate.h"\
	

"$(INTDIR)\vconsole.obj" : $(SOURCE) $(DEP_CPP_VCONS) "$(INTDIR)"

"$(INTDIR)\vconsole.sbr" : $(SOURCE) $(DEP_CPP_VCONS) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\os_win\donuts.rc
DEP_RSC_DONUTS=\
	".\os_win\..\_old\bangbang.wav"\
	".\os_win\..\_old\bounce.wav"\
	".\os_win\..\_old\c_bang.wav"\
	".\os_win\..\_old\d_bang.wav"\
	".\os_win\..\_old\donuts.bmp"\
	".\os_win\..\_old\gunfire.wav"\
	".\os_win\..\_old\hum.wav"\
	".\os_win\..\_old\level.wav"\
	".\os_win\..\_old\p_bang.wav"\
	".\os_win\..\_old\rev.wav"\
	".\os_win\..\_old\s_bang.wav"\
	".\os_win\..\_old\shield.wav"\
	".\os_win\..\_old\skid.wav"\
	".\os_win\..\_old\Splash.bmp"\
	".\os_win\donuts.ico"\
	".\os_win\icon1.ico"\
	

!IF  "$(CFG)" == "HZ - Win32 Release"


"$(INTDIR)\donuts.res" : $(SOURCE) $(DEP_RSC_DONUTS) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/donuts.res" /i "c:\DXSDK\sdk\inc\" /i "os_win"\
 /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"


".\hz.res" : $(SOURCE) $(DEP_RSC_DONUTS) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"hz.res" /i "os_win" /d "_DEBUG" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\os_win\control.cpp
DEP_CPP_CONTR=\
	".\os_win\control.h"\
	"c:\dx7asdk\dxf\include\dinput.h"\
	

!IF  "$(CFG)" == "HZ - Win32 Release"


"$(INTDIR)\control.obj" : $(SOURCE) $(DEP_CPP_CONTR) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\control.obj" : $(SOURCE) $(DEP_CPP_CONTR) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\control.sbr" : $(SOURCE) $(DEP_CPP_CONTR) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\os_win\ddutil.cpp
DEP_CPP_DDUTI=\
	".\os_win\ddutil.h"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	

!IF  "$(CFG)" == "HZ - Win32 Release"


"$(INTDIR)\ddutil.obj" : $(SOURCE) $(DEP_CPP_DDUTI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ddutil.obj" : $(SOURCE) $(DEP_CPP_DDUTI) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\ddutil.sbr" : $(SOURCE) $(DEP_CPP_DDUTI) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\os_win\drawhndl.cpp

!IF  "$(CFG)" == "HZ - Win32 Release"

DEP_CPP_DRAWH=\
	"..\lua31\include\lua.h"\
	".\dsutil.h"\
	".\i_sprtet.h"\
	".\luabase.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\main.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\os_win\drawhndl.h"\
	".\os_win\i_image.h"\
	".\os_win\i_sprtet.h"\
	".\os_win\i_system.h"\
	".\os_win\i_video.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_DRAWH=\
	".\i_video.h"\
	".\translate.h"\
	

"$(INTDIR)\drawhndl.obj" : $(SOURCE) $(DEP_CPP_DRAWH) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_DRAWH=\
	"..\lua31\include\lua.h"\
	".\luabase.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\main.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\os_win\drawhndl.h"\
	".\os_win\dsutil.h"\
	".\os_win\i_image.h"\
	".\os_win\i_sprtet.h"\
	".\os_win\i_system.h"\
	".\os_win\i_video.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_DRAWH=\
	".\translate.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\drawhndl.obj" : $(SOURCE) $(DEP_CPP_DRAWH) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\drawhndl.sbr" : $(SOURCE) $(DEP_CPP_DRAWH) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\os_win\platform.cpp

!IF  "$(CFG)" == "HZ - Win32 Release"

DEP_CPP_PLATF=\
	"..\lua31\include\lua.h"\
	".\dsutil.h"\
	".\i_sprtet.h"\
	".\luabase.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\Game.h"\
	".\os_win\..\main.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\os_win\i_system.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_PLATF=\
	".\i_video.h"\
	".\translate.h"\
	

"$(INTDIR)\platform.obj" : $(SOURCE) $(DEP_CPP_PLATF) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_PLATF=\
	"..\lua31\include\lua.h"\
	".\luabase.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\Game.h"\
	".\os_win\..\main.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\os_win\dsutil.h"\
	".\os_win\i_image.h"\
	".\os_win\i_sprtet.h"\
	".\os_win\i_system.h"\
	".\os_win\i_video.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_PLATF=\
	".\translate.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\platform.obj" : $(SOURCE) $(DEP_CPP_PLATF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\platform.sbr" : $(SOURCE) $(DEP_CPP_PLATF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\os_win\hndlmgr.cpp
DEP_CPP_HNDLM=\
	".\os_win\hndlmgr.h"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	

!IF  "$(CFG)" == "HZ - Win32 Release"


"$(INTDIR)\hndlmgr.obj" : $(SOURCE) $(DEP_CPP_HNDLM) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\hndlmgr.obj" : $(SOURCE) $(DEP_CPP_HNDLM) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\hndlmgr.sbr" : $(SOURCE) $(DEP_CPP_HNDLM) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\os_win\i_sprtet.cpp

!IF  "$(CFG)" == "HZ - Win32 Release"

DEP_CPP_I_SPR=\
	"..\lua31\include\lua.h"\
	".\dsutil.h"\
	".\i_sprtet.h"\
	".\luabase.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\os_win\i_image.h"\
	".\os_win\i_sprtet.h"\
	".\os_win\i_video.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_I_SPR=\
	".\i_video.h"\
	".\translate.h"\
	

"$(INTDIR)\i_sprtet.obj" : $(SOURCE) $(DEP_CPP_I_SPR) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_I_SPR=\
	"..\lua31\include\lua.h"\
	".\luabase.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\os_win\dsutil.h"\
	".\os_win\i_image.h"\
	".\os_win\i_sprtet.h"\
	".\os_win\i_video.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_I_SPR=\
	".\translate.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\i_sprtet.obj" : $(SOURCE) $(DEP_CPP_I_SPR) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\i_sprtet.sbr" : $(SOURCE) $(DEP_CPP_I_SPR) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\os_win\i_draw.cpp

!IF  "$(CFG)" == "HZ - Win32 Release"

DEP_CPP_I_DRA=\
	"..\lua31\include\lua.h"\
	".\dsutil.h"\
	".\i_sprtet.h"\
	".\luabase.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\spritet.h"\
	".\os_win\ddutil.h"\
	".\os_win\drawhndl.h"\
	".\os_win\hndlmgr.h"\
	".\os_win\i_draw.h"\
	".\os_win\i_image.h"\
	".\os_win\i_sprtet.h"\
	".\os_win\i_video.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_I_DRA=\
	".\translate.h"\
	

"$(INTDIR)\i_draw.obj" : $(SOURCE) $(DEP_CPP_I_DRA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_I_DRA=\
	"..\lua31\include\lua.h"\
	".\luabase.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\spritet.h"\
	".\os_win\ddutil.h"\
	".\os_win\drawhndl.h"\
	".\os_win\dsutil.h"\
	".\os_win\hndlmgr.h"\
	".\os_win\i_draw.h"\
	".\os_win\i_image.h"\
	".\os_win\i_sprtet.h"\
	".\os_win\i_video.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_I_DRA=\
	".\translate.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\i_draw.obj" : $(SOURCE) $(DEP_CPP_I_DRA) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\i_draw.sbr" : $(SOURCE) $(DEP_CPP_I_DRA) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\os_win\i_video.cpp

!IF  "$(CFG)" == "HZ - Win32 Release"

DEP_CPP_I_VID=\
	"..\lua31\include\lua.h"\
	".\dsutil.h"\
	".\i_sprtet.h"\
	".\luabase.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\map.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\os_win\drawhndl.h"\
	".\os_win\hndlmgr.h"\
	".\os_win\i_image.h"\
	".\os_win\i_sprtet.h"\
	".\os_win\i_system.h"\
	".\os_win\i_video.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_I_VID=\
	".\i_video.h"\
	".\translate.h"\
	

"$(INTDIR)\i_video.obj" : $(SOURCE) $(DEP_CPP_I_VID) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_I_VID=\
	"..\lua31\include\lua.h"\
	".\luabase.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\map.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\os_win\drawhndl.h"\
	".\os_win\dsutil.h"\
	".\os_win\hndlmgr.h"\
	".\os_win\i_image.h"\
	".\os_win\i_sprtet.h"\
	".\os_win\i_system.h"\
	".\os_win\i_video.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_I_VID=\
	".\translate.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\i_video.obj" : $(SOURCE) $(DEP_CPP_I_VID) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\i_video.sbr" : $(SOURCE) $(DEP_CPP_I_VID) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\os_win\i_system.cpp

!IF  "$(CFG)" == "HZ - Win32 Release"

DEP_CPP_I_SYS=\
	"..\lua31\include\lua.h"\
	".\dsutil.h"\
	".\i_sprtet.h"\
	".\luabase.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\main.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\os_win\hndlmgr.h"\
	".\os_win\i_image.h"\
	".\os_win\i_sprtet.h"\
	".\os_win\i_system.h"\
	".\os_win\i_video.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_I_SYS=\
	".\i_video.h"\
	".\translate.h"\
	

"$(INTDIR)\i_system.obj" : $(SOURCE) $(DEP_CPP_I_SYS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_I_SYS=\
	"..\lua31\include\lua.h"\
	".\luabase.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\main.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\os_win\dsutil.h"\
	".\os_win\hndlmgr.h"\
	".\os_win\i_image.h"\
	".\os_win\i_sprtet.h"\
	".\os_win\i_system.h"\
	".\os_win\i_video.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_I_SYS=\
	".\translate.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\i_system.obj" : $(SOURCE) $(DEP_CPP_I_SYS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\i_system.sbr" : $(SOURCE) $(DEP_CPP_I_SYS) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\os_win\i_main.cpp

!IF  "$(CFG)" == "HZ - Win32 Release"

DEP_CPP_I_MAI=\
	"..\lua31\include\lua.h"\
	".\dsutil.h"\
	".\i_sprtet.h"\
	".\luabase.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\main.h"\
	".\os_win\..\map.h"\
	".\os_win\..\net.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\os_win\hndlmgr.h"\
	".\os_win\i_image.h"\
	".\os_win\i_sprtet.h"\
	".\os_win\i_system.h"\
	".\os_win\i_video.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_I_MAI=\
	".\i_video.h"\
	".\translate.h"\
	

"$(INTDIR)\i_main.obj" : $(SOURCE) $(DEP_CPP_I_MAI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_I_MAI=\
	"..\lua31\include\lua.h"\
	".\luabase.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\main.h"\
	".\os_win\..\map.h"\
	".\os_win\..\net.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\os_win\dsutil.h"\
	".\os_win\hndlmgr.h"\
	".\os_win\i_image.h"\
	".\os_win\i_sprtet.h"\
	".\os_win\i_system.h"\
	".\os_win\i_video.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_I_MAI=\
	".\translate.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\i_main.obj" : $(SOURCE) $(DEP_CPP_I_MAI) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\i_main.sbr" : $(SOURCE) $(DEP_CPP_I_MAI) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Target\lua\util.lua

!IF  "$(CFG)" == "HZ - Win32 Release"

!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Target\lua\init.lua

!IF  "$(CFG)" == "HZ - Win32 Release"

!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Target\lua\obj_bse.lua

!IF  "$(CFG)" == "HZ - Win32 Release"

!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Target\lua\obj_tnk.lua

!IF  "$(CFG)" == "HZ - Win32 Release"

!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Target\lua\objects.lua

!IF  "$(CFG)" == "HZ - Win32 Release"

!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Target\lua\sprites.lua

!IF  "$(CFG)" == "HZ - Win32 Release"

!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Target\lua\spritet.lua

!IF  "$(CFG)" == "HZ - Win32 Release"

!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Target\lua\t.lua

!IF  "$(CFG)" == "HZ - Win32 Release"

!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Target\lua\game.lua

!IF  "$(CFG)" == "HZ - Win32 Release"

!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\os_win\i_net.cpp

!IF  "$(CFG)" == "HZ - Win32 Release"


"$(INTDIR)\i_net.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\i_net.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\i_net.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\os_win\i_sound.cpp
DEP_CPP_I_SOU=\
	".\os_win\ddutil.h"\
	".\os_win\dsutil.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	

!IF  "$(CFG)" == "HZ - Win32 Release"


"$(INTDIR)\i_sound.obj" : $(SOURCE) $(DEP_CPP_I_SOU) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\i_sound.obj" : $(SOURCE) $(DEP_CPP_I_SOU) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\i_sound.sbr" : $(SOURCE) $(DEP_CPP_I_SOU) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Target\lua\obj_flg.lua

!IF  "$(CFG)" == "HZ - Win32 Release"

!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Target\lua\visrep.lua

!IF  "$(CFG)" == "HZ - Win32 Release"

!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Target\lua\init_map.lua

!IF  "$(CFG)" == "HZ - Win32 Release"

!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Target\lua\obj_expl.lua

!IF  "$(CFG)" == "HZ - Win32 Release"

!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Target\lua\obj_proj.lua

!IF  "$(CFG)" == "HZ - Win32 Release"

!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Target\lua\traits.lua

!IF  "$(CFG)" == "HZ - Win32 Release"

!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\luabase.cpp

!IF  "$(CFG)" == "HZ - Win32 Release"

DEP_CPP_LUABA=\
	"..\lua31\include\lua.h"\
	".\luabase.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	
NODEP_CPP_LUABA=\
	".\i_sprtet.h"\
	".\i_video.h"\
	".\translate.h"\
	

"$(INTDIR)\luabase.obj" : $(SOURCE) $(DEP_CPP_LUABA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_LUABA=\
	"..\lua31\include\lua.h"\
	".\luabase.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	".\os_win\i_image.h"\
	".\os_win\i_sprtet.h"\
	".\os_win\i_video.h"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	
NODEP_CPP_LUABA=\
	".\translate.h"\
	

"$(INTDIR)\luabase.obj" : $(SOURCE) $(DEP_CPP_LUABA) "$(INTDIR)"

"$(INTDIR)\luabase.sbr" : $(SOURCE) $(DEP_CPP_LUABA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\luabase.h

!IF  "$(CFG)" == "HZ - Win32 Release"

!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
