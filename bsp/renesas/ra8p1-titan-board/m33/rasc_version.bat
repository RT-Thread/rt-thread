@echo off
setlocal ENABLEEXTENSIONS ENABLEDELAYEDEXPANSION

set "RascVersionFile=%~1"
set "RascVersion="
set "RascExe="

if exist "%RascVersionFile%" (
    set /a idx=0
    for /f "usebackq tokens=*" %%a in ("%RascVersionFile%") do (
        if !idx! EQU 1 set "RascVersion=%%a"
        if !idx! EQU 2 set "RascExe=%%a"
        set /a idx+=1
    )
)

if defined RascExe if exist "%RascExe%" exit /b 0

set "RascExe="
for %%r in ("C:\Tools\Renesas\FSP" "C:\Renesas\RA" "C:\Renesas") do (
    if not defined RascExe if exist "%%~r" (
        for /d %%d in ("%%~r\*fsp_v6.2.0*") do (
            if not defined RascExe if exist "%%~d\eclipse\rascc.exe" set "RascExe=%%~d\eclipse\rascc.exe"
        )
    )
)

if not defined RascExe (
    echo [ERROR] Renesas FSP 6.2.0 Smart Configurator was not found.
    exit /b 1
)

>"%RascVersionFile%" echo # RASC version and installation file
>>"%RascVersionFile%" echo 6.2.0
>>"%RascVersionFile%" echo %RascExe%
exit /b 0
