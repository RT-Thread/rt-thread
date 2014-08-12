/*
 * ARM GDB support
 * arch-specific portion of GDB stub
 * 
 * File      : arch_gdb.h(arm)
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
    #define RT_GDB_HAVE_HWBP 0
#endif
#ifndef RT_GDB_HAVE_SWBP
    #define RT_GDB_HAVE_SWBP 1
#endif


#if RT_GDB_HAVE_HWBP
    #error GDB:No hardware_breakpoint support
#endif


/*
 * By doing this as an undefined instruction trap, we force a mode
 * switch from SVC to UND mode, allowing us to save full kernel state.
 * We also define a GDB_COMPILED_BREAK which can be used to compile
 * in breakpoints. 
 */
#define BREAK_INSTR_SIZE	4
#define GDB_BREAKINST		0xe7ffdefe
#define GDB_COMPILED_BREAK	0xe7ffdeff
#define CACHE_FLUSH_IS_SAFE	1

#define ARM_GP_REGS	    	16
#define ARM_FP_REGS	    	8
#define ARM_EXTRA_REGS		2
#define GDB_MAX_REGS		(ARM_GP_REGS + (ARM_FP_REGS * 3) + ARM_EXTRA_REGS)
#define NUMREGBYTES	    	(GDB_MAX_REGS << 2)


//#define BUFMAX			((NUMREGBYTES << 1) + 10)
#define BUFMAX			400

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
    GDB_CPSR = GDB_MAX_REGS-1 
};

/* arch */
extern struct gdb_arch		arch_gdb_ops;
void gdb_breakpoint();
void gdb_get_register(unsigned long *gdb_regs);
void gdb_put_register(unsigned long *gdb_regs);
void gdb_set_register(void *hw_regs);
int gdb_arch_handle_exception(char *remcom_in_buffer,
                              char *remcom_out_buffer);
void gdb_flush_icache_range(unsigned long start, unsigned long end);
int gdb_undef_hook(void *regs);

int gdb_handle_exception(int signo, void *regs);

#endif /* __ARM_GDB_H__ */
