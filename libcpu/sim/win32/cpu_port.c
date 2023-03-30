/*
************************************************************************************************************************
* File    : cpu_port.c
* By      : xyou
* Version : V1.00.00
*
* By      : prife
* Version : V1.00.01
************************************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/
#include  <rtthread.h>
#include  <windows.h>
#include  <mmsystem.h>
#include  <stdio.h>
#include  "cpu_port.h"

/*
*********************************************************************************************************
*                                             WinThread STRUCTURE
*  Windows runs each task in a thread.
*  The context switch is managed by the threads.So the task stack does not have to be managed directly,
*  although the stack stack is still used to hold an WinThreadState structure this is the only thing it
*  will be ever hold.
*  YieldEvent used to make sure the thread does not execute before asynchronous SuspendThread() operation
*  actually being performed.
*  the structure indirectly maps the task handle to a thread handle
*********************************************************************************************************
*/
typedef struct
{
    void            *Param;                     //Thread param
    void            (*Entry)(void *);           //Thread entry
    void            (*Exit)(void);                      //Thread exit
    HANDLE          YieldEvent;
    HANDLE          ThreadHandle;
    DWORD           ThreadID;
}win_thread_t;

const DWORD MS_VC_EXCEPTION=0x406D1388;

#pragma pack(push,8)
typedef struct tagTHREADNAME_INFO
{
    DWORD dwType; // Must be 0x1000.
    LPCSTR szName; // Pointer to name (in user addr space).
    DWORD dwThreadID; // Thread ID (-1=caller thread).
    DWORD dwFlags; // Reserved for future use, must be zero.
} THREADNAME_INFO;
#pragma pack(pop)

/*
*********************************************************************************************************
*                                             LOCAL DEFINES
*********************************************************************************************************
*/
#define MAX_INTERRUPT_NUM       ((rt_uint32_t)sizeof(rt_uint32_t) * 8)

/*
 * Simulated interrupt waiting to be processed.this is a bit mask where each bit represent one interrupt
 * so a maximum of 32 interrupts can be simulated
 */
static volatile rt_uint32_t  CpuPendingInterrupts = 0;

/*
 * An event used to inform the simulated interrupt processing thread (a high priority thread
 *      that simulated interrupt processing) that an interrupt is pending
 */
static HANDLE   hInterruptEventHandle = NULL;

/*
 * Mutex used to protect all the simulated interrupt variables that are accessed by multiple threads
 */
static HANDLE   hInterruptEventMutex = NULL;

/*
 * Handler for all the simulate software interrupts.
 * The first two positions are used the Yield and Tick interrupt so are handled slightly differently
 * all the other interrupts can be user defined
*/
static rt_uint32_t (*CpuIsrHandler[MAX_INTERRUPT_NUM])(void) = {0};

/*
 * Handler for OSTick Thread
 */
static HANDLE       OSTick_Thread;
static DWORD        OSTick_ThreadID;
static HANDLE       OSTick_SignalPtr;
static TIMECAPS     OSTick_TimerCap;
static MMRESULT     OSTick_TimerID;

/*
 * flag in interrupt handling
 */
rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

/*
*********************************************************************************************************
*                                             PRIVATE FUNCTION PROTOTYPES
*********************************************************************************************************
*/
//static void WinThreadScheduler(void);
void WinThreadScheduler(void);
rt_uint32_t YieldInterruptHandle(void);
rt_uint32_t SysTickInterruptHandle(void);
static DWORD WINAPI ThreadforSysTickTimer(LPVOID lpParam);
static DWORD WINAPI ThreadforKeyGet(LPVOID lpParam);

static void SetThreadName(DWORD dwThreadID, char* threadName)
{
#if defined(_MSC_VER)
    THREADNAME_INFO info;
    info.dwType = 0x1000;
    info.szName = threadName;
    info.dwThreadID = dwThreadID;
    info.dwFlags = 0;

    __try
    {
        RaiseException( MS_VC_EXCEPTION, 0, sizeof(info)/sizeof(ULONG_PTR), (ULONG_PTR*)&info );
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
    }
#endif
}

