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

ALL : ".\Release\hz.exe"

CLEAN : 
	-@erase ".\Release\concmd.obj"
	-@erase ".\Release\control.obj"
	-@erase ".\Release\ddutil.obj"
	-@erase ".\Release\donuts.obj"
	-@erase ".\Release\donuts.res"
	-@erase ".\Release\drawhndl.obj"
	-@erase ".\Release\game.obj"
	-@erase ".\Release\hndlmgr.obj"
	-@erase ".\Release\hz.exe"
	-@erase ".\Release\i_draw.obj"
	-@erase ".\Release\i_main.obj"
	-@erase ".\Release\i_net.obj"
	-@erase ".\Release\i_sound.obj"
	-@erase ".\Release\i_sprtet.obj"
	-@erase ".\Release\i_system.obj"
	-@erase ".\Release\i_video.obj"
	-@erase ".\Release\luabase.obj"
	-@erase ".\Release\main.obj"
	-@erase ".\Release\map.obj"
	-@erase ".\Release\misc.obj"
	-@erase ".\Release\net.obj"
	-@erase ".\Release\platform.obj"
	-@erase ".\Release\sound.obj"
	-@erase ".\Release\sprite.obj"
	-@erase ".\Release\spritet.obj"
	-@erase ".\Release\vconsole.obj"
	-@erase ".\Release\view.obj"

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
	".\Release\concmd.obj" \
	".\Release\control.obj" \
	".\Release\ddutil.obj" \
	".\Release\donuts.obj" \
	".\Release\donuts.res" \
	".\Release\drawhndl.obj" \
	".\Release\game.obj" \
	".\Release\hndlmgr.obj" \
	".\Release\i_draw.obj" \
	".\Release\i_main.obj" \
	".\Release\i_net.obj" \
	".\Release\i_sound.obj" \
	".\Release\i_sprtet.obj" \
	".\Release\i_system.obj" \
	".\Release\i_video.obj" \
	".\Release\luabase.obj" \
	".\Release\main.obj" \
	".\Release\map.obj" \
	".\Release\misc.obj" \
	".\Release\net.obj" \
	".\Release\platform.obj" \
	".\Release\sound.obj" \
	".\Release\sprite.obj" \
	".\Release\spritet.obj" \
	".\Release\vconsole.obj" \
	".\Release\view.obj"

".\Release\hz.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

ALL : ".\Target\HZ.exe" ".\Debug\hz.bsc"

