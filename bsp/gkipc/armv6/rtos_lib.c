#include <sys/time.h>
#include <time.h>
#include "rtos_lib.h"
#include "gd_timer.h"
#include "gm_debug.h"
#include "rtthread.h"
#include "shell.h"

#ifdef RT_USING_FINSH
#include "shell.h"
#endif

//#define CACHE_MEM_MANAGE
#define CACHE_MEM_SIZE  0x200000//1152k
#define CACHE_DSP_SIZE  0x330000//3168k

#define CACHE_LINE_SIZE     32
#define CACHE_LINE_MASK     ~(CACHE_LINE_SIZE - 1)

static int cache_check_end = 0;
static int cache_check_start = 1;
//static int cache_check_fail_halt = 0;
void RTOS_MMU_ChangeMapEntry(U32 vaddrStart, U32 vaddrEnd, U32 paddrStart, U32 attr);

static inline void __delay(int loops);

u32 cpu_cpsr;
#define HZ      RT_TICK_PER_SECOND

#define LPS_PREC 8

#define jiffies raid6_jiffies()

static inline void __delay(int loops)
{
    return;
}

static inline unsigned int raid6_jiffies(void)
{
    //struct timeval tv;
    //gettimeofday(&tv, NULL);
    //return tv.tv_sec*1000 + tv.tv_usec/1000;
    return rt_tick_get()*1000;
}

static unsigned long  calibrate_delay_converge(void)
{
    /* First stage - slowly accelerate to find initial bounds */
    unsigned long lpj, lpj_base, ticks, loopadd, loopadd_base, chop_limit;
    int trials = 0, band = 0, trial_in_band = 0;

    lpj = (1<<12);

    /* wait for "start of" clock tick */
    ticks = jiffies;
    while (ticks == jiffies)
        ; /* nothing */
    /* Go .. */
    ticks = jiffies;
    do {
        if (++trial_in_band == (1<<band)) {
            ++band;
            trial_in_band = 0;
        }
        __delay(lpj * band);
        trials += band;
    } while (ticks == jiffies);
    /*
     * We overshot, so retreat to a clear underestimate. Then estimate
     * the largest likely undershoot. This defines our chop bounds.
     */
    trials -= band;
    loopadd_base = lpj * band;
    lpj_base = lpj * trials;

recalibrate:
    lpj = lpj_base;
    loopadd = loopadd_base;

    /*
     * Do a binary approximation to get lpj set to
     * equal one clock (up to LPS_PREC bits)
     */
    chop_limit = lpj >> LPS_PREC;
    while (loopadd > chop_limit) {
        lpj += loopadd;
        ticks = jiffies;
        while (ticks == jiffies)
            ; /* nothing */
        ticks = jiffies;
        __delay(lpj);
        if (jiffies != ticks)   /* longer than 1 tick */
            lpj -= loopadd;
        loopadd >>= 1;
    }
    /*
     * If we incremented every single time possible, presume we've
     * massively underestimated initially, and retry with a higher
     * start, and larger range. (Only seen on x86_64, due to SMIs)
     */
    if (lpj + loopadd * 2 == lpj_base + loopadd_base * 2) {
        lpj_base = lpj;
        loopadd_base <<= 2;
        goto recalibrate;
    }

    return lpj;
}

void RTOS_Jiffies()
{
    unsigned long lpj;
    lpj = calibrate_delay_converge();
    rt_kprintf("Calibrating delay loop... %lu.%02lu BogoMIPS (lpj=%lu)\n",
            lpj/(500000/HZ),
            (lpj/(5000/HZ)) % 100, lpj);
}

void gk7101_setting_pll()
{
    int i = 0;

    *((volatile U32 *)0x70170000) = 0x01202e01;
    *((volatile U32 *)0x70170004) = 0x00000000;
    *((volatile U32 *)0x7017000C) = 0x0000000c;
    *((volatile U32 *)0x70170014) = 0x01202401;
    *((volatile U32 *)0x70170018) = 0x00000000;
    *((volatile U32 *)0x7017001C) = 0x00000001;
    *((volatile U32 *)0x70170024) = 0x02406301;
    *((volatile U32 *)0x70170028) = 0x00000000;
    *((volatile U32 *)0x70170030) = 0x00000000;
    *((volatile U32 *)0x70170034) = 0x00000000;
    *((volatile U32 *)0x70170038) = 0x00000001;
    *((volatile U32 *)0x7017003C) = 0x00000008;
    *((volatile U32 *)0x7017004C) = 0x00000001;
    *((volatile U32 *)0x70170050) = 0x00000001;
    *((volatile U32 *)0x70170054) = 0x01202001;
    *((volatile U32 *)0x70170058) = 0x00c49ba5;
    *((volatile U32 *)0x7017005C) = 0x00000008;
    *((volatile U32 *)0x70170060) = 0x00000001;
    *((volatile U32 *)0x70170068) = 0x00000002;
    *((volatile U32 *)0x70170080) = 0x00206978;
    *((volatile U32 *)0x70170084) = 0x00000020;
    *((volatile U32 *)0x7017008C) = 0x0000000f;
    *((volatile U32 *)0x7017009C) = 0x00000002;
    *((volatile U32 *)0x701700A0) = 0x00000010;
    *((volatile U32 *)0x701700BC) = 0x00000001;
    *((volatile U32 *)0x701700E4) = 0x01203201;
    *((volatile U32 *)0x701700E8) = 0x00000000;
    *((volatile U32 *)0x701700EC) = 0x00000008;
    *((volatile U32 *)0x70170100) = 0x00000030;
    *((volatile U32 *)0x70170108) = 0x00000030;
    *((volatile U32 *)0x70170118) = 0x00000002;
    *((volatile U32 *)0x7017011C) = 0x00000030;
    *((volatile U32 *)0x70170124) = 0x00000030;
    *((volatile U32 *)0x70170130) = 0x00000030;
    *((volatile U32 *)0x70170148) = 0x00000001;
    *((volatile U32 *)0x70170198) = 0x00000000;
    *((volatile U32 *)0x7017019C) = 0x00000000;
    *((volatile U32 *)0x701701E0) = 0x00000000;
    *((volatile U32 *)0x701701E4) = 0x00000000;
    *((volatile U32 *)0x701701F4) = 0x00000002;
    *((volatile U32 *)0x701701FC) = 0x00000021;
    *((volatile U32 *)0x70170200) = 0x00000022;
    *((volatile U32 *)0x70170214) = 0x00000022;
#if 0
    *((volatile U32 *)0x7017021C) = 0x00000000;
    *((volatile U32 *)0x70170228) = 0x00000000;
    *((volatile U32 *)0x7017022C) = 0x00000000;
#endif

    for(i=0; i<14; i++)
    {
        *((volatile U32 *)((U32)0x70170230 + i*4)) = 0x11111111;
    }

#if 0
    *((volatile U32 *)0x70170270) = 0x00000000;
#endif

    *(volatile U32 *)(0x70009100+20*4) = (1<<8);
    *(volatile U32 *)(0x70009200+7*4) = 20;

    *(volatile U32 *)(0x70009100+22*4) = 9;

}
//-------------------------------------------------------

