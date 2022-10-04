@set RTT_CC=gcc
@set RTT_EXEC_PATH=C:\Program Files (x86)\GNU Tools ARM Embedded\8 2019-q3-aarch64-elf\bin
@set RTT_CC_PREFIX=aarch64-elf-
@set PATH=%RTT_EXEC_PATH%;%ENV_ROOT%\tools\gnu_gcc\arm_gcc\mingw\bin;%PATH%

make
python transcode.py
