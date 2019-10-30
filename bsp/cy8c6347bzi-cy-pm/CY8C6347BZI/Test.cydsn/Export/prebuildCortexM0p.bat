@REM This script allows a 3rd party IDE to use cymcuelftool.exe to perform
@REM the pre processing that is necessary to extract the bootloader
@REM data from the *.elf file for use when building the bootloadable
@REM application.
@REM NOTE: This script is auto generated. Do not modify.
@REM 
@REM Copy cymcuelftool executable from CMSIS-Pack into project
IF /I "%~2" NEQ "eclipse" GOTO not_eclipse
set OSTYPE=
if "%~3"=="win32" (
    set OSTYPE=win
) else (
    if "%~3"=="linux" (
        set OSTYPE=linux
    ) else (
        set OSTYPE=osx
    )
)

copy /Y "%~1\%OSTYPE%\elf\cymcuelftool*" "%cd%"
@IF %errorlevel% NEQ 0 EXIT /b %errorlevel%
EXIT

:not_eclipse
