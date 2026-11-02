@echo off
setlocal ENABLEEXTENSIONS ENABLEDELAYEDEXPANSION

set "RascVersionFile=%~1"
shift

set "InputFile=%~dp0configuration.xml"
set "OutputFile=%~dp0output.rasc"

if /i "%~3"=="--gensmartbundle" (
    set "InputFile=%~9"
    set "OutputFile=%~dpn9.sbd"
)

if not exist "%InputFile%" (
    echo [ERROR] Input file "%InputFile%" does not exist.
    exit /b 1
)

call "%~dp0rasc_version.bat" "%RascVersionFile%"
if errorlevel 1 exit /b 1

set /a idx=0
for /f "usebackq tokens=*" %%a in ("%RascVersionFile%") do (
    if !idx! EQU 2 set "RascExe=%%a"
    set /a idx+=1
)

if not defined RascExe (
    echo [ERROR] RASC executable is not configured.
    exit /b 1
)

set "RascExe=%RascExe:rasc.exe=rascc.exe%"
set "Parameters="
for %%a in (%*) do (
    if defined FirstParamSkipped set Parameters=!Parameters! %%a
    set FirstParamSkipped=true
)

echo [INFO] Generating Smart Bundle "%OutputFile%"...
"%RascExe%" %Parameters%
exit /b %errorlevel%