#if 0
rt_inline unsigned int rt_list_len(const rt_list_t *l)
{
    unsigned int len = 0;
    const rt_list_t *p = l;
    while (p->next != l)
    {
        p = p->next;
        len ++;
    }

    return len;
}
#endif

static void show_wait_queue(struct rt_list_node *list)
{
    struct rt_thread *thread;
    struct rt_list_node *node;

    for (node = list->next; node != list; node = node->next)
    {
        thread = rt_list_entry(node, struct rt_thread, tlist);
        rt_kprintf("%s", thread->name);

        if (node->next != list)
            rt_kprintf("/");
    }
}

void rtos_cache_inv_range(void *addr, unsigned int size)
{
    u32                 vstart;
    u32                 vend;
    u32                 addr_tmp;

    vstart = (u32)addr & CACHE_LINE_MASK;
    vend = ((u32)addr + size + CACHE_LINE_SIZE - 1) & CACHE_LINE_MASK;

    if (cache_check_start && (vstart != (u32)addr)) {
        return;
    }
    if (cache_check_end && (vend != ((u32)addr + size))) {
        return;
    }


    for (addr_tmp = vstart; addr_tmp < vend; addr_tmp += CACHE_LINE_SIZE) {
        __asm__ __volatile__ (
            "mcr p15, 0, %0, c7, c6, 1" : : "r" (addr_tmp));
    }
    dsb();
}

void rtos_cache_clean_range(void *addr, unsigned int size)
{


    u32                 vstart;
    u32                 vend;

    u32                 addr_tmp;

    vstart = (u32)addr & CACHE_LINE_MASK;
    vend = ((u32)addr + size + CACHE_LINE_SIZE - 1) & CACHE_LINE_MASK;
    if (cache_check_start && (vstart != (u32)addr)) {
        return;
    }
    if (cache_check_end && (vend != ((u32)addr + size))) {
        return;
    }


    for (addr_tmp = vstart; addr_tmp < vend; addr_tmp += CACHE_LINE_SIZE) {
        __asm__ __volatile__ (
            "mcr p15, 0, %0, c7, c10, 1" : : "r" (addr_tmp));
    }

    dsb();
}





