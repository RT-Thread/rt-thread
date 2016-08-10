INCLUDE(CMakeForceCompiler)

# CROSS COMPILER SETTING
SET(CMAKE_SYSTEM_NAME Generic)
CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

# THE VERSION NUMBER
SET (Tutorial_VERSION_MAJOR 1)
SET (Tutorial_VERSION_MINOR 0)

# ENABLE ASM
ENABLE_LANGUAGE(ASM)

SET(CMAKE_STATIC_LIBRARY_PREFIX)
SET(CMAKE_STATIC_LIBRARY_SUFFIX)

SET(CMAKE_EXECUTABLE_LIBRARY_PREFIX)
SET(CMAKE_EXECUTABLE_LIBRARY_SUFFIX)

 
# CURRENT DIRECTORY
SET(ProjDirPath ${CMAKE_CURRENT_SOURCE_DIR})


SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -DDEBUG")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -g")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -mthumb")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -fno-common")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -ffunction-sections")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -fdata-sections")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -ffreestanding")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -fno-builtin")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -Os")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -mapcs")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -std=gnu99")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -mcpu=cortex-m0plus")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -Wall")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -mthumb")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -fno-common")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -ffunction-sections")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -fdata-sections")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -ffreestanding")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -fno-builtin")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -Os")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -mapcs")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -std=gnu99")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -mcpu=cortex-m0plus")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -Wall")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DCPU_MKL27Z64VLH4")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DTWR_K64F120M")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fno-common")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -ffunction-sections")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fdata-sections")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -ffreestanding")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fno-builtin")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Os")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -mthumb")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -mapcs")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -std=gnu99")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -mcpu=cortex-m0plus")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -MMD")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -MP")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DNDEBUG")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DCPU_MKL27Z64VLH4")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DTWR_K64F120M")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Os")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fno-common")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -ffunction-sections")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fdata-sections")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -ffreestanding")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fno-builtin")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -mthumb")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -mapcs")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -std=gnu99")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -mcpu=cortex-m0plus")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -MMD")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -MP")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} --defsym=__ram_vector_table__=1")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Wl,--start-group")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -lnosys")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -lm")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -lc")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -lgcc")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Wl,--end-group")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} --specs=nano.specs")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -lm")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Wall")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -fno-common")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -ffunction-sections")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -fdata-sections")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -ffreestanding")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -fno-builtin")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Os")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -mthumb")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -mapcs")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} --gc-sections")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -static")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -z")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} muldefs")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -g")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} --defsym=__ram_vector_table__=1")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Wl,--start-group")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -lnosys")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -lm")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -lc")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -lgcc")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Wl,--end-group")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} --specs=nano.specs")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -lm")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Wall")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fno-common")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -ffunction-sections")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fdata-sections")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -ffreestanding")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fno-builtin")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Os")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -mthumb")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -mapcs")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} --gc-sections")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -static")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -z")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} muldefs")

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/devices)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/devices/MKL27Z644/include)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/devices/MKL27Z644/startup)

include_directories(${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z)

include_directories(${ProjDirPath}/../../../../bsp/freescale/common/sgtl5000)

include_directories(${ProjDirPath}/../../../../bsp/freescale/common/phyksz8041)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/system/src/clock/MKL27Z644)

include_directories(${ProjDirPath}/../../../../bsp/freescale/rt_app)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/drivers/inc)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/hal/inc)

include_directories(${ProjDirPath}/../../../../bsp/freescale/rtos)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/osa/inc)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/CMSIS/Include)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/system/inc)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/utilities/inc)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/utilities/src)

include_directories(${ProjDirPath}/../../../../components/drivers/include/drivers)

include_directories(${ProjDirPath}/../../../../components/drivers/include)

include_directories(${ProjDirPath}/../../../../bsp/freescale/driver_wrapper/inc)

include_directories(${ProjDirPath}/../../../../components/finsh)

include_directories(${ProjDirPath}/../../../../include)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/devices)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/devices/MKL27Z644/include)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/devices/MKL27Z644/startup)

include_directories(${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z)

include_directories(${ProjDirPath}/../../../../bsp/freescale/common/sgtl5000)

include_directories(${ProjDirPath}/../../../../bsp/freescale/common/phyksz8041)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/system/src/clock/MKL27Z644)

include_directories(${ProjDirPath}/../../../../bsp/freescale/rt_app)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/drivers/inc)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/hal/inc)

include_directories(${ProjDirPath}/../../../../bsp/freescale/rtos)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/osa/inc)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/CMSIS/Include)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/system/inc)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/utilities/inc)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/utilities/src)

include_directories(${ProjDirPath}/../../../../components/drivers/include/drivers)

