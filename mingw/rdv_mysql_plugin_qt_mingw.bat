@echo off
setlocal enabledelayedexpansion
set "PATH=C:\Qt\6.5.2\mingw_64\bin;%PATH%"
set "PATH=C:\Qt\Tools\mingw1120_64\bin;%PATH%"
set "BUILD_DIR=build-mingw"
set "CURRENT_DIR=%~dp0"

call %CURRENT_DIR%rdv_mysql_plugin_qt_mingw_build.bat
call %CURRENT_DIR%rdv_mysql_plugin_qt_mingw_compile.bat
call %CURRENT_DIR%rdv_mysql_plugin_qt_mingw_clean.bat

endlocal
