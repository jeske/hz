# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
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
CPP=cl.exe
RSC=rc.exe
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
	-@erase ".\Release\hz.exe"
	-@erase ".\Release\net.obj"
	-@erase ".\Release\i_system.obj"
	-@erase ".\Release\sprite.obj"
	-@erase ".\Release\map.obj"
	-@erase ".\Release\luabase.obj"
	-@erase ".\Release\control.obj"
	-@erase ".\Release\drawhndl.obj"
	-@erase ".\Release\i_net.obj"
	-@erase ".\Release\i_video.obj"
	-@erase ".\Release\concmd.obj"
	-@erase ".\Release\spritet.obj"
	-@erase ".\Release\view.obj"
	-@erase ".\Release\game.obj"
	-@erase ".\Release\hndlmgr.obj"
	-@erase ".\Release\misc.obj"
	-@erase ".\Release\i_sound.obj"
	-@erase ".\Release\i_sprtet.obj"
	-@erase ".\Release\i_draw.obj"
	-@erase ".\Release\ddutil.obj"
	-@erase ".\Release\i_main.obj"
	-@erase ".\Release\platform.obj"
	-@erase ".\Release\vconsole.obj"
	-@erase ".\Release\donuts.obj"
	-@erase ".\Release\sound.obj"
	-@erase ".\Release\main.obj"
	-@erase ".\Release\donuts.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "OS_WIN" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "OS_WIN" /Fp"$(INTDIR)/hz.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
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
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 lua.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /nodefaultlib
LINK32_FLAGS=lua.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)/hz.pdb" /machine:I386\
 /out:"$(OUTDIR)/hz.exe" 
LINK32_OBJS= \
	"$(INTDIR)/net.obj" \
	"$(INTDIR)/i_system.obj" \
	"$(INTDIR)/sprite.obj" \
	"$(INTDIR)/map.obj" \
	"$(INTDIR)/luabase.obj" \
	"$(INTDIR)/control.obj" \
	"$(INTDIR)/drawhndl.obj" \
	"$(INTDIR)/i_net.obj" \
	"$(INTDIR)/i_video.obj" \
	"$(INTDIR)/concmd.obj" \
	"$(INTDIR)/spritet.obj" \
	"$(INTDIR)/view.obj" \
	"$(INTDIR)/game.obj" \
	"$(INTDIR)/hndlmgr.obj" \
	"$(INTDIR)/misc.obj" \
	"$(INTDIR)/i_sound.obj" \
	"$(INTDIR)/i_sprtet.obj" \
	"$(INTDIR)/i_draw.obj" \
	"$(INTDIR)/ddutil.obj" \
	"$(INTDIR)/i_main.obj" \
	"$(INTDIR)/platform.obj" \
	"$(INTDIR)/vconsole.obj" \
	"$(INTDIR)/donuts.obj" \
	"$(INTDIR)/sound.obj" \
	"$(INTDIR)/main.obj" \
	"$(INTDIR)/donuts.res"

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

