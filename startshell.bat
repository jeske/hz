PATH=%PATH%;c:\local\bin;"C:\Program Files\XEmacs\XEmacs-21.1.9\i386-pc-win32\"
set CVSROOT=:pserver:jeske@chat.net:/vol2/cvsroot
set CVSIGNORE=*.sbr
set INCLUDE=c:\local\include;%INCLUDE%

REM ** For win95 boxes
set HOMEDRIVE=c:
set HOMEPATH=\local

doskey dir=ls -F $*
doskey ls=ls -F $*
doskey gc=gnuclientw.exe $*
doskey e=runemacs.exe $*
doskey vi=runemacs.exe $*


