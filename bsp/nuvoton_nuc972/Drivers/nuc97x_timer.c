/*
 * File      : nuc97x_timer.c
 * This file is part of RT-Thread RTOS
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/05/28     Urey         first implementation
 */
#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "nuc97x_conf.h"




/** \brief  Structure type of Timer Event
 */
#define TimerEventCount     10
typedef void (*sys_pvTimeFunPtr)();   /* function pointer */
typedef struct timeEvent_t {
    UINT32              active;     /*!< Active */
    UINT32              initTick;   /*!< init tick count */
    UINT32              curTick;    /*!< current tick count */
    sys_pvTimeFunPtr    funPtr;     /*!< callback function */
} TimeEvent_T;


/* Global variables */
rt_isr_handler_t  _sys_pvOldTimer0Vect, _sys_pvOldTimer1Vect;
UINT32 _sys_uTimer0ClockRate = 12000000;
UINT32 _sys_uTimer1ClockRate = 12000000;

UINT32 volatile _sys_uTimer0Count = 0, _sys_uTimer1Count = 0;
UINT32  volatile _sys_ReferenceTime_Clock = 0;
UINT32  volatile _sys_ReferenceTime_UTC;
BOOL   _sys_bIsSetTime0Event = FALSE, _sys_bIsSetTime1Event = FALSE;
UINT32 volatile _sys_uTime0EventCount = 0, _sys_uTime1EventCount = 0;
UINT32 volatile _sys_uTimer0TickPerSecond;
BOOL volatile _sys_bIsTimer0Initial = FALSE;
TimeEvent_T tTime0Event[TimerEventCount], tTime1Event[TimerEventCount];

/* Interrupt service routine */
void sysTimer0ISR(int vector,void *param)
{
    int volatile i;

    /*----- check channel 0 -----*/
    if (inpw(REG_TMR_TISR) & 0x00000001)
    {
        _sys_uTimer0Count++;
        outpw(REG_TMR_TISR, 0x01); /* clear TIF0 */
        if (_sys_uTimer0Count >= 0xfffffff)
            _sys_uTimer0Count = 0;

        if (_sys_bIsSetTime0Event)
        {
            for (i = 0; i < TimerEventCount; i++)
            {
                if (tTime0Event[i].active)
                {
                    tTime0Event[i].curTick--;
                    if (tTime0Event[i].curTick == 0)
                    {
                        (*tTime0Event[i].funPtr)();
                        tTime0Event[i].curTick = tTime0Event[i].initTick;
                    }
                }
            }
        }
    }
}

void sysTimer1ISR(int vector,void *param)
{
    int volatile i;

    /*----- check channel 1 -----*/
    if (inpw(REG_TMR_TISR) & 0x00000002)
    {
        _sys_uTimer1Count++;
        outpw(REG_TMR_TISR, 0x02); /* clear TIF1 */
        if (_sys_uTimer1Count >= 0xfffffff)
            _sys_uTimer1Count = 0;

        if (_sys_bIsSetTime1Event)
        {
            for (i = 0; i < TimerEventCount; i++)
            {
                if (tTime1Event[i].active)
                {
                    tTime1Event[i].curTick--;
                    if (tTime1Event[i].curTick == 0)
                    {
                        (*tTime1Event[i].funPtr)();
                        tTime1Event[i].curTick = tTime1Event[i].initTick;
                    }
                }
            }
        }
    }
}

/**
 *  @brief  system Timer - get current tick count
 *
 *  @param[in]  nTimeNo  Select TMR0 or TMR1. ( \ref TIMER0 / \ref TIMER1)
 *
 *  @return   Current tick count
 */
UINT32 sysGetTicks(INT32 nTimeNo)
{
    switch (nTimeNo)
    {
        case TIMER0:
            return _sys_uTimer0Count;

        case TIMER1:
            return _sys_uTimer1Count;

        default:
            ;
    }
    return 0;
}

/**
 *  @brief  system Timer - reset current tick count
 *
 *  @param[in]  nTimeNo  Select TMR0 or TMR1. ( \ref TIMER0 / \ref TIMER1)
 *
 *  @return   0
 */