/*
*********************************************************************************************************
*                                            rt_hw_stack_init()
* Description : Initialize stack of thread
* Argument(s) : void *pvEntry,void *pvParam,rt_uint8_t *pStackAddr,void *pvExit
* Return(s)   : rt_uint8_t*
* Caller(s)   : rt_thread_init or rt_thread_create
* Note(s)     : none
*********************************************************************************************************
*/

static DWORD WINAPI thread_run( LPVOID lpThreadParameter )
{
    rt_thread_t tid = rt_thread_self();
    win_thread_t  *pWinThread = (win_thread_t *)lpThreadParameter;

    SetThreadName(GetCurrentThreadId(), tid->parent.name);

    pWinThread->Entry(pWinThread->Param);

    pWinThread->Exit();
    return 0;
}

rt_uint8_t* rt_hw_stack_init(void *pEntry,void *pParam,rt_uint8_t *pStackAddr,void *pExit)
{
    win_thread_t    *pWinThread = NULL;

    /*
     * In this simulated case a stack is not initialized
     * The thread handles the context switching itself. The WinThreadState object is placed onto the stack
     * that was created for the task
     * so the stack buffer is still used,just not in the conventional way.
     */
    pWinThread = (win_thread_t *)(pStackAddr - sizeof(win_thread_t));

    pWinThread->Entry = pEntry;
    pWinThread->Param = pParam;
    pWinThread->Exit = pExit;

    pWinThread->ThreadHandle = NULL;
    pWinThread->ThreadID = 0;

    pWinThread->YieldEvent = CreateEvent(NULL,
                                         FALSE,
                                         FALSE,
                                         NULL);

    /* Create the winthread */
    pWinThread->ThreadHandle = CreateThread(NULL,
                                            0,
                                            (LPTHREAD_START_ROUTINE) thread_run,
                                            pWinThread,
                                            CREATE_SUSPENDED,
                                            &(pWinThread->ThreadID));
    SetThreadAffinityMask(pWinThread->ThreadHandle,
                          0x01);
    SetThreadPriorityBoost(pWinThread->ThreadHandle,
                           TRUE);
    SetThreadPriority(pWinThread->ThreadHandle,
                      THREAD_PRIORITY_IDLE);

    return (rt_uint8_t*)pWinThread;
} /*** rt_hw_stack_init ***/

/*
*********************************************************************************************************
*                                            rt_hw_interrupt_disable()
* Description : disable cpu interrupts
* Argument(s) : void
* Return(s)   : rt_base_t
* Caller(s)   : Applicatios or os_kernel
* Note(s)     : none
*********************************************************************************************************
*/
rt_base_t rt_hw_interrupt_disable(void)
{
    if(hInterruptEventMutex != NULL)
    {
        WaitForSingleObject(hInterruptEventMutex,INFINITE);
    }

    return 0;
} /*** rt_hw_interrupt_disable ***/


/*
*********************************************************************************************************
*                                            rt_hw_interrupt_enable()
* Description : enable cpu interrupts
* Argument(s) : rt_base_t level
* Return(s)   : void
* Caller(s)   : Applications or os_kernel
* Note(s)     : none
*********************************************************************************************************
*/
void rt_hw_interrupt_enable(rt_base_t level)
{
    level = level;

    if (hInterruptEventMutex != NULL)
    {
        ReleaseMutex(hInterruptEventMutex);
    }

} /*** rt_hw_interrupt_enable ***/

/*
*********************************************************************************************************
*                                            rt_hw_context_switch_interrupt()
* Description : switch thread's contex
* Argument(s) : void
* Return(s)   : void
* Caller(s)   : os kernel
* Note(s)     : none
*********************************************************************************************************
*/
void rt_hw_context_switch_interrupt(rt_uint32_t from,
                                    rt_uint32_t to)
{
    if(rt_thread_switch_interrupt_flag != 1)
    {
        rt_thread_switch_interrupt_flag = 1;

        // set rt_interrupt_from_thread
        rt_interrupt_from_thread = *((rt_uint32_t *)(from));
    }

    rt_interrupt_to_thread = *((rt_uint32_t *)(to));

    //trigger YIELD exception(cause context switch)
    TriggerSimulateInterrupt(CPU_INTERRUPT_YIELD);
} /*** rt_hw_context_switch_interrupt ***/



