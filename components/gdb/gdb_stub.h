/*
 * This provides the functions that GDB needs to share between 
 * different portions.
 *
 * GDB stub.
 * 
 * Migarte form linux to rt-thread by Wzyy2
 * Original edition : KGDB stub
 * 
 * File      : gdb_stub.h
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
#ifndef __GDB_STUB_H__
#define __GDB_STUB_H__

#include <rtthread.h>
#include <arch_gdb.h>


#ifndef RT_GDB_MAX_BREAKPOINTS
    #define GDB_MAX_BREAKPOINTS 20
#else
    #define GDB_MAX_BREAKPOINTS  RT_GDB_MAX_BREAKPOINTS
#endif


// Signal definitions
#define SIGHUP  1       /* hangup */
#define SIGINT  2       /* interrupt */   //irq or fiq
#define SIGQUIT 3       /* quit */
#define SIGILL  4       /* illegal instruction (not reset when caught) */
#define SIGTRAP 5       /* trace trap (not reset when caught) */
#define SIGIOT  6       /* IOT instruction */
#define SIGABRT 6       /* used by abort, replace SIGIOT in the future */
#define SIGEMT  7       /* EMT instruction */
#define SIGFPE  8       /* floating point exception */
#define SIGKILL 9       /* kill (cannot be caught or ignored) */
#define SIGBUS  10      /* bus error */  //abort or reserved
#define SIGSEGV 11      /* segmentation violation */
#define SIGSYS  12      /* bad argument to system call */
#define SIGPIPE 13      /* write on a pipe with no one to read it */
#define SIGALRM 14      /* alarm clock */
#define SIGTERM 15      /* software termination signal from kill */

enum gdb_bptype {
    BP_BREAKPOINT = 0,
    BP_HARDWARE_BREAKPOINT,
    BP_WRITE_WATCHPOINT,
    BP_READ_WATCHPOINT,
    BP_ACCESS_WATCHPOINT,
    BP_POKE_BREAKPOINT,
};

enum gdb_bpstate {
    BP_UNDEFINED = 0,
    BP_REMOVED,
    BP_SET,
    BP_ACTIVE
};

struct gdb_bkpt {
    unsigned long		bpt_addr;
    unsigned char		saved_instr[BREAK_INSTR_SIZE];
    enum gdb_bptype	type;
    enum gdb_bpstate	state;
};

/**
 * struct gdb_arch - Describe architecture specific values.
 * @gdb_bpt_instr: The instruction to trigger a breakpoint.
 * @flags: Flags for the breakpoint, currently just %GDB_HW_BREAKPOINT.
 * @set_hw_breakpoint: Allow an architecture to specify how to set a hardware
 * breakpoint.
 * @remove_hw_breakpoint: Allow an architecture to specify how to remove a
 * hardware breakpoint.
 * @remove_all_hw_break: Allow an architecture to specify how to remove all
 * hardware breakpoints.
 */
struct gdb_arch {
	unsigned char		gdb_bpt_instr[BREAK_INSTR_SIZE];
	unsigned long		flags;

	int	(*set_hw_breakpoint)(unsigned long, int, enum gdb_bptype);
	int	(*remove_hw_breakpoint)(unsigned long, int, enum gdb_bptype);
	void	(*remove_all_hw_break)(void);
};
/**
 * struct gdb_io - Describe the interface for an I/O driver to talk with KGDB.
 * @read_char: Pointer to a function that will return one char.
 * @write_char: Pointer to a function that will write one char.
 * @flush: Pointer to a function that will flush any pending writes.
 * @init: Pointer to a function that will initialize the device.
 */
struct gdb_io {
    int			(*read_char) (void);
    void			(*write_char) (char);
    void			(*flush) (void);
    int			(*init) (void);
};

extern int		gdb_connected;
extern void* volatile gdb_mem_fault_handler;

int gdb_hex2long(char **ptr, unsigned long *long_val);
int gdb_mem2hex(char *mem, char *buf, int count);
int gdb_hex2mem(char *buf, char *mem, int count);
int gdb_ebin2mem(char *buf, char *mem, int count);
int gdb_set_sw_break(unsigned long addr);
int gdb_remove_sw_break(unsigned long addr);
int gdb_isremovedbreak(unsigned long addr);
void gdb_console_write(const char *s, unsigned count);
int gdb_handle_exception(int signo, void *regs);

/* hal */
extern struct gdb_io		gdb_io_ops;
extern rt_device_t gdb_dev;
void gdb_start();
void gdb_set_device(const char* device_name);



#endif /* __GDB_STUB_H__ */
