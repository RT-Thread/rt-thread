@echo off
chcp 65001 >nul 2>&1
setlocal enabledelayedexpansion

:: ===================== 用户可配置参数 ======================
set "ORIGIN_BIN=rtthread.bin"
set "SIGNED_BIN=rtthread-trusted.bin"
set "SIGN_TOOL=STM32_SigningTool_CLI.exe"
set "FLASH_TOOL=STM32_Programmer_CLI"
set "FLASH_ADDR=0x70100000"

echo.
echo ==========================================================
echo                 STM32N6 固件签名下载工具
echo ==========================================================
echo  ⚠ 请确认：Boot0 = 0，Boot1 = 1，设备处于 Develop 模式
echo  正在检查工具与文件...

:: ===================== 依赖检查 =====================
if not exist "%ORIGIN_BIN%" (
    echo [错误] 未找到固件文件：%ORIGIN_BIN%
    echo        请先完成编译生成固件。
    pause
    exit /b 1
)

where %SIGN_TOOL% >nul 2>&1 || (
    echo [错误] 签名工具未找到：%SIGN_TOOL%
    echo        请确保该工具已加入系统 PATH。
    pause
    exit /b 1
)

where %FLASH_TOOL% >nul 2>&1 || (
    echo [错误] 下载工具未找到：%FLASH_TOOL%
    echo        请确保 STM32CubeProgrammer 已加入 PATH。
    pause
    exit /b 1
)

if not defined N6570_ExternalLoader (
    echo [错误] 外部加载器环境变量未配置：N6570_ExternalLoader
    echo        请正确设置 External Loader 路径。
    pause
    exit /b 1
)

echo [OK] 所有依赖检查通过！

:: ===================== 删除旧签名文件 =====================
echo.
echo ----------------------------------------------------------
echo   1/3  清理旧签名固件...
echo ----------------------------------------------------------

if exist "%SIGNED_BIN%" (
    echo [提示] 检测到旧文件：%SIGNED_BIN%
    echo [处理] 正在删除旧文件...
    del /f /q /a "%SIGNED_BIN%" >nul 2>&1

    if exist "%SIGNED_BIN%" (
        echo [错误] 无法删除旧签名文件（可能被占用）
        echo        请关闭相关程序后重试。
        pause
        exit /b 1
    )
    echo [OK] 旧签名文件已删除
) else (
    echo [OK] 无需清理
)

:: ===================== 固件签名 =====================
echo.
echo ----------------------------------------------------------
echo   2/3  正在为固件生成安全签名...
echo ----------------------------------------------------------
echo [执行] %SIGN_TOOL% -bin "%ORIGIN_BIN%" -nk -of 0x80000000 -t fsbl -o "%SIGNED_BIN%" -hv 2.3 -dump "%SIGNED_BIN%" --align

%SIGN_TOOL% -bin "%ORIGIN_BIN%" -nk -of 0x80000000 -t fsbl -o "%SIGNED_BIN%" -hv 2.3 -dump "%SIGNED_BIN%" --align

if not exist "%SIGNED_BIN%" (
    echo [错误] 签名失败！未生成：%SIGNED_BIN%
    pause
    exit /b 1
)

echo [OK] 签名完成！输出文件：%SIGNED_BIN%

:: ===================== 下载固件 =====================
echo.
echo ----------------------------------------------------------
echo   3/3  正在下载固件到 Flash 地址：%FLASH_ADDR%
echo ----------------------------------------------------------
echo [执行] %FLASH_TOOL% -c port=SWD mode=HOTPLUG ap=1 -el "%N6570_ExternalLoader%" -hardRst -w "%SIGNED_BIN%" %FLASH_ADDR%

%FLASH_TOOL% -c port=SWD mode=HOTPLUG ap=1 -el "%N6570_ExternalLoader%" -hardRst -w "%SIGNED_BIN%" %FLASH_ADDR%

if %errorlevel% equ 0 (
    echo.
    echo ==========================================================
    echo   ✔ 固件已成功烧录！
    echo   ⚠ 请切换启动方式为：Boot0 = 0，Boot1 = 0（Flash 启动）
    echo ==========================================================
) else (
    echo.
    echo [错误] 烧录失败，请检查：
    echo        1. SWD 连接是否正常
    echo        2. External Loader 路径是否正确
    echo        3. 芯片是否上电、BOOT 模式是否正确
)

echo.
pause
endlocal
