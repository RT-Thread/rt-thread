@echo off
REM RASC version handler 2024-08-05

setlocal ENABLEEXTENSIONS ENABLEDELAYEDEXPANSION

REM Initialisations
set "RascVersionFileHeader=# RASC version and installation file"
set "RascDescRootKey=SOFTWARE\Renesas\RASC\Installations"
set "VersionUnknown=Unknown"
set "RascVersionValueName=Version"
set "RascExeValueName=ExePath"
set "RascSearchPath=C:\Renesas"
set /a NumRascs=0
set "TargetRascVersion="
set "TargetRascExe="
set "TargetRascVersionDiffers="

REM First parameter is (possibly non-existent) file containing RASC version to invoke
set "RascVersionFile=%~1"

REM Second parameter specifies non-interactive mode
set "NonInteractiveMode=%~2"

REM Extract specific RASC version from file
REM echo "%RascVersionFile%"
if exist "%RascVersionFile%" (

    REM echo DEBUG: Have version file: "%RascVersionFile%"

    set /a idx=0
    for /f "usebackq tokens=*" %%a in ("%RascVersionFile%") do (
        if !idx! EQU 0 (
            if not "%%a" == "%RascVersionFileHeader%" (
                REM echo DEBUG: Header doesn't match

                goto _EndVersionFileParse
            )
        )
        if !idx! EQU 1 (
            set "TargetRascVersion=%%a"
        )
        if !idx! EQU 2 (
            set "TargetRascExe=%%a"
        )
        set /a idx+=1
    )
)

:_EndVersionFileParse

REM echo DEBUG: Target version: "%TargetRascVersion%"
REM echo DEBUG: Target exe: "%TargetRascExe%"

REM Search through registry RASC descriptions for match on exe path and version
for %%h in (HKCU HKLM) do (
    for %%v in (32 64) do (
        for /f "usebackq skip=1 tokens=*" %%a in (`reg query "%%h\%RascDescRootKey%" /reg:%%v 2^>nul`) do (
            set "RascDescKey=%%a"
            set "RascVersion="
            set "RascExe="

            REM echo DEBUG: Desc Key: !RascDescKey!

            for /f "usebackq skip=2 tokens=3" %%b in (`reg query "!RascDescKey!" /v "%RascVersionValueName%" /reg:%%v 2^>nul`) do (
                set "RascVersion=%%b"
            )

            REM echo DEBUG: Version: !RascVersion!

            for /f "usebackq skip=2 tokens=2*" %%b in (`reg query "!RascDescKey!" /v "%RascExeValueName%" /reg:%%v 2^>nul`) do (
                REM %%b is value name, so %%c is the value - supports values with spaces
                set "RascExe=%%c"
            )

            REM echo DEBUG: Exe: !RascExe!

            if not defined RascExe (
                REM Error - unable to extract executable
                set ErrorMessage=Unable to extract RASC executable path from the registry
                goto _Error
            )

            REM Check if exe exists, otherwise assume it's been removed
            if exist "!RascExe!" (
                REM Check for specified target version and exe path match
                if defined RascVersion (
                    if defined TargetRascVersion (
                        if /i "!RascExe!" == "%TargetRascExe%" (
                            REM echo "!RascVersion!"
                            REM echo "%TargetRascVersion%"
                            if "!RascVersion!" == "%TargetRascVersion%" (

                                REM echo DEBUG: Found match

                                goto _RascVersionRewrite
                            ) else (
                                REM Indicate target RASC has a different version than
                                REM the registry entry. In this case, target RASC has
                                REM changed, so possibly prompt the user to select a
                                REM RASC again
                                set "TargetRascVersionDiffers=true"
                            )
                        )
                    )
                ) else (
                    REM Error - unable to extract version
                    set ErrorMessage=Unable to extract RASC version from the registry
                    goto _Error
                )

                call :SubAddFoundRasc "!RascExe!" "!RascVersion!"
            )
        )
    )
)

REM If target RASC exists and doesn't differ from the registry version (i.e.
REM was not found in the registry), just run it
if defined TargetRascExe (
    if exist "%TargetRascExe%" (
        if not defined TargetRascVersionDiffers (
            set "RascExe=%TargetRascExe%"
            set "RascVersion=%VersionUnknown%"
            goto _RascVersionRewrite
        )
    )
)

if %NumRascs% EQU 0 (
    REM No entries found in the registry, search C:\Renesas\ as fallback
    echo/
    echo Searching in "%RascSearchPath%" for RA Smart Configurator installations ...
    for /f "usebackq tokens=*" %%a in (`dir "%RascSearchPath%\rasc.exe" /s /b 2^>nul`) do (
        if not "%%a" == "" (
            call :SubAddFoundRasc "%%a" "%VersionUnknown%"
        )
    )
)

if %NumRascs% EQU 0 (
    REM Still no RASCs found - give up
    set ErrorMessage=No "RA Smart Configurator" installations found, download one from renesas.com
    goto _Error
)

if %NumRascs% EQU 1 (
    set "RascExe=%RascExeList[0]%"
    set "RascVersion=%RascVersionList[0]%"
    goto _RascVersionRewrite
)

REM Exit with status 1 if choice required in non-interactive mode
if not "%NonInteractiveMode%"=="" exit /b 1

REM Prompt for user to choose from multiple RASCs
echo/
echo Multiple RA Smart Configurators installed:
set /a RascIdxMax=%NumRascs% - 1
set Choices=""
for /l %%a in (0,1,%RascIdxMax%) do (
    echo %%a: Version !RascVersionList[%%a]! ^("!RascExeList[%%a]!"^)
    set "Choices=!Choices!%%a"
)
echo/
set /a ChosenIdx=%NumRascs%
if %RascIdxMax% GTR 9 (
    set /p InputIdx=Select which one to run [0-%RascIdxMax%]?
    REM Check if the input string is a number
    set "NonNumber=" & for /f "delims=0123456789" %%i in ("!InputIdx!") do set "NonNumber=%%i"
    if not defined NonNumber (
        set /a ChosenIdx=!InputIdx!
    )
) else (
    choice /c %Choices% /m "Select which one to run"
    set /a ChosenIdx=!ERRORLEVEL! - 1
)
if %ChosenIdx% GEQ %NumRascs% (
    REM Out of range
    set ErrorMessage=Invalid selection
    goto _Error
)
set "RascExe=!RascExeList[%ChosenIdx%]!"
set "RascVersion=!RascVersionList[%ChosenIdx%]!"

:_RascVersionRewrite

REM Carefully re-write specific version file, if required
if exist "%RascVersionFile%" (
    if not defined TargetRascVersion (
        if not defined TargetRascExe (
            REM Unexpected version file contents, skip rewriting
            goto _EndRascVersionRewrite
        )
    )
)

if "!RascVersion!" == "%TargetRascVersion%" (
    if /i "!RascExe!" == "%TargetRascExe%" (
        REM Version file already up-to-date, skip rewriting
        goto _EndRascVersionRewrite
    )
)

echo %RascVersionFileHeader%>"%RascVersionFile%"
echo %RascVersion%>>"%RascVersionFile%"
echo %RascExe%>>"%RascVersionFile%"

:_EndRascVersionRewrite
goto :EOF

REM Add specified RASC to pseudo-list
REM Parameters:
REM 1: RascExe
REM 2: RascVersion
:SubAddFoundRasc
set "RascExeList[%NumRascs%]=%~1"
set "RascVersionList[%NumRascs%]=%~2"
set /a NumRascs+=1
goto :EOF

:_Error
echo/
echo %ErrorMessage%
if "%NonInteractiveMode%"=="" pause
exit /b 1