CLEAN : 
	-@erase ".\Debug\concmd.obj"
	-@erase ".\Debug\concmd.sbr"
	-@erase ".\Debug\control.obj"
	-@erase ".\Debug\control.sbr"
	-@erase ".\Debug\ddutil.obj"
	-@erase ".\Debug\ddutil.sbr"
	-@erase ".\Debug\donuts.obj"
	-@erase ".\Debug\donuts.sbr"
	-@erase ".\Debug\drawhndl.obj"
	-@erase ".\Debug\drawhndl.sbr"
	-@erase ".\Debug\game.obj"
	-@erase ".\Debug\game.sbr"
	-@erase ".\Debug\hndlmgr.obj"
	-@erase ".\Debug\hndlmgr.sbr"
	-@erase ".\Debug\hz.bsc"
	-@erase ".\Debug\HZ.pdb"
	-@erase ".\Debug\i_draw.obj"
	-@erase ".\Debug\i_draw.sbr"
	-@erase ".\Debug\i_main.obj"
	-@erase ".\Debug\i_main.sbr"
	-@erase ".\Debug\i_net.obj"
	-@erase ".\Debug\i_net.sbr"
	-@erase ".\Debug\i_sound.obj"
	-@erase ".\Debug\i_sound.sbr"
	-@erase ".\Debug\i_sprtet.obj"
	-@erase ".\Debug\i_sprtet.sbr"
	-@erase ".\Debug\i_system.obj"
	-@erase ".\Debug\i_system.sbr"
	-@erase ".\Debug\i_video.obj"
	-@erase ".\Debug\i_video.sbr"
	-@erase ".\Debug\luabase.obj"
	-@erase ".\Debug\luabase.sbr"
	-@erase ".\Debug\main.obj"
	-@erase ".\Debug\main.sbr"
	-@erase ".\Debug\map.obj"
	-@erase ".\Debug\map.sbr"
	-@erase ".\Debug\misc.obj"
	-@erase ".\Debug\misc.sbr"
	-@erase ".\Debug\net.obj"
	-@erase ".\Debug\net.sbr"
	-@erase ".\Debug\platform.obj"
	-@erase ".\Debug\platform.sbr"
	-@erase ".\Debug\sound.obj"
	-@erase ".\Debug\sound.sbr"
	-@erase ".\Debug\sprite.obj"
	-@erase ".\Debug\sprite.sbr"
	-@erase ".\Debug\spritet.obj"
	-@erase ".\Debug\spritet.sbr"
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vconsole.obj"
	-@erase ".\Debug\vconsole.sbr"
	-@erase ".\Debug\view.obj"
	-@erase ".\Debug\view.sbr"
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
	".\Debug\concmd.sbr" \
	".\Debug\control.sbr" \
	".\Debug\ddutil.sbr" \
	".\Debug\donuts.sbr" \
	".\Debug\drawhndl.sbr" \
	".\Debug\game.sbr" \
	".\Debug\hndlmgr.sbr" \
	".\Debug\i_draw.sbr" \
	".\Debug\i_main.sbr" \
	".\Debug\i_net.sbr" \
	".\Debug\i_sound.sbr" \
	".\Debug\i_sprtet.sbr" \
	".\Debug\i_system.sbr" \
	".\Debug\i_video.sbr" \
	".\Debug\luabase.sbr" \
	".\Debug\main.sbr" \
	".\Debug\map.sbr" \
	".\Debug\misc.sbr" \
	".\Debug\net.sbr" \
	".\Debug\platform.sbr" \
	".\Debug\sound.sbr" \
	".\Debug\sprite.sbr" \
	".\Debug\spritet.sbr" \
	".\Debug\vconsole.sbr" \
	".\Debug\view.sbr"

".\Debug\hz.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
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
	".\Debug\concmd.obj" \
	".\Debug\control.obj" \
	".\Debug\ddutil.obj" \
	".\Debug\donuts.obj" \
	".\Debug\drawhndl.obj" \
	".\Debug\game.obj" \
	".\Debug\hndlmgr.obj" \
	".\Debug\i_draw.obj" \
	".\Debug\i_main.obj" \
	".\Debug\i_net.obj" \
	".\Debug\i_sound.obj" \
	".\Debug\i_sprtet.obj" \
	".\Debug\i_system.obj" \
	".\Debug\i_video.obj" \
	".\Debug\luabase.obj" \
	".\Debug\main.obj" \
	".\Debug\map.obj" \
	".\Debug\misc.obj" \
	".\Debug\net.obj" \
	".\Debug\platform.obj" \
	".\Debug\sound.obj" \
	".\Debug\sprite.obj" \
	".\Debug\spritet.obj" \
	".\Debug\vconsole.obj" \
	".\Debug\view.obj" \
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
	".\os_win\..\Donuts.h"\
	".\os_win\..\Main.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\VConsole.h"\
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
	

