/*
 * CORTEXM GDB support
 * arch-specific portion of GDB stub
 * 
 * File      : cortexm_stub.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-07-04     Wzyy2      first version
 */
#include <rtthread.h>
#include <rthw.h>
#include <gdb_stub.h>

static Gdb_SavedRegisters *regs;
unsigned long single_step_basepri = 0;

void gdb_remove_all_hw_break();
void gdb_enable_hw_debug();
void gdb_disable_hw_debug();
int gdb_set_hw_break(unsigned long, int, enum gdb_bptype);
int gdb_remove_hw_break(unsigned long, int, enum gdb_bptype);

/*struct gdb_arch - Describe architecture specific values.*/
struct gdb_arch arch_gdb_ops = {
	/* Breakpoint instruction: */
    .gdb_bpt_instr		=  {0xfe, 0xde, 0xff, 0xe7},  //Little-Endian
    .flags			= RT_GDB_HAVE_HWBP,
    .set_hw_breakpoint	= gdb_set_hw_break,
    .remove_hw_breakpoint	= gdb_remove_hw_break,
    .remove_all_hw_break	= gdb_remove_all_hw_break
};

static struct hw_breakpoint {
	int		enabled;
	unsigned long		addr;
} breakinfo[HBP_NUM];

static struct hw_watchpoint {
	int		enabled;
	unsigned long		addr;
    int			len;
	enum gdb_bptype		type;
} watchinfo[HWP_NUM];

//The following table defines the memory areas that GDB is allow to touch
static  const struct {
    unsigned long   start;
    unsigned long   end;
} data_access[] =
{
   { 0x20000000,         0x40000000-1}, // On-chip ram
   { 0x60000000,         0xa0000000-1}, // External ram
   { 0x00000000,         0x20000000-1}, // On-chip flash
   { 0x60000000,         0xa0000000-1}, // External flash
   { 0xE0000000,         0x00000000-1}, // cortex-M peripheral
   { 0x40000000,         0x60000000-1}, // mcu peripheral
};


int gdb_permit_data_access(unsigned long addr, unsigned long count)
{
     unsigned char i;

     for (i = 0; i < sizeof(data_access)/sizeof(data_access[0]); i++) { 
         if ((addr >= data_access[i].start) && (addr + count) <= data_access[i].end) {
             return 0;
         }
     }

     return -1;
}

/*we need to block all pending interrupts by swtting basepri
 * before doing the steo
 */
void gdb_single_step()
{
    volatile unsigned long *base;

    //mask all interrupts
    single_step_basepri = regs->basepri;
    regs->basepri = GDB_CORTEXM_PRIORITY_MAX;

    //When MON_EN = 1, this steps the core     
    base = (unsigned long*)(GDB_DEBUG_REG_BASE + GDB_DEBUG_REG_DEMCR);
    *base |= GDB_DEBUG_REG_DEMCR_MON_STEP;

    /* Clear any bits set in DFSR*/
    base = (unsigned long*)(GDB_NVIC_REG_BASE + GDB_NVIC_REG_DFSR);
    *base = 0xffffffff;

}

void gdb_clear_single_step()
{
    volatile unsigned long *base;

    regs->basepri = single_step_basepri;

    /*clear single step*/
    base = (unsigned long*)(GDB_DEBUG_REG_BASE + GDB_DEBUG_REG_DEMCR);
    *base &= ~GDB_DEBUG_REG_DEMCR_MON_STEP;

    // Clear any bits set in DFSR
    base = (unsigned long*)(GDB_NVIC_REG_BASE + GDB_NVIC_REG_DFSR);
    *base = 0xffffffff;

}

/**
 * gdb_breakpoint - generate a breadk
 * It is used to sync up with a debugger and stop progarm
 */
void gdb_breakpoint()
{
    volatile unsigned long *base;

    // Enable the FPB-FLASH PATCH BREAKPOINT 
    base = (unsigned long*)(GDB_FPB_REG_BASE + GDB_FPB_REG_CTRL);
    *base |= GDB_FPB_REG_CTRL_KEY | GDB_FPB_REG_CTRL_ENABLE ;

    base = (unsigned long*)(GDB_DEBUG_REG_BASE + GDB_DEBUG_REG_DEMCR);
     /* 
      * Enable the debug monitor. When enabled, the System handler priority
      * register controls its priority level.
      * If disabled, then all debug events go
      * to Hard fault
      */
    *base |= GDB_DEBUG_REG_DEMCR_MON_EN;

    // Enable DWT
    *base |= GDB_DEBUG_REG_DEMCR_TRCENA ;

    //Fall into debug monitor
    *base |= GDB_DEBUG_REG_DEMCR_MON_PEND;

}

