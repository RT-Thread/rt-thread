/******************************************************************************
**
** \file      gd_timer.c
**
** \brief     TIMER driver (core functions).
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
#include <stdio.h>
#include <string.h>

#include "gtypes.h"
#include "gd_int.h"
#include "gd_timer.h"
#include "gh_timer.h"
#include <rtthread.h>
/*---------------------------------------------------------------------------*/
/* local defines                                                             */
/*---------------------------------------------------------------------------*/
#define GD_TIMER_MAX_SOFT_TIME          10

#define RTOS_TICK_PER_SECOND			1000
/*---------------------------------------------------------------------------*/
/* private datatypes (used by more than one driver module)                   */
/*---------------------------------------------------------------------------*/
enum
{
    START_STATE = 1,
    SET_TRUE_VALUE,
    SET_OK,
};

typedef enum
{
    TIME_FREE = 0,
    TIME_USED,
    TIME_DISABLE,
    TIME_STOPPED,
    TIME_RUNNING
}GD_TIMER_TIME_STATE_E;

typedef struct
{
    GD_HANDLE             handle;
    GD_TIMER_TIME_STATE_E eState;
    U32                   nTimeCount;
    U32                   nStoreCount;
    GBOOL*                bpTimeEnd;
    void                  (*fpCallBackAddress)();
    U32                   nIndex;
    GD_TIMER_IRQ_E        timer_irq;
    GD_TIMER_REG_E        timerReg;
}GD_TIMER_DEVICE_S;

/*---------------------------------------------------------------------------*/
/* local data                                                                */
/*---------------------------------------------------------------------------*/
static U8 CvsVersion[] = "$Revision: 1.47 $";
static volatile U32 nTimeStamp __attribute__ ((section(".nocache_buffer")));

/* GD_TIMER_MAX_SOFT_TIME for soft timer and one for time stamp time */
static GD_TIMER_DEVICE_S gd_timer_sSoftTime[GD_TIMER_MAX_SOFT_TIME+1];
static GD_TIMER_DEVICE_S gd_timer_sHardTime;
static GD_TIMER_DEVICE_S gd_timer_sGpregTime;

static GBOOL     gd_timer_TimerInitFlag        = GFALSE;


/*---------------------------------------------------------------------------*/
/* local functions                                                           */
/*---------------------------------------------------------------------------*/
void timer_enable(S8 tmr_id, U8 enable)
{
    U32 val;

    val = GH_TIMER_get_Control();

    //val &= ~(0x111 << (2-tmr_id));
    val &= ~(0x110 << (2-tmr_id));

    if(enable)
    {
        //val |= (0x111 << (2-tmr_id));
        val |= (0x110 << (2-tmr_id));
    }
    GH_TIMER_set_Control(val);
}
/*
*******************************************************************************
**
** \brief  Slow Low Soft-Timer interrupt routine.
**
******************************************************************************/
GISR1 GI_TIME_ISR(void)
{
    int index;

    nTimeStamp ++;
    for( index=0; index <= GD_TIMER_MAX_SOFT_TIME; index++ )
    {
        if( gd_timer_sSoftTime[index].eState == TIME_RUNNING )
        {
            if( gd_timer_sSoftTime[index].nTimeCount > 0 )
            {
                gd_timer_sSoftTime[index].nTimeCount--;
            }

            if( gd_timer_sSoftTime[index].nTimeCount == 0 )
            {
                if( gd_timer_sSoftTime[index].bpTimeEnd )
                    *(gd_timer_sSoftTime[index].bpTimeEnd) = GTRUE;

                if( gd_timer_sSoftTime[index].fpCallBackAddress )
                    (gd_timer_sSoftTime[index].fpCallBackAddress)();

                gd_timer_sSoftTime[index].nTimeCount = gd_timer_sSoftTime[index].nStoreCount;
            }
        }
    }
}

/*******************************************************************************
**
** \brief  Slow Low Hard-Timer interrupt routine.
**
******************************************************************************/
GISR1 GI_TIMER_HardTimerISR(void)
{
    if ( gd_timer_sHardTime.eState != TIME_RUNNING )
    {
        return;
    }

    if (gd_timer_sHardTime.bpTimeEnd != NULL)
        *(gd_timer_sHardTime.bpTimeEnd) = GTRUE;

    if (gd_timer_sHardTime.fpCallBackAddress != NULL)
        (gd_timer_sHardTime.fpCallBackAddress)();
}

/*
*******************************************************************************
**
** \brief  Slow Low External-Timer interrupt routine.
**
******************************************************************************/
GISR1 GI_TIMER_GPREGTimerISR(void)
{
    if ( gd_timer_sGpregTime.eState != TIME_RUNNING )
    {
        return;
    }

    if (gd_timer_sGpregTime.bpTimeEnd != NULL)
        *(gd_timer_sGpregTime.bpTimeEnd) = GTRUE;

    if (gd_timer_sGpregTime.fpCallBackAddress != NULL)
        (gd_timer_sGpregTime.fpCallBackAddress)();
}


/*---------------------------------------------------------------------------*/
/* GOKESDK functions                                                            */
/*---------------------------------------------------------------------------*/

/*!
*******************************************************************************
**
** \brief  Get the current driver version.
**
** \return Pointer to the version string.
**
******************************************************************************/
U8 *GD_TIMER_GetRevisionString(void)
{
    return(CvsVersion);
}