U32 RTOS_EnterCriticalSection( void )
{
    #if 0
    /*lint -save -e529 */
    U32 old_flags = 0;
    U32 new_flags = 0;

    #if defined(_ARM) && !defined(__GNUC__) && !defined(__polyspace__)
        __asm { mrs old_flags,cpsr }
        __asm { orr new_flags,old_flags,#0xC0 }
        __asm { msr cpsr_c,new_flags }
    #endif

    #if defined(_ARM) && defined(__GNUC__) && !defined(__polyspace__)
        asm volatile( "mrs %0,cpsr"     : "=r"(old_flags) : "r"(new_flags) );
        asm volatile( "orr %0,%1,#0xC0" : "=r"(new_flags) : "r"(old_flags) );
        asm volatile( "msr cpsr_c,%0"   : : "r"(new_flags) );
    #endif

    #if defined(_ARC) && !defined(__polyspace__)
        old_flags = _lr(0);
        _flag(0);
    #endif

    return( old_flags );
    #else
    return (U32)rt_hw_interrupt_disable();
    #endif
    /*lint -restore */
}

void RTOS_LeaveCriticalSection( U32 cpuStatus )
{
    #if 0
    /*lint -save -e715 */

    #if defined(_ARM) && !defined(__GNUC__) && !defined(__polyspace__)
        __asm { msr cpsr_c,cpuStatus }
    #endif

    #if defined(_ARM) && defined(__GNUC__) && !defined(__polyspace__)
        asm volatile ( "msr cpsr_c,%0" : : "r"(cpuStatus) );
    #endif

    #if defined(_ARC) && !defined(__polyspace__)
        cpuStatus &= 0x0C000000;
        _flag( cpuStatus >> 25 );
    #endif
    #else
    rt_hw_interrupt_enable(cpuStatus);
    #endif
    /*lint -restore */
}




void RTOS_Halt( void )
{
    RTOS_EnterCriticalSection();
}



//-------------------------------------------------------------
RTOS_Memory RTOS_MemorySet( RTOS_Memory mem, U8 value, RTOS_Size bytes )
{
    if( ( mem == (RTOS_Memory)0 ) || ( bytes == 0 ) )
        return( (RTOS_Memory)0 );
#if 0
    return rt_memset(mem,value,bytes);
#else// use libc 's memset to improve performance.
    return memset(mem,value,bytes);
#endif
}

RTOS_Memory RTOS_Malloc( RTOS_Size bytes)
{
    return rt_malloc(bytes);
}

RTOS_Memory RTOS_Realloc( RTOS_Memory addr, RTOS_Size bytes )
{
    return rt_realloc(addr, bytes);
}

char * RTOS_ThreadGetSelfName(void);
RTOS_Memory RTOS_MemoryAllocate( RTOS_Size bytes, RTOS_Flag shared )
{
    //if (bytes >= 0x10000)
    //    printf("RTOS_MemoryAllocate: %d(%s)\n",bytes, RTOS_ThreadGetSelfName());
    return rt_malloc(bytes);
}

RTOS_Status RTOS_MemoryRelease( RTOS_Memory memory )
{
    if(memory) rt_free(memory);
    return 0;
}

RTOS_Memory RTOS_SysMemoryAllocate( RTOS_Size bytes, RTOS_Flag shared )
{
#ifndef CACHE_MEM_MANAGE
    return (RTOS_Memory)rt_malloc(bytes);
#else
    return (RTOS_Memory)rt_dspmem_malloc(bytes);
#endif
}

RTOS_Status RTOS_SysMemoryRelease( RTOS_Memory memory )
{
    if(memory)
#ifndef CACHE_MEM_MANAGE
     rt_free(memory);
#else
    rt_dspmem_free(memory);
#endif
    return 0;
}

RTOS_Memory RTOS_KernelMemoryAllocate( RTOS_Size bytes)
{
    return (RTOS_Memory)RT_KERNEL_MALLOC(bytes);
}

RTOS_Status RTOS_KernelMemoryRelease( RTOS_Memory memory )
{
    if(memory)
        RT_KERNEL_FREE(memory);
    return 0;
}


void RTOS_GetMemInfo( RTOS_Size *Cache_memory, RTOS_Size *Uncache_memory)
{
    rt_uint32_t total,used,max_used;

    rt_memory_info(&total,&used,&max_used);
    *Cache_memory = total;
    *Uncache_memory = 0;

    #ifdef  CACHE_MEM_MANAGE
    rt_cache_memory_info(&total,&used,&max_used);
    *Uncache_memory = total;
    #endif
}



void RTOS_HeapMemoryReport( void )
{
    rt_uint32_t total,used,max_used;

    rt_memory_info(&total,&used,&max_used);
    rt_kprintf("Heap Memory Info [cache memory]\n");
    rt_kprintf("total memory:             %d KBytes,%d Btyes\n", total/1024,total);
    rt_kprintf("used memory :             %d KBytes,%d Btyes\n", used/1024,used);
    rt_kprintf("maximum allocated memory: %d KBytes,%d Btyes\n", max_used/1024,max_used);
}

void RTOS_SysMemoryReport( void )
{
#ifdef  CACHE_MEM_MANAGE
    rt_uint32_t total,used,max_used;

    rt_cache_memory_info(&total,&used,&max_used);
    rt_kprintf("Sys  Memory Info [cache memory]\n");
    rt_kprintf("total memory:             %d KBytes\n", total/1024);
    rt_kprintf("used memory :             %d KBytes\n", used/1024);
    rt_kprintf("maximum allocated memory: %d KBytes\n", max_used/1024);

    rt_dspmem_memory_info(&total,&used,&max_used);
    rt_kprintf("Drv  Memory Info [uncache memory]\n");
    rt_kprintf("total memory:             %d KBytes\n", total/1024);
    rt_kprintf("used memory :             %d KBytes\n", used/1024);
    rt_kprintf("maximum allocated memory: %d KBytes\n", max_used/1024);

#endif
}

RTOS_Memory RTOS_MemoryCopy( RTOS_Memory dst, RTOS_Memory src, RTOS_Size bytes )
{
#if 0
    U8*       dstArray = (U8*)dst;
    U8*       srcArray = (U8*)src;
    RTOS_Size index;

    if( ( dst == (RTOS_Memory)0 ) || ( bytes == 0 ) )
        return( (RTOS_Memory)0 );

    for( index=0; index < bytes; index++ )
        dstArray[index] = srcArray[index];

    return( dst );
#else// use libc 's memcpy to improve performance.
    if( ( dst == (RTOS_Memory)0 ) || ( bytes == 0 ) )
        return( (RTOS_Memory)0 );
    memcpy(dst, src, bytes);
    return( dst );
#endif
}

//-------------------------------------------------------------

U32 RTOS_SetThreadName( RTOS_ThreadT threadHandle, const char* optName)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    if(threadHandle)
    {
        rt_strncpy(((rt_thread_t)threadHandle)->name, optName, RT_NAME_MAX);
    }
    rt_hw_interrupt_enable(level);

    return 0;
}

U32 RTOS_ThreadSetName( RTOS_ThreadT threadHandle, const char* optName)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    if(threadHandle)
    {
        rt_strncpy(((rt_thread_t)threadHandle)->name, optName, RT_NAME_MAX);
    }
    rt_hw_interrupt_enable(level);

    return 0;
}
char * RTOS_ThreadGetSelfName(void)
{
    return rt_thread_self()->name;
}