void gdb_set_register(void *hw_regs)
{
    regs = hw_regs;
}

void gdb_get_register(unsigned long *gdb_regs)
{   
    int regno;
    /* Initialize all to zero. */
    for (regno = 0; regno < GDB_MAX_REGS; regno++)
        gdb_regs[regno] = 0;

    gdb_regs[GDB_R0]		= regs->r0;
    gdb_regs[GDB_R1]		= regs->r1;
    gdb_regs[GDB_R2]		= regs->r2;
    gdb_regs[GDB_R3]		= regs->r3;
    gdb_regs[GDB_R4]		= regs->r4;
    gdb_regs[GDB_R5]		= regs->r5;
    gdb_regs[GDB_R6]		= regs->r6;
    gdb_regs[GDB_R7]		= regs->r7;
    gdb_regs[GDB_R8]		= regs->r8;
    gdb_regs[GDB_R9]		= regs->r9;
    gdb_regs[GDB_R10]		= regs->r10;
    gdb_regs[GDB_FP]		= regs->r11;
    gdb_regs[GDB_IP]	    = regs->r12;
    gdb_regs[GDB_SPT]		= regs->sp;
    gdb_regs[GDB_LR]		= regs->lr;
    gdb_regs[GDB_PC]		= regs->pc;
    gdb_regs[GDB_CPSR]  	= regs->psr;

};


void gdb_put_register(unsigned long *gdb_regs)
{
    regs->r0    	= gdb_regs[GDB_R0];
    regs->r1    	= gdb_regs[GDB_R1];
    regs->r2    	= gdb_regs[GDB_R2];
    regs->r3    	= gdb_regs[GDB_R3];

    regs->r4       	= gdb_regs[GDB_R4];
    regs->r5    	= gdb_regs[GDB_R5];
    regs->r6    	= gdb_regs[GDB_R6];
    regs->r7    	= gdb_regs[GDB_R7];
    regs->r8    	= gdb_regs[GDB_R8];
    regs->r9    	= gdb_regs[GDB_R9];
    regs->r10    	= gdb_regs[GDB_R10];
    regs->r11    	= gdb_regs[GDB_FP];
    regs->r12    	= gdb_regs[GDB_IP];
    regs->sp    	= gdb_regs[GDB_SPT];
    regs->lr	    = gdb_regs[GDB_LR];
    regs->pc        = gdb_regs[GDB_PC];
    regs->psr       = gdb_regs[GDB_CPSR];

}


/* It will be called during process_packet */
int gdb_arch_handle_exception(char *remcom_in_buffer,
                              char *remcom_out_buffer)
{
    unsigned long addr;
    char *ptr;
    static int step = 0;

    if (step){
        gdb_clear_single_step();
        step = 0;
    }

    switch (remcom_in_buffer[0]) {
        case 'D':
        case 'k':
        case 'c':
            /*
             * If this was a compiled breakpoint, we need to move
             * to the next instruction or we will breakpoint
             * over and over again
             */
            ptr = &remcom_in_buffer[1];
            if (gdb_hex2long(&ptr, &addr))
                regs->pc = addr;

            return 0;
        case 's':
            ptr = &remcom_in_buffer[1];
            if (gdb_hex2long(&ptr, &addr))
                regs->pc = addr;

            gdb_single_step();
            step = 1;

            return 0;
    }

	return -1;

}

int gdb_set_hw_break(unsigned long addr, int len, enum gdb_bptype bptype)
{
    int i;

    if (bptype == BP_HARDWARE_BREAKPOINT) {
        for (i = 0; i < HBP_NUM; i++)
            if (!breakinfo[i].enabled)
                break;
        if (i == HBP_NUM)
            return -1;
        breakinfo[i].addr = addr;
        breakinfo[i].enabled = 1;
    }
    else if (bptype == BP_WRITE_WATCHPOINT) {
                for (i = 0; i < HWP_NUM; i++)
            if (!watchinfo[i].enabled)
                break;
        if (i == HWP_NUM)
            return -1;
        watchinfo[i].addr = addr;
        watchinfo[i].len = len;
        watchinfo[i].type = BP_WRITE_WATCHPOINT;	
        watchinfo[i].enabled = 1;
    }
    else if (bptype == BP_READ_WATCHPOINT) {
        for (i = 0; i < HWP_NUM; i++)
            if (!watchinfo[i].enabled)
                break;
        if (i == HWP_NUM)
            return -1;
        watchinfo[i].addr = addr;
        watchinfo[i].len = len;
        watchinfo[i].type = BP_READ_WATCHPOINT;	
        watchinfo[i].enabled = 1;
    }
    else if (bptype == BP_ACCESS_WATCHPOINT) {
                for (i = 0; i < HWP_NUM; i++)
            if (!watchinfo[i].enabled)
                break;
        if (i == HWP_NUM)
            return -1;
        watchinfo[i].addr = addr;
        watchinfo[i].len = len;
        watchinfo[i].type = BP_ACCESS_WATCHPOINT;	
        watchinfo[i].enabled = 1;
    }

    return 0;
}

