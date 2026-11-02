@echo off
setlocal

REM ============================================================
REM APP Programming Script
REM %1 = Project path ($P)
REM ============================================================

set "PROJECT=%~1"

if not defined PROJECT (
    echo ERROR: Project path is empty.
    exit /b 1
)

if not exist "%PROJECT%\" (
    echo ERROR: Project directory not found:
    echo %PROJECT%
    exit /b 1
)

REM APP signed image directory
set "APP_BIN=%PROJECT%\rtthread-trusted.bin"
set "FLASH_ADDR=0x70100000"

echo.
echo ==========================================
echo          APP Programming
echo ==========================================
echo APP BIN : %APP_BIN%
echo Address : %FLASH_ADDR%
echo.

REM ------------------------------------------------------------
REM 1. Check signed APP image
REM ------------------------------------------------------------
if not exist "%APP_BIN%" (
    echo ERROR: Signed APP image not found:
    echo %APP_BIN%
    exit /b 1
)

where STM32_Programmer_CLI.exe >nul 2>&1
if errorlevel 1 (
    echo ERROR: STM32_Programmer_CLI.exe not found.
    exit /b 1
)

if not defined N6570_ExternalLoader (
    echo ERROR: N6570_ExternalLoader is not defined.
    exit /b 1
)

REM ------------------------------------------------------------
REM 2. Program APP to external flash
REM ------------------------------------------------------------
echo Programming APP...

STM32_Programmer_CLI.exe ^
    -c port=SWD mode=HOTPLUG ap=1 ^
    -el "%N6570_ExternalLoader%" ^
    -hardRst ^
    -w "%APP_BIN%" %FLASH_ADDR%

if errorlevel 1 (
    echo.
    echo ERROR: APP programming failed.
    exit /b 1
)

echo.
echo ==========================================
echo APP programming completed successfully.
echo ==========================================

endlocal
exit /b 0