void rt_hw_context_switch(rt_uint32_t from,
                          rt_uint32_t to)
{
    if(rt_thread_switch_interrupt_flag != 1)
    {
        rt_thread_switch_interrupt_flag  = 1;

        // set rt_interrupt_from_thread
        rt_interrupt_from_thread = *((rt_uint32_t *)(from));

    }

    // set rt_interrupt_to_thread
    rt_interrupt_to_thread = *((rt_uint32_t *)(to));

    //trigger YIELD exception(cause contex switch)
    TriggerSimulateInterrupt(CPU_INTERRUPT_YIELD);

    // make sure the event is not already signaled
    win_thread_t *WinThread = (win_thread_t *)rt_interrupt_from_thread;
    ResetEvent(WinThread->YieldEvent);

    /*
     * enable interrupt in advance so that scheduler can be executed.please note that interrupt
     * maybe disable twice before.
     */
    rt_hw_interrupt_enable(0);
    rt_hw_interrupt_enable(0);

    // wait to suspend.
    WaitForSingleObject(WinThread->YieldEvent, INFINITE);
} /*** rt_hw_context_switch ***/

/*
*********************************************************************************************************
*                                            rt_hw_context_switch_to()
* Description : switch to new thread
* Argument(s) : rt_uint32_t to              //the stack address of the thread which will switch to
* Return(s)   : void
* Caller(s)   : rt_thread schecale
* Note(s)     : this function is used to perform the first thread switch
*********************************************************************************************************
*/
void rt_hw_context_switch_to(rt_uint32_t to)
{
    //set to thread
    rt_interrupt_to_thread = *((rt_uint32_t *)(to));

    //clear from thread
    rt_interrupt_from_thread = 0;

    //set interrupt to 1
    rt_thread_switch_interrupt_flag = 1;

    //start WinThreadScheduler
    WinThreadScheduler();

    //never reach here!
    return;

} /*** rt_hw_context_switch_to ***/



/*
*********************************************************************************************************
*                                            TriggerSimulateInterrupt()
* Description : Trigger a simulated interrupts handle
* Argument(s) : t_uint32_t IntIndex
* Return(s)   : void
* Caller(s)   : Applications
* Note(s)     : none
*********************************************************************************************************
*/
void TriggerSimulateInterrupt(rt_uint32_t IntIndex)
{
    if((IntIndex < MAX_INTERRUPT_NUM) && (hInterruptEventMutex != NULL))
    {
        /* Yield interrupts are processed even when critical nesting is non-zero  */
        WaitForSingleObject(hInterruptEventMutex,
                            INFINITE);

        CpuPendingInterrupts |= (1 << IntIndex);

        SetEvent(hInterruptEventHandle);

        ReleaseMutex(hInterruptEventMutex);
    }
} /*** TriggerSimulateInterrupt ***/

/*
*********************************************************************************************************
*                                            RegisterSimulateInterrupt()
* Description : Register a interrupt handle to simulate paltform
* Argument(s) : rt_uint32_t IntIndex,rt_uint32_t (*IntHandler)(void)
* Return(s)   : void
* Caller(s)   : Applications
* Note(s)     : none
*********************************************************************************************************
*/
void RegisterSimulateInterrupt(rt_uint32_t IntIndex,rt_uint32_t (*IntHandler)(void))
{
    if(IntIndex < MAX_INTERRUPT_NUM)
    {
        if (hInterruptEventMutex != NULL)
        {
            WaitForSingleObject(hInterruptEventMutex,
                                INFINITE);

            CpuIsrHandler[IntIndex] = IntHandler;

            ReleaseMutex(hInterruptEventMutex);
        }
        else
        {
            CpuIsrHandler[IntIndex] = IntHandler;
        }
    }

} /*** RegisterSimulateInterrupt ***/