/*!
*******************************************************************************
**
** \brief  Initializes the driver.
**
**         This function initializes the TIMER driver. It initializes the
**         internal timer variables and registers the interrupts of hard- and
**         soft timer. Furthermore it starts the time GPREG timer.
**
** \param initParams Pointer to TIMER init data structure containing all
**                   customizable driver parameter.
**
** \return One of the following status codes:
**         - #GD_OK if successful
**         - #GD_ERR_ALREADY_INITIALIZED if this function has already been
**                                       called.
**         - #GD_ERR_BAD_PARAMETER if the initialization parameter are not
**                                 correctly specified.
******************************************************************************/
GERR GD_TIMER_Init(GD_TIMER_INIT_PARAMS_S* initParams)
{
    GERR ret = GD_OK;

    GD_INT_OPEN_PARAMS_S params;
    int i;

    nTimeStamp = 0;

    if (gd_timer_TimerInitFlag != GFALSE)
        return  GD_ERR_ALREADY_INITIALIZED;

    if ((initParams->softTimerReg != GD_REG_TIMER1 &&
         initParams->softTimerReg != GD_REG_TIMER2 &&
         initParams->softTimerReg != GD_REG_TIMER3) ||
        (initParams->hardTimerReg != GD_REG_TIMER1 &&
         initParams->hardTimerReg != GD_REG_TIMER2 &&
         initParams->hardTimerReg != GD_REG_TIMER3) ||
        (initParams->gpregTimerReg != GD_REG_TIMER1 &&
         initParams->gpregTimerReg != GD_REG_TIMER2 &&
         initParams->gpregTimerReg != GD_REG_TIMER3) ||
        (initParams->hardTimerReg  == initParams->softTimerReg) ||
        (initParams->gpregTimerReg == initParams->softTimerReg) ||
        (initParams->hardTimerReg  == initParams->gpregTimerReg)
       )
    {
        return GD_ERR_BAD_PARAMETER;
    }


    for ( i = 0; i <= GD_TIMER_MAX_SOFT_TIME; i++ )
    {
        gd_timer_sSoftTime[i].nIndex      = i;
        gd_timer_sSoftTime[i].nTimeCount  = 0;
        gd_timer_sSoftTime[i].nStoreCount = 0;
        gd_timer_sSoftTime[i].eState      = TIME_FREE;
        gd_timer_sSoftTime[i].bpTimeEnd   = NULL;
        gd_timer_sSoftTime[i].fpCallBackAddress=NULL;
    }

    gd_timer_sHardTime.eState = TIME_FREE;
    gd_timer_sHardTime.nTimeCount = 0;
    gd_timer_sHardTime.bpTimeEnd = NULL;
    gd_timer_sHardTime.fpCallBackAddress = NULL;

    gd_timer_sGpregTime.eState = TIME_FREE;
    gd_timer_sGpregTime.nTimeCount = 0;
    gd_timer_sGpregTime.bpTimeEnd = NULL;
    gd_timer_sGpregTime.fpCallBackAddress = NULL;

    params.active      = GD_INT_NO_INVERT_IRQ;
    params.sensitivity = GD_INT_RISING_EDGE;


    /* soft timer init */
    if (initParams->softTimerReg == GD_REG_TIMER1)
        params.type = GD_INT_TIMER1_IRQ;
    else if (initParams->softTimerReg == GD_REG_TIMER2)
        params.type = GD_INT_TIMER2_IRQ;
    else if (initParams->softTimerReg == GD_REG_TIMER3)
        params.type = GD_INT_TIMER3_IRQ;

    for ( i = 0; i <= GD_TIMER_MAX_SOFT_TIME; i++ )
    {
        gd_timer_sSoftTime[i].timer_irq = GD_REG_SOFT_TIMER_IRQ;
        gd_timer_sSoftTime[i].timerReg  = (GD_TIMER_REG_E)initParams->softTimerReg;
    }

    params.priority       = initParams->softTimerpriority;
    params.isrFct.lowPrio = GI_TIME_ISR;
    ret = GD_INT_Open(&params, &gd_timer_sSoftTime[0].handle);
    if (ret != GD_OK)
    {
        return ret;
    }
    for ( i = 1; i <= GD_TIMER_MAX_SOFT_TIME; i++ )
    {
        gd_timer_sSoftTime[i].handle = gd_timer_sSoftTime[0].handle;
    }

    /* General the soft timer Interrupt pre 10ms */
    if(initParams->softTimerReg == GD_REG_TIMER1)
    {
        GH_TIMER_set_T1CntnSts(GD_GET_APB_ClkHz() / RTOS_TICK_PER_SECOND);
        GH_TIMER_set_T1Reloadn(GD_GET_APB_ClkHz() / RTOS_TICK_PER_SECOND);
        GH_TIMER_set_T1Match1(0x00);
        GH_TIMER_set_T1Match2(0x00);
    }
    else if(initParams->softTimerReg == GD_REG_TIMER2)
    {
        GH_TIMER_set_T2CntnSts(GD_GET_APB_ClkHz() / RTOS_TICK_PER_SECOND);
        GH_TIMER_set_T2Reloadn(GD_GET_APB_ClkHz() / RTOS_TICK_PER_SECOND);
        GH_TIMER_set_T2Match1(0x00);
        GH_TIMER_set_T2Match2(0x00);
    }
    else
    {
        GH_TIMER_set_T3CntnSts(GD_GET_APB_ClkHz() / RTOS_TICK_PER_SECOND);
        GH_TIMER_set_T3Reloadn(GD_GET_APB_ClkHz() / RTOS_TICK_PER_SECOND);
        GH_TIMER_set_T3Match1(0x00);
        GH_TIMER_set_T3Match2(0x00);
    }

    /* hard timer init */
    if (initParams->hardTimerReg == GD_REG_TIMER1)
        params.type = GD_INT_TIMER1_IRQ;
    else if (initParams->hardTimerReg == GD_REG_TIMER2)
        params.type = GD_INT_TIMER2_IRQ;
    else if (initParams->hardTimerReg == GD_REG_TIMER3)
        params.type = GD_INT_TIMER3_IRQ;
    gd_timer_sHardTime.timer_irq = GD_REG_HARD_TIMER_IRQ;
    params.priority         = initParams->hardTimerpriority;
    params.isrFct.lowPrio   = GI_TIMER_HardTimerISR;
    ret = GD_INT_Open(&params, &gd_timer_sHardTime.handle);
    if (ret != GD_OK)
    {
        GD_INT_Close(&gd_timer_sSoftTime[0].handle);
        for ( i = 1; i <= GD_TIMER_MAX_SOFT_TIME; i++ )
        {
            gd_timer_sSoftTime[i].handle = 0;
        }
        return ret;
    }
    gd_timer_sHardTime.timerReg = (GD_TIMER_REG_E)initParams->hardTimerReg;

    /* General the hard timer Interrupt pre 100ms */
    if(initParams->hardTimerReg == GD_REG_TIMER1)
    {
        GH_TIMER_set_T1CntnSts(GD_GET_APB_ClkHz() / 10);
        GH_TIMER_set_T1Reloadn(GD_GET_APB_ClkHz() / 10);
        GH_TIMER_set_T1Match1(0x00);
        GH_TIMER_set_T1Match2(0x00);
    }
    else if(initParams->hardTimerReg == GD_REG_TIMER2)
    {
        GH_TIMER_set_T2CntnSts(GD_GET_APB_ClkHz() / 10);
        GH_TIMER_set_T2Reloadn(GD_GET_APB_ClkHz() / 10);
        GH_TIMER_set_T2Match1(0x00);
        GH_TIMER_set_T2Match2(0x00);
    }
    else
    {
        GH_TIMER_set_T3CntnSts(GD_GET_APB_ClkHz() / 10);
        GH_TIMER_set_T3Reloadn(GD_GET_APB_ClkHz() / 10);
        GH_TIMER_set_T3Match1(0x00);
        GH_TIMER_set_T3Match2(0x00);
    }

    /* init time stamp timer */
    /* gpreg timer init */
    if (initParams->gpregTimerReg == GD_REG_TIMER1)
        params.type = GD_INT_TIMER1_IRQ;
    else if (initParams->gpregTimerReg == GD_REG_TIMER2)
        params.type = GD_INT_TIMER2_IRQ;
    else if (initParams->gpregTimerReg == GD_REG_TIMER3)
        params.type = GD_INT_TIMER3_IRQ;
    gd_timer_sGpregTime.timer_irq    = GD_REG_GPREG_TIMER_IRQ;
    params.priority             = initParams->gpregTimerpriority;
    params.isrFct.lowPrio       = GI_TIMER_GPREGTimerISR;
    ret = GD_INT_Open(&params, &gd_timer_sGpregTime.handle);
    if (ret != GD_OK)
    {
        GD_INT_Close(&gd_timer_sSoftTime[0].handle);
        for ( i = 1; i <= GD_TIMER_MAX_SOFT_TIME; i++ )
        {
            gd_timer_sSoftTime[i].handle = 0;
        }
        GD_INT_Close(&gd_timer_sHardTime.handle);
        return ret;
    }
    gd_timer_sGpregTime.timerReg = (GD_TIMER_REG_E)initParams->gpregTimerReg;

    /*set presclaer for generating the interrupt per 100ms*/
    if(initParams->gpregTimerReg == GD_REG_TIMER1)
    {
        GH_TIMER_set_T1CntnSts(GD_GET_APB_ClkHz() / 10);
        GH_TIMER_set_T1Reloadn(GD_GET_APB_ClkHz() / 10);
        GH_TIMER_set_T1Match1(0x00);
        GH_TIMER_set_T1Match2(0x00);
    }
    else if(initParams->gpregTimerReg == GD_REG_TIMER2)
    {
        GH_TIMER_set_T2CntnSts(GD_GET_APB_ClkHz() / 10);
        GH_TIMER_set_T2Reloadn(GD_GET_APB_ClkHz() / 10);
        GH_TIMER_set_T2Match1(0x00);
        GH_TIMER_set_T2Match2(0x00);
    }
    else
    {
        GH_TIMER_set_T3CntnSts(GD_GET_APB_ClkHz() / 10);
        GH_TIMER_set_T3Reloadn(GD_GET_APB_ClkHz() / 10);
        GH_TIMER_set_T3Match1(0x00);
        GH_TIMER_set_T3Match2(0x00);
    }

    gd_timer_TimerInitFlag = GTRUE;

    timer_enable(gd_timer_sSoftTime[0].timerReg, GD_INT_ENABLED);
    GD_INT_Enable(&gd_timer_sSoftTime[0].handle, GD_INT_ENABLED);
    return ret;
}

