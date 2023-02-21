
@set def_arch=arm

@if not "%1"=="" (
    @set def_arch=%1
)

@if %def_arch%==arm (
    @set RTT_CC=gcc
    @set RTT_EXEC_PATH=%cd%\tools\gnu_gcc\arm-linux-musleabi_for_i686-w64-mingw32\bin
    @set RTT_CC_PREFIX=arm-linux-musleabi-
    @copy configs\def_config_arm .config
) else if %def_arch%==riscv64 (
    @set RTT_CC=gcc
    @set RTT_EXEC_PATH=E:\workspace\rt-smart\userapps\tools\gnu_gcc\riscv64-linux-musleabi_for_i686-w64-mingw32\bin
    @set RTT_CC_PREFIX=riscv64-unknown-linux-musl-
    @copy configs\def_config_riscv64 .config
) else (
    @echo "ERROR:supported_arch=arm riscv64!"
    @goto EXIT
)

@set PATH=%RTT_EXEC_PATH%;%PATH%

@echo "Arch      => %def_arch%"
@echo "CC        => %RTT_CC%"
@echo "PREFIX    => %RTT_CC_PREFIX%"
@echo "EXEC_PATH => %RTT_EXEC_PATH%"

:EXIT