ALL : "$(OUTDIR)\HZ.exe" ".\Debug\hz.bsc"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\hz.bsc"
	-@erase ".\Debug\main.sbr"
	-@erase ".\Debug\drawhndl.sbr"
	-@erase ".\Debug\donuts.sbr"
	-@erase ".\Debug\view.sbr"
	-@erase ".\Debug\game.sbr"
	-@erase ".\Debug\i_sound.sbr"
	-@erase ".\Debug\misc.sbr"
	-@erase ".\Debug\i_sprtet.sbr"
	-@erase ".\Debug\luabase.sbr"
	-@erase ".\Debug\vconsole.sbr"
	-@erase ".\Debug\sound.sbr"
	-@erase ".\Debug\sprite.sbr"
	-@erase ".\Debug\hndlmgr.sbr"
	-@erase ".\Debug\concmd.sbr"
	-@erase ".\Debug\map.sbr"
	-@erase ".\Debug\platform.sbr"
	-@erase ".\Debug\i_net.sbr"
	-@erase ".\Debug\i_system.sbr"
	-@erase ".\Debug\i_draw.sbr"
	-@erase ".\Debug\control.sbr"
	-@erase ".\Debug\ddutil.sbr"
	-@erase ".\Debug\i_main.sbr"
	-@erase ".\Debug\i_video.sbr"
	-@erase ".\Debug\net.sbr"
	-@erase ".\Debug\spritet.sbr"
	-@erase ".\Target\HZ.exe"
	-@erase ".\Debug\i_net.obj"
	-@erase ".\Debug\i_system.obj"
	-@erase ".\Debug\i_draw.obj"
	-@erase ".\Debug\control.obj"
	-@erase ".\Debug\ddutil.obj"
	-@erase ".\Debug\i_main.obj"
	-@erase ".\Debug\i_video.obj"
	-@erase ".\Debug\net.obj"
	-@erase ".\Debug\spritet.obj"
	-@erase ".\Debug\main.obj"
	-@erase ".\Debug\drawhndl.obj"
	-@erase ".\Debug\donuts.obj"
	-@erase ".\Debug\view.obj"
	-@erase ".\Debug\game.obj"
	-@erase ".\Debug\i_sound.obj"
	-@erase ".\Debug\misc.obj"
	-@erase ".\Debug\i_sprtet.obj"
	-@erase ".\Debug\luabase.obj"
	-@erase ".\Debug\vconsole.obj"
	-@erase ".\Debug\sound.obj"
	-@erase ".\Debug\sprite.obj"
	-@erase ".\Debug\hndlmgr.obj"
	-@erase ".\Debug\concmd.obj"
	-@erase ".\Debug\map.obj"
	-@erase ".\Debug\platform.obj"
	-@erase ".\hz.res"
	-@erase ".\Target\HZ.ilk"
	-@erase ".\Debug\HZ.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /W3 /GX /Zi /Od /I "c:\dxsdk\sdk\inc" /D "_DEBUG" /D "LUA_COMPAT2_5" /D "WIN32" /D "_WINDOWS" /D "OS_WIN" /U "USE_DSOUND" /FR /YX /c
# SUBTRACT CPP /X
CPP_PROJ=/nologo /MTd /W3 /GX /Zi /Od /I "c:\dxsdk\sdk\inc" /D "_DEBUG" /D\
 "LUA_COMPAT2_5" /D "WIN32" /D "_WINDOWS" /D "OS_WIN" /U "USE_DSOUND"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/hz.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
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
	"$(INTDIR)/main.sbr" \
	"$(INTDIR)/drawhndl.sbr" \
	"$(INTDIR)/donuts.sbr" \
	"$(INTDIR)/view.sbr" \
	"$(INTDIR)/game.sbr" \
	"$(INTDIR)/i_sound.sbr" \
	"$(INTDIR)/misc.sbr" \
	"$(INTDIR)/i_sprtet.sbr" \
	"$(INTDIR)/luabase.sbr" \
	"$(INTDIR)/vconsole.sbr" \
	"$(INTDIR)/sound.sbr" \
	"$(INTDIR)/sprite.sbr" \
	"$(INTDIR)/hndlmgr.sbr" \
	"$(INTDIR)/concmd.sbr" \
	"$(INTDIR)/map.sbr" \
	"$(INTDIR)/platform.sbr" \
	"$(INTDIR)/i_net.sbr" \
	"$(INTDIR)/i_system.sbr" \
	"$(INTDIR)/i_draw.sbr" \
	"$(INTDIR)/control.sbr" \
	"$(INTDIR)/ddutil.sbr" \
	"$(INTDIR)/i_main.sbr" \
	"$(INTDIR)/i_video.sbr" \
	"$(INTDIR)/net.sbr" \
	"$(INTDIR)/spritet.sbr"

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
	"$(INTDIR)/i_net.obj" \
	"$(INTDIR)/i_system.obj" \
	"$(INTDIR)/i_draw.obj" \
	"$(INTDIR)/control.obj" \
	"$(INTDIR)/ddutil.obj" \
	"$(INTDIR)/i_main.obj" \
	"$(INTDIR)/i_video.obj" \
	"$(INTDIR)/net.obj" \
	"$(INTDIR)/spritet.obj" \
	"$(INTDIR)/main.obj" \
	"$(INTDIR)/drawhndl.obj" \
	"$(INTDIR)/donuts.obj" \
	"$(INTDIR)/view.obj" \
	"$(INTDIR)/game.obj" \
	"$(INTDIR)/i_sound.obj" \
	"$(INTDIR)/misc.obj" \
	"$(INTDIR)/i_sprtet.obj" \
	"$(INTDIR)/luabase.obj" \
	"$(INTDIR)/vconsole.obj" \
	"$(INTDIR)/sound.obj" \
	"$(INTDIR)/sprite.obj" \
	"$(INTDIR)/hndlmgr.obj" \
	"$(INTDIR)/concmd.obj" \
	"$(INTDIR)/map.obj" \
	"$(INTDIR)/platform.obj" \
	".\hz.res"