/*!
*******************************************************************************
**
** \brief  Exit the initiated driver.
**
**         This function exites the TIMER driver. It exites the
**         internal timer variables and registers the interrupts of hard- and
**         soft timer. Furthermore it close the time GPREG timer.
**
** \param initParams Pointer to TIMER init data structure containing all
**                   customizable driver parameter.
**
** \return One of the following status codes:
**         - #GD_OK if successful
**         - #GD_ERR_ALREADY_INITIALIZED if this function has already been
**                                       called.
**         - #GD_ERR_BAD_PARAMETER if the initialization parameter are not
**                                 correctly specified.
******************************************************************************/
GERR GD_TIMER_Exit(void)
{
    U32 i;
    if(gd_timer_TimerInitFlag == GFALSE)
    {
        return(GD_ERR_NOT_INITIALIZED );
    }

    GD_INT_Close(&gd_timer_sSoftTime[0].handle);
    for ( i = 1; i <= GD_TIMER_MAX_SOFT_TIME; i++ )
    {
        gd_timer_sSoftTime[i].handle = 0;
    }
    GD_INT_Close(&gd_timer_sHardTime.handle);
    GD_INT_Close(&gd_timer_sGpregTime.handle);
    gd_timer_TimerInitFlag = GFALSE;
    return GD_OK;

}