/*
*********************************************************************************************************
*                                             PRIVATE FUNCTION
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            WinThreadScheduler()
* Description : Handle all simulate interrupts
* Argument(s) : void
* Return(s)   : static void
* Caller(s)   : os scachle
* Note(s)     : none
*********************************************************************************************************
*/
#define WIN_WM_MIN_RES      (1)
 void WinThreadScheduler(void)
{
    HANDLE          hInterruptObjectList[2];
    HANDLE          hThreadHandle;
    rt_uint32_t     SwitchRequiredMask;
    rt_uint32_t     i;

    win_thread_t    *WinThreadFrom;
    win_thread_t    *WinThreadTo;

    /*
     * Install the interrupt handlers used bye scheduler itself
     */
    RegisterSimulateInterrupt(CPU_INTERRUPT_YIELD,
                              YieldInterruptHandle);
    RegisterSimulateInterrupt(CPU_INTERRUPT_TICK,
                              SysTickInterruptHandle);

    /*
     * Create the events and mutex that are used to synchronise all the WinThreads
     */
    hInterruptEventMutex = CreateMutex(NULL,
                                       FALSE,
                                       NULL);
    hInterruptEventHandle = CreateEvent(NULL,
                                        FALSE,
                                        FALSE,
                                        NULL);

    if((hInterruptEventMutex == NULL) || (hInterruptEventHandle == NULL))
    {
        return;
    }

    /*
     * Set the priority of this WinThread such that it is above the priority of the WinThreads
     * that run rt-threads.
     * This is higher priority is required to ensure simulate interrupts take priority over rt-threads
     */
    hThreadHandle = GetCurrentThread();
    if(hThreadHandle == NULL)
    {
        return;
    }

    if (SetThreadPriority(hThreadHandle,
                          THREAD_PRIORITY_HIGHEST) == 0)
    {
        return;
    }
    SetThreadPriorityBoost(hThreadHandle,
                           TRUE);
    SetThreadAffinityMask(hThreadHandle,
                          0x01);

    /*
     * Start the thread that simulates the timer peripheral to generate tick interrupts.
     */
    OSTick_Thread = CreateThread(NULL,
                                 0,
                                 ThreadforSysTickTimer,
                                 0,
                                 CREATE_SUSPENDED,
                                 &OSTick_ThreadID);
    if(OSTick_Thread == NULL)
    {
        //Display Error Message


        return;
    }
    SetThreadPriority(OSTick_Thread,
                      THREAD_PRIORITY_NORMAL);
    SetThreadPriorityBoost(OSTick_Thread,
                           TRUE);
    SetThreadAffinityMask(OSTick_Thread,
                          0x01);

    /*
     * Set timer Caps
     */
    if (timeGetDevCaps(&OSTick_TimerCap,
                       sizeof(OSTick_TimerCap)) != TIMERR_NOERROR)
    {

        CloseHandle(OSTick_Thread);

        return;
    }
    if (OSTick_TimerCap.wPeriodMin < WIN_WM_MIN_RES)
    {
        OSTick_TimerCap.wPeriodMin = WIN_WM_MIN_RES;
    }

    if(timeBeginPeriod(OSTick_TimerCap.wPeriodMin) != TIMERR_NOERROR)
    {
        CloseHandle(OSTick_Thread);

        return;
    }

    OSTick_SignalPtr = CreateEvent(NULL,TRUE,FALSE,NULL);
    if(OSTick_SignalPtr == NULL)
    {
        // disp error message

        timeEndPeriod(OSTick_TimerCap.wPeriodMin);
        CloseHandle(OSTick_Thread);

        return;
    }

    OSTick_TimerID = timeSetEvent((UINT             )   (1000 / RT_TICK_PER_SECOND) ,
                                  (UINT             )   OSTick_TimerCap.wPeriodMin,
                                  (LPTIMECALLBACK   )   OSTick_SignalPtr,
                                  (DWORD_PTR        )   NULL,
                                  (UINT             )   (TIME_PERIODIC | TIME_CALLBACK_EVENT_SET));

    if(OSTick_TimerID == 0)
    {
        //disp

        CloseHandle(OSTick_SignalPtr);
        timeEndPeriod(OSTick_TimerCap.wPeriodMin);
        CloseHandle(OSTick_Thread);

        return;
    }

    /*
     * Start OS Tick Thread an release Interrupt Mutex
     */
    ResumeThread(OSTick_Thread);
    ReleaseMutex( hInterruptEventMutex );

    //trigger YEILD INTERRUPT
    TriggerSimulateInterrupt(CPU_INTERRUPT_YIELD);

    /*
     * block on the mutex that ensure exclusive access to the simulated interrupt objects
     *  and the events that signals that a simulated interrupt should be processed.
     */

    hInterruptObjectList[0] = hInterruptEventHandle;
    hInterruptObjectList[1] = hInterruptEventMutex;


    while (1)
    {
        WaitForMultipleObjects(sizeof(hInterruptObjectList) / sizeof(HANDLE),
                               hInterruptObjectList,
                               TRUE,
                               INFINITE);

        /*
         * Used to indicate whether the simulate interrupt processing has necessitated a contex
         * switch to another thread
         */
        SwitchRequiredMask = 0;

        /*
         * For each interrupt we are interested in processing ,each of which is represented
         * by a bit in the 32bit CpuPendingInterrupts variable.
         */
        for (i = 0; i < MAX_INTERRUPT_NUM; ++i)
        {
            /* is the simulated interrupt pending ? */
            if (CpuPendingInterrupts & (1UL << i))
            {
                /* Is a handler installed ?*/
                if (CpuIsrHandler[i] != NULL)
                {
                    /* Run the actual handler */
                    if (CpuIsrHandler[i]() != 0)
                    {
                        SwitchRequiredMask |= (1UL << i);
                    }
                }

                /* Clear the interrupt pending bit */
                CpuPendingInterrupts &= ~(1UL << i);
            }
        }

        if(SwitchRequiredMask != 0)
        {
            WinThreadFrom = (win_thread_t *)rt_interrupt_from_thread;
            WinThreadTo = (win_thread_t *)rt_interrupt_to_thread;

            if ((WinThreadFrom != NULL) && (WinThreadFrom->ThreadHandle != NULL))
            {
                SuspendThread(WinThreadFrom->ThreadHandle);
                SetEvent(WinThreadFrom->YieldEvent);
            }

            ResumeThread(WinThreadTo->ThreadHandle);

        }

        ReleaseMutex(hInterruptEventMutex);
    }
} /*** WinThreadScheduler ***/