INT32 sysResetTicks(INT32 nTimeNo)
{
    switch (nTimeNo)
    {
        case TIMER0:
            _sys_uTimer0Count = 0;
            break;

        case TIMER1:
            _sys_uTimer1Count = 0;
            break;

        default:
            ;
    }
    return 0;
}

/**
 *  @brief  system Timer - update current tick count
 *
 *  @param[in]  nTimeNo  Select TMR0 or TMR1. ( \ref TIMER0 / \ref TIMER1)
 *  @param[in]  uCount   Update count
 *
 *  @return   0
 */
INT32 sysUpdateTickCount(INT32 nTimeNo, UINT32 uCount)
{
    switch (nTimeNo)
    {
        case TIMER0:
            _sys_uTimer0Count = uCount;
            break;

        case TIMER1:
            _sys_uTimer1Count = uCount;
            break;

        default:
            ;
    }
    return 0;
}

/**
 *  @brief  system Timer - set timer reference clock
 *
 *  @param[in]  nTimeNo  Select TMR0 or TMR1. ( \ref TIMER0 / \ref TIMER1)
 *  @param[in]  uClockRate   reference clock
 *
 *  @return   0
 */
INT32 sysSetTimerReferenceClock(INT32 nTimeNo, UINT32 uClockRate)
{
    switch (nTimeNo)
    {
        case TIMER0:
            _sys_uTimer0ClockRate = uClockRate;
            break;

        case TIMER1:
            _sys_uTimer1ClockRate = uClockRate;
            break;

        default:
            break;
    }
    return 0;
}

/**
 *  @brief  system Timer - start timer
 *
 *  @param[in]  nTimeNo  Select TMR0 or TMR1. ( \ref TIMER0 / \ref TIMER1)
 *  @param[in]  uTicksPerSecond   tick count per second
 *  @param[in]  nOpMode   Operation Mode. ( \ref ONE_SHOT_MODE / \ref PERIODIC_MODE / \ref TOGGLE_MODE)
 *
 *  @return   0
 */
INT32 sysStartTimer(INT32 nTimeNo, UINT32 uTicksPerSecond, INT32 nOpMode)
{
    int volatile i;
    UINT32 _mTicr, _mTcr;

    _mTcr = 0x60000000 | (nOpMode << 27);

    switch (nTimeNo)
    {
        case TIMER0:
            outpw(REG_CLK_PCLKEN0, inpw(REG_CLK_PCLKEN0)| 0x100);
            _sys_bIsTimer0Initial = TRUE;
            _sys_uTimer0TickPerSecond = uTicksPerSecond;

            outpw(REG_TMR0_TCSR, 0);    /* disable timer */
            outpw(REG_TMR_TISR, 1);     /* clear for safety */

            for (i = 0; i < TimerEventCount; i++)
                tTime0Event[i].active = FALSE;

            rt_hw_interrupt_install(TMR0_IRQn,sysTimer0ISR,RT_NULL,"tmr0");
            rt_hw_interrupt_set_priority(TMR0_IRQn,IRQ_LEVEL_1);
            rt_hw_interrupt_set_type(TMR0_IRQn,HIGH_LEVEL_SENSITIVE);
            rt_hw_interrupt_umask(TMR0_IRQn);

            _sys_uTimer0Count = 0;
            _mTicr = _sys_uTimer0ClockRate / uTicksPerSecond;
            outpw(REG_TMR0_TICR, _mTicr);
            outpw(REG_TMR0_TCSR, _mTcr);
            break;

        case TIMER1:
            outpw(REG_CLK_PCLKEN0, inpw(REG_CLK_PCLKEN0)| 0x200);
            outpw(REG_TMR1_TCSR, 0); /* disable timer */
            outpw(REG_TMR_TISR, 2); /* clear for safety */

            for (i = 0; i < TimerEventCount; i++)
                tTime1Event[i].active = FALSE;

            rt_hw_interrupt_install(TMR1_IRQn,sysTimer1ISR,RT_NULL,"tmr1");
            rt_hw_interrupt_set_priority(TMR1_IRQn,IRQ_LEVEL_1);
            rt_hw_interrupt_set_type(TMR1_IRQn,HIGH_LEVEL_SENSITIVE);
            rt_hw_interrupt_umask(TMR1_IRQn);

            _sys_uTimer1Count = 0;
            _mTicr = _sys_uTimer1ClockRate / uTicksPerSecond;
            outpw(REG_TMR1_TICR, _mTicr);
            outpw(REG_TMR1_TCSR, _mTcr);
            break;
        default:
            break;
    }

    return 0;
}