/*!
*******************************************************************************
**
** \brief  Opens an instance of the timer.
**
** \param pHandle Pointer where the pHandle of the timer should
**               be stored.
**\param timerIRQ style which come choose SOFT_IRQ,HARD_IRQ and GPREG_IRQ
**
** \return One of the following status codes:
**         - #GD_OK if successful
**         - #GD_ERR_NOT_INITIALIZED if GD_TIMER_Init() has not yet been called.
**         - #GD_ERR_TIMER_NO_FREE_HARD_TIME if no more hard timer  can be opend.
**
** \sa GD_TIMER_HardTimerClose
******************************************************************************/
GERR GD_TIMER_TimerOpen(GD_HANDLE *pHandle, GD_TIMER_IRQ_E timerIRQ)
{
    if(pHandle == NULL)
        return GD_ERR_INVALID_HANDLE;

    if (gd_timer_TimerInitFlag != GTRUE)
        return GD_ERR_NOT_INITIALIZED;

    if(timerIRQ == GD_REG_SOFT_TIMER_IRQ)//soft IRQ
    {
        return GD_TIMER_SoftTimerOpen(pHandle);
    }
    else if(timerIRQ == GD_REG_HARD_TIMER_IRQ)//hard IRQ
    {
        return GD_TIMER_HardTimerOpen(pHandle);
    }
    else if(timerIRQ == GD_REG_GPREG_TIMER_IRQ)//GPREG Timer IRQ
    {
        return GD_TIMER_GpregTimerOpen(pHandle);
    }

    return GD_OK;

}

/*!
*******************************************************************************
**
** \brief  Set  timer IRQ.
**
** This function sets the value to an instance of  timer,which can choose soft,hard and gpreg.
**
** \param pHandle The pHandle of the timer to be set.
** \param timerIRQ style which come choose SOFT_IRQ,HARD_IRQ and GPREG_IRQ
** \param timeValue The timer value in milliseconds.
** \param flag A pointer the timmer flag.
** \param fp Pointer to the callback function.
**
** \return One of the following status codes:
**         - #GD_OK if successful
**         - #GD_ERR_BAD_PARAMETER if the given parameter are not correctly
**                                 specified.
**
******************************************************************************/
GERR GD_TIMER_TimerSet(GD_HANDLE* pHandle,
                           U32 timeValue,
                           GBOOL* flag,
                           void(*fp)()
                          )
{
    GD_TIMER_DEVICE_S* device;

    if(pHandle == NULL)
        return GD_ERR_INVALID_HANDLE;

    device = (GD_TIMER_DEVICE_S*)(*pHandle);
    if(device == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }

    if (device->timer_irq == GD_REG_SOFT_TIMER_IRQ)
    {
        GD_TIMER_SoftTimerSet(pHandle, timeValue, flag, fp);
    }
    else if (device->timer_irq == GD_REG_HARD_TIMER_IRQ)
    {
        GD_TIMER_HardTimerSet(pHandle, timeValue, flag, fp);
    }
    else if (device->timer_irq == GD_REG_GPREG_TIMER_IRQ)
    {
        GD_TIMER_GpregTimerSet(pHandle, timeValue, flag, fp);
    }
    else
    {
        return GD_ERR_BAD_PARAMETER;
    }
    return GD_OK;
}

