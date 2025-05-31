@echo off
cls

echo /*
echo  * Copyright (c) 2006 - 2025, RT-Thread Development Team
echo  *
echo  * SPDX-License-Identifier: Apache-2.0
echo  *
echo  * Change Logs:
echo  * Date           Author       Notes
echo  * 2025/04/29     Wangshun     first version
echo  * 2025/05/14     Optimized    Improved robustness and error handling
echo  */
echo.

setlocal enabledelayedexpansion

set "CONFIG_FILE=qemu_config.txt"
set "CPU_CONFIG_FILE=cpu_config.txt"
set "DEFAULT_QEMU_DIR=E:\XuanTieCore\6.QEMU"
set "ELF_PATH=%CD%\rtthread.elf"

:: Load QEMU directory from config file or set default
if exist "!CONFIG_FILE!" (
    set /p QEMU_DIR=<"!CONFIG_FILE!"
    if not defined QEMU_DIR set "QEMU_DIR=!DEFAULT_QEMU_DIR!"
) else (
    set "QEMU_DIR=!DEFAULT_QEMU_DIR!"
)

:: Load CPU parameter from config file or set default
if exist "!CPU_CONFIG_FILE!" (
    set /p CPU_PARAM=<"!CPU_CONFIG_FILE!"
    if not defined CPU_PARAM set "CPU_PARAM=c910v3"
) else (
    set "CPU_PARAM=c910v3"
)

:: Prompt for new QEMU directory
set /p "USER_INPUT=Enter new QEMU directory (Enter for default: !QEMU_DIR!): "
if defined USER_INPUT (
    set "USER_INPUT=!USER_INPUT: =!"
    if not "!USER_INPUT!"=="" (
        set "QEMU_DIR=!USER_INPUT!"
        echo !QEMU_DIR!>"!CONFIG_FILE!"
    )
)

:: Validate QEMU path
set "QEMU_PATH=!QEMU_DIR!\qemu-system-riscv64.exe"
if not exist "!QEMU_PATH!" (
    echo Error: QEMU executable not found at "!QEMU_PATH!".
    echo Please verify the QEMU directory and try again.
    pause
    exit /b 1
)

:: Prompt for new CPU parameter
echo Current CPU parameter: !CPU_PARAM!
set /p "CPU_INPUT=Enter new -cpu parameter (Enter for default): "
if defined CPU_INPUT (
    set "CPU_INPUT=!CPU_INPUT: =!"
    if not "!CPU_INPUT!"=="" (
        set "CPU_PARAM=!CPU_INPUT!"
        echo !CPU_PARAM!>"!CPU_CONFIG_FILE!"
    )
)

:: Validate ELF file
if not exist "!ELF_PATH!" (
    echo Error: rtthread.elf not found at "!ELF_PATH!".
    pause
    exit /b 1
)

:: Display QEMU version
echo.
"!QEMU_PATH!" --version

:: Run QEMU
echo.
"!QEMU_PATH!" -machine xiaohui -kernel "!ELF_PATH!" -nographic -cpu !CPU_PARAM!
if !ERRORLEVEL! neq 0 (
    echo Error: QEMU failed to run. Check configuration or paths.
    pause
    exit /b !ERRORLEVEL!
)

echo QEMU terminated.
pause
endlocal
