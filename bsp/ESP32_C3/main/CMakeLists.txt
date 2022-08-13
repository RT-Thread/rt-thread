idf_component_register(SRCS "board.c" "main.c"
                    "drv_gpio.c"
                    "drv_uart.c"
                    "../../../libcpu/risc-v/common/cpuport.c"
                    "../../../libcpu/risc-v/common/context_gcc.S"
                    "../../../src/components.c"
                    "../../../src/scheduler.c"
                    "../../../src/device.c"
                    "../../../src/clock.c"
                    "../../../src/irq.c"
                    "../../../src/thread.c"
                    "../../../src/mempool.c"
                    "../../../src/ipc.c"
                    "../../../src/mem.c"
                    "../../../src/object.c"
                    "../../../src/idle.c"
                    "../../../src/timer.c"
                    "../../../src/kservice.c"
                    "../../../src/device.c"
                    "../../../components/drivers/misc/pin.c"
                    "../../../components/drivers/ipc/pipe.c"
                    "../../../components/drivers/ipc/ringblk_buf.c"
                    "../../../components/drivers/ipc/waitqueue.c"
                    "../../../components/drivers/ipc/completion.c"
                    "../../../components/drivers/ipc/dataqueue.c"
                    "../../../components/drivers/ipc/ringbuffer.c"
                    "../../../components/drivers/ipc/workqueue.c"
                    "../../../components/drivers/serial/serial.c"
                    "../../../components/finsh/cmd.c"
                    "../../../components/finsh/msh_file.c"
                    "../../../components/finsh/msh_parse.c"
                    "../../../components/finsh/msh.c"
                    "../../../components/finsh/shell.c"

                    INCLUDE_DIRS 
                    "../../../components/drivers/include/drivers"

                    "../../../components/drivers/include"
                    "../../../components/finsh"
                    "."
                    "../../../include" 
                    "../../../libcpu/risc-v/common" 
                    "../")
ADD_DEFINITIONS(
	-D__RTTHREAD__
)
#TODO
#list(APPEND LINK_FLAGS "-u __rt_init_desc_rt_hw_pin_init")
#set(compile_options "-u __rt_init_desc_rt_hw_pin_init")