int gdb_remove_hw_break(unsigned long addr, int len, enum gdb_bptype bptype)
{
    int i;

    if (bptype == BP_HARDWARE_BREAKPOINT) {
        for (i = 0; i < HBP_NUM; i++)
            if (breakinfo[i].addr == addr && breakinfo[i].enabled)
                break;
        if (i == HBP_NUM)
            return -1;
        breakinfo[i].enabled = 0;

    }
    else if (bptype == BP_WRITE_WATCHPOINT) {
        for (i = 0; i < HWP_NUM; i++)
            if (watchinfo[i].addr == addr && watchinfo[i].enabled && watchinfo[i].type == bptype)
                break;
        if (i == HWP_NUM)
            return -1;
        watchinfo[i].enabled = 0;

    }
    else if (bptype == BP_READ_WATCHPOINT) {
        for (i = 0; i < HWP_NUM; i++)
            if (watchinfo[i].addr == addr && watchinfo[i].enabled && watchinfo[i].type == bptype)
                break;
        if (i == HWP_NUM)
            return -1;
        watchinfo[i].enabled = 0;

    }
    else if (bptype == BP_ACCESS_WATCHPOINT) {
        for (i = 0; i < HWP_NUM; i++)
            if (watchinfo[i].addr == addr && watchinfo[i].enabled && watchinfo[i].type == bptype)
                break;
        if (i == HWP_NUM)
            return -1;
        watchinfo[i].enabled = 0;

    }

    return 0;
}

void gdb_remove_all_hw_break()
{
    int i;
    volatile unsigned long *base;

    // Disable hardware break
    for (i = 0; i < HBP_NUM; i++) {
        if (!breakinfo[i].enabled)
            break;
        base = (unsigned long*)(GDB_FPB_REG_BASE + GDB_FPB_REG_COMP + i * 4);
        *base &= ~GDB_FPB_REG_COMP_ENABLE ;  
    }
 
    // Disable watchpoint
    for (i = 0; i < HWP_NUM; i++) {
        if (!watchinfo[i].enabled)
            break;
        base = (unsigned long*)(GDB_DWT_REG_BASE + GDB_DWT_REG_FUNCTION + i * 12);
        *base &= ~GDB_DWT_REG_FUNCTION_FUC ;  
    }

}

void gdb_arch_late()
{
    gdb_remove_all_hw_break();
}

void gdb_arch_exit()
{  
    volatile unsigned long *base;
    char num = 1;
    int i;

    // Install the hardware break
    for (i = 0; i < HBP_NUM; i++) {
        if (breakinfo[i].enabled) {
            base = (unsigned long*)(GDB_FPB_REG_BASE + GDB_FPB_REG_COMP + i * 4);
            
            *base = GDB_FPB_REG_COMP_ADDR & ((unsigned long)(breakinfo[i].addr));

            if (breakinfo[i].addr & 2)
                *base |= (1UL << 31); //set BKPT on upper halfword
            else 
                *base |= (1UL << 30); //set BKPT on lower halfword,

            *base |= GDB_FPB_REG_COMP_ENABLE ;  
        }   
    }

    // Install the watchpoint
    for (i = 0; i < HWP_NUM; i++) {
        if (watchinfo[i].enabled) {
            base = (unsigned long*)(GDB_DWT_REG_BASE + GDB_DWT_REG_COMP + i * 12);
            *base = watchinfo[i].addr;

            base = (unsigned long*)(GDB_DWT_REG_BASE + GDB_DWT_REG_MASK + i * 12);
            while (watchinfo[i].len >> num) {
                num++;
            }
            *base = num - 1; //DWT matching is performed as:(ADDR & (~0 << MASK)) == COMP

            base = (unsigned long*)(GDB_DWT_REG_BASE + GDB_DWT_REG_FUNCTION + i * 12);

            if (watchinfo[i].type == BP_WRITE_WATCHPOINT) 
                *base =  (*base & ~GDB_DWT_REG_FUNCTION_FUC) + 0x05;            
            else if (watchinfo[i].type == BP_READ_WATCHPOINT) 
                *base =  (*base & ~GDB_DWT_REG_FUNCTION_FUC) + 0x06;          
            else if (watchinfo[i].type == BP_ACCESS_WATCHPOINT) 
                *base =  (*base & ~GDB_DWT_REG_FUNCTION_FUC) + 0x07;

        }   
    }

}