// thread-safe errno related api functions.
void RTOS_SetErrno(const int err)
{
#if 0
    rt_base_t level;
    level = rt_hw_interrupt_disable();

    rt_thread_t self = rt_thread_self();
    self->thr_internal_errno = err;//FIXME(heyong): error is used to errno.

    rt_hw_interrupt_enable(level);
    //rt_kprintf("RTOS_SetErrno %d\n", err);
#endif
}
int RTOS_GetErrno()
{
    int err;
#if 0
    rt_base_t level;
    level = rt_hw_interrupt_disable();

    rt_thread_t self = rt_thread_self();
    err = (int)self->thr_internal_errno;//FIXME(heyong): error is used to errno.

    rt_hw_interrupt_enable(level);
    //rt_kprintf("RTOS_GetErrno %d\n", err);
#endif
    return err;
}

RTOS_ThreadT RTOS_CreateThread(
        U32* stackBuffer, U32 stackSize, U32 priority,
        RTOS_ThreadFunctionT function, void* optArg, void* optData,
        const char* optName )
{
    rt_thread_t tid;

    if (priority < RTOS_ThreadPriorityHighest)
    {
        priority = RTOS_ThreadPriorityHighest - priority;
    }
    else
    {
        priority = 1;
    }

    tid = rt_thread_create((optName == NULL)?"thread":optName,
                    function, optArg,
                    stackSize, priority, THREAD_TIMESLICE);
    if (tid != RT_NULL)
    {
        rt_thread_startup(tid);
    }

    return (RTOS_ThreadT)tid;
}

U32 RTOS_DestroyThread( RTOS_ThreadT threadHandle )
{
    rt_err_t ret = 0;

    rt_enter_critical();
    ret = rt_thread_delete((rt_thread_t)threadHandle);
    rt_exit_critical();

    if (RT_EOK == ret)
    {
        ret = 1;
    }
    else
    {
        ret = 0;
    }

    return ret;
}

U32 RTOS_ThreadDestroy( RTOS_ThreadT threadHandle )
{
    rt_err_t ret = 0;

    rt_enter_critical();
    ret = rt_thread_delete((rt_thread_t)threadHandle);
    rt_exit_critical();

    if (RT_EOK == ret)
    {
        ret = 1;
    }
    else
    {
        ret = 0;
    }

    return ret;
}

U32 RTOS_GetThreadPriority(RTOS_ThreadT threadHandle)
{
    rt_thread_t tid = (rt_thread_t)threadHandle;
    int priority = tid->current_priority;

    if (priority < RTOS_ThreadPriorityHighest)
    {
        priority = RTOS_ThreadPriorityHighest - priority;
    }
    else
    {
        priority = 1;
    }
    return priority;
}


void gkosFinishThread( void )
{
    //rt_thread_t t = rt_thread_self();

    //rt_thread_detach(t);
}


void RTOS_LockScheduler( void )
{
    rt_enter_critical();
}

void RTOS_UnlockScheduler( void )
{
    rt_exit_critical();
}

void RTOS_SchedulerLock( void )
{
    rt_enter_critical();
}

void RTOS_SchedulerUnlock( void )
{
    rt_exit_critical();
}

U32 RTOS_SleepThread( U32 msecs )
{
    return  rt_thread_delay( msecs )  ;
}

U32 msleep( U32 msecs )
{
    return  rt_thread_delay( msecs )  ;
}


U32 RTOS_SuspendThread( RTOS_ThreadT threadHandle )
{
    return rt_thread_suspend((rt_thread_t)threadHandle);
}

U32 RTOS_WakeupThread( RTOS_ThreadT threadHandle )
{
    return rt_thread_resume( (rt_thread_t)threadHandle );
}

void thread_statistics()
{
    struct rt_thread *thread;
    struct rt_list_node *node;
    rt_uint8_t *ptr;

    rt_base_t level;

    struct rt_object_information *information;

    information = rt_object_get_information(RT_Object_Class_Thread);
    RT_ASSERT(information != RT_NULL);

    struct rt_list_node *list = &(information->object_list);

    level = rt_hw_interrupt_disable();

    for (node = list->next; node != list; node = node->next)
    {
        thread = rt_list_entry(node, struct rt_thread, list);
        //if(thread) thread->total_tick = 0;
    }

    rt_hw_interrupt_enable(level);

    rt_thread_delay(5000);

    //not close interrupt to avoid the venc error because the print time is too long.
    //level = rt_hw_interrupt_disable();
    rt_kprintf("          thread                 pri  status  tick   cpu%%         sp    stack addr stack size  max used  left tick\n");
    rt_kprintf("-------------------------------- --- ------- ------ -------    ---------- ---------- ---------- ---------- ---------- \n");
    for (node = list->next; node != list; node = node->next)
    {
        thread = rt_list_entry(node, struct rt_thread, list);
#if 0
        rt_kprintf("%-32.*s 0x%02x", RT_NAME_MAX, thread->name, thread->current_priority);
#else
        int priority = thread->current_priority;
        if (priority < RTOS_ThreadPriorityHighest)
        {
            priority = RTOS_ThreadPriorityHighest - priority;
        }
        else
        {
            priority = 1;
        }
        rt_kprintf("%-32.*s %3d", RT_NAME_MAX, thread->name, priority);
#endif
        if (thread->stat == RT_THREAD_READY)        rt_kprintf("   ready");
        else if (thread->stat == RT_THREAD_SUSPEND) rt_kprintf(" suspend");
        else if (thread->stat == RT_THREAD_INIT)    rt_kprintf("    init");
        else if (thread->stat == RT_THREAD_CLOSE)   rt_kprintf("   close");

        ptr = (rt_uint8_t*)thread->stack_addr;
        while (*ptr == '#')ptr ++;
#if 0
        rt_kprintf(" %5d   %5.2f%%    0x%08x 0x%08x 0x%08x 0x%08x 0x%08x \n",
            thread->total_tick,
            ((double)thread->total_tick/50)>=100.00?99.9:((double)thread->total_tick/50),
            thread->stack_size + ((rt_uint32_t)thread->stack_addr - (rt_uint32_t)thread->sp),
            thread->stack_addr,
            thread->stack_size,
            thread->stack_size - ((rt_uint32_t) ptr - (rt_uint32_t)thread->stack_addr),
            thread->remaining_tick);
#endif

        rt_kprintf(" 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x \n",
            thread->stack_size + ((rt_uint32_t)thread->stack_addr - (rt_uint32_t)thread->sp),
            thread->stack_addr,
            thread->stack_size,
            thread->stack_size - ((rt_uint32_t) ptr - (rt_uint32_t)thread->stack_addr),
            thread->remaining_tick);
    }
    //rt_hw_interrupt_enable(level);
}

