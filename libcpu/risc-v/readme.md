### RV32移植指南

#### 1.概述

为了简化RISC-V架构内核移植RT-Thread的流程，RT-Thread提供一分通用代码于common文件夹

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

（1）软件中断触发函数，通常向量管理中断需实现该函数，非向量中断管理方式一般不需要

```c
void rt_trigger_software_interrupt(void)
```

（2）保存上文后执行函数，该函数向量中断与非向量中断均需实现

```c
void rt_hw_do_after_save_above(void)
```

#### 3.准备工作

- 准备一个基础的裸机工程，需具备以下条件：

  - 明确中断管理方式(向量中断/非向量中断)

  - 实现系统节拍定时器中断
  - 实现一个串口中断

#### 4.移植步骤

<font color=red>对于新移植的RISC-V 32位内核，若采用非向量中断管理方式，推荐使用common中的文件，除了下述步骤中必要的修改以及中断初始化与注册步骤外，用户仅需拷贝一份cv32e40p移植文件，重命名为具体内核名称即可 。</font>

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

  - 将下述代码放置于链接脚本中中断栈顶名之后

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

  新建一个文件夹，并以内核命名

  （一）采用原有裸机的中断入口处理函数

  - 向量中断(可参考ch32)

    （1）在刚才新建的文件夹下，创建一个c文件，实现上文提供的俩个函数接口

    （2）实现上述俩个函数接口
    - 在void rt_trigger_software_interrupt(void) 中实现触发软件中断的操作
    - 在void rt_hw_do_after_save_above(void)中实现触发软件中断之后的工作，通常是清除软件中断置位标志位或类似操作

  - 非向量中断(可参考cv32e40p)

    - 在刚才新建的文件夹下，创建一个汇编文件，实现上述提供的函数接口
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

  （二）采用RT-Thread通用中断分发函数

  - 

    RISC-V架构的内核通常采用非向量中断的管理方式，为了进一步降低难度，为用户提供了一个统一的中断查询分发函数，该部分内容位于common文件夹的trap_common.c文件中，对于移植一个新的RV32内核推荐使用RT-Thread提供的统一函数接口。

    RT-Thread通用中断分发函数:
    
    ```c
    rt_weak void rt_rv32_system_irq_handler(rt_uint32_t mcause)
    {
        rt_uint32_t mscratch = read_csr(0x340);
        rt_uint32_t irq_id = (mcause & 0x1F);
        rt_uint32_t exception = !(mcause & 0x80000000);
        if(exception)
        {
            s_stack_frame = (rt_hw_stack_frame_t *)mscratch;
            rt_show_stack_frame();
        }
        else
        {
            rv32irq_table[irq_id].handler(irq_id, rv32irq_table[irq_id].param);
        }
    }
  ```
    
  采用RT-Thread提供的通用中断查询分发函数时，移植文件可不用任何修改直接使用下方示例代码：
    
    (或直接拷贝一份cv32e40p移植文件，重命名为具体内核名称即可)
    
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
    
    随后用户仅需调用rt_hw_interrupt_init进行初始化，然后将中断入口函数通过rt_hw_interrupt_install函数注册即可，注册的中断入口函数为裸机原有的中断入口函数，示例代码如下:
    
    ```c
        rt_hw_interrupt_init();
        rt_hw_interrupt_install(0x7, timer_irq_handler, RT_NULL, "timerirq");
        rt_hw_interrupt_install(0xb, fc_soc_event_handler1, RT_NULL, "eventirq");
    ```


#### 5.验证

- 创建一个静态线程，在线程中调用RT-Thread提供的与系统时基相关函数接口，例如rt_thread_mdelay，调试观察系统是否可以正常运行
- 移植RT-Thread的shell进一步验证系统是否移植成功