/*
*********************************************************************************************************
*                                            ThreadforSysTickTimer()
* Description : win thread to simulate a systick timer
* Argument(s) : LPVOID lpParam
* Return(s)   : static DWORD WINAPI
* Caller(s)   : none
* Note(s)     : This is not a real time way of generating tick events as the next wake time should be relative
*               to the previous wake time,not the time Sleep() is called.
*               It is done this way to prevent overruns in this very non real time simulated/emulated environment
*********************************************************************************************************
*/
static DWORD WINAPI ThreadforSysTickTimer(LPVOID lpParam)
{

    (void)lpParam;              //prevent compiler warnings

    for(;;)
    {
        /*
         * Wait until the timer expires and we can access the simulated interrupt variables.
         */
        WaitForSingleObject(OSTick_SignalPtr,INFINITE);

        ResetEvent(OSTick_SignalPtr);

        /*
         * Trigger a systick interrupt
         */
        TriggerSimulateInterrupt(CPU_INTERRUPT_TICK);

    }

    return 0;

} /*** prvThreadforSysTickTimer ***/

/*
*********************************************************************************************************
*                                            SysTickInterruptHandle()
* Description : Interrupt handle for systick
* Argument(s) : void
* Return(s)   : rt_uint32_t
* Caller(s)   : none
* Note(s)     : none
*********************************************************************************************************
*/
rt_uint32_t SysTickInterruptHandle(void)
{

    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();

    return 0;
} /*** SysTickInterruptHandle ***/

/*
*********************************************************************************************************
*                                            YieldInterruptHandle()
* Description : Interrupt handle for Yield
* Argument(s) : void
* Return(s)   : rt_uint32_t
* Caller(s)   : none
* Note(s)     : none
*********************************************************************************************************
*/
rt_uint32_t YieldInterruptHandle(void)
{

    /*
     * if rt_thread_switch_interrupt_flag = 1 yield already handled
     */
    if(rt_thread_switch_interrupt_flag != 0)
    {
        rt_thread_switch_interrupt_flag = 0;

        /* return thread switch request = 1 */
        return 1;
    }

    return 0;
} /*** YieldInterruptHandle ***/

/* system entry */
extern int rtthread_startup(void);
int wmain(int argc, char* argv[])
{
    /* disable interrupt first */
    rt_hw_interrupt_disable();
    /* startup RT-Thread RTOS */
    rtthread_startup();
}
#pragma comment(linker, "/subsystem:console /entry:wmainCRTStartup")