void RTOS_ThreadDisplayStatistics( void )
{
    rt_uint32_t total;
    rt_uint32_t used;
    rt_uint32_t max_used;

    rt_memory_info(&total,&used,&max_used);
    rt_kprintf("\n         memory info       size \n");
    rt_kprintf("--------------------------------- -------\n");
    rt_kprintf("total heap memory :               %d(%dKB)\n", total, total/1024);
    rt_kprintf("used  heap memory :               %d(%dKB)\n", used, used/1024);
    rt_kprintf("maximum allocated heap memory:    %d(%dKB)\n\n", max_used, max_used/1024);
#ifdef CACHE_MEM_MANAGE
    rt_cache_memory_info(&total,&used,&max_used);
    rt_kprintf("total sys  memory :             %d(%dKB)\n", total, total/1024);
    rt_kprintf("used  sys  memory :             %d(%dKB)\n", used, used/1024);
    rt_kprintf("maximum allocated sys memory:   %d(%dKB)\n", max_used, max_used/1024);

    rt_dspmem_memory_info(&total,&used,&max_used);
    rt_kprintf("total drv  memory :             %d(%dKB)\n", total, total/1024);
    rt_kprintf("used  drv  memory :             %d(%dKB)\n", used, used/1024);
    rt_kprintf("maximum allocated drv memory:   %d(%dKB)\n", max_used, max_used/1024);
#endif

    thread_statistics();

    return ;
}

U32 RTOS_GetFreeHeapSize()
{
    rt_uint32_t total;
    rt_uint32_t used;
    rt_uint32_t max_used;

    rt_memory_info(&total,&used,&max_used);

    return (total-used);
}

RTOS_Time RTOS_KernelTimerGetPeriod(void)
{
    return (1000 / RT_TICK_PER_SECOND);
}

//-------------------------sem--------------------------
RTOS_SemaphoreT RTOS_CreateSemaphore( U32 initCount )
{
    return (RTOS_SemaphoreT)rt_sem_create("sem", initCount, RT_IPC_FLAG_PRIO);
}

U32 RTOS_WaitSemaphore(RTOS_SemaphoreT semaphoreHandle, U32 suspend)
{
    if(suspend)
        return RTOS_GetSemaphore((RTOS_Semaphore)semaphoreHandle, RTOS_SUSPEND);
    else
        return RTOS_GetSemaphore((RTOS_Semaphore)semaphoreHandle, RTOS_NO_SUSPEND);
}


U32 RTOS_GetSemaphore( RTOS_SemaphoreT semaphoreHandle,
                           U32 msecsTimeout )
{
    return rt_sem_take((rt_sem_t)semaphoreHandle, msecsTimeout);
}

U32 RTOS_SetSemaphore( RTOS_SemaphoreT semaphoreHandle,
                            U32 msecsTimeout )
{
    return rt_sem_release((rt_sem_t)semaphoreHandle);
}

RTOS_Status RTOS_SemaphoreDestroy( RTOS_Semaphore semaphoreHandle )
{
    return rt_sem_delete((rt_sem_t)semaphoreHandle);
}

RTOS_Status RTOS_DestroySemaphore( RTOS_Semaphore semaphoreHandle )
{
    return rt_sem_delete((rt_sem_t)semaphoreHandle);
}

S32 RTOS_SemaphoreQuery( RTOS_Semaphore semaphoreHandle )
{
    S32 countPtr = 0;
    rt_ubase_t level;

    level = rt_hw_interrupt_disable();

    countPtr = ((rt_sem_t)semaphoreHandle)->value;

    rt_hw_interrupt_enable(level);

    return (S32)countPtr;
}

//-------------------------timer-------------------------
void GKOS_KernelTimerSetHook(RTOS_HookFunction function)
{
    if(gkosHookData)
    {
        if(gkosHookData->timerFunctionCount < (GKOS_TIMER_HOOK_TABLE_SIZE - 1))
        {
            gkosHookData->timerFunctionArray[gkosHookData->timerFunctionCount] = function;
            gkosHookData->timerFunctionCount ++;
        }
    }
}


void RTOS_KernelTimerSetHook(RTOS_HookFunction function)
{
    GKOS_KernelTimerSetHook(function);
}

//-------------------------mail queue-------------------------
#if 0
RTOS_MailqueueT RTOS_MailqueueCreate( U32 queueElements)
{
    struct rt_mailbox *mq;

    mq = rt_mb_create("mqt", queueElements, RT_IPC_FLAG_FIFO);

    return (RTOS_MailqueueT)mq;
}
#endif

