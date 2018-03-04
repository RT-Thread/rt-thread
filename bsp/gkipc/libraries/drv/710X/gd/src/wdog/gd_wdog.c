/******************************************************************************
**
** \file      gd_wdog.c
**
** \brief     DEMO test application.
**
**            (C) Goke Microelectronics China 2002 - 2007
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \version   \$Id: gd_wdog.c,v 1.8 2007/01/04 15:13:22 mneuma Exp $
**
******************************************************************************/
#include <stdio.h>
#include <string.h>

#include "gd_wdog.h"
#include "gd_int.h"
#include "gh_wdt.h"

//*****************************************************************************
//*****************************************************************************
//** Local Defines
//*****************************************************************************
//*****************************************************************************
#define INTENABLE  2
#define RSTENABLE  4

//*****************************************************************************
//*****************************************************************************
//** API Functions
//*****************************************************************************
//*****************************************************************************
static GD_INT_DATA_S* wdogHandler(void)
{

    GD_INT_DATA_S* intDataPtr = NULL;

    return( intDataPtr );
}

static GISR1 gd_wdog_isr(void)
{
    GD_INT_HANDLER_F Handler;
    GD_INT_DATA_S*   intDataP;
    Handler  = GD_INT_GetHandler( GD_INT_WDT_IRQ );
    intDataP = Handler();
    if ( intDataP && intDataP->processor )
        intDataP->processor( intDataP->data );
}

GERR GD_Wdog_Init(void)
{
    GERR    ret;
    GD_INT_OPEN_PARAMS_S    paramsInt;
    GD_HANDLE               wdtHandle  = 0;

    /* Open the I2C interrupt */
    paramsInt.active      = GD_INT_NO_INVERT_IRQ;
    paramsInt.sensitivity = GD_INT_BOTH_EDGES;

    paramsInt.type        = GD_INT_WDT_IRQ;
    paramsInt.isrFct.lowPrio = gd_wdog_isr;
    ret = GD_INT_Open(&paramsInt, &wdtHandle);
    GD_INT_SetHandler( paramsInt.type, wdogHandler);

    GD_INT_Enable(&wdtHandle, GD_INT_ENABLED);

    return ret;
}

GERR GD_Wdog_LoadValue(U32 index)
{
    GH_WDT_set_ReloadR(index);
    GH_WDT_set_RestartR(0x4755);
    return GD_OK;
}

GERR GD_Wdog_GetValue(void)
{
    U32 index;
    index = GH_WDT_get_CntStsR();
    return index;
}

GERR GD_Wdog_Enable(U32 index)
{
    if(index & INTENABLE)
    {
        GH_WDT_set_CtrlR_IntEnable(0x01);
    }
    if(index & RSTENABLE)
    {
        GH_WDT_set_CtrlR_ResetEnable(0x01);
    }
    GH_WDT_set_CtrlR_Enable(0x01);
    return GD_OK;

}

GERR GD_Wdog_Disable(void)
{
    GH_WDT_set_CtrlR_IntEnable(0x0);
    GH_WDT_set_CtrlR_ResetEnable(0x0);
    GH_WDT_set_CtrlR_Enable(0x0);
    return GD_OK;

}

GERR GD_Wdog_GetTimeout(void)
{
    U32 index;
    index=GH_WDT_get_TimeoutR();
    return index;
}
GERR GD_Wdog_ClrTimeout(void)
{
    GH_WDT_set_ClrR(0x01);
    return GD_OK;
}

GERR GD_Wdog_Enable_Reset(void)
{
    GH_WDT_set_CtrlR(0x3);
    return GD_OK;
}