/*!
*******************************************************************************
**
** \brief  Close a hard timer.
**
** This function closes an instance of the hard timer.
**
** \param pHandle The pHandle of the hard timer to be closed.
**\param timerIRQ style which come choose SOFT_IRQ,HARD_IRQ and GPREG_IRQ
**
** \return One of the following status codes:
**         - #GD_OK if successful
**         - #GD_ERR_BAD_PARAMETER if the given parameter is not correctly
**                                 specified.
**
** \sa GD_TIMER_HardTimerOpen
******************************************************************************/
GERR GD_TIMER_TimerClose(GD_HANDLE * pHandle)
{
    GD_TIMER_DEVICE_S* device;

    if(pHandle == NULL)
        return GD_ERR_INVALID_HANDLE;

    device = (GD_TIMER_DEVICE_S*)(*pHandle);
    if(device == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }

    if (device->timer_irq == GD_REG_SOFT_TIMER_IRQ)
    {
        return  GD_TIMER_SoftTimerClose(pHandle);
    }
    else if (device->timer_irq == GD_REG_HARD_TIMER_IRQ)
    {
        return GD_TIMER_HardTimerClose(pHandle);

    }
    else if (device->timer_irq == GD_REG_GPREG_TIMER_IRQ)
    {
        return GD_TIMER_GpregTimerClose(pHandle);

    }
    return GD_OK;

}

/*!
*******************************************************************************
**
** \brief  Opens an instance of the soft timer.
**
** \param pHandle Pointer where the pHandle of the timer should
**               be stored.
**
** \return One of the following status codes:
**         - #GD_OK if successful
**         - #GD_ERR_NOT_INITIALIZED if GD_TIMER_Init() has not yet been called.
**         - #GD_ERR_TIMER_NO_FREE_SOFT_TIME if no more soft timer can be opend.
**
** \sa GD_TIMER_SoftTimerClose
******************************************************************************/
GERR GD_TIMER_SoftTimerOpen(GD_HANDLE *pHandle)
{
    int i;

    if (gd_timer_TimerInitFlag != GTRUE)
        return GD_ERR_NOT_INITIALIZED;

    for ( i = 0; i< GD_TIMER_MAX_SOFT_TIME; i++)
    {
        if ( gd_timer_sSoftTime[i].eState == TIME_FREE )
        {
            *pHandle = (GD_HANDLE)&gd_timer_sSoftTime[i];

            gd_timer_sSoftTime[i].eState            = TIME_USED;
            gd_timer_sSoftTime[i].nTimeCount        = 0;
            gd_timer_sSoftTime[i].nStoreCount       = 0;
            gd_timer_sSoftTime[i].bpTimeEnd         = NULL;
            gd_timer_sSoftTime[i].fpCallBackAddress = NULL;

            return GD_OK;
        }
    }

    *pHandle = 0;
    return GD_ERR_TIMER_NO_FREE_SOFT_TIME;

}

/*!
*******************************************************************************
**
** \brief  Close a soft timer.
**
** This function closes an instance of the soft timer.
**
** \param pHandle The pHandle of the soft timer to be closed.
**
** \return One of the following status codes:
**         - #GD_OK if successful
**         - #GD_ERR_BAD_PARAMETER if the given parameter is not correctly
**                                 specified.
**
** \sa GD_TIMER_SoftTimerOpen
******************************************************************************/
GERR GD_TIMER_SoftTimerClose(GD_HANDLE * pHandle)
{
    GD_TIMER_DEVICE_S* device;

    if(pHandle == NULL)
        return GD_ERR_INVALID_HANDLE;

    device = (GD_TIMER_DEVICE_S*)(*pHandle);
    if(device == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }

    if ( device->nIndex > GD_TIMER_MAX_SOFT_TIME)
        return  GD_ERR_BAD_PARAMETER;

    device->eState            = TIME_FREE;
    device->nTimeCount        = 0;
    device->nStoreCount       = 0;
    device->bpTimeEnd         = NULL;
    device->fpCallBackAddress = NULL;

    *pHandle = 0;

    return GD_OK;

}


/*!
*******************************************************************************
**
** \brief  Set the soft timer.
**
** This function sets the value to an instance of the soft timer.
**
** \param pHandle The pHandle of the soft timer to be set.
** \param timeValue The timer value in 100 milliseconds.
** \param flag A pointer the timmer flag.
** \param fp Pointer to the callback function.
**
** \return One of the following status codes:
**         - #GD_OK if successful
**         - #GD_ERR_BAD_PARAMETER if the given parameter are not correctly
**                                 specified.
**
******************************************************************************/
GERR GD_TIMER_SoftTimerSet(GD_HANDLE* pHandle,
                                U32 timeValue,
                                GBOOL* flag,
                                void(*fp)()
                               )
{
    GD_TIMER_DEVICE_S* device;

    if(pHandle == NULL)
        return GD_ERR_INVALID_HANDLE;

    device = (GD_TIMER_DEVICE_S*)(*pHandle);
    if(device == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }

    if (device->nIndex > GD_TIMER_MAX_SOFT_TIME)
        return  GD_ERR_BAD_PARAMETER;

    if (timeValue == 0)
        return  GD_ERR_BAD_PARAMETER;

    device->nTimeCount  = timeValue;
    device->nStoreCount = timeValue;

    device->bpTimeEnd    = flag;
    device->fpCallBackAddress = fp;

    device->eState = TIME_RUNNING;

    return GD_OK;

}