RTOS_MailqueueT RTOS_CreateMailqueue( U32 queueElements, U32 elementBytes )
{
    struct rt_mailbox *mq;

    mq = rt_mb_create("mqt", queueElements, RT_IPC_FLAG_FIFO);

    return (RTOS_MailqueueT)mq;
}

RTOS_Status RTOS_MailqueueSend(RTOS_Mailqueue mailqueue, RTOS_Message data)
{
    //rt_kprintf("mail send...0x%x\n", data);
    return rt_mb_send((rt_mailbox_t)mailqueue, (rt_uint32_t)data);
}

RTOS_Status RTOS_MailqueueSendTimeout(RTOS_Mailqueue mailqueue, RTOS_Message data, RTOS_Time timeout)
{
    //rt_kprintf("mail send...0x%x\n", data);
    return rt_mb_send_wait((rt_mailbox_t)mailqueue, (rt_uint32_t)data, timeout);
}

RTOS_Message RTOS_MailqueueWait(RTOS_Mailqueue mailqueue, RTOS_Flag suspend)
{
    int ret;
    U32 timeout;
    U8* messagePtr;

    if( suspend )
        timeout = RTOS_SUSPEND;
    else
        timeout = RTOS_NO_SUSPEND;

    ret = rt_mb_recv((rt_mailbox_t)mailqueue, (void*)(&messagePtr), timeout);
    //rt_kprintf("mail recv [0x%x]...0x%x\n", (U32)timeout, messagePtr);

    if(ret != 0)
        return NULL;

    return (RTOS_Message)messagePtr;
}

RTOS_Message RTOS_MailqueueWaitTimeout( RTOS_Mailqueue mailqueue, RTOS_Time timeout )
{
    U8* messagePtr;
    int ret;

    ret = rt_mb_recv((rt_mailbox_t)mailqueue, (void*)(&messagePtr), timeout);
    //rt_kprintf("mail recv [0x%x]...0x%x\n", (U32)timeout, messagePtr);

    if(ret != 0)
        return NULL;
    return (RTOS_Message)messagePtr;
}

U32 RTOS_MailqueueDestroy( RTOS_MailqueueT mailqueuePtr )
{
    rt_mb_delete((rt_mailbox_t)mailqueuePtr);

    return 0;
}

U32 RTOS_DestroyMailqueue( RTOS_MailqueueT mailqueuePtr )
{
    rt_mb_delete((rt_mailbox_t)mailqueuePtr);

    return 0;
}

U32 RTOS_GetTimerStamp()
{
    return rt_tick_get();
}

/*
*******************************************************************************
**
** Create a new mutex and initializes it with the given value.
**
*******************************************************************************
*/
RTOS_MutexT RTOS_MutexCreate( void )
{
    return( (RTOS_MutexT) rt_mutex_create("mutex", RT_IPC_FLAG_FIFO) );
}

/*
*******************************************************************************
**
** Destroy a given mutex.
**
*******************************************************************************
*/
U32 RTOS_MutexDestroy( RTOS_MutexT mutex )
{

    return rt_mutex_delete( (rt_mutex_t) mutex );
}

/*
*******************************************************************************
**
** Query (read) the current value from a given mutex.
**
*******************************************************************************
*/
S32 RTOS_MutexQuery( RTOS_MutexT mutex )
{

    S32 countPtr = 0;
    rt_ubase_t level;

    level = rt_hw_interrupt_disable();

    countPtr = ((rt_mutex_t)mutex)->value;

    rt_hw_interrupt_enable(level);

    return countPtr;
}

/*
*******************************************************************************
**
** Wait and lock a given mutex
**
*******************************************************************************
*/
U32 RTOS_MutexLock( RTOS_MutexT mutex, RTOS_Flag suspend )
{
    U32 timeout;

    if( suspend )
        timeout = RTOS_SUSPEND;
    else
        timeout = RTOS_NO_SUSPEND;

    return rt_mutex_take( (rt_mutex_t) mutex, timeout );

}

U32 RTOS_MutexLockTimeout( RTOS_MutexT mutex, U32 timeout )
{

    return rt_mutex_take( (rt_mutex_t) mutex, timeout );

}

/*
*******************************************************************************
**
** Unlock an occupied mutex
**
*******************************************************************************
*/
U32 RTOS_MutexUnlock( RTOS_MutexT mutex )
{
    return rt_mutex_release( (rt_mutex_t) mutex );
}


//--------------------------------------------------------
RTOS_ThreadT RTOS_ThreadSelf( void )
{
    return( (RTOS_ThreadT)rt_thread_self() );
}


//-------------------------------------------------------

extern unsigned char __heap_end__[];
gkosHookDataT  HookData;

void RTOS_HwTickInit(void)
{

    GD_HANDLE   timerHandle;
    GBOOL       timerFlag;
    GERR        result;

    GD_INT_DisableAllInterrupts();
    // only use the os's timers
    // RTOS_TIMERTICK_IRQ must use the GD_INT_LOW_PRIORITY mode
    GD_INT_SetVector( GD_INT_TIMER1_IRQ, NULL );
    result = GD_TIMER_SoftTimerOpen( &timerHandle );

    if( result == GD_OK )
    {
        // modify the hard timer to Timer Tick
        result = GD_TIMER_SoftTimerSet( &timerHandle, 1, &timerFlag, NULL );
        GD_INT_SetVector( GD_INT_TIMER1_IRQ, rt_tick_increase );
    }


    int bytes = sizeof(gkosHookDataT);
    gkosHookData = &HookData;
    memset( gkosHookData, 0, bytes );

}

