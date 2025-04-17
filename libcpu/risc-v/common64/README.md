### RT-Thread RV64支持

#### 1.概述

该目录提供RT-Thread标准版及SMART版本对rv64体系结构支持，其中包括：

|      文件名      |                      文件内容                      |                                                                                     参考标准                                                                                     |
| :---------------: | :------------------------------------------------: | :-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------: |
|   atomic_rv64.c   |                  原子操作实现接口                  |                                                                "A" Extension for Atomic Instructions, Version 2.1                                                                |
|   context_gcc.S   |                   线程上下文切换                   |                                            The RISC-V Instruction Set Manual Volume II: privileged  supervisor-level ISA version 1.12                                            |
|   cpuport_gcc.S   |                    线程统一入口                    |                                                                                                                                                                                  |
|     cpuport.c     |                    线程栈初始化                    |                                                                                                                                                                                  |
|     cpuport.h     | 通用寄存器、浮点、向量寄存器个数定义，内存屏障接口 |                                            The RISC-V Instruction Set Manual Volume II: privileged  supervisor-level ISA version 1.12                                            |
|  interrupt_gcc.S  |          异常/中断处理、全局中断使能/关闭          |                                            The RISC-V Instruction Set Manual Volume II: privileged  supervisor-level ISA version 1.12                                            |
|       io.h       |          以字节、字、双字读、写IO地址接口          |                                                                                                                                                                                  |
|    encoding.h    |                   CSR寄存器定义                   |                                            The RISC-V Instruction Set Manual Volume II: privileged  supervisor-level ISA version 1.12                                            |
| vector_encoding.h |                 vector相关指令定义                 |                                                         RISC-V "V" Standard Extension for Vector Operations, Version 1.0                                                         |
|   ext_context.h   |             浮点/向量上下文保存与恢复             | RISC-V "V" Standard Extension for Vector Operations, Version 1.0                                                 "F" Extension for Single-Precision    Floating-Point Version 2.2 |
|       mmu.c       |               rv64 sv39 mmu管理接口               |                                            The RISC-V Instruction Set Manual Volume II: privileged  supervisor-level ISA version 1.12                                            |
|       mmu.h       |             rv64 sv39 mmu页表相关定义             |                                            The RISC-V Instruction Set Manual Volume II: privileged  supervisor-level ISA version 1.12                                            |
|      asid.c      |                 rv64 mmu asid支持                 |                                            The RISC-V Instruction Set Manual Volume II: privileged  supervisor-level ISA version 1.12                                            |
|    riscv_mmu.c    |             使能/关闭S态访问用户态页表             |                                            The RISC-V Instruction Set Manual Volume II: privileged  supervisor-level ISA version 1.12                                            |
|       sbi.c       |            通过ecall调用SBI相关信息接口            |                                                           RISC-V Supervisor Binary Interface Specification Version 1.0                                                           |
|       sbi.h       |                SBI spec相关接口定义                |                                                           RISC-V Supervisor Binary Interface Specification Version 1.0                                                           |
|      stack.h      |                   线程栈数据定义                   |                                            The RISC-V Instruction Set Manual Volume II: privileged  supervisor-level ISA version 1.12                                            |
|   stackframe.h   |                线程上下文保存/恢复                |                                            The RISC-V Instruction Set Manual Volume II: privileged  supervisor-level ISA version 1.12                                            |
|    syscall_c.c    |                    系统调用处理                    |                                                                                                                                                                                  |
|      tick.c      |              S态时钟初始化及中断处理              |                                                                                                                                                                                  |
|       tlb.h       |                  tlb刷新/无效接口                  |                                            The RISC-V Instruction Set Manual Volume II: privileged  supervisor-level ISA version 1.12                                            |
|      trap.c      |    异常/中断处理，包括中断分发及用户态异常处理    |                                            The RISC-V Instruction Set Manual Volume II: privileged  supervisor-level ISA version 1.12                                            |

#### 2.运行模式配置

| 选项            |  默认值 | 说明                                                                                                 |
| --------------- | --- | ---------------------------------------------------------------------------------------------------- |
| RISCV_S_MODE    | 打开 | 系统启动后是否运行在S态，关闭时系统将运行在M态；目前系统存在bug尚不可直接运行在M态，故此开关必须打开 |
| RT_USING_SMART  | 关闭 | 是否开启RTThread SMART版本，开启后系统运行在S+U态，且会开启MMU页表(satp);关闭时系统仅运行在S态，MMU关闭(satp为bare translation)    |
| ARCH_USING_ASID | 关闭 | MMU是否支持asid                                                                     |

#### 3.移植指南

（1）增加新的CPU支持

创建`libcpu/risc-v/<VENDOR_NAME>/<CPU_NAME>`新目录，同时在`libcpu/risc-v/SConscript`中增加该CPU。

（2）PLIC中断控制器支持

`libcpu/risc-v/virt64/plic.[c|h]`提供了符合《RISC-V Platform-Level Interrupt Controller Specification version 1.0.0 》标准的PLIC中断控制器驱动代码，可作为移植参考。

（3）串口uart支持

目前串口驱动在各bsp目录下，可参考`bsp/qemu-virt64-riscv/driver/drv_uart.[c|h]`