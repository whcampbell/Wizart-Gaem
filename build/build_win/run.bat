cmake -G "MinGW Makefiles" .
mingw32-make
del CMakeCache.txt
del cmake_install.cmake
del Makefile
rmdir CMakeFiles /s /q
cmd /k