/*!
*******************************************************************************
**
** \brief  Stop the soft timer.
**
** This function stops an instance of the soft timer. It can be continued by
** function GD_TIMER_ContinueSoftTimer.
**
** \param pHandle Pointer to the pHandle of the soft timer to stop.
**
** \return One of the following status codes:
**         - #GD_OK if successful
**         - #GD_ERR_BAD_PARAMETER if the given parameter is not correctly
**                                 specified.
**
** \sa  GD_TIMER_ContinueSoftTimer
******************************************************************************/
GERR GD_TIMER_StopSoftTimer(GD_HANDLE* pHandle)
{
    GD_TIMER_DEVICE_S* device;

    if(pHandle == NULL)
        return GD_ERR_INVALID_HANDLE;

    device = (GD_TIMER_DEVICE_S*)(*pHandle);
    if(device == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }

    if (device->nIndex > GD_TIMER_MAX_SOFT_TIME)
        return  GD_ERR_BAD_PARAMETER;

    device->eState = TIME_STOPPED;

    return  GD_OK;

}

/*!
*******************************************************************************
**
** \brief  Continue the soft timer.
**
** This function continues a previously stopped instance of the soft timer.
**
** \param pHandle Pointer to the pHandle of the soft timer to continue.
**
** \return One of the following status codes:
**         - #GD_OK if successful
**         - #GD_ERR_BAD_PARAMETER if the given parameter is not correctly
**                                 specified.
**
** \sa GD_TIMER_StopSoftTimer
******************************************************************************/
GERR GD_TIMER_ContinueSoftTimer(GD_HANDLE* pHandle)
{
    GD_TIMER_DEVICE_S* device;

    if(pHandle == NULL)
        return GD_ERR_INVALID_HANDLE;

    device = (GD_TIMER_DEVICE_S*)(*pHandle);
    if(device == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }

    if (device->nIndex > GD_TIMER_MAX_SOFT_TIME)
        return  GD_ERR_BAD_PARAMETER;

    device->eState = TIME_RUNNING;

    return  GD_OK;
}

/*!
*******************************************************************************
**
** \brief  Opens an instance of the hard timer.
**
** \param pHandle Pointer where the pHandle of the timer should
**               be stored.
**
** \return One of the following status codes:
**         - #GD_OK if successful
**         - #GD_ERR_NOT_INITIALIZED if GD_TIMER_Init() has not yet been called.
**         - #GD_ERR_TIMER_NO_FREE_HARD_TIME if no more hard timer  can be opend.
**
** \sa GD_TIMER_HardTimerClose
******************************************************************************/
GERR GD_TIMER_HardTimerOpen(GD_HANDLE *pHandle)
{
    if (gd_timer_TimerInitFlag != GTRUE)
        return GD_ERR_NOT_INITIALIZED;

    if (gd_timer_sHardTime.eState != TIME_FREE)
        return GD_ERR_TIMER_NO_FREE_HARD_TIME;

    gd_timer_sHardTime.eState = TIME_USED;
    *pHandle = (GD_HANDLE)&gd_timer_sHardTime;

    return GD_OK;

}


