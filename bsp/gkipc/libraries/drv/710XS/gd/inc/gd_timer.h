/*!
*******************************************************************************
**
** \file      gd_timer.h
**
** \brief     TIMER driver.
**
**            The driver provides functions for timer management.
**            It enables an application to make use of 8 soft timers, 1 hard
**            timer and 1 timestamp timer as a system clock.
**
**            Copyright:   2012 - 2013 (C) GoKe Microelectronics ShangHai Branch
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \version
**
******************************************************************************/
#ifndef _GD_TIMER_H_
#define _GD_TIMER_H_

#include <gtypes.h>
#include <gmodids.h>

/*---------------------------------------------------------------------------*/
/* constants and macros                                                      */
/*---------------------------------------------------------------------------*/
#define GD_TIMER_ERR_BASE (GD_TIMER_MODULE_ID<<16) //!< The timer base error code.

/* Note: Pre-scaler define hardcoded to avoid calculation in ISR! */
#define GD_TIMER_RESOLUTION_1_USEC   1UL          //!< timer resolution 1 usec
#define GD_TIMER_RESOLUTION_10_USEC  10UL         //!< timer resolution 10 usec
#define GD_TIMER_RESOLUTION_100_USEC 100UL        //!< timer resolution 100 usec
#define GD_TIMER_RESOLUTION_1_MSEC   1000UL       //!< timer resolution 1 msec
#define GD_TIMER_RESOLUTION_10_MSEC  10000UL      //!< timer resolution 10 msec
#define GD_TIMER_RESOLUTION_100_MSEC 100000UL     //!< timer resolution 100 msec
#define GD_TIMER_RESOLUTION_1_SEC    1000000UL    //!< timer resolution 1 sec
#define GD_TIMER_RESOLUTION_1_MIN    60000000UL   //!< timer resolution 1 minute
#define GD_TIMER_RESOLUTION_1_HOUR   3600000000UL //!< timer resolution 1 hour
#define GD_TIMER_RESOLUTION_1_HOUR   3600000000UL //!< timer resolution 1 hour

/*---------------------------------------------------------------------------*/
/* types, enums and structures                                               */
/*---------------------------------------------------------------------------*/

/*!
*******************************************************************************
**
** \brief TIMER driver error codes.
**
******************************************************************************/
typedef enum
{
    /*! Indicates all soft timer are  in use. */
    GD_ERR_TIMER_NO_FREE_SOFT_TIME = GD_TIMER_ERR_BASE,
    /*! Indicates all  hard  timer are in use */
    GD_ERR_TIMER_NO_FREE_HARD_TIME,
    /*! Indicates all time stamps are in use. */
    GD_ERR_TIMER_NO_FREE_GPREG_TIME,
    /*! */
    GD_ERR_TIMER_OUTOF_RANG,
}GD_TIMER_ERR_E;

/*!
*******************************************************************************
**
** \brief Allowed ARC timer settings.
**
******************************************************************************/
typedef enum
{
    /*! Reference to TIMER1 */
    GD_REG_TIMER1 = 0,
    /*! Reference to TIMER2 */
    GD_REG_TIMER2 = 1,
    /*! Reference to TIMER3 */
    GD_REG_TIMER3 = 2,
}GD_TIMER_REG_E;

typedef enum
{
    /*! Reference to  */
    GD_REG_SOFT_TIMER_IRQ   = 0,
    /*! Reference to  */
    GD_REG_HARD_TIMER_IRQ   = 1,
    /*! Reference to  */
    GD_REG_GPREG_TIMER_IRQ  = 2,
}GD_TIMER_IRQ_E;

/*!
*******************************************************************************
**
** \brief TIMER driver's initialization parameter.
**
******************************************************************************/
typedef struct
{
    /*! The ARC core timer register to be used for soft timer. */
    S8            softTimerReg;
    /*! The priority of the soft timer interrupt. */
    S8            softTimerpriority;
    /*! The ARC core timer register to be used for hard timer. */
    S8            hardTimerReg;
    /*! The priority of the hard timer interrupt. */
    S8            hardTimerpriority;
    /*! The ARC timestamp timer register to be used for gpreg IRQ. */
    S8            gpregTimerReg;
    /*! The priority of the gpreg timer interrupt. */
    S8            gpregTimerpriority;
}GD_TIMER_INIT_PARAMS_S;



/*---------------------------------------------------------------------------*/
/* function prototypes                                                       */
/*---------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

U8  *GD_TIMER_GetRevisionString(void);
GERR GD_TIMER_Init(GD_TIMER_INIT_PARAMS_S* initParams);
GERR GD_TIMER_Exit(void);

GERR GD_TIMER_TimerOpen(GD_HANDLE* pHandle,GD_TIMER_IRQ_E timerIRQ);
GERR GD_TIMER_TimerSet(GD_HANDLE* pHandle, U32 timeValue, GBOOL* flag, void(*fp)());
GERR GD_TIMER_TimerClose(GD_HANDLE* handle);

GERR GD_TIMER_HardTimerOpen(GD_HANDLE* pHandle);
GERR GD_TIMER_HardTimerSet(GD_HANDLE* pHandle, U32 timeValue, GBOOL* flag,void(*fp)());
GERR GD_TIMER_HardTimerClose(GD_HANDLE* pHandle);

GERR GD_TIMER_GpregTimerOpen(GD_HANDLE* pHandle);
GERR GD_TIMER_GpregTimerClose(GD_HANDLE* pHandle);
GERR GD_TIMER_GpregTimerSet(GD_HANDLE* pHandle, U32 timeValue, GBOOL* flag, void(*fp)());


U32  GD_TIMER_ReadTimerStamp(void);

GERR GD_TIMER_SoftTimerOpen(GD_HANDLE* pHandle);
GERR GD_TIMER_SoftTimerClose(GD_HANDLE* pHandle);
GERR GD_TIMER_SoftTimerSet(GD_HANDLE* pHandle, U32 timeValue, GBOOL* flag, void(*fp)());
GERR GD_TIMER_StopSoftTimer(GD_HANDLE* pHandle);
GERR GD_TIMER_ContinueSoftTimer(GD_HANDLE* pHandle);

GERR GD_TIMER_Delay(U32 msecs);
U32 GD_GET_ARM_ClkHz(void);
U32 GD_GET_AHB_ClkHz(void);
U32 GD_GET_APB_ClkHz(void);
U32 GD_GET_UART_ClkHz(void);
U32 GD_GET_IDSP_ClkHz(void);
U32 GD_GET_CORE_ClkHz(void);
U32 GD_GET_DRAM_ClkHz(void);
U32 GD_GET_I2S_ClkHz(void);
U32 GD_GET_SD_ClkHz(void);


#ifdef __cplusplus
}
#endif

#endif /* _GD_TIMER_H_ */
/* end of gd_timer.h */
