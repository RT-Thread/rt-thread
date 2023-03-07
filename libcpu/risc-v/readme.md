###  RV32移植指南

#### 1.概述

为了简化32位RISC-V架构内核移植RT-Thread的流程，RT-Thread提供一分通用代码于common文件夹

|       文件名        |            文件内容            |
| :-----------------: | :----------------------------: |
|    context_gcc.S    | 开关全局中断，线程上下文切换等 |
|      cpuport.c      |  线程栈初始化，软件中断触发等  |
|      cpuport.h      |        数据加载写入指令        |
|   interrupt_gcc.S   |        线程间上下文切换        |
|     riscv-ops.h     |       控制状态寄存器读写       |
| rt_hw_stack_frame.h |           线程栈格式           |
|    trap_common.c    |     中断注册，中断查询分发     |

#### 2.移植接口

（1）软件中断触发函数，通常向量管理中断方式需实现该函数，非向量中断管理方式一般不需要

```c
void rt_trigger_software_interrupt(void)
```

（2）保存上文后执行函数，该函数向量中断与非向量中断均需实现

```c
void rt_hw_do_after_save_above(void)
```

该函数需要实现的工作如下：

步骤1：将函数返回地址(ra)保存栈中

步骤2：加载中断处理函数的入口参数

步骤3：调用中断处理函数（新移植的BSP推荐使用RT-Thread common_trap.c文件中提供的统一中断处理函数:rt_rv32_system_irq_handler）

步骤4：从栈中加载返回地址(ra)，返回至SW_handler函数

#### 3.准备工作

- 准备一个基础的裸机工程，需具备以下条件：

  - 明确中断管理方式(向量中断/非向量中断)

  - 实现系统节拍定时器中断
  - 实现一个串口中断

#### 4.移植步骤

- 步骤一：配置中断管理入口，相关中断入口函数位于**common/interrupt_gcc.S**,入口函数为**SW_handler**

  - 根据使用的中断管理方式，执行下述操作

    - 向量中断管理方式

      > 通常会使用一个软件中断（该中断的优先级被配置为最低）作为在中断中触发上下文切换的入口函数。SW_handler在此仅作为触发软件中断时的入口参数，其他类型中断触发时跳转至各自的中断入口函数。
      >

      移植方法:修改原有的中断向量表中软件中断所在位置，将原有软件中断函数名修改为**SW_handler**

      示例（ch32系列）：

      ```assembly
      _vector_base:
          .option norvc;
          .word   _start
           ...
          .word   SW_handler    /* 将这里原来放置的软件中断函数名修改为SW_handler */
      ```

    - 非向量中断

      > 当有中断触发时，会进入一个统一的中断入口函数进行中断查询分发。SW_handler在此处不仅作为作为在中断中触发上下文切换的入口函数，同时承担中断查询分发与执行。
      >

      移植方法:将**SW_handler**的地址加载到保存统一中断入口地址的寄存器（通常为mtevc，具体名称需要根据具体的内核指定）

      示例(hpm6750系列):

      ```assembly
          la t0, SW_handler
          csrw mtvec, t0
      ```

- 步骤二：修改链接脚本,在中断栈顶名称后添加示例代码

  - 将下述代码放置于链接脚本中中断栈顶名称之后

    ```assembly
    PROVIDE( __rt_rvstack = . );
    ```

  - 示例（core-v-mcu链接脚本）：

    ```assembly
      .stack : ALIGN(16)
      {
        stack_start = .;
        __stack_bottom = .;
        . += __stack_size;
        __stack_top = .;
        PROVIDE( __rt_rvstack = . );//移植时添加 
        stack = .;
      } > L2
    ```
  
> __stack_top为core-v-mcu工程的中断栈顶名  不同工程此处的名称可能不一致 按上述方法将给出的代码放到具体工程链接脚本中断栈顶名称之后即可。

- 步骤三：实现在中断上下文切换的函数接口

  <font color=red>RISC-V架构的内核通常采用非向量中断的管理方式，为了进一步降低难度，针对非向量模式的中断管理方式，common文件夹中的trap_common.c为用户提供了一套统一的中断查询分发、中断入口函数注册以及中断初始化函数，在rthw.h中声明，对于移植一个新的RV32内核，若采用非向量中断管理的方式，推荐使用方式一，若采用向量中断管理方式或针对中断的处理有专门的优化时推荐使用方式二,期望采用原有裸机工程的统一的中断查询与处理函数也可使用方式二。以下是两种实现方式的示例：</font>

  方式一：面向非向量中断管理方式(例:core-v-mcu)

  在RT-Thread的BSP框架中的board文件夹创建一个统一名称的汇编文件：trap_gcc.S,将该文件添加到编译环境即可，该函数的实现如下(用户直接使用，无需修改）：

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

  随后用户仅需调用rt_hw_interrupt_init进行初始化，再将中断入口函数通过rt_hw_interrupt_install函数注册即可，注册的中断入口函数为裸机原有的中断入口函数，示例代码如下(相关设备的中断入口函数注册之前不可使用该设备):

  ```c
        rt_hw_interrupt_init();//中断入口函数初始化 
        rt_hw_interrupt_install(0x7, timer_irq_handler, RT_NULL, "timerirq");//注册系统定时器中断入口函数
        rt_hw_interrupt_install(0xb, fc_soc_event_handler1, RT_NULL, "eventirq");//注册外部中断入口函数
  ```

  方式二：面向向量中断管理方式(例:CH32)与针对中断管理有专门优化的内核(例:GD32)

  - 向量中断(可参考ch32)

    在RT-Thread的BSP框架中的board文件夹创建需要的文件，实现下述的两个函数：
    
    - 在void rt_trigger_software_interrupt(void) 中实现触发软件中断的操作
    
    - 在void rt_hw_do_after_save_above(void) 中实现触发软件中断之后的工作，通常是清除软件中断置位标志位或类似操作
  
  - 非向量中断(期望采用原有裸机工程的统一的中断查询与处理函数)
  
  在RT-Thread的BSP框架中的board文件夹创建一个统一名称的汇编文件：trap_gcc.S,将该文件添加到编译环境即可，此步骤与方式一提供的方法相似，仅在调用中断处理函数以及传递的参数不同，需要根据具体的移植工程实现，方式二下该函数的实现如下：
  
  示例代码：
  
  ```assembly
    #include "cpuport.h"
    
    	.globl rt_hw_do_after_save_above
    	.type rt_hw_do_after_save_above,@function
    rt_hw_do_after_save_above:
    	addi  sp, sp,  -4 // 移动栈指针 
        STORE ra,  0 * REGBYTES(sp) // 将返回地址寄存器值保存至栈中
            
        csrr  a0, mscratch// 加载函数入口参数
        call  trap_entry// 调用中断处理函数
            
        LOAD  ra,  0 * REGBYTES(sp) // 从栈中恢复返回地址寄存器值
        addi  sp, sp,  4// 移动栈指针 
        ret	// 返回SW_handler
  ```
  
    trap_entry为用户实现的中断源查询分发的函数，在移植时仅需要将该函数名修改为用户的中断查询分发函数即可。



#### 5.验证

- 创建一个静态线程，在线程中调用RT-Thread提供的与系统时基相关函数接口，例如rt_thread_mdelay，调试观察系统是否可以正常运行
- 移植RT-Thread的shell进一步验证系统是否移植成功

