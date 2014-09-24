/*
 * CORTEXM GDB support
 * arch-specific portion of GDB stub
 * 
 * File      : arch_gdb.h(cortexm)
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-07-04     wzyy2      first version
 */
#ifndef __ARM_GDB_H__
#define __ARM_GDB_H__ 

#include <rtthread.h>

#ifndef RT_GDB_HAVE_HWBP
    #define RT_GDB_HAVE_HWBP 1
#endif
#ifndef RT_GDB_HAVE_SWBP
    #define RT_GDB_HAVE_SWBP 0
#endif

#ifndef GDB_CORTEXM_PRIORITY_MAX 
    #define GDB_CORTEXM_PRIORITY_MAX  (1 << 6)
#endif

#define GDB_DATA_ACCESS

#define BREAK_INSTR_SIZE 4
#define ARM_GP_REGS	    	16
#define ARM_FP_REGS	    	8
#define ARM_EXTRA_REGS		2
#define GDB_MAX_REGS		(ARM_GP_REGS + (ARM_FP_REGS * 3) + ARM_EXTRA_REGS)
#define NUMREGBYTES	    	(GDB_MAX_REGS << 2)

#define HBP_NUM     6   //Max hardware breakpoint
#define HWP_NUM     4   //Max hardware watchpoint

//#define BUFMAX			((NUMREGBYTES << 1) + 10)
#define BUFMAX			400

#define GDB_DEBUG_REG_BASE      0xE000EDF0
#define GDB_DEBUG_REG_DHSR      0x00
#define GDB_DEBUG_REG_DCRSR      0x04
#define GDB_DEBUG_REG_DCRDR      0x08
#define GDB_DEBUG_REG_DEMCR      0x0c

#define GDB_DEBUG_REG_DEMCR_MON_EN      (1UL << 16)
#define GDB_DEBUG_REG_DEMCR_MON_PEND      (1UL << 17)
#define GDB_DEBUG_REG_DEMCR_MON_STEP      (1UL << 18)
#define GDB_DEBUG_REG_DEMCR_TRCENA      (1UL << 24)

#define GDB_NVIC_REG_BASE       0xE000E000
#define GDB_NVIC_REG_SHCSR      0xD24
#define GDB_NVIC_REG_DFSR       0xD30

#define GDB_NVIC_REG_SHCSR_MEMFAULTENA   (1 << 16)

#define GDB_FPB_REG_BASE       0xE0002000
#define GDB_FPB_REG_CTRL       0x0
#define GDB_FPB_REG_REMAP      0x4
#define GDB_FPB_REG_COMP       0x8

#define GDB_FPB_REG_CTRL_KEY        (1UL << 1) 
#define GDB_FPB_REG_CTRL_ENABLE      1
#define GDB_FPB_REG_COMP_ENABLE      1
#define GDB_FPB_REG_COMP_ADDR       (((1UL << 29) -1) << 2)
#define GDB_FPB_REG_COMP_REPLACE       (((1UL << 32) -1) << 30)

#define GDB_DWT_REG_BASE       0xE0001000
#define GDB_DWT_REG_CTRL       0x0
#define GDB_DWT_REG_COMP       0x20
#define GDB_DWT_REG_MASK       0x24
#define GDB_DWT_REG_FUNCTION       0x28

#define GDB_DWT_REG_FUNCTION_FUC    (((1UL << 4) -1) << 0)




enum regnames {
    GDB_R0,     /*0*/
    GDB_R1,     /*1*/
    GDB_R2,     /*2*/
    GDB_R3,     /*3*/
    GDB_R4,     /*4*/
    GDB_R5,     /*5*/
    GDB_R6,     /*6*/
    GDB_R7,     /*7*/
    GDB_R8,     /*8*/
    GDB_R9,     /*9*/
    GDB_R10,    /*10*/
    GDB_FP,     /*11*/
    GDB_IP,     /*12*/
    GDB_SPT,    /*13*/
    GDB_LR,     /*14*/
    GDB_PC,     /*15*/
    GDB_F0,     /*16*/
    GDB_F1,     /*17*/
    GDB_F2,     /*18*/
    GDB_F3,     /*19*/
    GDB_F4,     /*20*/
    GDB_F5,     /*21*/
    GDB_F6,     /*22*/
    GDB_F7,     /*23*/
    GDB_FPS,     /*24*/
    GDB_CPSR = GDB_MAX_REGS-1 
};

typedef struct 
{
    unsigned long           type;           // State type
    unsigned long           vector;         // Exception vector number
    unsigned long           basepri;        // BASEPRI

    unsigned long           r4;       // Remaining CPU registers
    unsigned long           r5;       // Remaining CPU registers
    unsigned long           r6;       // Remaining CPU registers
    unsigned long           r7;       // Remaining CPU registers
    unsigned long           r8;       // Remaining CPU registers
    unsigned long           r9;       // Remaining CPU registers
    unsigned long           r10;       // Remaining CPU registers
    unsigned long           r11;       // Remaining CPU registers
    unsigned long           sp;       // Remaining CPU registers

    unsigned long           xlr;            // Exception return LR
    // The following are saved and restored automatically by the CPU
    // for exceptions or interrupts.
    unsigned long           r0;
    unsigned long           r1;
    unsigned long           r2;
    unsigned long           r3;
    unsigned long           r12;
    unsigned long           lr;
    unsigned long           pc;
    unsigned long           psr;
} Gdb_SavedRegisters;

/* arch */
extern struct gdb_arch		arch_gdb_ops;
void gdb_breakpoint();
void gdb_get_register(unsigned long *gdb_regs);
void gdb_put_register(unsigned long *gdb_regs);
void gdb_set_register(void *hw_regs);
int gdb_arch_handle_exception(char *remcom_in_buffer,
                              char *remcom_out_buffer);

int gdb_permit_data_access(unsigned long addr, unsigned long count);
void gdb_arch_exit();
void gdb_arch_late();

#endif /* __CORTEXM_GDB_H__ */
