@echo off
cd main
g++ main.cpp
cd ..
cp main/a.exe bin
cd main
rm a.exe
pause
