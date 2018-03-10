#ifndef RTOS_LIB_H
#define RTOS_LIB_H
#include <limits.h>
#include <string.h>
#include "rthw.h"
#include "rtthread.h"

#include "gtypes.h"    /* global type definitions */
#include "gd_int.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void(*RTOS_ThreadFunctionT)(void*);
typedef void(*RTOS_HookFunctionT)(void*);
typedef void (*RTOS_TimerFunctionT)(void *);
typedef void* RTOS_ThreadT;
typedef void* RTOS_EventT;
typedef void* RTOS_SemaphoreT;
typedef void* RTOS_MailboxT;
typedef void* RTOS_MailqueueT;
typedef void* RTOS_MutexT;
typedef void* RTOS_TimerT;
typedef void* RTOS_CondT;

typedef U32   RTOS_SYS_SemaphoreT;
typedef void* RTOS_SYS_MailqueueT;

//typedef struct rt_thread *RTOS_ThreadT;
//typedef struct rt_semaphore * RTOS_SemaphoreT;
//typedef struct rt_messagequeue *RTOS_MailqueueT;
//typedef struct rt_mailbox *RTOS_MailqueueT;
//typedef struct rt_mutex *RTOS_MutexT;

/*
********************************************************************************
********************************************************************************
**
** macros to define various suspend modes
**
********************************************************************************
********************************************************************************
*/
#define RTOS_OK                     (RTOS_Status)0   //!< The OK status
#define RTOS_FAILURE                (RTOS_Status)-1  //!< The general FAILURE status


#define RTOS_NO_SUSPEND                0x00000000UL //!< do not suspend, return immediately
#define RTOS_SUSPEND                   0xFFFFFFFFUL //!< suspend forever, wait for valid event without timeout

#define RTOS_MAX_MAILQUEUE_ENTRIES     4096
#define RTOS_MSG_IS_POINTER 0xFFFFFFFFUL //!< the message to transport is a generic pointer only

typedef GBOOL                    RTOS_Flag;             //!< the boolean flag type
typedef S32                      RTOS_Status;           //!< the result status type
typedef S32                      RTOS_Size;             //!< the generic size type
typedef U32                      RTOS_Time;             //!< the generic time type
typedef RTOS_TimerT              RTOS_Timer;            //!< the generic time type
typedef RTOS_ThreadT             RTOS_Thread;           //!< the thread identifier type
typedef S32                      RTOS_Priority;         //!< the generic priority type
typedef RTOS_SemaphoreT          RTOS_Semaphore;        //!< the semaphore identifier type
typedef RTOS_MutexT              RTOS_Mutex;            //!< the mutex semaphore identifier type
typedef RTOS_MailboxT            RTOS_Mailbox;          //!< the mailbox identifier type
typedef RTOS_MailqueueT          RTOS_Mailqueue;        //!< the mailqueue identifier type
typedef void*                    RTOS_Message;          //!< the generic message identifier type
typedef void*                    RTOS_Memory;           //!< the generic memory pointer type
typedef U32                      RTOS_Segment;          //!< the memory heap segment type
typedef RTOS_ThreadFunctionT     RTOS_ThreadFunction;   //!< the thread function definition type
typedef RTOS_HookFunctionT       RTOS_HookFunction;     //!< the hook function definition type
typedef RTOS_ThreadT             RTOS_ThreadData;       //!< the optional thread data structure
typedef RTOS_CondT               RTOS_Cond;             //!< the cond semaphore identifier type


#define GKOS_TIMER_HOOK_TABLE_SIZE   8    //!< number of timer-tick hook function entries
#define GKOS_SWITCH_HOOK_TABLE_SIZE  4    //!< number of context-switch hook function entries

#define RTOS_ThreadPriorityHighest (RTOS_Priority)127 //!< The highest possible priority
#define RTOS_ThreadPriorityLowest  (RTOS_Priority)1   //!< The lowest possible priority

/*
********************************************************************************
********************************************************************************
**
** rtos type, gkos:0, rtthread:1
**
********************************************************************************
********************************************************************************
*/
#define RTOS_GKOS                   0
#define RTOS_RTTHREAD               1

#define RTOS_TIMER_FLAG_DEACTIVATED       0x0             /**< timer is deactive */
#define RTOS_TIMER_FLAG_ACTIVATED         0x1             /**< timer is active */
#define RTOS_TIMER_FLAG_ONE_SHOT          0x0             /**< one shot timer */
#define RTOS_TIMER_FLAG_PERIODIC          0x2             /**< periodic timer */

#define RTOS_TIMER_FLAG_HARD_TIMER        0x0             /**< hard timer,the timer's callback function will be called in tick isr. */
#define RTOS_TIMER_FLAG_SOFT_TIMER        0x4             /**< soft timer,the timer's callback function will be called in timer thread. */

#define RTOS_TIMER_CTRL_SET_TIME          0x0             /**< set timer control command */
#define RTOS_TIMER_CTRL_GET_TIME          0x1             /**< get timer control command */
#define RTOS_TIMER_CTRL_SET_ONESHOT       0x2             /**< change timer to one shot */
#define RTOS_TIMER_CTRL_SET_PERIODIC      0x3             /**< change timer to periodic */

typedef struct
{
    RTOS_HookFunctionT timerFunctionArray[GKOS_TIMER_HOOK_TABLE_SIZE];
    U32                timerFunctionCount;
    RTOS_HookFunctionT switchFunctionArray[GKOS_SWITCH_HOOK_TABLE_SIZE];
    U32                switchFunctionCount;
}gkosHookDataT;

gkosHookDataT*      gkosHookData;


