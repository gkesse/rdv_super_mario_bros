cd C:\Qt\6.5.2\Src\qtbase\src\plugins\sqldrivers
mkdir %BUILD_DIR%
cd %BUILD_DIR%

qt-cmake .. ^
-G "MinGW Makefiles" ^
-DMySQL_INCLUDE_DIR="C:\Program Files\MySQL\MySQL Server 8.0\include" ^
-DMySQL_LIBRARY="C:\Program Files\MySQL\MySQL Server 8.0\lib\libmysql.lib" ^
-DCMAKE_INSTALL_PREFIX="C:\Qt\6.5.2\mingw_64"