extern u32 ARM1176_MMU_ttb0[4096];


U32 RTOS_InitKernel(U32 Heap_size)
{
    u32 os_end_address=0;
    /* disable interrupt first */
    rt_hw_interrupt_disable();
    /* enable cpu cache */
    //rt_hw_cpu_icache_disable();
    //mmu_invalidate_icache();
    //rt_hw_cpu_icache_enable();

    /* initialize hardware interrupt */
    rt_hw_interrupt_init();

    /* initialize board */
    //rt_hw_board_init();

    /* show version */
    //rt_show_version();

    RTOS_HwTickInit();
    //rt_kprintf("set tick\n");

    /* initialize timer system */
    rt_system_timer_init();

    /* initialize heap memory system */
    os_end_address= (u32)__heap_end__+Heap_size;

#ifdef  CACHE_MEM_MANAGE
    rt_system_heap_init((void*)__heap_end__, (void*)(os_end_address-CACHE_MEM_SIZE-CACHE_DSP_SIZE));

    rt_system_cache_init((void*)(os_end_address-CACHE_MEM_SIZE-CACHE_DSP_SIZE),
                          (void*)(os_end_address-CACHE_DSP_SIZE));
    //cache-buffer for system
    #if 0
    RTOS_MMU_ChangeMapEntry((U32)(os_end_address-CACHE_MEM_SIZE-CACHE_DSP_SIZE),(U32)os_end_address-CACHE_DSP_SIZE,
                            (U32)(os_end_address-CACHE_MEM_SIZE), 0x00000DE2);
    #endif

    rt_system_dspmem_init((void*)(os_end_address-CACHE_DSP_SIZE), (void*)(os_end_address));
    //nocache nobuffer
    RTOS_MMU_ChangeMapEntry((U32)(os_end_address-CACHE_DSP_SIZE), (U32)os_end_address,
                            (U32)(os_end_address-CACHE_DSP_SIZE), 0x00000DE2);

        /* print mmu table */
    //rt_hw_cpu_dump_page_table((rt_uint32_t*)ARM1176_MMU_ttb0);

#else
    rt_system_heap_init((void*)__heap_end__, (void*)os_end_address);
#endif



#ifdef RT_USING_MODULE
    /* initialize module system*/
    rt_system_module_init();
#endif

    /* initialize scheduler system */
    rt_system_scheduler_init();

    return 0;
}

void RTOS_StartMultitasking( void )
{
    #ifdef RT_USING_FINSH
    /* initialize finsh */
    finsh_system_init();
#ifdef RT_USING_DEVICE
    finsh_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
#endif

    /* initialize system timer thread */
    rt_system_timer_thread_init();

    /* initialize idle thread */
    rt_thread_idle_init();

    rt_kprintf("start scheduler\n");
    /* start scheduler */

    rt_system_scheduler_start();

    /* never reach here */
    return ;
}


U32 RTOS_GetMailqueue( RTOS_MailqueueT mailqueueHandle,
                           void* resultBuffer, U32 msecsTimeout )
{
    return rt_mb_recv((rt_mailbox_t)mailqueueHandle,(rt_uint32_t*)resultBuffer,
                        (rt_uint32_t)msecsTimeout);
}

U32 RTOS_SetMailqueue( RTOS_MailqueueT mailqueueHandle,
                           void* messagePtr, U32 toFront,
                           U32 msecsTimeout )
{
    return rt_mb_send_wait((rt_mailbox_t)mailqueueHandle,
                            (rt_uint32_t)messagePtr, (rt_uint32_t)msecsTimeout);
}


/*Dummy func of os*/

//-----------------------------cond------------------------------
RTOS_CondT RTOS_CondCreate( void )
{
    rt_event_t evt;

    evt = rt_event_create("evt", 0);

    /* detach the object from system object container */
    rt_object_detach(&(evt->parent.parent));

    return (RTOS_CondT) evt;
}

RTOS_Status RTOS_CondDestroy( RTOS_CondT cond )
{
    rt_err_t result;
    if (cond == RT_NULL)
        return -2;

    result = rt_event_delete((rt_event_t)cond);
    if (result != RT_EOK)
        return -3;

    return( 0 );
}

int _cond_timedwait(RTOS_CondT  cond, RTOS_MutexT mutex, U32 timeout)
{
    int result;
    rt_uint32_t recved = 0XFF;
    if (!cond || !mutex)
        return -1;

    if(RTOS_MutexUnlock(mutex)!=0) return -2;

    result = rt_event_recv((rt_event_t)cond, 0x01,RT_EVENT_FLAG_AND|RT_EVENT_FLAG_CLEAR,timeout,&recved);
    if(result == -RT_ERROR && recved == 0XFF) // for boardcase event
    {
        result = RT_EOK;
    }
    /* lock mutex again */
    RTOS_MutexLock(mutex, 1);

    return result;
}


RTOS_Status RTOS_CondWait( RTOS_CondT cond, RTOS_MutexT mutex, RTOS_Flag suspend )
{
    S32 value = 0;
    U32 timeout;

    if( suspend )
        timeout = RTOS_SUSPEND;
    else
        timeout = RTOS_NO_SUSPEND;

    value = _cond_timedwait( (RTOS_CondT) cond, (RTOS_MutexT) mutex, timeout );
    if( value != RT_EOK )
        return( -1 );

    return( value );
}

RTOS_Status RTOS_CondWaitTimeout( RTOS_CondT cond, RTOS_MutexT mutex, U32 timeout )
{
    S32 value = 0;

    value = _cond_timedwait( (RTOS_CondT) cond, (RTOS_MutexT) mutex, timeout );
    if( value != RT_EOK )
        return( -1 );

    return( value );
}


