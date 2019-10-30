@echo off
setlocal enabledelayedexpansion

echo ===============================================================================
echo ===============================================================================
set srcpath=%cd%
echo srcpath: %srcpath%


if exist "!srcpath!\*.%username%" (
    del /q "!srcpath!\*.%username%"
    echo Delete "!srcpath!\*.%username%" file
) else (
    echo No !srcpath!\*.%username% file
)


for /d %%i in ("%srcpath%\*") do (
    echo ===============================================================================
    set prjpath=%%i
    echo prjpath: !prjpath!

    echo ==========Delete project tmp folder and files.

    if exist "!prjpath!\*.%username%" (
        del /q "!prjpath!\*.%username%"
        echo Delete "!prjpath!\*.%username%" file
    ) else (
        echo No !prjpath!\*.%username% file
    )

    if exist "!prjpath!\*.rpt" (
        del /q "!prjpath!\*.rpt"
        echo Delete "!prjpath!\*.rpt" file
    ) else (
        echo No !prjpath!\*.rpt file
    )

    if exist "!prjpath!\*.cycdx" (
        del /q "!prjpath!\*.cycdx"
        echo Delete "!prjpath!\*.cycdx" file
    ) else (
        echo No !prjpath!\*.cycdx file
    )

    if exist "!prjpath!\*.cyfit" (
        del /q "!prjpath!\*.cyfit"
        echo Delete "!prjpath!\*.cyfit" file
    ) else (
        echo No !prjpath!\*.cyfit file
    )
    
    if exist "!prjpath!\*.log" (
        del /q "!prjpath!\*.log"
        echo Delete "!prjpath!\*.log" file
    ) else (
        echo No !prjpath!\*.log file
    )

    if exist "!prjpath!\codegentemp" (
        rmdir /s /q "!prjpath!\codegentemp"
        echo Delete "!prjpath!\codegentemp" folder
    ) else (
        echo No !prjpath!\codegentemp dir
    )

    if exist "!prjpath!\CortexM0p" (
        rmdir /s /q "!prjpath!\CortexM0p"
        echo Delete "!prjpath!\CortexM0p" folder
    ) else (
        echo No !prjpath!\CortexM0p dir
    )
    
    if exist "!prjpath!\CortexM4" (
        rmdir /s /q "!prjpath!\CortexM4"
        echo Delete "!prjpath!\CortexM4" folder
    ) else (
        echo No !prjpath!\CortexM4 dir
    )
    
    if exist "!prjpath!\Generated_Source" (
        rmdir /s /q "!prjpath!\Generated_Source"
        echo Delete "!prjpath!\Generated_Source" folder
    ) else (
        echo No !prjpath!\Generated_Source dir
    )

    if exist "!prjpath!\Export" (
        rmdir /s /q "!prjpath!\Export"
        echo Delete "!prjpath!\Export" folder
    ) else (
        echo No !prjpath!\Export dir
    )
)

echo ===============================================================================

pause
