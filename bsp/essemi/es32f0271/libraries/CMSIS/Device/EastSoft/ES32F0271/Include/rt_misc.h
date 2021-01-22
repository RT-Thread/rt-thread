/* rt_misc.h: definitions for miscellaneous retargetable functions
 *
 * Copyright 1999,2013-2014 ARM Limited. All rights reserved.
 *
 * RCS $Revision$
 * Checkin $Date$
 * Revising $Author$
 */

#ifndef __RT_MISC_H
#define __RT_MISC_H
#define __ARMCLIB_VERSION 5060019

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

/*
 * This will be called during startup if it's defined, in order to
 * allow a user reimplementation of getenv() to initialise itself.
 */
extern void _getenv_init(void);

/*
 * This will be called during startup if it's defined, in order to
 * allow a user reimplementation of clock() to initialise itself.
 */
extern void _clock_init(void);

/*
 * This must return a pointer to __USER_LIBSPACE_SIZE bytes of
 * zero-initialised space, used to store vital static data such as
 * errno, the heap state, and the FP status word.
 */
#define __USER_LIBSPACE_SIZE 96
extern void *__user_libspace(void);

/*
 * This is the library init function itself, provided just in case
 * a user needs to call it directly. It is called just after
 * __rt_stackheap_init(), and passed an initial chunk of memory to
 * use as a heap. It returns argc and argv ready to be passed to
 * main(). (The __argc_argv structure contains four words rather
 * than just two, in case you need to pass anything else to main()
 * such as the Unix envp.  For AArch64 struct __argc_argv is 8 words
 * (4 registers) and explicit padding is used to ensure argc is in w0.)
 */
struct __argc_argv {
#if (defined(__ARM_64BIT_STATE) || defined(__TARGET_ARCH_AARCH64)) && \
    (defined(__ARM_BIG_ENDIAN) || defined(__BIG_ENDIAN))
    int padding;
#endif
    int argc;
#if (defined(__ARM_64BIT_STATE) || defined(__TARGET_ARCH_AARCH64)) && \
    !(defined(__ARM_BIG_ENDIAN) || defined(__BIG_ENDIAN))
    int padding;
#endif
    char **argv;
    void *r2;
    void *r3;
};
extern __value_in_regs struct __argc_argv
__rt_lib_init(unsigned /*heapbase*/, unsigned /*heaptop*/);

/*
 * This function is responsible for constructing argc and argv to
 * be passed to main(). Normally it works by calling
 * _sys_command_string() and then splitting up the returned command
 * line. If you define main() without arguments, the compiler also
 * defines an empty version of this function to save time. In
 * special circumstances, you might need to redefine this function
 * explicitly yourself.
 */
__value_in_regs struct __argc_argv __ARM_get_argv(void */*internal use only*/);

/*
 * This is the library shutdown function, analogous to
 * __rt_lib_init().
 */
extern void __rt_lib_shutdown(void);

/*
 * The medium-level exit function. exit() calls atexit()-registered
 * functions and shuts down the library; _sys_exit() does neither
 * of those things; __rt_exit() shuts down the library but doesn't
 * call atexit() functions.
 */
extern void __rt_exit(int /*returncode*/);   /* never returns */

/*
 * This can be defined to override the standard memory models' way
 * of determining where to put the initial stack and heap.
 *
 * The input parameters R0 and R2 contain nothing useful. The input
 * parameters SP and SL are the values that were in SP and SL when
 * the program began execution (so you can return them if you want
 * to keep that stack).
 *
 * The two `limit' fields in the return structure are ignored if
 * you are using the one-region memory model: the memory region is
 * taken to be all the space between heap_base and stack_base.
 */
struct __initial_stackheap {
    unsigned heap_base;                /* low-address end of initial heap */
    unsigned stack_base;               /* high-address end of initial stack */
    unsigned heap_limit;               /* high-address end of initial heap */
    unsigned stack_limit;              /* low-address end of initial stack */
};
extern __value_in_regs struct __initial_stackheap
__user_initial_stackheap(unsigned /*R0*/, unsigned /*SP*/,
                         unsigned /*R2*/, unsigned /*SL*/);

/*
 * This can be defined to give bounds on the address space the heap
 * will ever use.
 */
struct __heap_extent {
    uintptr_t base;
    size_t range;
};
extern __value_in_regs struct __heap_extent
__user_heap_extent(uintptr_t /*ignore*/, size_t /*ignore*/);

/*
 * This can be defined to specify how much spare stack is needed
 * below SL in addition to the 256 bytes required by ATPCS:
 * `always' gives the number of bytes of extra stack required at
 * all instants (so that an interrupt handler has space to run in,
 * for example), while `cleanup' gives the number of bytes of extra
 * stack required to be available after a stack overflow has
 * occurred, so that the stack overflow routine (e.g. SIGSTAK
 * handler) has room to tidy up.
 */
struct __stack_slop {
    unsigned always, cleanup;
};
extern __value_in_regs struct __stack_slop
__user_stack_slop(unsigned /*ignore*/, unsigned /*ignore*/);

/*
 * This can be defined to return extra blocks of memory, separate
 * from the initial one, to be used by the heap. It should place a
 * pointer to a block of at least the requested size in `*base',
 * and return the size of the block. It should return 0 if no such
 * block can be returned, in which case the value stored at `*base'
 * is never used.
 */
extern size_t __user_heap_extend(int /*ignore*/,
                                 void ** /*base*/,
                                 size_t /*requestedsize*/);

/*
 * Redefine this to completely override the C handling of signals
 * (bypassing the signal() mechanism). Return values are 0 to
 * continue execution, or a non-zero value to cause an exit with
 * that return code.
 */
int __raise(int /*sig*/, intptr_t /*type*/);

/*
 * Redefine this to change the default handling of signals. The
 * interface is the same as __raise(), but this function will only
 * get called after the C signal handling mechanism has declined to
 * process the signal.
 */
int __default_signal_handler(int /*sig*/, intptr_t /*type*/);

/*
 * Redefine this to replace the library's entire signal handling
 * mechanism in the most efficient possible way. The default
 * implementation of this is what calls __raise (above).
 */
void __rt_raise(int /*sig*/, intptr_t /*type*/);

#ifdef __cplusplus
}
#endif

#endif

