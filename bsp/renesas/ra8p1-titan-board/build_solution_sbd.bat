@echo off
setlocal ENABLEEXTENSIONS ENABLEDELAYEDEXPANSION

set "BspRoot=%~dp0"
set "Cpu0Bundle=%BspRoot%m85\Objects\template.sbd"
set "Cpu1Bundle=%BspRoot%m33\Objects\template.sbd"
set "RascVersionFile=%BspRoot%m85\rasc_version.txt"

if not exist "%Cpu0Bundle%" (
    echo [ERROR] CPU0 Smart Bundle "%Cpu0Bundle%" does not exist.
    echo [ERROR] Build the m85 Keil project first.
    exit /b 1
)

if not exist "%Cpu1Bundle%" (
    echo [ERROR] CPU1 Smart Bundle "%Cpu1Bundle%" does not exist.
    echo [ERROR] Build the m33 Keil project first.
    exit /b 1
)

call "%BspRoot%m85\rasc_version.bat" "%RascVersionFile%"
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
powershell -NoProfile -ExecutionPolicy Bypass -File "%BspRoot%build_solution_sbd.ps1" -RascExe "%RascExe%"
exit /b %errorlevel%
