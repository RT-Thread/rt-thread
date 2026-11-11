ifeq ($(shell uname), Linux)
    # Linux-specific settings
    toolchain=/home/mhy/gcc-arm-none-eabi-10.3-2021.10/bin
else
    # Windows-specific settings
    # toolchain=F:\work\TOOLS\sdk-toolchain-RISC-V-GCC-WCH\bin
    ifndef toolchain
        $(warning Please rewrite the toolchain in windows local directory")
        exit 0
    endif
endif

all:
	scons -j 8 --exec-path=$(toolchain)

PHONY: clean
clean:
	scons -c --exec-path=$(toolchain)
	rm -f *.bin *.hex *.map > /dev/null 2>&1

