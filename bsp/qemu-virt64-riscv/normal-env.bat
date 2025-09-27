
@set def_arch=riscv64

pushd %RTT_ENV_URL%\..\..
set RTT_ENV_ROOT=%cd%
popd

:: Download from:
:: https://github.com/xpack-dev-tools/riscv-none-elf-gcc-xpack/releases/download/v12.3.0-2/xpack-riscv-none-elf-gcc-12.3.0-2-win32-x64.zip
:: Extract as:
:: C:\env-windows\tools\gnu_gcc\xpack-riscv-none-elf-gcc-12.3.0-2

@set RTT_CC=gcc
@set RTT_EXEC_PATH=%RTT_ENV_ROOT%\tools\gnu_gcc\xpack-riscv-none-elf-gcc-12.3.0-2\bin
@set RTT_CC_PREFIX=riscv-none-elf-

@set PATH=%RTT_EXEC_PATH%;%RTT_ENV_ROOT%\.venv\Scripts;%_OLD_VIRTUAL_PATH%

@echo "Arch      => %def_arch%"
@echo "CC        => %RTT_CC%"
@echo "PREFIX    => %RTT_CC_PREFIX%"
@echo "EXEC_PATH => %RTT_EXEC_PATH%"

:EXIT