"$(OUTDIR)\HZ.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
DEP_CPP_VIEW_=\
	{$(INCLUDE)}"\lua.h"\
	{$(INCLUDE)}"\drawhndl.h"\
	{$(INCLUDE)}"\hndlmgr.h"\
	{$(INCLUDE)}"\i_video.h"\
	{$(INCLUDE)}"\i_draw.h"\
	{$(INCLUDE)}"\i_system.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\View.h"\
	".\os_win\..\main.h"\
	".\osdep.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\i_sprtet.h"\
	{$(INCLUDE)}"\i_image.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\os_win\ddutil.h"\
	{$(INCLUDE)}"\dsutil.h"\
	".\sprite.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\d3dvec.inl"\
	".\luabase.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\vconsole.h"\
	
NODEP_CPP_VIEW_=\
	".\translate.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\subwtype.h"\
	

!IF  "$(CFG)" == "HZ - Win32 Release"


"$(INTDIR)\view.obj" : $(SOURCE) $(DEP_CPP_VIEW_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"


"$(INTDIR)\view.obj" : $(SOURCE) $(DEP_CPP_VIEW_) "$(INTDIR)"

"$(INTDIR)\view.sbr" : $(SOURCE) $(DEP_CPP_VIEW_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\main.cpp
DEP_CPP_MAIN_=\
	{$(INCLUDE)}"\drawhndl.h"\
	{$(INCLUDE)}"\hndlmgr.h"\
	{$(INCLUDE)}"\i_system.h"\
	{$(INCLUDE)}"\i_video.h"\
	{$(INCLUDE)}"\i_draw.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\View.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\map.h"\
	".\concmd.h"\
	".\os_win\..\main.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\i_sprtet.h"\
	{$(INCLUDE)}"\i_image.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\os_win\ddutil.h"\
	{$(INCLUDE)}"\dsutil.h"\
	".\sprite.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\d3dvec.inl"\
	{$(INCLUDE)}"\lua.h"\
	".\luabase.h"\
	".\os_win\..\spritet.h"\
	
NODEP_CPP_MAIN_=\
	".\i_console.h"\
	".\translate.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\subwtype.h"\
	

!IF  "$(CFG)" == "HZ - Win32 Release"


"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"


"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"

"$(INTDIR)\main.sbr" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\donuts.cpp
DEP_CPP_DONUT=\
	{$(INCLUDE)}"\drawhndl.h"\
	{$(INCLUDE)}"\i_draw.h"\
	{$(INCLUDE)}"\i_video.h"\
	{$(INCLUDE)}"\i_system.h"\
	".\os_win\..\main.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\View.h"\
	".\sprite.h"\
	".\os_win\..\spritet.h"\
	".\misc.h"\
	".\os_win\..\Game.h"\
	".\os_win\..\map.h"\
	".\os_win\..\net.h"\
	{$(INCLUDE)}"\i_sprtet.h"\
	{$(INCLUDE)}"\i_image.h"\
	{$(INCLUDE)}"\ddraw.h"\
	".\os_win\..\vconsole.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\os_win\ddutil.h"\
	{$(INCLUDE)}"\dsutil.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\d3dvec.inl"\
	{$(INCLUDE)}"\lua.h"\
	".\luabase.h"\
	
NODEP_CPP_DONUT=\
	".\translate.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\subwtype.h"\
	

!IF  "$(CFG)" == "HZ - Win32 Release"


"$(INTDIR)\donuts.obj" : $(SOURCE) $(DEP_CPP_DONUT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"


"$(INTDIR)\donuts.obj" : $(SOURCE) $(DEP_CPP_DONUT) "$(INTDIR)"

"$(INTDIR)\donuts.sbr" : $(SOURCE) $(DEP_CPP_DONUT) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\sprite.cpp
DEP_CPP_SPRIT=\
	{$(INCLUDE)}"\lua.h"\
	{$(INCLUDE)}"\drawhndl.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\main.h"\
	".\misc.h"\
	".\os_win\..\map.h"\
	".\sprite.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\os_win\ddutil.h"\
	{$(INCLUDE)}"\dsutil.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\d3dvec.inl"\
	".\os_win\..\View.h"\
	".\os_win\..\vconsole.h"\
	{$(INCLUDE)}"\i_video.h"\
	{$(INCLUDE)}"\i_sprtet.h"\
	{$(INCLUDE)}"\i_image.h"\
	".\luabase.h"\
	".\os_win\..\spritet.h"\
	
NODEP_CPP_SPRIT=\
	".\translate.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\subwtype.h"\
	

!IF  "$(CFG)" == "HZ - Win32 Release"


"$(INTDIR)\sprite.obj" : $(SOURCE) $(DEP_CPP_SPRIT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"


"$(INTDIR)\sprite.obj" : $(SOURCE) $(DEP_CPP_SPRIT) "$(INTDIR)"

"$(INTDIR)\sprite.sbr" : $(SOURCE) $(DEP_CPP_SPRIT) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\misc.cpp
DEP_CPP_MISC_=\
	".\os_win\..\View.h"\
	".\os_win\..\main.h"\
	".\misc.h"\
	{$(INCLUDE)}"\ddraw.h"\
	".\os_win\..\vconsole.h"\
	
NODEP_CPP_MISC_=\
	".\translate.h"\
	

!IF  "$(CFG)" == "HZ - Win32 Release"


"$(INTDIR)\misc.obj" : $(SOURCE) $(DEP_CPP_MISC_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"


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
DEP_CPP_GAME_=\
	{$(INCLUDE)}"\lua.h"\
	{$(INCLUDE)}"\lualib.h"\
	{$(INCLUDE)}"\luadebug.h"\
	{$(INCLUDE)}"\i_system.h"\
	{$(INCLUDE)}"\i_video.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\map.h"\
	".\sprite.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\View.h"\
	".\os_win\..\main.h"\
	".\os_win\..\Game.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\i_sprtet.h"\
	{$(INCLUDE)}"\i_image.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\os_win\ddutil.h"\
	{$(INCLUDE)}"\dsutil.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\d3dvec.inl"\
	".\luabase.h"\
	".\os_win\..\vconsole.h"\
	
NODEP_CPP_GAME_=\
	".\i_console.h"\
	".\translate.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\subwtype.h"\
	

!IF  "$(CFG)" == "HZ - Win32 Release"


"$(INTDIR)\game.obj" : $(SOURCE) $(DEP_CPP_GAME_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"


"$(INTDIR)\game.obj" : $(SOURCE) $(DEP_CPP_GAME_) "$(INTDIR)"

"$(INTDIR)\game.sbr" : $(SOURCE) $(DEP_CPP_GAME_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\map.cpp
DEP_CPP_MAP_C=\
	{$(INCLUDE)}"\drawhndl.h"\
	{$(INCLUDE)}"\i_system.h"\
	{$(INCLUDE)}"\i_draw.h"\
	{$(INCLUDE)}"\i_video.h"\
	".\os_win\..\donuts.h"\
	".\sprite.h"\
	".\os_win\..\main.h"\
	".\os_win\..\Game.h"\
	".\os_win\..\map.h"\
	{$(INCLUDE)}"\i_sprtet.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\os_win\ddutil.h"\
	{$(INCLUDE)}"\dsutil.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\d3dvec.inl"\
	{$(INCLUDE)}"\lua.h"\
	".\luabase.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\View.h"\
	".\os_win\..\vconsole.h"\
	
NODEP_CPP_MAP_C=\
	".\translate.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\subwtype.h"\
	

!IF  "$(CFG)" == "HZ - Win32 Release"


"$(INTDIR)\map.obj" : $(SOURCE) $(DEP_CPP_MAP_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"


"$(INTDIR)\map.obj" : $(SOURCE) $(DEP_CPP_MAP_C) "$(INTDIR)"

"$(INTDIR)\map.sbr" : $(SOURCE) $(DEP_CPP_MAP_C) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\net.cpp
DEP_CPP_NET_C=\
	{$(INCLUDE)}"\dplay.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\main.h"\
	".\os_win\..\map.h"\
	".\os_win\..\net.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\os_win\ddutil.h"\
	{$(INCLUDE)}"\dsutil.h"\
	".\sprite.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\d3dvec.inl"\
	{$(INCLUDE)}"\lua.h"\
	".\luabase.h"\
	".\os_win\..\spritet.h"\
	{$(INCLUDE)}"\i_sprtet.h"\
	".\os_win\..\View.h"\
	".\os_win\..\vconsole.h"\
	
NODEP_CPP_NET_C=\
	".\translate.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\subwtype.h"\
	

!IF  "$(CFG)" == "HZ - Win32 Release"


"$(INTDIR)\net.obj" : $(SOURCE) $(DEP_CPP_NET_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"


"$(INTDIR)\net.obj" : $(SOURCE) $(DEP_CPP_NET_C) "$(INTDIR)"

"$(INTDIR)\net.sbr" : $(SOURCE) $(DEP_CPP_NET_C) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\concmd.cpp
DEP_CPP_CONCM=\
	{$(INCLUDE)}"\lua.h"\
	".\os_win\..\main.h"\
	".\os_win\..\net.h"\
	".\os_win\..\View.h"\
	".\concmd.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\map.h"\
	".\sprite.h"\
	{$(INCLUDE)}"\ddraw.h"\
	".\luabase.h"\
	".\os_win\..\spritet.h"\
	{$(INCLUDE)}"\i_sprtet.h"\
	
NODEP_CPP_CONCM=\
	".\translate.h"\
	

!IF  "$(CFG)" == "HZ - Win32 Release"


"$(INTDIR)\concmd.obj" : $(SOURCE) $(DEP_CPP_CONCM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"


"$(INTDIR)\concmd.obj" : $(SOURCE) $(DEP_CPP_CONCM) "$(INTDIR)"

"$(INTDIR)\concmd.sbr" : $(SOURCE) $(DEP_CPP_CONCM) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\spritet.cpp
DEP_CPP_SPRITE=\
	{$(INCLUDE)}"\lua.h"\
	{$(INCLUDE)}"\drawhndl.h"\
	{$(INCLUDE)}"\i_draw.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\View.h"\
	".\os_win\..\main.h"\
	".\os_win\..\spritet.h"\
	{$(INCLUDE)}"\i_sprtet.h"\
	{$(INCLUDE)}"\i_image.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\os_win\ddutil.h"\
	{$(INCLUDE)}"\dsutil.h"\
	".\sprite.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\d3dvec.inl"\
	".\luabase.h"\
	{$(INCLUDE)}"\i_video.h"\
	".\os_win\..\vconsole.h"\
	
NODEP_CPP_SPRITE=\
	".\translate.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\subwtype.h"\
	

!IF  "$(CFG)" == "HZ - Win32 Release"


"$(INTDIR)\spritet.obj" : $(SOURCE) $(DEP_CPP_SPRITE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"


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
	{$(INCLUDE)}"\lua.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\drawhndl.h"\
	{$(INCLUDE)}"\hndlmgr.h"\
	{$(INCLUDE)}"\i_system.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\View.h"\
	".\os_win\..\main.h"\
	".\os_win\..\vconsole.h"\
	{$(INCLUDE)}"\i_video.h"\
	".\osdep.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\os_win\ddutil.h"\
	{$(INCLUDE)}"\dsutil.h"\
	".\sprite.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\d3dvec.inl"\
	".\luabase.h"\
	".\os_win\..\spritet.h"\
	{$(INCLUDE)}"\i_sprtet.h"\
	{$(INCLUDE)}"\i_image.h"\
	
NODEP_CPP_VCONS=\
	".\translate.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\subwtype.h"\
	

"$(INTDIR)\vconsole.obj" : $(SOURCE) $(DEP_CPP_VCONS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_VCONS=\
	{$(INCLUDE)}"\lua.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\drawhndl.h"\
	{$(INCLUDE)}"\hndlmgr.h"\
	{$(INCLUDE)}"\i_system.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\View.h"\
	".\os_win\..\main.h"\
	".\os_win\..\vconsole.h"\
	{$(INCLUDE)}"\i_video.h"\
	".\osdep.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\os_win\ddutil.h"\
	{$(INCLUDE)}"\dsutil.h"\
	".\sprite.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\d3dvec.inl"\
	".\luabase.h"\
	".\os_win\..\spritet.h"\
	{$(INCLUDE)}"\i_sprtet.h"\
	{$(INCLUDE)}"\i_image.h"\
	
NODEP_CPP_VCONS=\
	".\translate.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\subwtype.h"\
	".\}"\
	

"$(INTDIR)\vconsole.obj" : $(SOURCE) $(DEP_CPP_VCONS) "$(INTDIR)"

"$(INTDIR)\vconsole.sbr" : $(SOURCE) $(DEP_CPP_VCONS) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\os_win\donuts.rc
DEP_RSC_DONUTS=\
	".\os_win\..\_old\Splash.bmp"\
	".\os_win\..\_old\donuts.bmp"\
	".\os_win\..\_old\level.wav"\
	".\os_win\..\_old\hum.wav"\
	".\os_win\..\_old\rev.wav"\
	".\os_win\..\_old\skid.wav"\
	".\os_win\..\_old\shield.wav"\
	".\os_win\..\_old\gunfire.wav"\
	".\os_win\..\_old\bounce.wav"\
	".\os_win\..\_old\bangbang.wav"\
	".\os_win\..\_old\d_bang.wav"\
	".\os_win\..\_old\p_bang.wav"\
	".\os_win\..\_old\c_bang.wav"\
	".\os_win\..\_old\s_bang.wav"\
	".\os_win\donuts.ico"\
	".\os_win\icon1.ico"\
	

!IF  "$(CFG)" == "HZ - Win32 Release"


"$(INTDIR)\donuts.res" : $(SOURCE) $(DEP_RSC_DONUTS) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/donuts.res" /i "c:\DXSDK\sdk\inc\" /i "os_win"\
 /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"


"$(INTDIR)\hz.res" : $(SOURCE) $(DEP_RSC_DONUTS) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"hz.res" /i "os_win" /d "_DEBUG" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\os_win\control.cpp
DEP_CPP_CONTR=\
	{$(INCLUDE)}"\dinput.h"\
	".\os_win\Control.h"\
	

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

!IF  "$(CFG)" == "HZ - Win32 Release"

DEP_CPP_DDUTI=\
	{$(INCLUDE)}"\ddraw.h"\
	".\os_win\ddutil.h"\
	

"$(INTDIR)\ddutil.obj" : $(SOURCE) $(DEP_CPP_DDUTI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"

DEP_CPP_DDUTI=\
	{$(INCLUDE)}"\ddraw.h"\
	".\os_win\ddutil.h"\
	
NODEP_CPP_DDUTI=\
	".\os_win\dwHeight"\
	

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
DEP_CPP_DRAWH=\
	{$(INCLUDE)}"\i_video.h"\
	".\os_win\..\donuts.h"\
	{$(INCLUDE)}"\drawhndl.h"\
	".\os_win\..\main.h"\
	{$(INCLUDE)}"\i_system.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\i_sprtet.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\os_win\ddutil.h"\
	{$(INCLUDE)}"\dsutil.h"\
	".\sprite.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\d3dvec.inl"\
	{$(INCLUDE)}"\lua.h"\
	".\luabase.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\View.h"\
	".\os_win\..\vconsole.h"\
	
NODEP_CPP_DRAWH=\
	".\translate.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\subwtype.h"\
	

!IF  "$(CFG)" == "HZ - Win32 Release"


"$(INTDIR)\drawhndl.obj" : $(SOURCE) $(DEP_CPP_DRAWH) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"


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
DEP_CPP_PLATF=\
	".\os_win\..\donuts.h"\
	".\os_win\..\Game.h"\
	".\os_win\..\View.h"\
	".\os_win\..\main.h"\
	{$(INCLUDE)}"\i_system.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\os_win\ddutil.h"\
	{$(INCLUDE)}"\dsutil.h"\
	".\sprite.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\d3dvec.inl"\
	{$(INCLUDE)}"\lua.h"\
	".\luabase.h"\
	".\os_win\..\spritet.h"\
	{$(INCLUDE)}"\i_sprtet.h"\
	".\os_win\..\vconsole.h"\
	
NODEP_CPP_PLATF=\
	".\translate.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\subwtype.h"\
	

!IF  "$(CFG)" == "HZ - Win32 Release"


"$(INTDIR)\platform.obj" : $(SOURCE) $(DEP_CPP_PLATF) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"


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
	{$(INCLUDE)}"\hndlmgr.h"\
	{$(INCLUDE)}"\ddraw.h"\
	

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
DEP_CPP_I_SPR=\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\i_video.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\vconsole.h"\
	{$(INCLUDE)}"\i_sprtet.h"\
	{$(INCLUDE)}"\i_image.h"\
	{$(INCLUDE)}"\lua.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\os_win\ddutil.h"\
	{$(INCLUDE)}"\dsutil.h"\
	".\sprite.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\d3dvec.inl"\
	".\luabase.h"\
	".\os_win\..\View.h"\
	
NODEP_CPP_I_SPR=\
	".\translate.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\subwtype.h"\
	

!IF  "$(CFG)" == "HZ - Win32 Release"


"$(INTDIR)\i_sprtet.obj" : $(SOURCE) $(DEP_CPP_I_SPR) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"


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
DEP_CPP_I_DRA=\
	{$(INCLUDE)}"\ddraw.h"\
	".\os_win\..\donuts.h"\
	{$(INCLUDE)}"\drawhndl.h"\
	{$(INCLUDE)}"\i_video.h"\
	{$(INCLUDE)}"\hndlmgr.h"\
	{$(INCLUDE)}"\i_draw.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\os_win\ddutil.h"\
	{$(INCLUDE)}"\dsutil.h"\
	".\sprite.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\d3dvec.inl"\
	{$(INCLUDE)}"\lua.h"\
	".\luabase.h"\
	".\os_win\..\spritet.h"\
	{$(INCLUDE)}"\i_sprtet.h"\
	{$(INCLUDE)}"\i_image.h"\
	
NODEP_CPP_I_DRA=\
	".\translate.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\subwtype.h"\
	

!IF  "$(CFG)" == "HZ - Win32 Release"


"$(INTDIR)\i_draw.obj" : $(SOURCE) $(DEP_CPP_I_DRA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"


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
DEP_CPP_I_VID=\
	{$(INCLUDE)}"\i_video.h"\
	".\os_win\..\donuts.h"\
	{$(INCLUDE)}"\drawhndl.h"\
	{$(INCLUDE)}"\i_system.h"\
	".\os_win\..\map.h"\
	".\os_win\..\vconsole.h"\
	{$(INCLUDE)}"\hndlmgr.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\i_sprtet.h"\
	{$(INCLUDE)}"\i_image.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\os_win\ddutil.h"\
	{$(INCLUDE)}"\dsutil.h"\
	".\sprite.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\d3dvec.inl"\
	{$(INCLUDE)}"\lua.h"\
	".\luabase.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\View.h"\
	
NODEP_CPP_I_VID=\
	".\translate.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\subwtype.h"\
	

!IF  "$(CFG)" == "HZ - Win32 Release"


"$(INTDIR)\i_video.obj" : $(SOURCE) $(DEP_CPP_I_VID) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"


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
DEP_CPP_I_SYS=\
	{$(INCLUDE)}"\i_system.h"\
	{$(INCLUDE)}"\i_video.h"\
	".\os_win\..\vconsole.h"\
	{$(INCLUDE)}"\hndlmgr.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\main.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\i_sprtet.h"\
	".\os_win\..\View.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\os_win\ddutil.h"\
	{$(INCLUDE)}"\dsutil.h"\
	".\sprite.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\d3dvec.inl"\
	{$(INCLUDE)}"\lua.h"\
	".\luabase.h"\
	".\os_win\..\spritet.h"\
	
NODEP_CPP_I_SYS=\
	".\translate.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\subwtype.h"\
	

!IF  "$(CFG)" == "HZ - Win32 Release"


"$(INTDIR)\i_system.obj" : $(SOURCE) $(DEP_CPP_I_SYS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"


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
DEP_CPP_I_MAI=\
	{$(INCLUDE)}"\i_video.h"\
	{$(INCLUDE)}"\i_system.h"\
	{$(INCLUDE)}"\hndlmgr.h"\
	".\os_win\..\donuts.h"\
	".\os_win\..\net.h"\
	".\os_win\..\main.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\i_sprtet.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\os_win\ddutil.h"\
	{$(INCLUDE)}"\dsutil.h"\
	".\sprite.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\d3dvec.inl"\
	{$(INCLUDE)}"\lua.h"\
	".\luabase.h"\
	".\os_win\..\spritet.h"\
	".\os_win\..\map.h"\
	".\os_win\..\View.h"\
	".\os_win\..\vconsole.h"\
	
NODEP_CPP_I_MAI=\
	".\translate.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\subwtype.h"\
	

!IF  "$(CFG)" == "HZ - Win32 Release"


"$(INTDIR)\i_main.obj" : $(SOURCE) $(DEP_CPP_I_MAI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"


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
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\os_win\ddutil.h"\
	{$(INCLUDE)}"\dsutil.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	".\..\..\MSDEV\DX5SDK\SDK\INC\d3dvec.inl"\
	
NODEP_CPP_I_SOU=\
	".\..\..\MSDEV\DX5SDK\SDK\INC\subwtype.h"\
	

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
DEP_CPP_LUABA=\
	".\luabase.h"\
	{$(INCLUDE)}"\lua.h"\
	".\os_win\..\vconsole.h"\
	".\os_win\..\View.h"\
	{$(INCLUDE)}"\ddraw.h"\
	
NODEP_CPP_LUABA=\
	".\translate.h"\
	

!IF  "$(CFG)" == "HZ - Win32 Release"


"$(INTDIR)\luabase.obj" : $(SOURCE) $(DEP_CPP_LUABA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HZ - Win32 Debug"


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
