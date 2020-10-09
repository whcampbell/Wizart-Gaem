cmake -G "MinGW Makefiles" .
mingw32-make
del CMakeCache.txt
del cmake_install.cmake
rmdir CMakeFiles /s /q
cmd /k