#define THREAD_TIMESLICE       10

#define RTOS_ThreadCreate(function,arg,priority,stackBuffer,stackSize)  \
        RTOS_CreateThread(stackBuffer, stackSize, priority, function, arg, 0, 0)
U32 RTOS_DestroyThread( RTOS_ThreadT threadHandle );

#define RTOS_ThreadSleep(msecs)    rt_thread_delay(msecs)



U32 RTOS_ThreadSetName( RTOS_ThreadT threadHandle, const char* optName);
U32 RTOS_SetThreadName( RTOS_ThreadT threadHandle, const char* optName);
char * RTOS_ThreadGetName();




RTOS_Status RTOS_MemoryRelease( RTOS_Memory memory );
RTOS_Memory RTOS_MemoryAllocate( RTOS_Size bytes, RTOS_Flag shared );
RTOS_Memory RTOS_MemorySet( RTOS_Memory mem, U8 value, RTOS_Size bytes );
RTOS_Memory RTOS_MemoryCopy( RTOS_Memory dst, RTOS_Memory src, RTOS_Size bytes );

RTOS_Memory RTOS_KernelMemoryAllocate( RTOS_Size bytes);
RTOS_Status RTOS_KernelMemoryRelease( RTOS_Memory memory );

#define RTOS_ATOM_PRINTF(format, ...)   do {\
        U32 pval = 0;\
        RTOS_EnterCritical(pval);\
        printf("\033[0;31m[@%s.%d]->"format"\033[0;0m\n", __FUNCTION__, __LINE__, ##__VA_ARGS__);\
        RTOS_LeaveCritical(pval);\
    }while(0)

#define RTOS_ASSERT(EX)                                                         \
    if (!(EX))                                                                    \
    {                                                                             \
        volatile char dummy = 0;                                                  \
        U32 pval = 0;\
        RTOS_EnterCritical(pval);\
        printf("(%s) assert failed at %s:%d thread name:%s\n", #EX, __FUNCTION__, __LINE__, RTOS_ThreadGetSelfName());\
        while (dummy == 0);                                                       \
    }

//U32 GKOS_EnterCriticalSection( void );
//void GKOS_LeaveCriticalSection( U32 cpuStatus );

void RTOS_LockScheduler( void );
void RTOS_UnlockScheduler( void );

void gkosFinishThread( void );

U32 RTOS_SleepThread( U32 msecs );


RTOS_SemaphoreT RTOS_CreateSemaphore( U32 initCount );
U32 RTOS_GetSemaphore( RTOS_SemaphoreT semaphoreHandle, U32 msecsTimeout );
U32 RTOS_SetSemaphore( RTOS_SemaphoreT semaphoreHandle, U32 msecsTimeout );
S32 RTOS_SemaphoreQuery( RTOS_Semaphore semaphoreHandle );
RTOS_Status RTOS_SemaphoreDestroy( RTOS_Semaphore semaphoreHandle );

#define RTOS_SemaphoreWait(semaphoreHandle, suspend)		RTOS_WaitSemaphore(semaphoreHandle, suspend)
#define RTOS_SemaphoreWaitTimeout(semaphoreHandle, timeout) RTOS_GetSemaphore((RTOS_Semaphore)semaphoreHandle, timeout)
#define RTOS_SemaphoreCreate(initCount)                     RTOS_CreateSemaphore(initCount)
#define RTOS_SemaphoreRelease(semaphoreHandle)              RTOS_SetSemaphore((RTOS_Semaphore)semaphoreHandle,RTOS_SUSPEND)


void RTOS_HwTickInit(void);


void RTOS_KernelTimerSetHook(RTOS_HookFunction function);


RTOS_MailqueueT RTOS_CreateMailqueue( U32 queueElements, U32 elementBytes );
#define RTOS_MailqueueCreate(elements)      RTOS_CreateMailqueue(elements, RTOS_MSG_IS_POINTER)


#define RTOS_EnterCritical(cpusr)   {cpusr=rt_hw_interrupt_disable();}
#define RTOS_LeaveCritical(cpusr)   {rt_hw_interrupt_enable(cpusr);}

extern U32 cpu_cpsr;

#define RTOS_EnterCriticalEx()   cpu_cpsr = RTOS_EnterCriticalSection()
#define RTOS_LeaveCriticalEx()   RTOS_LeaveCriticalSection(cpu_cpsr)

#define RTOS_ThreadSuspend(threadHandle)                                RTOS_SuspendThread(threadHandle)
#define RTOS_ThreadWakeup(threadHandle)                                 RTOS_WakeupThread(threadHandle)

RTOS_Status RTOS_MailqueueSend(RTOS_Mailqueue mailqueue, RTOS_Message data);

#define isb() __asm__ __volatile__ ("mcr p15, 0, %0, c7, c5, 4" \
                                    : : "r" (0) : "memory")
#define dsb() __asm__ __volatile__ ("mcr p15, 0, %0, c7, c10, 4" \
                                    : : "r" (0) : "memory")
#define dmb() __asm__ __volatile__ ("mcr p15, 0, %0, c7, c10, 5" \
                                    : : "r" (0) : "memory")

void 	rtos_cache_inv_range(void *addr, unsigned int size);
void 	rtos_cache_clean_range(void *addr, unsigned int size);


U32 RTOS_Initialize(U32 Heap_size);

#define RTOS_Initialize             RTOS_InitKernel

#define RTOS_GetIdentity            RTOS_GetIdentity


#ifdef __cplusplus
}
#endif


/*
********************************************************************************
** end of file
********************************************************************************
*/
#endif /* RTOS_LIB_H */