/*!
*******************************************************************************
**
** \brief  Set the hard timer.
**
** This function sets the value to an instance of the hard timer.
**
** \param pHandle The pHandle of the hard timer to be set.
** \param timeValue The timer value in milliseconds.
** \param flag A pointer the timmer flag.
** \param fp Pointer to the callback function.
**
** \return One of the following status codes:
**         - #GD_OK if successful
**         - #GD_ERR_BAD_PARAMETER if the given parameter are not correctly
**                                 specified.
**
******************************************************************************/
GERR GD_TIMER_HardTimerSet(GD_HANDLE* pHandle,
                           U32 timeValue,
                           GBOOL* flag,
                           void(*fp)()
                          )
{
    GD_TIMER_DEVICE_S* device;

    if(pHandle == NULL)
        return GD_ERR_INVALID_HANDLE;
    if(timeValue > (0xFFFFFFFF / (GD_GET_APB_ClkHz() / 100)))//
    {
        return GD_ERR_TIMER_OUTOF_RANG;
    }

    device = (GD_TIMER_DEVICE_S*)(*pHandle);
    if(device == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    /* Disable the slow hard timer interrupt until we set the state machine */
    GD_INT_Enable(&device->handle, GD_INT_DISABLED);
    timer_enable(device->timerReg, GD_INT_DISABLED);

    if (fp != NULL)
        device->fpCallBackAddress = fp;

    if (flag != NULL)
        device->bpTimeEnd = flag;

    device->nTimeCount = timeValue;// * 10;

    if(device->timerReg == GD_REG_TIMER1)
    {
        GH_TIMER_set_T1CntnSts(device->nTimeCount * (GD_GET_APB_ClkHz() / 1000) - 1);
        GH_TIMER_set_T1Reloadn(device->nTimeCount * (GD_GET_APB_ClkHz() / 1000) - 1);
    }
    else if(device->timerReg == GD_REG_TIMER2)
    {
        GH_TIMER_set_T2CntnSts(device->nTimeCount * (GD_GET_APB_ClkHz() / 1000) - 1);
        GH_TIMER_set_T2Reloadn(device->nTimeCount * (GD_GET_APB_ClkHz() / 1000) - 1);
    }
    else
    {
        GH_TIMER_set_T3CntnSts(device->nTimeCount * (GD_GET_APB_ClkHz() / 1000) - 1);
        GH_TIMER_set_T3Reloadn(device->nTimeCount * (GD_GET_APB_ClkHz() / 1000) - 1);
    }

    device->eState = TIME_RUNNING;

    /* Enable the slow hard timer interrupt */
    timer_enable(device->timerReg, GD_INT_ENABLED);
    GD_INT_Enable(&device->handle, GD_INT_ENABLED);

    return GD_OK;
}


/*!
*******************************************************************************
**
** \brief  Close a hard timer.
**
** This function closes an instance of the hard timer.
**
** \param pHandle The pHandle of the hard timer to be closed.
**
** \return One of the following status codes:
**         - #GD_OK if successful
**         - #GD_ERR_BAD_PARAMETER if the given parameter is not correctly
**                                 specified.
**
** \sa GD_TIMER_HardTimerOpen
******************************************************************************/
GERR GD_TIMER_HardTimerClose(GD_HANDLE * pHandle)
{
    GD_TIMER_DEVICE_S* device;

    if(pHandle == NULL)
        return GD_ERR_INVALID_HANDLE;

    device = (GD_TIMER_DEVICE_S*)(*pHandle);
    if(device == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }

    device->eState = TIME_FREE;
    device->nTimeCount = 0;
    device->bpTimeEnd = NULL;
    device->fpCallBackAddress = NULL;

    /* Disable the slow hard timer interrupt */
    timer_enable(device->timerReg, GD_INT_DISABLED);
    GD_INT_Enable(&device->handle, GD_INT_DISABLED);

    //1215 hhl add
    *pHandle = 0;

    return GD_OK;
}

/*!
*******************************************************************************
**
** \brief  Opens an instance of the GPREG timer.
**
** \param pHandle Pointer where the pHandle of the timer should
**               be stored.
**
** \return One of the following status codes:
**         - #GD_OK if successful
**         - #GD_ERR_NOT_INITIALIZED if GD_TIMER_Init() has not yet been called.
**         - #GD_ERR_TIMER_NO_FREE_SOFT_TIME if no more soft timer can be opend.
**
** \sa GD_TIMER_SoftTimerClose
******************************************************************************/
GERR GD_TIMER_GpregTimerOpen(GD_HANDLE *pHandle)
{
    if (gd_timer_TimerInitFlag != GTRUE)
        return GD_ERR_NOT_INITIALIZED;

    if (gd_timer_sGpregTime.eState != TIME_FREE)
        return GD_ERR_TIMER_NO_FREE_GPREG_TIME;

    gd_timer_sGpregTime.eState = TIME_USED;
    *pHandle = (GD_HANDLE)&gd_timer_sGpregTime;
    return GD_OK;
}

/*!
*******************************************************************************
**
** \brief  Close a soft timer.
**
** This function closes an instance of the soft timer.
**
** \param pHandle The pHandle of the soft timer to be closed.
**
** \return One of the following status codes:
**         - #GD_OK if successful
**         - #GD_ERR_BAD_PARAMETER if the given parameter is not correctly
**                                 specified.
**
** \sa GD_TIMER_SoftTimerOpen
******************************************************************************/
GERR GD_TIMER_GpregTimerClose(GD_HANDLE * pHandle)
{
    GD_TIMER_DEVICE_S* device;

    if(pHandle == NULL)
        return GD_ERR_INVALID_HANDLE;

    device = (GD_TIMER_DEVICE_S*)(*pHandle);
    if(device == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }

    device->eState = TIME_FREE;
    device->nTimeCount = 0;
    device->bpTimeEnd = NULL;
    device->fpCallBackAddress = NULL;

    /* Disable the slow hard timer interrupt */
    timer_enable(device->timerReg, GD_INT_DISABLED);
    GD_INT_Enable(&device->handle, GD_INT_DISABLED);

    //1215 hhl add
    *pHandle = 0;

    return GD_OK;
}

/*!
*******************************************************************************
**
** \brief  Set the soft timer.
**
** This function sets the value to an instance of the soft timer.
**
** \param pHandle The pHandle of the soft timer to be set.
** \param timeValue The timer value in 100 milliseconds.
** \param flag A pointer the timmer flag.
** \param fp Pointer to the callback function.
**
** \return One of the following status codes:
**         - #GD_OK if successful
**         - #GD_ERR_BAD_PARAMETER if the given parameter are not correctly
**                                 specified.
**
******************************************************************************/
GERR GD_TIMER_GpregTimerSet(GD_HANDLE* pHandle,
                                U32 timeValue,
                                GBOOL* flag,
                                void(*fp)()
                               )
{
    GD_TIMER_DEVICE_S* device;

    if(pHandle == NULL)
        return GD_ERR_INVALID_HANDLE;
    if(timeValue > (0xFFFFFFFF / (GD_GET_APB_ClkHz() / 100)))
    {
        return GD_ERR_TIMER_OUTOF_RANG;
    }

    device = (GD_TIMER_DEVICE_S*)(*pHandle);
    if(device == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    /* Disable the sbusl interrupt until we set the state machine */
    GD_INT_Enable(&device->handle, GD_INT_DISABLED);
    timer_enable(device->timerReg, GD_INT_DISABLED);

    if (fp != NULL)
        device->fpCallBackAddress = fp;

    if (flag != NULL)
        device->bpTimeEnd = flag;

    device->nTimeCount = timeValue * 10;// timeValue (ms)

    if(device->timerReg == GD_REG_TIMER1)
    {
        GH_TIMER_set_T1CntnSts(device->nTimeCount * (GD_GET_APB_ClkHz() / 1000) - 1);
        GH_TIMER_set_T1Reloadn(device->nTimeCount * (GD_GET_APB_ClkHz() / 1000) - 1);
    }
    else if(device->timerReg == GD_REG_TIMER2)
    {
        GH_TIMER_set_T2CntnSts(device->nTimeCount * (GD_GET_APB_ClkHz() / 1000) - 1);
        GH_TIMER_set_T2Reloadn(device->nTimeCount * (GD_GET_APB_ClkHz() / 1000) - 1);
    }
    else
    {
        GH_TIMER_set_T3CntnSts(device->nTimeCount * (GD_GET_APB_ClkHz() / 1000) - 1);
        GH_TIMER_set_T3Reloadn(device->nTimeCount * (GD_GET_APB_ClkHz() / 1000) - 1);
    }

    device->eState = TIME_RUNNING;

    /* Enable the slow hard timer interrupt */
    timer_enable(device->timerReg, GD_INT_ENABLED);
    GD_INT_Enable(&device->handle, GD_INT_ENABLED);

    return GD_OK;
}

/*!
*******************************************************************************
**
** \brief  Returns the current time stamp in milliseconds.
**
**         The time stamp timer will be reset (to 0ms) and started in
**         GD_TIMER_Init(). It will overflow after 49.7 days.
**
** \note   Since the hardware time stamp timer will overflow after around 16s
**         it is necessary to use an additional soft timer based on 10s
**         (for SmartMPEG). Enabling and disabling interrupts might produce
**         bad system tick values.
**
** \note   For SmartMPEG-E/C the timer implemented in GPREGS is used for this
**         and the combination with a soft timer is no longer needed.
**
** \return The system tick in milliseconds.
**
******************************************************************************/
U32 GD_TIMER_ReadTimerStamp(void)
{
#if 0
    U32 Reloadn, CntnSts, temp = 0,nStamp;
    nStamp = nTimeStamp;

    if(gd_timer_sSoftTime[0].timerReg == GD_REG_TIMER1)
    {
        CntnSts = GH_TIMER_get_T1CntnSts();
    }
    else if(gd_timer_sSoftTime[0].timerReg == GD_REG_TIMER2)
    {
        CntnSts = GH_TIMER_get_T2CntnSts();
    }
    else
    {
        CntnSts = GH_TIMER_get_T3CntnSts();
    }

    Reloadn = (GD_GET_APB_ClkHz() / 100);
    if(Reloadn != 0)
    {
        temp = (Reloadn - CntnSts) * 10 / Reloadn;
        temp %= 10;
    }
    return (nStamp + temp);
#else
	//return gkosGetTicks();
	return rt_tick_get();
#endif
}

/*!
*******************************************************************************
**
** \brief  delay in milliseconds.
**
** \param msecs to be delay in milliseconds
**
**
******************************************************************************/
GERR GD_TIMER_Delay(U32 msecs)
{
    U32     start_time = 0;
    U32     end_time = 0;
    int     time_difference  = 0;

    start_time = GD_TIMER_ReadTimerStamp();
    do
    {
        end_time = GD_TIMER_ReadTimerStamp();
        time_difference = (U32)(end_time - start_time);
        /* check overflow */
        if(start_time > end_time)
        {
            time_difference = ((time_difference < 0L) ? -time_difference : time_difference); /* C-LIB code for labs() */
        }
    }while(time_difference < msecs);

    return GD_OK;
}

U32 GD_GET_ARM_ClkHz(void)
{
#ifndef BOARD_FPGA
    return 600000000;
#else
    return 90000000;
#endif
}

U32 GD_GET_AHB_ClkHz(void)
{
#ifndef BOARD_FPGA
    return 138000000;
#else
    return 54000000;
#endif
}

U32 GD_GET_APB_ClkHz(void)
{
    // gk7101_pheriphral_0924_15_25_25.rbf
#ifndef BOARD_FPGA
    return 69000000;
#else
    return 25000000;
#endif
}

U32 GD_GET_UART_ClkHz(void)
{
#ifndef BOARD_FPGA
    return 48000000/2;
#else
    // 115200 gk7101_svn1800_1013_18_27_27_12_75.bit
    // 115200 GK7101_FPGA_SFLASH_0825_v5_27_25_25.rbf
    // 115200 gk7101_pheriphral_0924_15_25_25.rbf
    // 115200 GK7101_FPGA_20140923pm_svn1661_18_25_25.rbf
    // 9600 GK7101_FPGA_20140904_svn996_i2s_sd_enet.rbf
    return 25000000/2;
    //return 27000000/2;
    //9600 gk7101_rs485_0917_27_25_25.rbf
    //9600 gk7101_crypt_0917_v2_18_25_25.rbf
    //return 20000000/2;
#endif
}

U32 GD_GET_IDSP_ClkHz(void)
{
#ifndef BOARD_FPGA
    return 150000000;
#else
    return 18000000;
#endif
}

U32 GD_GET_CORE_ClkHz(void)
{
    return 18000000;
}

U32 GD_GET_DRAM_ClkHz(void)
{
    return 18000000;
}

U32 GD_GET_I2S_ClkHz(void)
{
#ifndef BOARD_FPGA
    return 12288000;
#else
    return 18000000;
#endif
}

U32 GD_GET_SD_ClkHz(void)
{
#ifndef BOARD_FPGA
    return 50180000;
#else
    return 18000000;
#endif
}


/* Version History */
/*****************************************************************************


******************************************************************************/