include_directories(${ProjDirPath}/../../../../components/drivers/include)

include_directories(${ProjDirPath}/../../../../bsp/freescale/driver_wrapper/inc)

include_directories(${ProjDirPath}/../../../../components/finsh)

include_directories(${ProjDirPath}/../../../../include)

add_executable(rt_thread_demo.elf 
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/MKL27Z644/startup/gcc/startup_MKL27Z644.S"
"${ProjDirPath}/../../../../libcpu/arm/cortex-m0/context_gcc.S"
"${ProjDirPath}/../../../../bsp/freescale/driver_wrapper/uart/drv_uart.c"
"${ProjDirPath}/../../../../bsp/freescale/driver_wrapper/inc/drv_uart.h"
"${ProjDirPath}/../../../../bsp/freescale/driver_wrapper/uart/fsl_uart_irq_rt.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/MKL27Z644/startup/system_MKL27Z644.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/startup.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/startup.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/gpio_pins.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/gpio_pins.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/board.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/board.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/pin_mux.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/pin_mux.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/rtconfig.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/MKL27Z644/startup/system_MKL27Z644.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/startup.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/startup.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/gpio_pins.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/gpio_pins.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/board.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/board.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/pin_mux.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/pin_mux.h"
"${ProjDirPath}/../../../../components/drivers/src/completion.c"
"${ProjDirPath}/../../../../components/drivers/src/pipe.c"
"${ProjDirPath}/../../../../components/drivers/src/portal.c"
"${ProjDirPath}/../../../../components/drivers/src/ringbuffer.c"
"${ProjDirPath}/../../../../components/drivers/src/workqueue.c"
"${ProjDirPath}/../../../../components/drivers/src/dataqueue.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/MKL27Z644/startup/system_MKL27Z644.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/startup.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/startup.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/gpio_pins.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/gpio_pins.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/board.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/board.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/pin_mux.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/pin_mux.h"
"${ProjDirPath}/../../../../components/finsh/cmd.c"
"${ProjDirPath}/../../../../components/finsh/finsh.h"
"${ProjDirPath}/../../../../components/finsh/finsh_compiler.c"
"${ProjDirPath}/../../../../components/finsh/finsh_error.c"
"${ProjDirPath}/../../../../components/finsh/finsh_error.h"
"${ProjDirPath}/../../../../components/finsh/finsh_heap.c"
"${ProjDirPath}/../../../../components/finsh/finsh_heap.h"
"${ProjDirPath}/../../../../components/finsh/finsh_init.c"
"${ProjDirPath}/../../../../components/finsh/finsh_node.c"
"${ProjDirPath}/../../../../components/finsh/finsh_node.h"
"${ProjDirPath}/../../../../components/finsh/finsh_ops.c"
"${ProjDirPath}/../../../../components/finsh/finsh_ops.h"
"${ProjDirPath}/../../../../components/finsh/finsh_parser.c"
"${ProjDirPath}/../../../../components/finsh/finsh_parser.h"
"${ProjDirPath}/../../../../components/finsh/finsh_token.c"
"${ProjDirPath}/../../../../components/finsh/finsh_token.h"
"${ProjDirPath}/../../../../components/finsh/finsh_var.c"
"${ProjDirPath}/../../../../components/finsh/finsh_var.h"
"${ProjDirPath}/../../../../components/finsh/finsh_vm.c"
"${ProjDirPath}/../../../../components/finsh/finsh_vm.h"
"${ProjDirPath}/../../../../components/finsh/msh.c"
"${ProjDirPath}/../../../../components/finsh/msh.h"
"${ProjDirPath}/../../../../components/finsh/msh_cmd.c"
"${ProjDirPath}/../../../../components/finsh/shell.c"
"${ProjDirPath}/../../../../components/finsh/shell.h"
"${ProjDirPath}/../../../../components/finsh/symbol.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/MKL27Z644/startup/system_MKL27Z644.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/startup.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/startup.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/gpio_pins.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/gpio_pins.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/board.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/board.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/pin_mux.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/pin_mux.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/MKL27Z644/startup/system_MKL27Z644.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/startup.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/startup.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/gpio_pins.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/gpio_pins.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/board.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/board.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/pin_mux.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/pin_mux.h"
"${ProjDirPath}/../../../../components/drivers/serial/serial.c"
"${ProjDirPath}/../../../../components/drivers/include/drivers/serial.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/MKL27Z644/startup/system_MKL27Z644.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/startup.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/startup.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/gpio_pins.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/gpio_pins.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/board.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/board.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/pin_mux.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/pin_mux.h"
"${ProjDirPath}/../../../../src/clock.c"
"${ProjDirPath}/../../../../src/device.c"
"${ProjDirPath}/../../../../src/idle.c"
"${ProjDirPath}/../../../../src/ipc.c"
"${ProjDirPath}/../../../../src/irq.c"
"${ProjDirPath}/../../../../src/kservice.c"
"${ProjDirPath}/../../../../src/mem.c"
"${ProjDirPath}/../../../../src/memheap.c"
"${ProjDirPath}/../../../../src/mempool.c"
"${ProjDirPath}/../../../../src/module.c"
"${ProjDirPath}/../../../../src/object.c"
"${ProjDirPath}/../../../../src/scheduler.c"
"${ProjDirPath}/../../../../src/slab.c"
"${ProjDirPath}/../../../../src/thread.c"
"${ProjDirPath}/../../../../src/timer.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/MKL27Z644/startup/system_MKL27Z644.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/startup.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/startup.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/gpio_pins.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/gpio_pins.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/board.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/board.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/pin_mux.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/pin_mux.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/MKL27Z644/startup/system_MKL27Z644.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/startup.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/startup.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/gpio_pins.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/gpio_pins.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/board.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/board.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/pin_mux.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/pin_mux.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/utilities/src/fsl_debug_console.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/utilities/inc/fsl_debug_console.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/utilities/src/print_scan.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/utilities/src/print_scan.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/utilities/src/fsl_misc_utilities.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/MKL27Z644/startup/system_MKL27Z644.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/startup.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/startup.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/gpio_pins.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/gpio_pins.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/board.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/board.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/pin_mux.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/pin_mux.h"
"${ProjDirPath}/../../../../bsp/freescale/rt_app/application.c"
"${ProjDirPath}/../../../../bsp/freescale/rt_app/startup_app.c"
"${ProjDirPath}/../../../../bsp/freescale/rt_app/board_app.c"
"${ProjDirPath}/../../../../bsp/freescale/rt_app/board_app.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/MKL27Z644/startup/system_MKL27Z644.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/startup.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/startup.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/gpio_pins.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/gpio_pins.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/board.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/board.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/pin_mux.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/pin_mux.h"
"${ProjDirPath}/../../../../libcpu/arm/cortex-m0/cpuport.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/MKL27Z644/startup/system_MKL27Z644.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/startup.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/startup.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/gpio_pins.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/gpio_pins.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/board.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/board.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/pin_mux.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/pin_mux.h"
"${ProjDirPath}/../../../../libcpu/arm/common/backtrace.c"
"${ProjDirPath}/../../../../libcpu/arm/common/div0.c"
"${ProjDirPath}/../../../../libcpu/arm/common/showmem.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/MKL27Z644/startup/system_MKL27Z644.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/startup.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/devices/startup.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/gpio_pins.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/gpio_pins.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/board.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/board.h"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/pin_mux.c"
"${ProjDirPath}/../../../../bsp/freescale/boards/frdmkl27z/pin_mux.h"
)


