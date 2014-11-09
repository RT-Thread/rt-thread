#include "cpuconfig.h"

//#include "iorx62n.h"
    EXTERN _rt_thread_switch_interrupt_flag
    EXTERN _rt_interrupt_from_thread
    EXTERN _rt_interrupt_to_thread
    EXTERN _rt_hw_hard_fault_exception
    EXTERN _rt_hw_cpu_shutdown 
    
    /*PUBLIC _Interrupt_SWINT*/
    PUBLIC ___interrupt_27
    PUBLIC ___interrupt_0
    RSEG CODE:CODE(4)

;/*
; * rt_base_t rt_hw_interrupt_disable();
; */
    PUBLIC _rt_hw_interrupt_disable
_rt_hw_interrupt_disable:
     MVTIPL      #MAX_SYSCALL_INTERRUPT_PRIORITY
     RTS

;/*
; * void rt_hw_interrupt_enable(rt_base_t level);
; */
    PUBLIC  _rt_hw_interrupt_enable
_rt_hw_interrupt_enable:
     MVTIPL     #KERNEL_INTERRUPT_PRIORITY
     RTS

; r0 --> swith from thread stack
; r1 --> swith to thread stack
; psr, pc, lr, r12, r3, r2, r1, r0 are pushed into [from] stack
/* 重定义软件中断函数*/
___interrupt_27:
/* 禁止中断的方法其实就是将优先级提到最高*/
/* 重新使能中断*/
    SETPSW   I
    MVTIPL   #MAX_SYSCALL_INTERRUPT_PRIORITY
    PUSH.L   R15

/* 判断rt_thread_switch_interrupt_flag是否为0，如果为0就是说不是切换任务*/
    MOV.L    #_rt_thread_switch_interrupt_flag, R15
    MOV.L    [ R15 ], R15
    CMP      #0, R15
    BEQ      notask_exit
/* 将rt_thread_switch_interrupt_flag清零*/
    MOV.L    #_rt_thread_switch_interrupt_flag, R15
    MOV.L    #0, [ R15 ]

/* 如果原来线程为空就不用保存寄存器*/
    MOV.L    #_rt_interrupt_from_thread, R15
    MOV.L    [ R15 ], R15
    CMP      #0, R15
    BEQ      need_modify_isp
    /*保存几个CPU寄存器*/
    /* 读取CPU栈指针*/
    MVFC     USP, R15
    /* 将栈指针移动到保存数据开始的地方*/
    SUB      #12, R15
    MVTC     R15, USP
    /* 拷贝数据*/
    MOV.L    [ R0 ], [ R15 ] ;PSW
    MOV.L    4[ R0 ], 4[ R15 ];PC
    MOV.L    8[ R0 ], 8[ R15 ] ;R15

    /*移动栈指针到它的新位置*/
    ADD      #12, R0
/*切换到用户栈*/
    SETPSW   U
    /* 将寄存器保存到当前的新位置*/
    PUSHM    R1-R14
    MVFC     FPSW, R15
    PUSH.L   R15
    MVFACHI  R15
    PUSH.L   R15
    MVFACMI  R15 ; Middle order word.
    SHLL     #16, R15 ; Shifted left as it is restored to the low orde  r w
    PUSH.L   R15
    /*将栈指针保存到rt_thread_from中*/
    MOV.L    #_rt_interrupt_from_thread, R15
    MOV.L    [ R15 ], R15
    MOV.L    R0, [ R15 ]
    BRA      swtich_to_thread
need_modify_isp:
/*  读取中断栈的指针*/
    MVFC     ISP, R15                
    ADD      #12, R15
    MVTC     R15, ISP
swtich_to_thread:
/* 切换到新任务*/
/* 移动栈指针到新任务栈*/
    SETPSW   U
    MOV.L    #_rt_interrupt_to_thread, R15
    MOV.L    [ R15 ], R15
    MOV.L    [ R15 ], R0
   /* 新任务的数据从栈中提出来*/
    POP      R15
    MVTACLO  R15
    POP      R15
    MVTACHI  R15
    POP      R15
    MVTC     R15, FPSW
    POPM     R1-R15
    BRA      pendsv_exit
/*这里是中断栈用的*/
notask_exit:
/* 一开始只弹了这三个寄存器*/
    POP     R15
pendsv_exit:

    /* 重新打开中断*/
     MVTIPL     #KERNEL_INTERRUPT_PRIORITY
     RTE
     NOP
     NOP
/*异常中断*/ 
___interrupt_0:
    PUSH.L   R15
    /*保存几个CPU寄存器*/
    /* 读取CPU栈指针*/
    MVFC     USP, R15
    /* 将栈指针移动到保存数据R1-R14开始的地方*/
    SUB      #12, R15
    MVTC     R15, USP
    /* 拷贝数据*/

    MOV.L    [ R0 ], [ R15 ] ;PSW
    MOV.L    4[ R0 ], 4[ R15 ];PC
    MOV.L    8[ R0 ], 8[ R15 ] ;R15

    /*移动栈指针到它的新位置*/
    ADD      #12, R0
		/*切换到用户栈*/
    SETPSW   U
    /* 将寄存器保存到当前的新位置*/
    PUSHM    R1-R14
    MVFC     FPSW, R15
    PUSH.L   R15
    MVFACHI  R15
    PUSH.L   R15
    MVFACMI  R15 ; Middle order word.
    SHLL     #16, R15 ; Shifted left as it is restored to the low orde  r w
    PUSH.L   R15
    /*将栈指针保存到R1作为参数中*/
     MOV.L    R0, R1
     BRA _rt_hw_hard_fault_exception   
     BRA _rt_hw_cpu_shutdown 
     RTE
     NOP
     NOP
     END

