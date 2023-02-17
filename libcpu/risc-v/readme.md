### RV32移植指南

#### 准备工作

- 准备一个基础的裸机工程，需具备以下条件：

  - 明确中断管理方式(向量中断/非向量中断)

  - 实现系统节拍定时器中断
  - 实现一个串口中断

#### 移植步骤

- 步骤一：配置中断管理入口，相关中断入口函数位于**common_trap/interrupt_gcc.S**,入口函数为**SW_handler**

  - 中断管理方式，根据具体使用的中断管理方式，选择对应的移植方式

    - 向量中断

      > 通常会使用一个软件中断（该中断的优先级被配置为最低）作为在中断中触发上下文切换的入口函数
      >
      > SW_handler在此仅作为触发软件中断时的入口参数，其他类型中断触发时跳转至各自的中断入口函数

      - 方法:修改原有的中断向量表中软件中断所在位置，将原有软件中断函数名修改为**SW_handler**

    - 非向量中断

      > 当有中断触发时，会进入一个统一的中断入口函数进行中断查询分发.
      >
      > SW_handler在此处不仅作为作为在中断中触发上下文切换的入口函数，同时承担中断查询分发与执行

      - 方法:将**SW_handler**的地址加载到保存统一中断入口地址的寄存器

- 步骤二：在系统启动前，将中断栈加载至**mscratch**寄存器

  - 一般情况可将该部分代码添加至启动文件中

  - 示例代码:

    ```assembly
        la t0, _sp
        csrw mscratch,t0
    ```

  > _sp为中断栈顶地址 不同内核的中断栈顶地址名称位于链接脚本中 

- 步骤三：实现在中断上下文切换的函数接口

  > 该步骤提供俩个函数接口，函数均采用弱定义的方式，用户需重新实现下述俩个函数

  ```c
  void rt_trigger_software_interrupt(void)
  ```

  ```c
  void rt_hw_do_after_save_above(void)
  ```

  - 在当前路径下新建一个文件夹，用于放置具体内核相关的文件

  - 向量中断(可参考ch32)

    - 在刚才新建的文件夹下，创建一个c文件，用于实现上述提供的俩个函数接口

    - 向量中断管理方式下，上述的俩个函数接口通常均需实现。
      - 在void rt_trigger_software_interrupt(void) 中实现触发软件中断的操作
      - 在void rt_hw_do_after_save_above(void)中实现触发软件中断后的工作，通常是需要做清除软件中断置位标志位的操作

  - 非向量中断(可参考cv32e40p)

    - 在刚才新建的文件夹下，创建一个汇编文件，用于实现上述提供的函数接口
    - 对于非向量中断的管理方式仅需实现rt_hw_do_after_save_above函数即可

    示例代码：

    ```assembly
    #include "cpuport.h"
    
    	.globl rt_hw_do_after_save_above
    	.type rt_hw_do_after_save_above,@function
    rt_hw_do_after_save_above:
    	addi  sp, sp,  -4
        STORE ra,  0 * REGBYTES(sp)
            
        csrr  a0, mscratch
        call  trap_entry
            
        LOAD  ra,  0 * REGBYTES(sp)
        addi  sp, sp,  4
        ret
    ```

    trap_entry为用户实现的中断源查询分发的函数，在移植时仅需要将该函数名修改为用户的中断查询分发函数即可。

  - 通用中断分发函数

    RISC-V架构的内核通常采用非向量中断的管理方式，所以为了进一步降低难度，为用户提供了一个统一的中断查询分发函数，该部分内容位于common文件夹的trap_common.c文件中，对于移植一个新的RV32内核推荐使用RT-Thread提供的统一函数接口，上述非向量中断中需要实现的汇编代码便可以完全使用下述代码：

    ```assembly
    #include "cpuport.h"
    
    	.globl rt_hw_do_after_save_above
    	.type rt_hw_do_after_save_above,@function
    rt_hw_do_after_save_above:
    	addi  sp, sp,  -4
        STORE ra,  0 * REGBYTES(sp)
    
        csrr  a0, mcause
        csrr  a1, mepc
        mv    a2, sp
        call  rt_rv32_system_irq_handler
    
        LOAD  ra,  0 * REGBYTES(sp)
        addi  sp, sp,  4
        ret
    ```

    随后用户仅需调用rt_hw_interrupt_init进行初始化，然后将中断入口函数通过rt_hw_interrupt_install函数注册即可，示例代码如下:

    ```c
    rt_hw_interrupt_install(0x7, timer_irq_handler, RT_NULL, "timerirq");
    ```

  >注：core-v-mcu工程均采用RT-Thread提供的移植抽象层接口，移植时可以参考该工程

#### 验证

- 创建一个静态线程，在线程中调用RT-Thread提供的与系统时基相关函数接口，例如rt_thread_mdelay，调试观察系统是否可以正常运行
- 移植RT-Thread的shell进一步验证系统是否移植成功