INT32 sysStopTimer(INT32 nTimeNo)
{
    switch (nTimeNo)
    {
        case TIMER0:
            rt_hw_interrupt_mask(TMR0_IRQn);

            outpw(REG_TMR0_TCSR, 0); /* disable timer */
            outpw(REG_TMR_TISR, 1); /* clear for safety */

            _sys_uTime0EventCount = 0;
            _sys_bIsSetTime0Event = FALSE;
            break;

        case TIMER1:
            rt_hw_interrupt_mask(TMR1_IRQn);

            outpw(REG_TMR1_TCSR, 0);    /* disable timer */
            outpw(REG_TMR_TISR, 2);     /* clear for safety */

            _sys_uTime1EventCount = 0;
            _sys_bIsSetTime1Event = FALSE;
            break;

        default:
            ;
    }

    return 0;
}

/**
 *  @brief  system Timer - install timer event
 *
 *  @param[in]  nTimeNo  Select TMR0 or TMR1. ( \ref TIMER0 / \ref TIMER1)
 *  @param[in]  uTimeTick  tick count
 *  @param[in]  pvFun  callback function
 *
 *  @return   event number
 */
INT32 sysSetTimerEvent(INT32 nTimeNo, UINT32 uTimeTick, PVOID pvFun)
{
    int volatile i;
    int val = 0;

    switch (nTimeNo)
    {
        case TIMER0:
            _sys_bIsSetTime0Event = TRUE;
            _sys_uTime0EventCount++;
            for (i = 0; i < TimerEventCount; i++)
            {
                if (tTime0Event[i].active == FALSE)
                {
                    tTime0Event[i].active   = TRUE;
                    tTime0Event[i].initTick = uTimeTick;
                    tTime0Event[i].curTick  = uTimeTick;
                    tTime0Event[i].funPtr   = (sys_pvTimeFunPtr) pvFun;
                    val = i + 1;
                    break;
                }
            }
            break;

        case TIMER1:
            _sys_bIsSetTime1Event = TRUE;
            _sys_uTime1EventCount++;
            for (i = 0; i < TimerEventCount; i++)
            {
                if (tTime1Event[i].active == FALSE)
                {
                    tTime1Event[i].active = TRUE;
                    tTime1Event[i].initTick = uTimeTick;
                    tTime1Event[i].curTick = uTimeTick;
                    tTime1Event[i].funPtr = (sys_pvTimeFunPtr) pvFun;
                    val = i + 1;
                    break;
                }
            }
            break;

        default:
            ;
    }

    return val;
}


/**
 *  @brief  system Timer - clear specific timer event
 *
 *  @param[in]  nTimeNo  Select TMR0 or TMR1. ( \ref TIMER0 / \ref TIMER1)
 *  @param[in]  uTimeEventNo  select timer event
 *
 *  @return   None
 */
void sysClearTimerEvent(INT32 nTimeNo, UINT32 uTimeEventNo)
{
    switch (nTimeNo)
    {
        case TIMER0:
            tTime0Event[uTimeEventNo - 1].active = FALSE;
            _sys_uTime0EventCount--;
            if (_sys_uTime0EventCount == 0)
                _sys_bIsSetTime0Event = FALSE;
            break;

        case TIMER1:
            tTime1Event[uTimeEventNo - 1].active = FALSE;
            _sys_uTime1EventCount--;
            if (_sys_uTime1EventCount == 0)
                _sys_bIsSetTime1Event = FALSE;
            break;

        default:
            ;
    }
}

