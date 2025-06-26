add_rules("mode.debug", "mode.release")

toolchain("arm-none-eabi")
    set_kind("standalone")
    set_sdkdir("/home/bernard/.env/tools/scripts/packages/arm-none-eabi-gcc-v13.2.rel1")
toolchain_end()

target("rt-thread")
    set_kind("binary")
    set_toolchains("arm-none-eabi")

    add_files(
        	"applications/main.c",
	"../../../components/libc/compilers/common/cctype.c",
	"../../../components/libc/compilers/common/cstdlib.c",
	"../../../components/libc/compilers/common/cstring.c",
	"../../../components/libc/compilers/common/ctime.c",
	"../../../components/libc/compilers/common/cunistd.c",
	"../../../components/libc/compilers/common/cwchar.c",
	"../../../components/libc/compilers/newlib/syscalls.c",
	"../../../components/drivers/core/device.c",
	"../../../components/drivers/ipc/completion_comm.c",
	"../../../components/drivers/ipc/completion_up.c",
	"../../../components/drivers/ipc/condvar.c",
	"../../../components/drivers/ipc/dataqueue.c",
	"../../../components/drivers/ipc/pipe.c",
	"../../../components/drivers/ipc/ringblk_buf.c",
	"../../../components/drivers/ipc/ringbuffer.c",
	"../../../components/drivers/ipc/waitqueue.c",
	"../../../components/drivers/ipc/workqueue.c",
	"../../../components/drivers/pin/dev_pin.c",
	"../../../components/drivers/serial/dev_serial.c",
	"../libraries/HAL_Drivers/drivers/drv_gpio.c",
	"../libraries/HAL_Drivers/drivers/drv_usart.c",
	"../libraries/HAL_Drivers/drv_common.c",
	"board/CubeMX_Config/Src/stm32f4xx_hal_msp.c",
	"board/board.c",
	"../../../components/finsh/shell.c",
	"../../../components/finsh/msh.c",
	"../../../components/finsh/msh_parse.c",
	"../../../components/finsh/cmd.c",
	"../../../src/clock.c",
	"../../../src/components.c",
	"../../../src/cpu_up.c",
	"../../../src/defunct.c",
	"../../../src/idle.c",
	"../../../src/ipc.c",
	"../../../src/irq.c",
	"../../../src/kservice.c",
	"../../../src/mem.c",
	"../../../src/mempool.c",
	"../../../src/object.c",
	"../../../src/scheduler_comm.c",
	"../../../src/scheduler_up.c",
	"../../../src/thread.c",
	"../../../src/timer.c",
	"../../../src/klibc/kstring.c",
	"../../../src/klibc/rt_vsscanf.c",
	"../../../src/klibc/kstdio.c",
	"../../../src/klibc/rt_vsnprintf_tiny.c",
	"../../../src/klibc/kerrno.c",
	"../../../libcpu/arm/common/atomic_arm.c",
	"../../../libcpu/arm/common/div0.c",
	"../../../libcpu/arm/common/showmem.c",
	"../../../libcpu/arm/cortex-m4/context_gcc.S",
	"../../../libcpu/arm/cortex-m4/cpuport.c",
	"packages/stm32f4_cmsis_driver-latest/Source/Templates/gcc/startup_stm32f412zx.s",
	"packages/stm32f4_cmsis_driver-latest/Source/Templates/system_stm32f4xx.c",
	"packages/stm32f4_hal_driver-latest/Src/stm32f4xx_hal_dma_ex.c",
	"packages/stm32f4_hal_driver-latest/Src/stm32f4xx_hal_usart.c",
	"packages/stm32f4_hal_driver-latest/Src/stm32f4xx_hal_pwr_ex.c",
	"packages/stm32f4_hal_driver-latest/Src/stm32f4xx_hal_cryp.c",
	"packages/stm32f4_hal_driver-latest/Src/stm32f4xx_hal_gpio.c",
	"packages/stm32f4_hal_driver-latest/Src/stm32f4xx_hal_rcc.c",
	"packages/stm32f4_hal_driver-latest/Src/stm32f4xx_hal.c",
	"packages/stm32f4_hal_driver-latest/Src/stm32f4xx_hal_cortex.c",
	"packages/stm32f4_hal_driver-latest/Src/stm32f4xx_hal_pwr.c",
	"packages/stm32f4_hal_driver-latest/Src/stm32f4xx_hal_cec.c",
	"packages/stm32f4_hal_driver-latest/Src/stm32f4xx_hal_cryp_ex.c",
	"packages/stm32f4_hal_driver-latest/Src/stm32f4xx_hal_dma.c",
	"packages/stm32f4_hal_driver-latest/Src/stm32f4xx_hal_uart.c",
	"packages/stm32f4_hal_driver-latest/Src/stm32f4xx_hal_rcc_ex.c",
	"packages/stm32f4_hal_driver-latest/Src/stm32f4xx_hal_crc.c",
	"packages/stm32f4_hal_driver-latest/Src/stm32f4xx_hal_rng.c"
    )

    add_includedirs(
        	"applications",
	"packages/CMSIS-Core-latest/Include",
	"../../../components/libc/compilers/newlib",
	"../../../components/libc/compilers/common/include",
	"../../../components/drivers/include",
	"../../../components/drivers/smp_call",
	"../../../components/drivers/phy",
	"board",
	"board/CubeMX_Config/Inc",
	"../libraries/HAL_Drivers/drivers",
	"../libraries/HAL_Drivers/drivers/config",
	"../libraries/HAL_Drivers",
	"../../../components/finsh",
	".",
	"../../../include",
	"../../../libcpu/arm/common",
	"../../../libcpu/arm/cortex-m4",
	"../../../components/libc/posix/ipc",
	"../../../components/libc/posix/io/poll",
	"../../../components/libc/posix/io/eventfd",
	"../../../components/libc/posix/io/epoll",
	"packages/stm32f4_cmsis_driver-latest/Include",
	"packages/stm32f4_hal_driver-latest/Inc",
	"packages/stm32f4_hal_driver-latest/Inc/Legacy"
    )

    add_defines(
        	"RT_USING_LIBC",
	"RT_USING_NEWLIBC",
	"STM32F412Zx",
	"USE_HAL_DRIVER",
	"_POSIX_C_SOURCE=1",
	"__RTTHREAD__"
    )

    add_cflags(
        " -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -Dgcc -O0 -gdwarf-2 -g" ,{force = true}
    )
    add_cxxflags(
        " -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -Dgcc -O0 -gdwarf-2 -g" ,{force = true}
    )

    add_asflags(
        " -c -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -x assembler-with-cpp -Wa,-mimplicit-it=thumb  -gdwarf-2" ,{force = true}
    )

    add_ldflags(
        " -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -Wl,--gc-sections,-Map=rt-thread.map,-cref,-u,Reset_Handler -T board/linker_scripts/link.lds" ,{force = true}
    )

    set_targetdir("./")
    set_filename("rtthread.elf")

    after_build(function(target)
        os.exec("/home/bernard/.env/tools/scripts/packages/arm-none-eabi-gcc-v13.2.rel1/bin/arm-none-eabi-objcopy -O ihex rtthread.elf rtthread.hex")
        os.exec("/home/bernard/.env/tools/scripts/packages/arm-none-eabi-gcc-v13.2.rel1/bin/arm-none-eabi-objcopy -O binary rtthread.elf rtthread.bin")
        os.exec("/home/bernard/.env/tools/scripts/packages/arm-none-eabi-gcc-v13.2.rel1/bin/arm-none-eabi-size rtthread.elf")
    end)