set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -T${ProjDirPath}/../../../../bsp/freescale/platform/devices/MKL27Z644/linker/gcc/MKL27Z64xxx4_flash.ld -static")

set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -T${ProjDirPath}/../../../../bsp/freescale/platform/devices/MKL27Z644/linker/gcc/MKL27Z64xxx4_flash.ld -static")

TARGET_LINK_LIBRARIES(rt_thread_demo.elf -Wl,--start-group)
target_link_libraries(rt_thread_demo.elf debug nosys)

target_link_libraries(rt_thread_demo.elf debug m)

target_link_libraries(rt_thread_demo.elf debug c)

target_link_libraries(rt_thread_demo.elf debug gcc)

target_link_libraries(rt_thread_demo.elf optimized nosys)

target_link_libraries(rt_thread_demo.elf optimized m)

target_link_libraries(rt_thread_demo.elf optimized c)

target_link_libraries(rt_thread_demo.elf optimized gcc)

TARGET_LINK_LIBRARIES(rt_thread_demo.elf -Wl,--end-group)

# BIN AND HEX
ADD_CUSTOM_COMMAND(TARGET rt_thread_demo.elf POST_BUILD COMMAND ${CMAKE_OBJCOPY}
-Oihex ${EXECUTABLE_OUTPUT_PATH}/rt_thread_demo.elf ${EXECUTABLE_OUTPUT_PATH}/rt_thread_demo.hex)
ADD_CUSTOM_COMMAND(TARGET rt_thread_demo.elf POST_BUILD COMMAND ${CMAKE_OBJCOPY}
-Obinary ${EXECUTABLE_OUTPUT_PATH}/rt_thread_demo.elf ${EXECUTABLE_OUTPUT_PATH}/rt_thread_demo.bin)