RTOS_Status RTOS_CondSignal( RTOS_CondT cond )
{
    RTOS_Status result;

    result = rt_event_send((rt_event_t)cond,0x01);
    if (result != RT_EOK)
        return -1;

    return 0;
}

RTOS_Status RTOS_CondBroadcast( RTOS_CondT cond )
{

    rt_event_control((rt_event_t)cond,RT_IPC_CMD_RESET,0);

    return 0;
}

U32 RTOS_OsType(void)
{
    return RTOS_RTTHREAD;
}


void RTOS_MMU_ChangeMapEntry(U32 vaddrStart, U32 vaddrEnd, U32 paddrStart, U32 attr)
{
    volatile U32 *pTT;
    volatile int i,nSec;

    extern U32 ARM1176_MMU_ttb0[];
    extern U32 ARM1176_MMU_ttb1[];

    U32*   table_ptr  = (U32*)ARM1176_MMU_ttb0;
    //printf("mmu table: 0x%x \n", (U32)ARM1176_MMU_ttb0);

    pTT  = (U32 *)table_ptr + (vaddrStart>>20);
    nSec = (vaddrEnd>>20) - (vaddrStart>>20);
    //printf("change table: 0x%x -- %d\n", (U32)pTT, nSec);

    for(i=0;i<=nSec;i++)
    {
        *pTT = attr |(((paddrStart>>20)+i)<<20);
        pTT++;
    }

    table_ptr  = (U32*)ARM1176_MMU_ttb1;
    //printf("mmu table: 0x%x \n", (U32)ARM1176_MMU_ttb1);

    pTT  = (U32 *)table_ptr + (vaddrStart>>20);
    nSec = (vaddrEnd>>20) - (vaddrStart>>20);
    //printf("change table: 0x%x -- %d\n", (U32)pTT, nSec);

    for(i=0;i<=nSec;i++)
    {
        *pTT = attr |(((paddrStart>>20)+i)<<20);
        pTT++;
    }

}

int RTOS_thread_yield(void)
{
    rt_thread_yield();

    return 0;
}

unsigned int RTOS_jiffies(void)
{
    return jiffies;
}

RTOS_TimerT RTOS_CreateTimer(U32 isContinouos, RTOS_SemaphoreT fireSemaphore, RTOS_HookFunctionT callbackFunction)
{
    //U8 name[32];

    //sprintf(name, "timer %X", (U32)callbackFunction);
    if(isContinouos)
    {
        return (RTOS_TimerT)rt_timer_create("timer", callbackFunction, NULL, 0, RT_TIMER_FLAG_PERIODIC);
    }
    else
    {
        return (RTOS_TimerT)rt_timer_create("timer", callbackFunction, NULL, 0, RT_TIMER_FLAG_ONE_SHOT);
    }
}

RTOS_TimerT RTOS_CreateTimerEx(const char *name, U8 flag, void *parameter, RTOS_TimerFunctionT callbackFunction)
{
    U8 timer_flag = 0;

    if(flag & RTOS_TIMER_FLAG_PERIODIC)
    {
        timer_flag = timer_flag | RT_TIMER_FLAG_PERIODIC;
    }
    else
    {
        timer_flag = timer_flag | RT_TIMER_FLAG_ONE_SHOT;
    }

    if(flag & RTOS_TIMER_FLAG_SOFT_TIMER)
    {
        timer_flag = timer_flag | RT_TIMER_FLAG_SOFT_TIMER;
    }
    else
    {
        timer_flag = timer_flag | RT_TIMER_FLAG_SOFT_TIMER;
    }

    return (RTOS_TimerT)rt_timer_create(name, callbackFunction, parameter, 0, timer_flag);
}


U32 RTOS_DestroyTimer(RTOS_TimerT timerHandle)
{
    return rt_timer_delete((rt_timer_t)timerHandle);
}
U32 RTOS_StartTimer(RTOS_TimerT timerHandle, U32 fireInterval)
{
    rt_timer_t handler = (rt_timer_t)timerHandle;

    handler->init_tick = fireInterval;
    return rt_timer_start((rt_timer_t)timerHandle);
}

U32 RTOS_StopTimer(RTOS_TimerT timerHandle)
{
    return rt_timer_stop((rt_timer_t)timerHandle);
}

U32 RTOS_ControlTimer(RTOS_TimerT timerHandle, U32 delay_time)
{
    return rt_timer_control((rt_timer_t)timerHandle, RT_TIMER_CTRL_SET_TIME, &delay_time);
}

U32 RTOS_GetTimerStatus(RTOS_TimerT timerHandle)
{
    rt_timer_t t;

    t = (rt_timer_t)timerHandle;
    if(t->parent.flag & RT_TIMER_FLAG_ACTIVATED)
    {
        return RTOS_TIMER_FLAG_ACTIVATED;
    }
    else
    {
        return RTOS_TIMER_FLAG_DEACTIVATED;
    }
}

void *RTOS_timer_get_context(RTOS_TimerT timerHandle)
{
    rt_timer_t t;

    t = (rt_timer_t)timerHandle;

    return t->parameter;
}

int RTOS_Thead_Switch_Priority(int priority)
{
    if (priority < RTOS_ThreadPriorityHighest)
    {
        priority = RTOS_ThreadPriorityHighest - priority;
    }
    else
    {
        priority = 1;
    }
    return priority;
}

void usleep(int micro_sec)
{
    int ms = micro_sec/1000;
    rt_thread_delay(ms);
}

void sleep(int sec)
{
    rt_thread_delay(sec*1000);
}