".\Release\view.obj" : $(SOURCE) $(DEP_CPP_VIEW_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_VIEW_=\
	"..\lua31\include\lua.h"\
	".\luabase.h"\
	".\os_win\..\Donuts.h"\
	".\os_win\..\Main.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\VConsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\osdep.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_VIEW_=\
	".\drawhndl.h"\
	".\dsutil.h"\
	".\hndlmgr.h"\
	".\i_draw.h"\
	".\i_sprtet.h"\
	".\i_system.h"\
	".\i_video.h"\
	".\translate.h"\
	

".\Debug\view.obj" : $(SOURCE) $(DEP_CPP_VIEW_) "$(INTDIR)"

".\Debug\view.sbr" : $(SOURCE) $(DEP_CPP_VIEW_) "$(INTDIR)"


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
	".\os_win\..\Donuts.h"\
	".\os_win\..\Main.h"\
	".\os_win\..\map.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\VConsole.h"\
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
	

".\Release\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_MAIN_=\
	"..\lua31\include\lua.h"\
	".\concmd.h"\
	".\luabase.h"\
	".\os_win\..\Donuts.h"\
	".\os_win\..\Main.h"\
	".\os_win\..\map.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\VConsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_MAIN_=\
	".\drawhndl.h"\
	".\dsutil.h"\
	".\hndlmgr.h"\
	".\i_console.h"\
	".\i_draw.h"\
	".\i_sprtet.h"\
	".\i_system.h"\
	".\i_video.h"\
	".\resource.h"\
	".\translate.h"\
	

".\Debug\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"

".\Debug\main.sbr" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"


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
	".\os_win\..\Donuts.h"\
	".\os_win\..\Game.h"\
	".\os_win\..\Main.h"\
	".\os_win\..\map.h"\
	".\os_win\..\net.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\VConsole.h"\
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
	

".\Release\donuts.obj" : $(SOURCE) $(DEP_CPP_DONUT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_DONUT=\
	"..\lua31\include\lua.h"\
	".\luabase.h"\
	".\misc.h"\
	".\os_win\..\Donuts.h"\
	".\os_win\..\Game.h"\
	".\os_win\..\Main.h"\
	".\os_win\..\map.h"\
	".\os_win\..\net.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\VConsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\osdep.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_DONUT=\
	".\drawhndl.h"\
	".\dsutil.h"\
	".\i_draw.h"\
	".\i_sprtet.h"\
	".\i_system.h"\
	".\i_video.h"\
	".\resource.h"\
	".\translate.h"\
	

".\Debug\donuts.obj" : $(SOURCE) $(DEP_CPP_DONUT) "$(INTDIR)"

".\Debug\donuts.sbr" : $(SOURCE) $(DEP_CPP_DONUT) "$(INTDIR)"


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
	".\os_win\..\Donuts.h"\
	".\os_win\..\Main.h"\
	".\os_win\..\map.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\VConsole.h"\
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
	

".\Release\sprite.obj" : $(SOURCE) $(DEP_CPP_SPRIT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_SPRIT=\
	"..\lua31\include\lua.h"\
	".\luabase.h"\
	".\misc.h"\
	".\os_win\..\Donuts.h"\
	".\os_win\..\Main.h"\
	".\os_win\..\map.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\VConsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_SPRIT=\
	".\drawhndl.h"\
	".\dsutil.h"\
	".\i_sprtet.h"\
	".\i_video.h"\
	".\translate.h"\
	

".\Debug\sprite.obj" : $(SOURCE) $(DEP_CPP_SPRIT) "$(INTDIR)"

".\Debug\sprite.sbr" : $(SOURCE) $(DEP_CPP_SPRIT) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\misc.cpp
DEP_CPP_MISC_=\
	".\misc.h"\
	".\os_win\..\Main.h"\
	".\os_win\..\VConsole.h"\
	".\os_win\..\View.h"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	
NODEP_CPP_MISC_=\
	".\i_sprtet.h"\
	".\i_video.h"\
	".\translate.h"\
	

!IF  "$(CFG)" == "HZ - Win32 Release"


".\Release\misc.obj" : $(SOURCE) $(DEP_CPP_MISC_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"


".\Debug\misc.obj" : $(SOURCE) $(DEP_CPP_MISC_) "$(INTDIR)"

".\Debug\misc.sbr" : $(SOURCE) $(DEP_CPP_MISC_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\sound.cpp

!IF  "$(CFG)" == "HZ - Win32 Release"


".\Release\sound.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"


".\Debug\sound.obj" : $(SOURCE) "$(INTDIR)"

".\Debug\sound.sbr" : $(SOURCE) "$(INTDIR)"


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
	".\os_win\..\Donuts.h"\
	".\os_win\..\Game.h"\
	".\os_win\..\Main.h"\
	".\os_win\..\map.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\VConsole.h"\
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
	

".\Release\game.obj" : $(SOURCE) $(DEP_CPP_GAME_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_GAME_=\
	"..\lua31\include\lua.h"\
	"..\lua31\include\luadebug.h"\
	"..\lua31\include\lualib.h"\
	".\luabase.h"\
	".\os_win\..\Donuts.h"\
	".\os_win\..\Game.h"\
	".\os_win\..\Main.h"\
	".\os_win\..\map.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\VConsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_GAME_=\
	".\dsutil.h"\
	".\i_console.h"\
	".\i_sprtet.h"\
	".\i_system.h"\
	".\i_video.h"\
	".\translate.h"\
	

".\Debug\game.obj" : $(SOURCE) $(DEP_CPP_GAME_) "$(INTDIR)"

".\Debug\game.sbr" : $(SOURCE) $(DEP_CPP_GAME_) "$(INTDIR)"


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
	".\os_win\..\Donuts.h"\
	".\os_win\..\Game.h"\
	".\os_win\..\Main.h"\
	".\os_win\..\map.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\VConsole.h"\
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
	

".\Release\map.obj" : $(SOURCE) $(DEP_CPP_MAP_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_MAP_C=\
	"..\lua31\include\lua.h"\
	".\luabase.h"\
	".\os_win\..\Donuts.h"\
	".\os_win\..\Game.h"\
	".\os_win\..\Main.h"\
	".\os_win\..\map.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\VConsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\osdep.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_MAP_C=\
	".\drawhndl.h"\
	".\dsutil.h"\
	".\i_draw.h"\
	".\i_sprtet.h"\
	".\i_system.h"\
	".\i_video.h"\
	".\translate.h"\
	

".\Debug\map.obj" : $(SOURCE) $(DEP_CPP_MAP_C) "$(INTDIR)"

".\Debug\map.sbr" : $(SOURCE) $(DEP_CPP_MAP_C) "$(INTDIR)"


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
	".\os_win\..\Donuts.h"\
	".\os_win\..\Main.h"\
	".\os_win\..\map.h"\
	".\os_win\..\net.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\VConsole.h"\
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
	

".\Release\net.obj" : $(SOURCE) $(DEP_CPP_NET_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_NET_C=\
	"..\lua31\include\lua.h"\
	".\luabase.h"\
	".\os_win\..\Donuts.h"\
	".\os_win\..\Main.h"\
	".\os_win\..\map.h"\
	".\os_win\..\net.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\VConsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dplay.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_NET_C=\
	".\dsutil.h"\
	".\i_sprtet.h"\
	".\i_video.h"\
	".\translate.h"\
	

".\Debug\net.obj" : $(SOURCE) $(DEP_CPP_NET_C) "$(INTDIR)"

".\Debug\net.sbr" : $(SOURCE) $(DEP_CPP_NET_C) "$(INTDIR)"


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
	".\os_win\..\Main.h"\
	".\os_win\..\map.h"\
	".\os_win\..\net.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\VConsole.h"\
	".\os_win\..\View.h"\
	".\sprite.h"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	
NODEP_CPP_CONCM=\
	".\i_video.h"\
	".\translate.h"\
	

".\Release\concmd.obj" : $(SOURCE) $(DEP_CPP_CONCM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_CONCM=\
	"..\lua31\include\lua.h"\
	".\concmd.h"\
	".\luabase.h"\
	".\os_win\..\Main.h"\
	".\os_win\..\map.h"\
	".\os_win\..\net.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\VConsole.h"\
	".\os_win\..\View.h"\
	".\sprite.h"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	
NODEP_CPP_CONCM=\
	".\i_sprtet.h"\
	".\i_video.h"\
	".\translate.h"\
	

".\Debug\concmd.obj" : $(SOURCE) $(DEP_CPP_CONCM) "$(INTDIR)"

".\Debug\concmd.sbr" : $(SOURCE) $(DEP_CPP_CONCM) "$(INTDIR)"


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
	".\os_win\..\Donuts.h"\
	".\os_win\..\Main.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\VConsole.h"\
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
	

".\Release\spritet.obj" : $(SOURCE) $(DEP_CPP_SPRITE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_SPRITE=\
	"..\lua31\include\lua.h"\
	".\luabase.h"\
	".\os_win\..\Donuts.h"\
	".\os_win\..\Main.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\VConsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_SPRITE=\
	".\drawhndl.h"\
	".\dsutil.h"\
	".\i_draw.h"\
	".\i_sprtet.h"\
	".\i_video.h"\
	".\translate.h"\
	

".\Debug\spritet.obj" : $(SOURCE) $(DEP_CPP_SPRITE) "$(INTDIR)"

".\Debug\spritet.sbr" : $(SOURCE) $(DEP_CPP_SPRITE) "$(INTDIR)"


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
	".\os_win\..\Donuts.h"\
	".\os_win\..\Main.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\VConsole.h"\
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
	

".\Release\vconsole.obj" : $(SOURCE) $(DEP_CPP_VCONS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_VCONS=\
	"..\lua31\include\lua.h"\
	".\luabase.h"\
	".\os_win\..\Donuts.h"\
	".\os_win\..\Main.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\VConsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\osdep.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_VCONS=\
	".\drawhndl.h"\
	".\dsutil.h"\
	".\hndlmgr.h"\
	".\i_sprtet.h"\
	".\i_system.h"\
	".\i_video.h"\
	".\translate.h"\
	

".\Debug\vconsole.obj" : $(SOURCE) $(DEP_CPP_VCONS) "$(INTDIR)"

".\Debug\vconsole.sbr" : $(SOURCE) $(DEP_CPP_VCONS) "$(INTDIR)"


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


".\Release\donuts.res" : $(SOURCE) $(DEP_RSC_DONUTS) "$(INTDIR)"
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


".\Release\control.obj" : $(SOURCE) $(DEP_CPP_CONTR) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

".\Debug\control.obj" : $(SOURCE) $(DEP_CPP_CONTR) "$(INTDIR)"
   $(BuildCmds)

".\Debug\control.sbr" : $(SOURCE) $(DEP_CPP_CONTR) "$(INTDIR)"
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


".\Release\ddutil.obj" : $(SOURCE) $(DEP_CPP_DDUTI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

".\Debug\ddutil.obj" : $(SOURCE) $(DEP_CPP_DDUTI) "$(INTDIR)"
   $(BuildCmds)

".\Debug\ddutil.sbr" : $(SOURCE) $(DEP_CPP_DDUTI) "$(INTDIR)"
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
	".\os_win\..\Donuts.h"\
	".\os_win\..\Main.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\VConsole.h"\
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
	

".\Release\drawhndl.obj" : $(SOURCE) $(DEP_CPP_DRAWH) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_DRAWH=\
	"..\lua31\include\lua.h"\
	".\luabase.h"\
	".\os_win\..\Donuts.h"\
	".\os_win\..\Main.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\VConsole.h"\
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
	".\dsutil.h"\
	".\i_sprtet.h"\
	".\i_video.h"\
	".\translate.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

".\Debug\drawhndl.obj" : $(SOURCE) $(DEP_CPP_DRAWH) "$(INTDIR)"
   $(BuildCmds)

".\Debug\drawhndl.sbr" : $(SOURCE) $(DEP_CPP_DRAWH) "$(INTDIR)"
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
	".\os_win\..\Donuts.h"\
	".\os_win\..\Game.h"\
	".\os_win\..\Main.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\VConsole.h"\
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
	

".\Release\platform.obj" : $(SOURCE) $(DEP_CPP_PLATF) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_PLATF=\
	"..\lua31\include\lua.h"\
	".\luabase.h"\
	".\os_win\..\Donuts.h"\
	".\os_win\..\Game.h"\
	".\os_win\..\Main.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\VConsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\os_win\i_system.h"\
	".\sprite.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	
NODEP_CPP_PLATF=\
	".\dsutil.h"\
	".\i_sprtet.h"\
	".\i_video.h"\
	".\translate.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

".\Debug\platform.obj" : $(SOURCE) $(DEP_CPP_PLATF) "$(INTDIR)"
   $(BuildCmds)

".\Debug\platform.sbr" : $(SOURCE) $(DEP_CPP_PLATF) "$(INTDIR)"
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


".\Release\hndlmgr.obj" : $(SOURCE) $(DEP_CPP_HNDLM) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

".\Debug\hndlmgr.obj" : $(SOURCE) $(DEP_CPP_HNDLM) "$(INTDIR)"
   $(BuildCmds)

".\Debug\hndlmgr.sbr" : $(SOURCE) $(DEP_CPP_HNDLM) "$(INTDIR)"
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
	".\os_win\..\Donuts.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\VConsole.h"\
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
	

".\Release\i_sprtet.obj" : $(SOURCE) $(DEP_CPP_I_SPR) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_I_SPR=\
	"..\lua31\include\lua.h"\
	".\luabase.h"\
	".\os_win\..\Donuts.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\VConsole.h"\
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
	".\dsutil.h"\
	".\i_sprtet.h"\
	".\i_video.h"\
	".\translate.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

".\Debug\i_sprtet.obj" : $(SOURCE) $(DEP_CPP_I_SPR) "$(INTDIR)"
   $(BuildCmds)

".\Debug\i_sprtet.sbr" : $(SOURCE) $(DEP_CPP_I_SPR) "$(INTDIR)"
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
	".\os_win\..\Donuts.h"\
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
	

".\Release\i_draw.obj" : $(SOURCE) $(DEP_CPP_I_DRA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_I_DRA=\
	"..\lua31\include\lua.h"\
	".\luabase.h"\
	".\os_win\..\Donuts.h"\
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
	".\dsutil.h"\
	".\i_sprtet.h"\
	".\translate.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

".\Debug\i_draw.obj" : $(SOURCE) $(DEP_CPP_I_DRA) "$(INTDIR)"
   $(BuildCmds)

".\Debug\i_draw.sbr" : $(SOURCE) $(DEP_CPP_I_DRA) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\os_win\i_video.cpp

!IF  "$(CFG)" == "HZ - Win32 Release"

DEP_CPP_I_VID=\
	".\dsutil.h"\
	".\i_sprtet.h"\
	".\luabase.h"\
	".\os_win\..\Donuts.h"\
	".\os_win\..\map.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\VConsole.h"\
	".\os_win\..\View.h"\
	".\os_win\ddutil.h"\
	".\os_win\drawhndl.h"\
	".\os_win\hndlmgr.h"\
	".\os_win\i_image.h"\
	".\os_win\i_sprtet.h"\
	".\os_win\i_system.h"\
	".\os_win\i_video.h"\
	".\sprite.h"\
	
NODEP_CPP_I_VID=\
	".\translate.h"\
	

".\Release\i_video.obj" : $(SOURCE) $(DEP_CPP_I_VID) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_I_VID=\
	"..\lua31\include\lua.h"\
	".\luabase.h"\
	".\os_win\..\Donuts.h"\
	".\os_win\..\map.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\VConsole.h"\
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
	

".\Debug\i_video.obj" : $(SOURCE) $(DEP_CPP_I_VID) "$(INTDIR)"
   $(BuildCmds)

".\Debug\i_video.sbr" : $(SOURCE) $(DEP_CPP_I_VID) "$(INTDIR)"
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
	".\os_win\..\Donuts.h"\
	".\os_win\..\Main.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\VConsole.h"\
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
	

".\Release\i_system.obj" : $(SOURCE) $(DEP_CPP_I_SYS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_I_SYS=\
	"..\lua31\include\lua.h"\
	".\luabase.h"\
	".\os_win\..\Donuts.h"\
	".\os_win\..\Main.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\VConsole.h"\
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
	".\dsutil.h"\
	".\i_sprtet.h"\
	".\i_video.h"\
	".\translate.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

".\Debug\i_system.obj" : $(SOURCE) $(DEP_CPP_I_SYS) "$(INTDIR)"
   $(BuildCmds)

".\Debug\i_system.sbr" : $(SOURCE) $(DEP_CPP_I_SYS) "$(INTDIR)"
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
	".\os_win\..\Donuts.h"\
	".\os_win\..\Main.h"\
	".\os_win\..\map.h"\
	".\os_win\..\net.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\VConsole.h"\
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
	

".\Release\i_main.obj" : $(SOURCE) $(DEP_CPP_I_MAI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_I_MAI=\
	"..\lua31\include\lua.h"\
	".\luabase.h"\
	".\os_win\..\Donuts.h"\
	".\os_win\..\Main.h"\
	".\os_win\..\map.h"\
	".\os_win\..\net.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\VConsole.h"\
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
	".\dsutil.h"\
	".\i_sprtet.h"\
	".\i_video.h"\
	".\translate.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

".\Debug\i_main.obj" : $(SOURCE) $(DEP_CPP_I_MAI) "$(INTDIR)"
   $(BuildCmds)

".\Debug\i_main.sbr" : $(SOURCE) $(DEP_CPP_I_MAI) "$(INTDIR)"
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


".\Release\i_net.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

".\Debug\i_net.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

".\Debug\i_net.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\os_win\i_sound.cpp

!IF  "$(CFG)" == "HZ - Win32 Release"

DEP_CPP_I_SOU=\
	".\os_win\ddutil.h"\
	".\os_win\dsutil.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	

".\Release\i_sound.obj" : $(SOURCE) $(DEP_CPP_I_SOU) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_I_SOU=\
	".\os_win\ddutil.h"\
	".\os_win\dsutil.h"\
	"C:\dx7asdk\DXF\include\d3dtypes.h"\
	"C:\dx7asdk\DXF\include\d3dvec.inl"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	"c:\dx7asdk\dxf\include\dsound.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

".\Debug\i_sound.obj" : $(SOURCE) $(DEP_CPP_I_SOU) "$(INTDIR)"
   $(BuildCmds)

".\Debug\i_sound.sbr" : $(SOURCE) $(DEP_CPP_I_SOU) "$(INTDIR)"
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
	".\os_win\..\VConsole.h"\
	".\os_win\..\View.h"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	
NODEP_CPP_LUABA=\
	".\i_sprtet.h"\
	".\i_video.h"\
	".\translate.h"\
	

".\Release\luabase.obj" : $(SOURCE) $(DEP_CPP_LUABA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_LUABA=\
	"..\lua31\include\lua.h"\
	".\luabase.h"\
	".\os_win\..\VConsole.h"\
	".\os_win\..\View.h"\
	"c:\dx7asdk\dxf\include\ddraw.h"\
	
NODEP_CPP_LUABA=\
	".\i_sprtet.h"\
	".\i_video.h"\
	".\translate.h"\
	

".\Debug\luabase.obj" : $(SOURCE) $(DEP_CPP_LUABA) "$(INTDIR)"

".\Debug\luabase.sbr" : $(SOURCE) $(DEP_CPP_LUABA) "$(INTDIR)"


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
