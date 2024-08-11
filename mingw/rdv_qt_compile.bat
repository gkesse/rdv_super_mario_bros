@echo off
setlocal enabledelayedexpansion
set "PATH=C:\Qt\6.5.2\mingw_64\bin;%PATH%"
del /q /s bin\rdv_super_mario_bro.exe
qmake
mingw32-make
bin\rdv_super_mario_bro.exe
endlocal
