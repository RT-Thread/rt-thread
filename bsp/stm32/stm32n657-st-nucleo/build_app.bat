@echo off
setlocal

REM ============================================================
REM APP Build Script
REM %1 = AXF file path (#L)
REM %2 = Project path ($P)
REM ============================================================

set "AXF=%~1"
set "PROJECT=%~2"

if not defined AXF (
    echo ERROR: AXF path is empty.
    exit /b 1
)

if not defined PROJECT (
    echo ERROR: Project path is empty.
    exit /b 1
)

if not exist "%AXF%" (
    echo ERROR: AXF file not found:
    echo %AXF%
    exit /b 1
)

REM Get AXF directory and filename
for %%F in ("%AXF%") do (
    set "AXF_DIR=%%~dpF"
    set "AXF_NAME=%%~nxF"
    set "BIN_NAME=%%~nF.bin"
)

set "BIN=%AXF_DIR%%BIN_NAME%"

echo.
echo ==========================================
echo        APP Build / Sign
echo ==========================================
echo AXF     : %AXF%
echo BIN     : %BIN%
echo PROJECT : %PROJECT%
echo.

REM ------------------------------------------------------------
REM 1. Check BIN
REM ------------------------------------------------------------
if not exist "%BIN%" (
    echo ERROR: BIN file not found:
    echo %BIN%
    exit /b 1
)

REM ------------------------------------------------------------
REM 2. Copy BIN to project directory
REM ------------------------------------------------------------
echo Copying BIN...
copy /Y "%BIN%" "%PROJECT%\"

if errorlevel 1 (
    echo ERROR: Failed to copy BIN.
    exit /b 1
)

REM ------------------------------------------------------------
REM 3. Sign APP
REM ------------------------------------------------------------
echo.
echo Signing APP...

where STM32_SigningTool_CLI.exe >nul 2>&1
if errorlevel 1 (
    echo ERROR: STM32_SigningTool_CLI.exe not found.
    exit /b 1
)

if exist "%PROJECT%\rtthread-trusted.bin" (
    del /f /q "%PROJECT%\rtthread-trusted.bin" >nul 2>&1
    if exist "%PROJECT%\rtthread-trusted.bin" (
        echo ERROR: Cannot remove old signed APP image.
        exit /b 1
    )
)

STM32_SigningTool_CLI.exe ^
    -bin "%PROJECT%\%BIN_NAME%" ^
    -nk ^
    -of 0x80000000 ^
    -t fsbl ^
    -o "%PROJECT%\rtthread-trusted.bin" ^
    -hv 2.3 ^
    -dump "%PROJECT%\rtthread-trusted.bin" ^
    --align

if errorlevel 1 (
    echo.
    echo ERROR: Signing failed.
    exit /b 1
)

if not exist "%PROJECT%\rtthread-trusted.bin" (
    echo.
    echo ERROR: Signed APP image was not generated.
    exit /b 1
)

echo.
echo ==========================================
echo APP build and signing completed.
echo Output:
echo %PROJECT%\rtthread-trusted.bin
echo ==========================================

endlocal
exit /b 0
