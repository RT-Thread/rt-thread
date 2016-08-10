@echo off

if .%1==. goto help
if exist %1 goto getSizeInfo
goto help

:getSizeInfo
%1\ARM\ARMCC\bin\armar --sizes %2 > %3
goto end

:help
echo   Syntax: getSizeInfo inFile outFile
echo.
echo   e.g.: getSizeInfo ..\..\..\Lib\ARM\arm_cortexM0l_math.lib  arm_cortexM0l_math.txt

:end

