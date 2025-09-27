
@set def_arch=riscv64

pushd %RTT_ENV_URL%\..\..
set RTT_ENV_ROOT=%cd%
popd

:: Download from:
:: https://download.rt-thread.org/download/rt-smart/toolchains/riscv64-linux-musleabi_for_i686-w64-mingw32_latest.zip
:: Extract as:
:: C:\env-windows\tools\gnu_gcc\riscv64-linux-musleabi_for_i686-w64-mingw32

@set RTT_CC=gcc
@set RTT_EXEC_PATH=%RTT_ENV_ROOT%\tools\gnu_gcc\riscv64-linux-musleabi_for_i686-w64-mingw32\bin
@set RTT_CC_PREFIX=riscv64-linux-musleabi-

@set PATH=%RTT_EXEC_PATH%;%RTT_ENV_ROOT%\.venv\Scripts;%_OLD_VIRTUAL_PATH%

@echo "Arch      => %def_arch%"
@echo "CC        => %RTT_CC%"
@echo "PREFIX    => %RTT_CC_PREFIX%"
@echo "EXEC_PATH => %RTT_EXEC_PATH%"

:EXIT